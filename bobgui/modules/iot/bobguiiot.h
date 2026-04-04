/* bobgui/modules/iot/bobguiiot.h */
#ifndef BOBGUI_IOT_H
#define BOBGUI_IOT_H

#include <glib-object.h>
#include <gio/gio.h>

G_BEGIN_DECLS

/* IoT Connectivity Hub (Better than Qt Bluetooth / Serial) */
#define BOBGUI_TYPE_IOT_MANAGER (bobgui_iot_manager_get_type ())
G_DECLARE_FINAL_TYPE (BobguiIotManager, bobgui_iot_manager, BOBGUI, IOT_MANAGER, GObject)

BobguiIotManager * bobgui_iot_manager_get_default (void);

/* Bluetooth Low Energy (BLE) API (Superior Parity) */
void bobgui_iot_ble_scan (BobguiIotManager *self, GAsyncReadyCallback callback);
void bobgui_iot_ble_connect (BobguiIotManager *self, const char *device_address);

/* Serial Port Communication (High-performance Async) */
typedef struct _BobguiSerialPort BobguiSerialPort;
BobguiSerialPort * bobgui_serial_port_new (const char *path);
void               bobgui_serial_port_open (BobguiSerialPort *self, int baud_rate);

/* NFC and Proximity (Better than standard toolkits) */
void bobgui_iot_nfc_wait_for_tag (BobguiIotManager *self, GAsyncReadyCallback callback);

G_END_DECLS

#endif /* BOBGUI_IOT_H */
