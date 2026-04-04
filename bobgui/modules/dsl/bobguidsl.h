/* bobgui/modules/dsl/bobguidsl.h */
#ifndef BOBGUI_DSL_H
#define BOBGUI_DSL_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* DSL Macros for Fluent Builder (SwiftUI/Flutter-style) */
#define BOBGUI_VERTICAL_BOX(...) bobgui_dsl_box(BOBGUI_ORIENTATION_VERTICAL, __VA_ARGS__, NULL)
#define BOBGUI_HORIZONTAL_BOX(...) bobgui_dsl_box(BOBGUI_ORIENTATION_HORIZONTAL, __VA_ARGS__, NULL)
#define BOBGUI_BUTTON(label, callback) bobgui_dsl_button(label, callback)
#define BOBGUI_LABEL(text) bobgui_dsl_label(text)
#define BOBGUI_PADDING(widget, p) bobgui_dsl_set_padding(widget, p)

/* DSL Internal Builder functions (Superior to verbose GObject calls) */
BobguiWidget* bobgui_dsl_box    (BobguiOrientation orientation, ...);
BobguiWidget* bobgui_dsl_button (const char *label, GCallback callback);
BobguiWidget* bobgui_dsl_label  (const char *text);
BobguiWidget* bobgui_dsl_set_padding (BobguiWidget *w, int padding);

/* Example Usage:
   BobguiWidget *ui = BOBGUI_VERTICAL_BOX(
       BOBGUI_LABEL("Welcome to Bobgui"),
       BOBGUI_BUTTON("Click Me", G_CALLBACK(on_click)),
       BOBGUI_HORIZONTAL_BOX(
           BOBGUI_BUTTON("Left", NULL),
           BOBGUI_BUTTON("Right", NULL)
       )
   );
*/

G_END_DECLS

#endif /* BOBGUI_DSL_H */
