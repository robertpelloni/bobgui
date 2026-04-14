/* GDK - The GIMP Drawing Kit
 *
 * gdkglcontext-x11.c: X11 specific OpenGL wrappers
 *
 * Copyright © 2014  Emmanuele Bassi
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "gdkglcontext-x11.h"
#include "gdkdisplay-x11.h"
#include "gdkprivate-x11.h"
#include "gdkscreen-x11.h"

#include "gdkx11display.h"
#include "gdkx11glcontext.h"
#include "gdkx11screen.h"
#include "gdkx11property.h"
#include <X11/Xatom.h>

#include <glib/gi18n-lib.h>

#include <cairo-xlib.h>

#include <epoxy/glx.h>

G_GNUC_BEGIN_IGNORE_DEPRECATIONS

G_DEFINE_ABSTRACT_TYPE (GdkX11GLContext, gdk_x11_gl_context, GDK_TYPE_GL_CONTEXT)

static void
gdk_x11_gl_context_empty_frame (GdkDrawContext *draw_context)
{
}

static void
gdk_x11_gl_context_class_init (GdkX11GLContextClass *klass)
{
  GdkDrawContextClass *draw_context_class = GDK_DRAW_CONTEXT_CLASS (klass);

  draw_context_class->empty_frame = gdk_x11_gl_context_empty_frame;
}

static void
gdk_x11_gl_context_init (GdkX11GLContext *self)
{
}

<<<<<<< HEAD
=======
gboolean
gdk_x11_screen_init_gl (GdkScreen *screen)
{
  GdkDisplay *display = gdk_screen_get_display (screen);
  GdkX11Display *display_x11 = GDK_X11_DISPLAY (display);
  Display *dpy;
  int error_base, event_base;
  int screen_num;

  if (display_x11->have_glx)
    return TRUE;

  if (_gdk_gl_flags & GDK_GL_DISABLE)
    return FALSE;

  dpy = gdk_x11_display_get_xdisplay (display);

  if (!epoxy_has_glx (dpy))
    return FALSE;

  if (!glXQueryExtension (dpy, &error_base, &event_base))
    return FALSE;

  screen_num = GDK_X11_SCREEN (screen)->screen_num;

  display_x11->have_glx = TRUE;

  display_x11->glx_version = epoxy_glx_version (dpy, screen_num);
  display_x11->glx_error_base = error_base;
  display_x11->glx_event_base = event_base;

  display_x11->has_glx_create_context =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_ARB_create_context_profile");
  display_x11->has_glx_create_es2_context =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_EXT_create_context_es2_profile");
  display_x11->has_glx_swap_interval =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_SGI_swap_control");
  display_x11->has_glx_texture_from_pixmap =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_EXT_texture_from_pixmap");
  display_x11->has_glx_video_sync =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_SGI_video_sync");
  display_x11->has_glx_buffer_age =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_EXT_buffer_age");
  display_x11->has_glx_sync_control =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_OML_sync_control");
  display_x11->has_glx_multisample =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_ARB_multisample");
  display_x11->has_glx_visual_rating =
    epoxy_has_glx_extension (dpy, screen_num, "GLX_EXT_visual_rating");

  GDK_NOTE (OPENGL,
            g_message ("GLX version %d.%d found\n"
                       " - Vendor: %s\n"
                       " - Checked extensions:\n"
                       "\t* GLX_ARB_create_context_profile: %s\n"
                       "\t* GLX_EXT_create_context_es2_profile: %s\n"
                       "\t* GLX_SGI_swap_control: %s\n"
                       "\t* GLX_EXT_texture_from_pixmap: %s\n"
                       "\t* GLX_SGI_video_sync: %s\n"
                       "\t* GLX_EXT_buffer_age: %s\n"
                       "\t* GLX_OML_sync_control: %s",
                     display_x11->glx_version / 10,
                     display_x11->glx_version % 10,
                     glXGetClientString (dpy, GLX_VENDOR),
                     display_x11->has_glx_create_context ? "yes" : "no",
                     display_x11->has_glx_create_es2_context ? "yes" : "no",
                     display_x11->has_glx_swap_interval ? "yes" : "no",
                     display_x11->has_glx_texture_from_pixmap ? "yes" : "no",
                     display_x11->has_glx_video_sync ? "yes" : "no",
                     display_x11->has_glx_buffer_age ? "yes" : "no",
                     display_x11->has_glx_sync_control ? "yes" : "no"));

  return TRUE;
}

#define MAX_GLX_ATTRS   30

static gboolean
find_fbconfig_for_visual (GdkDisplay   *display,
			  GdkVisual    *visual,
                          GLXFBConfig  *fb_config_out,
                          GError      **error)
{
  static int attrs[MAX_GLX_ATTRS];
  Display *dpy = gdk_x11_display_get_xdisplay (display);
  GLXFBConfig *configs;
  int n_configs, i;
  gboolean use_rgba;
  gboolean retval = FALSE;
  VisualID xvisual_id = XVisualIDFromVisual(gdk_x11_visual_get_xvisual (visual));

  i = 0;
  attrs[i++] = GLX_DRAWABLE_TYPE;
  attrs[i++] = GLX_WINDOW_BIT;

  attrs[i++] = GLX_RENDER_TYPE;
  attrs[i++] = GLX_RGBA_BIT;

  attrs[i++] = GLX_DOUBLEBUFFER;
  attrs[i++] = GL_TRUE;

  attrs[i++] = GLX_RED_SIZE;
  attrs[i++] = 1;
  attrs[i++] = GLX_GREEN_SIZE;
  attrs[i++] = 1;
  attrs[i++] = GLX_BLUE_SIZE;
  attrs[i++] = 1;

  use_rgba = (visual == gdk_screen_get_rgba_visual (gdk_display_get_default_screen (display)));
  if (use_rgba)
    {
      attrs[i++] = GLX_ALPHA_SIZE;
      attrs[i++] = 1;
    }
  else
    {
      attrs[i++] = GLX_ALPHA_SIZE;
      attrs[i++] = GLX_DONT_CARE;
    }

  attrs[i++] = None;

  g_assert (i < MAX_GLX_ATTRS);

  configs = glXChooseFBConfig (dpy, DefaultScreen (dpy), attrs, &n_configs);
  if (configs == NULL || n_configs == 0)
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_UNSUPPORTED_FORMAT,
                           _("No available configurations for the given pixel format"));
      return FALSE;
    }

  for (i = 0; i < n_configs; i++)
    {
      XVisualInfo *visinfo;

      visinfo = glXGetVisualFromFBConfig (dpy, configs[i]);
      if (visinfo == NULL)
        continue;

      if (visinfo->visualid != xvisual_id)
        {
          XFree (visinfo);
          continue;
        }

      if (fb_config_out != NULL)
        *fb_config_out = configs[i];

      XFree (visinfo);
      retval = TRUE;
      goto out;
    }

  g_set_error (error, GDK_GL_ERROR,
               GDK_GL_ERROR_UNSUPPORTED_FORMAT,
               _("No available configurations for the given RGBA pixel format"));

out:
  XFree (configs);

  return retval;
}

struct glvisualinfo {
  int supports_gl;
  int double_buffer;
  int stereo;
  int alpha_size;
  int depth_size;
  int stencil_size;
  int num_multisample;
  int visual_caveat;
};

static gboolean
visual_compatible (const GdkVisual *a, const GdkVisual *b)
{
  return a->type == b->type &&
    a->depth == b->depth &&
    a->red_mask == b->red_mask &&
    a->green_mask == b->green_mask &&
    a->blue_mask == b->blue_mask &&
    a->colormap_size == b->colormap_size &&
    a->bits_per_rgb == b->bits_per_rgb;
}

static gboolean
visual_is_rgba (const GdkVisual *visual)
{
  return
    visual->depth == 32 &&
    visual->red_mask   == 0xff0000 &&
    visual->green_mask == 0x00ff00 &&
    visual->blue_mask  == 0x0000ff;
}

/* This picks a compatible (as in has the same X visual details) visual
   that has "better" characteristics on the GL side */
