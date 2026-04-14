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

#include <gdk/gdktypes.h>
#include <gdk/gdkdevice.h>
#include <gdk/gdkdevicetool.h>
#include <gdk/gdkdrag.h>

G_BEGIN_DECLS

#define GDK_TYPE_EVENT          (gdk_event_get_type ())
#define GDK_TYPE_EVENT_SEQUENCE (gdk_event_sequence_get_type ())

#define GDK_IS_EVENT(obj)       (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_EVENT))
#define GDK_EVENT(obj)          (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_EVENT, GdkEvent))

#define GDK_IS_EVENT_TYPE(event, type)  (gdk_event_get_event_type ((event)) == (type))

/**
 * GDK_PRIORITY_EVENTS: (value 0)
 *
 * This is the priority that events from the X server are given in the main loop.
 */
#define GDK_PRIORITY_EVENTS	(G_PRIORITY_DEFAULT)

/**
 * GDK_PRIORITY_REDRAW: (value 120)
 *
 * This is the priority that the idle handler processing surface updates
 * is given in the main loop.
 */
#define GDK_PRIORITY_REDRAW     (G_PRIORITY_HIGH_IDLE + 20)

/**
 * GDK_EVENT_PROPAGATE:
 *
 * Use this macro as the return value for continuing the propagation of
 * an event handler.
 */
#define GDK_EVENT_PROPAGATE     (FALSE)

/**
 * GDK_EVENT_STOP:
 *
 * Use this macro as the return value for stopping the propagation of
 * an event handler.
 */
#define GDK_EVENT_STOP          (TRUE)

/**
 * GDK_BUTTON_PRIMARY:
 *
 * The primary button. This is typically the left mouse button, or the
 * right button in a left-handed setup.
 */
#define GDK_BUTTON_PRIMARY      (1)

/**
 * GDK_BUTTON_MIDDLE:
 *
 * The middle button.
 */
#define GDK_BUTTON_MIDDLE       (2)

/**
 * GDK_BUTTON_SECONDARY:
 *
 * The secondary button. This is typically the right mouse button, or the
 * left button in a left-handed setup.
 */
#define GDK_BUTTON_SECONDARY    (3)

typedef struct _GdkEventSequence        GdkEventSequence;
typedef struct _GdkEvent                GdkEvent;

#define GDK_TYPE_BUTTON_EVENT (gdk_button_event_get_type())
#define GDK_TYPE_CROSSING_EVENT (gdk_crossing_event_get_type())
#define GDK_TYPE_DELETE_EVENT (gdk_delete_event_get_type())
#define GDK_TYPE_DND_EVENT (gdk_dnd_event_get_type())
#define GDK_TYPE_FOCUS_EVENT (gdk_focus_event_get_type())
#define GDK_TYPE_GRAB_BROKEN_EVENT (gdk_grab_broken_event_get_type())
#define GDK_TYPE_KEY_EVENT (gdk_key_event_get_type())
#define GDK_TYPE_MOTION_EVENT (gdk_motion_event_get_type())
#define GDK_TYPE_PAD_EVENT (gdk_pad_event_get_type())
#define GDK_TYPE_PROXIMITY_EVENT (gdk_proximity_event_get_type())
#define GDK_TYPE_SCROLL_EVENT (gdk_scroll_event_get_type())
#define GDK_TYPE_TOUCH_EVENT (gdk_touch_event_get_type())
#define GDK_TYPE_TOUCHPAD_EVENT (gdk_touchpad_event_get_type())

typedef struct _GdkButtonEvent          GdkButtonEvent;
typedef struct _GdkCrossingEvent        GdkCrossingEvent;
typedef struct _GdkDeleteEvent          GdkDeleteEvent;
typedef struct _GdkDNDEvent             GdkDNDEvent;
typedef struct _GdkFocusEvent           GdkFocusEvent;
typedef struct _GdkGrabBrokenEvent      GdkGrabBrokenEvent;
typedef struct _GdkKeyEvent             GdkKeyEvent;
typedef struct _GdkMotionEvent          GdkMotionEvent;
typedef struct _GdkPadEvent             GdkPadEvent;
typedef struct _GdkProximityEvent       GdkProximityEvent;
typedef struct _GdkScrollEvent          GdkScrollEvent;
typedef struct _GdkTouchEvent           GdkTouchEvent;
typedef struct _GdkTouchpadEvent        GdkTouchpadEvent;

/**
 * GdkEventType:
 * @GDK_DELETE: the window manager has requested that the toplevel surface be
 *   hidden or destroyed, usually when the user clicks on a special icon in the
 *   title bar.
 * @GDK_MOTION_NOTIFY: the pointer (usually a mouse) has moved.
 * @GDK_BUTTON_PRESS: a mouse button has been pressed.
 * @GDK_BUTTON_RELEASE: a mouse button has been released.
 * @GDK_KEY_PRESS: a key has been pressed.
 * @GDK_KEY_RELEASE: a key has been released.
 * @GDK_ENTER_NOTIFY: the pointer has entered the surface.
 * @GDK_LEAVE_NOTIFY: the pointer has left the surface.
 * @GDK_FOCUS_CHANGE: the keyboard focus has entered or left the surface.
 * @GDK_PROXIMITY_IN: an input device has moved into contact with a sensing
 *   surface (e.g. a touchscreen or graphics tablet).
 * @GDK_PROXIMITY_OUT: an input device has moved out of contact with a sensing
 *   surface.
 * @GDK_DRAG_ENTER: the mouse has entered the surface while a drag is in progress.
 * @GDK_DRAG_LEAVE: the mouse has left the surface while a drag is in progress.
 * @GDK_DRAG_MOTION: the mouse has moved in the surface while a drag is in
 *   progress.
 * @GDK_DROP_START: a drop operation onto the surface has started.
 * @GDK_SCROLL: the scroll wheel was turned
 * @GDK_GRAB_BROKEN: a pointer or keyboard grab was broken.
 * @GDK_TOUCH_BEGIN: A new touch event sequence has just started.
 * @GDK_TOUCH_UPDATE: A touch event sequence has been updated.
 * @GDK_TOUCH_END: A touch event sequence has finished.
 * @GDK_TOUCH_CANCEL: A touch event sequence has been canceled.
 * @GDK_TOUCHPAD_SWIPE: A touchpad swipe gesture event, the current state
 *   is determined by its phase field.
 * @GDK_TOUCHPAD_PINCH: A touchpad pinch gesture event, the current state
 *   is determined by its phase field.
 * @GDK_PAD_BUTTON_PRESS: A tablet pad button press event.
 * @GDK_PAD_BUTTON_RELEASE: A tablet pad button release event.
 * @GDK_PAD_RING: A tablet pad axis event from a "ring".
 * @GDK_PAD_STRIP: A tablet pad axis event from a "strip".
 * @GDK_PAD_GROUP_MODE: A tablet pad group mode change.
 * @GDK_PAD_DIAL: A tablet pad axis event from a "dial".
 * @GDK_EVENT_LAST: marks the end of the GdkEventType enumeration.
 *
 * Specifies the type of the event.
 */
