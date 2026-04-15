package core

// Widget represents the foundational UI component in Bobtk
type Widget struct {
    ID     string
    Parent *Widget
    // TODO: expand with generic widget properties (position, size, layout, styling)
}

// NewWidget initializes a basic Widget instance
func NewWidget(id string) *Widget {
    return &Widget{
        ID: id,
    }
}
