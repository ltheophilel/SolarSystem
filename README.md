# Solar System Simulation in C with SDL2
![Interface](/view.png)

This is a **2D simulation** of the Solar System, including the Sun and the 8 planets. 
## Prerequisites
- make
- cmake
- SDL2 (with SDL2_TTF)
- A C compiler (GCC for instance)

## Installing

#### On Ubuntu / Debian
```bash
sudo apt-get install build-essential cmake libsdl2-dev libsdl2-ttf-dev
```
#### On MacOs
```bash
brew install cmake sdl2 sdl2_ttf
```
#### On Windows
Download and install SDL2 and SDL2_TTF, then ensure your compiler can find the libraries.

## Compilation
Use **CMake** to compile it : Inside the work directory :
```bash
mkdir build
cd build
cmake ..
make
./solarsystem # Run it !
```

## Usage
### Running
You can choose : 
- The **scale** : fit the screen or a "real" scale :
```bash
./solarsystem # Screen adapted size
./solarsystem on_scale # Real scale (except for the Sun reduced to a dot)
```

- The computing method : kinematics or dynamics :
```bash
./solarsystem # Kinematics
./solarsystem dynamics # Dynamics 
```

### Controls
+ Exit : hitting **Escape**
+ Pause : holding the **Space bar**
+ Right Arrow : speed up
+ Left Arrow : slow down

## Features

### Two simulation modes :

> Kinematic : Precomputed orbits (faster, less CPU-intensive).  
Dynamic : Real-time physics (more accurate).

### Two scale modes :

> Screen-adapted (default).  
Real scale : Distances are on scale, planet sizes too but not with repect to the other (if so, all planets would be a few pixels wide).

Real-time date display (top-left corner).  
FPS printing (averaged on the whole simulation)  
Max acceleration : ~8,000,000 (1 year in 5 seconds).


## Project Structure
```
├── CMakeLists.txt
├── LICENSE
├── README.md
├── fonts
├── include
│   ├── compute.h
│   ├── constants.h
│   ├── date.h
│   ├── display.h
│   ├── main.h
│   └── shape.h
├── src
│   ├── compute.c
│   ├── constants.c
│   ├── date.c
│   ├── display.c
│   ├── main.c
│   └── shape.c
└── view.png  (TB replaced with a gif)
```
## Next steps
+ Better Interface : date (add 'today' as (default) parameter --> avoid having to adapt the date reading), option for full screen
+ Infos on planets
