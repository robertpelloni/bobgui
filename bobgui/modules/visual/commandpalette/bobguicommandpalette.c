#include "bobguicommandpalette.h"

typedef struct
{
  char *id;
  char *title;
  char *subtitle;
  BobguiCommandPaletteFunc callback;
  gpointer user_data;
} BobguiCommandPaletteItem;

struct _BobguiCommandPalette
{
  GObject parent_instance;
  BobguiWindow *window;
  BobguiSearchEntry *search_entry;
  BobguiListBox *list_box;
  GPtrArray *items;
};

G_DEFINE_TYPE (BobguiCommandPalette, bobgui_command_palette, G_TYPE_OBJECT)

static void
bobgui_command_palette_item_free (BobguiCommandPaletteItem *item)
{
  g_free (item->id);
  g_free (item->title);
  g_free (item->subtitle);
  g_free (item);
}

static BobguiCommandPaletteItem *
bobgui_command_palette_item_from_row (BobguiListBoxRow *row)
{
  return g_object_get_data (G_OBJECT (row), "bobgui-command-palette-item");
}

static void
bobgui_command_palette_on_row_activated (BobguiListBox *box,
                                         BobguiListBoxRow *row,
                                         gpointer user_data)
{
  BobguiCommandPalette *self = BOBGUI_COMMAND_PALETTE (user_data);
  BobguiCommandPaletteItem *item = bobgui_command_palette_item_from_row (row);

  (void) box;

  if (item && item->callback)
    item->callback (item->id, item->user_data);

  bobgui_window_close (self->window);
}

static BobguiWidget *
bobgui_command_palette_build_row (BobguiCommandPaletteItem *item)
{
  BobguiWidget *row;
  BobguiWidget *box;
  BobguiWidget *title;
  BobguiWidget *subtitle;

  row = bobgui_list_box_row_new ();
  box = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 2);
  title = bobgui_label_new (item->title ? item->title : item->id);
  subtitle = bobgui_label_new (item->subtitle ? item->subtitle : "");

  bobgui_label_set_xalign (BOBGUI_LABEL (title), 0.0f);
  bobgui_label_set_xalign (BOBGUI_LABEL (subtitle), 0.0f);
  bobgui_box_append (BOBGUI_BOX (box), title);
  bobgui_box_append (BOBGUI_BOX (box), subtitle);
  bobgui_list_box_row_set_child (BOBGUI_LIST_BOX_ROW (row), box);
  g_object_set_data (G_OBJECT (row), "bobgui-command-palette-item", item);

  return row;
}

static gboolean
bobgui_command_palette_item_matches (BobguiCommandPaletteItem *item,
                                     const char               *query)
{
  char *id_lower;
  char *title_lower;
  char *subtitle_lower;
  char *query_lower;
  gboolean matches;

  if (query == NULL || *query == '\0')
    return TRUE;

  query_lower = g_utf8_strdown (query, -1);
  id_lower = g_utf8_strdown (item->id ? item->id : "", -1);
  title_lower = g_utf8_strdown (item->title ? item->title : "", -1);
  subtitle_lower = g_utf8_strdown (item->subtitle ? item->subtitle : "", -1);

  matches = strstr (id_lower, query_lower) != NULL ||
            strstr (title_lower, query_lower) != NULL ||
            strstr (subtitle_lower, query_lower) != NULL;

  g_free (query_lower);
  g_free (id_lower);
  g_free (title_lower);
  g_free (subtitle_lower);

  return matches;
}

static void
bobgui_command_palette_rebuild (BobguiCommandPalette *self)
{
  const char *query;
  guint i;

  bobgui_list_box_remove_all (self->list_box);
  query = bobgui_editable_get_text (BOBGUI_EDITABLE (self->search_entry));

  for (i = 0; i < self->items->len; i++)
    {
      BobguiCommandPaletteItem *item = g_ptr_array_index (self->items, i);

      if (bobgui_command_palette_item_matches (item, query))
        bobgui_list_box_append (self->list_box, bobgui_command_palette_build_row (item));
    }
}

