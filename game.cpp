#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

    // Gravas pontuações
        // Estrutura
        struct info {
            int scores;
            string nicknames;
        };
        info ranking;

        bool cmp(const info &a, const info &b) {
            return a.scores > b.scores || (a.scores == b.scores && a.nicknames < b.nicknames);
        }

        string salvarNick;
        int salvarScore;


int main() {   
    // Iniciando tela
    const int windowWidth = 600, windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tux Jump");
    window.setFramerateLimit(60);

    // Carregamento das texturas
    sf::Texture backgroundTexture; // Textura do background
    backgroundTexture.loadFromFile("./assets/backgroundGame.png");
    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Texture nameScreenTexture; // Textura do Nickname
    nameScreenTexture.loadFromFile("./assets/nameScreen.png");
    sf::Sprite nameSprite(nameScreenTexture);

    sf::Texture menuTexture; // Textura do Menu
    menuTexture.loadFromFile("./assets/menuGame.png");
    sf::Sprite menuSprite(menuTexture);

    sf::Texture gameOverTexture; // Textura do GameOver
    gameOverTexture.loadFromFile("./assets/gameoverScreen.png");
    sf::Sprite gameOverSprite(gameOverTexture);

    sf::Texture platformTexture; // Textura das plataformas 
    platformTexture.loadFromFile("./assets/plataformaGame.png");
    sf::Sprite platformSprite(platformTexture);

    sf::Texture tuxTexture; // Textura do Tux
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

    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(42);
    playerText.setOutlineColor(sf::Color::Black);
    playerText.setFillColor(sf::Color::White);

    //Vetor para salvar os dados da estrutura
    vector<info>rankingFinal;

        //Partidas anteriores
        ifstream entrada;
        entrada.open("ranking.txt");

        if (entrada) {
            while (entrada >> ranking.nicknames) {
                entrada >> ranking.scores;
                rankingFinal.push_back(ranking);
            }
            entrada.close();  
        }   
        rankingFinal.push_back(ranking);
        salvarNick = ranking.nicknames;
        salvarScore = ranking.scores;

    // Iniciando plataformas
    sf::Vector2u platformPosition[6];
	std::uniform_int_distribution<unsigned> x(0, 600 - platformTexture.getSize().x);
	std::uniform_int_distribution<unsigned> y(100, 900);
	std::default_random_engine e(time(0));
    for(size_t i = 0; i<6; i++)
	{
		platformPosition[i].y = y(e);
        platformPosition[i].x = x(e);
	}

    // Iniciando variaveis
    bool writeNickname = true;
    bool gameOver = true;
    bool telaGameOver = true;
    int score = 0;
    int height = 160;
    string nickname;
    float dy = 0;
    float playerPosX = 300, playerPosY = 150;
    bool aberto = false;
    
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
            else if (event.type == sf::Event::TextEntered) {
                    if (playerInput.getSize() < 10) {
                        playerInput.replace(sf::String(" "), sf::String(""));
                        playerInput.replace(sf::String(""), sf::String(""));
                        playerInput +=event.text.unicode;
                        playerText.setString(playerInput);
                        nickname = playerText.getString();
                    }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            // sem restart
        }

        if(writeNickname && gameOver) {
            playerText.setPosition(240, 420);
            if (event.key.code == sf::Keyboard::F1) {
                writeNickname = false;
                gameOver = true;
                telaGameOver = false;
            }
        }

        if(gameOver && !writeNickname) {
            if (event.key.code == sf::Keyboard::Space) {    
                gameOver = false;
            }
        }
        
        // Gameplay
        if(!gameOver && !writeNickname) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                playerPosX -= 5;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                playerPosX += 5;
            }
            
            playerSprite.setPosition(playerPosX, playerPosY);
            
            if (!aberto) {
                aberto = true;
                ifstream entrada;
                entrada.open("ranking.txt");

                if (entrada) {
                    while (entrada >> ranking.nicknames) {
                        entrada >> ranking.scores;
                        entrada.ignore();
                        if (ranking.scores > 0) {
                        rankingFinal.push_back(ranking);
                        }
                    }
                    entrada.close();

                    salvarNick = ranking.nicknames;
                    salvarScore = ranking.scores;
                    ofstream saida;
                    saida.open("ranking.txt");
                        for (auto i : rankingFinal){
                            saida << i.nicknames << " " << i.scores << endl;
                        }
                        saida.close();
                    }
                }

                ranking.nicknames = nickname;
                playerInput.clear();
            
            // Jogador quando sai pelo lado volta do outro
            if (playerPosX > 680) {
                playerPosX = -80;
            }
            if (playerPosX < -80) {
                playerPosX = 680;
            }

            // Adicionar nova plataforma conforme jogador sobe
            if (playerPosY < height) {
			for (size_t i = 0; i<6; i++)
                {
                    playerPosY = height;
                    platformPosition[i].y -= dy; 
                    if (platformPosition[i].y > 700)
                    {
                        platformPosition[i].y = 0;
                        platformPosition[i].x = x(e);
                    }
                        
                }
            }
            
            // Pulo do jogador na plataforma
            for (size_t i = 0; i<6; i++)
            {
                if ((playerPosX + direitaPlayer > platformPosition[i].x)
                    && (playerPosX + esquerdaPlayer < platformPosition[i].x + platformTexture.getSize().x)
                    && (playerPosY + baixoPlayer > platformPosition[i].y)
                    && (playerPosY + baixoPlayer < platformPosition[i].y + platformTexture.getSize().y)
                    && (dy > 0)) {
                    dy = -12.5;
                }
                    
            }

            // Adicionando score ao jogador
            if (playerPosY == height && dy < (-1.62)) {
                score++;
                textScore.setPosition(20, 20);
                textScore.setString(std::to_string(score));
            }
            dy += 0.2;
            playerPosY += dy;


            // Se o jogador cair até o final da tela será game over
            if(playerPosY > 840) {
                if (salvarScore < score) {
                    ranking.scores = score;
                    rankingFinal.pop_back();
                    rankingFinal.push_back(ranking);
                }

                if (salvarScore < score) {
                    ranking.scores = score;
                    rankingFinal.pop_back();
                    rankingFinal.push_back(ranking);
                    sort(rankingFinal.begin(), rankingFinal.end(), cmp);
                    ofstream saida;
                    saida.open("ranking.txt");
                        for (auto i : rankingFinal){
                            saida << i.nicknames << " " << i.scores << endl;
                        }
                        saida.close();

                        ifstream entrada;
                        entrada.open("ranking.txt");

                        if (entrada) {
                            rankingFinal.clear();
                            while (entrada >> ranking.nicknames) {
                            entrada >> ranking.scores;
                            entrada.ignore();
                                if (ranking.scores > 0) {
                                    rankingFinal.push_back(ranking);
                                 }
                            }
                            entrada.close();

                            ofstream saidaf;
                            saidaf.open("ranking.txt");
                                for (auto i : rankingFinal){
                                    saidaf << i.nicknames << " " << i.scores  << endl;
                                }
                            saidaf.close();
                        }
                    
                }
                gameOver = true;
                telaGameOver = true;
            }
        }

        // Desenha os frames
        window.clear();
        window.draw(backgroundSprite);

        // Comecar jogo
        if(!gameOver && !writeNickname) {
            // Desenhando as plataformas
            for (size_t i = 0; i<6; i++)
		    {
			    platformSprite.setPosition(platformPosition[i].x, platformPosition[i].y);
			    window.draw(platformSprite);
		    }
            window.draw(playerSprite);
            window.draw(textScore);
            // window.draw(textName);
        }

        // Tela de gameover
        if(telaGameOver && gameOver && playerPosY > 840) {
            window.draw(gameOverSprite);
        }

        // Mostrar menu
        if(!telaGameOver && gameOver && !writeNickname) {
            window.draw(menuSprite);
        }

        ///INSERIR TELA DE NICKNAME
        if(writeNickname) {
            window.draw(nameSprite);
            // quando escrever o nickname atualizar para true
            window.draw(playerText);
        }

        window.display();
    }
    
    return 0;
}