static GdkVisual *
pick_better_visual_for_gl (GdkX11Screen *x11_screen,
                           struct glvisualinfo *gl_info,
                           GdkVisual *compatible)
{
  GdkVisual *visual;
  int i;
  gboolean want_alpha = visual_is_rgba (compatible);

  /* First look for "perfect match", i.e:
   * supports gl
   * double buffer
   * alpha iff visual is an rgba visual
   * no unnecessary stuff
   */
  for (i = 0; i < x11_screen->nvisuals; i++)
    {
      visual = x11_screen->visuals[i];
      if (visual_compatible (visual, compatible) &&
          gl_info[i].supports_gl &&
          gl_info[i].double_buffer &&
          !gl_info[i].stereo &&
          (want_alpha ? (gl_info[i].alpha_size > 0) : (gl_info[i].alpha_size == 0)) &&
          (gl_info[i].depth_size == 0) &&
          (gl_info[i].stencil_size == 0) &&
          (gl_info[i].num_multisample == 0) &&
          (gl_info[i].visual_caveat == GLX_NONE_EXT))
        return visual;
    }

  if (!want_alpha)
    {
      /* Next, allow alpha even if we don't want it: */
      for (i = 0; i < x11_screen->nvisuals; i++)
        {
          visual = x11_screen->visuals[i];
          if (visual_compatible (visual, compatible) &&
              gl_info[i].supports_gl &&
              gl_info[i].double_buffer &&
              !gl_info[i].stereo &&
              (gl_info[i].depth_size == 0) &&
              (gl_info[i].stencil_size == 0) &&
              (gl_info[i].num_multisample == 0) &&
              (gl_info[i].visual_caveat == GLX_NONE_EXT))
            return visual;
        }
    }

  /* Next, allow depth and stencil buffers: */
  for (i = 0; i < x11_screen->nvisuals; i++)
    {
      visual = x11_screen->visuals[i];
      if (visual_compatible (visual, compatible) &&
          gl_info[i].supports_gl &&
          gl_info[i].double_buffer &&
          !gl_info[i].stereo &&
          (gl_info[i].num_multisample == 0) &&
          (gl_info[i].visual_caveat == GLX_NONE_EXT))
        return visual;
    }

  /* Next, allow multisample: */
  for (i = 0; i < x11_screen->nvisuals; i++)
    {
      visual = x11_screen->visuals[i];
      if (visual_compatible (visual, compatible) &&
          gl_info[i].supports_gl &&
          gl_info[i].double_buffer &&
          !gl_info[i].stereo &&
          (gl_info[i].visual_caveat == GLX_NONE_EXT))
        return visual;
    }

  return compatible;
}

