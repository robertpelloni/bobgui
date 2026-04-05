#include <bobgui/cpp/bobgui.hpp>

#include <memory>
#include <string>

using bobgui::cpp::Application;
using bobgui::cpp::StudioShell;
using bobgui::cpp::Workbench;

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

    Workbench::CommandOptions about_options;
    Workbench::CommandOptions sidebar_options;

    about_options.section = "Help";
    about_options.category = "Application";
    about_options.shortcut = "Ctrl+Shift+A";
    about_options.icon_name = "help-about-symbolic";

    sidebar_options.section = "Panels";
    sidebar_options.category = "View";
    sidebar_options.shortcut = "Ctrl+B";
    sidebar_options.icon_name = "sidebar-show-right-symbolic";

    shell->add_command ("app.about",
                        "About",
                        "Show application information",
                        about_options,
                        [&] (const std::string &) {
                          shell->set_status ("About action triggered");
                        });

    shell->add_toggle_command ("view.toggle-left-sidebar",
                               "Toggle Left Sidebar",
                               "Show or hide the project sidebar",
                               sidebar_options,
                               true,
                               [&] (const std::string &) {
                                 shell->set_status ("Sidebar toggle action triggered");
                               });

    {
      bobgui::cpp::ToolSurfaceModel tool_surface = shell->tool_surface_model ();
      std::string status = "Ready: " + std::to_string (tool_surface.section_count ()) +
                           " sections / " + std::to_string (tool_surface.item_count ()) +
                           " tools";
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
