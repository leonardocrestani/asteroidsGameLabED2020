#include <SFML/Graphics.hpp>

int main()
{
    const int windowWidth = 800, windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Asteroids Remastered 2020");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/backgroundGame.jpg");
    sf::IntRect backgroundRect(0, 0, windowWidth, windowHeight);
    sf::Sprite backgroundSprite(backgroundTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    
    return 0;
}