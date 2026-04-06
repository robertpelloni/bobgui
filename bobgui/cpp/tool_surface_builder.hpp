#ifndef BOBGUI_CPP_TOOL_SURFACE_BUILDER_HPP
#define BOBGUI_CPP_TOOL_SURFACE_BUILDER_HPP

#include <bobgui/bobgui.h>

#include "action_registry.hpp"
#include "tool_surface.hpp"

#include <string>

namespace bobgui {
namespace cpp {

class ToolSurfaceBuilder
{
public:
  explicit ToolSurfaceBuilder (ActionRegistry &registry)
  : registry_ (registry)
  {
  }

  BobguiWidget *build_widget (const ToolSurfaceModel &model)
  {
    BobguiWidget *root = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 8);

    for (std::vector<ToolSurfaceModel::ToolSection>::const_iterator section = model.sections ().begin ();
         section != model.sections ().end ();
         ++section)
      {
        BobguiWidget *section_box = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 4);
        BobguiWidget *section_label = bobgui_label_new (section->title.c_str ());
        BobguiWidget *items_box = bobgui_box_new (BOBGUI_ORIENTATION_HORIZONTAL, 4);

        bobgui_label_set_xalign (BOBGUI_LABEL (section_label), 0.0f);
        bobgui_box_append (BOBGUI_BOX (section_box), section_label);

        for (std::vector<ToolSurfaceModel::ToolItem>::const_iterator item = section->items.begin ();
             item != section->items.end ();
             ++item)
          bobgui_box_append (BOBGUI_BOX (items_box), build_button (*item));

        bobgui_box_append (BOBGUI_BOX (section_box), items_box);
        bobgui_box_append (BOBGUI_BOX (root), section_box);
      }

    return root;
  }

private:
  struct ButtonBinding
  {
    ActionRegistry *registry;
    std::string action_id;
  };

  static void on_button_clicked (BobguiButton *button,
                                 gpointer      user_data)
  {
    ButtonBinding *binding = static_cast<ButtonBinding *> (user_data);

    (void) button;

    if (binding->registry != NULL)
      binding->registry->activate (binding->action_id.c_str ());
  }

  static void destroy_binding (gpointer data,
                               GClosure *closure)
  {
    (void) closure;
    delete static_cast<ButtonBinding *> (data);
  }

  BobguiWidget *build_button (const ToolSurfaceModel::ToolItem &item)
  {
    ButtonBinding *binding = new ButtonBinding;
    BobguiWidget *button;
    std::string label = item.title;

    binding->registry = &registry_;
    binding->action_id = item.action_id;

    if (item.checkable && item.checked)
      label = std::string ("✓ ") + label;

    button = bobgui_button_new_with_label (label.c_str ());

    if (!item.icon_name.empty ())
      bobgui_button_set_icon_name (BOBGUI_BUTTON (button), item.icon_name.c_str ());

    g_signal_connect_data (button,
                           "clicked",
                           G_CALLBACK (&ToolSurfaceBuilder::on_button_clicked),
                           binding,
                           &ToolSurfaceBuilder::destroy_binding,
                           GConnectFlags (0));

    return button;
  }

  ActionRegistry &registry_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
