_This project has been created as part of the 42 curriculum by amezoe and sionow_

# cub3d
Simulating a 3D view from a grid map using MiniLibX and Raycasting.


## Prerequisites
- make
- CC
- X11 for MiniLibX

## Description
cub3d is a 3D ray-casting engine inspired by the first person game Wolfenstein 3D(1992). This project enables you to explore ray-casting by creating a dynamic view inside a maze where you must find your way. 
Using the miniLibX graphics library, it renders a first-person perspective environment with textured walls, configurable floor and ceiling colors, and smooth player key (+ mouse)movement.

## Instructions
### Build

make or make bonus to generate executable

### Run
Provide a '.cub' file:
- ./cub3d maps/example.cub

bonus:
- ./cub3d_bonus maps/example.cub


## Maps

More valid and invalid maps can be found in their corresponding paths
- maps/validmaps/...
- maps/invalidmaps/...

Map overview:
- 0 = free space
- 1 = wall
- N,E,S,W = player position and facing direction
- D = door

## Controls
mandatory:
- Player movement: W, A, S, D
- Camera movement: left arrow, right arrow
- Close: ESC or window close button

bonus:
- same as above with following additions:
- Camera movement: also possible with mouse
- Door open/close: Spacebar


## Structure

- `inc/` textures, minilibx and previous projects that got used
- `maps/` sample maps
- `src/` all files for mandatory part divided in parse and exec + headers
- `src_bonus/` all files for bonus part divided in parse and exec + headers


## Resources

https://lodev.org/cgtutor/raycasting.html

https://hackmd.io/@nszl/H1LXByIE2

AI was used for:
- Explanation of ray-casting related math
- providing right mathematical formula for fisheye correction

## Licenses
This project is educational and falls under fair use guidelines.
All textures and assets used are either original or freely licensed.