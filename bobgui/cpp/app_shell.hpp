#ifndef BOBGUI_CPP_APP_SHELL_HPP
#define BOBGUI_CPP_APP_SHELL_HPP

#include "workbench.hpp"

#include <utility>

namespace bobgui {
namespace cpp {

class AppShell
{
public:
  explicit AppShell (Application &application)
  : workbench_ (application),
    action_registry_ (),
    command_palette_ (application)
  {
    workbench_.set_action_registry (action_registry_);
    workbench_.set_command_palette (command_palette_);
  }

  Workbench &workbench ()
  {
    return workbench_;
  }

  ActionRegistry &actions ()
  {
    return action_registry_;
  }

  CommandPalette &palette ()
  {
    return command_palette_;
  }

  void set_title (const char *title)
  {
    workbench_.set_title (title);
  }

  void set_central (BobguiWidget *widget)
  {
    workbench_.set_central (widget);
  }

  void set_left_sidebar (BobguiWidget *widget)
  {
    workbench_.set_left_sidebar (widget);
  }

  void set_right_sidebar (BobguiWidget *widget)
  {
    workbench_.set_right_sidebar (widget);
  }

  void set_status (const char *message)
  {
    workbench_.set_status (message);
  }

  void pin_command (const char *command_id,
                    bool        pinned)
  {
    command_palette_.set_pinned (command_id, pinned);
  }

  void add_header_action_for_command (const char *label,
                                      const char *command_id)
  {
    workbench_.add_header_action_for_command (label, command_id);
  }

  void enable_menubar (bool enabled)
  {
    workbench_.enable_menubar (enabled);
  }

  void enable_toolbar (bool enabled)
  {
    workbench_.enable_toolbar (enabled);
  }

  void add_command (const char               *command_id,
                    const char               *title,
                    const char               *subtitle,
                    const Workbench::CommandOptions &options,
                    Workbench::CommandHandler handler)
  {
    workbench_.add_command (command_id,
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
    workbench_.add_toggle_command (command_id,
                                   title,
                                   subtitle,
                                   options,
                                   checked,
                                   std::move (handler));
  }

  void present ()
  {
    workbench_.present ();
  }

private:
  Workbench workbench_;
  ActionRegistry action_registry_;
  CommandPalette command_palette_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
