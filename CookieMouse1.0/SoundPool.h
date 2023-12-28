#pragma once
#ifndef SOUNDPool_H
#define SOUNDPool_H

#include <vector>
#include <SFML/Audio.hpp>
#include <random>

class SoundPool {
public:
    SoundPool(size_t size);
    void addSoundBuffer(const sf::SoundBuffer& buffer);
    void play();

private:
    std::vector<sf::Sound> sounds;
    std::vector<const sf::SoundBuffer*> buffers;
    std::default_random_engine generator;
    std::uniform_int_distribution<size_t> distribution;
};

#endif // SOUNDPool_H