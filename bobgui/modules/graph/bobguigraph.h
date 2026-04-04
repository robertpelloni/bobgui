/* bobgui/modules/graph/bobguigraph.h */
#ifndef BOBGUI_GRAPH_H
#define BOBGUI_GRAPH_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Node Graph Engine (Better than Unreal Blueprints / Blender Nodes) */
#define BOBGUI_TYPE_GRAPH_NODE (bobgui_graph_node_get_type ())
G_DECLARE_DERIVABLE_TYPE (BobguiGraphNode, bobgui_graph_node, BOBGUI, GRAPH_NODE, GObject)

typedef struct _BobguiGraphPin BobguiGraphPin;

/* Graph Editor Widget */
#define BOBGUI_TYPE_GRAPH_VIEW (bobgui_graph_view_get_type ())
G_DECLARE_FINAL_TYPE (BobguiGraphView, bobgui_graph_view, BOBGUI, GRAPH_VIEW, BobguiWidget)

BobguiGraphView * bobgui_graph_view_new (void);

/* Node and Pin API */
void bobgui_graph_view_add_node (BobguiGraphView *view, BobguiGraphNode *node, double x, double y);
void bobgui_graph_view_connect  (BobguiGraphView *view, BobguiGraphPin *output, BobguiGraphPin *input);

/* Serialization (Standard in Bobgui) */
char * bobgui_graph_to_json (BobguiGraphView *view);
void   bobgui_graph_from_json (BobguiGraphView *view, const char *json);

G_END_DECLS

#endif /* BOBGUI_GRAPH_H */
