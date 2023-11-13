#pragma once

#include "Controller.h"
#include <SFML/Window/Keyboard.hpp>

class Player;
class Game;

struct InputData
{
    bool m_movingUp = false;
    bool m_movingDown = false;
    bool m_movingLeft = false;
    bool m_movingRight = false;
    bool m_MouseRight = false;
    bool m_MouseLeft = false;

    bool hasInputs() { return m_movingUp || m_movingDown || m_movingLeft || m_movingRight;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

    void onMouseDown(sf::Mouse::Button key);
    void onMouseRelease(sf::Mouse::Button key);

private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
};
