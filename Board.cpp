// ID: 205739907
// Email: eladima66@gmail.com

#include <SFML/Graphics.hpp>
#include "Board.hpp"

using namespace ariel;

// Constructor
Board::Board()
{
    // Initialize the hexagon grid with hexagons using the default constructor
    this->_hexagonGrid = vector<vector<shared_ptr<Hexagon>>>(5, vector<shared_ptr<Hexagon>>(5));
    this->initHexagons();
}

// Destructor
Board::~Board()
{
    // Clean up the hexagons
    for (size_t i = 0; i < this->_hexagonGrid.size(); ++i)
    {
        for (size_t j = 0; j < this->_hexagonGrid[i].size(); ++j)
        {
            this->_hexagonGrid[i][j].reset();
        }
    }
    this->_hexagonGrid.clear();

    // Clean up the hexagons
    for (auto &pair : _hexagonsMap)
    {
        pair.second.reset(); // Explicitly reset each shared_ptr
    }
    _hexagonsMap.clear();
}

void Board::initHexagons()
{
    // Define the moves for the hexagons
    double rightMove = sqrt(3);
    double downLeftMoveY = 1.5;
    double downRightMoveX = sqrt(3) / 2;
    // Define the starting coordinates
    double startingX = -2;
    double startingY = 2;

    double x = -2;
    double y = 2;
    // Create the hexagons as they appear on the actual board
    // We start from the top left corner and move to the right and then down
    Point center1(x, y);
    shared_ptr<Hexagon> hex1 = make_shared<Hexagon>(LandType::Mountains, 10, center1, 1);

    hex1->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][2] = hex1;
    this->_hexagonsMap[center1] = hex1;
    x += rightMove;
    Point center2(x, y);
    shared_ptr<Hexagon> hex2 = make_shared<Hexagon>(LandType::Pasture, 2, center2, 2);

    hex2->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][3] = hex2;
    this->_hexagonsMap[center2] = hex2;
    x += rightMove;
    Point center3(x, y);
    shared_ptr<Hexagon> hex3 = make_shared<Hexagon>(LandType::Forest, 9, center3, 3);

    hex3->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[0][4] = hex3;
    this->_hexagonsMap[center3] = hex3;

    // Move to the next row (row 2)
    x = startingX - downRightMoveX;
    startingX -= downRightMoveX;
    y = startingY - downLeftMoveY;
    startingY -= downLeftMoveY;

    Point center4(x, y);
    shared_ptr<Hexagon> hex4 = make_shared<Hexagon>(LandType::Field, 12, center4, 4);

    hex4->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][1] = hex4;
    this->_hexagonsMap[center4] = hex4;
    x += rightMove;
    Point center5(x, y);
    shared_ptr<Hexagon> hex5 = make_shared<Hexagon>(LandType::Hills, 6, center5, 5);

    hex5->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][2] = hex5;
    this->_hexagonsMap[center5] = hex5;
    x += rightMove;
    Point center6(x, y);
    shared_ptr<Hexagon> hex6 = make_shared<Hexagon>(LandType::Pasture, 4, center6, 6);

    hex6->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][3] = hex6;
    this->_hexagonsMap[center6] = hex6;
    x += rightMove;
    Point center7(x, y);
    shared_ptr<Hexagon> hex7 = make_shared<Hexagon>(LandType::Hills, 10, center7, 7);

    hex7->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[1][4] = hex7;
    this->_hexagonsMap[center7] = hex7;
    // Move to the next row (row 3)
    x = startingX - downRightMoveX;
    startingX -= downRightMoveX;
    y = startingY - downLeftMoveY;
    startingY -= downLeftMoveY;

    Point center8(x, y);
    shared_ptr<Hexagon> hex8 = make_shared<Hexagon>(LandType::Field, 9, center8, 8);

    hex8->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][0] = hex8;
    this->_hexagonsMap[center8] = hex8;
    x += rightMove;
    Point center9(x, y);
    shared_ptr<Hexagon> hex9 = make_shared<Hexagon>(LandType::Forest, 11, center9, 9);

    hex9->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][1] = hex9;
    this->_hexagonsMap[center9] = hex9;
    x += rightMove;
    Point center10(x, y);
    shared_ptr<Hexagon> hex10 = make_shared<Hexagon>(LandType::Desert, 0, center10, 10);

    hex10->initHexagon(_verticesMap, _edgesMap);
    // Set the robber on the desert hexagon
    hex10->setRobber(true);
    this->_hexagonGrid[2][2] = hex10;
    this->_hexagonsMap[center10] = hex10;
    x += rightMove;
    Point center11(x, y);
    shared_ptr<Hexagon> hex11 = make_shared<Hexagon>(LandType::Forest, 3, center11, 11);

    hex11->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][3] = hex11;
    this->_hexagonsMap[center11] = hex11;
    x += rightMove;
    Point center12(x, y);
    shared_ptr<Hexagon> hex12 = make_shared<Hexagon>(LandType::Mountains, 8, center12, 12);

    hex12->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[2][4] = hex12;
    this->_hexagonsMap[center12] = hex12;
    // Move to the next row (row 4). But now we need to move down and to the right
    x = startingX + downRightMoveX;
    startingX += downRightMoveX;
    y = startingY - downLeftMoveY;
    startingY -= downLeftMoveY;

    Point center13(x, y);
    shared_ptr<Hexagon> hex13 = make_shared<Hexagon>(LandType::Forest, 8, center13, 13);

    hex13->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][0] = hex13;
    this->_hexagonsMap[center13] = hex13;
    x += rightMove;
    Point center14(x, y);
    shared_ptr<Hexagon> hex14 = make_shared<Hexagon>(LandType::Mountains, 3, center14, 14);

    hex14->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][1] = hex14;
    this->_hexagonsMap[center14] = hex14;
    x += rightMove;
    Point center15(x, y);
    shared_ptr<Hexagon> hex15 = make_shared<Hexagon>(LandType::Field, 4, center15, 15);

    hex15->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][2] = hex15;
    this->_hexagonsMap[center15] = hex15;
    x += rightMove;
    Point center16(x, y);
    shared_ptr<Hexagon> hex16 = make_shared<Hexagon>(LandType::Pasture, 5, center16, 16);

    hex16->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[3][3] = hex16;
    this->_hexagonsMap[center16] = hex16;
    // Move to the next row (row 5). But now we need to move down and to the right
    x = startingX + downRightMoveX;
    startingX += downRightMoveX;
    y = startingY - downLeftMoveY;
    startingY -= downLeftMoveY;

    Point center17(x, y);
    shared_ptr<Hexagon> hex17 = make_shared<Hexagon>(LandType::Hills, 5, center17, 17);

    hex17->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][0] = hex17;
    this->_hexagonsMap[center17] = hex17;

    x += rightMove;
    Point center18(x, y);
    shared_ptr<Hexagon> hex18 = make_shared<Hexagon>(LandType::Field, 6, center18, 18);

    hex18->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][1] = hex18;
    this->_hexagonsMap[center18] = hex18;

    x += rightMove;
    Point center19(x, y);
    shared_ptr<Hexagon> hex19 = make_shared<Hexagon>(LandType::Pasture, 11, center19, 19);
    // Hexagon hex19(LandType::Pasture, 11, center19, 19);
    hex19->initHexagon(_verticesMap, _edgesMap);
    this->_hexagonGrid[4][2] = hex19;
    this->_hexagonsMap[center19] = hex19;
}

