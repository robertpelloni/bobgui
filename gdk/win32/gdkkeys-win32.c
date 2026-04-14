/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2000 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the BOBGUI+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the BOBGUI+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * BOBGUI+ at ftp://ftp.bobgui.org/pub/bobgui/.
 */
#include "config.h"

#include "gdkwin32keys.h"

#include "gdk.h"

#include "gdkprivate-win32.h"
#include "gdkdebugprivate.h"
#include "gdkdisplay-win32.h"
#include "gdkkeysyms.h"
#include "gdkkeysprivate.h"
#include "gdkkeys-win32.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define GDK_MOD2_MASK (1 << 4)

<<<<<<< HEAD
/* GdkWin32Keymap */
=======
#include "gdkprivate-win32.h"
#include "gdkinternals.h"
#include "gdkkeysyms.h"
#include "gdkkeysprivate.h"
#include "gdkwin32keys.h"

enum _GdkWin32KeyLevelState
{
  GDK_WIN32_LEVEL_NONE = 0,
  GDK_WIN32_LEVEL_SHIFT,
  GDK_WIN32_LEVEL_CAPSLOCK,
  GDK_WIN32_LEVEL_SHIFT_CAPSLOCK,
  GDK_WIN32_LEVEL_ALTGR,
  GDK_WIN32_LEVEL_SHIFT_ALTGR,
  GDK_WIN32_LEVEL_CAPSLOCK_ALTGR,
  GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR,
  GDK_WIN32_LEVEL_COUNT
};

typedef enum _GdkWin32KeyLevelState GdkWin32KeyLevelState;

struct _GdkWin32KeyNode
{
  /* Non-spacing version of the dead key */
  guint                  undead_gdk_keycode;

  /* Virtual key code */
  guint8                 vk;

  /* Level for which this virtual key code produces this gdk_keycode */
  GdkWin32KeyLevelState  level;

  /* GDK (X11) code for this key */
  guint                  gdk_keycode;

  /* Array of GdkWin32KeyNode should be sorted by gdk_keycode, then by level */
  GArray                *combinations;
};

typedef struct _GdkWin32KeyNode GdkWin32KeyNode;

/*
Example:
  GdkWin32KeyNode
  {
    undead_gdk_keycode = 0x0b4 GDK_KEY_acute (')
    vk = 0xde VK_OEM_7
    level = GDK_WIN32_LEVEL_NONE
    gdk_keycode = 0xfe51 GDK_KEY_dead_acute
    combinations = 
    {
      GdkWin32KeyNode
      {
        undead_gdk_keycode = 0x061 GDK_KEY_a (a)
        level = GDK_WIN32_LEVEL_NONE
        vk = 0x41 VK_A
        gdk_keycode = 0xe1 GDK_KEY_aacute á
        combinations = NULL
      },
      GdkWin32KeyNode
      {
        unicode_char = 0x041 GDK_KEY_A (A)
        level = GDK_WIN32_LEVEL_SHIFT
        vk = 0x41 VK_A
        gdk_keycode = 0x0c1 GDK_KEY_Aacute Á
        combinations = NULL
      },
      { ... }
    }
  }

Thus:

GDK_KEY_dead_acute + GDK_KEY_a
= GDK_KEY_aacute

GDK_KEY_dead_acute + GDK_KEY_A
= GDK_KEY_Aacute

GDK_KEY_dead_acute + GDK_KEY_s
matches partially
(GDK_KEY_dead_acute is a known dead key, but does not combine with GDK_KEY_s)
and resolves into:
GDK_KEY_acute + GDK_KEY_s

GDK_KEY_dead_somethingelse + GDK_KEY_anything
does not match at all
(W32 API did not provide any deadkey info for GDK_KEY_dead_somethingelse)
and the caller will try other matching mechanisms for compose_buffer
*/

struct _GdkWin32KeyGroupOptions
{
  /* character that should be used as the decimal separator */
  wchar_t         decimal_mark;

  /* Scancode for the VK_RSHIFT */
  guint           scancode_rshift;

  /* TRUE if Ctrl+Alt emulates AltGr */
  gboolean        has_altgr;

  GArray         *dead_keys;
};

typedef struct _GdkWin32KeyGroupOptions GdkWin32KeyGroupOptions;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

struct _GdkWin32KeymapClass
{
  GdkKeymapClass parent_class;
};

struct _GdkWin32Keymap
{
  GdkKeymap parent_instance;

  /* Array of HKL */
  GArray *layout_handles;

<<<<<<< HEAD
  /* Array of GdkWin32KeymapLayoutInfo */
  GArray *layout_infos;
=======
  /* VirtualKeyCode -> gdk_keyval table
   * length = 256 * length(layout_handles) * 2 * 4
   * 256 is the number of virtual key codes,
   * 2x4 is the number of Shift/AltGr/CapsLock combinations (level),
   * length(layout_handles) is the number of layout handles (group).
   */
  guint  *keysym_tab;

  /* length = length(layout_handles), type =  GdkWin32KeyGroupOptions
   * Kept separate from layout_handles because layout_handles is
   * populated by W32 API.
   */
  GArray *options;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

  /* Index of a handle in layout_handles,
   * at any point it should be the same handle as GetKeyboardLayout(0) returns,
   * but GDK caches it to avoid calling GetKeyboardLayout (0) every time.
   */
  guint8 active_layout;

  guint current_serial;

  /* Pointer to the implementation to be used. See comment in gdkkeys-win32.h.
   * (we will dynamically choose at runtime for 32-bit builds based on whether
   * we are running under WOW64)
   */
  const GdkWin32KeymapImpl *gdkwin32_keymap_impl;
};

G_DEFINE_TYPE (GdkWin32Keymap, gdk_win32_keymap, GDK_TYPE_KEYMAP)

/* forward declarations */
static void update_keymap              (GdkWin32Keymap *gdk_keymap);
static void clear_keyboard_layout_info (gpointer        data);

static void
gdk_win32_keymap_init (GdkWin32Keymap *keymap)
{
  /* Regular implementation (32 bit & 64 bit) */
  extern const GdkWin32KeymapImpl gdkwin32_keymap_impl;
  /* Implementation for 32 bit applications running on a 64 bit host (WOW64). */
#ifndef _WIN64
  extern const GdkWin32KeymapImpl gdkwin32_keymap_impl_wow64;
#endif

  keymap->layout_infos = g_array_new (FALSE, TRUE,
                                      sizeof (GdkWin32KeymapLayoutInfo));
  g_array_set_clear_func (keymap->layout_infos,
                          clear_keyboard_layout_info);

  keymap->layout_handles = g_array_new (FALSE, FALSE,
                                        sizeof (GdkWin32KeymapLayoutInfo));
  keymap->active_layout = 0;

  keymap->gdkwin32_keymap_impl = &gdkwin32_keymap_impl;
#ifndef _WIN64
  if (_gdk_win32_check_processor (GDK_WIN32_WOW64))
    keymap->gdkwin32_keymap_impl = &gdkwin32_keymap_impl_wow64;
#endif
}

static void
gdk_win32_keymap_constructed (GObject *object)
{
  GdkWin32Keymap *keymap;

  keymap = GDK_WIN32_KEYMAP (object);
  update_keymap (keymap);
}

static void
gdk_win32_keymap_finalize (GObject *object)
{
  GdkWin32Keymap *keymap = GDK_WIN32_KEYMAP (object);

  g_clear_pointer (&keymap->layout_handles, g_array_unref);
  g_clear_pointer (&keymap->layout_infos, g_array_unref);

  G_OBJECT_CLASS (gdk_win32_keymap_parent_class)->finalize (object);
}

<<<<<<< HEAD
/* Convenience wrapper functions */
=======
#ifdef G_ENABLE_DEBUG
static void
print_keysym_tab (GdkWin32Keymap *keymap)
{
  gint                      li;
  GdkWin32KeyGroupOptions  *options;
  gint                      vk;
  GdkWin32KeyLevelState     level;
  gint                      group_size = keymap->layout_handles->len;

  for (li = 0; li < group_size; li++)
    {
      options = &g_array_index (keymap->options, GdkWin32KeyGroupOptions, li);
      g_print ("keymap %d (0x%p):%s\n",
               li, g_array_index (keymap->layout_handles, HKL, li),
               options->has_altgr ? " (uses AltGr)" : "");

      for (vk = 0; vk < KEY_STATE_SIZE; vk++)
        {
          g_print ("%#.02x: ", vk);

          for (level = 0; level < GDK_WIN32_LEVEL_COUNT; level++)
            {
              gchar *name = gdk_keyval_name (keymap->keysym_tab[vk * group_size * GDK_WIN32_LEVEL_COUNT + level]);

              g_print ("%s ", name ? name : "(none)");
            }

          g_print ("\n");
        }
    }
}
#endif

static void
handle_special (guint  vk,
		guint *ksymp,
		gint   shift)

