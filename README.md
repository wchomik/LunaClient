# LunaClient
Companion App for https://github.com/romanchom/lunaEsp32Template

LunaClient allows you controlling your wireless LED strands. Available modes include:
* Light: any reproducible color, black body radiation, system theme color.
* Screen: capture your desktop in realtime and control your lights based on screen contents.
* Audio: Capture your audio output in realtime and make the lighs flash in rythm.
* Flame: A nice fireplace-like flame.
* Plasma: Colorful and slowly changing lights like a lava lamp. 

# Building
Requires MSVC 2019, may work with MinGW.
In powershell:
```
mkdir build
cd build
conan install .. --build=missing
cmake .. -DCMAKE_INSTALL_PREFIX=package
cmake --build . --config=Release
cmake --install .
```