/**
  * GDK_TOUCHPAD_HOLD:
  *
  * A touchpad hold gesture event, the current state is determined by its phase
  * field.
  *
  * Since: 4.6
  */
typedef enum
{
  GDK_DELETE,
  GDK_MOTION_NOTIFY,
  GDK_BUTTON_PRESS,
  GDK_BUTTON_RELEASE,
  GDK_KEY_PRESS,
  GDK_KEY_RELEASE,
  GDK_ENTER_NOTIFY,
  GDK_LEAVE_NOTIFY,
  GDK_FOCUS_CHANGE,
  GDK_PROXIMITY_IN,
  GDK_PROXIMITY_OUT,
  GDK_DRAG_ENTER,
  GDK_DRAG_LEAVE,
  GDK_DRAG_MOTION,
  GDK_DROP_START,
  GDK_SCROLL,
  GDK_GRAB_BROKEN,
  GDK_TOUCH_BEGIN,
  GDK_TOUCH_UPDATE,
  GDK_TOUCH_END,
  GDK_TOUCH_CANCEL,
  GDK_TOUCHPAD_SWIPE,
  GDK_TOUCHPAD_PINCH,
  GDK_PAD_BUTTON_PRESS,
  GDK_PAD_BUTTON_RELEASE,
  GDK_PAD_RING,
  GDK_PAD_STRIP,
  GDK_PAD_GROUP_MODE,
  GDK_TOUCHPAD_HOLD,
  GDK_PAD_DIAL,
  GDK_EVENT_LAST        /* helper variable for decls */
} GdkEventType;

/**
 * GdkTouchpadGesturePhase:
 * @GDK_TOUCHPAD_GESTURE_PHASE_BEGIN: The gesture has begun.
 * @GDK_TOUCHPAD_GESTURE_PHASE_UPDATE: The gesture has been updated.
 * @GDK_TOUCHPAD_GESTURE_PHASE_END: The gesture was finished, changes
 *   should be permanently applied.
 * @GDK_TOUCHPAD_GESTURE_PHASE_CANCEL: The gesture was cancelled, all
 *   changes should be undone.
 *
 * Specifies the current state of a touchpad gesture.
 *
 * All gestures are guaranteed to begin with an event with phase
 * %GDK_TOUCHPAD_GESTURE_PHASE_BEGIN, followed by 0 or several events
 * with phase %GDK_TOUCHPAD_GESTURE_PHASE_UPDATE.
 *
 * A finished gesture may have 2 possible outcomes, an event with phase
 * %GDK_TOUCHPAD_GESTURE_PHASE_END will be emitted when the gesture is
 * considered successful, this should be used as the hint to perform any
 * permanent changes.

 * Cancelled gestures may be so for a variety of reasons, due to hardware
 * or the compositor, or due to the gesture recognition layers hinting the
 * gesture did not finish resolutely (eg. a 3rd finger being added during
 * a pinch gesture). In these cases, the last event will report the phase
 * %GDK_TOUCHPAD_GESTURE_PHASE_CANCEL, this should be used as a hint
 * to undo any visible/permanent changes that were done throughout the
 * progress of the gesture.
 */
typedef enum
{
  GDK_TOUCHPAD_GESTURE_PHASE_BEGIN,
  GDK_TOUCHPAD_GESTURE_PHASE_UPDATE,
  GDK_TOUCHPAD_GESTURE_PHASE_END,
  GDK_TOUCHPAD_GESTURE_PHASE_CANCEL
} GdkTouchpadGesturePhase;

/**
 * GdkScrollDirection:
 * @GDK_SCROLL_UP: the surface is scrolled up.
 * @GDK_SCROLL_DOWN: the surface is scrolled down.
 * @GDK_SCROLL_LEFT: the surface is scrolled to the left.
 * @GDK_SCROLL_RIGHT: the surface is scrolled to the right.
 * @GDK_SCROLL_SMOOTH: the scrolling is determined by the delta values
 *   in scroll events. See gdk_scroll_event_get_deltas()
 *
 * Specifies the direction for scroll events.
 */
typedef enum
{
  GDK_SCROLL_UP,
  GDK_SCROLL_DOWN,
  GDK_SCROLL_LEFT,
  GDK_SCROLL_RIGHT,
  GDK_SCROLL_SMOOTH
} GdkScrollDirection;

/**
 * GdkScrollUnit:
 * @GDK_SCROLL_UNIT_WHEEL: The delta is in number of wheel clicks.
 * @GDK_SCROLL_UNIT_SURFACE: The delta is in surface pixels to scroll directly
 *   on screen.
 *
 * Specifies the unit of scroll deltas.
 *
 * When you get %GDK_SCROLL_UNIT_WHEEL, a delta of 1.0 means 1 wheel detent
 * click in the south direction, 2.0 means 2 wheel detent clicks in the south
 * direction... This is the same logic for negative values but in the north
 * direction.
 *
 * If you get %GDK_SCROLL_UNIT_SURFACE, are managing a scrollable view and get a
 * value of 123, you have to scroll 123 surface logical pixels right if it's
 * @delta_x or down if it's @delta_y. This is the same logic for negative values
 * but you have to scroll left instead of right if it's @delta_x and up instead
 * of down if it's @delta_y.
 *
 * 1 surface logical pixel is equal to 1 real screen pixel multiplied by the
 * final scale factor of your graphical interface (the product of the desktop
 * scale factor and eventually a custom scale factor in your app).
 *
 * Since: 4.8
 */
typedef enum
{
  GDK_SCROLL_UNIT_WHEEL,
  GDK_SCROLL_UNIT_SURFACE
} GdkScrollUnit;

/**
 * GdkNotifyType:
 * @GDK_NOTIFY_ANCESTOR: the surface is entered from an ancestor or
 *   left towards an ancestor.
 * @GDK_NOTIFY_VIRTUAL: the pointer moves between an ancestor and an
 *   inferior of the surface.
 * @GDK_NOTIFY_INFERIOR: the surface is entered from an inferior or
 *   left towards an inferior.
 * @GDK_NOTIFY_NONLINEAR: the surface is entered from or left towards
 *   a surface which is neither an ancestor nor an inferior.
 * @GDK_NOTIFY_NONLINEAR_VIRTUAL: the pointer moves between two surfaces
 *   which are not ancestors of each other and the surface is part of
 *   the ancestor chain between one of these surfaces and their least
 *   common ancestor.
 * @GDK_NOTIFY_UNKNOWN: an unknown type of enter/leave event occurred.
 *
 * Specifies the kind of crossing for enter and leave events.
 *
 * See the X11 protocol specification of LeaveNotify for
 * full details of crossing event generation.
 */
