package layout

import "bobtk/pkg/core"

// LayoutType determines how child widgets are arranged
type LayoutType int

const (
    LayoutTypeFlex LayoutType = iota
    LayoutTypeGrid
    LayoutTypeAbsolute
)

// Manager interfaces abstract layout systems
type Manager interface {
    Apply(parent *core.Widget, children []*core.Widget)
}

// FlexManager implements flexible CSS-like layout
type FlexManager struct {
    Direction      string
    JustifyContent string
    AlignItems     string
}

func (fm *FlexManager) Apply(parent *core.Widget, children []*core.Widget) {
    // Basic logic stub for positioning calculations
}