static void
bobgui_command_palette_on_search_changed (BobguiSearchEntry     *entry,
                                          BobguiCommandPalette  *self)
{
  (void) entry;
  bobgui_command_palette_rebuild (self);
}

static void
bobgui_command_palette_dispose (GObject *object)
{
  BobguiCommandPalette *self = BOBGUI_COMMAND_PALETTE (object);

  g_clear_object (&self->window);
  if (self->items)
    {
      g_ptr_array_unref (self->items);
      self->items = NULL;
    }

  G_OBJECT_CLASS (bobgui_command_palette_parent_class)->dispose (object);
}

static void
bobgui_command_palette_class_init (BobguiCommandPaletteClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  object_class->dispose = bobgui_command_palette_dispose;
}

static void
bobgui_command_palette_init (BobguiCommandPalette *self)
{
  self->items = g_ptr_array_new_with_free_func ((GDestroyNotify) bobgui_command_palette_item_free);
}

BobguiCommandPalette *
bobgui_command_palette_new (BobguiApplication *application)
{
  BobguiCommandPalette *self = g_object_new (BOBGUI_TYPE_COMMAND_PALETTE, NULL);
  BobguiWidget *root;
  BobguiWidget *scroller;

  self->window = BOBGUI_WINDOW (g_object_new (BOBGUI_TYPE_APPLICATION_WINDOW,
                                              "application", application,
                                              NULL));
  bobgui_window_set_title (self->window, "Command Palette");
  bobgui_window_set_default_size (self->window, 560, 420);

  root = bobgui_box_new (BOBGUI_ORIENTATION_VERTICAL, 8);
  self->search_entry = BOBGUI_SEARCH_ENTRY (bobgui_search_entry_new ());
  self->list_box = BOBGUI_LIST_BOX (bobgui_list_box_new ());
  scroller = bobgui_scrolled_window_new ();

  bobgui_scrolled_window_set_child (BOBGUI_SCROLLED_WINDOW (scroller), BOBGUI_WIDGET (self->list_box));
  bobgui_box_append (BOBGUI_BOX (root), BOBGUI_WIDGET (self->search_entry));
  bobgui_box_append (BOBGUI_BOX (root), scroller);
  bobgui_window_set_child (self->window, root);

  g_signal_connect (self->list_box, "row-activated",
                    G_CALLBACK (bobgui_command_palette_on_row_activated), self);
  g_signal_connect (self->search_entry, "search-changed",
                    G_CALLBACK (bobgui_command_palette_on_search_changed), self);

  return self;
}

void
bobgui_command_palette_add_command (BobguiCommandPalette     *self,
                                    const char               *command_id,
                                    const char               *title,
                                    const char               *subtitle,
                                    BobguiCommandPaletteFunc  callback,
                                    gpointer                  user_data)
{
  BobguiCommandPaletteItem *item;

  g_return_if_fail (BOBGUI_IS_COMMAND_PALETTE (self));

  item = g_new0 (BobguiCommandPaletteItem, 1);
  item->id = g_strdup (command_id);
  item->title = g_strdup (title);
  item->subtitle = g_strdup (subtitle);
  item->callback = callback;
  item->user_data = user_data;

  g_ptr_array_add (self->items, item);
  bobgui_command_palette_rebuild (self);
}

void
bobgui_command_palette_attach_to_window (BobguiCommandPalette *self,
                                         BobguiWindow         *window)
{
  g_return_if_fail (BOBGUI_IS_COMMAND_PALETTE (self));
  g_return_if_fail (BOBGUI_IS_WINDOW (window));

  bobgui_window_set_transient_for (self->window, window);
  bobgui_window_set_modal (self->window, TRUE);
}

void
bobgui_command_palette_present (BobguiCommandPalette *self)
{
  g_return_if_fail (BOBGUI_IS_COMMAND_PALETTE (self));
  bobgui_window_present (self->window);
}
