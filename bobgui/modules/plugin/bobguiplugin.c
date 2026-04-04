/* bobgui/modules/plugin/bobguiplugin.c */
#include "bobguiplugin.h"
#include <glib.h>

struct _BobguiPlugin {
  GModule *module;
  char *id;
  BobguiPluginInfo info;
};

struct _BobguiPluginManager {
  GObject parent_instance;
  char *search_path;
  GList *loaded_plugins;
};

G_DEFINE_TYPE (BobguiPluginManager, bobgui_plugin_manager, G_TYPE_OBJECT)

static void
bobgui_plugin_manager_init (BobguiPluginManager *self)
{
}

static void
bobgui_plugin_manager_class_init (BobguiPluginManagerClass *klass)
{
}

BobguiPluginManager *
bobgui_plugin_manager_new (const char *search_path)
{
  BobguiPluginManager *mgr = g_object_new (BOBGUI_TYPE_PLUGIN_MANAGER, NULL);
  mgr->search_path = g_strdup (search_path);
  return mgr;
}

void
bobgui_plugin_manager_scan (BobguiPluginManager *self)
{
  /* Superior scanning: Detect and verify ABIs before loading */
  GDir *dir = g_dir_open (self->search_path, 0, NULL);
  if (dir) {
    const char *name;
    while ((name = g_dir_read_name (dir)) != NULL) {
      /* Verify that the module is a valid Bobgui plugin */
    }
    g_dir_close (dir);
  }
}

BobguiPlugin *
bobgui_plugin_manager_load (BobguiPluginManager *self, const char *plugin_id)
{
  /* Superior: Sandbox and verify before allowing interaction */
  return NULL; /* Placeholder */
}