{
  switch (vk)
    {
    case VK_CANCEL:
      *ksymp = GDK_KEY_Cancel; break;
    case VK_BACK:
      *ksymp = GDK_KEY_BackSpace; break;
    case VK_TAB:
      if (shift & 0x1)
	*ksymp = GDK_KEY_ISO_Left_Tab;
      else
	*ksymp = GDK_KEY_Tab;
      break;
    case VK_CLEAR:
      *ksymp = GDK_KEY_Clear; break;
    case VK_RETURN:
      *ksymp = GDK_KEY_Return; break;
    case VK_SHIFT:
    case VK_LSHIFT:
      *ksymp = GDK_KEY_Shift_L; break;
    case VK_CONTROL:
    case VK_LCONTROL:
      *ksymp = GDK_KEY_Control_L; break;
    case VK_MENU:
    case VK_LMENU:
      *ksymp = GDK_KEY_Alt_L; break;
    case VK_PAUSE:
      *ksymp = GDK_KEY_Pause; break;
    case VK_ESCAPE:
      *ksymp = GDK_KEY_Escape; break;
    case VK_PRIOR:
      *ksymp = GDK_KEY_Prior; break;
    case VK_NEXT:
      *ksymp = GDK_KEY_Next; break;
    case VK_END:
      *ksymp = GDK_KEY_End; break;
    case VK_HOME:
      *ksymp = GDK_KEY_Home; break;
    case VK_LEFT:
      *ksymp = GDK_KEY_Left; break;
    case VK_UP:
      *ksymp = GDK_KEY_Up; break;
    case VK_RIGHT:
      *ksymp = GDK_KEY_Right; break;
    case VK_DOWN:
      *ksymp = GDK_KEY_Down; break;
    case VK_SELECT:
      *ksymp = GDK_KEY_Select; break;
    case VK_PRINT:
      *ksymp = GDK_KEY_Print; break;
    case VK_SNAPSHOT:
      *ksymp = GDK_KEY_Print; break;
    case VK_EXECUTE:
      *ksymp = GDK_KEY_Execute; break;
    case VK_INSERT:
      *ksymp = GDK_KEY_Insert; break;
    case VK_DELETE:
      *ksymp = GDK_KEY_Delete; break;
    case VK_HELP:
      *ksymp = GDK_KEY_Help; break;
    case VK_LWIN:
      *ksymp = GDK_KEY_Meta_L; break;
    case VK_RWIN:
      *ksymp = GDK_KEY_Meta_R; break;
    case VK_APPS:
      *ksymp = GDK_KEY_Menu; break;
    case VK_DECIMAL:
      *ksymp = GDK_KEY_KP_Decimal; break;
    case VK_MULTIPLY:
      *ksymp = GDK_KEY_KP_Multiply; break;
    case VK_ADD:
      *ksymp = GDK_KEY_KP_Add; break;
    case VK_SEPARATOR:
      *ksymp = GDK_KEY_KP_Separator; break;
    case VK_SUBTRACT:
      *ksymp = GDK_KEY_KP_Subtract; break;
    case VK_DIVIDE:
      *ksymp = GDK_KEY_KP_Divide; break;
    case VK_NUMPAD0:
      *ksymp = GDK_KEY_KP_0; break;
    case VK_NUMPAD1:
      *ksymp = GDK_KEY_KP_1; break;
    case VK_NUMPAD2:
      *ksymp = GDK_KEY_KP_2; break;
    case VK_NUMPAD3:
      *ksymp = GDK_KEY_KP_3; break;
    case VK_NUMPAD4:
      *ksymp = GDK_KEY_KP_4; break;
    case VK_NUMPAD5:
      *ksymp = GDK_KEY_KP_5; break;
    case VK_NUMPAD6:
      *ksymp = GDK_KEY_KP_6; break;
    case VK_NUMPAD7:
      *ksymp = GDK_KEY_KP_7; break;
    case VK_NUMPAD8:
      *ksymp = GDK_KEY_KP_8; break;
    case VK_NUMPAD9:
      *ksymp = GDK_KEY_KP_9; break;
    case VK_F1:
      *ksymp = GDK_KEY_F1; break;
    case VK_F2:
      *ksymp = GDK_KEY_F2; break;
    case VK_F3:
      *ksymp = GDK_KEY_F3; break;
    case VK_F4:
      *ksymp = GDK_KEY_F4; break;
    case VK_F5:
      *ksymp = GDK_KEY_F5; break;
    case VK_F6:
      *ksymp = GDK_KEY_F6; break;
    case VK_F7:
      *ksymp = GDK_KEY_F7; break;
    case VK_F8:
      *ksymp = GDK_KEY_F8; break;
    case VK_F9:
      *ksymp = GDK_KEY_F9; break;
    case VK_F10:
      *ksymp = GDK_KEY_F10; break;
    case VK_F11:
      *ksymp = GDK_KEY_F11; break;
    case VK_F12:
      *ksymp = GDK_KEY_F12; break;
    case VK_F13:
      *ksymp = GDK_KEY_F13; break;
    case VK_F14:
      *ksymp = GDK_KEY_F14; break;
    case VK_F15:
      *ksymp = GDK_KEY_F15; break;
    case VK_F16:
      *ksymp = GDK_KEY_F16; break;
    case VK_F17:
      *ksymp = GDK_KEY_F17; break;
    case VK_F18:
      *ksymp = GDK_KEY_F18; break;
    case VK_F19:
      *ksymp = GDK_KEY_F19; break;
    case VK_F20:
      *ksymp = GDK_KEY_F20; break;
    case VK_F21:
      *ksymp = GDK_KEY_F21; break;
    case VK_F22:
      *ksymp = GDK_KEY_F22; break;
    case VK_F23:
      *ksymp = GDK_KEY_F23; break;
    case VK_F24:
      *ksymp = GDK_KEY_F24; break;
    case VK_NUMLOCK:
      *ksymp = GDK_KEY_Num_Lock; break;
    case VK_SCROLL:
      *ksymp = GDK_KEY_Scroll_Lock; break;
    case VK_RSHIFT:
      *ksymp = GDK_KEY_Shift_R; break;
    case VK_RCONTROL:
      *ksymp = GDK_KEY_Control_R; break;
    case VK_RMENU:
      *ksymp = GDK_KEY_Alt_R; break;
    }
}

static void
set_level_vks (guchar               *key_state,
	       GdkWin32KeyLevelState level)
{
  switch (level)
    {
    case GDK_WIN32_LEVEL_NONE:
      key_state[VK_SHIFT] = 0;
      key_state[VK_CAPITAL] = 0;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0;
      break;
    case GDK_WIN32_LEVEL_SHIFT:
      key_state[VK_SHIFT] = 0x80;
      key_state[VK_CAPITAL] = 0;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0;
      break;
    case GDK_WIN32_LEVEL_CAPSLOCK:
      key_state[VK_SHIFT] = 0;
      key_state[VK_CAPITAL] = 0x01;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0;
      break;
    case GDK_WIN32_LEVEL_SHIFT_CAPSLOCK:
      key_state[VK_SHIFT] = 0x80;
      key_state[VK_CAPITAL] = 0x01;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0;
      break;
    case GDK_WIN32_LEVEL_ALTGR:
      key_state[VK_SHIFT] = 0;
      key_state[VK_CAPITAL] = 0;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0x80;
      break;
    case GDK_WIN32_LEVEL_SHIFT_ALTGR:
      key_state[VK_SHIFT] = 0x80;
      key_state[VK_CAPITAL] = 0;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0x80;
      break;
    case GDK_WIN32_LEVEL_CAPSLOCK_ALTGR:
      key_state[VK_SHIFT] = 0;
      key_state[VK_CAPITAL] = 0x01;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0x80;
      break;
    case GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR:
      key_state[VK_SHIFT] = 0x80;
      key_state[VK_CAPITAL] = 0x01;
      key_state[VK_CONTROL] = key_state[VK_MENU] = 0x80;
      break;
    case GDK_WIN32_LEVEL_COUNT:
      g_assert_not_reached ();
      break;
    }
}

static void
reset_after_dead (guchar key_state[KEY_STATE_SIZE],
                  HKL    handle)
{
  guchar  temp_key_state[KEY_STATE_SIZE];
  wchar_t wcs[2];

  memmove (temp_key_state, key_state, KEY_STATE_SIZE);

  temp_key_state[VK_SHIFT] =
    temp_key_state[VK_CONTROL] =
    temp_key_state[VK_CAPITAL] =
    temp_key_state[VK_MENU] = 0;

  ToUnicodeEx (VK_SPACE, MapVirtualKey (VK_SPACE, 0),
	       temp_key_state, wcs, G_N_ELEMENTS (wcs),
	       0, handle);
}

static void
handle_dead (guint  keysym,
	     guint *ksymp)
{
  switch (keysym)
    {
    case '"': /* 0x022 */
      *ksymp = GDK_KEY_dead_diaeresis; break;
    case '\'': /* 0x027 */
      *ksymp = GDK_KEY_dead_acute; break;
    case GDK_KEY_asciicircum: /* 0x05e */
      *ksymp = GDK_KEY_dead_circumflex; break;
    case GDK_KEY_grave:	/* 0x060 */
      *ksymp = GDK_KEY_dead_grave; break;
    case GDK_KEY_asciitilde: /* 0x07e */
      *ksymp = GDK_KEY_dead_tilde; break;
    case GDK_KEY_diaeresis: /* 0x0a8 */
      *ksymp = GDK_KEY_dead_diaeresis; break;
    case GDK_KEY_degree: /* 0x0b0 */
      *ksymp = GDK_KEY_dead_abovering; break;
    case GDK_KEY_acute:	/* 0x0b4 */
      *ksymp = GDK_KEY_dead_acute; break;
    case GDK_KEY_periodcentered: /* 0x0b7 */
      *ksymp = GDK_KEY_dead_abovedot; break;
    case GDK_KEY_cedilla: /* 0x0b8 */
      *ksymp = GDK_KEY_dead_cedilla; break;
    case GDK_KEY_breve:	/* 0x1a2 */
      *ksymp = GDK_KEY_dead_breve; break;
    case GDK_KEY_ogonek: /* 0x1b2 */
      *ksymp = GDK_KEY_dead_ogonek; break;
    case GDK_KEY_caron:	/* 0x1b7 */
      *ksymp = GDK_KEY_dead_caron; break;
    case GDK_KEY_doubleacute: /* 0x1bd */
      *ksymp = GDK_KEY_dead_doubleacute; break;
    case GDK_KEY_abovedot: /* 0x1ff */
      *ksymp = GDK_KEY_dead_abovedot; break;
    case 0x1000384: /* Greek tonos */
      *ksymp = GDK_KEY_dead_acute; break;
    case GDK_KEY_Greek_accentdieresis: /* 0x7ae */
      *ksymp = GDK_KEY_Greek_accentdieresis; break;
    default:
      /* By default use the keysym as such. This takes care of for
       * instance the dead U+09CD (BENGALI VIRAMA) on the ekushey
       * Bengali layout.
       */
      *ksymp = keysym; break;
    }
}

