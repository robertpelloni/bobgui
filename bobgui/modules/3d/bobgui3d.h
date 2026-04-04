/* bobgui/3d/bobgui3d.h */
#ifndef BOBGUI_3D_H
#define BOBGUI_3D_H

#include <graphene.h>
#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* 3D Scene Graph (JavaFX/Qt Parity) */
#define BOBGUI_TYPE_3D_NODE (bobgui_3d_node_get_type ())
G_DECLARE_DERIVABLE_TYPE (Bobgui3dNode, bobgui_3d_node, BOBGUI, 3D_NODE, GObject)

Bobgui3dNode * bobgui_3d_node_new (void);
void           bobgui_3d_node_add_child (Bobgui3dNode *parent, Bobgui3dNode *child);
void           bobgui_3d_node_set_transform (Bobgui3dNode *self, graphene_matrix_t *m);

/* Mesh Handling (ImGui/Qt Parity) */
typedef struct _Bobgui3dMesh Bobgui3dMesh;
Bobgui3dMesh * bobgui_3d_mesh_new_sphere (float radius);
Bobgui3dMesh * bobgui_3d_mesh_new_cube (float size);
void           bobgui_3d_node_set_mesh (Bobgui3dNode *self, Bobgui3dMesh *mesh);

/* Materials and Shaders (Qt6/ImGui Parity) */
typedef struct _Bobgui3dMaterial Bobgui3dMaterial;
Bobgui3dMaterial * bobgui_3d_material_new_phong (graphene_vec3_t *diffuse_color);
void               bobgui_3d_node_set_material (Bobgui3dNode *self, Bobgui3dMaterial *material);

/* Camera (JavaFX/Qt Parity) */
typedef struct _Bobgui3dCamera Bobgui3dCamera;
Bobgui3dCamera * bobgui_3d_camera_new (void);
void             bobgui_3d_camera_set_projection (Bobgui3dCamera *self, graphene_matrix_t *m);

/* bobgui-3d Viewer Widget (Parity with Qt3DView) */
#define BOBGUI_TYPE_3D_VIEW (bobgui_3d_view_get_type ())
G_DECLARE_FINAL_TYPE (Bobgui3dView, bobgui_3d_view, BOBGUI, 3D_VIEW, BobguiWidget)

Bobgui3dView * bobgui_3d_view_new (Bobgui3dNode *root_node, Bobgui3dCamera *camera);

G_END_DECLS

#endif /* BOBGUI_3D_H */
