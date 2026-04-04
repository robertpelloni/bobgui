/* bobgui/modules/script/bobguiscript.h */
#ifndef BOBGUI_SCRIPT_H
#define BOBGUI_SCRIPT_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Scripting Engine (Better than QML / JavaScript) */
#define BOBGUI_TYPE_SCRIPT_CONTEXT (bobgui_script_context_get_type ())
G_DECLARE_FINAL_TYPE (BobguiScriptContext, bobgui_script_context, BOBGUI, SCRIPT_CONTEXT, GObject)

BobguiScriptContext * bobgui_script_context_new (const char *engine_type);

/* Load and Execute Logic (Better than standard interpreted JS) */
void bobgui_script_run (BobguiScriptContext *ctx, const char *script_source);
void bobgui_script_load_file (BobguiScriptContext *ctx, const char *path);

/* Direct GObject/Widget Bridge (Superior Parity with JavaFX) */
void bobgui_script_expose_widget (BobguiScriptContext *ctx, BobguiWidget *widget, const char *name);

/* Reactive Callbacks (Better than standard Signal/Slot) */
void bobgui_script_set_handler (BobguiScriptContext *ctx, 
                               BobguiWidget *widget, 
                               const char *signal, 
                               const char *script_func);

G_END_DECLS

#endif /* BOBGUI_SCRIPT_H */
