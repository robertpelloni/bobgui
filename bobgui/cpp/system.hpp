#pragma once

#include <bobgui/bobgui.h>
#include <bobgui/cpp/object_handle.hpp>
#include <bobgui/cpp/widget.hpp>
#include <string>
#include <memory>
#include <vector>

namespace bobtk {
namespace system {

// ---------------------------------------------------------
// INPUT SUBSYSTEM (HID, VR, Haptics)
// ---------------------------------------------------------

class InputManager : public core::ObjectHandle<BobguiInputManager> {
public:
    static std::shared_ptr<InputManager> getDefault() {
        return std::shared_ptr<InputManager>(new InputManager(bobgui_input_manager_get_default()));
    }

    void scanDevices() {
        bobgui_input_scan_devices(handle());
    }

    float getAxisState(int deviceId, int axis) {
        float value = 0.0f;
        bobgui_input_get_axis_state(handle(), deviceId, axis, &value);
        return value;
    }

    void playHaptic(int deviceId, const std::string& patternId, float intensity) {
        bobgui_input_play_haptic(handle(), deviceId, patternId.c_str(), intensity);
    }

    void captureRaw(int deviceId, GAsyncReadyCallback callback, gpointer userData) {
        bobgui_input_capture_raw(handle(), deviceId, callback, userData);
    }

private:
    InputManager(BobguiInputManager* handle) : core::ObjectHandle<BobguiInputManager>(handle) {}
};

// ---------------------------------------------------------
// OS / WINDOW MANAGER SUBSYSTEM
// ---------------------------------------------------------

class VirtualOs : public Widget {
public:
    VirtualOs() : Widget(bobgui_virtual_os_new()) {}

    void launchApp(Widget& appRoot, const std::string& title) {
        bobgui_virtual_os_launch_app(BOBGUI_VIRTUAL_OS(handle()), BOBGUI_WIDGET(appRoot.handle()), title.c_str());
    }

    void setWorkspace(int index) {
        bobgui_virtual_os_set_workspace(BOBGUI_VIRTUAL_OS(handle()), index);
    }

    void killApp(Widget& appRoot) {
        bobgui_virtual_os_kill_app(BOBGUI_VIRTUAL_OS(handle()), BOBGUI_WIDGET(appRoot.handle()));
    }

    void showTaskbar(bool show) {
        bobgui_virtual_os_show_taskbar(BOBGUI_VIRTUAL_OS(handle()), show ? TRUE : FALSE);
    }
};

// ---------------------------------------------------------
// IPC SUBSYSTEM
// ---------------------------------------------------------

class IpcManager : public core::ObjectHandle<BobguiIpcManager> {
public:
    explicit IpcManager(const std::string& namespaceId)
        : core::ObjectHandle<BobguiIpcManager>(bobgui_ipc_manager_new(namespaceId.c_str())) {}

    void sendCommand(const std::string& targetProcess, uint32_t cmdId, GBytes* payload) {
        bobgui_ipc_send_command(handle(), targetProcess.c_str(), cmdId, payload);
    }

    void shareWidgetState(Widget& sourceWidget, const std::string& stateId) {
        bobgui_ipc_share_widget_state(handle(), BOBGUI_WIDGET(sourceWidget.handle()), stateId.c_str());
    }
};

// ---------------------------------------------------------
// VIRTUAL FILE SYSTEM
// ---------------------------------------------------------

class VFS : public core::ObjectHandle<BobguiVFS> {
public:
    static std::shared_ptr<VFS> getDefault() {
        return std::shared_ptr<VFS>(new VFS(bobgui_vfs_get_default()));
    }

private:
    VFS(BobguiVFS* handle) : core::ObjectHandle<BobguiVFS>(handle) {}
};

// ---------------------------------------------------------
// SHELL / DESKTOP ENVIORNMENT SUBSYSTEM
// ---------------------------------------------------------

class ShellManager : public core::ObjectHandle<BobguiShellManager> {
public:
    static std::shared_ptr<ShellManager> getDefault() {
        return std::shared_ptr<ShellManager>(new ShellManager(bobgui_shell_manager_get_default()));
    }

