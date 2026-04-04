/* bobgui/modules/live/bobguilive.h */
#ifndef BOBGUI_LIVE_H
#define BOBGUI_LIVE_H

#include <gmodule.h>
#include <bobgui/bobgui.h>

G_BEGIN_DECLS

typedef struct _BobguiLiveContext BobguiLiveContext;

/* Hot-swap callback for UI rebuild */
typedef BobguiWidget* (*BobguiLiveRebuildFunc) (gpointer state);

BobguiLiveContext * bobgui_live_context_new      (const char *module_path);
void                 bobgui_live_watch_and_swap (BobguiLiveContext *ctx, 
                                                BobguiWidget **ui_root, 
                                                gpointer state);

/* State Persistence across reloads (Unmatched feature) */
void bobgui_live_persist_state (BobguiLiveContext *ctx, gpointer state, size_t size);
void bobgui_live_restore_state (BobguiLiveContext *ctx, gpointer state, size_t size);

G_END_DECLS

#endif /* BOBGUI_LIVE_H */
