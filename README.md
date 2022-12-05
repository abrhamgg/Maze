
# Maze Project

A 3D maze raycasting game developed with SDL library and C.


## Demo
https://youtu.be/nnNUVkh4TR8

## Tech Stack
- C programming language
- SDL library v2.0 : to display graphics in the window
- upng: to decode images.

## Main files and Project structure
 ```sh
  ├── README.md
  |── Makefile
  ├── src
  │   ├── graphics.c         
  |   ├── textures.c  
  |   |── ray.c  
  |   ├── player.c  
  |   ├── main.c  
  │   ├── wall.c
  │   ├── sprite.c 
  │   ├── map.c 
  │   └── upng.c
  └── headers
      ├── graphics.h
      ├── textures.h
      ├── ray.h
      ├── player.h
      ├── wall.h
      ├── sprite.h
      ├── upng.h
      ├── map.h
  ```
  ## Development Setup
- https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php
  
  For debian based linux os `` sudo apt-get install libsdl2-dev``

## Compilation

  `` make ``
## Execution

  `` ./main ``

## Instructions
- Use the arrow keys to move around the maze.

## Author
    - Abrham Gebregiorgis -> abrhamgg@gmail.com
