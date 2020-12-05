#include <SFML/Graphics.hpp>
#include <random>
#include <string>


int main()
{   
    // Iniciando tela
    const int windowWidth = 600, windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tux Jump");
    window.setFramerateLimit(60);

    // Carregamento das texturas
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

    sf::Text textName;
    textName.setFont(font);
    textName.setCharacterSize(42);
    textName.setOutlineColor(sf::Color::Black);
    textName.setFillColor(sf::Color::White);


    // Iniciando plataformas
    sf::Vector2u platformPosition[7];
	std::uniform_int_distribution<unsigned> x(0, 600 - platformTexture.getSize().x);
	std::uniform_int_distribution<unsigned> y(100, 900);
	std::default_random_engine e(time(0));
    for(size_t i = 0; i<7; i++)
	{
		platformPosition[i].y = y(e);
        platformPosition[i].x = x(e);
	}

    // Iniciando variaveis
    bool writeNickname = true;
    bool gameOver = false;
    int score = 0;
    int height = 160;
    float dy = 0;
    float playerPosX = 300, playerPosY = 150;
    
    const int esquerdaPlayer = 40;
	const int direitaPlayer = 40;
	const int baixoPlayer = 80;

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
            else if (event.key.code == sf::Keyboard::F2){
                    gameOver = false;
                    playerPosX = 300;
                    playerPosY = 150;
                    score = 0;
                    height = 160;
                    dy = 0;
                    textScore.setString("0");
                }
        }

        // Atualizacao dos estados do jogo (elementos)
        // escrever nickname pegar ele e salvar
        
        // Gameplay
        if(!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerPosX -= 3;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerPosX += 3;
            }
            
            playerSprite.setPosition(playerPosX, playerPosY);
            /* ESCREVER NOME DO JOGADOR
            textName.setPosition(350, 20);
            textName.setString();*/
            
            // Jogador quando sai pelo lado volta do outro
            if (playerPosX > 680) {
                playerPosX = -80;
            }
            if (playerPosX < -80) {
                playerPosX = 680;
            }

            // Pulo do jogador na plataforma
            for (size_t i = 0; i<7; i++)
            {
                if ((playerPosX + direitaPlayer > platformPosition[i].x)
                    && (playerPosX + esquerdaPlayer < platformPosition[i].x + platformTexture.getSize().x)
                    && (playerPosY + baixoPlayer > platformPosition[i].y)
                    && (playerPosY + baixoPlayer < platformPosition[i].y + platformTexture.getSize().y)
                    && (dy > 0)) {
                    dy = -12.5;
                }
                    
            }

            // Se o jogador cair até o final da tela será game over
            if(playerPosY > 840) {
                gameOver = true;
            }

        }

        // Desenha os frames
        window.clear();
        window.draw(backgroundSprite);


        /* INSERIR TELA DE NICKNAME
         if(writeNickname) {
            window.draw(nameSprite);
            // quando escrever o nickname atualizar para true
        } */

        // Mostrar menu
        /*if(gameOver && !writeNickname) {
            window.draw(menuSprite);
        }*/

        // Comecar jogo
        if(!gameOver) {
            // Desenhando as plataformas
            for (size_t i = 0; i<7; i++)
		    {
			    platformSprite.setPosition(platformPosition[i].x, platformPosition[i].y);
			    window.draw(platformSprite);
		    }
            window.draw(playerSprite);
            window.draw(textScore);
            //window.draw(textName);
        }
        // Tela de gameover
        if(gameOver) {
            window.draw(gameOverSprite);
        }
        window.display();
    }
    
    return 0;
}