#include <exception>
#include "Level.h"

Level::Level(const std::string& fileName, std::unique_ptr<Player> &player):
    m_pPlayer(player)
{
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

std::vector<std::unique_ptr<Coin>>& Level::getCoins(){
    return m_pCoins;
}

std::vector<std::unique_ptr<Rectangle>>& Level::getRectangles(){
    return m_pRectangles;
}

std::unique_ptr<Player>& Level::getPlayer(){
    return m_pPlayer;
}

std::unique_ptr<Door>& Level::getDoor(){
    return m_pDoor;
}

void Level::setDimensions(size_t xDim, size_t yDim){
    m_pLvlWidth = xDim;
    m_pLvlHeight = yDim;
}

void Level::setPosition(std::unique_ptr<sf::Transformable>& entity, size_t x, size_t y){
    entity->setPosition(sf::Vector2f{float(x * m_pTileSize), float(y * m_pTileSize)});
}


// Get the type of the tile at the given coordinates
int Level::getTile(size_t x, size_t y) {
    return (*m_pTiles)[y][x];
}

// Set the type of the tile at the given coordinates
void Level::setTile(size_t x, size_t y, int tileType) {
    (*m_pTiles)[y][x] = tileType;
}

sf::Vector2i Level::getTileIndices(int pixelX, int pixelY, int tileSize) const{
    return sf::Vector2i(pixelX / tileSize, pixelY / tileSize);
}

void Level::resetLevel()
{
    getCoins().clear();
    getRectangles().clear();

    m_pPlayer->setIsDead(false);
    m_pPlayer->resetCoins();
    m_pDoor->setTriggered(false);

    for (int y = 0; y < m_pGridSize; y++){

        for (int x = 0; x < m_pGridSize; x++){

            const sf::Vector2f worldPos = sf::Vector2f(x * m_pTileSize, y * m_pTileSize);
            switch ((*m_pTiles)[x][y].get<eTile>()) {

                case    eTile::eCoin:
                    m_pCoins.push_back(std::make_unique<Coin>(CoinRadius, worldPos));
                    break;
                case    eTile::eBlock:
                    m_pRectangles.push_back(std::make_unique<Rectangle>(sf::Vector2f{float(m_pTileSize), float(m_pTileSize)}, worldPos));
                    break;
                case    eTile::ePlayerSpawn :
                    m_pPlayer->setPosition(worldPos);
                    break;
                case    eTile::eDoor :
                    m_pDoor->setPosition(worldPos);
                    break;
                default:
                    break;
            }
        }
    }
}

// Save the current state of the level to a JSON file
void Level::saveLevel(const std::string& fileName) const{
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

