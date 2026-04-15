# Deployment Instructions - Bobtk

## Requirements
* OS: Linux (Ubuntu/Debian recommended for build consistency)
* Dependencies:
```bash
sudo apt-get update
sudo apt-get install -y build-essential meson ninja-build libxkbcommon-dev libsoup-3.0-dev libvulkan-dev libdrm-dev glslc gettext libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev libwayland-dev
```

## Compilation (C)
To compile the core Bobtk package:
```bash
meson setup build
meson compile -C build
```

To install globally:
```bash
sudo ninja -C build install
```

## Go Port
To run the Go port:
```bash
cd go
go run main.go
```
