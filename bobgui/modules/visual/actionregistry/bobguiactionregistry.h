#ifndef BOBGUI_ACTION_REGISTRY_H
#define BOBGUI_ACTION_REGISTRY_H

#include <glib-object.h>

G_BEGIN_DECLS

typedef void (*BobguiActionRegistryFunc) (const char *action_id,
                                          gpointer    user_data);

typedef struct _BobguiCommandPalette BobguiCommandPalette;

#define BOBGUI_TYPE_ACTION_REGISTRY (bobgui_action_registry_get_type ())
G_DECLARE_FINAL_TYPE (BobguiActionRegistry, bobgui_action_registry, BOBGUI, ACTION_REGISTRY, GObject)

BobguiActionRegistry * bobgui_action_registry_new              (void);
void                   bobgui_action_registry_add              (BobguiActionRegistry     *self,
                                                               const char               *action_id,
                                                               const char               *title,
                                                               const char               *subtitle,
                                                               BobguiActionRegistryFunc  callback,
                                                               gpointer                  user_data);
void                   bobgui_action_registry_activate         (BobguiActionRegistry     *self,
                                                               const char               *action_id);
void                   bobgui_action_registry_populate_palette (BobguiActionRegistry     *self,
                                                               BobguiCommandPalette     *palette);

G_END_DECLS

#endif
