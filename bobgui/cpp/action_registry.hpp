#ifndef BOBGUI_CPP_ACTION_REGISTRY_HPP
#define BOBGUI_CPP_ACTION_REGISTRY_HPP

#include <bobgui/modules/visual/actionregistry/bobguiactionregistry.h>

#include "object_handle.hpp"

namespace bobgui {
namespace cpp {

class ActionRegistry
{
public:
  ActionRegistry ()
  : registry_ (bobgui_action_registry_new ())
  {
  }

  BobguiActionRegistry *native () const
  {
    return registry_.get ();
  }

private:
  ObjectHandle<BobguiActionRegistry> registry_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
