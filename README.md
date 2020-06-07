# Z-Machine
A barebones Z-machine implementation in C++ created entirely from scratch. 

A game-engine for text-based interactive fiction games. The two primary components of world building is the Map graph and the Items vector. To create your own game, you need to populate these two componenets which you can do by directly modifying the **game_map.txt** and **game_items.txt** present in the *world_components* folder.

Syntax for Map node:

```
[Location] 
Location description 
exit1 
exit2 
.
.
exitn
```

Syntax for Item description:
```
[Name]
Item description
Item_location
Portability
```



Currently implemented commands:

Command | description
--- | ---
**look** | examines the environment
**examine** | examines an item
**goTo** | moves to a location
**inventory** | Checks inventory
**take** | Picks up an item
**drop** | drops an item
**stop** | quit the game

A sample map and itemset are present in the uploaded world_components files, please refer to that for better understanding.

---

This project expands on my previously implemented Graph-parser

[![graph-parser](https://img.shields.io/badge/graph--parser-link-brightgreen)](https://github.com/Kunal-khanwalkar/graph-parser)


---
Footnote:

This project does not use **any** external library, every component is created from scratch (Okay, except STL library but that doesn't count).

I extensively used Object Oriented Programming throughout this project to utilize encapsulation and code reusability. Regardless of the perks, I do not think Object Oriented Programming is the best paradigm when it comes to Game dev and Engine design. A certain prospective would be to use *Data Oriented design* and recreate the engine to reduce the usage of Getters, Setters, and Pointers as well as Package the code as part of the data itself. It will definitely reduce the overhead which we find in OOP or even Procedural Programming.