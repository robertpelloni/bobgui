package media

// AudioDeviceManager abstracts audio I/O hardware
type AudioDeviceManager struct {
    SampleRate int
    BufferSize int
}

// AudioProcessor handles DSP operations
type AudioProcessor interface {
    Process(buffer []float32) error
}

func NewDeviceManager(sampleRate, bufferSize int) *AudioDeviceManager {
    return &AudioDeviceManager{
        SampleRate: sampleRate,
        BufferSize: bufferSize,
    }
}
