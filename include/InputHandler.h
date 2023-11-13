#pragma once

#include "Controller.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

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
    GameInput(Game* pGame, std::unique_ptr<Player>& player);
    ~GameInput();

    void update(float deltaTime);
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

    void onMouseDown(sf::Mouse::Button key);
    void onMouseRelease(sf::Mouse::Button key);

private:
    InputData m_inputData;
    std::unique_ptr<Player>& m_pPlayer; //dangerous
    Game* m_pGame;
};
