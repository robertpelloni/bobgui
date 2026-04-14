/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2010 Red Hat, Inc.
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

<<<<<<< HEAD
#pragma once

#if !defined (__GDKWIN32_H_INSIDE__) && !defined (BOBGUI_COMPILATION)
=======
#ifndef __GDK_WIN32_DND_PRIVATE_H__
#define __GDK_WIN32_DND_PRIVATE_H__

#if !defined (__GDKWIN32_H_INSIDE__) && !defined (GDK_COMPILATION)
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
#error "Only <gdk/gdkwin32.h> can be included directly."
#endif

#include <gdk/gdk.h>

<<<<<<< HEAD
#include "gdk/gdkdragprivate.h"

G_BEGIN_DECLS

typedef struct _GdkWin32DragUtilityData GdkWin32DragUtilityData;

/* This structure is deliberately designed to be
 * copiable with memcpy(), i.e. no pointers inside.
 */
struct _GdkWin32DragUtilityData
{
  int              last_x;         /* Coordinates from last event, in GDK space */
  int              last_y;
  DWORD            last_key_state; /* Key state from last event */
  GdkWin32DndState state;
};

struct _GdkWin32Drag
{
  GdkDrag drag;

  /* The drag protocol being used */
  GdkDragProtocol  protocol;

  /* The surface used for grabs.
   * Usually the same as GdkDrag->source_surface
   */
  GdkSurface      *grab_surface;

  /* The HWND currently under cursor.
   * Will be INVALID_HANDLE_VALUE (not NULL!) if it is not known
   */
  HWND             dest_hwnd;

  /* The surface that we move along with the cursor to indicate
   * what exactly is being dragged.
   */
  GdkSurface      *drag_surface;
  GdkCursor       *cursor;
  GdkSeat         *grab_seat;

  /* Used to keep track of current drag action, and
   * emit an "action-changed" signal whenever it changes.
   * In the end the actual action is decided on the basis of
   * the last information we receive from the drop site, this
   * field is not used for that purpose.
   */
  GdkDragAction    current_action;

  GdkWin32DragUtilityData util_data;

  guint scale;             /* Temporarily caches the HiDPI scale */
  int   hot_x;             /* Hotspot offset from the top-left of the drag-window, scaled (can be added to GDK space coordinates) */
  int   hot_y;
  int   start_x;           /* Coordinates of the drag start, in GDK space */
  int   start_y;

  guint drag_status : 4;   /* Current status of drag */
  guint drop_failed : 1;   /* Whether the drop was unsuccessful */
  guint handle_events : 1; /* Whether handle_event() should do anything */

  /* keep track of thread data for the DnD op, kept in the GdkDisplay that we create, a GdkWin32DndThread structure */
  void *dnd_thread_items;
};

struct _GdkWin32DragClass
{
  GdkDragClass parent_class;
};


gpointer _gdk_win32_dnd_thread_main           (gpointer    data);

GdkDrag *gdk_win32_find_drag_for_dest_surface (GdkSurface *surface);


G_END_DECLS

=======
G_BEGIN_DECLS

struct _GdkWin32DragContext
{
  GdkDragContext context;
  GdkWindow *ipc_window;
  GdkWindow *drag_window;
  GdkCursor *cursor;
  GdkSeat *grab_seat;
  GdkDragAction actions;
  GdkDragAction current_action;

  guint drag_status : 4;             /* Current status of drag */
  guint drop_failed : 1;             /* Whether the drop was unsuccessful */
  guint has_image_format : 1;
  guint has_text_uri_list : 1;
  guint has_shell_id_list : 1;
  guint has_unicodetext : 1;
  guint has_cf_png : 1;
  guint has_cf_dib : 1;
  guint has_gif : 1;
  guint has_jfif : 1;

  guint scale;              /* Temporarily caches the HiDPI scale */
  gint hot_x;             /* Hotspot offset from the top-left of the drag-window, scaled (can be added to GDK space coordinates) */
  gint hot_y;
  gint last_x;            /* Coordinates from last event, in GDK space */
  gint last_y;
  gint start_x;           /* Coordinates of the drag start, in GDK space */
  gint start_y;
  DWORD last_key_state;     /* Key state from last event */

  /* Just like context->targets, but an array, and with format IDs
   * stored inside.
   */
  GArray *droptarget_format_target_map;
};

struct _GdkWin32DragContextClass
{
  GdkDragContextClass parent_class;
};

G_END_DECLS

#endif /* __GDK_WIN32_DND_PRIVATE_H__ */
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