void Board::printBoard(sf::RenderWindow &window)
{
    double radius = 60.0; // Scaled radius for rendering
    int windowHeight = window.getSize().y;
    int windowWidth = window.getSize().x;
    int n = this->_hexagonGrid.size();
    sf::CircleShape robber;
    double horizSpacing = sqrt(3) * radius; // Horizontal distance between centers of adjacent hexagons
    double vertSpacing = 1.5 * radius;      // Vertical distance between centers of adjacent hexagons

    // Calculate offsets to center the grid in the window
    double totalGridWidth = (this->_hexagonGrid[0].size() - 1) * horizSpacing + radius * 2;
    double totalGridHeight = n * vertSpacing + radius;
    double xOffset = (windowWidth - totalGridWidth) / 2;
    double yOffset = (windowHeight - totalGridHeight) / 1;

    // Load the font from a default location
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font." << std::endl;
        return;
    }
    
    // Loop through the hexagon grid and draw each hexagon
    for (size_t i = 0; i < this->_hexagonGrid.size(); ++i)
    {
        for (size_t j = 0; j < this->_hexagonGrid[i].size(); ++j)
        {
            if (this->_hexagonGrid[i][j] && this->_hexagonGrid[i][j]->getLandType() != LandType::None)
            {
                // Calculate the hexagon's center position
                double x = xOffset + j * horizSpacing + (i % 2) * (horizSpacing / 2);

                if (i == 1 || i == 0)
                {
                    x -= horizSpacing / 1; // Shift second row left
                }
                else if (i == 4)
                {
                    x += horizSpacing / 1; // Shift fifth row right
                }
                double y = yOffset + i * vertSpacing;

                // Create the hexagon shape
                sf::CircleShape hexagon(radius, 6);
                hexagon.setOrigin(radius, radius);
                hexagon.setPosition(x, y);
                hexagon.setRotation(60); // Rotate to make pointy top

                // Set the fill color based on the LandType
                switch (this->_hexagonGrid[i][j]->getLandType())
                {
                case LandType::Desert:
                    hexagon.setFillColor(sf::Color::Yellow);
                    break;
                case LandType::Field:
                    hexagon.setFillColor(sf::Color::Green);
                    break;
                case LandType::Forest:
                    hexagon.setFillColor(sf::Color(0, 100, 0)); // Dark Green
                    break;
                case LandType::Hills:
                    hexagon.setFillColor(sf::Color(139, 69, 19)); // Brown
                    break;
                case LandType::Mountains:
                    hexagon.setFillColor(sf::Color(128, 128, 128)); // Gray
                    break;
                case LandType::Pasture:
                    hexagon.setFillColor(sf::Color(152, 251, 152)); // Light Green
                    break;
                default:
                    hexagon.setFillColor(sf::Color::Transparent);
                    break;
                }

                // Set color for the robber
                if (this->_hexagonGrid[i][j]->hasRobber())
                {

                    // Add the robber as a fill on the center of the hexagon
                    robber = sf::CircleShape(20, 3);
                    robber.setOrigin(20, 20);
                    robber.setPosition(x, y);
                    robber.setFillColor(sf::Color::Black);
                }

                // Create the text
                sf::Text text;
                text.setFont(font);
                string value = to_string(this->_hexagonGrid[i][j]->getValue()) + " " + this->_hexagonGrid[i][j]->getLandTypeString();
                text.setString(value);
                text.setCharacterSize(10); // Adjust size as needed
                text.setFillColor(sf::Color::Black);
                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                text.setPosition(x, y);

                // Draw the hexagon and text
                window.draw(hexagon);
                window.draw(text);
                if (this->_hexagonGrid[i][j]->hasRobber())
                {
                    window.draw(robber);
                }

                // Draw the structure on vertices if they exist
                for (const auto &[location, vertex] : this->_hexagonGrid[i][j]->getVerticesMap())
                {
                    auto vertexPtr = vertex.lock();
                    
                    // Calculate the vertex's  with a switch case
                    double vertexX = x;
                    double vertexY = y;
                    // Calculate the vertex's position based on the hexagon's center and radius
                    switch (location)
                    {
                    case VertexLocation::TOP:
                        vertexY -= radius;
                        break;
                    case VertexLocation::TOP_RIGHT:
                        vertexX += radius * sqrt(3) / 2;
                        vertexY -= radius / 2;
                        break;
                    case VertexLocation::BOTTOM_RIGHT:
                        vertexX += radius * sqrt(3) / 2;
                        vertexY += radius / 2;
                        break;
                    case VertexLocation::BOTTOM:
                        vertexY += radius;
                        break;
                    case VertexLocation::BOTTOM_LEFT:
                        vertexX -= radius * sqrt(3) / 2;
                        vertexY += radius / 2;
                        break;

                    case VertexLocation::TOP_LEFT:
                        vertexX -= radius * sqrt(3) / 2;
                        vertexY -= radius / 2;
                        break;

                    }
                    vertexPtr->draw(window, vertexX, vertexY);
                }

                // Draw the roads on edges if they exist
                for (const auto &[location, trail] : this->_hexagonGrid[i][j]->getEdgesMap())
                {
                    auto trailPtr = trail.lock();
                    double startX = x;
                    double startY = y;
                    double endX = x;
                    double endY = y;
                    // Calculate the trail's start and end points based on the hexagon's center and radius
                    switch (location)
                    {
                        case TrailLocation::TOP_RIGHT_EDGE:
                            // Calculate the top (start) and top right (end) vertices
                            startY -= radius;
                            endX += radius * sqrt(3) / 2;
                            endY -= radius / 2;
                            break;
                        
                        case TrailLocation::RIGHT_EDGE:
                            // Calculate the top right (start) and bottom right (end) vertices
                            startX += radius * sqrt(3) / 2;
                            startY -= radius / 2;
                            endX += radius * sqrt(3) / 2;
                            endY += radius / 2;
                            break;
                        
                        case TrailLocation::BOTTOM_RIGHT_EDGE:
                            // Calculate the bottom right (start) and bottom (end) vertices
                            startX += radius * sqrt(3) / 2;
                            startY += radius / 2;
                            endY += radius;
                            break;

                        case TrailLocation::BOTTOM_LEFT_EDGE:
                            // Calculate the bottom (start) and bottom left (end) vertices
                            startY += radius;
                            endX -= radius * sqrt(3) / 2;
                            endY += radius / 2;
                            break;

                        case TrailLocation::LEFT_EDGE:
                            // Calculate the bottom left (start) and top left (end) vertices
                            startX -= radius * sqrt(3) / 2;
                            startY += radius / 2;
                            endX -= radius * sqrt(3) / 2;
                            endY -= radius / 2;
                            break;
                        
                        case TrailLocation::TOP_LEFT_EDGE:
                            // Calculate the top left (start) and top (end) vertices
                            startX -= radius * sqrt(3) / 2;
                            startY -= radius / 2;
                            endY -= radius;
                            break;
                        
                    }
                    
                    trailPtr->draw(window, startX, startY, endX, endY);
                }
            }
        }
    }
}

