
#include "Board.hpp"

using namespace std;
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
    Hexagon hex1(Mountains, 10, center1, 1);
    hex1.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][2] = hex1;
    this->_hexagonsMap[center1] = hex1;
    

    Point center2(0, 3);
    Hexagon hex2(Pasture, 2, center2, 2);
    hex2.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][3] = hex2;
    this->_hexagonsMap[center2] = hex2;
    

    Point center3(0, 4);
    Hexagon hex3(Forest, 9, center3, 3);
    hex3.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][4] = hex3;
    this->_hexagonsMap[center3] = hex3;

    Point center4(1, 1);
    Hexagon hex4(Field, 12, center4, 4);
    hex4.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][1] = hex4;
    this->_hexagonsMap[center4] = hex4;

    Point center5(1, 2);
    Hexagon hex5(Hills, 6, center5, 5);
    hex5.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][2] = hex5;
    this->_hexagonsMap[center5] = hex5;

    Point center6(1, 3);
    Hexagon hex6(Pasture, 4, center6, 6);
    hex6.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][3] = hex6;
    this->_hexagonsMap[center6] = hex6;

    Point center7(1, 4);
    Hexagon hex7(Hills, 10, center7, 7);
    hex7.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][4] = hex7;
    this->_hexagonsMap[center7] = hex7;

    Point center8(2, 0);
    Hexagon hex8(Field, 9, center8, 8);
    hex8.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][0] = hex8;
    this->_hexagonsMap[center8] = hex8;

    Point center9(2, 1);
    Hexagon hex9(Forest, 11, center9, 9);
    hex9.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][1] = hex9;
    this->_hexagonsMap[center9] = hex9;

    Point center10(2, 2);
    Hexagon hex10(Desert, 0, center10, 10);
    hex10.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][2] = hex10;
    this->_hexagonsMap[center10] = hex10;

    Point center11(2, 3);
    Hexagon hex11(Forest, 3, center11, 11);
    hex11.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][3] = hex11;
    this->_hexagonsMap[center11] = hex11;

    Point center12(2, 4);
    Hexagon hex12(Mountains, 8, center12, 12);
    hex12.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][4] = hex12;
    this->_hexagonsMap[center12] = hex12;

    Point center13(3, 0);
    Hexagon hex13(Forest, 8, center13, 13);
    hex13.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][0] = hex13;
    this->_hexagonsMap[center13] = hex13;

    Point center14(3, 1);
    Hexagon hex14(Mountains, 3, center14, 14);
    hex14.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][1] = hex14;
    this->_hexagonsMap[center14] = hex14;

    Point center15(3, 2);
    Hexagon hex15(Field, 4, center15, 15);
    hex15.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][2] = hex15;
    this->_hexagonsMap[center15] = hex15;

    Point center16(3, 3);
    Hexagon hex16(Pasture, 5, center16, 16);
    hex16.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][3] = hex16;
    this->_hexagonsMap[center16] = hex16;

    Point center17(4, 0);
    Hexagon hex17(Hills, 5, center17, 17);
    hex17.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][0] = hex17;
    this->_hexagonsMap[center17] = hex17;

    Point center18(4, 1);
    Hexagon hex18(Field, 6, center18, 18);
    hex18.initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][1] = hex18;
    this->_hexagonsMap[center18] = hex18;

    Point center19(4, 2);
    Hexagon hex19(Pasture, 11, center19, 19);
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
            if (this->_hexagonGrid[i][j].getLandType() != NONE) {
                
                cout << this->_hexagonGrid[i][j];
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
            if (hex.getLandType() == places[0] && hex.getResourceType() == placesNum[0]) {
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