#pragma once

#include "external/json/include/nlohmann/json.hpp"
#include <Vector2.hpp>
#include <string>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <filesystem>


class Level {
    public:
        Level(const std::string& fileName);
        ~Level();
        void          setDimensions(size_t xDim, size_t yDim);
        void          setPlayerPos(size_t x, size_t y);
        void          setDoorPos(size_t x, size_t y);
        int           getTile(size_t x, size_t y);
        void          setTile(size_t x, size_t y, int tileType);
        sf::Vector2i  getTileIndices(int pixelX, int pixelY, int tileSize);
        void          saveLevel(const std::string& fileName);
        bool          isFileGood();

    private:
        size_t                           m_pLvlWidth;
        size_t                           m_pLvlHeight;
        sf::Vector2f                     m_pPlayerPos;
        sf::Vector2f                     m_pDoorPos;
        std::unique_ptr<nlohmann::json>  m_pTiles;

};