# [![icon.png](https://i.postimg.cc/d38xpWGd/icon.png)](https://postimg.cc/FkHpJVWs) Platformer 2D

Platformer 2D is a customizable C++20 tile-based game, where you can create your own worlds and alter the settings easily.

The objective for the player is to find an exit in a possibly huge world, without getting himself killed.

## Preview

[![main-screen.png](https://i.postimg.cc/KvRT9XN6/main-screen.png)](https://postimg.cc/JGCtn2Sx)

[![main-screen-2.png](https://i.postimg.cc/3JVvVLfd/main-screen-2.png)](https://postimg.cc/nCKrQ1JJ)

### Main Menu

[![menu.png](https://i.postimg.cc/13zy0PrF/menu.png)](https://postimg.cc/MvhkxC4Z)


### Paused Menu 

[![game-paused.png](https://i.postimg.cc/X7LVyXd3/game-paused.png)](https://postimg.cc/RN3rkSgb)

### Options

[![options.png](https://i.postimg.cc/65WKwwSP/options.png)](https://postimg.cc/4nSqQCXv)

### Keybindings
[![keybinds-gif.gif](https://i.postimg.cc/PJJjNdXt/keybinds-gif.gif)](https://postimg.cc/WFBKHLqK)

### Map Loader

[![map-loader-gif.gif](https://i.postimg.cc/sfHzqGm1/map-loader-gif.gif)](https://postimg.cc/Z0NXyR1h)

### Exemplary `.bmp` world

 _(scaled 400%)_


[![map-scaled.png](https://i.postimg.cc/267tXLzS/map-scaled.png)](https://postimg.cc/S2jVns2B)

The worlds are also loadable from `.txt` files!

### Map builder

Independent JS project _(work in progress)_

[![map-builder.png](https://i.postimg.cc/2Sggqfcr/map-builder.png)](https://postimg.cc/k2FTZLPp)


## Usage

_todo_

## Installation

The following is a complete installation for MinGW along with all required libraries.

```bash
git clone https://github.com/Wenox/platformer-2d.git
cd platformer-2d
mkdir lib && mkdir test/lib && mkdir build
# <Install SFML into lib/>
# <Install tgui into lib/>
# <Install dynamic SFML and tgui libraries into lib/shared_lib or build/>
# <Install googletest into test/lib/>
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
```

The project is fully cross-platform. Adjust the installation to your own compiler / environment system.

## Documentation

The game API is fully documented. 

See: [Github pages](https://wenox.github.io/platformer-2d/html/modules.html "Documentation")

## License

This project is licensed under MIT license.
 
Feel free to re-use the game or its independent modules to suit your needs.