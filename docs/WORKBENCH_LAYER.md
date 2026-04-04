# Bobgui Workbench Layer

## Goal
A practical way to make bobgui feel more like a modern application framework—closer to Qt's `QMainWindow` ergonomics—without becoming Qt.

## Why this was added
One of Qt's strongest advantages is not just widgets, but the ease of building a professional application shell:
- top-level main window
- central content area
- left/right side panels
- header / toolbar region
- bottom status area
- straightforward app-shell composition

GTK-derived APIs are powerful but often feel low-level and assembly-oriented for app-shell work. The new `BobguiWorkbench` layer is intended to reduce that friction.

## What `BobguiWorkbench` provides
`BobguiWorkbench` offers a higher-level application shell abstraction with:
- application window ownership
- header bar management
- central widget placement
- left sidebar support
- right sidebar support
- simple status line updates
- easy header action buttons

## Key API
- `bobgui_workbench_new()`
- `bobgui_workbench_set_title()`
- `bobgui_workbench_set_central()`
- `bobgui_workbench_set_left_sidebar()`
- `bobgui_workbench_set_right_sidebar()`
- `bobgui_workbench_set_status()`
- `bobgui_workbench_add_header_action()`
- `bobgui_workbench_present()`

## Why this is "more like Qt but not Qt"
This is intentionally not a copy of `QMainWindow`.
Instead, it follows a bobgui-native direction:
- still built from ordinary bobgui widgets
- still composable using paned/box/headerbar primitives
- no separate object model or meta compiler
- integrates naturally with grouped module headers and future DSL work

## Strategic value
`BobguiWorkbench` is a good example of the next phase bobgui needs:
- fewer abstract module stubs
- more developer-facing ergonomics
- more cohesive vertical slices that directly improve usability

## Recommended next step
The most valuable follow-up would be:
1. add a command-palette API
2. add workbench-managed dock registration
3. integrate status updates with shell/progress APIs
4. provide a small demo app using the workbench shell
