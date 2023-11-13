#pragma once

#include "Rectangle.h"
#include "Level.h"
#include "Door.h"

struct InputData;

class Level;
class Door;

class Player : public Rectangle
{
public:
    Player();
    virtual ~Player() {}
    
    bool initialise(){};
    void move(InputData inputData, float deltaTime);
    void updatePhysics(float deltaTime);
    void update(float deltaTime);

    int getCoins() const { return m_coins; };

    bool isDead() const { return m_isDead; }
    void setIsDead(bool isDead) { m_isDead = isDead; }
    void resetCoins(){m_coins = 0;}

private:
    bool                    m_isGrounded = false;
    bool                    m_isDead = false;
    float                   m_jumpTimer = 0.0f;
    std::unique_ptr<Level>  m_pLevel;
    int                     m_coins = 0;
};