    void setProgress(double fraction) {
        bobgui_shell_set_progress(handle(), fraction);
    }

private:
    ShellManager(BobguiShellManager* handle) : core::ObjectHandle<BobguiShellManager>(handle) {}
};

// ---------------------------------------------------------
// IOT / HARDWARE ABSTRACTION
// ---------------------------------------------------------

class IotManager : public core::ObjectHandle<BobguiIotManager> {
public:
    static std::shared_ptr<IotManager> getDefault() {
        return std::shared_ptr<IotManager>(new IotManager(bobgui_iot_manager_get_default()));
    }

private:
    IotManager(BobguiIotManager* handle) : core::ObjectHandle<BobguiIotManager>(handle) {}
};

// ---------------------------------------------------------
// OMNI RUNTIME (WASM / JIT ENV)
// ---------------------------------------------------------

class OmniRuntime : public core::ObjectHandle<BobguiOmniRuntime> {
public:
    static std::shared_ptr<OmniRuntime> getDefault() {
        return std::shared_ptr<OmniRuntime>(new OmniRuntime(bobgui_omni_runtime_get_default()));
    }

    void runApplication(const std::string& wasmPayload, const std::string& entryPoint) {
        bobgui_omni_run_application(handle(), wasmPayload.c_str(), entryPoint.c_str());
    }

    void optimizeJit() {
        bobgui_omni_optimize_jit(handle());
    }

private:
    OmniRuntime(BobguiOmniRuntime* handle) : core::ObjectHandle<BobguiOmniRuntime>(handle) {}
};

// ---------------------------------------------------------
// PACKAGE MANAGEMENT
// ---------------------------------------------------------

class PackageManager : public core::ObjectHandle<BobguiPackageManager> {
public:
    static std::shared_ptr<PackageManager> getDefault() {
        return std::shared_ptr<PackageManager>(new PackageManager(bobgui_package_manager_get_default()));
    }

private:
    PackageManager(BobguiPackageManager* handle) : core::ObjectHandle<BobguiPackageManager>(handle) {}
};

// ---------------------------------------------------------
// PLUGIN MANAGER
// ---------------------------------------------------------

class PluginManager : public core::ObjectHandle<BobguiPluginManager> {
public:
    explicit PluginManager(const std::string& searchPath)
        : core::ObjectHandle<BobguiPluginManager>(bobgui_plugin_manager_new(searchPath.c_str())) {}
};

// ---------------------------------------------------------
// SECURITY
// ---------------------------------------------------------

class SecureEntry : public core::ObjectHandle<BobguiSecureEntry> {
public:
    SecureEntry() : core::ObjectHandle<BobguiSecureEntry>(bobgui_secure_entry_new()) {}
};

// ---------------------------------------------------------
// LIVE CODING CONTEXT
// ---------------------------------------------------------

class LiveContext : public core::ObjectHandle<BobguiLiveContext> {
public:
    explicit LiveContext(const std::string& modulePath)
        : core::ObjectHandle<BobguiLiveContext>(bobgui_live_context_new(modulePath.c_str())) {}
};

// ---------------------------------------------------------
// MACHINE VISION / PREDICTION AI
// ---------------------------------------------------------

class VisionContext : public core::ObjectHandle<BobguiVisionContext> {
public:
    static std::shared_ptr<VisionContext> getDefault() {
        return std::shared_ptr<VisionContext>(new VisionContext(bobgui_vision_context_get_default()));
    }

    void analyzeUi(Widget& root) {
        bobgui_vision_analyze_ui(handle(), BOBGUI_WIDGET(root.handle()));
    }

    void predictNextAction(Widget& currentFocus, GAsyncReadyCallback callback) {
        bobgui_vision_predict_next_action(handle(), BOBGUI_WIDGET(currentFocus.handle()), callback);
    }

    void processCameraFeed(int cameraId, GAsyncReadyCallback callback) {
        bobgui_vision_process_camera_feed(handle(), cameraId, callback);
    }

private:
    VisionContext(BobguiVisionContext* handle) : core::ObjectHandle<BobguiVisionContext>(handle) {}
};

} // namespace system
} // namespace bobtk
