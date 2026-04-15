package layout

import "testing"

func TestFlexManager(t *testing.T) {
	fm := &FlexManager{Direction: "row", JustifyContent: "center"}
	if fm.Direction != "row" {
		t.Errorf("Expected Direction 'row', got '%s'", fm.Direction)
	}
}
