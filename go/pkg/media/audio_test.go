package media

import "testing"

func TestNewDeviceManager(t *testing.T) {
	am := NewDeviceManager(44100, 512)
	if am.SampleRate != 44100 {
		t.Errorf("Expected SampleRate 44100, got %d", am.SampleRate)
	}
}
