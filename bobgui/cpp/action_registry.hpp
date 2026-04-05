#ifndef BOBGUI_CPP_ACTION_REGISTRY_HPP
#define BOBGUI_CPP_ACTION_REGISTRY_HPP

#include <bobgui/modules/visual/actionregistry/bobguiactionregistry.h>

#include "object_handle.hpp"

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace bobgui {
namespace cpp {

class ActionRegistry
{
public:
  typedef std::function<void(const std::string &)> ActionHandler;

  struct ActionOptions
  {
    const char *section;
    const char *category;
    const char *shortcut;
    const char *icon_name;

    ActionOptions ()
    : section (NULL),
      category (NULL),
      shortcut (NULL),
      icon_name (NULL)
    {
    }
  };

  ActionRegistry ()
  : registry_ (bobgui_action_registry_new ())
  {
  }

  BobguiActionRegistry *native () const
  {
    return registry_.get ();
  }

  void add_action (const char          *action_id,
                   const char          *title,
                   const char          *subtitle,
                   const ActionOptions &options,
                   ActionHandler        handler)
  {
    ActionBinding *binding = add_binding (std::move (handler));

    bobgui_action_registry_add_sectioned (registry_.get (),
                                          action_id,
                                          title,
                                          subtitle,
                                          options.section,
                                          options.category,
                                          options.shortcut,
                                          options.icon_name,
                                          &ActionRegistry::action_trampoline,
                                          binding);
  }

  void add_toggle_action (const char          *action_id,
                          const char          *title,
                          const char          *subtitle,
                          const ActionOptions &options,
                          bool                 checked,
                          ActionHandler        handler)
  {
    ActionBinding *binding = add_binding (std::move (handler));

    bobgui_action_registry_add_toggle (registry_.get (),
                                       action_id,
                                       title,
                                       subtitle,
                                       options.section,
                                       options.category,
                                       options.shortcut,
                                       options.icon_name,
                                       checked,
                                       &ActionRegistry::action_trampoline,
                                       binding);
  }

  void activate (const char *action_id)
  {
    bobgui_action_registry_activate (registry_.get (), action_id);
  }

  void set_checked (const char *action_id,
                    bool        checked)
  {
    bobgui_action_registry_set_checked (registry_.get (), action_id, checked);
  }

  bool is_checked (const char *action_id) const
  {
    return bobgui_action_registry_get_checked (registry_.get (), action_id);
  }

  ObjectHandle<GMenuModel> create_menu_model () const
  {
    return ObjectHandle<GMenuModel> (bobgui_action_registry_create_menu_model (registry_.get ()));
  }

private:
  struct ActionBinding
  {
    ActionHandler handler;
  };

  static void action_trampoline (const char *action_id,
                                 gpointer    user_data)
  {
    ActionBinding *binding = static_cast<ActionBinding *> (user_data);

    if (binding->handler)
      binding->handler (action_id != nullptr ? std::string (action_id) : std::string ());
  }

  ActionBinding *add_binding (ActionHandler handler)
  {
    bindings_.push_back (std::unique_ptr<ActionBinding> (new ActionBinding));
    bindings_.back ()->handler = std::move (handler);
    return bindings_.back ().get ();
  }

  ObjectHandle<BobguiActionRegistry> registry_;
  std::vector<std::unique_ptr<ActionBinding> > bindings_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
