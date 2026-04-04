/* bobgui/audio/bobguiaudio.c */
#include "bobguiaudio.h"

G_DEFINE_ABSTRACT_TYPE (BobguiAudioProcessor, bobgui_audio_processor, G_TYPE_OBJECT)

static void
bobgui_audio_processor_class_init (BobguiAudioProcessorClass *klass)
{
  /* Abstract class initialization */
}

static void
bobgui_audio_processor_init (BobguiAudioProcessor *self)
{
  /* Initial state */
}

void
bobgui_audio_processor_prepare_to_play (BobguiAudioProcessor *self, double sample_rate, int samples_per_block)
{
  BobguiAudioProcessorClass *klass = BOBGUI_AUDIO_PROCESSOR_GET_CLASS (self);
  if (klass->prepare_to_play)
    klass->prepare_to_play (self, sample_rate, samples_per_block);
}

void
bobgui_audio_processor_process_block (BobguiAudioProcessor *self, float **buffer, int num_channels, int num_samples)
{
  BobguiAudioProcessorClass *klass = BOBGUI_AUDIO_PROCESSOR_GET_CLASS (self);
  if (klass->process_block)
    klass->process_block (self, buffer, num_channels, num_samples);
}

struct _BobguiAudioDeviceManager {
  BobguiAudioProcessor *processor;
  double sample_rate;
  int block_size;
};

BobguiAudioDeviceManager *
bobgui_audio_device_manager_new (void)
{
  BobguiAudioDeviceManager *mgr = g_new0 (BobguiAudioDeviceManager, 1);
  mgr->sample_rate = 44100.0;
  mgr->block_size = 512;
  return mgr;
}

void
bobgui_audio_device_manager_init (BobguiAudioDeviceManager *self, int num_inputs, int num_outputs)
{
  /* Initialize backend audio driver (PulseAudio, JACK, or CoreAudio) */
  /* For absolute parity, we would spawn an audio thread here and call process_block */
}

void
bobgui_audio_device_manager_set_processor (BobguiAudioDeviceManager *self, BobguiAudioProcessor *processor)
{
  self->processor = processor;
  if (processor) {
    bobgui_audio_processor_prepare_to_play (processor, self->sample_rate, self->block_size);
  }
}