/* keypad decimal mark depends on active keyboard layout
 * return current decimal mark as unicode character
 */
guint32
_gdk_win32_keymap_get_decimal_mark (GdkWin32Keymap *keymap)
{
  if (keymap != NULL &&
      keymap->layout_handles->len > 0 &&
      g_array_index (keymap->options, GdkWin32KeyGroupOptions, keymap->active_layout).decimal_mark)
    return g_array_index (keymap->options, GdkWin32KeyGroupOptions, keymap->active_layout).decimal_mark;

  return (guint32) '.';
}
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

static gboolean
load_layout_dll (GdkWin32Keymap           *keymap,
                 const char               *dll,
                 GdkWin32KeymapLayoutInfo *info)
{
  return keymap->gdkwin32_keymap_impl->load_layout_dll (dll, info);
}

static void
init_vk_lookup_table (GdkWin32Keymap           *keymap,
                      GdkWin32KeymapLayoutInfo *info)
{
  keymap->gdkwin32_keymap_impl->init_vk_lookup_table (info);
}

static BYTE
keystate_to_modbits (GdkWin32Keymap           *keymap,
                     GdkWin32KeymapLayoutInfo *info,
                     const BYTE                keystate[256])
{
  return keymap->gdkwin32_keymap_impl->keystate_to_modbits (info, keystate);
}

static BYTE
modbits_to_level (GdkWin32Keymap           *keymap,
                  GdkWin32KeymapLayoutInfo *info,
                  BYTE                      modbits)
{
  return keymap->gdkwin32_keymap_impl->modbits_to_level (info, modbits);
}

static WCHAR
vk_to_char_fuzzy (GdkWin32Keymap           *keymap,
                  GdkWin32KeymapLayoutInfo *info,
                  BYTE                      mod_bits,
                  BYTE                      lock_bits,
                  BYTE                     *consumed_mod_bits,
                  gboolean                 *is_dead,
                  BYTE                      vk)
{
  return keymap->gdkwin32_keymap_impl->vk_to_char_fuzzy (info, mod_bits, lock_bits,
                                                         consumed_mod_bits, is_dead, vk);
}

/*
 * Return the keyboard layout according to the user's keyboard layout
 * substitution preferences.
 *
 * The result is heap-allocated and should be freed with g_free().
 */
static char*
get_keyboard_layout_substituted_name (const char *layout_name)
{
  HKEY     hkey     = 0;
  DWORD    var_type = REG_SZ;
  char    *result   = NULL;
  DWORD    buf_len  = 0;
  LSTATUS  status;

  static const char *substitute_path = "Keyboard Layout\\Substitutes";

  status = RegOpenKeyExA (HKEY_CURRENT_USER, substitute_path, 0,
                          KEY_QUERY_VALUE, &hkey);
  if (status != ERROR_SUCCESS)
    {
      /* No substitute set for this value, not sure if this is a normal case */
      g_warning("Could not open registry key '%s'. Error code: %d",
                substitute_path, (int)status);

      goto fail1;
    }

  status = RegQueryValueExA (hkey, layout_name, 0, &var_type, 0, &buf_len);
  if (status != ERROR_SUCCESS)
    {
      g_debug("Could not query registry key '%s\\%s'. Error code: %d",
              substitute_path, layout_name, (int)status);
      goto fail2;
    }

  /* Allocate buffer */
  result = (char*) g_malloc (buf_len);

  /* Retrieve substitute name */
  status = RegQueryValueExA (hkey, layout_name, 0, &var_type,
                             (LPBYTE) result, &buf_len);
  if (status != ERROR_SUCCESS)
    {
      g_warning("Could not obtain registry value at key '%s\\%s'. "
                "Error code: %d",
                substitute_path, layout_name, (int)status);
      goto fail3;
    }

  RegCloseKey (hkey);
  return result;

fail3:
  g_free (result);
fail2:
  RegCloseKey (hkey);
fail1:
  return NULL;
}

static char*
_get_keyboard_layout_file (const char *layout_name)
{
  HKEY     hkey              = 0;
  DWORD    var_type          = REG_SZ;
  char    *result            = NULL;
  DWORD    file_name_len     = 0;
  int      dir_len           = 0;
  int      buf_len           = 0;
  LSTATUS  status;

  static const char prefix[] = "SYSTEM\\CurrentControlSet\\Control\\"
                               "Keyboard Layouts\\";
  char kbdKeyPath[sizeof (prefix) + KL_NAMELENGTH];

  g_snprintf (kbdKeyPath, sizeof (prefix) + KL_NAMELENGTH, "%s%s",
              prefix, layout_name);

  status = RegOpenKeyExA (HKEY_LOCAL_MACHINE, (LPCSTR) kbdKeyPath, 0,
                          KEY_QUERY_VALUE, &hkey);
  if (status == ERROR_FILE_NOT_FOUND)
    {
      return NULL;
    }
  else if (status != ERROR_SUCCESS)
    {
      g_warning("Could not open registry key '%s'. Error code: %d",
                kbdKeyPath, (int)status);
      return NULL;
    }

  /* Get sizes */
  status = RegQueryValueExA (hkey, "Layout File", 0, &var_type, 0,
                             &file_name_len);
  if (status != ERROR_SUCCESS)
    {
      g_warning("Could not query registry key '%s\\Layout File'. Error code: %d",
                kbdKeyPath, (int)status);
      goto fail_close_key;
    }

  dir_len = GetSystemDirectoryA (0, 0); /* includes \0 */
  if (dir_len == 0)
    {
      g_warning("GetSystemDirectoryA failed. Error: %d", (int)GetLastError());
      goto fail_close_key;
    }

  /* Allocate buffer */
  buf_len = dir_len + (int) strlen ("\\") + file_name_len;
  result = (char*) g_malloc (buf_len);

  /* Append system directory. The -1 is because dir_len includes \0 */
  if (GetSystemDirectoryA (&result[0], dir_len) != dir_len - 1)
    goto fail_free_result;

  /* Append directory separator */
  result[dir_len - 1] = '\\';

  /* Append file name */
  status = RegQueryValueExA (hkey, "Layout File", 0, &var_type,
                             (LPBYTE) &result[dir_len], &file_name_len);
  if (status != ERROR_SUCCESS)
    goto fail_free_result;

  result[dir_len + file_name_len] = '\0';

  RegCloseKey (hkey);
  return result;

fail_free_result:
  g_free (result);
fail_close_key:
  RegCloseKey (hkey);
  return NULL;
}

/*
 * Get the file path of the keyboard layout dll.
 * The result is heap-allocated and should be freed with g_free().
 */
static char*
get_keyboard_layout_file (const char *layout_name)
{
  char *result = _get_keyboard_layout_file (layout_name);

  /* If we could not retrieve a path, it may be that we need to perform layout
   * substitution
   */
  if (result == NULL)
    {
      char *substituted = get_keyboard_layout_substituted_name (layout_name);
      result = _get_keyboard_layout_file (substituted);
      g_free (substituted);
    }

  return result;
}

static void
clear_keyboard_layout_info (gpointer data)
{
  GdkWin32KeymapLayoutInfo *layout_info = (GdkWin32KeymapLayoutInfo*) data;

  g_free (layout_info->file);

  if (layout_info->key_entries != NULL)
    g_array_unref (layout_info->key_entries);

  if (layout_info->reverse_lookup_table != NULL)
    g_hash_table_destroy (layout_info->reverse_lookup_table);

  if (layout_info->lib != NULL)
    FreeLibrary (layout_info->lib);

  memset (layout_info, 0, sizeof (GdkWin32KeymapLayoutInfo));
}

