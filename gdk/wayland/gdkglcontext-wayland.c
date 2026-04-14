/* GDK - The GIMP Drawing Kit
 *
 * gdkglcontext-wayland.c: Wayland specific OpenGL wrappers
 *
 * Copyright © 2014  Emmanuele Bassi
 * Copyright © 2014  Alexander Larsson
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

#include "gdkglcontext-wayland.h"

#include "gdkdisplay-wayland.h"
#include "gdksurface-wayland-private.h"

#include "gdkwaylanddisplay.h"
#include "gdkwaylandglcontext.h"
#include "gdkwaylandsurface.h"

#include "gdkprivate.h"
#include "gdksurfaceprivate.h"
#include "gdkprofilerprivate.h"

#include <glib/gi18n-lib.h>

#include <epoxy/egl.h>

/**
 * GdkWaylandGLContext:
 *
 * The Wayland implementation of `GdkGLContext`.
 */

struct _GdkWaylandGLContext
{
  GdkGLContext parent_instance;

  struct wl_egl_window *egl_window;
};

struct _GdkWaylandGLContextClass
{
  GdkGLContextClass parent_class;
};

G_DEFINE_TYPE (GdkWaylandGLContext, gdk_wayland_gl_context, GDK_TYPE_GL_CONTEXT)

static void
gdk_wayland_gl_context_end_frame (GdkDrawContext *draw_context,
                                  gpointer        context_data,
                                  cairo_region_t *painted)
{
  GdkSurface *surface = gdk_draw_context_get_surface (draw_context);
  GdkWaylandSurface *impl = GDK_WAYLAND_SURFACE (surface);
  int dx = impl->pending_buffer_offset_x;
  int dy = impl->pending_buffer_offset_y;

  impl->pending_buffer_offset_x = 0;
  impl->pending_buffer_offset_y = 0;

  gdk_wayland_surface_sync (surface);
  gdk_wayland_surface_request_frame (surface);

  if (wl_surface_get_version (impl->display_server.wl_surface) >=
      WL_SURFACE_OFFSET_SINCE_VERSION)
    wl_surface_offset (impl->display_server.wl_surface, dx, dy);

  /* We should do this when setting up the EGLSurface, but we don't make_current then */
  eglSwapInterval (gdk_display_get_egl_display (gdk_draw_context_get_display (draw_context)), 0);

  GDK_DRAW_CONTEXT_CLASS (gdk_wayland_gl_context_parent_class)->end_frame (draw_context, context_data, painted);

  gdk_wayland_surface_notify_committed (surface);
}

static void
gdk_wayland_gl_context_empty_frame (GdkDrawContext *draw_context)
{
  GdkSurface *surface = gdk_draw_context_get_surface (draw_context);

  gdk_wayland_surface_handle_empty_frame (surface);
}

static gboolean
gdk_wayland_gl_context_surface_attach (GdkDrawContext  *context,
                                       GError         **error)
{
  GdkWaylandGLContext *self = GDK_WAYLAND_GL_CONTEXT (context);
  GdkGLContext *gl_context = GDK_GL_CONTEXT (context);
  GdkSurface *surface;
  guint width, height;

  g_assert (self->egl_window == NULL);

  surface = gdk_draw_context_get_surface (context);

  gdk_draw_context_get_buffer_size (context, &width, &height);
  self->egl_window = wl_egl_window_create (gdk_wayland_surface_get_wl_surface (surface),
                                           width, height);
  gdk_gl_context_set_egl_native_window (gl_context, self->egl_window);

  return TRUE;
}

static void
gdk_wayland_gl_context_surface_detach (GdkDrawContext *context)
{
  GdkWaylandGLContext *self = GDK_WAYLAND_GL_CONTEXT (context);

  GDK_DRAW_CONTEXT_CLASS (gdk_wayland_gl_context_parent_class)->surface_detach (context);

  g_clear_pointer (&self->egl_window, wl_egl_window_destroy);
}

