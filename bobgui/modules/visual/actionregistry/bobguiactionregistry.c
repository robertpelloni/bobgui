#include "bobguiactionregistry.h"
#include "bobguicommandpalette.h"

typedef struct
{
  char *id;
  char *title;
  char *subtitle;
  BobguiActionRegistryFunc callback;
  gpointer user_data;
} BobguiActionRegistryItem;

struct _BobguiActionRegistry
{
  GObject parent_instance;
  GPtrArray *items;
};

G_DEFINE_TYPE (BobguiActionRegistry, bobgui_action_registry, G_TYPE_OBJECT)

static void
bobgui_action_registry_item_free (BobguiActionRegistryItem *item)
{
  g_free (item->id);
  g_free (item->title);
  g_free (item->subtitle);
  g_free (item);
}

static void
bobgui_action_registry_dispose (GObject *object)
{
  BobguiActionRegistry *self = BOBGUI_ACTION_REGISTRY (object);

  g_clear_pointer (&self->items, g_ptr_array_unref);

  G_OBJECT_CLASS (bobgui_action_registry_parent_class)->dispose (object);
}

static void
bobgui_action_registry_class_init (BobguiActionRegistryClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->dispose = bobgui_action_registry_dispose;
}

static void
bobgui_action_registry_init (BobguiActionRegistry *self)
{
  self->items = g_ptr_array_new_with_free_func ((GDestroyNotify) bobgui_action_registry_item_free);
}

BobguiActionRegistry *
bobgui_action_registry_new (void)
{
  return g_object_new (BOBGUI_TYPE_ACTION_REGISTRY, NULL);
}

void
bobgui_action_registry_add (BobguiActionRegistry      *self,
                            const char                *action_id,
                            const char                *title,
                            const char                *subtitle,
                            BobguiActionRegistryFunc   callback,
                            gpointer                   user_data)
{
  BobguiActionRegistryItem *item;

  g_return_if_fail (BOBGUI_IS_ACTION_REGISTRY (self));
  g_return_if_fail (action_id != NULL);

  item = g_new0 (BobguiActionRegistryItem, 1);
  item->id = g_strdup (action_id);
  item->title = g_strdup (title);
  item->subtitle = g_strdup (subtitle);
  item->callback = callback;
  item->user_data = user_data;
  g_ptr_array_add (self->items, item);
}

void
bobgui_action_registry_activate (BobguiActionRegistry *self,
                                 const char           *action_id)
{
  guint i;

  g_return_if_fail (BOBGUI_IS_ACTION_REGISTRY (self));
  g_return_if_fail (action_id != NULL);

  for (i = 0; i < self->items->len; i++)
    {
      BobguiActionRegistryItem *item = g_ptr_array_index (self->items, i);

      if (g_strcmp0 (item->id, action_id) == 0)
        {
          if (item->callback)
            item->callback (item->id, item->user_data);
          return;
        }
    }
}

void
bobgui_action_registry_populate_palette (BobguiActionRegistry *self,
                                         BobguiCommandPalette *palette)
{
  guint i;

  g_return_if_fail (BOBGUI_IS_ACTION_REGISTRY (self));
  g_return_if_fail (BOBGUI_IS_COMMAND_PALETTE (palette));

  bobgui_command_palette_clear (palette);

  for (i = 0; i < self->items->len; i++)
    {
      BobguiActionRegistryItem *item = g_ptr_array_index (self->items, i);
      bobgui_command_palette_add_command (palette,
                                          item->id,
                                          item->title,
                                          item->subtitle,
                                          item->callback,
                                          item->user_data);
    }
}
