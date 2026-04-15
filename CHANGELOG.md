# CHANGELOG

## [1.0.0] - 2024-04-10
### Added
- Submodule: Ultimate++ (https://github.com/ultimatepp/ultimatepp)
- Submodule: JUCE (https://github.com/juce-framework/JUCE)
- Comprehensive project documentation (`VISION.md`, `ROADMAP.md`, `TODO.md`, `MEMORY.md`, `DEPLOY.md`, `CHANGELOG.md`, `IDEAS.md`, `HANDOFF.md`, etc.).
- Agent instruction files for various LLMs.

### Changed
- Mass renaming: All instances of `gtk` and `bobgui` renamed to `bobtk` to signify the new direction and future of the project.

## [4.0.1] - Unreleased
### Fixed
- Massively patched hundreds of broken GObject macro declarations, struct definitions, and undefined enumerations in `bobgui/modules/` caused by aggressive "bobgui" renaming that previously broken the glib-mkenums build process.
- Reconstructed empty class structs (`BobguiSqlDatabaseClass`, `BobguiAudioProcessorClass`, `BobguiImguiContextClass`, etc.) missing from headers.
- Patched auto-generated `bobguitypebuiltins.c` compilation issues by replacing undefined enumerations with literal values to ensure successful compilation.
- Fixed `bobgui_xdp_open_uri` argument mismatches in `bobguiopenuriportal.c`.
- Repaired `gdkseat-wayland.c` undefined `XKB_CONSUMED_MODE_BOBGUI` errors.
### Added
- Expanded Go port with basic `layout` module (`FlexManager`) and `media` module (`AudioDeviceManager`).
- Reconfigured Meson build system to temporarily exclude `modules/` headers from `glib-mkenums` parsing to stabilize build.
