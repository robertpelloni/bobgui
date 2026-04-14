/* Text View/Tabs
 *
<<<<<<< HEAD:demos/bobgui-demo/tabs.c
 * BobguiTextView can position text at fixed positions, using tabs.
 * Tabs can specify alignment, and also allow aligning numbers
 * on the decimal point.
 *
 * The example here has three tabs, with left, numeric and right
 * alignment.
 */

#include <bobgui/bobgui.h>
#include <gdk/gdkkeysyms.h>

BobguiWidget *
do_tabs (BobguiWidget *do_widget)
{
  static BobguiWidget *window = NULL;

  if (!window)
    {
      BobguiWidget *view;
      BobguiWidget *sw;
      BobguiTextBuffer *buffer;
      PangoTabArray *tabs;

      window = bobgui_window_new ();
      bobgui_window_set_title (BOBGUI_WINDOW (window), "Tabs");
      bobgui_window_set_display (BOBGUI_WINDOW (window),
                              bobgui_widget_get_display (do_widget));
      bobgui_window_set_default_size (BOBGUI_WINDOW (window), 330, 130);
      bobgui_window_set_resizable (BOBGUI_WINDOW (window), FALSE);
      g_object_add_weak_pointer (G_OBJECT (window), (gpointer *)&window);

      view = bobgui_text_view_new ();
      bobgui_text_view_set_wrap_mode (BOBGUI_TEXT_VIEW (view), BOBGUI_WRAP_WORD);
      bobgui_text_view_set_top_margin (BOBGUI_TEXT_VIEW (view), 20);
      bobgui_text_view_set_bottom_margin (BOBGUI_TEXT_VIEW (view), 20);
      bobgui_text_view_set_left_margin (BOBGUI_TEXT_VIEW (view), 20);
      bobgui_text_view_set_right_margin (BOBGUI_TEXT_VIEW (view), 20);

      tabs = pango_tab_array_new (3, TRUE);
      pango_tab_array_set_tab (tabs, 0, PANGO_TAB_LEFT, 0);
      pango_tab_array_set_tab (tabs, 1, PANGO_TAB_DECIMAL, 150);
      pango_tab_array_set_decimal_point (tabs, 1, '.');
      pango_tab_array_set_tab (tabs, 2, PANGO_TAB_RIGHT, 290);
      bobgui_text_view_set_tabs (BOBGUI_TEXT_VIEW (view), tabs);
      pango_tab_array_free (tabs);

      buffer = bobgui_text_view_get_buffer (BOBGUI_TEXT_VIEW (view));
      bobgui_text_buffer_set_text (buffer, "one\t2.0\tthree\nfour\t5.555\tsix\nseven\t88.88\tnine", -1);

      sw = bobgui_scrolled_window_new ();
      bobgui_scrolled_window_set_policy (BOBGUI_SCROLLED_WINDOW (sw),
                                      BOBGUI_POLICY_NEVER,
                                      BOBGUI_POLICY_AUTOMATIC);
      bobgui_window_set_child (BOBGUI_WINDOW (window), sw);
      bobgui_scrolled_window_set_child (BOBGUI_SCROLLED_WINDOW (sw), view);
    }

  if (!bobgui_widget_get_visible (window))
    bobgui_widget_set_visible (window, TRUE);
  else
    bobgui_window_destroy (BOBGUI_WINDOW (window));
=======
 * GtkTextView can position text at fixed positions, using tabs.
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

GtkWidget *
do_tabs (GtkWidget *do_widget)
{
  static GtkWidget *window = NULL;

  if (!window)
    {
      GtkWidget *view;
      GtkWidget *sw;
      GtkTextBuffer *buffer;
      PangoTabArray *tabs;

      window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
      gtk_window_set_title (GTK_WINDOW (window), "Tabs");
      gtk_window_set_screen (GTK_WINDOW (window),
                             gtk_widget_get_screen (do_widget));
      gtk_window_set_default_size (GTK_WINDOW (window), 450, 450);

      g_signal_connect (window, "destroy",
                        G_CALLBACK (gtk_widget_destroyed), &window);

      gtk_container_set_border_width (GTK_CONTAINER (window), 0);

      view = gtk_text_view_new ();
      gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view), GTK_WRAP_WORD);
      gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 20);
      gtk_text_view_set_right_margin (GTK_TEXT_VIEW (view), 20);

      tabs = pango_tab_array_new (3, TRUE);
      pango_tab_array_set_tab (tabs, 0, PANGO_TAB_LEFT, 0);
      pango_tab_array_set_tab (tabs, 1, PANGO_TAB_LEFT, 150);
      pango_tab_array_set_tab (tabs, 2, PANGO_TAB_LEFT, 300);
      gtk_text_view_set_tabs (GTK_TEXT_VIEW (view), tabs);
      pango_tab_array_free (tabs);

      buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
      gtk_text_buffer_set_text (buffer, "one\ttwo\tthree\nfour\tfive\tsix\nseven\teight\tnine", -1);

      sw = gtk_scrolled_window_new (NULL, NULL);
      gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
                                      GTK_POLICY_AUTOMATIC,
                                      GTK_POLICY_AUTOMATIC);
      gtk_container_add (GTK_CONTAINER (window), sw);
      gtk_container_add (GTK_CONTAINER (sw), view);

      gtk_widget_show_all (sw);
    }

  if (!gtk_widget_get_visible (window))
    gtk_widget_show (window);
  else
    gtk_widget_destroy (window);
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px:demos/gtk-demo/tabs.c

  return window;
}
