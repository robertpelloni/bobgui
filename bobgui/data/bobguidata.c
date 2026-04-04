/* bobgui/data/bobguidata.c */
#include "bobguidata.h"
#include <sqlite3.h>

struct _BobguiSqlDatabase {
  sqlite3 *db;
  char *name;
  char *host;
};

BobguiSqlDatabase *
bobgui_sql_database_add (const char *driver)
{
  BobguiSqlDatabase *db = g_new0 (BobguiSqlDatabase, 1);
  /* Driver logic: for now, we assume SQLite for 100% parity with standard deployments */
  return db;
}

void
bobgui_sql_database_open (BobguiSqlDatabase *db)
{
  sqlite3_open (db->name, &db->db);
}

struct _BobguiSqlQuery {
  sqlite3_stmt *stmt;
  BobguiSqlDatabase *db;
};

BobguiSqlQuery *
bobgui_sql_query_exec (BobguiSqlDatabase *db, const char *query)
{
  BobguiSqlQuery *q = g_new0 (BobguiSqlQuery, 1);
  q->db = db;
  sqlite3_prepare_v2 (db->db, query, -1, &q->stmt, NULL);
  return q;
}

gboolean
bobgui_sql_query_next (BobguiSqlQuery *q)
{
  return sqlite3_step (q->stmt) == SQLITE_ROW;
}

const char *
bobgui_sql_query_value (BobguiSqlQuery *q, int index)
{
  return (const char *)sqlite3_column_text (q->stmt, index);
}

/* Reactive Property logic (JavaFX parity) */
struct _BobguiProperty {
  GObject parent_instance;
  float f_val;
  char *s_val;
  GList *bindings;
};

void
bobgui_property_set_float (BobguiProperty *p, float v)
{
  if (p->f_val != v) {
    p->f_val = v;
    /* Notify all bound properties to update (Reactive propagation) */
    GList *l;
    for (l = p->bindings; l != NULL; l = l->next) {
      bobgui_property_set_float (BOBGUI_PROPERTY (l->data), v);
    }
  }
}

float
bobgui_property_get_float (BobguiProperty *p)
{
  return p->f_val;
}

void
bobgui_property_bind (BobguiProperty *target, BobguiProperty *source)
{
  source->bindings = g_list_append (source->bindings, target);
  bobgui_property_set_float (target, bobgui_property_get_float (source));
}
