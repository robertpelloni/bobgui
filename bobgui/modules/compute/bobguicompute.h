/* bobgui/modules/compute/bobguicompute.h */
#ifndef BOBGUI_COMPUTE_H
#define BOBGUI_COMPUTE_H

#include <glib-object.h>
#include <gdk/gdk.h>

G_BEGIN_DECLS

/* GPGPU Compute API (Better than standard UI logic) */
#define BOBGUI_TYPE_COMPUTE_CONTEXT (bobgui_compute_context_get_type ())
G_DECLARE_FINAL_TYPE (BobguiComputeContext, bobgui_compute_context, BOBGUI, COMPUTE_CONTEXT, GObject)

BobguiComputeContext * bobgui_compute_context_new (const char *backend);

/* Parallel Computation (Superior to standard CPU loops) */
void bobgui_compute_execute (BobguiComputeContext *ctx, 
                             const char *kernel_source, 
                             float *data_in, 
                             float *data_out, 
                             size_t size,
                             GAsyncReadyCallback callback);

/* Automated Texture Processing (Superior integration with GdkTexture) */
void bobgui_compute_apply_to_texture (BobguiComputeContext *ctx, 
                                     GdkTexture *texture, 
                                     const char *shader_source);

G_END_DECLS

#endif /* BOBGUI_COMPUTE_H */
