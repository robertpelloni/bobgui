/* bobgui/modules/plugin/bobguiplugin.h */
#ifndef BOBGUI_PLUGIN_H
#define BOBGUI_PLUGIN_H

#include <gmodule.h>
#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Plugin Architecture (Better than JUCE / Qt Plugins) */
typedef struct _BobguiPlugin BobguiPlugin;

/* Plugin Metadata and Capabilities */
typedef struct {
  const char *name;
  const char *version;
  const char *description;
  const char *author;
} BobguiPluginInfo;

/* Universal Plugin API (Parity with JUCE / VST3) */
#define BOBGUI_TYPE_PLUGIN_MANAGER (bobgui_plugin_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiPluginManager, bobgui_plugin_manager, BOBGUI, PLUGIN_MANAGER, GObject)

BobguiPluginManager * bobgui_plugin_manager_new (const char *search_path);
void                   bobgui_plugin_manager_scan (BobguiPluginManager *self);

/* Dynamic Loading with Sandboxing and ABI verification */
BobguiPlugin * bobgui_plugin_manager_load (BobguiPluginManager *self, const char *plugin_id);
void            bobgui_plugin_manager_unload (BobguiPluginManager *self, BobguiPlugin *plugin);

G_END_DECLS

#endif /* BOBGUI_PLUGIN_H */
