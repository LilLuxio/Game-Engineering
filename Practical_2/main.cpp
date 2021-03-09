#include <SFML/Graphics.hpp>
#include <iostream>
#include "ship.h"
#include "game.h"

using namespace sf;
using namespace std;

sf::Texture spritesheet;
//sf::Sprite invader;
//sf::Sprite player;

std::vector<Ship*> ships;

//const int gameWidth = 800;
//const int gameHeight = 600;



void Load() {
    // Load up the sprite sheet
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    // Load in all the invaders
    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = IntRect(0, 0, 32, 32);
        for (int c = 0; c < invaders_columns; ++c) {
            Vector2f position = Vector2f(16 + (c *32), 16 + (r * 32));
            auto inv = new Invader(rect, position);
            ships.push_back(inv);
        }
    }

    // Load in the player
    // player.setTexture(spritesheet);
    // player.setTextureRect(sf::IntRect(160, 32, 32, 32));
    auto playerActor = new Player();
    ships.push_back(playerActor);
}

void Update(RenderWindow& window) {
    // Reset clock, recalculate deltatime
    static Clock clock;
    float dt = clock.restart().asSeconds();
    // Check and consume events
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            return;
        }
    }
    for (auto& s : ships) {
        s->Update(dt);
    };

    // Invader Speed
    Invader::speed = 20.f;
}

void Render(RenderWindow& window) {
    //window.draw(invader);
    //window.draw(player);

    for (const auto s : ships) {
        window.draw(*s);
    }
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
    Load();

    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;
}

