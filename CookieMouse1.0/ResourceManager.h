#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    // Constructor
}

ResourceManager::~ResourceManager() {
    // Destructor
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(const std::string& filename) {
    auto iter = textures.find(filename);
    if (iter != textures.end()) {
        return iter->second;
    }
    else {
        return loadTexture(filename);
    }
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::getSoundBuffer(const std::string& filename) {
    auto iter = soundBuffers.find(filename);
    if (iter != soundBuffers.end()) {
        return iter->second;
    }
    else {
        return loadSoundBuffer(filename);
    }
}

std::shared_ptr<sf::Texture> ResourceManager::loadTexture(const std::string& filename) {
    auto texture = std::make_shared<sf::Texture>();
    if (texture->loadFromFile(filename)) {
        textures[filename] = texture;
        return texture;
    }
    else {
        return nullptr; // Failed to load texture
    }
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::loadSoundBuffer(const std::string& filename) {
    auto soundBuffer = std::make_shared<sf::SoundBuffer>();
    if (soundBuffer->loadFromFile(filename)) {
        soundBuffers[filename] = soundBuffer;
        return soundBuffer;
    }
    else {
        return nullptr; // Failed to load sound buffer
    }
}
