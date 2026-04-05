#include <bobgui/cpp/bobgui.hpp>

#include <memory>

using bobgui::cpp::ActionRegistry;
using bobgui::cpp::Application;
using bobgui::cpp::CommandPalette;
using bobgui::cpp::Workbench;

int
main (int argc, char **argv)
{
  Application app ("org.bobgui.WorkbenchDemoCpp");
  std::unique_ptr<Workbench> workbench;
  std::unique_ptr<ActionRegistry> actions;
  std::unique_ptr<CommandPalette> palette;

  app.on_activate ([&] (Application &application) {
    workbench.reset (new Workbench (application));
    actions.reset (new ActionRegistry ());
    palette.reset (new CommandPalette (application));

    BobguiWidget *editor = bobgui_text_view_new ();
    BobguiWidget *sidebar = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);

    bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Project"));
    bobgui_box_append (BOBGUI_BOX (sidebar), bobgui_label_new ("Files"));

    workbench->set_action_registry (*actions);
    workbench->set_command_palette (*palette);
    palette->set_pinned ("app.about", true);

    workbench->set_title ("Bobgui Workbench Demo (C++)");
    workbench->set_left_sidebar (sidebar);
    workbench->set_central (editor);

    workbench->add_sectioned_command ("app.about",
                                     "About",
                                     "Show application information",
                                     "Help",
                                     "Application",
                                     "Ctrl+Shift+A",
                                     "help-about-symbolic",
                                     [&] (const std::string &) {
                                       workbench->set_status ("About action triggered");
                                     });

    workbench->add_toggle_sectioned_command ("view.toggle-left-sidebar",
                                            "Toggle Left Sidebar",
                                            "Show or hide the project sidebar",
                                            "Panels",
                                            "View",
                                            "Ctrl+B",
                                            "sidebar-show-right-symbolic",
                                            true,
                                            [&] (const std::string &) {
                                              workbench->set_status ("Sidebar toggle action triggered");
                                            });

    workbench->add_header_action_for_command ("About", "app.about");
    workbench->add_header_action_for_command ("Sidebar", "view.toggle-left-sidebar");
    workbench->enable_menubar (true);
    workbench->enable_toolbar (true);
    workbench->present ();
  });

  return app.run (argc, argv);
}
