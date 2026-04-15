package core

import "testing"

func TestNewWidget(t *testing.T) {
	w := NewWidget("test_widget")
	if w.ID != "test_widget" {
		t.Errorf("Expected ID 'test_widget', got '%s'", w.ID)
	}
}
