#include <SFML/Graphics.hpp>

int main()
{
    const int windowWidth = 600, windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tux Jump");
    window.setFramerateLimit(60);

    // Load textures

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./assets/backgroundGame.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Texture nameScreenTexture;
    nameScreenTexture.loadFromFile("./assets/nameScreen.png");
    sf::Sprite nameSprite(nameScreenTexture);

    sf::Texture menuTexture;
    menuTexture.loadFromFile("./assets/menuGame.png");
    sf::Sprite menuSprite(menuTexture);

    sf::Texture plataformaTexture;
    plataformaTexture.loadFromFile("./assets/plataforaGame.png");
    sf::Sprite plataformaSprite(plataformaTexture);

    sf::Texture tuxTexture;
    tuxTexture.loadFromFile("./assets/tuxGame.png");
    sf::Sprite playerSprite(tuxTexture);

    
    bool writeNickname = true;
    bool gameOver = true;
    int score = 0;
    float playerPosX = 487, playerPosY = 281;
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
        // escrever nickname pegar ele e salvar
        
        // gameplay
        if(!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerPosX += 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerPosX -= 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                playerPosY -= 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                playerPosY += 3;
            }
            playerSprite.setPosition(playerPosX, playerPosY);
        }
        
        
        // Desenha os frames
        window.clear();
        window.draw(backgroundSprite);
        // Digitar o nickname
        if(writeNickname) {
            window.draw(nameSprite);
            // quando escrever o nickname atualizar para true
        }
        // Mostrar menu
        if(gameOver && !writeNickname) {
            window.draw(menuSprite);
        }
        // Comecar jogo
        if(!gameOver) {
            window.draw(playerSprite);
        }
        window.display();
    }
    
    return 0;
}