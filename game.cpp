#include <SFML/Graphics.hpp>
#include <random>

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

    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("./assets/gameoverScreen.png");
    sf::Sprite gameOverSprite(gameOverTexture);

    sf::Texture platformTexture;
    platformTexture.loadFromFile("./assets/plataformaGame.png");
    sf::Sprite platformSprite(platformTexture);

    sf::Texture tuxTexture;
    tuxTexture.loadFromFile("./assets/tuxGame.png");
    sf::Sprite playerSprite(tuxTexture);

    sf::Font font;
    font.loadFromFile("assets/small_font.ttf");

    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(42);
    textScore.setOutlineColor(sf::Color::Black);
    textScore.setFillColor(sf::Color::White);
    
    sf::Vector2u platformPosition[10];
	std::uniform_int_distribution<unsigned> x(0, 600 - platformTexture.getSize().x);
	std::uniform_int_distribution<unsigned> y(100, 900);
	std::default_random_engine e(time(0));
	
    // Iniciando plataformas
    for(size_t i = 0; i < 10; i++)
	{
		platformPosition[i].y = y(e);
        platformPosition[i].x = x(e);
	}

    bool writeNickname = true;
    bool gameOver = false;
    int score = 0;
    int height = 150;
    float dy = 0;
    /* variaves para serem criadas
        nickname
        data e hora do jogo
    */
    float playerPosX = 250, playerPosY = 150;

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
        // jogador fora do alcance X muda de lado
        if (playerPosX > 600)
			playerPosX = 0;
		if (playerPosX < -40)
			playerPosX = window.getSize().x - tuxTexture.getSize().x;
        }

        // Atualizacao dos estados do jogo (elementos)
        // escrever nickname pegar ele e salvar
        
        // gameplay
        if(!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerPosX -= 6;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerPosX += 6;
            }
            
            playerSprite.setPosition(playerPosX, playerPosY);
            textScore.setPosition(20, 20);
            textScore.setString(std::to_string(score));

            // Se o jogador cair até o final da tela será game over
            if(playerPosY > 820) {
                gameOver = true;
            }

        }

        // Desenha os frames
        window.clear();
        window.draw(backgroundSprite);

        // Digitar o nickname

        /* if(writeNickname) {
            window.draw(nameSprite);
            // quando escrever o nickname atualizar para true
        } */

        // Mostrar menu
        /*if(gameOver && !writeNickname) {
            window.draw(menuSprite);
        }*/

        // Comecar jogo
        if(!gameOver) {
            window.draw(playerSprite);
            window.draw(textScore);

            // Definindo plataformas
            for (size_t i = 0; i < 10; i++)
		    {
			    platformSprite.setPosition(platformPosition[i].x, platformPosition[i].y);
			    window.draw(platformSprite);
		    }
        }
        
        if(gameOver) {
            window.draw(gameOverSprite);
        }
        window.display();
    }
    
    return 0;
}