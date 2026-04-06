#include <bobgui/cpp/bobgui.hpp>

#include <memory>
#include <string>

using bobgui::cpp::Application;
using bobgui::cpp::StudioShell;

int
main (int argc, char **argv)
{
  Application app ("org.bobgui.WorkbenchDemoCpp");
  std::unique_ptr<StudioShell> shell;

  app.on_activate ([&] (Application &application) {
    shell.reset (new StudioShell (application));

    BobguiWidget *editor = bobgui_text_view_new ();
    BobguiWidget *sidebar = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);
    BobguiWidget *inspector = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);

    bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Project"));
    bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Files"));
    bobgui_box_append (BOBGUI_BOX (inspector), bobgui_label_new ("Inspector"));
    bobgui_box_append (BOBGUI_BOX (inspector), bobgui_label_new ("Properties"));

    shell->pin_command ("app.about", true);

    shell->set_title ("Bobgui Workbench Demo (C++)");
    shell->set_navigation_panel (sidebar);
    shell->set_document_view (editor);
    shell->set_inspector_panel (inspector);

    bobgui::cpp::ActionRegistry::ActionOptions about_options;

    about_options.section = "Help";
    about_options.category = "Application";
    about_options.shortcut = "Ctrl+Shift+A";
    about_options.icon_name = "help-about-symbolic";

    shell->add_command ("app.about",
                        "About",
                        "Show application information",
                        about_options,
                        [&] (const std::string &) {
                          shell->set_status ("About action triggered");
                        });

    shell->add_panel_toggle_command ("view.toggle-left-sidebar",
                                     "Toggle Left Sidebar",
                                     "Show or hide the project sidebar",
                                     "Ctrl+B",
                                     "sidebar-show-right-symbolic",
                                     true,
                                     [&] (const std::string &) {
                                       shell->set_status ("Sidebar toggle action triggered");
                                     });

    shell->add_workspace_command ("workspace.focus-editor",
                                  "Focus Editor",
                                  "Move attention to the main document view",
                                  "Ctrl+1",
                                  "document-edit-symbolic",
                                  [&] (const std::string &) {
                                    shell->set_status ("Editor workspace action triggered");
                                  });

    bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Workspace"));
    bobgui_box_append (BOBGUI_BOX (sidebar), shell->build_workspace_toolbar_preset ());

    bobgui_box_append (BOBGUI_BOX (inspector), bobgui_label_new ("Panels"));
    bobgui_box_append (BOBGUI_BOX (inspector), shell->build_panel_toolbar_preset ());

    bobgui_box_append (BOBGUI_BOX (inspector), bobgui_label_new ("Panel Tools"));
    bobgui_box_append (BOBGUI_BOX (inspector), shell->build_panel_tool_surface_preset ());

    bobgui_box_append (BOBGUI_BOX (inspector), bobgui_label_new ("All Tools"));
    bobgui_box_append (BOBGUI_BOX (inspector), shell->build_descriptive_tool_surface_widget ());

    {
      bobgui::cpp::ToolSurfaceModel tool_surface = shell->tool_surface_model ();
      std::string status = "Ready: " + std::to_string (tool_surface.section_count ()) +
                           " sections / " + std::to_string (tool_surface.item_count ()) +
                           " tools / " + std::to_string (shell->workspace_action_count ()) +
                           " workspace / " + std::to_string (shell->panel_action_count ()) +
                           " panel";
      shell->set_status (status.c_str ());
    }

    shell->add_header_action_for_command ("About", "app.about");
    shell->add_header_action_for_command ("Sidebar", "view.toggle-left-sidebar");
    shell->enable_menubar (true);
    shell->enable_toolbar (true);
    shell->present ();
  });

  return app.run (argc, argv);
}
