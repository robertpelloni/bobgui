/* bobgui/modules/package/bobguipackage.h */
#ifndef BOBGUI_PACKAGE_H
#define BOBGUI_PACKAGE_H

#include <glib-object.h>

G_BEGIN_DECLS

/* Extension & Module Manager (Better than manual DLL/SO loading) */
#define BOBGUI_TYPE_PACKAGE_MANAGER (bobgui_package_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiPackageManager, bobgui_package_manager, BOBGUI, PACKAGE_MANAGER, GObject)

BobguiPackageManager * bobgui_package_manager_get_default (void);

/* Remote Package Discovery (Unmatched Parity) */
void bobgui_package_manager_refresh (BobguiPackageManager *self, GAsyncReadyCallback callback);
void bobgui_package_manager_install (BobguiPackageManager *self, const char *pkg_id, GAsyncReadyCallback callback);

/* Dependency Resolution and Verification (Using BobguiSecurity) */
gboolean bobgui_package_manager_verify_signature (BobguiPackageManager *self, const char *pkg_id);

/* Runtime Activation (No restart required) */
void bobgui_package_manager_activate (BobguiPackageManager *self, const char *pkg_id);
void bobgui_package_manager_deactivate (BobguiPackageManager *self, const char *pkg_id);

G_END_DECLS

#endif /* BOBGUI_PACKAGE_H */