static void
gdk_wayland_gl_context_surface_resized (GdkDrawContext *context)
{
  GdkWaylandGLContext *self = GDK_WAYLAND_GL_CONTEXT (context);

  if (self->egl_window)
    {
      guint w, h;
      gdk_draw_context_get_buffer_size (context, &w, &h);
      GDK_DISPLAY_DEBUG (gdk_draw_context_get_display (context), OPENGL,
                         "Resizing EGL window to %d %d",
                         w, h);
      wl_egl_window_resize (self->egl_window, w, h, 0, 0);
    }
}

static void
gdk_wayland_gl_context_class_init (GdkWaylandGLContextClass *klass)
{
  GdkDrawContextClass *draw_context_class = GDK_DRAW_CONTEXT_CLASS (klass);
  GdkGLContextClass *context_class = GDK_GL_CONTEXT_CLASS (klass);

  draw_context_class->end_frame = gdk_wayland_gl_context_end_frame;
  draw_context_class->empty_frame = gdk_wayland_gl_context_empty_frame;
  draw_context_class->surface_attach = gdk_wayland_gl_context_surface_attach;
  draw_context_class->surface_detach = gdk_wayland_gl_context_surface_detach;
  draw_context_class->surface_resized = gdk_wayland_gl_context_surface_resized;

  context_class->backend_type = GDK_GL_EGL;
}

static void
gdk_wayland_gl_context_init (GdkWaylandGLContext *self)
{
}

<<<<<<< HEAD
/**
 * gdk_wayland_display_get_egl_display:
 * @display: (type GdkWaylandDisplay): a Wayland display
 *
 * Retrieves the EGL display connection object for the given GDK display.
 *
 * Returns: (nullable): the EGL display
 *
 * Since: 4.4
 */