typedef enum
{
  GDK_NOTIFY_ANCESTOR		= 0,
  GDK_NOTIFY_VIRTUAL		= 1,
  GDK_NOTIFY_INFERIOR		= 2,
  GDK_NOTIFY_NONLINEAR		= 3,
  GDK_NOTIFY_NONLINEAR_VIRTUAL	= 4,
  GDK_NOTIFY_UNKNOWN		= 5
} GdkNotifyType;

/**
 * GdkCrossingMode:
 * @GDK_CROSSING_NORMAL: crossing because of pointer motion.
 * @GDK_CROSSING_GRAB: crossing because a grab is activated.
 * @GDK_CROSSING_UNGRAB: crossing because a grab is deactivated.
 * @GDK_CROSSING_BOBGUI_GRAB: crossing because a BOBGUI grab is activated.
 * @GDK_CROSSING_BOBGUI_UNGRAB: crossing because a BOBGUI grab is deactivated.
 * @GDK_CROSSING_STATE_CHANGED: crossing because a BOBGUI widget changed
 *   state (e.g. sensitivity).
 * @GDK_CROSSING_TOUCH_BEGIN: crossing because a touch sequence has begun,
 *   this event is synthetic as the pointer might have not left the surface.
 * @GDK_CROSSING_TOUCH_END: crossing because a touch sequence has ended,
 *   this event is synthetic as the pointer might have not left the surface.
 * @GDK_CROSSING_DEVICE_SWITCH: crossing because of a device switch (i.e.
 *   a mouse taking control of the pointer after a touch device), this event
 *   is synthetic as the pointer didn’t leave the surface.
 *
 * Specifies the crossing mode for enter and leave events.
 */
typedef enum
{
  GDK_CROSSING_NORMAL,
  GDK_CROSSING_GRAB,
  GDK_CROSSING_UNGRAB,
  GDK_CROSSING_BOBGUI_GRAB,
  GDK_CROSSING_BOBGUI_UNGRAB,
  GDK_CROSSING_STATE_CHANGED,
  GDK_CROSSING_TOUCH_BEGIN,
  GDK_CROSSING_TOUCH_END,
  GDK_CROSSING_DEVICE_SWITCH
} GdkCrossingMode;

<<<<<<< HEAD
GDK_AVAILABLE_IN_ALL
GType                   gdk_event_get_type              (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GType                   gdk_event_sequence_get_type     (void) G_GNUC_CONST;
=======
/**
 * GdkPropertyState:
 * @GDK_PROPERTY_NEW_VALUE: the property value was changed.
 * @GDK_PROPERTY_DELETE: the property was deleted.
 *
 * Specifies the type of a property change for a #GdkEventProperty.
 */
typedef enum
{
  GDK_PROPERTY_NEW_VALUE,
  GDK_PROPERTY_DELETE
} GdkPropertyState;

/**
 * GdkWindowState:
 * @GDK_WINDOW_STATE_WITHDRAWN: the window is not shown.
 * @GDK_WINDOW_STATE_ICONIFIED: the window is minimized.
 * @GDK_WINDOW_STATE_MAXIMIZED: the window is maximized.
 * @GDK_WINDOW_STATE_STICKY: the window is sticky.
 * @GDK_WINDOW_STATE_FULLSCREEN: the window is maximized without
 *   decorations.
 * @GDK_WINDOW_STATE_ABOVE: the window is kept above other windows.
 * @GDK_WINDOW_STATE_BELOW: the window is kept below other windows.
 * @GDK_WINDOW_STATE_FOCUSED: the window is presented as focused (with active decorations).
 * @GDK_WINDOW_STATE_TILED: the window is in a tiled state, Since 3.10. Since 3.22.23, this
 *                          is deprecated in favor of per-edge information.
 * @GDK_WINDOW_STATE_TOP_TILED: whether the top edge is tiled, Since 3.22.23
 * @GDK_WINDOW_STATE_TOP_RESIZABLE: whether the top edge is resizable, Since 3.22.23
 * @GDK_WINDOW_STATE_RIGHT_TILED: whether the right edge is tiled, Since 3.22.23
 * @GDK_WINDOW_STATE_RIGHT_RESIZABLE: whether the right edge is resizable, Since 3.22.23
 * @GDK_WINDOW_STATE_BOTTOM_TILED: whether the bottom edge is tiled, Since 3.22.23
 * @GDK_WINDOW_STATE_BOTTOM_RESIZABLE: whether the bottom edge is resizable, Since 3.22.23
 * @GDK_WINDOW_STATE_LEFT_TILED: whether the left edge is tiled, Since 3.22.23
 * @GDK_WINDOW_STATE_LEFT_RESIZABLE: whether the left edge is resizable, Since 3.22.23
 *
 * Specifies the state of a toplevel window.
 */
typedef enum
{
  GDK_WINDOW_STATE_WITHDRAWN        = 1 << 0,
  GDK_WINDOW_STATE_ICONIFIED        = 1 << 1,
  GDK_WINDOW_STATE_MAXIMIZED        = 1 << 2,
  GDK_WINDOW_STATE_STICKY           = 1 << 3,
  GDK_WINDOW_STATE_FULLSCREEN       = 1 << 4,
  GDK_WINDOW_STATE_ABOVE            = 1 << 5,
  GDK_WINDOW_STATE_BELOW            = 1 << 6,
  GDK_WINDOW_STATE_FOCUSED          = 1 << 7,
  GDK_WINDOW_STATE_TILED            = 1 << 8,
  GDK_WINDOW_STATE_TOP_TILED        = 1 << 9,
  GDK_WINDOW_STATE_TOP_RESIZABLE    = 1 << 10,
  GDK_WINDOW_STATE_RIGHT_TILED      = 1 << 11,
  GDK_WINDOW_STATE_RIGHT_RESIZABLE  = 1 << 12,
  GDK_WINDOW_STATE_BOTTOM_TILED     = 1 << 13,
  GDK_WINDOW_STATE_BOTTOM_RESIZABLE = 1 << 14,
  GDK_WINDOW_STATE_LEFT_TILED       = 1 << 15,
  GDK_WINDOW_STATE_LEFT_RESIZABLE   = 1 << 16
} GdkWindowState;

/**
 * GdkSettingAction:
 * @GDK_SETTING_ACTION_NEW: a setting was added.
 * @GDK_SETTING_ACTION_CHANGED: a setting was changed.
 * @GDK_SETTING_ACTION_DELETED: a setting was deleted.
 *
 * Specifies the kind of modification applied to a setting in a
 * #GdkEventSetting.
 */
typedef enum
{
  GDK_SETTING_ACTION_NEW,
  GDK_SETTING_ACTION_CHANGED,
  GDK_SETTING_ACTION_DELETED
} GdkSettingAction;

/**
 * GdkOwnerChange:
 * @GDK_OWNER_CHANGE_NEW_OWNER: some other app claimed the ownership
 * @GDK_OWNER_CHANGE_DESTROY: the window was destroyed
 * @GDK_OWNER_CHANGE_CLOSE: the client was closed
 *
 * Specifies why a selection ownership was changed.
 */
typedef enum
{
  GDK_OWNER_CHANGE_NEW_OWNER,
  GDK_OWNER_CHANGE_DESTROY,
  GDK_OWNER_CHANGE_CLOSE
} GdkOwnerChange;

/**
 * GdkEventAny:
 * @type: the type of the event.
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 *
 * Contains the fields which are common to all event structs.
 * Any event pointer can safely be cast to a pointer to a #GdkEventAny to
 * access these fields.
 */
struct _GdkEventAny
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
};

