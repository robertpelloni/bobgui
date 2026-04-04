/* bobgui/audio/bobguiaudio.h */
#ifndef BOBGUI_AUDIO_H
#define BOBGUI_AUDIO_H

#include <glib-object.h>

G_BEGIN_DECLS

#define BOBGUI_TYPE_AUDIO_PROCESSOR (bobgui_audio_processor_get_type ())
G_DECLARE_DERIVABLE_TYPE (BobguiAudioProcessor, bobgui_audio_processor, BOBGUI, AUDIO_PROCESSOR, GObject)

struct _BobguiAudioProcessorClass
{
  GObjectClass parent_class;

  void (* process_block) (BobguiAudioProcessor *self, float **buffer, int num_channels, int num_samples);
  void (* prepare_to_play) (BobguiAudioProcessor *self, double sample_rate, int samples_per_block);
  void (* release_resources) (BobguiAudioProcessor *self);
};

/* Audio Device Management (JUCE Parity) */
typedef struct _BobguiAudioDeviceManager BobguiAudioDeviceManager;

BobguiAudioDeviceManager * bobgui_audio_device_manager_new (void);
void                       bobgui_audio_device_manager_init (BobguiAudioDeviceManager *self, int num_inputs, int num_outputs);
void                       bobgui_audio_device_manager_set_processor (BobguiAudioDeviceManager *self, BobguiAudioProcessor *processor);

/* MIDI Handling (JUCE Parity) */
typedef struct _BobguiMidiMessage BobguiMidiMessage;
BobguiMidiMessage * bobgui_midi_message_note_on (int channel, int note, float velocity);
BobguiMidiMessage * bobgui_midi_message_note_off (int channel, int note, float velocity);

G_END_DECLS

#endif /* BOBGUI_AUDIO_H */