void Board::printBoard()
{   
    // Create the sfml window
    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Catan Board");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear the window for the next frame
        window.clear();
        printBoard(window);
        window.display();
    }
}

shared_ptr<Vertex> Board::getVertex(vector<LandType> &places, vector<int> &placesNum) const
{
    // Check if the input is valid, we expect exactly 2 places and 2 numbers
    if (places.size() != placesNum.size() || places.size() != 2)
    {
        throw std::invalid_argument("The size of places and placesNum must be the same and exactly 2.");
    }

    // Find vertices for the first hexagon
    map<VertexLocation, weak_ptr<Vertex>> hex1Vertices;
    bool firstHexagonFound = false;
    // Find the first hexagon that matches the given land type and value
    for (const auto &[key, hex] : this->_hexagonsMap)
    {
        if (hex->getLandType() == places[0] && hex->getValue() == placesNum[0])
        {

            hex1Vertices = hex->getVerticesMap();

            firstHexagonFound = true;
            break; // We assume there's only one matching hexagon for each type/number combination
        }
    }

    if (!firstHexagonFound)
    {
        cout << "No matching first hexagon found." << endl;
        return nullptr;
    }

    // Filter vertices that are also part of the second hexagon
    for (const auto &[key, hex] : this->_hexagonsMap)
    {
        if (hex->getLandType() == places[1] && hex->getValue() == placesNum[1])
        {
            // Get the vertices of the second hexagon and compare them with the vertices of the first hexagon
            const map<VertexLocation, weak_ptr<Vertex>> hex2Vertices = hex->getVerticesMap();
            for (const auto &[location, vertex] : hex2Vertices)
            {
                for (const auto &[location1, vertex1] : hex1Vertices)
                {
                    // If the vertices match, return the shared pointer
                    if (vertex.lock() == vertex1.lock())
                    {

                        return vertex.lock();
                    }
                }
            }
        }
    }

    cout << "No matching vertex found." << endl;
    return nullptr; // No matching vertex found
}