/**
 * GdkEventExpose:
 * @type: the type of the event (%GDK_EXPOSE or %GDK_DAMAGE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @area: bounding box of @region.
 * @region: the region that needs to be redrawn.
 * @count: the number of contiguous %GDK_EXPOSE events following this one.
 *   The only use for this is “exposure compression”, i.e. handling all
 *   contiguous %GDK_EXPOSE events in one go, though GDK performs some
 *   exposure compression so this is not normally needed.
 *
 * Generated when all or part of a window becomes visible and needs to be
 * redrawn.
 */
struct _GdkEventExpose
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkRectangle area;
  cairo_region_t *region;
  gint count; /* If non-zero, how many more events follow. */
};

/**
 * GdkEventVisibility:
 * @type: the type of the event (%GDK_VISIBILITY_NOTIFY).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @state: the new visibility state (%GDK_VISIBILITY_FULLY_OBSCURED,
 *   %GDK_VISIBILITY_PARTIAL or %GDK_VISIBILITY_UNOBSCURED).
 *
 * Generated when the window visibility status has changed.
 *
 * Deprecated: 3.12: Modern composited windowing systems with pervasive
 *     transparency make it impossible to track the visibility of a window
 *     reliably, so this event can not be guaranteed to provide useful
 *     information.
 */
struct _GdkEventVisibility
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkVisibilityState state;
};

/**
 * GdkEventMotion:
 * @type: the type of the event.
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @x: the x coordinate of the pointer relative to the window.
 * @y: the y coordinate of the pointer relative to the window.
 * @axes: @x, @y translated to the axes of @device, or %NULL if @device is
 *   the mouse.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 * @is_hint: set to 1 if this event is just a hint, see the
 *   %GDK_POINTER_MOTION_HINT_MASK value of #GdkEventMask.
 * @device: the master device that the event originated from. Use
 * gdk_event_get_source_device() to get the slave device.
 * @x_root: the x coordinate of the pointer relative to the root of the
 *   screen.
 * @y_root: the y coordinate of the pointer relative to the root of the
 *   screen.
 *
 * Generated when the pointer moves.
 */
struct _GdkEventMotion
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble *axes;
  guint state;
  gint16 is_hint;
  GdkDevice *device;
  gdouble x_root, y_root;
};

/**
 * GdkEventButton:
 * @type: the type of the event (%GDK_BUTTON_PRESS, %GDK_2BUTTON_PRESS,
 *   %GDK_3BUTTON_PRESS or %GDK_BUTTON_RELEASE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @x: the x coordinate of the pointer relative to the window.
 * @y: the y coordinate of the pointer relative to the window.
 * @axes: @x, @y translated to the axes of @device, or %NULL if @device is
 *   the mouse.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 * @button: the button which was pressed or released, numbered from 1 to 5.
 *   Normally button 1 is the left mouse button, 2 is the middle button,
 *   and 3 is the right button. On 2-button mice, the middle button can
 *   often be simulated by pressing both mouse buttons together.
 * @device: the master device that the event originated from. Use
 * gdk_event_get_source_device() to get the slave device.
 * @x_root: the x coordinate of the pointer relative to the root of the
 *   screen.
 * @y_root: the y coordinate of the pointer relative to the root of the
 *   screen.
 *
 * Used for button press and button release events. The
 * @type field will be one of %GDK_BUTTON_PRESS,
 * %GDK_2BUTTON_PRESS, %GDK_3BUTTON_PRESS or %GDK_BUTTON_RELEASE,
 *
 * Double and triple-clicks result in a sequence of events being received.
 * For double-clicks the order of events will be:
 *
 * - %GDK_BUTTON_PRESS
 * - %GDK_BUTTON_RELEASE
 * - %GDK_BUTTON_PRESS
 * - %GDK_2BUTTON_PRESS
 * - %GDK_BUTTON_RELEASE
 *
 * Note that the first click is received just like a normal
 * button press, while the second click results in a %GDK_2BUTTON_PRESS
 * being received just after the %GDK_BUTTON_PRESS.
 *
 * Triple-clicks are very similar to double-clicks, except that
 * %GDK_3BUTTON_PRESS is inserted after the third click. The order of the
 * events is:
 *
 * - %GDK_BUTTON_PRESS
 * - %GDK_BUTTON_RELEASE
 * - %GDK_BUTTON_PRESS
 * - %GDK_2BUTTON_PRESS
 * - %GDK_BUTTON_RELEASE
 * - %GDK_BUTTON_PRESS
 * - %GDK_3BUTTON_PRESS
 * - %GDK_BUTTON_RELEASE
 *
 * For a double click to occur, the second button press must occur within
 * 1/4 of a second of the first. For a triple click to occur, the third
 * button press must also occur within 1/2 second of the first button press.
 */
struct _GdkEventButton
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble *axes;
  guint state;
  guint button;
  GdkDevice *device;
  gdouble x_root, y_root;
};

