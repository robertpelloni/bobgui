/* bobgui/modules/dock/bobguidock.h */
#ifndef BOBGUI_DOCK_H
#define BOBGUI_DOCK_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Advanced Docking System (Better than Dear ImGui / Qt Docking) */
#define BOBGUI_TYPE_DOCK_MANAGER (bobgui_dock_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiDockManager, bobgui_dock_manager, BOBGUI, DOCK_MANAGER, GObject)

BobguiDockManager * bobgui_dock_manager_new (BobguiWindow *main_window);

/* Docking Workspace API */
void bobgui_dock_manager_add_item (BobguiDockManager *self, 
                                  BobguiWidget *widget, 
                                  const char *title, 
                                  const char *target_area);

/* Multi-Viewport and Tab Tearing (Superior Parity) */
void bobgui_dock_manager_set_allow_tearing (BobguiDockManager *self, gboolean allow);
void bobgui_dock_manager_serialize_layout (BobguiDockManager *self, const char *path);
void bobgui_dock_manager_restore_layout (BobguiDockManager *self, const char *path);

/* High-level Dock Areas */
typedef enum {
  BOBGUI_DOCK_AREA_CENTER,
  BOBGUI_DOCK_AREA_LEFT,
  BOBGUI_DOCK_AREA_RIGHT,
  BOBGUI_DOCK_AREA_TOP,
  BOBGUI_DOCK_AREA_BOTTOM
} BobguiDockArea;

G_END_DECLS

#endif /* BOBGUI_DOCK_H */
