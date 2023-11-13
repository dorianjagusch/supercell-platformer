#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "InputHandler.h"
#include "Player.h"
#include "resources/Resources.h"
#include "Rectangle.h"
#include "Coin.h"
#include "Level.h"

Game::Game() :
    m_state(State::WAITING),
    m_pClock(std::make_unique<sf::Clock>()),
    m_pPlayer(std::make_unique<Player>()),
    m_score(0),
    m_clearedLevels(0)
{
    initLevels(m_pPlayer);
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer);
}

Game::~Game()
{
    
}

bool Game::initialise(sf::Vector2f pitchSize)
{
    m_pClock->restart();
    std::string assetPath = Resources::getAssetPath();
    if (!m_font.loadFromFile(assetPath + "Lavigne.ttf"))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }

    //Initialize shapes from TileMap
    resetLevel(m_pLevels[m_clearedLevels]);
    return true;
}

void Game::initLevels(std::unique_ptr<Player>& player){
    std::vector<std::string> fileNames;

    for (const auto& entry : std::filesystem::directory_iterator{"../../../levels/"}) {
        if (entry.is_regular_file()) {
            fileNames.push_back(entry.path().filename().string());
        }
    }

    std::sort(fileNames.begin(), fileNames.end());

    for (const auto& fileName : fileNames) {
        try{
            m_pLevels.push_back(std::make_unique<Level>(fileName, player));
        }
        catch (std::exception &e){
            std::cerr << e.what() << std::endl;
        }
    }
}

void Game::resetLevel(std::unique_ptr<Level>& level)
{
    level->resetLevel();
}

void Game::update(float deltaTime)
{
    switch (m_state)
    {
        case State::WAITING:
        {
            if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
            {
                m_state = State::ACTIVE;
            }
        }
        break;
            
        case State::ACTIVE:
        {
            m_pGameInput->update(deltaTime);
            m_pPlayer->updatePhysics(deltaTime);
            m_pPlayer->update(deltaTime);

            if (m_pLevels[m_clearedLevels]->getPlayer()->isDead()){
                m_clearedLevels = 0;
                resetLevel(m_pLevels[m_clearedLevels]);
            }
            if (m_pLevels[m_clearedLevels]->getDoor()->isTriggered())
            {
                m_clearedLevels++;
                if (m_clearedLevels == LevelCount)
                {
                    m_clearedLevels = 0;
                    m_score = 0;
                    m_state = State::WAITING;
                    m_pClock->restart();
                }
                resetLevel(m_pLevels[m_clearedLevels]);
            }
        }
        break;
    }
    int i = 0;
    auto& Coins = m_pLevels[m_clearedLevels]->getCoins();
    while (i < Coins.size())
    {
        if (Coins[i]->getCollected())
        {
            std::swap(Coins[i], Coins.back());
            Coins.pop_back();
            continue;
        }
        i++;
    }

    
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //  Draw texts.
    if (m_state == State::WAITING)
    {
        sf::Text startText;
        startText.setFont(m_font);
        startText.setString("Game Start!");
        startText.setFillColor(sf::Color::White);
        startText.setPosition(80.0f, 80.0f);
        startText.setStyle(sf::Text::Bold);
        target.draw(startText);
    }
    else
    {
        sf::Text coinText;
        coinText.setFont(m_font);
        coinText.setFillColor(sf::Color::White);
        coinText.setStyle(sf::Text::Bold);
        coinText.setString(std::to_string(m_pLevels[m_clearedLevels]->getPlayer()->getCoins()));
        coinText.setColor(sf::Color::Yellow);
        coinText.setPosition(sf::Vector2f(ScreenWidth - coinText.getLocalBounds().getSize().x, 0));
        target.draw(coinText);
    }

    // Draw player.
    m_pPlayer->draw(target, states);

    //  Draw world.
    for (auto& temp : m_pLevels[m_clearedLevels]->getCoins())
    {
        temp->draw(target, states);
    }
    for (auto& temp : m_pLevels[m_clearedLevels]->getCoins())
    {
        temp->draw(target, states);
    }

    m_pLevels[m_clearedLevels]->getDoor()->draw(target, states);
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}


void Game::onMouseClick(sf::Mouse::Button key){
    m_pGameInput->onMouseDown(key);
}

void Game::onMouseRelease(sf::Mouse::Button key){
    m_pGameInput->onMouseRelease(key);
}