/**
 * GdkEventTouch:
 * @type: the type of the event (%GDK_TOUCH_BEGIN, %GDK_TOUCH_UPDATE,
 *   %GDK_TOUCH_END, %GDK_TOUCH_CANCEL)
 * @window: the window which received the event
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @x: the x coordinate of the pointer relative to the window
 * @y: the y coordinate of the pointer relative to the window
 * @axes: @x, @y translated to the axes of @device, or %NULL if @device is
 *   the mouse
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType
 * @sequence: the event sequence that the event belongs to
 * @emulating_pointer: whether the event should be used for emulating
 *   pointer event
 * @device: the master device that the event originated from. Use
 * gdk_event_get_source_device() to get the slave device.
 * @x_root: the x coordinate of the pointer relative to the root of the
 *   screen
 * @y_root: the y coordinate of the pointer relative to the root of the
 *   screen
 *
 * Used for touch events.
 * @type field will be one of %GDK_TOUCH_BEGIN, %GDK_TOUCH_UPDATE,
 * %GDK_TOUCH_END or %GDK_TOUCH_CANCEL.
 *
 * Touch events are grouped into sequences by means of the @sequence
 * field, which can also be obtained with gdk_event_get_event_sequence().
 * Each sequence begins with a %GDK_TOUCH_BEGIN event, followed by
 * any number of %GDK_TOUCH_UPDATE events, and ends with a %GDK_TOUCH_END
 * (or %GDK_TOUCH_CANCEL) event. With multitouch devices, there may be
 * several active sequences at the same time.
 */
struct _GdkEventTouch
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble *axes;
  guint state;
  GdkEventSequence *sequence;
  gboolean emulating_pointer;
  GdkDevice *device;
  gdouble x_root, y_root;
};

/**
 * GdkEventScroll:
 * @type: the type of the event (%GDK_SCROLL).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @x: the x coordinate of the pointer relative to the window.
 * @y: the y coordinate of the pointer relative to the window.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 * @direction: the direction to scroll to (one of %GDK_SCROLL_UP,
 *   %GDK_SCROLL_DOWN, %GDK_SCROLL_LEFT, %GDK_SCROLL_RIGHT or
 *   %GDK_SCROLL_SMOOTH).
 * @device: the master device that the event originated from. Use
 * gdk_event_get_source_device() to get the slave device.
 * @x_root: the x coordinate of the pointer relative to the root of the
 *   screen.
 * @y_root: the y coordinate of the pointer relative to the root of the
 *   screen.
 * @delta_x: the x coordinate of the scroll delta
 * @delta_y: the y coordinate of the scroll delta
 *
 * Generated from button presses for the buttons 4 to 7. Wheel mice are
 * usually configured to generate button press events for buttons 4 and 5
 * when the wheel is turned.
 *
 * Some GDK backends can also generate “smooth” scroll events, which
 * can be recognized by the %GDK_SCROLL_SMOOTH scroll direction. For
 * these, the scroll deltas can be obtained with
 * gdk_event_get_scroll_deltas().
 */
struct _GdkEventScroll
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  gdouble x;
  gdouble y;
  guint state;
  GdkScrollDirection direction;
  GdkDevice *device;
  gdouble x_root, y_root;
  gdouble delta_x;
  gdouble delta_y;
  guint is_stop : 1;
};

/**
 * GdkEventKey:
 * @type: the type of the event (%GDK_KEY_PRESS or %GDK_KEY_RELEASE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 * @keyval: the key that was pressed or released. See the
 *   `gdk/gdkkeysyms.h` header file for a
 *   complete list of GDK key codes.
 * @length: the length of @string.
 * @string: a string containing an approximation of the text that
 *   would result from this keypress. The only correct way to handle text
 *   input of text is using input methods (see #GtkIMContext), so this
 *   field is deprecated and should never be used.
 *   (gdk_unicode_to_keyval() provides a non-deprecated way of getting
 *   an approximate translation for a key.) The string is encoded in the
 *   encoding of the current locale (Note: this for backwards compatibility:
 *   strings in GTK+ and GDK are typically in UTF-8.) and NUL-terminated.
 *   In some cases, the translation of the key code will be a single
 *   NUL byte, in which case looking at @length is necessary to distinguish
 *   it from the an empty translation.
 * @hardware_keycode: the raw code of the key that was pressed or released.
 * @group: the keyboard group.
 * @is_modifier: a flag that indicates if @hardware_keycode is mapped to a
 *   modifier. Since 2.10
 *
 * Describes a key press or key release event.
 */
struct _GdkEventKey
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  guint state;
  guint keyval;
  gint length;
  gchar *string;
  guint16 hardware_keycode;
  guint8 group;
  guint is_modifier : 1;
};

/**
 * GdkEventCrossing:
 * @type: the type of the event (%GDK_ENTER_NOTIFY or %GDK_LEAVE_NOTIFY).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @subwindow: the window that was entered or left.
 * @time: the time of the event in milliseconds.
 * @x: the x coordinate of the pointer relative to the window.
 * @y: the y coordinate of the pointer relative to the window.
 * @x_root: the x coordinate of the pointer relative to the root of the screen.
 * @y_root: the y coordinate of the pointer relative to the root of the screen.
 * @mode: the crossing mode (%GDK_CROSSING_NORMAL, %GDK_CROSSING_GRAB,
 *  %GDK_CROSSING_UNGRAB, %GDK_CROSSING_GTK_GRAB, %GDK_CROSSING_GTK_UNGRAB or
 *  %GDK_CROSSING_STATE_CHANGED).  %GDK_CROSSING_GTK_GRAB, %GDK_CROSSING_GTK_UNGRAB,
 *  and %GDK_CROSSING_STATE_CHANGED were added in 2.14 and are always synthesized,
 *  never native.
 * @detail: the kind of crossing that happened (%GDK_NOTIFY_INFERIOR,
 *  %GDK_NOTIFY_ANCESTOR, %GDK_NOTIFY_VIRTUAL, %GDK_NOTIFY_NONLINEAR or
 *  %GDK_NOTIFY_NONLINEAR_VIRTUAL).
 * @focus: %TRUE if @window is the focus window or an inferior.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 *
 * Generated when the pointer enters or leaves a window.
 */
struct _GdkEventCrossing
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkWindow *subwindow;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble x_root;
  gdouble y_root;
  GdkCrossingMode mode;
  GdkNotifyType detail;
  gboolean focus;
  guint state;
};

/**
 * GdkEventFocus:
 * @type: the type of the event (%GDK_FOCUS_CHANGE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @in: %TRUE if the window has gained the keyboard focus, %FALSE if
 *   it has lost the focus.
 *
 * Describes a change of keyboard focus.
 */
struct _GdkEventFocus
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  gint16 in;
};

