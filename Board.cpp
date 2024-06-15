
#include "Board.hpp"

using namespace ariel;

// Constructor
Board::Board()
{
    // Initialize the hexagon grid with null hexagons
    this->_hexagonGrid = vector<vector<Hexagon>>(5, vector<Hexagon>(5, Hexagon()));
    this->initHexagons();
}

// Destructor
Board::~Board() {}

void Board::initHexagons()
{
    Point center1(0, 2);
    Hexagon hex1(LandType::Mountains, 10, center1, 1);
    hex1.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][2] = hex1;
    this->_hexagonsMap[center1] = hex1;
    

    Point center2(0, 3);
    Hexagon hex2(LandType::Pasture, 2, center2, 2);
    hex2.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][3] = hex2;
    this->_hexagonsMap[center2] = hex2;
    

    Point center3(0, 4);
    Hexagon hex3(LandType::Forest, 9, center3, 3);
    hex3.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][4] = hex3;
    this->_hexagonsMap[center3] = hex3;

    Point center4(1, 1);
    Hexagon hex4(LandType::Field, 12, center4, 4);
    hex4.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][1] = hex4;
    this->_hexagonsMap[center4] = hex4;

    Point center5(1, 2);
    Hexagon hex5(LandType::Hills, 6, center5, 5);
    hex5.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][2] = hex5;
    this->_hexagonsMap[center5] = hex5;

    Point center6(1, 3);
    Hexagon hex6(LandType::Pasture, 4, center6, 6);
    hex6.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][3] = hex6;
    this->_hexagonsMap[center6] = hex6;

    Point center7(1, 4);
    Hexagon hex7(LandType::Hills, 10, center7, 7);
    hex7.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][4] = hex7;
    this->_hexagonsMap[center7] = hex7;

    Point center8(2, 0);
    Hexagon hex8(LandType::Field, 9, center8, 8);
    hex8.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][0] = hex8;
    this->_hexagonsMap[center8] = hex8;

    Point center9(2, 1);
    Hexagon hex9(LandType::Forest, 11, center9, 9);
    hex9.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][1] = hex9;
    this->_hexagonsMap[center9] = hex9;

    Point center10(2, 2);
    Hexagon hex10(LandType::Desert, 0, center10, 10);
    hex10.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][2] = hex10;
    this->_hexagonsMap[center10] = hex10;

    Point center11(2, 3);
    Hexagon hex11(LandType::Forest, 3, center11, 11);
    hex11.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][3] = hex11;
    this->_hexagonsMap[center11] = hex11;

    Point center12(2, 4);
    Hexagon hex12(LandType::Mountains, 8, center12, 12);
    hex12.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][4] = hex12;
    this->_hexagonsMap[center12] = hex12;

    Point center13(3, 0);
    Hexagon hex13(LandType::Forest, 8, center13, 13);
    hex13.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][0] = hex13;
    this->_hexagonsMap[center13] = hex13;

    Point center14(3, 1);
    Hexagon hex14(LandType::Mountains, 3, center14, 14);
    hex14.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][1] = hex14;
    this->_hexagonsMap[center14] = hex14;

    Point center15(3, 2);
    Hexagon hex15(LandType::Field, 4, center15, 15);
    hex15.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][2] = hex15;
    this->_hexagonsMap[center15] = hex15;

    Point center16(3, 3);
    Hexagon hex16(LandType::Pasture, 5, center16, 16);
    hex16.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][3] = hex16;
    this->_hexagonsMap[center16] = hex16;

    Point center17(4, 0);
    Hexagon hex17(LandType::Hills, 5, center17, 17);
    hex17.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][0] = hex17;
    this->_hexagonsMap[center17] = hex17;

    Point center18(4, 1);
    Hexagon hex18(LandType::Field, 6, center18, 18);
    hex18.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][1] = hex18;
    this->_hexagonsMap[center18] = hex18;

    Point center19(4, 2);
    Hexagon hex19(LandType::Pasture, 11, center19, 19);
    hex19.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][2] = hex19;
    this->_hexagonsMap[center19] = hex19;
}

