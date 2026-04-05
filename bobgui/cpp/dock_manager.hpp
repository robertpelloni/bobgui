#ifndef BOBGUI_CPP_DOCK_MANAGER_HPP
#define BOBGUI_CPP_DOCK_MANAGER_HPP

#include <bobgui/modules/visual/dock/bobguidock.h>

#include "object_handle.hpp"

namespace bobgui {
namespace cpp {

class DockManager
{
public:
  explicit DockManager (BobguiWindow *window)
  : manager_ (bobgui_dock_manager_new (window))
  {
  }

  BobguiDockManager *native () const
  {
    return manager_.get ();
  }

private:
  ObjectHandle<BobguiDockManager> manager_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