/**
 * GdkEventConfigure:
 * @type: the type of the event (%GDK_CONFIGURE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @x: the new x coordinate of the window, relative to its parent.
 * @y: the new y coordinate of the window, relative to its parent.
 * @width: the new width of the window.
 * @height: the new height of the window.
 *
 * Generated when a window size or position has changed.
 */
struct _GdkEventConfigure
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  gint x, y;
  gint width;
  gint height;
};

/**
 * GdkEventProperty:
 * @type: the type of the event (%GDK_PROPERTY_NOTIFY).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @atom: the property that was changed.
 * @time: the time of the event in milliseconds.
 * @state: (type GdkPropertyState): whether the property was changed
 *   (%GDK_PROPERTY_NEW_VALUE) or deleted (%GDK_PROPERTY_DELETE).
 *
 * Describes a property change on a window.
 */
struct _GdkEventProperty
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkAtom atom;
  guint32 time;
  guint state;
};

/**
 * GdkEventSelection:
 * @type: the type of the event (%GDK_SELECTION_CLEAR,
 *   %GDK_SELECTION_NOTIFY or %GDK_SELECTION_REQUEST).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @selection: the selection.
 * @target: the target to which the selection should be converted.
 * @property: the property in which to place the result of the conversion.
 * @time: the time of the event in milliseconds.
 * @requestor: the window on which to place @property or %NULL if none.
 *
 * Generated when a selection is requested or ownership of a selection
 * is taken over by another client application.
 */
struct _GdkEventSelection
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkAtom selection;
  GdkAtom target;
  GdkAtom property;
  guint32 time;
  GdkWindow *requestor;
};

/**
 * GdkEventOwnerChange:
 * @type: the type of the event (%GDK_OWNER_CHANGE).
 * @window: the window which received the event
 * @send_event: %TRUE if the event was sent explicitly.
 * @owner: the new owner of the selection, or %NULL if there is none
 * @reason: the reason for the ownership change as a #GdkOwnerChange value
 * @selection: the atom identifying the selection
 * @time: the timestamp of the event
 * @selection_time: the time at which the selection ownership was taken
 *   over
 *
 * Generated when the owner of a selection changes. On X11, this
 * information is only available if the X server supports the XFIXES
 * extension.
 *
 * Since: 2.6
 */
struct _GdkEventOwnerChange
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkWindow *owner;
  GdkOwnerChange reason;
  GdkAtom selection;
  guint32 time;
  guint32 selection_time;
};

/**
 * GdkEventProximity:
 * @type: the type of the event (%GDK_PROXIMITY_IN or %GDK_PROXIMITY_OUT).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @device: the master device that the event originated from. Use
 * gdk_event_get_source_device() to get the slave device.
 *
 * Proximity events are generated when using GDK’s wrapper for the
 * XInput extension. The XInput extension is an add-on for standard X
 * that allows you to use nonstandard devices such as graphics tablets.
 * A proximity event indicates that the stylus has moved in or out of
 * contact with the tablet, or perhaps that the user’s finger has moved
 * in or out of contact with a touch screen.
 *
 * This event type will be used pretty rarely. It only is important for
 * XInput aware programs that are drawing their own cursor.
 */
struct _GdkEventProximity
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  GdkDevice *device;
};

/**
 * GdkEventSetting:
 * @type: the type of the event (%GDK_SETTING).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @action: what happened to the setting (%GDK_SETTING_ACTION_NEW,
 *   %GDK_SETTING_ACTION_CHANGED or %GDK_SETTING_ACTION_DELETED).
 * @name: the name of the setting.
 *
 * Generated when a setting is modified.
 */
struct _GdkEventSetting
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkSettingAction action;
  char *name;
};

/**
 * GdkEventWindowState:
 * @type: the type of the event (%GDK_WINDOW_STATE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @changed_mask: mask specifying what flags have changed.
 * @new_window_state: the new window state, a combination of
 *   #GdkWindowState bits.
 *
 * Generated when the state of a toplevel window changes.
 */
struct _GdkEventWindowState
{
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkWindowState changed_mask;
  GdkWindowState new_window_state;
};

/**
 * GdkEventGrabBroken:
 * @type: the type of the event (%GDK_GRAB_BROKEN)
 * @window: the window which received the event, i.e. the window
 *   that previously owned the grab
 * @send_event: %TRUE if the event was sent explicitly.
 * @keyboard: %TRUE if a keyboard grab was broken, %FALSE if a pointer
 *   grab was broken
 * @implicit: %TRUE if the broken grab was implicit
 * @grab_window: If this event is caused by another grab in the same
 *   application, @grab_window contains the new grab window. Otherwise
 *   @grab_window is %NULL.
 *
 * Generated when a pointer or keyboard grab is broken. On X11, this happens
 * when the grab window becomes unviewable (i.e. it or one of its ancestors
 * is unmapped), or if the same application grabs the pointer or keyboard
 * again. Note that implicit grabs (which are initiated by button presses)
 * can also cause #GdkEventGrabBroken events.
 *
 * Since: 2.8
 */
struct _GdkEventGrabBroken {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  gboolean keyboard;
  gboolean implicit;
  GdkWindow *grab_window;
};

/**
 * GdkEventDND:
 * @type: the type of the event (%GDK_DRAG_ENTER, %GDK_DRAG_LEAVE,
 *   %GDK_DRAG_MOTION, %GDK_DRAG_STATUS, %GDK_DROP_START or
 *   %GDK_DROP_FINISHED).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @context: the #GdkDragContext for the current DND operation.
 * @time: the time of the event in milliseconds.
 * @x_root: the x coordinate of the pointer relative to the root of the
 *   screen, only set for %GDK_DRAG_MOTION and %GDK_DROP_START.
 * @y_root: the y coordinate of the pointer relative to the root of the
 *   screen, only set for %GDK_DRAG_MOTION and %GDK_DROP_START.
 *
 * Generated during DND operations.
 */
struct _GdkEventDND {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  GdkDragContext *context;

  guint32 time;
  gshort x_root, y_root;
};

/**
 * GdkEventTouchpadSwipe:
 * @type: the type of the event (%GDK_TOUCHPAD_SWIPE)
 * @window: the window which received the event
 * @send_event: %TRUE if the event was sent explicitly
 * @phase: the current phase of the gesture
 * @n_fingers: The number of fingers triggering the swipe
 * @time: the time of the event in milliseconds
 * @x: The X coordinate of the pointer
 * @y: The Y coordinate of the pointer
 * @dx: Movement delta in the X axis of the swipe focal point
 * @dy: Movement delta in the Y axis of the swipe focal point
 * @x_root: The X coordinate of the pointer, relative to the
 *   root of the screen.
 * @y_root: The Y coordinate of the pointer, relative to the
 *   root of the screen.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 *
 * Generated during touchpad swipe gestures.
 */
