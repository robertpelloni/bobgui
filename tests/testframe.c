/* testframe.c
 * Copyright (C) 2007  Xan López <xan@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bobgui/bobgui.h>
#include <math.h>

<<<<<<< HEAD
=======
static gint hpadding = 0, vpadding = 0;

static void
spin_hpadding_cb (GtkSpinButton *spin, gpointer user_data)
{
  GtkWidget *frame = user_data;
  GtkCssProvider *provider;
  GtkStyleContext *context;
  gchar *data;

  context = gtk_widget_get_style_context (frame);
  provider = g_object_get_data (G_OBJECT (frame), "provider");
  if (provider == NULL)
    {
      provider = gtk_css_provider_new ();
      g_object_set_data (G_OBJECT (frame), "provider", provider);
      gtk_style_context_add_provider (context,
                                      GTK_STYLE_PROVIDER (provider),
                                      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

  hpadding = (gint)gtk_spin_button_get_value (spin);
  data = g_strdup_printf ("frame > border { padding: %dpx %dpx }",
                          vpadding, hpadding);

  gtk_css_provider_load_from_data (provider, data, -1, NULL);
  g_free (data);

  gtk_widget_queue_resize (frame);
}

static void
spin_vpadding_cb (GtkSpinButton *spin, gpointer user_data)
{
  GtkWidget *frame = user_data;
  GtkCssProvider *provider;
  GtkStyleContext *context;
  gchar *data;

  context = gtk_widget_get_style_context (frame);
  provider = g_object_get_data (G_OBJECT (frame), "provider");
  if (provider == NULL)
    {
      provider = gtk_css_provider_new ();
      g_object_set_data (G_OBJECT (frame), "provider", provider);
      gtk_style_context_add_provider (context,
                                      GTK_STYLE_PROVIDER (provider),
                                      GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    }

  vpadding = (gint)gtk_spin_button_get_value (spin);
  data = g_strdup_printf ("frame > border { padding: %dpx %dpx }",
                          vpadding, hpadding);

  gtk_css_provider_load_from_data (provider, data, -1, NULL);
  g_free (data);

  gtk_widget_queue_resize (frame);
}

>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
/* Function to normalize rounding errors in FP arithmetic to
   our desired limits */

#define EPSILON 1e-10

static double
double_normalize (double n)
{
  if (fabs (1.0 - n) < EPSILON)
    n = 1.0;
  else if (n < EPSILON)
    n = 0.0;

  return n;
}

static void
spin_xalign_cb (BobguiSpinButton *spin, BobguiFrame *frame)
{
  double xalign;

  xalign = double_normalize (bobgui_spin_button_get_value (spin));
  bobgui_frame_set_label_align (frame, xalign);
}

static void
quit_cb (BobguiWidget *widget,
         gpointer   data)
{
  gboolean *done = data;

  *done = TRUE;

  g_main_context_wakeup (NULL);
}

static void
draw_border_cb (GtkToggleButton *toggle_button, GtkFrame *frame)
{
  GtkShadowType shadow_type = gtk_toggle_button_get_active (toggle_button)
                              ? GTK_SHADOW_IN : GTK_SHADOW_NONE;

  gtk_frame_set_shadow_type (frame, shadow_type);
}

