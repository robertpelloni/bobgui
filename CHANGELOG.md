# CHANGELOG

## [1.0.0] - 2024-04-10
### Added
- Submodule: Ultimate++ (https://github.com/ultimatepp/ultimatepp)
- Submodule: JUCE (https://github.com/juce-framework/JUCE)
- Comprehensive project documentation (`VISION.md`, `ROADMAP.md`, `TODO.md`, `MEMORY.md`, `DEPLOY.md`, `CHANGELOG.md`, `IDEAS.md`, `HANDOFF.md`, etc.).
- Agent instruction files for various LLMs.

### Changed
- Mass renaming: All instances of `gtk` and `bobgui` renamed to `bobtk` to signify the new direction and future of the project.

## [4.0.6] - Unreleased
### Added
- Implemented high-level C++ wrappers for Core subsystems (`bobtk::core_subsystems::AutonomousController`, `BrainNode`, `ComputePipeline`, `SqlDatabase`, `EntityManager`, `FinChart`, `Translator`, `ModernLayout`, `MetaOrchestrator`, `QuantumScheduler`, `RealtimeKernel`, `ReflectContext`, `ScriptContext`, `StateMachine`, `Stream`).
- Implemented the `bobtk::module::CorePillar` interface to manage the creation and state of all data, rendering, layout, machine learning, logic, and state management subsystems within the core 6-pillar framework.
- Exported new C++ core classes through the master `bobgui.hpp` header.
