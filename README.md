# Pacman Gevorderd Programmeren

_Mathijs Pittoors - 20241112_

## Core Game Requirements

- Startup screen + scoreboard [x] _See MenuState.h_
- Maze & collision correctness [x]
- Smooth continuous movement [x]
- Ghost AI (4 modes, Manhattan distance, direction locking) [x] _See IGhost.h and World.cpp_
- Coin/fruit score modifiers [x] _See ScoreKeeper.cpp_
- Fear mode + ghost reversal [x] _See IGhost.h and World.cpp_
- Level clearing + scaling difficulty [x] _See ScoreKeeper.cpp, LevelState.cpp and World.cpp_
- Life system & game over [x] _See ScoreKeeper.cpp, LevelState.cpp and World.cpp_

## Soft. Design & Code Arch.
- Clear MVC separation [x] _Models do not know views exist, they only see Observers_
- Patterns: 
  - MVC [x] _See `ViewCompatibleEntityFactory.h`, `IEntity.h`
  - Observer [x] _See `IObserver.h`, `ISubject.h`
  - Abstract Factory [x] _See `AbstractFactory.h`_
  - Singleton [x] _See `Camera.h`, `Random.h`_
  - State [x] _See the `state` directory_
- Logic as standalone library [x] _See GitHub Actions, `CMakeList.txt`
- Camera & normalized coords [x] _See `WorldCreator.cpp`_
- Good polymorphism & extensibility [x] _Ex. ISubject > IEntityModel > IDirectionalEntityModel > IGhost > RedGhost_

## Bonus Features

- Extra gameplay/visuals [ ]
- Sounds/music [ ]
- Smarter AI (BFS, A*) [ ]
- Procedural maps [ ]
- Multithreading [ ]
- Extra design patterns [x] _See Visitor.h_