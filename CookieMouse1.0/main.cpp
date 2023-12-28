#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <algorithm>
#include "SoundPool.h"

const int MAX_COOKIES = 100;
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int FRAME_RATE_FOR_NEW_COOKIE = 5000;
const float MOVEMENT_SPEED = .06f;  // Adjust this value to control speed
const float CURSOR_THRESHOLD = 50.0f; // Distance from cursor within which the sprite won't move

sf::Vector2f getRandomPosition(int width, int height, const sf::Vector2u& spriteSize) {
    // Calculate maximum x and y positions to ensure the sprite is fully on screen
    int maxX = width - spriteSize.x;
    int maxY = height - spriteSize.y;

    // Generate random position within the adjusted bounds
    return sf::Vector2f(rand() % maxX + spriteSize.x / 2, rand() % maxY + spriteSize.y / 2);
}


void addCookieIfNecessary(std::vector<sf::Sprite>& cookies, sf::Texture& cookieTexture) {
    if (cookies.size() < MAX_COOKIES) {
        sf::Sprite cookie(cookieTexture);
        cookie.setPosition(getRandomPosition(WINDOW_WIDTH, WINDOW_HEIGHT, cookieTexture.getSize()));
        cookies.push_back(cookie);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Initialize random seed

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Simple Game", sf::Style::Fullscreen);
    window.setMouseCursorVisible(false);

    // Load textures
    sf::Texture mouseTexture, cookieTexture;
    if (!mouseTexture.loadFromFile("C:/Users/alkal/source/repos/CookieMouse1.0/PNG Assets/Mouse_no_cookie.png") ||
        !cookieTexture.loadFromFile("C:/Users/alkal/source/repos/CookieMouse1.0/PNG Assets/cookie_no_mouse.png")) {
        return -1; // Error loading the textures
    }

    // Create mouse sprite
    sf::Sprite mouse(mouseTexture);
    mouse.setOrigin(mouseTexture.getSize().x / 2, mouseTexture.getSize().y / 2);

    sf::SoundBuffer buffer1, buffer2;
    if (!buffer1.loadFromFile("C:/Users/alkal/source/repos/CookieMouse1.0/Sound Assets/2chomps.wav") ||
        !buffer2.loadFromFile("C:/Users/alkal/source/repos/CookieMouse1.0/Sound Assets/Tinynibbles.wav")) {
        return -1; // Error loading the sounds
    }

    SoundPool soundPool(10); // Updated constructor call
    soundPool.addSoundBuffer(buffer1); // Add first sound buffer
    soundPool.addSoundBuffer(buffer2); // Add second sound buffer

    int frameCounter = 0;
    std::vector<sf::Sprite> cookies;

    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    float lastXDirection = 1.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Vector2f targetPos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        sf::Vector2f direction = targetPos - mousePos;

        // Calculate the distance to the cursor
        float distanceToCursor = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distanceToCursor > CURSOR_THRESHOLD) {
            // Normalize the direction vector and then scale it by MOVEMENT_SPEED
            if (distanceToCursor != 0) {
                direction.x /= distanceToCursor;
                direction.y /= distanceToCursor;
            }

            direction *= MOVEMENT_SPEED;

            // Update mouse position
            mousePos += direction;
        }

        // Ensure the mouse sprite stays within the window bounds
        mousePos.x = std::max(static_cast<float>(mouseTexture.getSize().x / 2), std::min(mousePos.x, static_cast<float>(WINDOW_WIDTH - mouseTexture.getSize().x / 2)));

        mousePos.y = std::max(static_cast<float>(mouseTexture.getSize().y / 2), std::min(mousePos.y, static_cast<float>(WINDOW_HEIGHT - mouseTexture.getSize().y / 2)));


        mouse.setPosition(mousePos);

        // Flip the sprite based on the direction of movement
        if (direction.x < 0 && lastXDirection >= 0) {
            mouse.setScale(-1.f, 1.f);
            lastXDirection = -1.0f;
        }
        else if (direction.x > 0 && lastXDirection <= 0) {
            mouse.setScale(1.f, 1.f);
            lastXDirection = 1.0f;
        }

        if (frameCounter++ >= FRAME_RATE_FOR_NEW_COOKIE) {
            addCookieIfNecessary(cookies, cookieTexture);
            frameCounter = 0;
        }

        cookies.erase(std::remove_if(cookies.begin(), cookies.end(),
            [&mouse, &soundPool](const sf::Sprite& cookie) {
                if (mouse.getGlobalBounds().intersects(cookie.getGlobalBounds())) {
                    soundPool.play();
                    return true;
                }
                return false;
            }), cookies.end());

        window.clear(sf::Color::White);
        window.draw(mouse);
        for (const auto& cookie : cookies) {
            window.draw(cookie);
        }
        window.display();
    }
    return 0;
}