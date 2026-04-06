#include <bobgui/cpp/bobgui.hpp>

#include <memory>
#include <string>

using bobgui::cpp::Application;
using bobgui::cpp::DashboardShell;

int
main (int argc, char **argv)
{
  Application app ("org.bobgui.DashboardDemoCpp");
  std::unique_ptr<DashboardShell> shell;

  app.on_activate ([&] (Application &application) {
    shell.reset (new DashboardShell (application));

    BobguiWidget *navigation = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);
    BobguiWidget *dashboard = bobgui_text_view_new ();
    BobguiWidget *context = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 6);

    bobgui_box_append (BOBGUI_BOX (navigation), bobgui_label_new ("Navigation"));
    bobgui_box_append (BOBGUI_BOX (navigation), bobgui_label_new ("Overview"));
    bobgui_box_append (BOBGUI_BOX (navigation), bobgui_label_new ("Alerts"));
    bobgui_box_append (BOBGUI_BOX (context), bobgui_label_new ("Context"));
    bobgui_box_append (BOBGUI_BOX (context), bobgui_label_new ("Filters"));

    shell->set_title ("Bobgui Dashboard Demo (C++)");
    shell->set_navigation_panel (navigation);
    shell->set_dashboard_view (dashboard);
    shell->set_context_panel (context);
    shell->pin_command ("dashboard.refresh", true);

    shell->add_dashboard_command ("dashboard.refresh",
                                  "Refresh Dashboard",
                                  "Reload the active dashboard view",
                                  "Ctrl+R",
                                  "view-refresh-symbolic",
                                  [&] (const std::string &) {
                                    shell->set_status ("Dashboard refresh triggered");
                                  });

    shell->add_workspace_command ("dashboard.focus-main",
                                  "Focus Main Dashboard",
                                  "Jump to the primary dashboard view",
                                  "Ctrl+1",
                                  "view-grid-symbolic",
                                  [&] (const std::string &) {
                                    shell->set_status ("Dashboard workspace action triggered");
                                  });

    shell->add_panel_toggle_command ("dashboard.context.toggle",
                                     "Toggle Context Panel",
                                     "Show or hide the contextual side panel",
                                     "Ctrl+Shift+P",
                                     "sidebar-show-right-symbolic",
                                     true,
                                     [&] (const std::string &) {
                                       shell->set_status ("Context panel toggle triggered");
                                     });

    bobgui_box_append (BOBGUI_BOX (navigation), bobgui_label_new ("Dashboard Actions"));
    bobgui_box_append (BOBGUI_BOX (navigation), shell->build_dashboard_toolbar_widget ());

    bobgui_box_append (BOBGUI_BOX (context), bobgui_label_new ("Panel Actions"));
    bobgui_box_append (BOBGUI_BOX (context), shell->build_dashboard_panel_toolbar_widget ());
    bobgui_box_append (BOBGUI_BOX (context), bobgui_label_new ("Panel Tools"));
    bobgui_box_append (BOBGUI_BOX (context), shell->build_dashboard_panel_tools_widget ());

    shell->add_header_action_for_command ("Refresh", "dashboard.refresh");
    shell->add_header_action_for_command ("Context", "dashboard.context.toggle");
    shell->enable_menubar (true);
    shell->enable_toolbar (true);
    shell->set_status ("Dashboard shell ready");
    shell->present ();
  });

  return app.run (argc, argv);
}
