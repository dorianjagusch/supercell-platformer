#include "Player.h"
#include "InputHandler.h"
#include "Constants.h"
#include "Coin.h"
#include <vector>
#include "Game.h"
#include "Door.h"

Player::Player() : Rectangle(sf::Vector2f(PlayerWidth, PlayerHeight))
{
    setPosition(sf::Vector2f(ScreenWidth * 0.5f, ScreenHeight * 0.5f)); //TODO: spawn position constant?
    setOrigin(sf::Vector2f(0.0f, 0.0f));
    setColor(sf::Color::Blue);
}

void Player::move(InputData inputData, float deltaTime)
{
    float xSpeed = 0.0f;
    
    xSpeed -= inputData.m_movingLeft * PlayerSpeed;
    xSpeed += inputData.m_movingRight * PlayerSpeed;
    xSpeed *= deltaTime;
    
    sf::Transformable::move(sf::Vector2f(xSpeed, 0.0f));

    auto& Rectangles = m_pLevel->getRectangles();
    for (auto& Rectangle : Rectangles)
    {
        //Move player back if collided with level geometry
        if (Rectangle->collidesWith(this))
        {
            sf::Transformable::move(sf::Vector2f(-xSpeed, 0.0f));
        }
    }
    
    setPosition(std::clamp(getPosition().x, 0.0f, (float)ScreenWidth), getPosition().y); //TODO: clean

    if (inputData.m_movingUp && m_jumpTimer == 0.0f && m_isGrounded)
    {
        m_jumpTimer = PlayerJumpTime;
    }
}

void Player::updatePhysics(float deltaTime)
{
    m_jumpTimer -= deltaTime;
    if (m_jumpTimer < 0.0f)
    {
        m_jumpTimer = 0.0f;
    }

    float ySpeed = 0.0f;
    if (m_jumpTimer > 0.0f)
    {
        ySpeed = JumpYVelocity;
    }
    else
    {
        ySpeed = Gravity;
    }
    sf::Transformable::move(0.0f, ySpeed * deltaTime);
    
    m_isGrounded = false;
    auto& Rectangles = m_pLevel->getRectangles();
    for (auto& Rectangle : Rectangles)
    {
        //Move player back if collided with level geometry
        if (Rectangle->collidesWith(this))
        {
            m_jumpTimer = 0.0f;
            sf::Transformable::move(sf::Vector2f(0.0f, -ySpeed * deltaTime));
            m_isGrounded = true;
        }
    }
    
    m_isDead = getPosition().y > ScreenHeight;
}

void Player::update(float deltaTime)
{
    std::vector<std::unique_ptr<Coin>>& Coins = m_pLevel->getCoins();
    int i = 0;

    for (auto& temp : Coins)
    {
        if (temp->collidesWith(this))
        {
            temp->setCollected(true);
            m_coins++;
        }
    }

    if (m_pLevel->getDoor()->collidesWith(this))
    {
        m_pLevel->getDoor()->setTriggered(true);
    }
}

