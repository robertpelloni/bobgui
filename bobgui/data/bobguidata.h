/* bobgui/data/bobguidata.h */
#ifndef BOBGUI_DATA_H
#define BOBGUI_DATA_H

#include <glib-object.h>

G_BEGIN_DECLS

/* SQL Database Management (Qt Parity) */
typedef struct _BobguiSqlDatabase BobguiSqlDatabase;

BobguiSqlDatabase * bobgui_sql_database_add (const char *driver);
void                bobgui_sql_database_set_host (BobguiSqlDatabase *db, const char *host);
void                bobgui_sql_database_set_database_name (BobguiSqlDatabase *db, const char *name);
void                bobgui_sql_database_open (BobguiSqlDatabase *db);

typedef struct _BobguiSqlQuery BobguiSqlQuery;
BobguiSqlQuery *    bobgui_sql_query_exec (BobguiSqlDatabase *db, const char *query);
gboolean            bobgui_sql_query_next (BobguiSqlQuery *q);
const char *        bobgui_sql_query_value (BobguiSqlQuery *q, int index);

/* Reactive Properties and Bindings (JavaFX Parity) */
typedef struct _BobguiProperty BobguiProperty;

BobguiProperty * bobgui_property_new_float (float init_value);
BobguiProperty * bobgui_property_new_string (const char *init_value);

void             bobgui_property_bind (BobguiProperty *target, BobguiProperty *source);
void             bobgui_property_bind_bidirectional (BobguiProperty *a, BobguiProperty *b);

float            bobgui_property_get_float (BobguiProperty *p);
void             bobgui_property_set_float (BobguiProperty *p, float v);

G_END_DECLS

#endif /* BOBGUI_DATA_H */
