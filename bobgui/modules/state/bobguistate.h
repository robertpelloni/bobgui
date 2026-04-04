/* bobgui/state/bobguistate.h */
#ifndef BOBGUI_STATE_H
#define BOBGUI_STATE_H

#include <glib-object.h>

G_BEGIN_DECLS

/* Immutable State Node */
typedef struct _BobguiStateNode BobguiStateNode;

/* State Machine (Redux-style) for 1:1 Parity and Superiority */
#define BOBGUI_TYPE_STATE_MACHINE (bobgui_state_machine_get_type ())
G_DECLARE_FINAL_TYPE (BobguiStateMachine, bobgui_state_machine, BOBGUI, STATE_MACHINE, GObject)

BobguiStateMachine * bobgui_state_machine_new (BobguiStateNode *initial_state);

/* Atomic State Transitions */
void bobgui_state_machine_dispatch (BobguiStateMachine *self, const char *action_type, GVariant *payload);

/* Time-Travel (Qt/JUCE don't have this built-in) */
void bobgui_state_machine_undo (BobguiStateMachine *self);
void bobgui_state_machine_redo (BobguiStateMachine *self);

/* Reactive Subscription */
void bobgui_state_machine_subscribe (BobguiStateMachine *self, 
                                     GCallback callback, 
                                     gpointer user_data);

G_END_DECLS

#endif /* BOBGUI_STATE_H */
