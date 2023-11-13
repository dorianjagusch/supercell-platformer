#pragma once

#include <nlohmann/json.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <filesystem>
#include "Player.h"
#include "Rectangle.h"
#include "Coin.h"
#include "Constants.h"
#include "Door.h"

class Player;
class Door;

class Level {
    public:
        Level(const std::string& fileName, std::unique_ptr<Player>& player);
        ~Level();

        void                    setDimensions(size_t xDim, size_t yDim);
        void                    setPosition(std::unique_ptr<sf::Transformable>& entity, size_t x, size_t y);
        int                     getTile(size_t x, size_t y);
        void                    setTile(size_t x, size_t y, int tileType);
        sf::Vector2i            getTileIndices(int pixelX, int pixelY, int tileSize) const;
        void                    saveLevel(const std::string& fileName) const;
        void                    resetLevel();

        std::vector<std::unique_ptr<Coin>>&         getCoins();
        std::vector<std::unique_ptr<Rectangle>>&    getRectangles();
        std::unique_ptr<Player>&                    getPlayer();
        std::unique_ptr<Door>&                      getDoor();

    private:
        size_t                                  m_pLvlWidth;
        size_t                                  m_pLvlHeight;
        size_t                                  m_pGridSize;
        size_t                                  m_pTileSize;
        std::unique_ptr<Player>&                m_pPlayer;
        std::unique_ptr<Door>                   m_pDoor;
        std::vector<std::unique_ptr<Rectangle>> m_pRectangles;
        std::vector<std::unique_ptr<Coin>>      m_pCoins;
        std::unique_ptr<nlohmann::json>         m_pTiles;

};