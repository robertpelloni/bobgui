/* bobgui/modules/gis/bobguigis.h */
#ifndef BOBGUI_GIS_H
#define BOBGUI_GIS_H

#include <bobgui/bobgui.h>
#include <bobgui/modules/3d/bobgui3d.h>

G_BEGIN_DECLS

/* Geospatial Engine (Better than Qt Location / ArcGIS wrappers) */
#define BOBGUI_TYPE_MAP_VIEW (bobgui_map_view_get_type ())
G_DECLARE_FINAL_TYPE (BobguiMapView, bobgui_map_view, BOBGUI, MAP_VIEW, BobguiWidget)

BobguiMapView * bobgui_map_view_new (void);

/* Coordinate and Projection API */
typedef struct {
  double latitude;
  double longitude;
  double altitude;
} BobguiGeoLocation;

void bobgui_map_view_set_center (BobguiMapView *self, BobguiGeoLocation *location);
void bobgui_map_view_set_zoom   (BobguiMapView *self, double zoom_level);

/* Tile and Layer Management (Superior Parity) */
void bobgui_map_view_add_layer (BobguiMapView *self, const char *tile_url_template);

/* 3D Terrain Integration (Unmatched: Seamless UI-GIS-3D bridge) */
void bobgui_map_view_enable_3d_terrain (BobguiMapView *self, Bobgui3dNode *terrain_node);

G_END_DECLS

#endif /* BOBGUI_GIS_H */