int main (int argc, char **argv)
{
<<<<<<< HEAD
  BobguiWidget *window, *widget;
  BobguiBox *vbox;
  BobguiFrame *frame;
  BobguiGrid *grid;
  float xalign;
  gboolean done = FALSE;
=======
  GtkWidget *window, *widget;
  GtkBox *vbox;
  GtkFrame *frame;
  GtkGrid *grid;
  gfloat xalign, yalign;
  gboolean draw_border;
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

  bobgui_init ();

  window = bobgui_window_new ();
  bobgui_window_set_default_size (BOBGUI_WINDOW (window), 300, 300);

<<<<<<< HEAD
  g_signal_connect (window, "destroy", G_CALLBACK (quit_cb), &done);

  vbox = BOBGUI_BOX (bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 5));
  bobgui_widget_set_margin_start (BOBGUI_WIDGET (vbox), 12);
  bobgui_widget_set_margin_end (BOBGUI_WIDGET (vbox), 12);
  bobgui_widget_set_margin_top (BOBGUI_WIDGET (vbox), 12);
  bobgui_widget_set_margin_bottom (BOBGUI_WIDGET (vbox), 12);
  bobgui_window_set_child (BOBGUI_WINDOW (window), BOBGUI_WIDGET (vbox));

  frame = BOBGUI_FRAME (bobgui_frame_new ("Test BobguiFrame"));
  bobgui_widget_set_vexpand (BOBGUI_WIDGET (frame), TRUE);
  bobgui_box_append (BOBGUI_BOX (vbox), BOBGUI_WIDGET (frame));

  widget = bobgui_button_new_with_label ("Hello!");
  bobgui_frame_set_child (BOBGUI_FRAME (frame), widget);

  grid = BOBGUI_GRID (bobgui_grid_new ());
  bobgui_grid_set_row_spacing (grid, 12);
  bobgui_grid_set_column_spacing (grid, 6);
  bobgui_box_append (BOBGUI_BOX (vbox), BOBGUI_WIDGET (grid));

  xalign = bobgui_frame_get_label_align (frame);

  /* Spin to control :label-xalign */
  widget = bobgui_label_new ("label xalign:");
  bobgui_grid_attach (grid, widget, 0, 0, 1, 1);

  widget = bobgui_spin_button_new_with_range (0.0, 1.0, 0.1);
  bobgui_spin_button_set_value (BOBGUI_SPIN_BUTTON (widget), xalign);
  g_signal_connect (widget, "value-changed", G_CALLBACK (spin_xalign_cb), frame);
  bobgui_grid_attach (grid, widget, 1, 0, 1, 1);

  bobgui_window_present (BOBGUI_WINDOW (window));

  while (!done)
    g_main_context_iteration (NULL, TRUE);
=======
  g_signal_connect (window, "delete-event", gtk_main_quit, NULL);

  vbox = GTK_BOX (gtk_box_new (GTK_ORIENTATION_VERTICAL, 5));
  g_object_set (vbox, "margin", 12, NULL);
  gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (vbox));

  frame = GTK_FRAME (gtk_frame_new ("Test GtkFrame"));
  gtk_box_pack_start (vbox, GTK_WIDGET (frame), TRUE, TRUE, 0);

  widget = gtk_button_new_with_label ("Hello!");
  gtk_container_add (GTK_CONTAINER (frame), widget);

  grid = GTK_GRID (gtk_grid_new ());
  gtk_grid_set_row_spacing (grid, 12);
  gtk_grid_set_column_spacing (grid, 6);
  gtk_box_pack_start (vbox, GTK_WIDGET (grid), FALSE, FALSE, 0);

  gtk_frame_get_label_align (frame, &xalign, &yalign);

  /* Spin to control :label-xalign */
  widget = gtk_label_new ("label xalign:");
  gtk_grid_attach (grid, widget, 0, 0, 1, 1);

  widget = gtk_spin_button_new_with_range (0.0, 1.0, 0.1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), xalign);
  g_signal_connect (widget, "value-changed", G_CALLBACK (spin_xalign_cb), frame);
  gtk_grid_attach (grid, widget, 1, 0, 1, 1);

  /* Spin to control :label-yalign */
  widget = gtk_label_new ("label yalign:");
  gtk_grid_attach (grid, widget, 0, 1, 1, 1);

  widget = gtk_spin_button_new_with_range (0.0, 1.0, 0.1);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), yalign);
  g_signal_connect (widget, "value-changed", G_CALLBACK (spin_yalign_cb), frame);
  gtk_grid_attach (grid, widget, 1, 1, 1, 1);

  /* Spin to control vertical padding */
  widget = gtk_label_new ("vertical padding:");
  gtk_grid_attach (grid, widget, 0, 2, 1, 1);

  widget = gtk_spin_button_new_with_range (0, 250, 1);
  g_signal_connect (widget, "value-changed", G_CALLBACK (spin_vpadding_cb), frame);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), vpadding);
  gtk_grid_attach (grid, widget, 1, 2, 1, 1);

  /* Spin to control horizontal padding */
  widget = gtk_label_new ("horizontal padding:");
  gtk_grid_attach (grid, widget, 0, 3, 1, 1);

  widget = gtk_spin_button_new_with_range (0, 250, 1);
  g_signal_connect (widget, "value-changed", G_CALLBACK (spin_hpadding_cb), frame);
  gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget), hpadding);
  gtk_grid_attach (grid, widget, 1, 3, 1, 1);

  /* CheckButton to control whether to draw border */
  draw_border = gtk_frame_get_shadow_type (frame) != GTK_SHADOW_NONE;
  widget = gtk_check_button_new_with_label ("draw border");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), draw_border);
  g_signal_connect (widget, "toggled", G_CALLBACK (draw_border_cb), frame);
  gtk_grid_attach (grid, widget, 0, 4, 2, 1);

  gtk_widget_show_all (window);

  gtk_main ();
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

  return 0;
}
