#ifndef BOBGUI_DOCK_H
#define BOBGUI_DOCK_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

#define BOBGUI_TYPE_DOCK_MANAGER (bobgui_dock_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiDockManager, bobgui_dock_manager, BOBGUI, DOCK_MANAGER, GObject)

BobguiDockManager * bobgui_dock_manager_new (BobguiWindow *main_window);

G_END_DECLS

#endif
