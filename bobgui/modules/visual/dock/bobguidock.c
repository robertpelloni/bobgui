#include "bobguidock.h"
G_DEFINE_TYPE (BobguiDockManager, bobgui_dock_manager, G_TYPE_OBJECT)
static void bobgui_dock_manager_init (BobguiDockManager *s) {}
static void bobgui_dock_manager_class_init (BobguiDockManagerClass *k) {}
BobguiDockManager * bobgui_dock_manager_new (BobguiWindow *w) { return g_object_new (BOBGUI_TYPE_DOCK_MANAGER, NULL); }
