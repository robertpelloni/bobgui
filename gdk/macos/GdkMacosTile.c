/* GdkMacosTile.c
 *
 * Copyright © 2022 Red Hat, Inc.
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

#include "config.h"
<<<<<<< HEAD:gdk/macos/GdkMacosTile.c
=======
#include "gdktypes.h"
#include "gdkprivate.h"
#include "gdkquartz.h"
#include "gdkinternal-quartz.h"
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gdk/quartz/gdkglobals-quartz.c

#include <AppKit/AppKit.h>

#import "GdkMacosTile.h"

@implementation GdkMacosTile

-(id)init
{
<<<<<<< HEAD:gdk/macos/GdkMacosTile.c
  self = [super init];

  [self setEdgeAntialiasingMask:0];
  [self setDrawsAsynchronously:YES];

  return self;
=======
  static gint32 vkey = GDK_OSX_UNSUPPORTED;

  if (vkey == GDK_OSX_UNSUPPORTED)
    {
#if MAC_OS_X_VERSION_MIN_REQUIRED < 101000
      OSErr err = Gestalt (gestaltSystemVersionMinor, (SInt32*)&vkey);

      g_return_val_if_fail (err == noErr, GDK_OSX_UNSUPPORTED);
#else
      NSOperatingSystemVersion version;

      version = [[NSProcessInfo processInfo] operatingSystemVersion];
      vkey = version.majorVersion == 10 ? version.minorVersion : version.majorVersion + 5;
#endif
    }

  if (vkey < GDK_OSX_MIN)
    return GDK_OSX_UNSUPPORTED;
  else if (vkey > GDK_OSX_CURRENT)
    return GDK_OSX_NEW;
  else
    return vkey;
>>>>>>> origin/4627-printing-Unref-old-spool_io-before-setting-new-one-gtk3:gdk/quartz/gdkglobals-quartz.c
}

-(void)swapBuffer:(IOSurfaceRef)buffer withRect:(CGRect)rect
{
  if G_LIKELY ([self contents] == (id)buffer)
    [(id<CanSetContentsChanged>)self setContentsChanged];
  else
    [self setContents:(id)buffer];

  if G_UNLIKELY (!CGRectEqualToRect ([self contentsRect], rect))
    self.contentsRect = rect;
}

@end
