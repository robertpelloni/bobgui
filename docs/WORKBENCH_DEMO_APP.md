# Workbench Demo App

## Summary
A small example shell was added at:
- `examples/workbench-demo/main.c`

## Purpose
The demo is meant to show the intended direction for bobgui application development:
- high-level workbench shell
- central action registry
- command palette integration
- command-backed header actions

## Why this matters
It is easier to evaluate whether bobgui is becoming "more like Qt but not Qt" when there is a concrete application-shell example instead of only isolated APIs.

## What the demo demonstrates
- creating a `BobguiWorkbench`
- creating and attaching a `BobguiActionRegistry`
- creating and attaching a `BobguiCommandPalette`
- registering commands through the workbench
- binding header actions directly to those command identifiers
- presenting a coherent shell with a left sidebar and central editor area

## Next expected enhancement
The natural next step for the demo is to enable a generated menubar from the shared action registry so the example shows a complete action-driven shell, not just palette + header buttons.

## Strategic value
This is the type of example that starts turning bobgui from a toolkit people inspect into a framework people can imitate and build on.

## Recommended next step
The next useful enhancement would be to make this example buildable by default behind an option or example target, once the surrounding module scaffolding stabilizes.
