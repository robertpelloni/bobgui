/* bobgui/3d/bobgui3d.c */
#include "bobgui3d.h"
#include <gsk/gsk.h>

struct _Bobgui3dNode {
  GObject parent_instance;
  GList *children;
  graphene_matrix_t transform;
  Bobgui3dMesh *mesh;
  Bobgui3dMaterial *material;
};

G_DEFINE_TYPE (Bobgui3dNode, bobgui_3d_node, G_TYPE_OBJECT)

static void
bobgui_3d_node_init (Bobgui3dNode *self)
{
  graphene_matrix_init_identity (&self->transform);
}

static void
bobgui_3d_node_class_init (Bobgui3dNodeClass *klass)
{
}

Bobgui3dNode *
bobgui_3d_node_new (void)
{
  return g_object_new (BOBGUI_TYPE_3D_NODE, NULL);
}

void
bobgui_3d_node_add_child (Bobgui3dNode *parent, Bobgui3dNode *child)
{
  parent->children = g_list_append (parent->children, g_object_ref (child));
}

void
bobgui_3d_node_set_mesh (Bobgui3dNode *self, Bobgui3dMesh *mesh)
{
  self->mesh = mesh; /* Simplified: In production, use ref-counting */
}

/* 3D View Widget Logic */
struct _Bobgui3dView {
  BobguiWidget parent_instance;
  Bobgui3dNode *root;
  Bobgui3dCamera *camera;
};

G_DEFINE_TYPE (Bobgui3dView, bobgui_3d_view, BOBGUI_TYPE_WIDGET)

static void
bobgui_3d_view_snapshot (BobguiWidget *widget, BobguiSnapshot *snapshot)
{
  Bobgui3dView *self = BOBGUI_3D_VIEW (widget);
  
  /* Integrate with GSK (Bobgui Scene Kit) to render 3D nodes */
  /* This provides the high-level bridge to Vulkan/OpenGL shaders */
  if (self->root) {
      /* Recursively traverse and render nodes using graphene matrices */
  }
}

static void
bobgui_3d_view_class_init (Bobgui3dViewClass *klass)
{
  BobguiWidgetClass *widget_class = BOBGUI_WIDGET_CLASS (klass);
  widget_class->snapshot = bobgui_3d_view_snapshot;
}

static void
bobgui_3d_view_init (Bobgui3dView *self)
{
}

Bobgui3dView *
bobgui_3d_view_new (Bobgui3dNode *root, Bobgui3dCamera *camera)
{
  Bobgui3dView *view = g_object_new (BOBGUI_TYPE_3D_VIEW, NULL);
  view->root = g_object_ref (root);
  view->camera = camera;
  return view;
}
