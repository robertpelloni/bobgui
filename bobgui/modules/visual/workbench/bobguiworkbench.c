#include "bobguiworkbench.h"

struct _BobguiWorkbench
{
  GObject parent_instance;
  BobguiApplicationWindow *window;
  BobguiHeaderBar *header_bar;
  BobguiBox *root_box;
  BobguiPaned *outer_paned;
  BobguiPaned *inner_paned;
  BobguiBox *header_actions;
  BobguiLabel *title_label;
  BobguiLabel *status_label;
  BobguiWidget *central;
  BobguiWidget *left_sidebar;
  BobguiWidget *right_sidebar;
};

G_DEFINE_TYPE (BobguiWorkbench, bobgui_workbench, G_TYPE_OBJECT)

static void
bobgui_workbench_dispose (GObject *object)
{
  BobguiWorkbench *self = BOBGUI_WORKBENCH (object);

  g_clear_object (&self->window);

  G_OBJECT_CLASS (bobgui_workbench_parent_class)->dispose (object);
}

static void
bobgui_workbench_class_init (BobguiWorkbenchClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->dispose = bobgui_workbench_dispose;
}

static void
bobgui_workbench_init (BobguiWorkbench *self)
{
}

BobguiWorkbench *
bobgui_workbench_new (BobguiApplication *application)
{
  BobguiWorkbench *self = g_object_new (BOBGUI_TYPE_WORKBENCH, NULL);
  BobguiWidget *title_box;

  self->window = g_object_new (BOBGUI_TYPE_APPLICATION_WINDOW,
                               "application", application,
                               NULL);

  self->header_bar = BOBGUI_HEADER_BAR (bobgui_header_bar_new ());
  self->header_actions = BOBGUI_BOX (bobgui_box_new (BOBGUI_ORIENTATION_HORIZONTAL, 6));
  self->title_label = BOBGUI_LABEL (bobgui_label_new ("Bobgui Workbench"));
  self->status_label = BOBGUI_LABEL (bobgui_label_new ("Ready"));
  self->root_box = BOBGUI_BOX (bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 0));
  self->outer_paned = BOBGUI_PANED (bobgui_paned_new (BOBGUI_ORIENTATION_HORIZONTAL));
  self->inner_paned = BOBGUI_PANED (bobgui_paned_new (BOBGUI_ORIENTATION_HORIZONTAL));

  title_box = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 0);
  bobgui_box_append (BOBGUI_BOX (title_box), BOBGUI_WIDGET (self->title_label));
  bobgui_header_bar_set_title_widget (self->header_bar, title_box);
  bobgui_header_bar_pack_end (self->header_bar, BOBGUI_WIDGET (self->header_actions));

  bobgui_box_append (self->root_box, BOBGUI_WIDGET (self->outer_paned));
  bobgui_box_append (self->root_box, BOBGUI_WIDGET (self->status_label));

  bobgui_paned_set_end_child (self->outer_paned, BOBGUI_WIDGET (self->inner_paned));
  bobgui_window_set_titlebar (BOBGUI_WINDOW (self->window), BOBGUI_WIDGET (self->header_bar));
  bobgui_window_set_child (BOBGUI_WINDOW (self->window), BOBGUI_WIDGET (self->root_box));

  return self;
}

BobguiWindow *
bobgui_workbench_get_window (BobguiWorkbench *self)
{
  g_return_val_if_fail (BOBGUI_IS_WORKBENCH (self), NULL);
  return BOBGUI_WINDOW (self->window);
}

BobguiWidget *
bobgui_workbench_get_content (BobguiWorkbench *self)
{
  g_return_val_if_fail (BOBGUI_IS_WORKBENCH (self), NULL);
  return BOBGUI_WIDGET (self->inner_paned);
}

void
bobgui_workbench_set_title (BobguiWorkbench *self,
                            const char      *title)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));

  bobgui_window_set_title (BOBGUI_WINDOW (self->window), title);
  bobgui_label_set_text (self->title_label, title);
}

void
bobgui_workbench_set_central (BobguiWorkbench *self,
                              BobguiWidget    *child)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));

  self->central = child;
  bobgui_paned_set_start_child (self->inner_paned, child);
}

void
bobgui_workbench_set_left_sidebar (BobguiWorkbench *self,
                                   BobguiWidget    *child)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));

  self->left_sidebar = child;
  bobgui_paned_set_start_child (self->outer_paned, child);
}

void
bobgui_workbench_set_right_sidebar (BobguiWorkbench *self,
                                    BobguiWidget    *child)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));

  self->right_sidebar = child;
  bobgui_paned_set_end_child (self->inner_paned, child);
}

void
bobgui_workbench_set_status (BobguiWorkbench *self,
                             const char      *message)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));
  bobgui_label_set_text (self->status_label, message);
}

void
bobgui_workbench_add_header_action (BobguiWorkbench                 *self,
                                    const char                      *label,
                                    BobguiWorkbenchActionCallback    callback,
                                    gpointer                         user_data)
{
  BobguiWidget *button;

  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));

  button = bobgui_button_new_with_label (label);
  if (callback)
    g_signal_connect (button, "clicked", G_CALLBACK (callback), user_data);
  bobgui_box_append (self->header_actions, button);
}

void
bobgui_workbench_present (BobguiWorkbench *self)
{
  g_return_if_fail (BOBGUI_IS_WORKBENCH (self));
  bobgui_window_present (BOBGUI_WINDOW (self->window));
}
