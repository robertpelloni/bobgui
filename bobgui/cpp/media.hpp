#pragma once

#include <bobgui/bobgui.h>
#include <bobgui/cpp/object_handle.hpp>
#include <bobgui/cpp/widget.hpp>
#include <string>
#include <memory>

namespace bobtk {
namespace media {

class AudioDeviceManager : public core::ObjectHandle<BobguiAudioDeviceManager> {
public:
    AudioDeviceManager()
        : core::ObjectHandle<BobguiAudioDeviceManager>(bobgui_audio_device_manager_new()) {}
};

class AudioProcessor : public core::ObjectHandle<BobguiAudioProcessor> {
protected:
    AudioProcessor(BobguiAudioProcessor* handle) : core::ObjectHandle<BobguiAudioProcessor>(handle) {}
};

class AudioDial : public Widget {
public:
    AudioDial() : Widget(bobgui_audio_dial_new()) {}
};

class AudioFader : public Widget {
public:
    AudioFader() : Widget(bobgui_audio_fader_new()) {}
};

class AudioScope : public Widget {
public:
    AudioScope() : Widget(bobgui_audio_scope_new()) {}
};

class AudioAnalyzer : public Widget {
public:
    AudioAnalyzer() : Widget(bobgui_audio_analyzer_new()) {}
};

class ThreeDNode : public core::ObjectHandle<Bobgui3dNode> {
public:
    ThreeDNode() : core::ObjectHandle<Bobgui3dNode>(bobgui_3d_node_new()) {}
};

class Hologram : public core::ObjectHandle<BobguiHologram> {
public:
    Hologram(gpointer voxels, int width, int height, int depth)
        : core::ObjectHandle<BobguiHologram>(bobgui_hologram_new_from_voxels(voxels, width, height, depth)) {}

    void projectToSpace(float x, float y, float z, float w, float h, float d) {
        bobgui_hologram_project_to_space(handle(), x, y, z, w, h, d);
    }

    void setInteractionDensity(float threshold) {
        bobgui_hologram_set_interaction_density(handle(), threshold);
    }
};

class HolographView : public Widget {
public:
    HolographView() : Widget(bobgui_holograph_view_new()) {}

    void display(const Hologram& hologram) {
        bobgui_holograph_view_display(BOBGUI_HOLOGRAPH_VIEW(handle()), hologram.handle());
    }
};

class MapView : public Widget {
public:
    MapView() : Widget(bobgui_map_view_new()) {}
};

class EffectShader : public core::ObjectHandle<BobguiEffectShader> {
public:
    explicit EffectShader(const std::string& source)
        : core::ObjectHandle<BobguiEffectShader>(bobgui_effect_shader_new_from_source(source.c_str())) {}
};

class PhysicsWorld : public core::ObjectHandle<BobguiPhysicsWorld> {
public:
    PhysicsWorld() : core::ObjectHandle<BobguiPhysicsWorld>(bobgui_physics_world_new()) {}

    void step(float deltaTime) {
        bobgui_physics_world_step(handle(), deltaTime);
    }

    void setGravity(float x, float y, float z) {
        bobgui_physics_world_set_gravity(handle(), x, y, z);
    }
};

class Timeline : public core::ObjectHandle<BobguiTimeline> {
public:
    Timeline() : core::ObjectHandle<BobguiTimeline>(bobgui_timeline_new()) {}
};

class BioManager : public core::ObjectHandle<BobguiBioManager> {
public:
    static std::shared_ptr<BioManager> getDefault() {
        return std::shared_ptr<BioManager>(new BioManager(bobgui_bio_manager_get_default()));
    }

    void startSensorStream(const std::string& sensorId) {
        bobgui_bio_start_sensor_stream(handle(), sensorId.c_str());
    }

    void enableBiometricAdaptation(Widget& uiRoot) {
        bobgui_bio_enable_biometric_adaptation(handle(), BOBGUI_WIDGET(uiRoot.handle()));
    }

private:
    BioManager(BobguiBioManager* handle) : core::ObjectHandle<BobguiBioManager>(handle) {}
};

class BioViewer : public Widget {
public:
    BioViewer() : Widget(bobgui_bio_viewer_new()) {}

    void loadDicom(const std::string& path) {
        bobgui_bio_viewer_load_dicom(BOBGUI_BIO_VIEWER(handle()), path.c_str());
    }
};

class SpatialContext : public core::ObjectHandle<BobguiSpatialContext> {
public:
    explicit SpatialContext(const std::string& runtimeName)
        : core::ObjectHandle<BobguiSpatialContext>(bobgui_spatial_context_new(runtimeName.c_str())) {}
};

} // namespace media
} // namespace bobtk
