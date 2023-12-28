#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <map>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    std::shared_ptr<sf::Texture> getTexture(const std::string& filename);
    std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string& filename);

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;

    std::shared_ptr<sf::Texture> loadTexture(const std::string& filename);
    std::shared_ptr<sf::SoundBuffer> loadSoundBuffer(const std::string& filename);
};

#endif // RESOURCEMANAGER_H