#define DEFINE_SPECIAL(map)                 \
  map (VK_CANCEL,     GDK_KEY_Cancel)       \
  map (VK_BACK,       GDK_KEY_BackSpace)    \
  map (VK_CLEAR,      GDK_KEY_Clear)        \
  map (VK_RETURN,     GDK_KEY_Return)       \
  map (VK_LSHIFT,     GDK_KEY_Shift_L)      \
  map (VK_LCONTROL,   GDK_KEY_Control_L)    \
  map (VK_LMENU,      GDK_KEY_Alt_L)        \
  map (VK_PAUSE,      GDK_KEY_Pause)        \
  map (VK_ESCAPE,     GDK_KEY_Escape)       \
  map (VK_PRIOR,      GDK_KEY_Prior)        \
  map (VK_NEXT,       GDK_KEY_Next)         \
  map (VK_END,        GDK_KEY_End)          \
  map (VK_HOME,       GDK_KEY_Home)         \
  map (VK_LEFT,       GDK_KEY_Left)         \
  map (VK_UP,         GDK_KEY_Up)           \
  map (VK_RIGHT,      GDK_KEY_Right)        \
  map (VK_DOWN,       GDK_KEY_Down)         \
  map (VK_SELECT,     GDK_KEY_Select)       \
  map (VK_PRINT,      GDK_KEY_Print)        \
  map (VK_EXECUTE,    GDK_KEY_Execute)      \
  map (VK_INSERT,     GDK_KEY_Insert)       \
  map (VK_DELETE,     GDK_KEY_Delete)       \
  map (VK_HELP,       GDK_KEY_Help)         \
  map (VK_LWIN,       GDK_KEY_Meta_L)       \
  map (VK_RWIN,       GDK_KEY_Meta_R)       \
  map (VK_APPS,       GDK_KEY_Menu)         \
  map (VK_DECIMAL,    GDK_KEY_KP_Decimal)   \
  map (VK_MULTIPLY,   GDK_KEY_KP_Multiply)  \
  map (VK_ADD,        GDK_KEY_KP_Add)       \
  map (VK_SEPARATOR,  GDK_KEY_KP_Separator) \
  map (VK_SUBTRACT,   GDK_KEY_KP_Subtract)  \
  map (VK_DIVIDE,     GDK_KEY_KP_Divide)    \
  map (VK_NUMPAD0,    GDK_KEY_KP_0)         \
  map (VK_NUMPAD1,    GDK_KEY_KP_1)         \
  map (VK_NUMPAD2,    GDK_KEY_KP_2)         \
  map (VK_NUMPAD3,    GDK_KEY_KP_3)         \
  map (VK_NUMPAD4,    GDK_KEY_KP_4)         \
  map (VK_NUMPAD5,    GDK_KEY_KP_5)         \
  map (VK_NUMPAD6,    GDK_KEY_KP_6)         \
  map (VK_NUMPAD7,    GDK_KEY_KP_7)         \
  map (VK_NUMPAD8,    GDK_KEY_KP_8)         \
  map (VK_NUMPAD9,    GDK_KEY_KP_9)         \
  map (VK_F1,         GDK_KEY_F1)           \
  map (VK_F2,         GDK_KEY_F2)           \
  map (VK_F3,         GDK_KEY_F3)           \
  map (VK_F4,         GDK_KEY_F4)           \
  map (VK_F5,         GDK_KEY_F5)           \
  map (VK_F6,         GDK_KEY_F6)           \
  map (VK_F7,         GDK_KEY_F7)           \
  map (VK_F8,         GDK_KEY_F8)           \
  map (VK_F9,         GDK_KEY_F9)           \
  map (VK_F10,        GDK_KEY_F10)          \
  map (VK_F11,        GDK_KEY_F11)          \
  map (VK_F12,        GDK_KEY_F12)          \
  map (VK_F13,        GDK_KEY_F13)          \
  map (VK_F14,        GDK_KEY_F14)          \
  map (VK_F15,        GDK_KEY_F15)          \
  map (VK_F16,        GDK_KEY_F16)          \
  map (VK_F17,        GDK_KEY_F17)          \
  map (VK_F18,        GDK_KEY_F18)          \
  map (VK_F19,        GDK_KEY_F19)          \
  map (VK_F20,        GDK_KEY_F20)          \
  map (VK_F21,        GDK_KEY_F21)          \
  map (VK_F22,        GDK_KEY_F22)          \
  map (VK_F23,        GDK_KEY_F23)          \
  map (VK_F24,        GDK_KEY_F24)          \
  map (VK_NUMLOCK,    GDK_KEY_Num_Lock)     \
  map (VK_SCROLL,     GDK_KEY_Scroll_Lock)  \
  map (VK_RSHIFT,     GDK_KEY_Shift_R)      \
  map (VK_RCONTROL,   GDK_KEY_Control_R)    \
  map (VK_RMENU,      GDK_KEY_Alt_R)        \
  map (VK_CAPITAL,    GDK_KEY_Caps_Lock)


#define DEFINE_DEAD(map)                                                      \
  map ('"',                          /* 0x022 */ GDK_KEY_dead_diaeresis)      \
  map ('\'',                         /* 0x027 */ GDK_KEY_dead_acute)          \
  map (GDK_KEY_asciicircum,          /* 0x05e */ GDK_KEY_dead_circumflex)     \
  map (GDK_KEY_grave,                /* 0x060 */ GDK_KEY_dead_grave)          \
  map (GDK_KEY_asciitilde,           /* 0x07e */ GDK_KEY_dead_tilde)          \
  map (GDK_KEY_diaeresis,            /* 0x0a8 */ GDK_KEY_dead_diaeresis)      \
  map (GDK_KEY_degree,               /* 0x0b0 */ GDK_KEY_dead_abovering)      \
  map (GDK_KEY_acute,                /* 0x0b4 */ GDK_KEY_dead_acute)          \
  map (GDK_KEY_periodcentered,       /* 0x0b7 */ GDK_KEY_dead_abovedot)       \
  map (GDK_KEY_cedilla,              /* 0x0b8 */ GDK_KEY_dead_cedilla)        \
  map (GDK_KEY_breve,                /* 0x1a2 */ GDK_KEY_dead_breve)          \
  map (GDK_KEY_ogonek,               /* 0x1b2 */ GDK_KEY_dead_ogonek)         \
  map (GDK_KEY_caron,                /* 0x1b7 */ GDK_KEY_dead_caron)          \
  map (GDK_KEY_doubleacute,          /* 0x1bd */ GDK_KEY_dead_doubleacute)    \
  map (GDK_KEY_abovedot,             /* 0x1ff */ GDK_KEY_dead_abovedot)       \
  map (0x1000384,              /* Greek tonos */ GDK_KEY_dead_acute)          \
  map (GDK_KEY_Greek_accentdieresis, /* 0x7ae */ GDK_KEY_Greek_accentdieresis)


static guint
vk_and_mod_bits_to_gdk_keysym (GdkWin32Keymap     *keymap,
                               GdkWin32KeymapLayoutInfo *info,
                               guint               vk,
                               BYTE                mod_bits,
                               BYTE                lock_bits,
                               BYTE               *consumed_mod_bits)

{
  gboolean is_dead = FALSE;
  gunichar c;
  guint    sym;

  if (consumed_mod_bits)
    *consumed_mod_bits = 0;

  /* Handle special key: Tab */
  if (vk == VK_TAB)
    {
      if (consumed_mod_bits)
        *consumed_mod_bits = mod_bits & KBDSHIFT;
      return (mod_bits & KBDSHIFT) ? GDK_KEY_ISO_Left_Tab : GDK_KEY_Tab;
    }

  /* Handle other special keys */
  switch (vk)
    {
      #define MAP(a_vk, a_gdk) case a_vk: return a_gdk;

      DEFINE_SPECIAL (MAP)

      /* Non-bijective mappings: */
      MAP (VK_SHIFT,    GDK_KEY_Shift_L)
      MAP (VK_CONTROL,  GDK_KEY_Control_L)
      MAP (VK_MENU,     GDK_KEY_Alt_L)
      MAP (VK_SNAPSHOT, GDK_KEY_Print)

      #undef MAP
    }

  /* Handle regular keys (including dead keys) */
  c = vk_to_char_fuzzy (keymap, info, mod_bits, lock_bits,
                        consumed_mod_bits, &is_dead, vk);

  if (c == WCH_NONE)
    return GDK_KEY_VoidSymbol;

  sym = gdk_unicode_to_keyval (c);

  if (is_dead)
    {
      switch (sym)
	{
	  #define MAP(a_nondead, a_dead) case a_nondead: return a_dead;
	  DEFINE_DEAD (MAP)
	  #undef MAP
	}
    }

  return sym;
}

static int
gdk_keysym_to_key_entry_index (GdkWin32KeymapLayoutInfo *info,
                               guint               sym)
{
  gunichar c;
  gintptr  index;

  if (info->reverse_lookup_table == NULL)
    return -1;

  /* Special cases */
  if (sym == GDK_KEY_Tab)
    return VK_TAB;
  if (sym == GDK_KEY_ISO_Left_Tab)
    return 256;

  /* Generic non-printable keys */
  switch (sym)
    {
      #define MAP(a_vk, a_gdk) case a_gdk: return a_vk;
      DEFINE_SPECIAL (MAP)
      #undef MAP
    }

  /* Fix up dead keys */
  #define MAP(a_nondead, a_dead) \
    if (sym == a_dead)           \
      sym = a_nondead;
  DEFINE_DEAD (MAP)
  #undef MAP

  /* Try converting to Unicode and back */
  c = gdk_keyval_to_unicode (sym);

  index = -1;
  if (g_hash_table_lookup_extended (info->reverse_lookup_table,
                                    GINT_TO_POINTER (c),
                                    NULL, (gpointer*) &index))
    {
      return index;
    }
  else
    {
      return -1;
    }
}

static GdkModifierType
mod_bits_to_gdk_mod_mask (BYTE mod_bits)
{
  GdkModifierType result = 0;
  if (mod_bits & KBDSHIFT)
    result |= GDK_SHIFT_MASK;
  if (mod_bits & KBDCTRL)
    result |= GDK_CONTROL_MASK;
  if (mod_bits & KBDALT)
    result |= GDK_ALT_MASK;
  return result;
}

static BYTE
gdk_mod_mask_to_mod_bits (GdkModifierType mod_mask)
{
  BYTE result = 0;
  if (mod_mask & GDK_SHIFT_MASK)
    result |= KBDSHIFT;
  if (mod_mask & GDK_CONTROL_MASK)
    result |= KBDCTRL;
  if (mod_mask & GDK_ALT_MASK)
    result |= KBDALT;
  return result;
}

