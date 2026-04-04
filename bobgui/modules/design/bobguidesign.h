/* bobgui/modules/design/bobguidesign.h */
#ifndef BOBGUI_DESIGN_H
#define BOBGUI_DESIGN_H

#include <glib-object.h>
#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Design Token System (Better than standard CSS) */
typedef enum {
  BOBGUI_DESIGN_COLOR_PRIMARY,
  BOBGUI_DESIGN_COLOR_SECONDARY,
  BOBGUI_DESIGN_COLOR_BACKGROUND,
  BOBGUI_DESIGN_COLOR_SURFACE,
  BOBGUI_DESIGN_SPACING_SMALL,
  BOBGUI_DESIGN_SPACING_MEDIUM,
  BOBGUI_DESIGN_SPACING_LARGE,
  BOBGUI_DESIGN_FONT_HEADING,
  BOBGUI_DESIGN_FONT_BODY,
} BobguiDesignToken;

/* Design Theme (Automatic Dark/Light, and Accessibility) */
#define BOBGUI_TYPE_DESIGN_SYSTEM (bobgui_design_system_get_type ())
G_DECLARE_FINAL_TYPE (BobguiDesignSystem, bobgui_design_system, BOBGUI, DESIGN_SYSTEM, GObject)

BobguiDesignSystem * bobgui_design_system_get_default (void);
void                  bobgui_design_system_set_theme   (BobguiDesignSystem *self, const char *theme_name);

/* Dynamic Token Lookup (Better than manual CSS string concatenation) */
GdkRGBA * bobgui_design_token_get_color (BobguiDesignToken token);
int       bobgui_design_token_get_spacing (BobguiDesignToken token);

/* Superior: One-call application of Design Tokens to any widget */
void bobgui_widget_apply_token (BobguiWidget *w, BobguiDesignToken token, const char *property);

G_END_DECLS

#endif /* BOBGUI_DESIGN_H */