static gboolean
get_cached_gl_visuals (GdkDisplay *display, int *system, int *rgba)
{
  gboolean found;
  Atom type_return;
  gint format_return;
  gulong nitems_return;
  gulong bytes_after_return;
  guchar *data = NULL;
  Display *dpy;

  dpy = gdk_x11_display_get_xdisplay (display);

  found = FALSE;

  gdk_x11_display_error_trap_push (display);
  if (XGetWindowProperty (dpy, DefaultRootWindow (dpy),
                          gdk_x11_get_xatom_by_name_for_display (display, "GDK_VISUALS"),
                          0, 2, False, XA_INTEGER, &type_return,
                          &format_return, &nitems_return,
                          &bytes_after_return, &data) == Success)
    {
      if (type_return == XA_INTEGER &&
          format_return == 32 &&
          nitems_return == 2 &&
          data != NULL)
        {
          long *visuals = (long *) data;

          *system = (int)visuals[0];
          *rgba = (int)visuals[1];
          found = TRUE;
        }
    }
  gdk_x11_display_error_trap_pop_ignored (display);

  if (data)
    XFree (data);

  return found;
}

static void
save_cached_gl_visuals (GdkDisplay *display, int system, int rgba)
{
  long visualdata[2];
  Display *dpy;

  dpy = gdk_x11_display_get_xdisplay (display);

  visualdata[0] = system;
  visualdata[1] = rgba;

  gdk_x11_display_error_trap_push (display);
  XChangeProperty (dpy, DefaultRootWindow (dpy),
                   gdk_x11_get_xatom_by_name_for_display (display, "GDK_VISUALS"),
                   XA_INTEGER, 32, PropModeReplace,
                   (unsigned char *)visualdata, 2);
  gdk_x11_display_error_trap_pop_ignored (display);
}