gpointer
gdk_wayland_display_get_egl_display (GdkDisplay *display)
{
  g_return_val_if_fail (GDK_IS_WAYLAND_DISPLAY (display), NULL);

  return gdk_display_get_egl_display (display);
=======
static EGLDisplay
gdk_wayland_get_display (GdkWaylandDisplay *display_wayland)
{
  EGLDisplay dpy = NULL;

  if (epoxy_has_egl_extension (NULL, "EGL_KHR_platform_base"))
    {
      PFNEGLGETPLATFORMDISPLAYPROC getPlatformDisplay =
	(void *) eglGetProcAddress ("eglGetPlatformDisplay");

      if (getPlatformDisplay)
	dpy = getPlatformDisplay (EGL_PLATFORM_WAYLAND_EXT,
				  display_wayland->wl_display,
				  NULL);
      if (dpy)
	return dpy;
    }

  if (epoxy_has_egl_extension (NULL, "EGL_EXT_platform_base"))
    {
      PFNEGLGETPLATFORMDISPLAYEXTPROC getPlatformDisplay =
	(void *) eglGetProcAddress ("eglGetPlatformDisplayEXT");

      if (getPlatformDisplay)
	dpy = getPlatformDisplay (EGL_PLATFORM_WAYLAND_EXT,
				  display_wayland->wl_display,
				  NULL);
      if (dpy)
	return dpy;
    }

  return eglGetDisplay ((EGLNativeDisplayType) display_wayland->wl_display);
}

gboolean
gdk_wayland_display_init_gl (GdkDisplay *display)
{
  GdkWaylandDisplay *display_wayland = GDK_WAYLAND_DISPLAY (display);
  EGLint major, minor;
  EGLDisplay dpy;

  if (display_wayland->have_egl)
    return TRUE;

  dpy = gdk_wayland_get_display (display_wayland);

  if (dpy == NULL)
    return FALSE;

  if (!eglInitialize (dpy, &major, &minor))
    return FALSE;

  if (!eglBindAPI (EGL_OPENGL_API))
    return FALSE;

  display_wayland->egl_display = dpy;
  display_wayland->egl_major_version = major;
  display_wayland->egl_minor_version = minor;

  display_wayland->have_egl = TRUE;

  display_wayland->have_egl_khr_create_context =
    epoxy_has_egl_extension (dpy, "EGL_KHR_create_context");

  display_wayland->have_egl_buffer_age =
    epoxy_has_egl_extension (dpy, "EGL_EXT_buffer_age");

  display_wayland->have_egl_swap_buffers_with_damage =
    epoxy_has_egl_extension (dpy, "EGL_EXT_swap_buffers_with_damage");

  display_wayland->have_egl_surfaceless_context =
    epoxy_has_egl_extension (dpy, "EGL_KHR_surfaceless_context");

  GDK_NOTE (OPENGL,
            g_message ("EGL API version %d.%d found\n"
                       " - Vendor: %s\n"
                       " - Version: %s\n"
                       " - Client APIs: %s\n"
                       " - Extensions:\n"
                       "\t%s",
                       display_wayland->egl_major_version,
                       display_wayland->egl_minor_version,
                       eglQueryString (dpy, EGL_VENDOR),
                       eglQueryString (dpy, EGL_VERSION),
                       eglQueryString (dpy, EGL_CLIENT_APIS),
                       eglQueryString (dpy, EGL_EXTENSIONS)));

  return TRUE;
}

#define MAX_EGL_ATTRS   30

static gboolean
find_eglconfig_for_window (GdkWindow  *window,
                           EGLConfig  *egl_config_out,
                           EGLint     *min_swap_interval_out,
                           GError    **error)
{
  GdkDisplay *display = gdk_window_get_display (window);
  GdkWaylandDisplay *display_wayland = GDK_WAYLAND_DISPLAY (display);
  GdkVisual *visual = gdk_window_get_visual (window);
  EGLint attrs[MAX_EGL_ATTRS];
  EGLint count;
  EGLConfig *configs, chosen_config;
  gboolean use_rgba;

  int i = 0;

  attrs[i++] = EGL_SURFACE_TYPE;
  attrs[i++] = EGL_WINDOW_BIT;

  attrs[i++] = EGL_COLOR_BUFFER_TYPE;
  attrs[i++] = EGL_RGB_BUFFER;

  attrs[i++] = EGL_RED_SIZE;
  attrs[i++] = 1;
  attrs[i++] = EGL_GREEN_SIZE;
  attrs[i++] = 1;
  attrs[i++] = EGL_BLUE_SIZE;
  attrs[i++] = 1;

  use_rgba = (visual == gdk_screen_get_rgba_visual (gdk_display_get_default_screen (display)));

  if (use_rgba)
    {
      attrs[i++] = EGL_ALPHA_SIZE;
      attrs[i++] = 1;
    }
  else
    {
      attrs[i++] = EGL_ALPHA_SIZE;
      attrs[i++] = 0;
    }

  attrs[i++] = EGL_NONE;
  g_assert (i < MAX_EGL_ATTRS);

  if (!eglChooseConfig (display_wayland->egl_display, attrs, NULL, 0, &count) || count < 1)
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_UNSUPPORTED_FORMAT,
                           _("No available configurations for the given pixel format"));
      return FALSE;
    }

  configs = g_new (EGLConfig, count);

  if (!eglChooseConfig (display_wayland->egl_display, attrs, configs, count, &count) || count < 1)
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_UNSUPPORTED_FORMAT,
                           _("No available configurations for the given pixel format"));
      return FALSE;
    }

  /* Pick first valid configuration i guess? */
  chosen_config = configs[0];

  if (!eglGetConfigAttrib (display_wayland->egl_display, chosen_config,
                           EGL_MIN_SWAP_INTERVAL, min_swap_interval_out))
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_NOT_AVAILABLE,
                           "Could not retrieve the minimum swap interval");
      g_free (configs);
      return FALSE;
    }

  if (egl_config_out != NULL)
    *egl_config_out = chosen_config;

  g_free (configs);

  return TRUE;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
}

