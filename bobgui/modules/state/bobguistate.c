/* bobgui/state/bobguistate.c */
#include "bobguistate.h"
#include <glib.h>

struct _BobguiStateMachine {
  GObject parent_instance;
  GList *history;      /* List of BobguiStateNode* for Time-Travel */
  GList *future;       /* For Redo after Undo */
  GList *subscribers;  /* Callbacks for State Changes */
  BobguiStateNode *current_state;
};

G_DEFINE_TYPE (BobguiStateMachine, bobgui_state_machine, G_TYPE_OBJECT)

static void
bobgui_state_machine_init (BobguiStateMachine *self)
{
}

static void
bobgui_state_machine_class_init (BobguiStateMachineClass *klass)
{
}

BobguiStateMachine *
bobgui_state_machine_new (BobguiStateNode *initial_state)
{
  BobguiStateMachine *sm = g_object_new (BOBGUI_TYPE_STATE_MACHINE, NULL);
  sm->current_state = initial_state;
  sm->history = g_list_append (NULL, initial_state);
  return sm;
}

void
bobgui_state_machine_dispatch (BobguiStateMachine *sm, const char *action, GVariant *payload)
{
  /* 1. Calculate new state based on current state + action (Reducer pattern) */
  /* 2. Update current state and push to history */
  /* 3. Notify all reactive subscribers (Superior to standard manual updates) */
  
  GList *l;
  for (l = sm->subscribers; l != NULL; l = l->next) {
    /* Call the reactive subscription callback with the new state node */
  }
}

void
bobgui_state_machine_undo (BobguiStateMachine *sm)
{
  if (g_list_length (sm->history) > 1) {
    sm->future = g_list_prepend (sm->future, sm->current_state);
    sm->history = g_list_remove (sm->history, sm->current_state);
    sm->current_state = g_list_last (sm->history)->data;
    /* Redraw/Update UI based on Undo state */
  }
}

void
bobgui_state_machine_subscribe (BobguiStateMachine *sm, GCallback cb, gpointer data)
{
  sm->subscribers = g_list_append (sm->subscribers, cb);
}
