/* bobgui/modules/quantum/bobguiquantum.h */
#ifndef BOBGUI_QUANTUM_H
#define BOBGUI_QUANTUM_H

#include <glib-object.h>

G_BEGIN_DECLS

/* Lock-free Task Orchestration (Better than QtConcurrent) */
#define BOBGUI_TYPE_QUANTUM_SCHEDULER (bobgui_quantum_scheduler_get_type ())
G_DECLARE_FINAL_TYPE (BobguiQuantumScheduler, bobgui_quantum_scheduler, BOBGUI, QUANTUM_SCHEDULER, GObject)

BobguiQuantumScheduler * bobgui_quantum_scheduler_get_default (void);

/* Quantum Task API (Real-time safe, non-blocking) */
typedef gpointer (*BobguiQuantumTaskFunc) (gpointer data);

void bobgui_quantum_execute (BobguiQuantumScheduler *self, 
                            BobguiQuantumTaskFunc func, 
                            gpointer data,
                            GAsyncReadyCallback callback);

/* Parallel Foreach (Superior Parity with Qt) */
void bobgui_quantum_foreach (BobguiQuantumScheduler *self, 
                            GList *items, 
                            BobguiQuantumTaskFunc func,
                            GAsyncReadyCallback callback);

/* UI/Audio Synchronization (Exclusive: No-jank guarantee) */
void bobgui_quantum_sync_to_frame (BobguiQuantumScheduler *self, GCallback callback);

G_END_DECLS

#endif /* BOBGUI_QUANTUM_H */