static void
update_keymap (GdkWin32Keymap *keymap)
{
  HKL  current_layout;
  BOOL changed = FALSE;
  int  n_layouts;
  int  i;
  GdkWin32Display *display = GDK_WIN32_DISPLAY (GDK_KEYMAP (keymap)->display);


  if (keymap->current_serial == gdk_win32_display_get_keymap_serial (display) &&
      keymap->layout_handles->len > 0)
    {
      return;
    }

  n_layouts = GetKeyboardLayoutList (0, 0);
  g_array_set_size (keymap->layout_handles, n_layouts);
  n_layouts = GetKeyboardLayoutList (n_layouts,
		                     &g_array_index(keymap->layout_handles,
				                    HKL, 0));

  g_array_set_size (keymap->layout_infos, n_layouts);

  current_layout = GetKeyboardLayout (0);

  for (i = 0; i < n_layouts; ++i)
    {
      GdkWin32KeymapLayoutInfo *info = &g_array_index(keymap->layout_infos,
                                                      GdkWin32KeymapLayoutInfo, i);
      HKL hkl = g_array_index(keymap->layout_handles, HKL, i);

      if (info->handle != hkl)
        {
          changed = TRUE;

          /* Free old data */
          clear_keyboard_layout_info (info);

          /* Load new data */
          info->handle = hkl;
          ActivateKeyboardLayout (hkl, 0);
          GetKeyboardLayoutNameA (info->name);

          info->file = get_keyboard_layout_file (info->name);

          if (info->file != NULL && load_layout_dll (keymap, info->file, info))
            {
              info->key_entries = g_array_new (FALSE, FALSE,
                                               sizeof (GdkWin32KeymapKeyEntry));

              info->reverse_lookup_table = g_hash_table_new (g_direct_hash,
                                                             g_direct_equal);
              init_vk_lookup_table (keymap, info);
            }
          else
            {
              g_warning("Failed to load keyboard layout DLL for layout %s: %s",
                        info->name, info->file);
            }
        }

<<<<<<< HEAD
      if (info->handle == current_layout)
=======
  GDK_NOTE (EVENTS, g_print ("\n"));

  keysym_tab_size = hkls_len * 256 * 2 * 4;

  if (hkls_len != keymap->layout_handles->len)
    keymap->keysym_tab = g_renew (guint, keymap->keysym_tab, keysym_tab_size);

  memset (keymap->keysym_tab, 0, keysym_tab_size);
  g_array_set_size (keymap->layout_handles, hkls_len);
  g_array_set_size (keymap->options, hkls_len);

  for (i = 0; i < hkls_len; i++)
    {
      options = &g_array_index (keymap->options, GdkWin32KeyGroupOptions, i);

      options->decimal_mark = 0;
      options->scancode_rshift = 0;
      options->has_altgr = FALSE;
      options->dead_keys = g_array_new (FALSE, FALSE, sizeof (GdkWin32KeyNode));
      g_array_set_clear_func (options->dead_keys, (GDestroyNotify) gdk_win32_key_node_clear);

      g_array_index (keymap->layout_handles, HKL, i) = hkls[i];

      if (hkls[i] == _gdk_input_locale)
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
        keymap->active_layout = i;
    }

  if (changed)
    {
      GdkSeat *seat;
      GdkDevice *device;

<<<<<<< HEAD
      ActivateKeyboardLayout (current_layout, 0);

      seat = gdk_display_get_default_seat (GDK_DISPLAY (display));
      device = gdk_seat_get_keyboard (seat);
      g_object_notify (G_OBJECT (device), "active-layout-index");
      g_object_notify (G_OBJECT (device), "layout-names");
    }

  keymap->current_serial = gdk_win32_display_get_keymap_serial (display);
=======
          /* MapVirtualKeyEx() fails to produce a scancode for VK_DIVIDE and VK_PAUSE.
           * Ignore that, handle_special() will figure out a Gdk keyval for these
           * without needing a scancode.
           */
          if (scancode == 0 &&
              vk != VK_DIVIDE &&
              vk != VK_PAUSE)
            {
              for (level = GDK_WIN32_LEVEL_NONE; level < GDK_WIN32_LEVEL_COUNT; level++)
                keygroup[level] = GDK_KEY_VoidSymbol;

              continue;
            }

          if (vk == VK_RSHIFT)
            options->scancode_rshift = scancode;

          key_state[vk] = 0x80;

          for (level = GDK_WIN32_LEVEL_NONE; level < GDK_WIN32_LEVEL_COUNT; level++)
            {
              guint *ksymp = &keygroup[level];

              set_level_vks (key_state, level);

              *ksymp = 0;

              /* First, handle those virtual keys that we always want
               * as special GDK_* keysyms, even if ToAsciiEx might
               * turn some them into a ASCII character (like TAB and
               * ESC).
               */
              handle_special (vk, ksymp, level);

              if ((*ksymp == 0) ||
                  ((vk == VK_DECIMAL) && (level == GDK_WIN32_LEVEL_NONE)))
                {
                  wchar_t         wcs[10];
                  gint            k;
                  guint           keysym;
                  GdkWin32KeyNode dead_key;

                  wcs[0] = wcs[1] = 0;
                  k = ToUnicodeEx (vk, scancode, key_state,
                                   wcs, G_N_ELEMENTS (wcs),
                                   0, hkls[group]);
#if 0
                  g_print ("ToUnicodeEx(%#02x, %d: %d): %d, %04x %04x\n",
                           vk, scancode, level, k,
                           wcs[0], wcs[1]);
#endif
                  switch (k)
                    {
                    case 1:
                      if ((vk == VK_DECIMAL) && (level == GDK_WIN32_LEVEL_NONE))
                        options->decimal_mark = wcs[0];
                      else
                        *ksymp = gdk_unicode_to_keyval (wcs[0]);
                      break;
                    case -1:
                      keysym = gdk_unicode_to_keyval (wcs[0]);

                      /* It is a dead key, and it has been stored in
                       * the keyboard layout's state by
                       * ToAsciiEx()/ToUnicodeEx(). Yes, this is an
                       * incredibly silly API! Make the keyboard
                       * layout forget it by calling
                       * ToAsciiEx()/ToUnicodeEx() once more, with the
                       * virtual key code and scancode for the
                       * spacebar, without shift or AltGr. Otherwise
                       * the next call to ToAsciiEx() with a different
                       * key would try to combine with the dead key.
                       */
                      reset_after_dead (key_state, hkls[group]);

                      /* Use dead keysyms instead of "undead" ones */
                      handle_dead (keysym, ksymp);

                      dead_key.undead_gdk_keycode = keysym;
                      dead_key.vk = vk;
                      dead_key.level = level;
                      dead_key.gdk_keycode = *ksymp;
                      dead_key.combinations = NULL;
                      g_array_append_val (options->dead_keys, dead_key);
                      break;
                    case 0:
                      /* Seems to be necessary to "reset" the keyboard layout
                       * in this case, too. Otherwise problems on NT4.
                       */
                      reset_after_dead (key_state, hkls[group]);
                      break;
                    default:
#if 0
                      GDK_NOTE (EVENTS,
                                g_print ("ToUnicodeEx returns %d "
                                         "for vk:%02x, sc:%02x%s%s\n",
                                         k, vk, scancode,
                                         (shift&0x1 ? " shift" : ""),
                                         (shift&0x2 ? " altgr" : "")));
#endif
                      break;
                    }
                }

              if (*ksymp == 0)
                *ksymp = GDK_KEY_VoidSymbol;
            }

          key_state[vk] = 0;

          /* Check if keyboard has an AltGr key by checking if
           * the mapping with Control+Alt is different.
           * Don't test CapsLock here, as it does not seem to affect
           * dead keys themselves, only the results of dead key combinations.
           */
          if (!options->has_altgr)
            if ((keygroup[GDK_WIN32_LEVEL_ALTGR] != GDK_KEY_VoidSymbol &&
                 keygroup[GDK_WIN32_LEVEL_NONE] != keygroup[GDK_WIN32_LEVEL_ALTGR]) ||
                (keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR] != GDK_KEY_VoidSymbol &&
                 keygroup[GDK_WIN32_LEVEL_SHIFT] != keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR]))
              options->has_altgr = TRUE;
        }
    }

  scancode = 0x0;

  for (group = 0; group < hkls_len; group++)
    {
      options = &g_array_index (keymap->options, GdkWin32KeyGroupOptions, group);

      for (i = 0; i < options->dead_keys->len; i++)
        {
          wchar_t          wcs[10];
          gint             k;
          GdkWin32KeyNode *dead_key;
          GdkWin32KeyNode  combo;

          dead_key = &g_array_index (options->dead_keys, GdkWin32KeyNode, i);

          for (vk = 0; vk < KEY_STATE_SIZE; vk++)
            {
              for (level = GDK_WIN32_LEVEL_NONE; level < GDK_WIN32_LEVEL_COUNT; level++)
                {
                  /* Prime the ToUnicodeEx() internal state */
                  wcs[0] = wcs[1] = 0;
                  set_level_vks (key_state, dead_key->level);
                  k = ToUnicodeEx (dead_key->vk, scancode, key_state,
                                   wcs, G_N_ELEMENTS (wcs),
                                   0, hkls[group]);
                  switch (k)
                    {
                    case -1:
                      /* Okay */
                      break;
                    default:
                      /* Expected a dead key, got something else */
                      reset_after_dead (key_state, hkls[group]);
                      continue;
                    }

                  /* Check how it combines with vk */
                  wcs[0] = wcs[1] = 0;
                  set_level_vks (key_state, level);
                  k = ToUnicodeEx (vk, scancode, key_state,
                                   wcs, G_N_ELEMENTS (wcs),
                                   0, hkls[group]);

                  if (k == 0)
                    {
                      reset_after_dead (key_state, hkls[group]);
                    }
                  else if (k == -1)
                    {
                      /* Dead key chaining? TODO: support this (deeper tree?) */
                      reset_after_dead (key_state, hkls[group]);
                    }
                  else if (k == 1)
                    {
                      combo.vk = vk;
                      combo.level = level;
                      combo.gdk_keycode = gdk_unicode_to_keyval (wcs[0]);
                      combo.undead_gdk_keycode = combo.gdk_keycode;
                      combo.combinations = NULL;

                      if (dead_key->combinations == NULL)
                        {
                          dead_key->combinations = g_array_new (FALSE, FALSE, sizeof (GdkWin32KeyNode));
                          g_array_set_clear_func (dead_key->combinations, (GDestroyNotify) gdk_win32_key_node_clear);
                        }

#if 0
                      {
                        char *dead_key_undead_u8, *wcs_u8;
                        wchar_t t = gdk_keyval_to_unicode (dead_key->undead_gdk_keycode);
                        dead_key_undead_u8 = g_utf16_to_utf8 (&t, 1, NULL, NULL, NULL);
                        wcs_u8 = g_utf16_to_utf8 (wcs, 1, NULL, NULL, NULL);
                        g_fprintf (stdout, "%d %s%s%s0x%02x (%s) + %s%s%s0x%02x = 0x%04x (%s)\n", group,
                                 (dead_key->level == GDK_WIN32_LEVEL_SHIFT ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_ALTGR ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "SHIFT-" : "      ",
                                 (dead_key->level == GDK_WIN32_LEVEL_CAPSLOCK ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK ||
                                  dead_key->level == GDK_WIN32_LEVEL_CAPSLOCK_ALTGR ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "CAPSLOCK-" : "         ",
                                 (dead_key->level == GDK_WIN32_LEVEL_ALTGR ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_ALTGR ||
                                  dead_key->level == GDK_WIN32_LEVEL_CAPSLOCK_ALTGR ||
                                  dead_key->level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "ALTGR-" : "      ",
                                 dead_key->vk,
                                 dead_key_undead_u8,
                                 (combo.level == GDK_WIN32_LEVEL_SHIFT ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_ALTGR ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "SHIFT-" : "      ",
                                 (combo.level == GDK_WIN32_LEVEL_CAPSLOCK ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK ||
                                  combo.level == GDK_WIN32_LEVEL_CAPSLOCK_ALTGR ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "CAPSLOCK-" : "         ",
                                 (combo.level == GDK_WIN32_LEVEL_ALTGR ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_ALTGR ||
                                  combo.level == GDK_WIN32_LEVEL_CAPSLOCK_ALTGR ||
                                  combo.level == GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR) ? "ALTGR-" : "      ",
                                 vk,
                                 wcs[0],
                                 wcs_u8);
                        g_free (dead_key_undead_u8);
                        g_free (wcs_u8);
                      }
#endif

                      g_array_append_val (dead_key->combinations, combo);
                    }
                }
            }
        }

       g_array_sort (options->dead_keys, (GCompareFunc) sort_key_nodes_by_gdk_keyval);
    }

  GDK_NOTE (EVENTS, print_keysym_tab (keymap));

  check_that_active_layout_is_in_sync (keymap);
  current_serial = _gdk_keymap_serial;
}

static gboolean
find_deadkey_by_keyval (GArray *dead_keys, guint16 keyval, gsize *index)
{
  gsize deadkey_i;
  gsize deadkey_i_max;

  if (dead_keys->len == 0)
    return FALSE;

  deadkey_i = 0;
  deadkey_i_max = dead_keys->len - 1;

  while (deadkey_i != deadkey_i_max)
    {
      GdkWin32KeyNode *dead_key;
      gsize middle;

      if (g_array_index (dead_keys, GdkWin32KeyNode, deadkey_i).gdk_keycode == keyval)
        {
          break;
        }
      else if (g_array_index (dead_keys, GdkWin32KeyNode, deadkey_i_max).gdk_keycode == keyval)
        {
          deadkey_i = deadkey_i_max;
          break;
        }
      else if (deadkey_i + 1 == deadkey_i_max)
        {
          break;
        }

      middle = deadkey_i + (deadkey_i_max - deadkey_i) / 2;
      dead_key = &g_array_index (dead_keys, GdkWin32KeyNode, middle);

      if (dead_key->gdk_keycode < keyval)
        deadkey_i = middle;
      else if (dead_key->gdk_keycode > keyval)
        deadkey_i_max = middle;
      else
        deadkey_i = deadkey_i_max = middle;
    }

  if (g_array_index (dead_keys, GdkWin32KeyNode, deadkey_i).gdk_keycode == keyval)
    {
      *index = deadkey_i;

      return TRUE;
    }

  return FALSE;
}

GdkWin32KeymapMatch
gdk_win32_keymap_check_compose (GdkWin32Keymap *keymap,
                                guint16        *compose_buffer,
                                gsize           compose_buffer_len,
                                guint16        *output,
                                gsize          *output_len)
{
  gint partial_match;
  guint8 active_group;
  gsize deadkey_i, node_i;
  GdkWin32KeyNode *dead_key;
  GdkWin32KeyGroupOptions *options;
  GdkWin32KeymapMatch match;
  gsize output_size;

  g_return_val_if_fail (output != NULL && output_len != NULL, GDK_WIN32_KEYMAP_MATCH_NONE);

  if (compose_buffer_len < 1)
    return GDK_WIN32_KEYMAP_MATCH_NONE;

  output_size = *output_len;

  active_group = _gdk_win32_keymap_get_active_group (keymap);
  options = &g_array_index (keymap->options, GdkWin32KeyGroupOptions, active_group);

  partial_match = -1;
  match = GDK_WIN32_KEYMAP_MATCH_NONE;

  if (find_deadkey_by_keyval (options->dead_keys, compose_buffer[0], &deadkey_i))
    {
      while (deadkey_i > 0 &&
             g_array_index (options->dead_keys, GdkWin32KeyNode, deadkey_i - 1).gdk_keycode == compose_buffer[0])
        deadkey_i--;

      /* Hardcoded 2-tier tree here (dead key + non dead key = character).
       * TODO: support trees with arbitrary depth for dead key chaining.
       */
      dead_key = &g_array_index (options->dead_keys, GdkWin32KeyNode, deadkey_i);

      /* "Partial match" means "matched the whole sequence except the last key"
       * (right now the sequence only has 2 keys, so this turns into "matched
       * at least the first key").
       * "last key" should be identified by having NULL further combinations.
       * As a heuristic, convert the buffer contents into keyvals and use
       * them as-is (normally there should be a separate unichar buffer for
       * each combination, but we do not store these).
       */
      partial_match = deadkey_i;

      if (compose_buffer_len < 2)
        match = GDK_WIN32_KEYMAP_MATCH_INCOMPLETE;

      for (node_i = 0;
           match != GDK_WIN32_KEYMAP_MATCH_INCOMPLETE &&
           node_i < dead_key->combinations->len;
           node_i++)
        {
          GdkWin32KeyNode *node;

          node = &g_array_index (dead_key->combinations, GdkWin32KeyNode, node_i);

          if (keymap->keysym_tab[(node->vk * keymap->layout_handles->len + active_group) * GDK_WIN32_LEVEL_COUNT + node->level] == compose_buffer[1])
            {
              match = GDK_WIN32_KEYMAP_MATCH_EXACT;
              *output_len = 0;

              if (*output_len < output_size && node->gdk_keycode != 0)
                output[(*output_len)++] = node->gdk_keycode;

              break;
            }
        }
    }

  if (match == GDK_WIN32_KEYMAP_MATCH_EXACT ||
      match == GDK_WIN32_KEYMAP_MATCH_INCOMPLETE)
    {
      return match;
    }

  if (partial_match >= 0)
    {
      if (compose_buffer_len == 2)
        {
          dead_key = &g_array_index (options->dead_keys, GdkWin32KeyNode, partial_match);
          *output_len = 0;

          if (output_size >= 1)
            output[(*output_len)++] = dead_key->undead_gdk_keycode;

          if (output_size >= 2)
            {
              gsize second_deadkey_i;

              /* Special case for "deadkey + deadkey = space-version-of-deadkey, space-version-of-deadkey" combinations.
               * Normally the result is a sequence of 2 unichars, but we do not store this.
               * For "deadkey + nondeadkey = space-version-of-deadkey, nondeadkey", we can use compose_buffer
               * contents as-is, but space version of a dead key need to be looked up separately.
               */
              if (find_deadkey_by_keyval (options->dead_keys, compose_buffer[1], &second_deadkey_i))
                output[(*output_len)++] = g_array_index (options->dead_keys, GdkWin32KeyNode, second_deadkey_i).undead_gdk_keycode;
              else
                output[(*output_len)++] = compose_buffer[1];
            }
        }

      return GDK_WIN32_KEYMAP_MATCH_PARTIAL;
    }

  return GDK_WIN32_KEYMAP_MATCH_NONE;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
}

guint8
_gdk_win32_keymap_get_rshift_scancode (GdkWin32Keymap *keymap)
{
  return MapVirtualKey (VK_RSHIFT, MAPVK_VK_TO_VSC);
}

void
_gdk_win32_keymap_set_active_layout (GdkWin32Keymap *keymap,
                                     HKL             hkl)
{
  if (keymap != NULL &&
      keymap->layout_handles->len > 0)
    {
      int group;

      for (group = 0; group < keymap->layout_handles->len; group++)
        if (g_array_index (keymap->layout_handles, HKL, group) == hkl)
          if (keymap->active_layout != group)
            {
              GdkSeat *seat;
              GdkDevice *device;

              keymap->active_layout = group;

              seat = gdk_display_get_default_seat (GDK_KEYMAP (keymap)->display);
              device = gdk_seat_get_keyboard (seat);
              g_object_notify (G_OBJECT (device), "active-layout-index");
            }
    }
}

guint8
_gdk_win32_keymap_get_active_group (GdkWin32Keymap *keymap)
{
  if (keymap != NULL &&
      keymap->layout_handles->len > 0)
    return keymap->active_layout;

  return 0;
}

GdkModifierType
_gdk_win32_keymap_get_mod_mask (GdkWin32Keymap *keymap)
{
  GdkWin32KeymapLayoutInfo *layout_info;
  BYTE                      keystate[256] = {0};
  BYTE                      mod_bits;
    
  update_keymap (keymap);

  layout_info = &g_array_index (keymap->layout_infos, GdkWin32KeymapLayoutInfo,
                                keymap->active_layout);
    
  GetKeyboardState (keystate);
    
  mod_bits = keystate_to_modbits (keymap, layout_info, keystate);

  return mod_bits_to_gdk_mod_mask (mod_bits);
}

static PangoDirection
get_hkl_direction (HKL hkl)
{
  switch (PRIMARYLANGID (LOWORD ((DWORD) (gintptr) hkl)))
    {
    case LANG_HEBREW:
    case LANG_ARABIC:
#ifdef LANG_URDU
    case LANG_URDU:
#endif
    case LANG_FARSI:
      /* Others? */
      return PANGO_DIRECTION_RTL;

    default:
      return PANGO_DIRECTION_LTR;
    }
}

static PangoDirection
gdk_win32_keymap_get_direction (GdkKeymap *gdk_keymap)
{
  GdkWin32Keymap *keymap;
  HKL             active_hkl;
  
  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), PANGO_DIRECTION_LTR);

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);

  update_keymap (keymap);

  if (keymap->layout_handles->len <= 0)
    active_hkl = GetKeyboardLayout (0);
  else
    active_hkl = g_array_index (keymap->layout_handles, HKL,
                                keymap->active_layout);

  return get_hkl_direction (active_hkl);
}

static gboolean
gdk_win32_keymap_have_bidi_layouts (GdkKeymap *gdk_keymap)
{
  GdkWin32Keymap *keymap;
  gboolean        have_rtl = FALSE;
  gboolean        have_ltr = FALSE;
  int             group;

  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), FALSE);

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);

  update_keymap (keymap);

  for (group = 0; group < keymap->layout_handles->len; group++)
    {
      if (get_hkl_direction (g_array_index (keymap->layout_handles, HKL,
                             group)) == PANGO_DIRECTION_RTL)
        have_rtl = TRUE;
      else
        have_ltr = TRUE;
    }

  return have_ltr && have_rtl;
}

