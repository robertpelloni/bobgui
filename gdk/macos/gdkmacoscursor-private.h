/* gdkmacoscursor-private.h
 *
 * Copyright (C) 2005-2007 Imendio AB
 * Copyright (C) 2020 Red Hat, Inc.
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

<<<<<<< HEAD:gdk/macos/gdkmacoscursor-private.h
#pragma once
=======
#ifndef __GDK_QUARTZ_DND__
#define __GDK_QUARTZ_DND__

#include <gdkdndprivate.h>
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gdk/quartz/gdkdnd-quartz.h

#include <AppKit/AppKit.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

NSCursor *_gdk_macos_cursor_get_ns_cursor (GdkCursor *cursor);

G_END_DECLS

