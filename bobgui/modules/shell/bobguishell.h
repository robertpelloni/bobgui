/* bobgui/modules/shell/bobguishell.h */
#ifndef BOBGUI_SHELL_H
#define BOBGUI_SHELL_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* System Mastery (Better than Qt System Tray / Taskbar) */
#define BOBGUI_TYPE_SHELL_MANAGER (bobgui_shell_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiShellManager, bobgui_shell_manager, BOBGUI, SHELL_MANAGER, GObject)

BobguiShellManager * bobgui_shell_manager_get_default (void);

/* System Tray and Status Icons (Superior Parity) */
void bobgui_shell_set_tray_icon (BobguiShellManager *self, GdkPaintable *icon, const char *tooltip);
void bobgui_shell_set_tray_menu (BobguiShellManager *self, GMenuModel *menu);

/* Taskbar and Dock Integration (Better than standard toolkits) */
void bobgui_shell_set_progress (BobguiShellManager *self, double fraction);
void bobgui_shell_set_badge (BobguiShellManager *self, const char *text);

/* Native Notifications (Unified across Win/Mac/Linux) */
void bobgui_shell_notify (BobguiShellManager *self, 
                         const char *title, 
                         const char *body, 
                         GdkPaintable *icon);

/* Global Menus (Superior Parity with macOS) */
void bobgui_shell_set_global_menu (BobguiShellManager *self, GMenuModel *menu);

G_END_DECLS

#endif /* BOBGUI_SHELL_H */
