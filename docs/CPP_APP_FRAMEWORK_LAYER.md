# Bobgui C++ App Framework Layer

## Summary
This pass starts a thin C++ convenience layer on top of the existing bobgui C API instead of attempting a risky full rewrite.

New headers:
- `bobgui/cpp/bobgui.hpp`
- `bobgui/cpp/object_handle.hpp`
- `bobgui/cpp/application.hpp`
- `bobgui/cpp/action_registry.hpp`
- `bobgui/cpp/command_palette.hpp`
- `bobgui/cpp/workbench.hpp`

New example:
- `examples/workbench-demo/main.cpp`

## Why this direction
The project goal is to make bobgui feel easier to use, more coherent, and more application-framework-oriented.

For that, a thin C++ layer is much safer and more realistic than trying to rewrite a very large C codebase all at once.

This follows the same strategic pattern used successfully by frameworks that keep a stable C core while offering higher-level bindings or wrappers.

## Design principles
The C++ layer is intentionally:
- thin
- header-only
- non-invasive
- split into small focused headers instead of one growing monolith
- built on top of the existing C API
- aligned with the new workbench/action/command-palette model

That means the C core remains the source of truth while C++ consumers get a more direct, ergonomic entry point.

## What the wrapper currently provides
The first wrapper pass introduces small C++ objects for:
- `Application`
- `ActionRegistry`
- `CommandPalette`
- `Workbench`

The current wrapper focuses on:
- ownership of GObject-based instances
- straightforward workbench construction
- action-registry attachment
- command-palette attachment
- section-aware command registration
- lambda-friendly command handlers via `std::function`

## Why this is a better step than a rewrite
A rewrite would currently risk:
- losing renamed-path progress
- fragmenting the public API again
- introducing a second incomplete implementation
- breaking the momentum around the shared action/app-shell direction

A thin wrapper keeps the architecture converging instead of splitting.

## Relationship to the action-section work
The new C++ layer directly benefits from the explicit action-section model.

That is important because wrapper APIs need stable semantics for:
- menu sections
- toolbar groups
- command-palette groups
- toggle actions

By making those concepts explicit in the C layer first, the C++ API can stay simple instead of encoding fragile heuristics.

## Example direction
The new C++ example shows a workbench shell that:
- creates an application
- builds a workbench
- attaches an action registry
- attaches a command palette
- registers section-aware commands
- enables menubar and toolbar generation

## Rename audit note
A targeted audit of legacy toolkit spellings in the working tree came back clean during this pass.

That does not guarantee every historical trace is gone in every possible substring form, but it does indicate the visible high-level naming surface is already strongly normalized around `bobgui`.

## Validation status
A real compile-validation pass was attempted after this refactor, but the current environment does not provide Meson or a C++ compiler. The blocker is tool availability, not a decision to skip verification.

## Recommended next steps
1. add more wrapper coverage around actions, menus, and status helpers
2. introduce a small `MainWindow`/`Dock` style C++ convenience layer on top of workbench
3. add a build-wired C++ example once the current shell APIs settle a little more
4. continue eliminating naming drift only where it improves clarity without destabilizing inherited lower-level internals
