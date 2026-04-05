#ifndef BOBGUI_CPP_BOBGUI_HPP
#define BOBGUI_CPP_BOBGUI_HPP

#include <bobgui/bobgui.h>
#include <bobgui/modules/visual/visual.h>

#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace bobgui {
namespace cpp {

template <typename T>
class ObjectHandle
{
public:
  explicit ObjectHandle (T *object = nullptr)
  : object_ (object)
  {
  }

  ~ObjectHandle ()
  {
    if (object_ != nullptr)
      g_object_unref (object_);
  }

  ObjectHandle (const ObjectHandle &) = delete;
  ObjectHandle &operator= (const ObjectHandle &) = delete;

  ObjectHandle (ObjectHandle &&other) noexcept
  : object_ (other.object_)
  {
    other.object_ = nullptr;
  }

  ObjectHandle &operator= (ObjectHandle &&other) noexcept
  {
    if (this != &other)
      {
        if (object_ != nullptr)
          g_object_unref (object_);
        object_ = other.object_;
        other.object_ = nullptr;
      }

    return *this;
  }

  T *get () const
  {
    return object_;
  }

  operator T *() const
  {
    return object_;
  }

private:
  T *object_;
};

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

class CommandPalette
{
public:
  explicit CommandPalette (Application &application)
  : palette_ (bobgui_command_palette_new (application.native ()))
  {
  }

  BobguiCommandPalette *native () const
  {
    return palette_.get ();
  }

  void set_pinned (const char *command_id,
                   bool        pinned)
  {
    bobgui_command_palette_set_pinned (palette_.get (), command_id, pinned);
  }

  void clear_history ()
  {
    bobgui_command_palette_clear_history (palette_.get ());
  }

private:
  ObjectHandle<BobguiCommandPalette> palette_;
};

class Workbench
{
public:
  typedef std::function<void(const std::string &)> CommandHandler;

  explicit Workbench (Application &application)
  : workbench_ (bobgui_workbench_new (application.native ()))
  {
  }

  BobguiWorkbench *native () const
  {
    return workbench_.get ();
  }

  BobguiWindow *window () const
  {
    return bobgui_workbench_get_window (workbench_.get ());
  }

  void set_title (const char *title)
  {
    bobgui_workbench_set_title (workbench_.get (), title);
  }

  void set_central (BobguiWidget *widget)
  {
    bobgui_workbench_set_central (workbench_.get (), widget);
  }

  void set_left_sidebar (BobguiWidget *widget)
  {
    bobgui_workbench_set_left_sidebar (workbench_.get (), widget);
  }

  void set_right_sidebar (BobguiWidget *widget)
  {
    bobgui_workbench_set_right_sidebar (workbench_.get (), widget);
  }

  void set_status (const char *message)
  {
    bobgui_workbench_set_status (workbench_.get (), message);
  }

  void set_action_registry (ActionRegistry &registry)
  {
    bobgui_workbench_set_action_registry (workbench_.get (), registry.native ());
  }

  void set_command_palette (CommandPalette &palette)
  {
    bobgui_workbench_set_command_palette (workbench_.get (), palette.native ());
  }

  void add_header_action_for_command (const char *label,
                                      const char *command_id)
  {
    bobgui_workbench_add_header_action_for_command (workbench_.get (), label, command_id);
  }

  void enable_menubar (bool enabled)
  {
    bobgui_workbench_enable_menubar (workbench_.get (), enabled);
  }

  void enable_toolbar (bool enabled)
  {
    bobgui_workbench_enable_toolbar (workbench_.get (), enabled);
  }

  void add_sectioned_command (const char *command_id,
                              const char *title,
                              const char *subtitle,
                              const char *section,
                              const char *category,
                              const char *shortcut,
                              const char *icon_name,
                              CommandHandler handler)
  {
    command_bindings_.push_back (std::unique_ptr<CommandBinding> (new CommandBinding));
    command_bindings_.back ()->handler = std::move (handler);

    bobgui_workbench_add_command_sectioned_visual (workbench_.get (),
                                                   command_id,
                                                   title,
                                                   subtitle,
                                                   section,
                                                   category,
                                                   shortcut,
                                                   icon_name,
                                                   &Workbench::command_trampoline,
                                                   command_bindings_.back ().get ());
  }

  void add_toggle_sectioned_command (const char *command_id,
                                     const char *title,
                                     const char *subtitle,
                                     const char *section,
                                     const char *category,
                                     const char *shortcut,
                                     const char *icon_name,
                                     bool        checked,
                                     CommandHandler handler)
  {
    command_bindings_.push_back (std::unique_ptr<CommandBinding> (new CommandBinding));
    command_bindings_.back ()->handler = std::move (handler);

    bobgui_workbench_add_toggle_command_sectioned_visual (workbench_.get (),
                                                          command_id,
                                                          title,
                                                          subtitle,
                                                          section,
                                                          category,
                                                          shortcut,
                                                          icon_name,
                                                          checked,
                                                          &Workbench::command_trampoline,
                                                          command_bindings_.back ().get ());
  }

  void present ()
  {
    bobgui_workbench_present (workbench_.get ());
  }

private:
  struct CommandBinding
  {
    CommandHandler handler;
  };

  static void command_trampoline (const char *command_id,
                                  gpointer    user_data)
  {
    CommandBinding *binding = static_cast<CommandBinding *> (user_data);

    if (binding->handler)
      binding->handler (command_id != nullptr ? std::string (command_id) : std::string ());
  }

  ObjectHandle<BobguiWorkbench> workbench_;
  std::vector<std::unique_ptr<CommandBinding> > command_bindings_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
