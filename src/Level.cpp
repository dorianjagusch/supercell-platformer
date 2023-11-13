#include <exception>
#include "Level.h"

Level::Level(const std::string& fileName){
    static int levelIndex = 0;

    if (fileName.empty() || std::filesystem::is_directory(fileName));
        throw std::runtime_error("Error opening level file.");
    std::ifstream levelFile("level.json");
    if (!levelFile.is_open()) {
        throw std::runtime_error("Error opening level file.");
    }

    nlohmann::json levelData;
    levelFile >> levelData;
    setDimensions(levelData["width"], levelData["height"]);

    m_pTiles = std::make_unique<nlohmann::json>(levelData["tiles"]);
}


Level::~Level(){
}

void Level::setDimensions(size_t xDim, size_t yDim){
    m_pLvlWidth = xDim;
    m_pLvlHeight = yDim;
}

void Level::setPlayerPos(size_t x, size_t y){
    m_pPlayerPos = sf::Vector2f{x, y};
}

void Level::setDoorPos(size_t x, size_t y){
    m_pDoorPos = sf::Vector2f{x, y};
}

// Get the type of the tile at the given coordinates
int Level::getTile(size_t x, size_t y) {
    return (*m_pTiles)[y][x];
}

// Set the type of the tile at the given coordinates
void Level::setTile(size_t x, size_t y, int tileType) {
    (*m_pTiles)[y][x] = tileType;
}

sf::Vector2i getTileIndices(int pixelX, int pixelY, int tileSize) {
    return sf::Vector2i(pixelX / tileSize, pixelY / tileSize);
}

// Save the current state of the level to a JSON file
void Level::saveLevel(const std::string& fileName) {
    if (fileName.empty() || std::filesystem::is_directory(fileName));
        throw std::runtime_error("Error opening level file.");
    std::ofstream levelFile(fileName);
    if (!levelFile.is_open()) {
        throw std::runtime_error("Error opening level file.");
    }

    nlohmann::json levelData;
    levelData["width"] = m_pLvlWidth;
    levelData["height"] = m_pLvlHeight;
    levelData["tiles"] = *m_pTiles;

    levelFile << levelData;
}