GdkGLContext *
gdk_wayland_display_init_gl (GdkDisplay  *display,
                             GError     **error)
{
  GdkWaylandDisplay *self = GDK_WAYLAND_DISPLAY (display);

<<<<<<< HEAD
  if (!gdk_display_init_egl (display,
                             EGL_PLATFORM_WAYLAND_EXT,
                             self->wl_display,
                             TRUE,
                             error))
=======
  if (!gdk_wayland_display_init_gl (display))
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_NOT_AVAILABLE,
                           _("No GL implementation is available"));
      return NULL;
    }

  if (!display_wayland->have_egl_khr_create_context)
    {
      g_set_error_literal (error, GDK_GL_ERROR,
                           GDK_GL_ERROR_UNSUPPORTED_PROFILE,
                           _("Core GL is not available on EGL implementation"));
      return NULL;
    }

  if (!find_eglconfig_for_window (window, &config,
                                  &display_wayland->egl_min_swap_interval,
                                  error))
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
    return NULL;

  return g_object_new (GDK_TYPE_WAYLAND_GL_CONTEXT,
                       "display", display,
                       NULL);
}

<<<<<<< HEAD
=======
static void
gdk_x11_gl_context_dispose (GObject *gobject)
{
  GdkWaylandGLContext *context_wayland = GDK_WAYLAND_GL_CONTEXT (gobject);

  if (context_wayland->egl_context != NULL)
    {
      GdkGLContext *context = GDK_GL_CONTEXT (gobject);
      GdkWindow *window = gdk_gl_context_get_window (context);
      GdkDisplay *display = gdk_window_get_display (window);
      GdkWaylandDisplay *display_wayland = GDK_WAYLAND_DISPLAY (display);

      if (eglGetCurrentContext () == context_wayland->egl_context)
        eglMakeCurrent(display_wayland->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                       EGL_NO_CONTEXT);

      GDK_NOTE (OPENGL, g_message ("Destroying EGL context"));

      eglDestroyContext (display_wayland->egl_display,
                         context_wayland->egl_context);
      context_wayland->egl_context = NULL;
    }

  G_OBJECT_CLASS (gdk_wayland_gl_context_parent_class)->dispose (gobject);
}

gboolean
gdk_wayland_display_make_gl_context_current (GdkDisplay   *display,
                                             GdkGLContext *context)
{
  GdkWaylandDisplay *display_wayland = GDK_WAYLAND_DISPLAY (display);
  GdkWaylandGLContext *context_wayland;
  GdkWindow *window;
  EGLSurface egl_surface;

  if (context == NULL)
    {
      eglMakeCurrent(display_wayland->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                     EGL_NO_CONTEXT);
      return TRUE;
    }

  context_wayland = GDK_WAYLAND_GL_CONTEXT (context);
  window = gdk_gl_context_get_window (context);

  if (context_wayland->is_attached)
    egl_surface = gdk_wayland_window_get_egl_surface (window->impl_window, context_wayland->egl_config);
  else
    {
      if (display_wayland->have_egl_surfaceless_context)
	egl_surface = EGL_NO_SURFACE;
      else
	egl_surface = gdk_wayland_window_get_dummy_egl_surface (window->impl_window,
								context_wayland->egl_config);
    }

  if (!eglMakeCurrent (display_wayland->egl_display, egl_surface,
                       egl_surface, context_wayland->egl_context))
    {
      g_warning ("eglMakeCurrent failed");
      return FALSE;
    }

  if (display_wayland->egl_min_swap_interval == 0)
    eglSwapInterval (display_wayland->egl_display, 0);
  else
    g_debug ("Can't disable GL swap interval");

  return TRUE;
}
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
