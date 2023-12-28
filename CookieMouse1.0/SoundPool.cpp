#include "SoundPool.h"

SoundPool::SoundPool(size_t size) : distribution(0, 0) { // Initialize distribution with dummy values
    for (size_t i = 0; i < size; ++i) {
        sf::Sound sound;
        sounds.push_back(sound);
    }
}

void SoundPool::addSoundBuffer(const sf::SoundBuffer& buffer) {
    buffers.push_back(&buffer);
    distribution = std::uniform_int_distribution<size_t>(0, buffers.size() - 1); // Update distribution range
}

void SoundPool::play() {
    if (buffers.empty()) return; // Do nothing if no buffers are added

    size_t bufferIndex = distribution(generator); // Randomly select a buffer
    const sf::SoundBuffer* selectedBuffer = buffers[bufferIndex];

    for (auto& sound : sounds) {
        if (sound.getStatus() != sf::Sound::Playing) {
            sound.setBuffer(*selectedBuffer);
            sound.play();
            break;
        }
    }
}
