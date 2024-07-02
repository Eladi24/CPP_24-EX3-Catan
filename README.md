# Catan Game Engine

## Author
- **Name:** Elad Imany
- **Email:** eladima66@gmail.com

## Project Overview
This project implements the core logic and structure for a digital version of the popular board game, Catan. The game of Catan is a multiplayer board game that revolves around resource gathering, trading, and building with the ultimate goal of earning victory points to win. The game is set on an island where players build settlements, cities, and roads on hexagonal tiles, each representing different types of land that produce specific resources.

## Class Hierarchy and Libraries

### Classes
The project is structured around several key classes, each representing a component of the game:
- **Point and Vertex:** Represent points and vertices on the game board. Vertex extends Point and is used to manage settlements and cities.
- **Hexagon:** Represents the hexagonal tiles on the board.
- **Trail:** Represents the paths (edges) between vertices where roads can be built.
- **Structure, Settlement, and Road:** Abstract and concrete classes for the buildings and roads players can construct.
- **Player:** Represents a player in the game, managing their resources, cards, and constructions.
- **DevCard, ProgressCard, and VictoryPointCard:** Represent the development cards that players can purchase and use for various effects.
- **Cashbox:** Manages the game's currency and transactions.

### Libraries
Libraries used in this project include:
- **SFML (Simple and Fast Multimedia Library):** Used for rendering the game board and interactive elements.
- **C++ Standard Library:** Provides data structures, memory management, and utility functions.

## Key Methods
Some of the important methods implemented in this project include:
- **Resource Management:** Methods for managing resources, such as `yieldResources` in Settlement and Structure, which handle the production of resources based on the game's rules.
- **Building and Upgrading:** Methods like `buildSettlement`, `buildCity`, and `setRoad` in Vertex and Trail classes, allowing players to construct and upgrade their buildings and roads.
- **Card Management:** Methods for handling development cards, including purchasing and activating them. Each card type, such as ProgressCard and VictoryPointCard, has an `activate` method that implements its unique effect.

## Additional Resources
A very helpful guide for understanding and implementing hexagonal grids, which are a core part of the Catan board, can be found here: [Hexagonal Grids](https://www.redblobgames.com/grids/hexagons/).

## Additional Notes
This project is designed with extensibility in mind, allowing for future enhancements such as AI players, different board layouts, and additional development cards. The use of polymorphism and abstract classes facilitates the addition of new features without significant modifications to the existing codebase.

## Conclusion
This Catan game engine project lays the foundation for a fully functional digital version of the game, focusing on the core mechanics, class design, and interaction between different components of the game. It provides a solid base for further development, including graphical interface implementation, networked multiplayer, and game rule expansions.