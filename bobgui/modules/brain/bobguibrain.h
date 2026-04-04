/* bobgui/brain/bobguibrain.h */
#ifndef BOBGUI_BRAIN_H
#define BOBGUI_BRAIN_H

#include <glib-object.h>
#include <bobgui/bobgui.h>

G_BEGIN_DECLS

/* Integrated ML Inference (ONNX/TF) */
#define BOBGUI_TYPE_BRAIN_MODEL (bobgui_brain_model_get_type ())
G_DECLARE_FINAL_TYPE (BobguiBrainModel, bobgui_brain_model, BOBGUI, BRAIN_MODEL, GObject)

BobguiBrainModel * bobgui_brain_model_load (const char *path);

/* High-level Predictive UI (Unmatched Parity) */
void bobgui_brain_predict_layout (BobguiBrainModel *self, 
                                  BobguiWidget *root, 
                                  GAsyncReadyCallback callback);

/* Accessibility/Voice Inference (Better than standard Screen Readers) */
void bobgui_brain_voice_to_action (BobguiBrainModel *self, 
                                   float *audio_buffer, 
                                   int samples);

/* Smart Input Completion (Better than simple QCompleter) */
void bobgui_brain_predict_input (BobguiBrainModel *self, 
                                 BobguiEntry *entry);

G_END_DECLS

#endif /* BOBGUI_BRAIN_H */
