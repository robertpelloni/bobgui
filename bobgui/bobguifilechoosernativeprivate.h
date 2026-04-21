/* BOBGUI - The Bobgui Framework
 * bobguifilechoosernativeprivate.h: Native File selector dialog
 * Copyright (C) 2015, Red Hat, Inc.
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

#pragma once

<<<<<<< HEAD:bobgui/bobguifilechoosernativeprivate.h
#include <bobgui/deprecated/bobguifilechoosernative.h>
=======
#include <gtk/gtkfilechoosernative.h>
#ifdef GDK_WINDOWING_QUARTZ
#include <AvailabilityMacros.h>
#endif
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gtk/gtkfilechoosernativeprivate.h

G_BEGIN_DECLS

typedef struct {
  char *id;
  char *label;
  char **options;
  char **option_labels;
  char *selected;
} BobguiFileChooserNativeChoice;

struct _BobguiFileChooserNative
{
  BobguiNativeDialog parent_instance;

  char *accept_label;
  char *cancel_label;

  int mode;
  GSList *custom_files;

  GFile *current_folder;
  GFile *current_file;
  char *current_name;
  BobguiFileFilter *current_filter;
  GSList *choices;

  /* Fallback mode */
  BobguiWidget *dialog;
  BobguiWidget *accept_button;
  BobguiWidget *cancel_button;

  gpointer mode_data;
};

gboolean bobgui_file_chooser_native_win32_show (BobguiFileChooserNative *self);
void bobgui_file_chooser_native_win32_hide (BobguiFileChooserNative *self);

<<<<<<< HEAD:bobgui/bobguifilechoosernativeprivate.h
gboolean bobgui_file_chooser_native_quartz_show (BobguiFileChooserNative *self);
void bobgui_file_chooser_native_quartz_hide (BobguiFileChooserNative *self);
=======
#if defined GDK_WINDOWING_QUARTZ && MAC_OS_X_VERSION_MAX_ALLOWED >= 1060
gboolean gtk_file_chooser_native_quartz_show (GtkFileChooserNative *self);
void gtk_file_chooser_native_quartz_hide (GtkFileChooserNative *self);
#endif
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gtk/gtkfilechoosernativeprivate.h

gboolean bobgui_file_chooser_native_android_show (BobguiFileChooserNative *self);
void bobgui_file_chooser_native_android_hide (BobguiFileChooserNative *self);

gboolean bobgui_file_chooser_native_portal_show (BobguiFileChooserNative *self);
void bobgui_file_chooser_native_portal_hide (BobguiFileChooserNative *self);

G_END_DECLS

