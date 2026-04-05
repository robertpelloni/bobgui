#ifndef BOBGUI_CPP_STUDIO_SHELL_HPP
#define BOBGUI_CPP_STUDIO_SHELL_HPP

#include "app_shell.hpp"

#include <utility>

namespace bobgui {
namespace cpp {

class StudioShell
{
public:
  explicit StudioShell (Application &application)
  : shell_ (application)
  {
    shell_.dock_manager ();
  }

  AppShell &shell ()
  {
    return shell_;
  }

  Workbench &workbench ()
  {
    return shell_.workbench ();
  }

  ActionRegistry &actions ()
  {
    return shell_.actions ();
  }

  CommandPalette &palette ()
  {
    return shell_.palette ();
  }

  DockManager &dock_manager ()
  {
    return shell_.dock_manager ();
  }

  void set_title (const char *title)
  {
    shell_.set_title (title);
  }

  void set_navigation_panel (BobguiWidget *widget)
  {
    shell_.set_left_sidebar (widget);
  }

  void set_document_view (BobguiWidget *widget)
  {
    shell_.set_central (widget);
  }

  void set_inspector_panel (BobguiWidget *widget)
  {
    shell_.set_right_sidebar (widget);
  }

  void set_status (const char *message)
  {
    shell_.set_status (message);
  }

  void pin_command (const char *command_id,
                    bool        pinned)
  {
    shell_.pin_command (command_id, pinned);
  }

  void add_header_action_for_command (const char *label,
                                      const char *command_id)
  {
    shell_.add_header_action_for_command (label, command_id);
  }

  void enable_menubar (bool enabled)
  {
    shell_.enable_menubar (enabled);
  }

  void enable_toolbar (bool enabled)
  {
    shell_.enable_toolbar (enabled);
  }

  void add_command (const char               *command_id,
                    const char               *title,
                    const char               *subtitle,
                    const Workbench::CommandOptions &options,
                    Workbench::CommandHandler handler)
  {
    shell_.add_command (command_id,
                        title,
                        subtitle,
                        options,
                        std::move (handler));
  }

  void add_toggle_command (const char               *command_id,
                           const char               *title,
                           const char               *subtitle,
                           const Workbench::CommandOptions &options,
                           bool                      checked,
                           Workbench::CommandHandler handler)
  {
    shell_.add_toggle_command (command_id,
                               title,
                               subtitle,
                               options,
                               checked,
                               std::move (handler));
  }

  ObjectHandle<GMenuModel> menu_model () const
  {
    return shell_.menu_model ();
  }

  void visit_actions (ActionRegistry::ActionVisitor visitor) const
  {
    shell_.visit_actions (std::move (visitor));
  }

  std::vector<ActionRegistry::ActionInfo> list_actions () const
  {
    return shell_.list_actions ();
  }

  std::vector<ActionRegistry::ActionSection> list_tool_sections () const
  {
    return shell_.list_action_sections ();
  }

  ToolSurfaceModel tool_surface_model () const
  {
    return shell_.tool_surface_model ();
  }

  void present ()
  {
    shell_.present ();
  }

private:
  AppShell shell_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
