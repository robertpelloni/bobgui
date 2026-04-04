/* bobgui/modules/test/bobguitest.h */
#ifndef BOBGUI_TEST_H
#define BOBGUI_TEST_H

#include <bobgui/bobgui.h>
#include <bobgui/modules/brain/bobguibrain.h>

G_BEGIN_DECLS

/* AI-Driven Test Engine (Better than standard Unit Tests) */
#define BOBGUI_TYPE_TEST_RUNNER (bobgui_test_runner_get_type ())
G_DECLARE_FINAL_TYPE (BobguiTestRunner, bobgui_test_runner, BOBGUI, TEST_RUNNER, GObject)

BobguiTestRunner * bobgui_test_runner_new (BobguiWidget *root);

/* Autonomous Monkey Testing (Using BobguiBrain to find crashes) */
void bobgui_test_runner_run_monkey (BobguiTestRunner *self, 
                                   int duration_sec, 
                                   GAsyncReadyCallback callback);

/* Automated Visual Regression (AI-based comparison) */
void bobgui_test_runner_take_baseline (BobguiTestRunner *self, 
                                      const char *test_id);
void bobgui_test_runner_compare (BobguiTestRunner *self, 
                               const char *test_id, 
                               GAsyncReadyCallback callback);

/* Recorded Action Replay (Better than standard UI drivers) */
void bobgui_test_runner_load_replay (BobguiTestRunner *self, const char *path);
void bobgui_test_runner_play (BobguiTestRunner *self, GAsyncReadyCallback callback);

G_END_DECLS

#endif /* BOBGUI_TEST_H */
