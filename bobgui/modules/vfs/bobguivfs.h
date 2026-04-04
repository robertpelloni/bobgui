/* bobgui/modules/vfs/bobguivfs.h */
#ifndef BOBGUI_VFS_H
#define BOBGUI_VFS_H

#include <gio/gio.h>

G_BEGIN_DECLS

/* Universal Virtual File System (Better than standard GIO/Stdio) */
#define BOBGUI_TYPE_VFS (bobgui_vfs_get_type ())
G_DECLARE_FINAL_TYPE (BobguiVFS, bobgui_vfs, BOBGUI, VFS, GObject)

BobguiVFS * bobgui_vfs_get_default (void);

/* Transparent Mounting (Unmatched Parity & Security) */
void bobgui_vfs_mount_zip (BobguiVFS *self, const char *zip_path, const char *mount_point);
void bobgui_vfs_mount_s3  (BobguiVFS *self, const char *bucket_name, const char *mount_point);
void bobgui_vfs_mount_encrypted (BobguiVFS *self, const char *image_path, const char *mount_point, const char *key);

/* Unified Access (Superior to standard POSIX calls) */
GInputStream * bobgui_vfs_read_async (BobguiVFS *self, const char *vpath, GAsyncReadyCallback callback);
void            bobgui_vfs_write_async (BobguiVFS *self, const char *vpath, GBytes *data, GAsyncReadyCallback callback);

/* Automated Caching (Better than standard manual caching) */
void bobgui_vfs_set_cache_policy (BobguiVFS *self, int size_mb, int ttl_sec);

G_END_DECLS

#endif /* BOBGUI_VFS_H */
