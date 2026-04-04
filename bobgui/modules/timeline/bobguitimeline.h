/* bobgui/modules/timeline/bobguitimeline.h */
#ifndef BOBGUI_TIMELINE_H
#define BOBGUI_TIMELINE_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Keyframe-based Animation Engine (Better than standard Tweens) */
#define BOBGUI_TYPE_TIMELINE (bobgui_timeline_get_type ())
G_DECLARE_FINAL_TYPE (BobguiTimeline, bobgui_timeline, BOBGUI, TIMELINE, GObject)

BobguiTimeline * bobgui_timeline_new (void);

/* Track and Keyframe API (Non-linear Editor style) */
void bobgui_timeline_add_track (BobguiTimeline *self, 
                               GObject *target, 
                               const char *property);

void bobgui_timeline_set_keyframe (BobguiTimeline *self, 
                                  GObject *target, 
                                  const char *property, 
                                  double time, 
                                  GVariant *value,
                                  const char *easing);

/* Playback Control (Superior to CSS transitions) */
void bobgui_timeline_play (BobguiTimeline *self);
void bobgui_timeline_pause (BobguiTimeline *self);
void bobgui_timeline_seek (BobguiTimeline *self, double time);

G_END_DECLS

#endif /* BOBGUI_TIMELINE_H */
