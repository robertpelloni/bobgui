/* bobgui/imgui/bobguiimgui.h */
#ifndef BOBGUI_IMGUI_H
#define BOBGUI_IMGUI_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

typedef struct _BobguiImguiContext BobguiImguiContext;

BobguiImguiContext * bobgui_imgui_context_new    (void);
void                 bobgui_imgui_context_free   (BobguiImguiContext *context);

void                 bobgui_imgui_new_frame      (BobguiImguiContext *context);
void                 bobgui_imgui_render         (BobguiImguiContext *context, BobguiWidget *parent);

/* Immediate Mode Widgets (IMGUI Parity) */
gboolean             bobgui_imgui_button         (BobguiImguiContext *context, const char *label);
void                 bobgui_imgui_text           (BobguiImguiContext *context, const char *format, ...);
gboolean             bobgui_imgui_slider_float   (BobguiImguiContext *context, const char *label, float *v, float v_min, float v_max);
gboolean             bobgui_imgui_checkbox       (BobguiImguiContext *context, const char *label, gboolean *v);

G_END_DECLS

#endif /* BOBGUI_IMGUI_H */
