#pragma once

#include <bobgui/cpp/module.hpp>
#include <bobgui/cpp/media.hpp>
#include <memory>
#include <string>

namespace bobtk {
namespace module {

// The Media Pillar interface acts as the service registry for all audio/video/3d modules
class MediaPillar : public Module {
public:
    MediaPillar() : Module("Media", "1.0.0") {}

    // Audio Subsystem
    std::shared_ptr<media::AudioDeviceManager> getAudioDeviceManager() {
        if (!audioManager) {
            audioManager = std::make_shared<media::AudioDeviceManager>();
        }
        return audioManager;
    }

    // Holographic Subsystem
    std::shared_ptr<media::Hologram> createHologram(void* voxels, int width, int height, int depth) {
        return std::make_shared<media::Hologram>(voxels, width, height, depth);
    }

    std::shared_ptr<media::HolographView> createHolographView() {
        return std::make_shared<media::HolographView>();
    }

    // GIS Subsystem
    std::shared_ptr<media::MapView> createMapView() {
        return std::make_shared<media::MapView>();
    }

    // Shader Subsystem
    std::shared_ptr<media::EffectShader> createShader(const std::string& source) {
        return std::make_shared<media::EffectShader>(source);
    }

    // Physics Subsystem
    std::shared_ptr<media::PhysicsWorld> getPhysicsWorld() {
        if (!physicsWorld) {
            physicsWorld = std::make_shared<media::PhysicsWorld>();
        }
        return physicsWorld;
    }

    // Timeline Subsystem
    std::shared_ptr<media::Timeline> createTimeline() {
        return std::make_shared<media::Timeline>();
    }

    // Bio Subsystem
    std::shared_ptr<media::BioManager> getBioManager() {
        return media::BioManager::getDefault();
    }

    std::shared_ptr<media::BioViewer> createBioViewer() {
        return std::make_shared<media::BioViewer>();
    }

    // Spatial Subsystem
    std::shared_ptr<media::SpatialContext> createSpatialContext(const std::string& runtimeName) {
        return std::make_shared<media::SpatialContext>(runtimeName);
    }

protected:
    bool onInitialize() override {
        // Initialize underlying C libraries
        return true;
    }

    bool onStart() override {
        return true;
    }

    bool onStop() override {
        return true;
    }

private:
    std::shared_ptr<media::AudioDeviceManager> audioManager;
    std::shared_ptr<media::PhysicsWorld> physicsWorld;
};

} // namespace module
} // namespace bobtk