void
_gdk_x11_screen_update_visuals_for_gl (GdkScreen *screen)
{
  GdkX11Screen *x11_screen;
  GdkDisplay *display;
  GdkX11Display *display_x11;
  Display *dpy;
  struct glvisualinfo *gl_info;
  int i;
  int system_visual_id, rgba_visual_id;

  x11_screen = GDK_X11_SCREEN (screen);
  display = x11_screen->display;
  display_x11 = GDK_X11_DISPLAY (display);
  dpy = gdk_x11_display_get_xdisplay (display);

  /* We save the default visuals as a property on the root window to avoid
     having to initialize GL each time, as it may not be used later. */
  if (get_cached_gl_visuals (display, &system_visual_id, &rgba_visual_id))
    {
      for (i = 0; i < x11_screen->nvisuals; i++)
        {
          GdkVisual *visual = x11_screen->visuals[i];
          int visual_id = gdk_x11_visual_get_xvisual (visual)->visualid;

          if (visual_id == system_visual_id)
            x11_screen->system_visual = visual;
          if (visual_id == rgba_visual_id)
            x11_screen->rgba_visual = visual;
        }

      return;
    }

  if (!gdk_x11_screen_init_gl (screen))
    return;

  gl_info = g_new0 (struct glvisualinfo, x11_screen->nvisuals);

  for (i = 0; i < x11_screen->nvisuals; i++)
    {
      XVisualInfo *visual_list;
      XVisualInfo visual_template;
      int nxvisuals;

      visual_template.screen = x11_screen->screen_num;
      visual_template.visualid = gdk_x11_visual_get_xvisual (x11_screen->visuals[i])->visualid;
      visual_list = XGetVisualInfo (x11_screen->xdisplay, VisualIDMask| VisualScreenMask, &visual_template, &nxvisuals);

      if (visual_list == NULL)
        continue;

      glXGetConfig (dpy, &visual_list[0], GLX_USE_GL, &gl_info[i].supports_gl);
      glXGetConfig (dpy, &visual_list[0], GLX_DOUBLEBUFFER, &gl_info[i].double_buffer);
      glXGetConfig (dpy, &visual_list[0], GLX_STEREO, &gl_info[i].stereo);
      glXGetConfig (dpy, &visual_list[0], GLX_ALPHA_SIZE, &gl_info[i].alpha_size);
      glXGetConfig (dpy, &visual_list[0], GLX_DEPTH_SIZE, &gl_info[i].depth_size);
      glXGetConfig (dpy, &visual_list[0], GLX_STENCIL_SIZE, &gl_info[i].stencil_size);

      if (display_x11->has_glx_multisample)
        glXGetConfig(dpy, &visual_list[0], GLX_SAMPLE_BUFFERS_ARB, &gl_info[i].num_multisample);

      if (display_x11->has_glx_visual_rating)
        glXGetConfig(dpy, &visual_list[0], GLX_VISUAL_CAVEAT_EXT, &gl_info[i].visual_caveat);
      else
        gl_info[i].visual_caveat = GLX_NONE_EXT;

      XFree (visual_list);
    }

  x11_screen->system_visual = pick_better_visual_for_gl (x11_screen, gl_info, x11_screen->system_visual);
  if (x11_screen->rgba_visual)
    x11_screen->rgba_visual = pick_better_visual_for_gl (x11_screen, gl_info, x11_screen->rgba_visual);

  g_free (gl_info);

  save_cached_gl_visuals (display,
                          gdk_x11_visual_get_xvisual (x11_screen->system_visual)->visualid,
                          x11_screen->rgba_visual ? gdk_x11_visual_get_xvisual (x11_screen->rgba_visual)->visualid : 0);
}

