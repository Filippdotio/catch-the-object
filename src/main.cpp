/* TODO: IMPLEMENT SCORE SYSTEM; MULTIPLE OBJECT CREATION; OBJECT REMOVAL ON COLLISION WITH PLAYER; GAME OVER SCREEN IF OBJECT NOT CATCHED BY PLAYER */

#include <iostream>
#include <SFML/Graphics.hpp>

const int windowWidth = 800;
const int windowHeight = 600;

class Player
{
public:
    float width;
    float height;
    float posX;
    float posY;

    Player(float w, float h, float x, float y)
    {
        width = w;
        height = h;
        posX = x;
        posY = y;
    }

    void move(std::string direction, int distance, int windowWidth) 
    {
        if (direction == "left") {
            posX -= distance;
            if (posX < 0) posX = 0;  // Don't go off the left edge
        } else if (direction == "right") {
            posX += distance;
            if (posX + width > windowWidth) posX = windowWidth - width; // Don't go off the right edge
        }
    }
};

class Object
{
public:
    float radius;
    float posX;
    float posY;

    Object(float r, float x, float y)
    {
        radius = r;
        posX = x;
        posY = y;
    }

    void move() 
    {
        this->posY += 2;
    } 
};

bool checkCollision(const sf::RectangleShape& rect, const sf::CircleShape& circle) {
    sf::Vector2f circlePos = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()); // circle center
    sf::Vector2f rectPos = rect.getPosition();
    sf::Vector2f rectSize = rect.getSize();

    // Find closest point on rectangle to circle center
    float closestX = std::clamp(circlePos.x, rectPos.x, rectPos.x + rectSize.x);
    float closestY = std::clamp(circlePos.y, rectPos.y, rectPos.y + rectSize.y);

    // Calculate distance
    float distanceX = circlePos.x - closestX;
    float distanceY = circlePos.y - closestY;

    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
    return distanceSquared < (circle.getRadius() * circle.getRadius());
}

int main()
{
    Player player(120.f, 50.f, (windowWidth / 2) - 50, windowHeight - 50);
    Object object(20.f, (windowWidth / 2) - 50, windowHeight - 550);

    auto window = sf::RenderWindow(sf::VideoMode({800, 600u}), "Catch The Object");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                // left key is pressed: move our character
                player.move("left", 30, windowWidth);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                // left key is pressed: move our character
                player.move("right", 30, windowWidth);
            }
        }

        window.clear();

        sf::RectangleShape rectangle({player.width, player.height});
        rectangle.setPosition({player.posX, player.posY});

        sf::CircleShape circle(object.radius);
        circle.setPosition({object.posX, object.posY});
        circle.setFillColor(sf::Color(100, 250, 50));

        window.draw(rectangle);
        window.draw(circle);

        if (checkCollision(rectangle, circle))
        {
            window.close();
        }
        
        object.move();

        window.display();
    }
}
