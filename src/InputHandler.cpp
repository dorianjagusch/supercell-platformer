#include "InputHandler.h"
#include "Player.h"

GameInput::GameInput(Game* pGame, std::unique_ptr<Player>& player) :
    m_pGame(pGame), m_pPlayer(player)
{
}

GameInput::~GameInput()
{
}

void GameInput::update(float deltaTime)
{
    if (m_inputData.hasInputs())
    {
        m_pPlayer->move(m_inputData, deltaTime);
    }
}

void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = true;
    }
}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_movingUp = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_movingDown = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_movingLeft = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_movingRight = false;
    }
}

void GameInput::onMouseDown(sf::Mouse::Button key)
{
    if (key == sf::Mouse::Left)
    {
        m_inputData.m_MouseLeft = true;
    }
    else if (key == sf::Mouse::Right)
    {
        m_inputData.m_MouseRight = true;
    }
}


void GameInput::onMouseRelease(sf::Mouse::Button key)
{
    if (key == sf::Mouse::Left)
    {
        m_inputData.m_MouseLeft = false;
    }
    else if (key == sf::Mouse::Right)
    {
        m_inputData.m_MouseRight = false;
    }
}