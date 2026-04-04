/* bobgui/modules/spatial/bobguispatial.h */
#ifndef BOBGUI_SPATIAL_H
#define BOBGUI_SPATIAL_H

#include <bobgui/bobgui.h>
#include <graphene.h>

G_BEGIN_DECLS

/* Spatial Computing Engine (Better than Qt Quick 3D / OpenXR wrappers) */
#define BOBGUI_TYPE_SPATIAL_CONTEXT (bobgui_spatial_context_get_type ())
G_DECLARE_FINAL_TYPE (BobguiSpatialContext, bobgui_spatial_context, BOBGUI, SPATIAL_CONTEXT, GObject)

BobguiSpatialContext * bobgui_spatial_context_new (const char *runtime_name);

/* Projected UI (Any BobguiWidget can be a 3D Plane) */
void bobgui_spatial_project_widget (BobguiSpatialContext *ctx, 
                                   BobguiWidget *widget, 
                                   graphene_matrix_t *transform);

/* Immersive Hand/Controller Tracking (Superior Parity with Apple VisionOS) */
typedef struct _BobguiSpatialEvent BobguiSpatialEvent;
void bobgui_spatial_on_interaction (BobguiSpatialContext *ctx, 
                                   GCallback callback, 
                                   gpointer user_data);

G_END_DECLS

#endif /* BOBGUI_SPATIAL_H */
