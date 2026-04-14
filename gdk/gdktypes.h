/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
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

#pragma once

#if !defined (__GDK_H_INSIDE__) && !defined (BOBGUI_COMPILATION)
#error "Only <gdk/gdk.h> can be included directly."
#endif

/* GDK uses "glib". (And so does BOBGUI).
 */
#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <cairo.h>
#include <pango/pango.h>

/* The system specific file gdkconfig.h contains such configuration
 * settings that are needed not only when compiling GDK (or BOBGUI)
 * itself, but also occasionally when compiling programs that use GDK
 * (or BOBGUI). One such setting is what windowing API backend is in use.
 */
#include <gdk/gdkconfig.h>
#include <gdk/gdkenums.h>
#include <gdk/version/gdkversionmacros.h>

G_BEGIN_DECLS

/**
 * GDK_CURRENT_TIME:
 *
 * Represents the current time, and can be used anywhere a time is expected.
 */
#define GDK_CURRENT_TIME     0L

#ifdef __GI_SCANNER__
/* The introspection scanner is currently unable to lookup how
 * cairo_rectangle_int_t is actually defined. This prevents
 * introspection data for the GdkRectangle type to include fields
 * descriptions. To workaround this issue, we define it with the same
 * content as cairo_rectangle_int_t, but only under the introspection
 * define.
 */
struct _GdkRectangle
{
    int x, y;
    int width, height;
};
typedef struct _GdkRectangle          GdkRectangle;
#else
typedef cairo_rectangle_int_t         GdkRectangle;
#endif

/* Forward declarations of commonly used types */
typedef struct _GdkRGBA               GdkRGBA;
typedef struct _GdkCicpParams         GdkCicpParams;
typedef struct _GdkColorState         GdkColorState;
typedef struct _GdkContentFormats     GdkContentFormats;
typedef struct _GdkContentProvider    GdkContentProvider;
typedef struct _GdkCursor             GdkCursor;
typedef struct _GdkTexture            GdkTexture;
typedef struct _GdkTextureDownloader  GdkTextureDownloader;
typedef struct _GdkDevice             GdkDevice;
typedef struct _GdkDrag               GdkDrag;
typedef struct _GdkDrop               GdkDrop;

typedef struct _GdkClipboard          GdkClipboard;
typedef struct _GdkDisplayManager     GdkDisplayManager;
typedef struct _GdkDisplay            GdkDisplay;
typedef struct _GdkSurface             GdkSurface;
typedef struct _GdkAppLaunchContext   GdkAppLaunchContext;
typedef struct _GdkSeat               GdkSeat;
typedef struct _GdkSnapshot           GdkSnapshot;

typedef struct _GdkDrawContext        GdkDrawContext;
typedef struct _GdkCairoContext       GdkCairoContext;
typedef struct _GdkGLContext          GdkGLContext;
typedef struct _GdkVulkanContext      GdkVulkanContext;

typedef struct _GdkDmabufFormats      GdkDmabufFormats;
typedef struct _GdkDmabufTexture      GdkDmabufTexture;

/*<private>
 * GDK_DECLARE_INTERNAL_TYPE:
 * @ModuleObjName: The name of the new type, in camel case (like BobguiWidget)
 * @module_obj_name: The name of the new type in lowercase, with words
 *  separated by '_' (like 'bobgui_widget')
 * @MODULE: The name of the module, in all caps (like 'BOBGUI')
 * @OBJ_NAME: The bare name of the type, in all caps (like 'WIDGET')
 * @ParentName: the name of the parent type, in camel case (like BobguiWidget)
 *
 * A convenience macro for emitting the usual declarations in the
 * header file for a type which is intended to be subclassed only
 * by internal consumers.
 *
 * This macro differs from %G_DECLARE_DERIVABLE_TYPE and %G_DECLARE_FINAL_TYPE
 * by declaring a type that is only derivable internally. Internal users can
 * derive this type, assuming they have access to the instance and class
 * structures; external users will not be able to subclass this type.
 */
