_This project has been created as part of the 42 curriculum by amezoe and sionow_

# cub3d
Simulating a 3D view from a grid map using MiniLibX and raycasting.

## Description
cub3d is a 3D ray-casting engine inspired by Wolfenstein 3D (1992), the game that defined the first-person shooter genre.This project enables you to explore ray-casting by creating a dynamic view inside a maze where you must find your way.
Using the miniLibX graphics library, it renders a first-person perspective environment with textured walls, configurable floor and ceiling colors, and smooth player key (+ mouse)movement.


## Features

### Core Architecture
- **Raycasting engine** → Projects a 3D view from a 2D grid map in real time using the DDA algorithm
- **MiniLibX rendering** → Draws directly to a pixel buffer for efficient frame output
- **Map parser** → Validates and loads `.cub` configuration files including textures, colors, and map layout
- **DDA Algorithm** -> For each vertical screen column, casts a ray from the player's position using the DDA (Digital Differential Analysis) algorithm
- **Wall projection math** Computes the distance to the nearest wall, corrects for fisheye distortion, then determines wall slice height and texture coordinates

### Rendering
- **Textured walls** → Each cardinal direction (North, East, South, West) has its own texture
- **Configurable floor & ceiling** → RGB color values set in the `.cub` file
- **Fisheye correction** → Proper distance calculation to avoid lens distortion on wide FOV

## Prerequisites
- make
- CC
- X11 for MiniLibX

## Instructions

### Build
```sh
make/make bonus
```

### Run
Provide a '.cub' file:
```sh
./cub3d maps/example.cub
```

bonus:
```sh
./cub3d_bonus maps/example.cub
```


## Maps

More valid and invalid maps can be found in their corresponding paths
```sh
maps/validmaps/...
```
```sh
maps/invalidmaps/...
```

Map overview:
- `0` = free space
- `1` = wall
- `N`,`E`,`S`,`W` = player position and facing direction
- `D` = door

### Controls (Mandatory)
- `W` `A` `S` `D` → Player movement
- `←` `→` (arrow keys) → Camera rotation
- `ESC` or window close button → Exit

### Bonus Features
- **Mouse look** → Camera rotation via horizontal mouse movement
- **Doors** → `D` tiles in the map act as openable/closable doors
  - `Spacebar` → Toggle door open/close

## Structure

- `inc/` textures, minilibx and previous projects that got used
- `maps/` sample maps
- `src/` all files for mandatory part divided in parse and exec + headers
- `src_bonus/` all files for bonus part divided in parse and exec + headers


## Project Requirements (Summary)
- Written in C, compliant with the 42 Norm
- No memory leaks — all allocated memory must be freed on exit
- Graceful exit on ESC and window close button
- No crashes, no undefined behavior under any valid input
- Makefile with standard rules: all, clean, fclean, re, bonus
- Must use MiniLibX

## Resources

https://lodev.org/cgtutor/raycasting.html

https://hackmd.io/@nszl/H1LXByIE2

AI was used for:
- Explanation of ray-casting related math
- providing right mathematical formula for fisheye correction

## Licenses
This is a 42 school project for educational purposes only. Fair use applies.
All textures and assets used are either original or freely licensed.