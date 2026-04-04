/* bobgui/modules/shader/bobguishader.h */
#ifndef BOBGUI_SHADER_H
#define BOBGUI_SHADER_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Shader Effects Engine (Better than JavaFX Effects / QtShaderTools) */
#define BOBGUI_TYPE_EFFECT_SHADER (bobgui_effect_shader_get_type ())
G_DECLARE_FINAL_TYPE (BobguiEffectShader, bobgui_effect_shader, BOBGUI, EFFECT_SHADER, GObject)

BobguiEffectShader * bobgui_effect_shader_new_from_source (const char *source);

/* Parameter Binding (Reactive integration with BobguiData) */
void bobgui_effect_shader_set_float (BobguiEffectShader *self, const char *name, float value);
void bobgui_effect_shader_set_color (BobguiEffectShader *self, const char *name, GdkRGBA *color);

/* Application to UI (Any widget can have custom GPU effects) */
void bobgui_widget_set_effect (BobguiWidget *widget, BobguiEffectShader *shader);

/* Built-in High-End Effects (Superior Parity) */
void bobgui_widget_enable_bloom (BobguiWidget *widget, float intensity);
void bobgui_widget_enable_glass (BobguiWidget *widget, float blur_radius, float opacity);

G_END_DECLS

#endif /* BOBGUI_SHADER_H */