static gboolean
gdk_win32_keymap_get_caps_lock_state (GdkKeymap *keymap)
{
  (void) keymap;

  return ((GetKeyState (VK_CAPITAL) & 1) != 0);
}

static gboolean
gdk_win32_keymap_get_num_lock_state (GdkKeymap *keymap)
{
  (void) keymap;

  return ((GetKeyState (VK_NUMLOCK) & 1) != 0);
}

static gboolean
gdk_win32_keymap_get_scroll_lock_state (GdkKeymap *keymap)
{
  (void) keymap;

  return ((GetKeyState (VK_SCROLL) & 1) != 0);
}

static gboolean
gdk_win32_keymap_get_entries_for_keyval (GdkKeymap     *gdk_keymap,
                                         guint          keyval,
                                         GArray        *retval)
{
  GdkWin32Keymap *keymap;
  int             group;
  guint           len = retval->len;

  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), FALSE);
  g_return_val_if_fail (keyval != 0, FALSE);

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);

  update_keymap (keymap);

  for (group = 0; group < keymap->layout_handles->len; group++)
    {
      GdkWin32KeymapLayoutInfo *info = &g_array_index (keymap->layout_infos,
                                                       GdkWin32KeymapLayoutInfo,
                                                       group);
      int entry_index = gdk_keysym_to_key_entry_index (info, keyval);

      while (entry_index >= 0)
        {
          GdkWin32KeymapKeyEntry  *entry        = &g_array_index (info->key_entries,
                                                                  GdkWin32KeymapKeyEntry,
                                                                  entry_index);
          BYTE                     base_modbits = entry->mod_bits;
          BYTE                     extra_modbits;
          GdkKeymapKey             gdk_key      = {0};

          /* Add original key combination */
          gdk_key.keycode = entry->vk;
          gdk_key.level   = modbits_to_level (keymap, info, entry->mod_bits);
          gdk_key.group   = group;

          g_array_append_val (retval, gdk_key);

          /* Add combinations with modifiers that do not affect the translation */
          for (extra_modbits = 0;
               extra_modbits <= info->max_modbit_value;
               ++extra_modbits)
            {
              BYTE  modbits;
              guint sym;

              /* We are only interested in masks which are orthogonal to the
               * original mask. */
              if ((extra_modbits | base_modbits) == base_modbits ||
                  (extra_modbits & base_modbits) != 0)
                continue;

              modbits = base_modbits | extra_modbits;

              /* Check if the additional modifiers change the semantics.
               * If they do not, add them. */
              sym = vk_and_mod_bits_to_gdk_keysym (keymap, info, entry->vk,
                                                   modbits, 0, NULL);
              if (sym == keyval || sym == GDK_KEY_VoidSymbol)
                {
                  gdk_key.keycode = entry->vk;
                  gdk_key.level   = modbits_to_level (keymap, info, modbits);
                  gdk_key.group   = group;
                  g_array_append_val (retval, gdk_key);
                }
            }

          entry_index = entry->next;
        }
   }

  return retval->len > len;
}

