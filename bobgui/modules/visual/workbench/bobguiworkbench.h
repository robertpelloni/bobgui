#ifndef BOBGUI_WORKBENCH_H
#define BOBGUI_WORKBENCH_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

typedef struct _BobguiCommandPalette BobguiCommandPalette;

typedef void (*BobguiWorkbenchActionCallback) (BobguiButton *button,
                                               gpointer      user_data);
typedef void (*BobguiWorkbenchCommandCallback) (const char *command_id,
                                                gpointer    user_data);

#define BOBGUI_TYPE_WORKBENCH (bobgui_workbench_get_type ())
G_DECLARE_FINAL_TYPE (BobguiWorkbench, bobgui_workbench, BOBGUI, WORKBENCH, GObject)

BobguiWorkbench * bobgui_workbench_new               (BobguiApplication *application);
BobguiWindow    * bobgui_workbench_get_window        (BobguiWorkbench   *self);
BobguiWidget    * bobgui_workbench_get_content       (BobguiWorkbench   *self);

void             bobgui_workbench_set_title          (BobguiWorkbench   *self,
                                                      const char        *title);
void             bobgui_workbench_set_central        (BobguiWorkbench   *self,
                                                      BobguiWidget      *child);
void             bobgui_workbench_set_left_sidebar   (BobguiWorkbench   *self,
                                                      BobguiWidget      *child);
void             bobgui_workbench_set_right_sidebar  (BobguiWorkbench   *self,
                                                      BobguiWidget      *child);
void             bobgui_workbench_set_status         (BobguiWorkbench   *self,
                                                      const char        *message);
void             bobgui_workbench_add_header_action  (BobguiWorkbench   *self,
                                                      const char        *label,
                                                      BobguiWorkbenchActionCallback callback,
                                                      gpointer           user_data);
void             bobgui_workbench_set_command_palette(BobguiWorkbench   *self,
                                                      BobguiCommandPalette *palette);
void             bobgui_workbench_add_command        (BobguiWorkbench   *self,
                                                      const char        *command_id,
                                                      const char        *title,
                                                      const char        *subtitle,
                                                      BobguiWorkbenchCommandCallback callback,
                                                      gpointer           user_data);
void             bobgui_workbench_present            (BobguiWorkbench   *self);

G_END_DECLS

#endif
