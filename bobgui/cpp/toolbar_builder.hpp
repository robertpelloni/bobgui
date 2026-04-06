#ifndef BOBGUI_CPP_TOOLBAR_BUILDER_HPP
#define BOBGUI_CPP_TOOLBAR_BUILDER_HPP

#include <bobgui/bobgui.h>

#include "action_registry.hpp"
#include "tool_surface.hpp"

#include <string>

namespace bobgui {
namespace cpp {

class ToolbarBuilder
{
public:
  struct Options
  {
    bool show_section_labels;
    bool show_button_labels;
    bool show_shortcuts;
    bool show_checked_prefix;
    int section_spacing;
    int item_spacing;

    Options ()
    : show_section_labels (true),
      show_button_labels (true),
      show_shortcuts (false),
      show_checked_prefix (true),
      section_spacing (8),
      item_spacing (4)
    {
    }
  };

  explicit ToolbarBuilder (ActionRegistry &registry)
  : registry_ (registry)
  {
  }

  BobguiWidget *build_widget (const ToolSurfaceModel &model,
                              const Options          &options = Options ())
  {
    BobguiWidget *root = bobgui_box_new (BOBGUI_ORIENTATION_HORIZONTAL, options.section_spacing);

    for (std::vector<ToolSurfaceModel::ToolSection>::const_iterator section = model.sections ().begin ();
         section != model.sections ().end ();
         ++section)
      {
        BobguiWidget *section_box = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, options.item_spacing);
        BobguiWidget *items_box = bobgui_box_new (BOBGUI_ORIENTATION_HORIZONTAL, options.item_spacing);

        if (options.show_section_labels)
          {
            BobguiWidget *section_label = bobgui_label_new (section->title.c_str ());
            bobgui_label_set_xalign (BOBGUI_LABEL (section_label), 0.0f);
            bobgui_box_append (BOBGUI_BOX (section_box), section_label);
          }

        for (std::vector<ToolSurfaceModel::ToolItem>::const_iterator item = section->items.begin ();
             item != section->items.end ();
             ++item)
          bobgui_box_append (BOBGUI_BOX (items_box), build_button (*item, options));

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

  BobguiWidget *build_button (const ToolSurfaceModel::ToolItem &item,
                              const Options                    &options)
  {
    ButtonBinding *binding = new ButtonBinding;
    BobguiWidget *button;
    std::string label;

    binding->registry = &registry_;
    binding->action_id = item.action_id;

    if (options.show_button_labels)
      label = item.title;
    else if (!item.icon_name.empty ())
      label = "";
    else
      label = item.title;

    if (options.show_shortcuts && !item.shortcut.empty ())
      {
        if (!label.empty ())
          label += " (" + item.shortcut + ")";
        else
          label = item.shortcut;
      }

    if (options.show_checked_prefix && item.checkable && item.checked && !label.empty ())
      label = std::string ("✓ ") + label;
    else if (options.show_checked_prefix && item.checkable && item.checked && label.empty ())
      label = "✓";

    button = bobgui_button_new_with_label (label.c_str ());

    if (!item.icon_name.empty ())
      bobgui_button_set_icon_name (BOBGUI_BUTTON (button), item.icon_name.c_str ());

    g_signal_connect_data (button,
                           "clicked",
                           G_CALLBACK (&ToolbarBuilder::on_button_clicked),
                           binding,
                           &ToolbarBuilder::destroy_binding,
                           GConnectFlags (0));

    return button;
  }

  ActionRegistry &registry_;
};

} /* namespace cpp */
} /* namespace bobgui */

#endif
