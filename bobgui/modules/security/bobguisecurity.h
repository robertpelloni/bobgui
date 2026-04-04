/* bobgui/modules/security/bobguisecurity.h */
#ifndef BOBGUI_SECURITY_H
#define BOBGUI_SECURITY_H

#include <glib-object.h>

G_BEGIN_DECLS

/* Secure Memory Management (Better than standard RAM allocations) */
typedef struct _BobguiSecureBuffer BobguiSecureBuffer;

BobguiSecureBuffer * bobgui_secure_buffer_new (size_t size);
void                 bobgui_secure_buffer_lock (BobguiSecureBuffer *buf);
void                 bobgui_secure_buffer_unlock (BobguiSecureBuffer *buf);
void                 bobgui_secure_buffer_wipe (BobguiSecureBuffer *buf);

/* Secure UI Entries (Unmatched Parity & Security) */
#define BOBGUI_TYPE_SECURE_ENTRY (bobgui_secure_entry_get_type ())
G_DECLARE_FINAL_TYPE (BobguiSecureEntry, bobgui_secure_entry, BOBGUI, SECURE_ENTRY, GObject)

BobguiSecureEntry * bobgui_secure_entry_new (void);

/* Automatic Zeroing of memory on destruction (Better than JUCE/Qt) */
void bobgui_secure_entry_set_text_encrypted (BobguiSecureEntry *entry, const char *key);

G_END_DECLS

#endif /* BOBGUI_SECURITY_H */