struct _GdkEventTouchpadSwipe {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  gint8 phase;
  gint8 n_fingers;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble dx;
  gdouble dy;
  gdouble x_root, y_root;
  guint state;
};

/**
 * GdkEventTouchpadPinch:
 * @type: the type of the event (%GDK_TOUCHPAD_PINCH)
 * @window: the window which received the event
 * @send_event: %TRUE if the event was sent explicitly
 * @phase: the current phase of the gesture
 * @n_fingers: The number of fingers triggering the pinch
 * @time: the time of the event in milliseconds
 * @x: The X coordinate of the pointer
 * @y: The Y coordinate of the pointer
 * @dx: Movement delta in the X axis of the swipe focal point
 * @dy: Movement delta in the Y axis of the swipe focal point
 * @angle_delta: The angle change in radians, negative angles
 *   denote counter-clockwise movements
 * @scale: The current scale, relative to that at the time of
 *   the corresponding %GDK_TOUCHPAD_GESTURE_PHASE_BEGIN event
 * @x_root: The X coordinate of the pointer, relative to the
 *   root of the screen.
 * @y_root: The Y coordinate of the pointer, relative to the
 *   root of the screen.
 * @state: (type GdkModifierType): a bit-mask representing the state of
 *   the modifier keys (e.g. Control, Shift and Alt) and the pointer
 *   buttons. See #GdkModifierType.
 *
 * Generated during touchpad swipe gestures.
 */
struct _GdkEventTouchpadPinch {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  gint8 phase;
  gint8 n_fingers;
  guint32 time;
  gdouble x;
  gdouble y;
  gdouble dx;
  gdouble dy;
  gdouble angle_delta;
  gdouble scale;
  gdouble x_root, y_root;
  guint state;
};

/**
 * GdkEventPadButton:
 * @type: the type of the event (%GDK_PAD_BUTTON_PRESS or %GDK_PAD_BUTTON_RELEASE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @group: the pad group the button belongs to. A %GDK_SOURCE_TABLET_PAD device
 *   may have one or more groups containing a set of buttons/rings/strips each.
 * @button: The pad button that was pressed.
 * @mode: The current mode of @group. Different groups in a %GDK_SOURCE_TABLET_PAD
 *   device may have different current modes.
 *
 * Generated during %GDK_SOURCE_TABLET_PAD button presses and releases.
 *
 * Since: 3.22
 */
struct _GdkEventPadButton {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  guint group;
  guint button;
  guint mode;
};

/**
 * GdkEventPadAxis:
 * @type: the type of the event (%GDK_PAD_RING or %GDK_PAD_STRIP).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @group: the pad group the ring/strip belongs to. A %GDK_SOURCE_TABLET_PAD
 *   device may have one or more groups containing a set of buttons/rings/strips
 *   each.
 * @index: number of strip/ring that was interacted. This number is 0-indexed.
 * @mode: The current mode of @group. Different groups in a %GDK_SOURCE_TABLET_PAD
 *   device may have different current modes.
 * @value: The current value for the given axis.
 *
 * Generated during %GDK_SOURCE_TABLET_PAD interaction with tactile sensors.
 *
 * Since: 3.22
 */
struct _GdkEventPadAxis {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  guint group;
  guint index;
  guint mode;
  gdouble value;
};

/**
 * GdkEventPadGroupMode:
 * @type: the type of the event (%GDK_PAD_GROUP_MODE).
 * @window: the window which received the event.
 * @send_event: %TRUE if the event was sent explicitly.
 * @time: the time of the event in milliseconds.
 * @group: the pad group that is switching mode. A %GDK_SOURCE_TABLET_PAD
 *   device may have one or more groups containing a set of buttons/rings/strips
 *   each.
 * @mode: The new mode of @group. Different groups in a %GDK_SOURCE_TABLET_PAD
 *   device may have different current modes.
 *
 * Generated during %GDK_SOURCE_TABLET_PAD mode switches in a group.
 *
 * Since: 3.22
 */
struct _GdkEventPadGroupMode {
  GdkEventType type;
  GdkWindow *window;
  gint8 send_event;
  guint32 time;
  guint group;
  guint mode;
};

/**
 * GdkEvent:
 * @type: the #GdkEventType
 * @any: a #GdkEventAny
 * @expose: a #GdkEventExpose
 * @visibility: a #GdkEventVisibility
 * @motion: a #GdkEventMotion
 * @button: a #GdkEventButton
 * @touch: a #GdkEventTouch
 * @scroll: a #GdkEventScroll
 * @key: a #GdkEventKey
 * @crossing: a #GdkEventCrossing
 * @focus_change: a #GdkEventFocus
 * @configure: a #GdkEventConfigure
 * @property: a #GdkEventProperty
 * @selection: a #GdkEventSelection
 * @owner_change: a #GdkEventOwnerChange
 * @proximity: a #GdkEventProximity
 * @dnd: a #GdkEventDND
 * @window_state: a #GdkEventWindowState
 * @setting: a #GdkEventSetting
 * @grab_broken: a #GdkEventGrabBroken
 * @touchpad_swipe: a #GdkEventTouchpadSwipe
 * @touchpad_pinch: a #GdkEventTouchpadPinch
 * @pad_button: a #GdkEventPadButton
 * @pad_axis: a #GdkEventPadAxis
 * @pad_group_mode: a #GdkEventPadGroupMode
 *
 * A #GdkEvent contains a union of all of the event types,
 * and allows access to the data fields in a number of ways.
 *
 * The event type is always the first field in all of the event types, and
 * can always be accessed with the following code, no matter what type of
 * event it is:
 * |[<!-- language="C" -->
 *   GdkEvent *event;
 *   GdkEventType type;
 *
 *   type = event->type;
 * ]|
 *
 * To access other fields of the event, the pointer to the event
 * can be cast to the appropriate event type, or the union member
 * name can be used. For example if the event type is %GDK_BUTTON_PRESS
 * then the x coordinate of the button press can be accessed with:
 * |[<!-- language="C" -->
 *   GdkEvent *event;
 *   gdouble x;
 *
 *   x = ((GdkEventButton*)event)->x;
 * ]|
 * or:
 * |[<!-- language="C" -->
 *   GdkEvent *event;
 *   gdouble x;
 *
 *   x = event->button.x;
 * ]|
 */
