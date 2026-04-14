<<<<<<< HEAD
#include <bobgui/bobgui.h>

G_GNUC_BEGIN_IGNORE_DEPRECATIONS
=======
#include <gtk/gtk.h>
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px

typedef enum {
  RESPONSE_UNREVEAL,
} Response;

static void
<<<<<<< HEAD
on_info_bar_response (BobguiInfoBar *info_bar,
=======
on_info_bar_response (GtkInfoBar *info_bar,
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
                      int         response_id,
                      void       *user_data)
{
  switch (response_id)
  {
<<<<<<< HEAD
  case BOBGUI_RESPONSE_CLOSE:
    bobgui_widget_set_visible (BOBGUI_WIDGET (info_bar), FALSE);
    break;

  case RESPONSE_UNREVEAL:
    bobgui_info_bar_set_revealed (info_bar, FALSE);
=======
  case GTK_RESPONSE_CLOSE:
    gtk_widget_hide (GTK_WIDGET (info_bar));
    break;

  case RESPONSE_UNREVEAL:
    gtk_info_bar_set_revealed (info_bar, FALSE);
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
    break;

  default:
    g_assert_not_reached ();
  }
}

static void
on_activate (GApplication *application,
             void         *user_data)
{
<<<<<<< HEAD
  BobguiWidget *box;
  BobguiWidget *info_bar;
  BobguiWidget *widget;

  box = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 10);

  info_bar = bobgui_info_bar_new ();
  bobgui_info_bar_add_child (BOBGUI_INFO_BAR (info_bar),
                          bobgui_label_new ("Hello!\nI am a BobguiInfoBar"));

  widget = bobgui_toggle_button_new_with_label ("Toggle :visible");
  bobgui_toggle_button_set_active (BOBGUI_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "visible",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  bobgui_box_append (BOBGUI_BOX (box), widget);

  widget = bobgui_toggle_button_new_with_label ("Toggle :revealed");
  bobgui_toggle_button_set_active (BOBGUI_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "revealed",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  bobgui_box_append (BOBGUI_BOX (box), widget);

  widget = bobgui_toggle_button_new_with_label ("Toggle :show-close-button");
  bobgui_toggle_button_set_active (BOBGUI_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "show-close-button",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  bobgui_box_append (BOBGUI_BOX (box), widget);

  widget = bobgui_combo_box_text_new ();
  bobgui_combo_box_text_append (BOBGUI_COMBO_BOX_TEXT (widget),
                             NULL, "BOBGUI_MESSAGE_INFO");
  bobgui_combo_box_text_append (BOBGUI_COMBO_BOX_TEXT (widget),
                             NULL, "BOBGUI_MESSAGE_WARNING");
  bobgui_combo_box_text_append (BOBGUI_COMBO_BOX_TEXT (widget),
                             NULL, "BOBGUI_MESSAGE_QUESTION");
  bobgui_combo_box_text_append (BOBGUI_COMBO_BOX_TEXT (widget),
                             NULL, "BOBGUI_MESSAGE_ERROR");
  bobgui_combo_box_text_append (BOBGUI_COMBO_BOX_TEXT (widget),
                             NULL, "BOBGUI_MESSAGE_OTHER");
  bobgui_combo_box_set_active (BOBGUI_COMBO_BOX (widget), 0);
  g_object_bind_property (widget, "active",
                          info_bar, "message-type",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  bobgui_box_append (BOBGUI_BOX (box), widget);

  bobgui_box_append (BOBGUI_BOX (box), info_bar);

  widget = bobgui_button_new_with_label ("Un-reveal");
  bobgui_info_bar_add_action_widget (BOBGUI_INFO_BAR (info_bar), widget,
=======
  GtkWidget *box;
  GtkWidget *info_bar;
  GtkWidget *widget;

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);

  info_bar = gtk_info_bar_new ();
  gtk_container_add (GTK_CONTAINER (gtk_info_bar_get_content_area (GTK_INFO_BAR (info_bar))),
                     gtk_label_new ("Hello!\nI am a GtkInfoBar"));

  widget = gtk_toggle_button_new_with_label ("Toggle :visible");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "visible",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  gtk_container_add (GTK_CONTAINER (box), widget);

  widget = gtk_toggle_button_new_with_label ("Toggle :revealed");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "revealed",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  gtk_container_add (GTK_CONTAINER (box), widget);

  widget = gtk_toggle_button_new_with_label ("Toggle :show-close-button");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (widget), TRUE);
  g_object_bind_property (widget, "active",
                          info_bar, "show-close-button",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  gtk_container_add (GTK_CONTAINER (box), widget);

  widget = gtk_combo_box_text_new ();
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (widget),
                             NULL, "GTK_MESSAGE_INFO");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (widget),
                             NULL, "GTK_MESSAGE_WARNING");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (widget),
                             NULL, "GTK_MESSAGE_QUESTION");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (widget),
                             NULL, "GTK_MESSAGE_ERROR");
  gtk_combo_box_text_append (GTK_COMBO_BOX_TEXT (widget),
                             NULL, "GTK_MESSAGE_OTHER");
  gtk_combo_box_set_active (GTK_COMBO_BOX (widget), 0);
  g_object_bind_property (widget, "active",
                          info_bar, "message-type",
                          G_BINDING_SYNC_CREATE | G_BINDING_BIDIRECTIONAL);
  gtk_container_add (GTK_CONTAINER (box), widget);

  gtk_container_add (GTK_CONTAINER (box), info_bar);

  widget = gtk_button_new_with_label ("Un-reveal");
  gtk_info_bar_add_action_widget (GTK_INFO_BAR (info_bar), widget,
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
                                  RESPONSE_UNREVEAL);

  g_signal_connect (info_bar, "response",
                    G_CALLBACK (on_info_bar_response), widget);

<<<<<<< HEAD
  widget = bobgui_window_new ();
  bobgui_window_set_child (BOBGUI_WINDOW (widget), box);
  bobgui_widget_show (widget);
  bobgui_application_add_window (BOBGUI_APPLICATION (application),
                              BOBGUI_WINDOW (widget));
=======
  widget = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_container_add (GTK_CONTAINER (widget), box);
  gtk_widget_show_all (widget);
  gtk_application_add_window (GTK_APPLICATION (application),
                              GTK_WINDOW (widget));
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
}

int
main (int   argc,
      char *argv[])
{
<<<<<<< HEAD
  BobguiApplication *application;
  int result;

  application = bobgui_application_new ("org.bobgui.test.infobar",
                                     G_APPLICATION_DEFAULT_FLAGS);
=======
  GtkApplication *application;
  int result;

  application = gtk_application_new ("org.gtk.test.infobar",
                                     G_APPLICATION_FLAGS_NONE);
>>>>>>> origin/1422-gtkentry-s-minimum-width-is-hardcoded-to-150px
  g_signal_connect (application, "activate", G_CALLBACK (on_activate), NULL);

  result = g_application_run (G_APPLICATION (application), argc, argv);
  g_object_unref (application);
  return result;
}
