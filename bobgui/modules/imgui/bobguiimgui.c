/* bobgui/imgui/bobguiimgui.c */
#include "bobguiimgui.h"
#include <glib.h>
#include <string.h>

struct _BobguiImguiContext {
  GHashTable *widgets;  /* label -> BobguiWidget* cache */
  GList *active_frame_widgets;
  BobguiWidget *current_parent;
  BobguiBox *root_box;
};

BobguiImguiContext *
bobgui_imgui_context_new (void)
{
  BobguiImguiContext *ctx = g_new0 (BobguiImguiContext, 1);
  ctx->widgets = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);
  ctx->root_box = BOBGUI_BOX (bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 2));
  g_object_ref_sink (ctx->root_box);
  return ctx;
}

void
bobgui_imgui_context_free (BobguiImguiContext *ctx)
{
  g_hash_table_destroy (ctx->widgets);
  g_object_unref (ctx->root_box);
  g_free (ctx);
}

void
bobgui_imgui_new_frame (BobguiImguiContext *ctx)
{
  /* Hide all widgets from previous frame */
  GHashTableIter iter;
  gpointer value;
  g_hash_table_iter_init (&iter, ctx->widgets);
  while (g_hash_table_iter_next (&iter, NULL, &value)) {
    bobgui_widget_set_visible (BOBGUI_WIDGET (value), FALSE);
  }
  ctx->active_frame_widgets = NULL;
}

static BobguiWidget *
get_or_create_widget (BobguiImguiContext *ctx, const char *label, GType type)
{
  BobguiWidget *w = g_hash_table_lookup (ctx->widgets, label);
  if (!w) {
    if (type == BOBGUI_TYPE_BUTTON)
      w = bobgui_button_new_with_label (label);
    else if (type == BOBGUI_TYPE_LABEL)
      w = bobgui_label_new (label);
    else if (type == BOBGUI_TYPE_CHECK_BUTTON)
      w = bobgui_check_button_new_with_label (label);
    else
      w = g_object_new (type, NULL);
    
    g_hash_table_insert (ctx->widgets, g_strdup (label), w);
    bobgui_box_append (ctx->root_box, w);
  }
  bobgui_widget_set_visible (w, TRUE);
  return w;
}

gboolean
bobgui_imgui_button (BobguiImguiContext *ctx, const char *label)
{
  BobguiButton *btn = BOBGUI_BUTTON (get_or_create_widget (ctx, label, BOBGUI_TYPE_BUTTON));
  /* In a real implementation, we'd poll the signal state here or use a callback */
  /* For absolute parity, we implement a 'clicked' flag based on recent signal events */
  return FALSE; /* Placeholder: requires event-loop integration for 100% parity */
}

void
bobgui_imgui_text (BobguiImguiContext *ctx, const char *format, ...)
{
  va_list args;
  va_start (args, format);
  char *text = g_strdup_vprintf (format, args);
  va_end (args);
  
  BobguiLabel *lbl = BOBGUI_LABEL (get_or_create_widget (ctx, text, BOBGUI_TYPE_LABEL));
  bobgui_label_set_text (lbl, text);
  g_free (text);
}

void
bobgui_imgui_render (BobguiImguiContext *ctx, BobguiWidget *parent)
{
  /* Append the IMGUI root box to the provided parent if not already there */
  if (BOBGUI_WIDGET (ctx->root_box)->parent != parent) {
    if (BOBGUI_IS_BOX (parent))
      bobgui_box_append (BOBGUI_BOX (parent), BOBGUI_WIDGET (ctx->root_box));
  }
}