static gboolean
gdk_win32_keymap_get_entries_for_keycode (GdkKeymap     *gdk_keymap,
                                          guint          hardware_keycode,
                                          GdkKeymapKey **keys,
                                          guint        **keyvals,
                                          int           *n_entries)
{
  GdkWin32Keymap *keymap;
  GArray         *key_array;
  GArray         *keyval_array;
  int             group;
  BYTE            vk;

  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), FALSE);
  g_return_val_if_fail (n_entries != NULL, FALSE);

  *n_entries = 0;

  if (keys != NULL)
    key_array = g_array_new (FALSE, FALSE, sizeof (GdkKeymapKey));
  else
    key_array = NULL;

  if (keyvals != NULL)
    keyval_array = g_array_new (FALSE, FALSE, sizeof (guint));
  else
    keyval_array = NULL;

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);
  update_keymap (keymap);

  vk = hardware_keycode;

  for (group = 0; group < keymap->layout_handles->len; group++)
    {
      GdkWin32KeymapLayoutInfo *info = &g_array_index (keymap->layout_infos,
                                                       GdkWin32KeymapLayoutInfo,
                                                       group);
      int level;

      for (level = 0; level <= info->max_level; ++level)
        {
          BYTE         modbits          = info->level_to_modbits[level];
          BYTE         consumed_modbits = 0;
          GdkKeymapKey key              = {0};
          guint        keyval;

          keyval = vk_and_mod_bits_to_gdk_keysym (keymap, info, vk, modbits, 0, &consumed_modbits);

          if (keyval == GDK_KEY_VoidSymbol || consumed_modbits != modbits)
            continue;

          key.keycode = vk;
          key.group = group;
          key.level = level;

          if (key_array)
            g_array_append_val (key_array, key);

          if (keyval_array)
            g_array_append_val (keyval_array, keyval);

          ++(*n_entries);
        }
    }
  
  if (keys != NULL)
    *keys = (GdkKeymapKey*) g_array_free (key_array, FALSE);

  if (keyvals != NULL)
    *keyvals = (guint*) g_array_free (keyval_array, FALSE);

  return *n_entries > 0;
}

static guint
gdk_win32_keymap_lookup_key (GdkKeymap          *gdk_keymap,
                             const GdkKeymapKey *key)
{
  GdkWin32Keymap           *keymap;
  GdkWin32KeymapLayoutInfo *info;

  BYTE                      modbits;
  guint                     sym;

  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), 0);
  g_return_val_if_fail (key != NULL, 0);

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);
  update_keymap (keymap);

  info = &g_array_index (keymap->layout_infos, GdkWin32KeymapLayoutInfo, key->group);

  if (key->group < 0 || key->group >= keymap->layout_handles->len)
    return 0;
  if (key->level < 0 || key->level > info->max_level)
    return 0;

  modbits = info->level_to_modbits[key->level];
  sym = vk_and_mod_bits_to_gdk_keysym (keymap, info, key->keycode, modbits, 0, NULL);

  if (sym == GDK_KEY_VoidSymbol)
    return 0;
  else
    return sym;
}

