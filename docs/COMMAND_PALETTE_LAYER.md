# Bobgui Command Palette Layer

## Summary
This pass adds a higher-level command palette abstraction to make bobgui feel more like a serious application framework rather than a low-level widget assembly kit.

## Why this matters
One of the practical things that makes Qt-based applications feel polished is the presence of discoverable command systems and application-shell ergonomics. A command palette is a lightweight but high-value piece of that experience.

It improves:
- discoverability
- keyboard-oriented workflows
- command organization
- app-shell polish

## What was added
### New module
- `bobgui/modules/visual/commandpalette/bobguicommandpalette.h`
- `bobgui/modules/visual/commandpalette/bobguicommandpalette.c`

### Core API
- `bobgui_command_palette_new()`
- `bobgui_command_palette_add_command()`
- `bobgui_command_palette_attach_to_window()`
- `bobgui_command_palette_present()`

## Current behavior improvements
This pass also added built-in filtering behavior:
- the palette listens to `BobguiSearchEntry::search-changed`
- commands are filtered by substring match against:
  - command id
  - title
  - subtitle

That makes the palette feel much more like a modern command launcher rather than a static dialog.

### Workbench integration
`BobguiWorkbench` was extended with:
- `bobgui_workbench_set_command_palette()`

This makes it easy to attach a command palette to a workbench shell and expose it through a header action.

## Design direction
This is intentionally **Qt-like but not Qt**:
- it adds app-shell ergonomics
- it stays composed from ordinary bobgui widgets
- it avoids introducing a separate meta-object runtime or reinventing the framework identity

## Strategic value
This is a strong example of the direction bobgui should keep taking:
- fewer disconnected conceptual modules
- more cohesive, developer-facing usability features
- more framework-level affordances that make building a real app easier

## Recommended next steps
1. add keyboard shortcut activation for the command palette
2. improve ranking beyond substring matching (scored fuzzy match)
3. integrate command palette entries with workbench/dock/actions
4. add a small demo application showing the full workbench + command palette flow