union _GdkEvent
{
  GdkEventType		    type;
  GdkEventAny		    any;
  GdkEventExpose	    expose;
  GdkEventVisibility	    visibility;
  GdkEventMotion	    motion;
  GdkEventButton	    button;
  GdkEventTouch             touch;
  GdkEventScroll            scroll;
  GdkEventKey		    key;
  GdkEventCrossing	    crossing;
  GdkEventFocus		    focus_change;
  GdkEventConfigure	    configure;
  GdkEventProperty	    property;
  GdkEventSelection	    selection;
  GdkEventOwnerChange  	    owner_change;
  GdkEventProximity	    proximity;
  GdkEventDND               dnd;
  GdkEventWindowState       window_state;
  GdkEventSetting           setting;
  GdkEventGrabBroken        grab_broken;
  GdkEventTouchpadSwipe     touchpad_swipe;
  GdkEventTouchpadPinch     touchpad_pinch;
  GdkEventPadButton         pad_button;
  GdkEventPadAxis           pad_axis;
  GdkEventPadGroupMode      pad_group_mode;
};
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

GDK_AVAILABLE_IN_ALL
GdkEvent *              gdk_event_ref                   (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
void                    gdk_event_unref                 (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkEventType            gdk_event_get_event_type        (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkSurface *            gdk_event_get_surface           (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkSeat *               gdk_event_get_seat              (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkDevice *             gdk_event_get_device            (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkDeviceTool *         gdk_event_get_device_tool       (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
guint32                 gdk_event_get_time              (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkDisplay *            gdk_event_get_display           (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkEventSequence *      gdk_event_get_event_sequence    (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GdkModifierType         gdk_event_get_modifier_state    (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
gboolean                gdk_event_get_position          (GdkEvent  *event,
					                 double	   *x,
					                 double	   *y);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_event_get_axes              (GdkEvent  *event,
                                                         double   **axes,
                                                         guint     *n_axes);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_event_get_axis              (GdkEvent   *event,
                                                         GdkAxisUse  axis_use,
                                                         double     *value);
GDK_AVAILABLE_IN_ALL
GdkTimeCoord *          gdk_event_get_history           (GdkEvent *event,
                                                         guint    *out_n_coords);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_event_get_pointer_emulated (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GType                   gdk_button_event_get_type       (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
guint                   gdk_button_event_get_button     (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_scroll_event_get_type       (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GdkScrollDirection      gdk_scroll_event_get_direction  (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
void                    gdk_scroll_event_get_deltas     (GdkEvent *event,
                                                         double   *delta_x,
                                                         double   *delta_y);
GDK_AVAILABLE_IN_4_8
GdkScrollUnit           gdk_scroll_event_get_unit       (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
gboolean                gdk_scroll_event_is_stop        (GdkEvent *event);
GDK_AVAILABLE_IN_4_20
GdkScrollRelativeDirection
                        gdk_scroll_event_get_relative_direction (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_key_event_get_type          (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
guint                   gdk_key_event_get_keyval        (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
guint                   gdk_key_event_get_keycode       (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GdkModifierType         gdk_key_event_get_consumed_modifiers (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
guint                   gdk_key_event_get_layout        (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
guint                   gdk_key_event_get_level         (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_key_event_is_modifier       (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_focus_event_get_type        (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
gboolean                gdk_focus_event_get_in          (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_touch_event_get_type        (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
gboolean                gdk_touch_event_get_emulating_pointer (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_crossing_event_get_type     (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GdkCrossingMode         gdk_crossing_event_get_mode     (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GdkNotifyType           gdk_crossing_event_get_detail   (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_crossing_event_get_focus    (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_touchpad_event_get_type     (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GdkTouchpadGesturePhase
                        gdk_touchpad_event_get_gesture_phase (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
guint                   gdk_touchpad_event_get_n_fingers     (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
void                    gdk_touchpad_event_get_deltas        (GdkEvent *event,
                                                              double   *dx,
                                                              double   *dy);
GDK_AVAILABLE_IN_ALL
double                  gdk_touchpad_event_get_pinch_angle_delta (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
double                  gdk_touchpad_event_get_pinch_scale       (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_pad_event_get_type          (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
guint                   gdk_pad_event_get_button        (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
void                    gdk_pad_event_get_axis_value    (GdkEvent *event,
                                                         guint    *index,
                                                         double   *value);
GDK_AVAILABLE_IN_ALL
void                    gdk_pad_event_get_group_mode    (GdkEvent *event,
                                                         guint    *group,
                                                         guint    *mode);
GDK_AVAILABLE_IN_ALL
GType                   gdk_dnd_event_get_type          (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GdkDrop *               gdk_dnd_event_get_drop          (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
GType                   gdk_grab_broken_event_get_type  (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GdkSurface *            gdk_grab_broken_event_get_grab_surface (GdkEvent *event);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_grab_broken_event_get_implicit     (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
GType                   gdk_motion_event_get_type       (void) G_GNUC_CONST;

GDK_AVAILABLE_IN_ALL
GType                   gdk_delete_event_get_type       (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GType                   gdk_proximity_event_get_type    (void) G_GNUC_CONST;

GDK_AVAILABLE_IN_ALL
gboolean                gdk_event_triggers_context_menu (GdkEvent *event);

GDK_AVAILABLE_IN_ALL
gboolean                gdk_events_get_distance         (GdkEvent *event1,
                                                         GdkEvent *event2,
                                                         double   *distance);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_events_get_angle            (GdkEvent *event1,
                                                         GdkEvent *event2,
                                                         double   *angle);
GDK_AVAILABLE_IN_ALL
gboolean                gdk_events_get_center           (GdkEvent *event1,
                                                         GdkEvent *event2,
                                                         double   *x,
                                                         double   *y);

/**
 * GdkKeyMatch:
 * @GDK_KEY_MATCH_NONE: The key event does not match
 * @GDK_KEY_MATCH_PARTIAL: The key event matches if keyboard state
 *   (specifically, the currently active group) is ignored
 * @GDK_KEY_MATCH_EXACT: The key event matches
 *
 * Describes how well an event matches a given keyval and modifiers.
 *
 * `GdkKeyMatch` values are returned by [method@Gdk.KeyEvent.matches].
 */
typedef enum {
  GDK_KEY_MATCH_NONE,
  GDK_KEY_MATCH_PARTIAL,
  GDK_KEY_MATCH_EXACT
} GdkKeyMatch;

GDK_AVAILABLE_IN_ALL
GdkKeyMatch            gdk_key_event_matches (GdkEvent        *event,
                                              guint            keyval,
                                              GdkModifierType  modifiers);

GDK_AVAILABLE_IN_ALL
gboolean               gdk_key_event_get_match (GdkEvent        *event,
                                                guint           *keyval,
                                                GdkModifierType *modifiers);


G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkEvent, gdk_event_unref)

G_END_DECLS

