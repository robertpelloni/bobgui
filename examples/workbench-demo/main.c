#include <bobgui/bobgui.h>
#include <bobgui/modules/visual/visual.h>

static void
on_show_about (const char *command_id,
               gpointer    user_data)
{
  BobguiWorkbench *workbench = user_data;

  (void) command_id;
  bobgui_workbench_set_status (workbench, "About action triggered");
}

static void
on_toggle_left (const char *command_id,
                gpointer    user_data)
{
  BobguiWorkbench *workbench = user_data;

  (void) command_id;
  bobgui_workbench_set_status (workbench, "Toggle sidebar action triggered");
}

static void
on_activate (BobguiApplication *application,
             gpointer           user_data)
{
  BobguiWorkbench *workbench;
  BobguiActionRegistry *registry;
  BobguiCommandPalette *palette;
  BobguiWidget *editor;
  BobguiWidget *sidebar;

  (void) user_data;

  workbench = bobgui_workbench_new (application);
  registry = bobgui_action_registry_new ();
  palette = bobgui_command_palette_new (application);

  bobgui_workbench_set_action_registry (workbench, registry);
  bobgui_workbench_set_command_palette (workbench, palette);
  bobgui_workbench_set_title (workbench, "Bobgui Workbench Demo");

  editor = bobgui_text_view_new ();
  sidebar = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);
  bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Project"));
  bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Files"));

  bobgui_workbench_set_left_sidebar (workbench, sidebar);
  bobgui_workbench_set_central (workbench, editor);

  bobgui_workbench_add_command (workbench,
                                "app.about",
                                "About",
                                "Show application information",
                                on_show_about,
                                workbench);
  bobgui_workbench_add_command (workbench,
                                "view.toggle-left-sidebar",
                                "Toggle Left Sidebar",
                                "Show or hide the project sidebar",
                                on_toggle_left,
                                workbench);

  bobgui_workbench_add_header_action_for_command (workbench, "About", "app.about");
  bobgui_workbench_add_header_action_for_command (workbench, "Sidebar", "view.toggle-left-sidebar");
  bobgui_workbench_present (workbench);
}

int
main (int argc, char **argv)
{
  BobguiApplication *application;
  int status;

  application = g_object_new (BOBGUI_TYPE_APPLICATION,
                              "application-id", "org.bobgui.WorkbenchDemo",
                              NULL);
  g_signal_connect (application, "activate", G_CALLBACK (on_activate), NULL);
  status = g_application_run (G_APPLICATION (application), argc, argv);
  g_object_unref (application);

  return status;
}
