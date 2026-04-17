#pragma once

#include <bobgui/cpp/module.hpp>
#include <bobgui/cpp/system.hpp>
#include <memory>
#include <string>

namespace bobtk {
namespace module {

// The System Pillar interface acts as the service registry for OS/Hardware/Low-level modules
class SystemPillar : public Module {
public:
    SystemPillar() : Module("System", "1.0.0") {}

    // Input / HID Subsystem
    std::shared_ptr<system::InputManager> getInputManager() {
        return system::InputManager::getDefault();
    }

    // OS / Window Manager Subsystem
    std::shared_ptr<system::VirtualOs> createVirtualOs() {
        return std::make_shared<system::VirtualOs>();
    }

    // IPC Subsystem
    std::shared_ptr<system::IpcManager> createIpcManager(const std::string& namespaceId) {
        return std::make_shared<system::IpcManager>(namespaceId);
    }

    // Virtual File System
    std::shared_ptr<system::VFS> getVFS() {
        return system::VFS::getDefault();
    }

    // Shell / Desktop Environment
    std::shared_ptr<system::ShellManager> getShellManager() {
        return system::ShellManager::getDefault();
    }

    // IoT / Hardware Abstraction
    std::shared_ptr<system::IotManager> getIotManager() {
        return system::IotManager::getDefault();
    }

    // Omni Runtime (WASM/JIT)
    std::shared_ptr<system::OmniRuntime> getOmniRuntime() {
        return system::OmniRuntime::getDefault();
    }

    // Package Management
    std::shared_ptr<system::PackageManager> getPackageManager() {
        return system::PackageManager::getDefault();
    }

    // Plugin Manager
    std::shared_ptr<system::PluginManager> createPluginManager(const std::string& searchPath) {
        return std::make_shared<system::PluginManager>(searchPath);
    }

    // Security
    std::shared_ptr<system::SecureEntry> createSecureEntry() {
        return std::make_shared<system::SecureEntry>();
    }

    // Live Coding Context
    std::shared_ptr<system::LiveContext> createLiveContext(const std::string& modulePath) {
        return std::make_shared<system::LiveContext>(modulePath);
    }

    // Machine Vision AI
    std::shared_ptr<system::VisionContext> getVisionContext() {
        return system::VisionContext::getDefault();
    }

protected:
    bool onInitialize() override {
        // Initialize underlying C libraries
        return true;
    }

    bool onStart() override {
        return true;
    }

    bool onStop() override {
        return true;
    }
};

} // namespace module
} // namespace bobtk
