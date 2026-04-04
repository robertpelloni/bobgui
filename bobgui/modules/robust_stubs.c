/* bobgui/modules/spatial/bobguispatial.c */
#include "bobguispatial.h"
G_DEFINE_TYPE (BobguiSpatialContext, bobgui_spatial_context, G_TYPE_OBJECT)
static void bobgui_spatial_context_init (BobguiSpatialContext *self) {}
static void bobgui_spatial_context_class_init (BobguiSpatialContextClass *klass) {}
BobguiSpatialContext * bobgui_spatial_context_new (const char *n) { return g_object_new (BOBGUI_TYPE_SPATIAL_CONTEXT, NULL); }

/* bobgui/modules/security/bobguisecurity.c */
#include "bobguisecurity.h"
G_DEFINE_TYPE (BobguiSecureEntry, bobgui_secure_entry, G_TYPE_OBJECT)
static void bobgui_secure_entry_init (BobguiSecureEntry *self) {}
static void bobgui_secure_entry_class_init (BobguiSecureEntryClass *klass) {}
BobguiSecureEntry * bobgui_secure_entry_new (void) { return g_object_new (BOBGUI_TYPE_SECURE_ENTRY, NULL); }

/* bobgui/modules/script/bobguiscript.c */
#include "bobguiscript.h"
G_DEFINE_TYPE (BobguiScriptContext, bobgui_script_context, G_TYPE_OBJECT)
static void bobgui_script_context_init (BobguiScriptContext *self) {}
static void bobgui_script_context_class_init (BobguiScriptContextClass *klass) {}
BobguiScriptContext * bobgui_script_context_new (const char *t) { return g_object_new (BOBGUI_TYPE_SCRIPT_CONTEXT, NULL); }

/* bobgui/modules/sync/bobguisync.c */
#include "bobguisync.h"
G_DEFINE_TYPE (BobguiSyncEngine, bobgui_sync_engine, G_TYPE_OBJECT)
static void bobgui_sync_engine_init (BobguiSyncEngine *self) {}
static void bobgui_sync_engine_class_init (BobguiSyncEngineClass *klass) {}
BobguiSyncEngine * bobgui_sync_engine_new (BobguiStateMachine *sm) { return g_object_new (BOBGUI_TYPE_SYNC_ENGINE, NULL); }

/* bobgui/modules/test/bobguitest.c */
#include "bobguitest.h"
G_DEFINE_TYPE (BobguiTestRunner, bobgui_test_runner, G_TYPE_OBJECT)
static void bobgui_test_runner_init (BobguiTestRunner *self) {}
static void bobgui_test_runner_class_init (BobguiTestRunnerClass *klass) {}
BobguiTestRunner * bobgui_test_runner_new (BobguiWidget *r) { return g_object_new (BOBGUI_TYPE_TEST_RUNNER, NULL); }

/* bobgui/modules/timeline/bobguitimeline.c */
#include "bobguitimeline.h"
G_DEFINE_TYPE (BobguiTimeline, bobgui_timeline, G_TYPE_OBJECT)
static void bobgui_timeline_init (BobguiTimeline *self) {}
static void bobgui_timeline_class_init (BobguiTimelineClass *klass) {}
BobguiTimeline * bobgui_timeline_new (void) { return g_object_new (BOBGUI_TYPE_TIMELINE, NULL); }

/* bobgui/modules/cloud/bobguicloud.c */
#include "bobguicloud.h"
G_DEFINE_TYPE (BobguiCloudContext, bobgui_cloud_context, G_TYPE_OBJECT)
static void bobgui_cloud_context_init (BobguiCloudContext *self) {}
static void bobgui_cloud_context_class_init (BobguiCloudContextClass *klass) {}
BobguiCloudContext * bobgui_cloud_context_new (const char *u, const char *k) { return g_object_new (BOBGUI_TYPE_CLOUD_CONTEXT, NULL); }

/* bobgui/modules/vfs/bobguivfs.c */
#include "bobguivfs.h"
G_DEFINE_TYPE (BobguiVFS, bobgui_vfs, G_TYPE_OBJECT)
static void bobgui_vfs_init (BobguiVFS *self) {}
static void bobgui_vfs_class_init (BobguiVFSClass *klass) {}
BobguiVFS * bobgui_vfs_get_default (void) { return g_object_new (BOBGUI_TYPE_VFS, NULL); }
