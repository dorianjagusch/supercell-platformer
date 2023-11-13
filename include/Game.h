#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <filesystem>
#include "Constants.h"
#include "Door.h"

class Player;
class Game;
class GameInput;
class Rectangle;
class Coin;
class Door;
class Level;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
        WAITING,
        ACTIVE,
        EDIT
    };
    
    Game();
    ~Game();
    
    bool initialise(sf::Vector2f pitchSize);
    void update(float deltaTime);
    void resetLevel(std::unique_ptr<Level>& level);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void initLevels(std::unique_ptr<Player>& player);
    size_t countFilesinDir(const std::string& path);
    
    State getState() const { return m_state; }
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
    void onMouseClick(sf::Mouse::Button key);
    void onMouseRelease(sf::Mouse::Button key);

private:

    std::vector<std::unique_ptr<Level>> m_pLevels;

    State m_state;
     std::unique_ptr<Player>   m_pPlayer;
    std::unique_ptr<sf::Clock> m_pClock;
    std::unique_ptr<GameInput> m_pGameInput;

    int m_clearedLevels;
    int m_score;
    
    sf::Font m_font;
};
