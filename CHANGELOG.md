# CHANGELOG

## [1.0.0] - 2024-04-10
### Added
- Submodule: Ultimate++ (https://github.com/ultimatepp/ultimatepp)
- Submodule: JUCE (https://github.com/juce-framework/JUCE)
- Comprehensive project documentation (`VISION.md`, `ROADMAP.md`, `TODO.md`, `MEMORY.md`, `DEPLOY.md`, `CHANGELOG.md`, `IDEAS.md`, `HANDOFF.md`, etc.).
- Agent instruction files for various LLMs.

### Changed
- Mass renaming: All instances of `gtk` and `bobgui` renamed to `bobtk` to signify the new direction and future of the project.

## [4.0.3] - Unreleased
### Added
- Implemented high-level C++ wrappers for Network subsystems (`bobtk::network::NetworkAccessManager`, `WebSocket`, `RemoteServer`, `RemoteClient`, `WebView`, `CloudContext`, `BlockchainManager`, `SyncEngine`).
- Implemented the `bobtk::module::NetworkPillar` interface to manage the creation and state of all connectivity-related subsystems within the core 6-pillar framework.
- Exported new C++ network classes through the master `bobgui.hpp` header.

## [4.0.4] - Unreleased
### Added
- Implemented high-level C++ wrappers for System subsystems (`bobtk::system::InputManager`, `VirtualOs`, `IpcManager`, `VFS`, `ShellManager`, `IotManager`, `OmniRuntime`, `PackageManager`, `PluginManager`, `SecureEntry`, `LiveContext`, `VisionContext`).
- Implemented the `bobtk::module::SystemPillar` interface to manage the creation and state of all OS, hardware, and low-level subsystems within the core 6-pillar framework.
- Exported new C++ system classes through the master `bobgui.hpp` header.
