# Project Memory: Bobtk (formerly Bobgui/GTK)

## 1. Project Overview & Vision
Bobtk is an ambitious, modern, multi-paradigm UI library currently being developed in C++ alongside a complete port to Go. It is an evolution of a legacy GTK/Bobgui codebase. The project's ultimate goal is to become the "greatest UI library of all time" by achieving:
- **100% Feature Parity** with major UI frameworks including Qt6 (and beta Qt7), JavaFX, WxWidgets, WinUI, and DearImgui.
- **Backwards Compatibility** with existing GTK software, making it trivial for legacy applications to migrate to the modern Bobtk framework.
- **Cross-Framework Integration**, specifically utilizing the JUCE framework and the Ultimate++ (U++) utility toolkit, allowing developers to intermix widgets from different paradigms seamlessly.

## 2. Core Architecture & Six-Pillar System
The C++ layer has been refactored away from a "thin wrapper" over C/GObject to a robust, application-centric framework. The architecture is organized into a **Six-Pillar Module System**:
- **Core:** Brain/AI interactions, utilities, translations (`bobtktranslate`), `data`, `i18n`, `stream`, and `brain`.
- **System:** OS-level integrations, filesystem watchers (`FileSystemWatcher`), inter-process communication (`LocalServer`), and system-level `live` elements.
- **Network:** High-level asynchronous HTTP wrapping, bidirectional `WebSocket` communication, and custom `bobguinetwork` interfaces.
- **Visual:** Semantic commands, CSS-based themes (`Theme`), custom C++ UI rendering (`Canvas`), chart configurations, docking configurations, DSL integrations, RHI rendering configurations, and immediate/retained-mode intermixing capabilities (`Graphics`).
- **Media:** Advanced handling for audio (`BobguiAudioDeviceManager`), physics simulation (`BobguiPhysicsWorld`), video, 3D, and GIS.
- **Tools:** Internal tooling and utility interfaces.

## 3. Submodules & Integrations
The project integrates specific external repositories to expand its capabilities rapidly. These live in the `/submodules` directory:
- **JUCE:** Provides deep audio tooling, modern C++ UI layout engines, and cross-platform painting capabilities (`Graphics`).
- **Ultimate++ (U++):** Brings a highly optimized C++ utility toolkit.
*Strategic Goal:* Identify the best architectural components of these submodules, extract them, and assimilate them directly into Bobtk (and its subsequent Go port).

## 4. The Go Port
A simultaneous effort is underway to port the entire UI framework to Go.
- **Location:** Resides in the top-level `/go` directory.
- **Current State:** Initialization of foundational Go packages mimicking the C++ module layout, including `pkg/core/data`, `pkg/core/i18n`, `pkg/core/stream`, and `pkg/core/brain`. 
- **Strategy:** The port will be comprehensive, examining C++ features one-by-one, selecting the best architectural patterns from the C++ base, JUCE, and U++, and rewriting them idiomatically and robustly in Go.
- **Future Frontends:** The Go port will eventually support native UI frontends alongside web UI.

## 5. Documentation & Agent Instructions
The project relies heavily on extensive, continuously updated documentation to maintain velocity across various AI implementor models.
- **Core Tracking Documents:**
  - `VISION.md`: Long-term goals and philosophical direction.
  - `ROADMAP.md`: High-level phases and major feature blocks.
  - `TODO.md`: Fine-grained, immediate tasks and bug fixes.
  - `MEMORY.md`: Ongoing observations about codebase quirks and structural patterns.
  - `DEPLOY.md`: Active instructions for building and running the project.
  - `CHANGELOG.md`: Chronological feature releases.
  - `IDEAS.md`: Free-form thoughts on C++ modernization, bindings, and renderer abstraction.
  - `HANDOFF.md`: Critical state-transfer document summarizing what was accomplished in the current session and what the *next* agent must do.
  - `VERSION`: Centralized file containing the single source of truth for the project version number.
- **Agent Instructions:** Foundational guidelines (`AGENTS.md`) combined with model-specific directives (`CLAUDE.md`, `GEMINI.md`, `GPT.md`, `copilot-instructions.md`).

## 6. Development Workflow & Rules
- **Renaming Conventions:** The codebase has been aggressively scrubbed of `gtk` and `bobgui`. All future additions must use `bobtk` nomenclature.
- **GObject/GType Handling:** The project employs heavy use of the GObject C-macros (`G_DEFINE_TYPE`, `G_DECLARE_FINAL_TYPE`). When adding or altering new C components under `bobgui/modules/`, be aware that the `meson` build scripts auto-generate `bobguitypebuiltins.c` files. Stubs must properly declare matching signatures to what the headers declare, otherwise `meson compile` will fail aggressively.
- **Documentation Comments:** Code must be commented in extreme depth. Explain *why* a decision was made, document side effects, alternate non-working methods, and general optimizations. However, completely self-explanatory code should remain uncommented.
- **UI Representation:** Every backend feature must have comprehensive frontend representations (UI config, options, labels, tooltips). No hidden functionality.
- **Autonomy & Continuity:** Development is continuous. Agents are expected to complete tasks, update the documentation (`HANDOFF.md`, `CHANGELOG.md`, etc.), bump the `VERSION`, commit and push to Git, and proceed autonomously to the next feature without waiting.

## 7. Current State & Handoff
- The foundational regex renaming (`gtk`/`bobgui` -> `bobtk`) has been completed across directories, files, and text contents.
- The `juce` and `ultimatepp` submodules have been initialized.
- The C++ `meson.build` pipeline was validated. Massive renaming caused breaks in GObject macro resolution, which were identified and fixed by aligning stubs and removing redundant macro declarations in headers.
- The Go module infrastructure has been initialized, including basic packages mirroring the C++ structure.
- The documentation framework for AI agent handoff is live.
- *Next Immediate Action:* Proceed mapping the rest of the C++ modules directly to Go structs, and begin translating business logic into the Go port layer.