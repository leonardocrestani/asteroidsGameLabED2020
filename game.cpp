#include <SFML/Graphics.hpp>

int main()
{
    const int windowWidth = 1000, windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Asteroids Remastered 2020");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./assets/backgroundImage.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    // Game loop (funcionamento)
    while (window.isOpen())
    {
        // Tratamento de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Atualizacao dos estados do jogo (elementos)

        // Local onde sao desenhados os frames
        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
    
    return 0;
}