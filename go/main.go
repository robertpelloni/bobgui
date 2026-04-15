package main

import (
	"fmt"
	"bobtk/pkg/core"
    "bobtk/pkg/layout"
    "bobtk/pkg/media"
)

func main() {
	widget := core.NewWidget("root_widget")

    flexManager := &layout.FlexManager{Direction: "row", JustifyContent: "center"}

    audioManager := media.NewDeviceManager(44100, 512)

	fmt.Println("Welcome to the Bobtk Go runtime!")
	fmt.Printf("Root widget initialized with ID: %s\n", widget.ID)
    fmt.Printf("Flex Layout Configured: Direction=%s, Justify=%s\n", flexManager.Direction, flexManager.JustifyContent)
    fmt.Printf("Audio Device Manager active: %d Hz, %d samples buffer\n", audioManager.SampleRate, audioManager.BufferSize)
}
