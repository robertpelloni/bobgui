/* bobgui/modules/chart/bobguichart.h */
#ifndef BOBGUI_CHART_H
#define BOBGUI_CHART_H

#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Reactive Chart Engine (Better than Qt Charts / JavaFX Charts) */
typedef enum {
  BOBGUI_CHART_TYPE_LINE,
  BOBGUI_CHART_TYPE_BAR,
  BOBGUI_CHART_TYPE_PIE,
  BOBGUI_CHART_TYPE_SCATTER,
  BOBGUI_CHART_TYPE_RADAR
} BobguiChartType;

#define BOBGUI_TYPE_CHART_VIEW (bobgui_chart_view_get_type ())
G_DECLARE_FINAL_TYPE (BobguiChartView, bobgui_chart_view, BOBGUI, CHART_VIEW, BobguiWidget)

BobguiChartView * bobgui_chart_view_new (BobguiChartType type);

/* Data Series Management (Fully Integrated with BobguiData) */
void bobgui_chart_view_add_series (BobguiChartView *self, 
                                  const char *name, 
                                  GList *data_points);

/* Cinematic Transitions (Better than standard static charts) */
void bobgui_chart_view_animate_to_data (BobguiChartView *self, 
                                       GList *new_data_points, 
                                       double duration_ms);

/* Interactive Elements (Parity with high-end BI tools) */
void bobgui_chart_view_set_interactive (BobguiChartView *self, gboolean interactive);

G_END_DECLS

#endif /* BOBGUI_CHART_H */
