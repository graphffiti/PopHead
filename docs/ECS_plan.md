# Overview
This document will contain all plans, schemas, assets, etc. that will be used to change our current game objects architecture (inheritance based) to ECS (Entity-Component-System). We decided to use existing ECS library - Entt - to not deal with problems of implementing ECS.

#### Useful Docs:
- ECS introduction
  - [wikipedia](https://en.wikipedia.org/wiki/Entity_component_system)
  - [https://www.richardlord.net/blog/ecs/what-is-an-entity-framework.html](https://www.richardlord.net/blog/ecs/what-is-an-entity-framework.html)
  - [https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/understanding-component-entity-systems-r3013/)
  - [https://medium.com/ingeniouslysimple/entities-components-and-systems-89c31464240d](https://medium.com/ingeniouslysimple/entities-components-and-systems-89c31464240d)
  - [https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-entity-component-system-c-game-design-pattern-part-1-r4803/](https://www.gamedev.net/articles/programming/general-and-gameplay-programming/the-entity-component-system-c-game-design-pattern-part-1-r4803/)
- Entt library
  - [GitHub repository](https://github.com/skypjack/entt)
  - [Official documentation](https://skypjack.github.io/entt/)

## Components and Systems
In order to create a new game objects architecture we need to make a list of components and systems.
 Since we are not adding new types of objects we just need to divide existing classes into variables (components) and logic (systems).

### Components Proposal
If a component is not clear it's useful to add comment with use cases.
##### Note: Don't mind of namespaces, our naming rule of variables (hungarian case) and C++ syntax for now. It's just the first version of list.
```cpp
struct Name { // for example for debugging and logging
    std::string name;
}
struct Health {
    int healtPoints;
}
struct Sprite {
    sf::Sprite sprite;
}
struct Animation {
    // TODO: add actual variables here
}
struct Velocity {
    // !!! there are two possible versions (both with the same size)
    // 1. polar coordinates
    float speed;
    float angle; // [0, 360)
    // 2. cartesian coordinates
    sf::Vector2f velocity;
}
```

### Systems Proposal
System's description MUST contain list of used components.