bool Board::hasRoad(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const
{
    auto trail = v1->getTrail(v2);
    if (trail)
    {
        return trail->hasRoad();
    }
    return false;
}

bool Board::vertexMatches(shared_ptr<Vertex> v, vector<LandType> &places, vector<int> &placesNum) const
{
    // Check if the input is valid, we expect exactly 2 places and 2 numbers
    if (places.size() != placesNum.size() || places.size() != 2)
    {
        throw std::invalid_argument("The size of places and placesNum must be the same and exactly 2.");
    }

    // Track found places
    int matchCount = 0;

    // Check if the vertex matches the given land type and number of vertices
    for (const auto &hex : v->getHexagons())
    {
        if (!hex.expired())
        {
            shared_ptr<Hexagon> hexPtr = hex.lock();

            if (hexPtr->getLandType() == places[0] && hexPtr->getValue() == placesNum[0])
            {

                matchCount++;
            }
            else if (hexPtr->getLandType() == places[1] && hexPtr->getValue() == placesNum[1])
            {

                matchCount++;
            }
        }
    }

    // If both places are matched
    return (matchCount == 2);
}

vector<shared_ptr<Vertex>> Board::getNeighborVertices(shared_ptr<Vertex> v) const
{
    vector<shared_ptr<Vertex>> neighbors;

    // Iterate over the trails of the vertex and add the connected vertices
    for (const auto &trail : v->getTrails())
    {
        if (!trail.expired())
        {
            shared_ptr<Trail> tPtr = trail.lock();
            // Get the vertices connected by the trail
            const auto &start = tPtr->getStart().lock();

            const auto &end = tPtr->getEnd().lock();

            // Add the vertex that is not the input vertex
            if (start != v && find(neighbors.begin(), neighbors.end(), start) == neighbors.end())

            {
                neighbors.push_back(start);
            }
            // Add the vertex that is not the input vertex
            if (end != v && find(neighbors.begin(), neighbors.end(), end) == neighbors.end())
            {
                neighbors.push_back(end);
            }
        }
    }
    return neighbors;
}

shared_ptr<Trail> Board::getTrail(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2) const
{
    return v1->getTrail(v2);
}

shared_ptr<Hexagon> Board::getRobberHexagon() const
{
    for (const auto &[key, hex] : this->_hexagonsMap)
    {
        if (hex->hasRobber())
        {
            return hex;
        }
    }
    return nullptr;
}

bool Board::distanceRule(shared_ptr<Vertex> v)
{
    auto neighbors = getNeighborVertices(v);

    // Iterate over the neighbors (3) and check if they are occupied
    for (auto &n : neighbors)
    {
        if (n->isOccupied())
        {
            return false;
        }
    }

    return true;
}