void Board::drawHexagon(int row, int col, const Hexagon& hexagon) const {
    std::vector<std::string> hexArt = {
        "  /\\  ",
        " /  \\ ",
        "/    \\",
        "\\    /",
        " \\  / ",
        "  \\/  "
    };

    int colOffset = col * 4; // Adjusting width offset for pointy-topped hexagon
    int rowOffset = row * 3; // Adjusting height offset for pointy-topped hexagon

    for (size_t i = 0; i < hexArt.size(); ++i) {
        std::cout << std::setw(colOffset) << "" << hexArt[i] << std::endl;
    }
}

void Board::printBoard() {
    for (size_t i = 0; i < this->_hexagonGrid.size(); ++i) {
        for (size_t j = 0; j < this->_hexagonGrid[i].size(); ++j) {
            if (this->_hexagonGrid[i][j].getLandType() != LandType::None) {
                
                cout << this->_hexagonGrid[i][j].getLandType() << " " << this->_hexagonGrid[i][j].getValue();
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
}


shared_ptr<Vertex> Board::getVertex(vector<LandType>& places, vector<int>& placesNum) const {
        if (places.size() != placesNum.size() || places.size() != 2) {
            throw std::invalid_argument("The size of places and placesNum must be the same and exactly 2.");
        }

        // Find vertices for the first hexagon
        std::set<std::shared_ptr<Vertex>> potentialVertices;
        for (const auto& [key, hex] : this->_hexagonsMap) {
            if (hex.getLandType() == places[0] && hex.getValue() == placesNum[0]) {
                const auto& vertices = hex.getVerticesMap();
                for (const auto& [vertexKey, vertex] : vertices) {
                    potentialVertices.insert(vertex);
                }
                break; // We assume there's only one matching hexagon for each type/number combination
            }
        }

        // Filter vertices that are also part of the second hexagon
        for (const auto& [key, hex] : this->_hexagonsMap) {
            if (hex.getLandType() == places[1] && hex.getValue() == placesNum[1]) {
                const auto& vertices = hex.getVerticesMap();
                for (const auto& [vertexKey, vertex] : vertices) {
                    if (potentialVertices.find(vertex) != potentialVertices.end()) {
                        return vertex;
                    }
                }
            }
        }

        return nullptr; // No matching vertex found
    }

bool Board::hasRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const {
    auto key = std::make_pair(v1, v2);
    auto it = _edgesMap.find(key);
    return it != _edgesMap.end() && it->second->hasRoad();
}

void Board::placeRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, const Player* owner) {
        auto key = std::make_pair(v1, v2);
        auto it = _edgesMap.find(key);
        if (it != _edgesMap.end()) {
            it->second->setRoad(owner);
        } else {
            _edgesMap[key] = make_shared<Trail>(v1, v2);
            _edgesMap[key]->setRoad(owner);
        }
    }

bool Board::vertexMatches(shared_ptr<Vertex> v, vector<LandType>& places, vector<int>& placesNum) const {
    if (places.size() != placesNum.size() || places.size() != 2) {
        throw std::invalid_argument("The size of places and placesNum must be the same and exactly 2.");
    }

    // Track found places
    int matchCount = 0;
    
    for (const auto& hex : v->getHexagons()) {
        if ((hex->getLandType() == places[0] && hex->getValue() == placesNum[0]) || 
            (hex->getLandType() == places[1] && hex->getValue() == placesNum[1])) {
            matchCount++;
        }
    }
    
    // If both places are matched
    return (matchCount == 2);
}

vector<shared_ptr<Vertex>> Board::getNeighborVertices(shared_ptr<Vertex> v) const {
    vector<shared_ptr<Vertex>> neighbors;
    
    // Get all the trails connected to the vertex
    const auto& trails = v->getTrails();
    
    for (const auto& trail : trails) {
        // Get the vertices connected by the trail
        const auto& start = trail->getStart();
        const auto& end = trail->getEnd();
        
        // Add the vertex that is not the input vertex
        if (start != v) {
            neighbors.push_back(start);
        }
        if (end != v) {
            neighbors.push_back(end);
        }
    }
    
    return neighbors;
}

shared_ptr<Trail> Board::getTrail(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const {
    auto key = std::make_pair(v1, v2);
    auto it = _edgesMap.find(key);
    if (it != _edgesMap.end()) {
        return it->second;
    }
    return nullptr;
}

