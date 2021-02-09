#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
    Keyboard::A, // Player1 UP
    Keyboard::Z, // Player1 Down
    Keyboard::Up, // Player2 Up
    Keyboard::Down // Player2 Down
};

const Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;

CircleShape ball;
RectangleShape paddles[2];

Vector2f ballVelocity;
bool server = false;

Font font;
Text text;

int player1Score = 0;
int player2Score = 0;

void Reset() {
    // Reset paddle position
    paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
    paddles[1].setPosition(gameWidth - (paddleSize.x + 10) / 2, gameHeight / 2);

    // reset ball position
    ball.setPosition(gameWidth / 2, gameHeight / 2);

    // Ball Velocity
    ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };

    // Update Score Text
    text.setString("Score: ");
    
    // Keep Score Text Centered
    text.setPosition((gameWidth * .5f) - (text.getLocalBounds().width * .5f), 0);
}

void Colours() {
    // Setting colours
    paddles[0].setFillColor(sf::Color::Yellow);
    paddles[1].setFillColor(sf::Color::Yellow);
    ball.setFillColor(sf::Color::Yellow);
}

void Load() {
    // Set size and origin of paddles
    for (auto& p : paddles) {
        p.setSize(paddleSize - Vector2f(3, 3));
        p.setOrigin(paddleSize / 2.f);
    }

    // Set size and origin of ball
    ball.setRadius(ballRadius);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

    Reset();
    Colours();

    // Load font-face from res dir
    //font.loadFromFile("res/fonts/PIXEL-LI.ttf");
    // Set text element to use font
    //text.setFont(font);
    // Set the character size to 24 pixels
    text.setCharacterSize(24);

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

    // Moving the ball
    ball.move(ballVelocity * dt);

    // Quit Via ESC Key
    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
        window.close();
    }

    // Handle paddle [LEFT] movement
    float Leftdirection = 0.0f;
    if (Keyboard::isKeyPressed(controls[0])) {
        Leftdirection--;
    }
    if (Keyboard::isKeyPressed(controls[1])) {
        Leftdirection++;
    }
    paddles[0].move(0, Leftdirection * paddleSpeed * dt);
    // Handle paddle [RIGHT] movement
    float Rightdirection = 0.0f;
    if (Keyboard::isKeyPressed(controls[2])) {
        Rightdirection--;
    }
    if (Keyboard::isKeyPressed(controls[3])) {
        Rightdirection++;
    }
    paddles[1].move(0, Rightdirection * paddleSpeed * dt);

    // Check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;

    if (by > gameHeight) { // Bottom wall

        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, -10);
    }
    else if (by < 0) { // Top wall
    
        ballVelocity.x *= 1.1f;
        ballVelocity.y *= -1.1f;
        ball.move(0, 10);
    }
    else if (bx > gameWidth) {
        // Right wall
        player1Score += 1;
        Reset();
    }
    else if (bx < 0) {
        // Left wall
        player2Score += 1;
        Reset();
    }
    else if (
        // LEFT PADDLE COLLISION
        // ball is inline or behind paddle
        bx < paddleSize.x &&
        // AND ball is below top edge of paddle
        by > paddles[0].getPosition().y - (paddleSize.y * 0.5) &&
        // AND ball is above bottom edge of paddle
        by < paddles[0].getPosition().y + (paddleSize.y * 0.5)
        ) {

        // Bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(10, 0);
    }
    else if (
        // RIGHT PADDLE COLLISION
        // ball is inline or behind paddle
        bx > (paddles[1].getPosition().x - 25) &&
        // AND ball is below top edge of paddle
        by > paddles[1].getPosition().y - (paddleSize.y) &&
        // AND ball is above bottom edge of paddle
        by < paddles[1].getPosition().y + (paddleSize.y)
        ) {

        // Bounce off left paddle
        ballVelocity.x *= -1.1f;
        ballVelocity.y *= 1.1f;
        ball.move(-10, 0);
    }

}

void Render(RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

int main() {
    RenderWindow window(VideoMode(gameWidth, gameHeight), "PONG");
    Load();

    while (window.isOpen()) {
        window.clear();
        Update(window);
        Render(window);
        window.display();
    }
    return 0;

}