static gboolean
gdk_win32_keymap_translate_keyboard_state (GdkKeymap       *gdk_keymap,
                                           guint            hardware_keycode,
                                           GdkModifierType  state,
                                           int              group,
                                           guint           *keyval,
                                           int             *effective_group,
                                           int             *level,
                                           GdkModifierType *consumed_modifiers)
{
<<<<<<< HEAD
  GdkWin32Keymap           *keymap;
  guint                     tmp_keyval;
  int                       tmp_effective_group;
  int                       tmp_level;
  BYTE                      consumed_mod_bits;
=======
  GdkWin32Keymap *keymap;
  guint tmp_keyval;
  guint *keygroup;
  GdkWin32KeyLevelState shift_level;
  GdkModifierType modifiers = GDK_SHIFT_MASK | GDK_LOCK_MASK | GDK_MOD2_MASK;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

  GdkWin32KeymapLayoutInfo *layout_info;
  guint                     vk;
  BYTE                      mod_bits;
  BYTE                      lock_bits = 0;

  g_return_val_if_fail (GDK_IS_KEYMAP (gdk_keymap), FALSE);

  keymap = GDK_WIN32_KEYMAP (gdk_keymap);
  update_keymap (keymap);

  g_return_val_if_fail (group >= 0 && group < keymap->layout_infos->len, FALSE);

  layout_info = &g_array_index (keymap->layout_infos, GdkWin32KeymapLayoutInfo,
                                group);

  vk = hardware_keycode;
  mod_bits = gdk_mod_mask_to_mod_bits (state);

<<<<<<< HEAD
  if (vk == VK_SHIFT || vk == VK_LSHIFT || vk == VK_RSHIFT)
    mod_bits &= ~KBDSHIFT;
  if (vk == VK_CONTROL || vk == VK_LCONTROL || vk == VK_RCONTROL)
    mod_bits &= ~KBDCTRL;
  if (vk == VK_MENU || vk == VK_LMENU || vk == VK_RMENU)
    mod_bits &= ~KBDALT;
  if (vk == VK_RMENU)
    mod_bits &= ~KBDALTGR;

  /* Translate lock state
   *
   * Right now the only locking modifier is CAPSLOCK. We don't handle KANALOK
   * because GDK doesn't have an equivalent modifier mask to my knowledge (On
   * X11, I believe the same effect is achieved by shifting to a different
   * group. It's just a different concept, that doesn't translate to Windows).
   * But since KANALOK is only used on far-eastern keyboards, which require IME
   * anyway, this is probably fine. The IME input module has actually been the
   * default for all languages (not just far-eastern) for a while now, which
   * means that the keymap is now only used for things like accelerators and
   * keybindings, where you probably don't even want KANALOK to affect the
   * translation.
   */

  if (state & GDK_LOCK_MASK)
    lock_bits |= CAPLOK;

  tmp_keyval = vk_and_mod_bits_to_gdk_keysym (keymap, layout_info, vk, mod_bits,
                                              lock_bits, &consumed_mod_bits);
  tmp_effective_group = group;
  tmp_level = modbits_to_level (keymap, layout_info, consumed_mod_bits);

  /* Determine consumed modifiers */
  
=======
  keygroup = &keymap->keysym_tab[(hardware_keycode * keymap->layout_handles->len + group) * GDK_WIN32_LEVEL_COUNT];

  if ((state & (GDK_SHIFT_MASK | GDK_LOCK_MASK)) == (GDK_SHIFT_MASK | GDK_LOCK_MASK))
    shift_level = GDK_WIN32_LEVEL_SHIFT_CAPSLOCK;
  else if (state & GDK_SHIFT_MASK)
    shift_level = GDK_WIN32_LEVEL_SHIFT;
  else if (state & GDK_LOCK_MASK)
    shift_level = GDK_WIN32_LEVEL_CAPSLOCK;
  else
    shift_level = GDK_WIN32_LEVEL_NONE;

  if (state & GDK_MOD2_MASK)
    {
      if (shift_level == GDK_WIN32_LEVEL_NONE)
        shift_level = GDK_WIN32_LEVEL_ALTGR;
      else if (shift_level == GDK_WIN32_LEVEL_SHIFT)
        shift_level = GDK_WIN32_LEVEL_SHIFT_ALTGR;
      else if (shift_level == GDK_WIN32_LEVEL_CAPSLOCK)
        shift_level = GDK_WIN32_LEVEL_CAPSLOCK_ALTGR;
      else
        shift_level = GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR;
    }

  /* Drop altgr, capslock and shift if there are no keysymbols on
   * the key for those.
   */
  if (keygroup[shift_level] == GDK_KEY_VoidSymbol)
    {
      switch (shift_level)
        {
         case GDK_WIN32_LEVEL_NONE:
         case GDK_WIN32_LEVEL_ALTGR:
         case GDK_WIN32_LEVEL_SHIFT:
         case GDK_WIN32_LEVEL_CAPSLOCK:
           if (keygroup[GDK_WIN32_LEVEL_NONE] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_NONE;
           break;
         case GDK_WIN32_LEVEL_SHIFT_CAPSLOCK:
           if (keygroup[GDK_WIN32_LEVEL_CAPSLOCK] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_CAPSLOCK;
           else if (keygroup[GDK_WIN32_LEVEL_SHIFT] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_SHIFT;
           else if (keygroup[GDK_WIN32_LEVEL_NONE] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_NONE;
           break;
         case GDK_WIN32_LEVEL_CAPSLOCK_ALTGR:
           if (keygroup[GDK_WIN32_LEVEL_ALTGR] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_ALTGR;
           else if (keygroup[GDK_WIN32_LEVEL_CAPSLOCK] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_CAPSLOCK;
           else if (keygroup[GDK_WIN32_LEVEL_NONE] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_NONE;
           break;
         case GDK_WIN32_LEVEL_SHIFT_ALTGR:
           if (keygroup[GDK_WIN32_LEVEL_ALTGR] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_ALTGR;
           else if (keygroup[GDK_WIN32_LEVEL_SHIFT] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_SHIFT;
           else if (keygroup[GDK_WIN32_LEVEL_NONE] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_NONE;
           break;
         case GDK_WIN32_LEVEL_SHIFT_CAPSLOCK_ALTGR:
           if (keygroup[GDK_WIN32_LEVEL_CAPSLOCK_ALTGR] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_CAPSLOCK_ALTGR;
           else if (keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_SHIFT_ALTGR;
           else if (keygroup[GDK_WIN32_LEVEL_ALTGR] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_ALTGR;
           else if (keygroup[GDK_WIN32_LEVEL_SHIFT_CAPSLOCK] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_SHIFT_CAPSLOCK;
           else if (keygroup[GDK_WIN32_LEVEL_CAPSLOCK] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_CAPSLOCK;
           else if (keygroup[GDK_WIN32_LEVEL_SHIFT] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_SHIFT;
           else if (keygroup[GDK_WIN32_LEVEL_NONE] != GDK_KEY_VoidSymbol)
             shift_level = GDK_WIN32_LEVEL_NONE;
           break;
         case GDK_WIN32_LEVEL_COUNT:
           g_assert_not_reached ();
        }
    }

  /* See whether the shift level actually mattered
   * to know what to put in consumed_modifiers
   */
  if ((keygroup[GDK_WIN32_LEVEL_SHIFT] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_NONE] == keygroup[GDK_WIN32_LEVEL_SHIFT]) &&
      (keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_ALTGR] == keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR]) &&
      (keygroup[GDK_WIN32_LEVEL_SHIFT_CAPSLOCK] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_CAPSLOCK] == keygroup[GDK_WIN32_LEVEL_SHIFT_CAPSLOCK]))
      modifiers &= ~GDK_SHIFT_MASK;

  if ((keygroup[GDK_WIN32_LEVEL_CAPSLOCK] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_NONE] == keygroup[GDK_WIN32_LEVEL_CAPSLOCK]) &&
      (keygroup[GDK_WIN32_LEVEL_CAPSLOCK_ALTGR] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_ALTGR] == keygroup[GDK_WIN32_LEVEL_CAPSLOCK_ALTGR]) &&
      (keygroup[GDK_WIN32_LEVEL_SHIFT_CAPSLOCK] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_SHIFT] == keygroup[GDK_WIN32_LEVEL_SHIFT_CAPSLOCK]))
      modifiers &= ~GDK_LOCK_MASK;

  if ((keygroup[GDK_WIN32_LEVEL_ALTGR] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_NONE] == keygroup[GDK_WIN32_LEVEL_ALTGR]) &&
      (keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_SHIFT] == keygroup[GDK_WIN32_LEVEL_SHIFT_ALTGR]) &&
      (keygroup[GDK_WIN32_LEVEL_CAPSLOCK_ALTGR] == GDK_KEY_VoidSymbol ||
       keygroup[GDK_WIN32_LEVEL_CAPSLOCK] == keygroup[GDK_WIN32_LEVEL_CAPSLOCK_ALTGR]))
      modifiers &= ~GDK_MOD2_MASK;

  tmp_keyval = keygroup[shift_level];

>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
  if (keyval)
    *keyval = tmp_keyval;
  if (effective_group)
    *effective_group = tmp_effective_group;
  if (level)
    *level = tmp_level;
  if (consumed_modifiers)
    *consumed_modifiers = mod_bits_to_gdk_mod_mask (consumed_mod_bits);

  /* Just a diagnostic message to inform the user why their keypresses aren't working.
   * Shouldn't happen under normal circumstances. */
  if (tmp_keyval == GDK_KEY_VoidSymbol && layout_info->tables == NULL)
    g_warning("Failed to translate keypress (keycode: %u) for group %d (%s) because "
              "we could not load the layout.",
              hardware_keycode, group, layout_info->name);

  return tmp_keyval != GDK_KEY_VoidSymbol;
}

static char **
gdk_win32_keymap_get_layout_names (GdkKeymap *gdk_keymap)
{
  GdkWin32Keymap *keymap = GDK_WIN32_KEYMAP (gdk_keymap);

  update_keymap (keymap);

  if (keymap->layout_infos)
    {
      GStrvBuilder *names_builder;
      char **layout_names;
      int i;

      names_builder = g_strv_builder_new ();

      for (i = 0; i < keymap->layout_infos->len; ++i)
        {
          LCID lcid;
          char *endptr;
          GdkWin32KeymapLayoutInfo *info;

          info = &g_array_index (keymap->layout_infos, GdkWin32KeymapLayoutInfo, i);
          lcid = strtoul (info->name, &endptr, 16);

          if (info->name != endptr)
            {
              wchar_t *locale_name_w;
              int locale_size = GetLocaleInfoW (lcid, LOCALE_SLOCALIZEDDISPLAYNAME, NULL, 0);

              locale_name_w = g_new0 (wchar_t, locale_size);

              if (GetLocaleInfoW (lcid, LOCALE_SLOCALIZEDDISPLAYNAME, locale_name_w, locale_size))
                {
                  gchar *locale_name = g_utf16_to_utf8 (locale_name_w, -1, NULL, NULL, NULL);
                  g_strv_builder_add (names_builder, locale_name);
                }

              g_free (locale_name_w);
            }
        }

      layout_names = g_strv_builder_end (names_builder);
      g_strv_builder_unref (names_builder);

      return layout_names;
    }

  return NULL;
}

static int
gdk_win32_keymap_get_active_layout_index (GdkKeymap *gdk_keymap)
{
  GdkWin32Keymap *keymap = GDK_WIN32_KEYMAP (gdk_keymap);

  update_keymap (keymap);

  if (keymap->layout_infos)
    return (int) keymap->active_layout;

  return -1;
}

static void
gdk_win32_keymap_class_init (GdkWin32KeymapClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GdkKeymapClass *keymap_class = GDK_KEYMAP_CLASS (klass);

  object_class->constructed = gdk_win32_keymap_constructed;
  object_class->finalize = gdk_win32_keymap_finalize;

  keymap_class->get_direction = gdk_win32_keymap_get_direction;
  keymap_class->have_bidi_layouts = gdk_win32_keymap_have_bidi_layouts;
  keymap_class->get_caps_lock_state = gdk_win32_keymap_get_caps_lock_state;
  keymap_class->get_num_lock_state = gdk_win32_keymap_get_num_lock_state;
  keymap_class->get_scroll_lock_state = gdk_win32_keymap_get_scroll_lock_state;
  keymap_class->get_entries_for_keyval = gdk_win32_keymap_get_entries_for_keyval;
  keymap_class->get_entries_for_keycode = gdk_win32_keymap_get_entries_for_keycode;
  keymap_class->lookup_key = gdk_win32_keymap_lookup_key;
  keymap_class->translate_keyboard_state = gdk_win32_keymap_translate_keyboard_state;
  keymap_class->get_active_layout_index = gdk_win32_keymap_get_active_layout_index;
  keymap_class->get_layout_names = gdk_win32_keymap_get_layout_names;
}