GdkGLContext *
gdk_x11_window_create_gl_context (GdkWindow    *window,
                                  gboolean      attached,
                                  GdkGLContext *share,
                                  GError      **error)
{
  GdkDisplay *display;
  GdkX11GLContext *context;
  GdkVisual *visual;
  GLXFBConfig config;

  display = gdk_window_get_display (window);

  if (!gdk_x11_screen_init_gl (gdk_window_get_screen (window)))
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_NOT_AVAILABLE,
                           _("No GL implementation is available"));
      return NULL;
    }

  visual = gdk_window_get_visual (window);
  if (!find_fbconfig_for_visual (display, visual, &config, error))
    return NULL;

  context = g_object_new (GDK_TYPE_X11_GL_CONTEXT,
                          "display", display,
                          "window", window,
                          "shared-context", share,
                          NULL);

  context->glx_config = config;
  context->is_attached = attached;

  return GDK_GL_CONTEXT (context);
}

gboolean
gdk_x11_display_make_gl_context_current (GdkDisplay   *display,
                                         GdkGLContext *context)
{
  GdkX11GLContext *context_x11;
  Display *dpy = gdk_x11_display_get_xdisplay (display);
  GdkWindow *window;
  GdkScreen *screen;
  gboolean do_frame_sync = FALSE;

  if (context == NULL)
    {
      glXMakeContextCurrent (dpy, None, None, NULL);
      return TRUE;
    }

  context_x11 = GDK_X11_GL_CONTEXT (context);
  if (context_x11->glx_context == NULL)
    {
      g_critical ("No GLX context associated to the GdkGLContext; you must "
                  "call gdk_gl_context_realize() first.");
      return FALSE;
    }

  GDK_NOTE (OPENGL,
            g_message ("Making GLX context current to drawable %lu",
                       (unsigned long) context_x11->drawable));

  if (!glXMakeContextCurrent (dpy, context_x11->drawable, context_x11->drawable,
                              context_x11->glx_context))
    {
      GDK_NOTE (OPENGL,
                g_message ("Making GLX context current failed"));
      return FALSE;
    }

  if (context_x11->is_attached && GDK_X11_DISPLAY (display)->has_glx_swap_interval)
    {
      window = gdk_gl_context_get_window (context);

      /* If the WM is compositing there is no particular need to delay
       * the swap when drawing on the offscreen, rendering to the screen
       * happens later anyway, and its up to the compositor to sync that
       * to the vblank. */
      screen = gdk_window_get_screen (window);
      do_frame_sync = ! gdk_screen_is_composited (screen);

      if (do_frame_sync != context_x11->do_frame_sync)
        {
          context_x11->do_frame_sync = do_frame_sync;

          if (do_frame_sync)
            glXSwapIntervalSGI (1);
          else
            glXSwapIntervalSGI (0);
        }
    }

  return TRUE;
}

/**
 * gdk_x11_display_get_glx_version:
 * @display: a #GdkDisplay
 * @major: (out): return location for the GLX major version
 * @minor: (out): return location for the GLX minor version
 *
 * Retrieves the version of the GLX implementation.
 *
 * Returns: %TRUE if GLX is available
 *
 * Since: 3.16
 */
gboolean
gdk_x11_display_get_glx_version (GdkDisplay *display,
                                 gint       *major,
                                 gint       *minor)
{
  g_return_val_if_fail (GDK_IS_DISPLAY (display), FALSE);

  if (!GDK_IS_X11_DISPLAY (display))
    return FALSE;

  if (!gdk_x11_screen_init_gl (gdk_display_get_default_screen (display)))
    return FALSE;

  if (major != NULL)
    *major = GDK_X11_DISPLAY (display)->glx_version / 10;
  if (minor != NULL)
    *minor = GDK_X11_DISPLAY (display)->glx_version % 10;

  return TRUE;
}
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
