#ifndef BOBGUI_CPP_APPLICATION_HPP
#define BOBGUI_CPP_APPLICATION_HPP

#include <bobgui/bobgui.h>

#include "object_handle.hpp"

#include <functional>
#include <utility>

namespace bobgui {
namespace cpp {

class Application
{
public:
  typedef std::function<void(Application &)> ActivateHandler;

  explicit Application (const char *application_id)
  : app_ (BOBGUI_APPLICATION (g_object_new (BOBGUI_TYPE_APPLICATION,
                                            "application-id", application_id,
                                            NULL)))
  {
    g_signal_connect (app_.get (),
                      "activate",
                      G_CALLBACK (&Application::activate_trampoline),
                      this);
  }

  BobguiApplication *native () const
  {
    return app_.get ();
  }

  void on_activate (ActivateHandler handler)
  {
    on_activate_ = std::move (handler);
  }

  int run (int argc, char **argv)
  {
    return g_application_run (G_APPLICATION (app_.get ()), argc, argv);
  }

private:
  static void activate_trampoline (BobguiApplication *, gpointer user_data)
  {
    Application *self = static_cast<Application *> (user_data);

    if (self->on_activate_)
      self->on_activate_ (*self);
  }

  ObjectHandle<BobguiApplication> app_;
  ActivateHandler on_activate_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
