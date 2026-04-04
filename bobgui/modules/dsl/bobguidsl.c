/* bobgui/modules/dsl/bobguidsl.c */
#include "bobguidsl.h"
#include <stdarg.h>

BobguiWidget *
bobgui_dsl_box (BobguiOrientation orientation, ...)
{
  BobguiBox *box = BOBGUI_BOX (bobgui_box_new (orientation, 0));
  va_list args;
  va_start (args, orientation);
  
  BobguiWidget *child;
  while ((child = va_arg (args, BobguiWidget *)) != NULL) {
    bobgui_box_append (box, child);
  }
  
  va_end (args);
  return BOBGUI_WIDGET (box);
}

BobguiWidget *
bobgui_dsl_button (const char *label, GCallback callback)
{
  BobguiWidget *btn = bobgui_button_new_with_label (label);
  if (callback) {
    g_signal_connect (btn, "clicked", callback, NULL);
  }
  return btn;
}

BobguiWidget *
bobgui_dsl_label (const char *text)
{
  return bobgui_label_new (text);
}

BobguiWidget *
bobgui_dsl_set_padding (BobguiWidget *w, int padding)
{
  bobgui_widget_set_margin_start (w, padding);
  bobgui_widget_set_margin_end (w, padding);
  bobgui_widget_set_margin_top (w, padding);
  bobgui_widget_set_margin_bottom (w, padding);
  return w;
}