#define GDK_DECLARE_INTERNAL_TYPE(ModuleObjName, module_obj_name, MODULE, OBJ_NAME, ParentName) \
  GType module_obj_name##_get_type (void);                                                               \
  G_GNUC_BEGIN_IGNORE_DEPRECATIONS                                                                       \
  typedef struct _##ModuleObjName ModuleObjName;                                                         \
  typedef struct _##ModuleObjName##Class ModuleObjName##Class;                                           \
                                                                                                         \
  _GLIB_DEFINE_AUTOPTR_CHAINUP (ModuleObjName, ParentName)                                               \
  G_DEFINE_AUTOPTR_CLEANUP_FUNC (ModuleObjName##Class, g_type_class_unref)                               \
                                                                                                         \
  G_GNUC_UNUSED static inline ModuleObjName * MODULE##_##OBJ_NAME (gpointer ptr) {                       \
    return G_TYPE_CHECK_INSTANCE_CAST (ptr, module_obj_name##_get_type (), ModuleObjName); }             \
  G_GNUC_UNUSED static inline ModuleObjName##Class * MODULE##_##OBJ_NAME##_CLASS (gpointer ptr) {        \
    return G_TYPE_CHECK_CLASS_CAST (ptr, module_obj_name##_get_type (), ModuleObjName##Class); }         \
  G_GNUC_UNUSED static inline gboolean MODULE##_IS_##OBJ_NAME (gpointer ptr) {                           \
    return G_TYPE_CHECK_INSTANCE_TYPE (ptr, module_obj_name##_get_type ()); }                            \
  G_GNUC_UNUSED static inline gboolean MODULE##_IS_##OBJ_NAME##_CLASS (gpointer ptr) {                   \
    return G_TYPE_CHECK_CLASS_TYPE (ptr, module_obj_name##_get_type ()); }                               \
  G_GNUC_UNUSED static inline ModuleObjName##Class * MODULE##_##OBJ_NAME##_GET_CLASS (gpointer ptr) {    \
    return G_TYPE_INSTANCE_GET_CLASS (ptr, module_obj_name##_get_type (), ModuleObjName##Class); }       \
  G_GNUC_END_IGNORE_DEPRECATIONS

typedef struct _GdkKeymapKey GdkKeymapKey;

/**
 * GdkKeymapKey:
 * @keycode: the hardware keycode. This is an identifying number for a
 *   physical key.
 * @group: indicates movement in a horizontal direction. Usually groups are used
 *   for two different languages. In group 0, a key might have two English
 *   characters, and in group 1 it might have two Hebrew characters. The Hebrew
 *   characters will be printed on the key next to the English characters.
 * @level: indicates which symbol on the key will be used, in a vertical direction.
 *   So on a standard US keyboard, the key with the number “1” on it also has the
 *   exclamation point ("!") character on it. The level indicates whether to use
 *   the “1” or the “!” symbol. The letter keys are considered to have a lowercase
 *   letter at level 0, and an uppercase letter at level 1, though only the
 *   uppercase letter is printed.
 *
 * Represents a hardware key that can be mapped to a keyval.
 */
struct _GdkKeymapKey
{
<<<<<<< HEAD
  guint keycode;
  int   group;
  int   level;
=======
  GDK_LSB_FIRST,
  GDK_MSB_FIRST
} GdkByteOrder;

/* Types of modifiers.
 */
/**
 * GdkModifierType:
 * @GDK_SHIFT_MASK: the Shift key.
 * @GDK_LOCK_MASK: a Lock key (depending on the modifier mapping of the
 *  X server this may either be CapsLock or ShiftLock).
 * @GDK_CONTROL_MASK: the Control key.
 * @GDK_MOD1_MASK: the fourth modifier key (it depends on the modifier
 *  mapping of the X server which key is interpreted as this modifier, but
 *  normally it is the Alt key).
 * @GDK_MOD2_MASK: the fifth modifier key (it depends on the modifier
 *  mapping of the X server which key is interpreted as this modifier).
 * @GDK_MOD3_MASK: the sixth modifier key (it depends on the modifier
 *  mapping of the X server which key is interpreted as this modifier).
 * @GDK_MOD4_MASK: the seventh modifier key (it depends on the modifier
 *  mapping of the X server which key is interpreted as this modifier).
 * @GDK_MOD5_MASK: the eighth modifier key (it depends on the modifier
 *  mapping of the X server which key is interpreted as this modifier).
 * @GDK_BUTTON1_MASK: the first mouse button.
 * @GDK_BUTTON2_MASK: the second mouse button.
 * @GDK_BUTTON3_MASK: the third mouse button.
 * @GDK_BUTTON4_MASK: the fourth mouse button.
 * @GDK_BUTTON5_MASK: the fifth mouse button.
 * @GDK_MODIFIER_RESERVED_13_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_14_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_15_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_16_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_17_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_18_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_19_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_20_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_21_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_22_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_23_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_24_MASK: A reserved bit flag; do not use in your own code
 * @GDK_MODIFIER_RESERVED_25_MASK: A reserved bit flag; do not use in your own code
 * @GDK_SUPER_MASK: the Super modifier. Since 2.10
 * @GDK_HYPER_MASK: the Hyper modifier. Since 2.10
 * @GDK_META_MASK: the Meta modifier. Since 2.10
 * @GDK_MODIFIER_RESERVED_29_MASK: A reserved bit flag; do not use in your own code
 * @GDK_RELEASE_MASK: not used in GDK itself. GTK+ uses it to differentiate
 *  between (keyval, modifiers) pairs from key press and release events.
 * @GDK_MODIFIER_MASK: a mask covering all modifier types.
 *
 * A set of bit-flags to indicate the state of modifier keys and mouse buttons
 * in various event types. Typical modifier keys are Shift, Control, Meta,
 * Super, Hyper, Alt, Compose, Apple, CapsLock or ShiftLock.
 *
 * Like the X Window System, GDK supports 8 modifier keys and 5 mouse buttons.
 *
 * Since 2.10, GDK recognizes which of the Meta, Super or Hyper keys are mapped
 * to Mod2 - Mod5, and indicates this by setting %GDK_SUPER_MASK,
 * %GDK_HYPER_MASK or %GDK_META_MASK in the state field of key events.
 *
 * Note that GDK may add internal values to events which include
 * reserved values such as %GDK_MODIFIER_RESERVED_13_MASK.  Your code
 * should preserve and ignore them.  You can use %GDK_MODIFIER_MASK to
 * remove all reserved values.
 *
 * Also note that the GDK X backend interprets button press events for button
 * 4-7 as scroll events, so %GDK_BUTTON4_MASK and %GDK_BUTTON5_MASK will never
 * be set.
 */
typedef enum
{
  GDK_SHIFT_MASK    = 1 << 0,
  GDK_LOCK_MASK     = 1 << 1,
  GDK_CONTROL_MASK  = 1 << 2,
  GDK_MOD1_MASK     = 1 << 3,
  GDK_MOD2_MASK     = 1 << 4,
  GDK_MOD3_MASK     = 1 << 5,
  GDK_MOD4_MASK     = 1 << 6,
  GDK_MOD5_MASK     = 1 << 7,
  GDK_BUTTON1_MASK  = 1 << 8,
  GDK_BUTTON2_MASK  = 1 << 9,
  GDK_BUTTON3_MASK  = 1 << 10,
  GDK_BUTTON4_MASK  = 1 << 11,
  GDK_BUTTON5_MASK  = 1 << 12,

  GDK_MODIFIER_RESERVED_13_MASK  = 1 << 13,
  GDK_MODIFIER_RESERVED_14_MASK  = 1 << 14,
  GDK_MODIFIER_RESERVED_15_MASK  = 1 << 15,
  GDK_MODIFIER_RESERVED_16_MASK  = 1 << 16,
  GDK_MODIFIER_RESERVED_17_MASK  = 1 << 17,
  GDK_MODIFIER_RESERVED_18_MASK  = 1 << 18,
  GDK_MODIFIER_RESERVED_19_MASK  = 1 << 19,
  GDK_MODIFIER_RESERVED_20_MASK  = 1 << 20,
  GDK_MODIFIER_RESERVED_21_MASK  = 1 << 21,
  GDK_MODIFIER_RESERVED_22_MASK  = 1 << 22,
  GDK_MODIFIER_RESERVED_23_MASK  = 1 << 23,
  GDK_MODIFIER_RESERVED_24_MASK  = 1 << 24,
  GDK_MODIFIER_RESERVED_25_MASK  = 1 << 25,

  /* The next few modifiers are used by XKB, so we skip to the end.
   * Bits 15 - 25 are currently unused. Bit 29 is used internally.
   */
  
  GDK_SUPER_MASK    = 1 << 26,
  GDK_HYPER_MASK    = 1 << 27,
  GDK_META_MASK     = 1 << 28,
  
  GDK_MODIFIER_RESERVED_29_MASK  = 1 << 29,

  GDK_RELEASE_MASK  = 1 << 30,

  /* Combination of GDK_SHIFT_MASK..GDK_BUTTON5_MASK + GDK_SUPER_MASK
     + GDK_HYPER_MASK + GDK_META_MASK + GDK_RELEASE_MASK */
  GDK_MODIFIER_MASK = 0x5c001fff
} GdkModifierType;

/**
 * GdkModifierIntent:
 * @GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR: the primary modifier used to invoke
 *  menu accelerators.
 * @GDK_MODIFIER_INTENT_CONTEXT_MENU: the modifier used to invoke context menus.
 *  Note that mouse button 3 always triggers context menus. When this modifier
 *  is not 0, it additionally triggers context menus when used with mouse button 1.
 * @GDK_MODIFIER_INTENT_EXTEND_SELECTION: the modifier used to extend selections
 *  using `modifier`-click or `modifier`-cursor-key
 * @GDK_MODIFIER_INTENT_MODIFY_SELECTION: the modifier used to modify selections,
 *  which in most cases means toggling the clicked item into or out of the selection.
 * @GDK_MODIFIER_INTENT_NO_TEXT_INPUT: when any of these modifiers is pressed, the
 *  key event cannot produce a symbol directly. This is meant to be used for
 *  input methods, and for use cases like typeahead search.
 * @GDK_MODIFIER_INTENT_SHIFT_GROUP: the modifier that switches between keyboard
 *  groups (AltGr on X11/Windows and Option/Alt on OS X).
 * @GDK_MODIFIER_INTENT_DEFAULT_MOD_MASK: The set of modifier masks accepted
 * as modifiers in accelerators. Needed because Command is mapped to MOD2 on
 * OSX, which is widely used, but on X11 MOD2 is NumLock and using that for a
 * mod key is problematic at best.
 * Ref: https://bugzilla.gnome.org/show_bug.cgi?id=736125.
 *
 * This enum is used with gdk_keymap_get_modifier_mask()
 * in order to determine what modifiers the
 * currently used windowing system backend uses for particular
 * purposes. For example, on X11/Windows, the Control key is used for
 * invoking menu shortcuts (accelerators), whereas on Apple computers
 * it’s the Command key (which correspond to %GDK_CONTROL_MASK and
 * %GDK_MOD2_MASK, respectively).
 *
 * Since: 3.4
 **/
typedef enum
{
  GDK_MODIFIER_INTENT_PRIMARY_ACCELERATOR,
  GDK_MODIFIER_INTENT_CONTEXT_MENU,
  GDK_MODIFIER_INTENT_EXTEND_SELECTION,
  GDK_MODIFIER_INTENT_MODIFY_SELECTION,
  GDK_MODIFIER_INTENT_NO_TEXT_INPUT,
  GDK_MODIFIER_INTENT_SHIFT_GROUP,
  GDK_MODIFIER_INTENT_DEFAULT_MOD_MASK,
} GdkModifierIntent;

typedef enum
{
  GDK_OK          = 0,
  GDK_ERROR       = -1,
  GDK_ERROR_PARAM = -2,
  GDK_ERROR_FILE  = -3,
  GDK_ERROR_MEM   = -4
} GdkStatus;

/**
 * GdkGrabStatus:
 * @GDK_GRAB_SUCCESS: the resource was successfully grabbed.
 * @GDK_GRAB_ALREADY_GRABBED: the resource is actively grabbed by another client.
 * @GDK_GRAB_INVALID_TIME: the resource was grabbed more recently than the
 *  specified time.
 * @GDK_GRAB_NOT_VIEWABLE: the grab window or the @confine_to window are not
 *  viewable.
 * @GDK_GRAB_FROZEN: the resource is frozen by an active grab of another client.
 * @GDK_GRAB_FAILED: the grab failed for some other reason. Since 3.16
 *
 * Returned by gdk_device_grab(), gdk_pointer_grab() and gdk_keyboard_grab() to
 * indicate success or the reason for the failure of the grab attempt.
 */
typedef enum
{
  GDK_GRAB_SUCCESS         = 0,
  GDK_GRAB_ALREADY_GRABBED = 1,
  GDK_GRAB_INVALID_TIME    = 2,
  GDK_GRAB_NOT_VIEWABLE    = 3,
  GDK_GRAB_FROZEN          = 4,
  GDK_GRAB_FAILED          = 5
} GdkGrabStatus;

/**
 * GdkGrabOwnership:
 * @GDK_OWNERSHIP_NONE: All other devices’ events are allowed.
 * @GDK_OWNERSHIP_WINDOW: Other devices’ events are blocked for the grab window.
 * @GDK_OWNERSHIP_APPLICATION: Other devices’ events are blocked for the whole application.
 *
 * Defines how device grabs interact with other devices.
 */
typedef enum
{
  GDK_OWNERSHIP_NONE,
  GDK_OWNERSHIP_WINDOW,
  GDK_OWNERSHIP_APPLICATION
} GdkGrabOwnership;

/**
 * GdkEventMask:
 * @GDK_EXPOSURE_MASK: receive expose events
 * @GDK_POINTER_MOTION_MASK: receive all pointer motion events
 * @GDK_POINTER_MOTION_HINT_MASK: deprecated. see the explanation above
 * @GDK_BUTTON_MOTION_MASK: receive pointer motion events while any button is pressed
 * @GDK_BUTTON1_MOTION_MASK: receive pointer motion events while 1 button is pressed
 * @GDK_BUTTON2_MOTION_MASK: receive pointer motion events while 2 button is pressed
 * @GDK_BUTTON3_MOTION_MASK: receive pointer motion events while 3 button is pressed
 * @GDK_BUTTON_PRESS_MASK: receive button press events
 * @GDK_BUTTON_RELEASE_MASK: receive button release events
 * @GDK_KEY_PRESS_MASK: receive key press events
 * @GDK_KEY_RELEASE_MASK: receive key release events
 * @GDK_ENTER_NOTIFY_MASK: receive window enter events
 * @GDK_LEAVE_NOTIFY_MASK: receive window leave events
 * @GDK_FOCUS_CHANGE_MASK: receive focus change events
 * @GDK_STRUCTURE_MASK: receive events about window configuration change
 * @GDK_PROPERTY_CHANGE_MASK: receive property change events
 * @GDK_VISIBILITY_NOTIFY_MASK: receive visibility change events
 * @GDK_PROXIMITY_IN_MASK: receive proximity in events
 * @GDK_PROXIMITY_OUT_MASK: receive proximity out events
 * @GDK_SUBSTRUCTURE_MASK: receive events about window configuration changes of
 *   child windows
 * @GDK_SCROLL_MASK: receive scroll events
 * @GDK_TOUCH_MASK: receive touch events. Since 3.4
 * @GDK_SMOOTH_SCROLL_MASK: receive smooth scrolling events. Since 3.4
   @GDK_TOUCHPAD_GESTURE_MASK: receive touchpad gesture events. Since 3.18
 * @GDK_TABLET_PAD_MASK: receive tablet pad events. Since 3.22
 * @GDK_ALL_EVENTS_MASK: the combination of all the above event masks.
 *
 * A set of bit-flags to indicate which events a window is to receive.
 * Most of these masks map onto one or more of the #GdkEventType event types
 * above.
 *
 * See the [input handling overview][chap-input-handling] for details of
 * [event masks][event-masks] and [event propagation][event-propagation].
 *
 * %GDK_POINTER_MOTION_HINT_MASK is deprecated. It is a special mask
 * to reduce the number of %GDK_MOTION_NOTIFY events received. When using
 * %GDK_POINTER_MOTION_HINT_MASK, fewer %GDK_MOTION_NOTIFY events will
 * be sent, some of which are marked as a hint (the is_hint member is
 * %TRUE). To receive more motion events after a motion hint event,
 * the application needs to asks for more, by calling
 * gdk_event_request_motions().
 * 
 * Since GTK 3.8, motion events are already compressed by default, independent
 * of this mechanism. This compression can be disabled with
 * gdk_window_set_event_compression(). See the documentation of that function
 * for details.
 *
 * If %GDK_TOUCH_MASK is enabled, the window will receive touch events
 * from touch-enabled devices. Those will come as sequences of #GdkEventTouch
 * with type %GDK_TOUCH_UPDATE, enclosed by two events with
 * type %GDK_TOUCH_BEGIN and %GDK_TOUCH_END (or %GDK_TOUCH_CANCEL).
 * gdk_event_get_event_sequence() returns the event sequence for these
 * events, so different sequences may be distinguished.
 */
typedef enum
{
  GDK_EXPOSURE_MASK             = 1 << 1,
  GDK_POINTER_MOTION_MASK       = 1 << 2,
  GDK_POINTER_MOTION_HINT_MASK  = 1 << 3,
  GDK_BUTTON_MOTION_MASK        = 1 << 4,
  GDK_BUTTON1_MOTION_MASK       = 1 << 5,
  GDK_BUTTON2_MOTION_MASK       = 1 << 6,
  GDK_BUTTON3_MOTION_MASK       = 1 << 7,
  GDK_BUTTON_PRESS_MASK         = 1 << 8,
  GDK_BUTTON_RELEASE_MASK       = 1 << 9,
  GDK_KEY_PRESS_MASK            = 1 << 10,
  GDK_KEY_RELEASE_MASK          = 1 << 11,
  GDK_ENTER_NOTIFY_MASK         = 1 << 12,
  GDK_LEAVE_NOTIFY_MASK         = 1 << 13,
  GDK_FOCUS_CHANGE_MASK         = 1 << 14,
  GDK_STRUCTURE_MASK            = 1 << 15,
  GDK_PROPERTY_CHANGE_MASK      = 1 << 16,
  GDK_VISIBILITY_NOTIFY_MASK    = 1 << 17,
  GDK_PROXIMITY_IN_MASK         = 1 << 18,
  GDK_PROXIMITY_OUT_MASK        = 1 << 19,
  GDK_SUBSTRUCTURE_MASK         = 1 << 20,
  GDK_SCROLL_MASK               = 1 << 21,
  GDK_TOUCH_MASK                = 1 << 22,
  GDK_SMOOTH_SCROLL_MASK        = 1 << 23,
  GDK_TOUCHPAD_GESTURE_MASK     = 1 << 24,
  GDK_TABLET_PAD_MASK           = 1 << 25,
  GDK_ALL_EVENTS_MASK           = 0x3FFFFFE
} GdkEventMask;

/**
 * GdkPoint:
 * @x: the x coordinate of the point.
 * @y: the y coordinate of the point.
 *
 * Defines the x and y coordinates of a point.
 */
struct _GdkPoint
{
  gint x;
  gint y;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
};

G_END_DECLS

