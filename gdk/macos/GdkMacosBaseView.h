/* GdkMacosBaseView.h
 *
 * Copyright © 2020 Red Hat, Inc.
 * Copyright © 2005-2007 Imendio AB
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
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

<<<<<<< HEAD:gdk/macos/GdkMacosBaseView.h
#include <gdk/gdk.h>
=======
/* Text Input Client */
#define TIC_MARKED_TEXT "tic-marked-text"
#define TIC_SELECTED_POS  "tic-selected-pos"
#define TIC_SELECTED_LEN  "tic-selected-len"
#define TIC_INSERT_TEXT "tic-insert-text"
#define TIC_INSERT_TEXT_REPLACE_LEN "tic-insert-text-replace-len"
#define TIC_IN_KEY_DOWN "tic-in-key-down"
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gdk/quartz/GdkQuartzView.h

#include "gdkmacosdisplay.h"
#include "gdkmacossurface.h"

#define GDK_IS_MACOS_BASE_VIEW(obj) ((obj) && [obj isKindOfClass:[GdkMacosBaseView class]])

@interface GdkMacosBaseView : NSView <NSTextInputClient>
{
  NSTrackingArea *trackingArea;
  BOOL needsInvalidateShadow;
  NSRange markedRange;
  NSRange selectedRange;
}

-(GdkMacosSurface *)gdkSurface;
-(GdkMacosDisplay *)gdkDisplay;
-(void)setNeedsInvalidateShadow: (BOOL)invalidate;
-(NSTrackingArea *)trackingArea;
-(void)setOpaqueRegion:(cairo_region_t *)region;
-(void)setInputArea:(const cairo_rectangle_int_t *)area;

@end
