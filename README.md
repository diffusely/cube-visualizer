cube-visualizer
=========
A 3D Rubik’s Cube visualizer built from scratch using C++ and OpenGL.

Clone
-----
```bash
git clone --recurse-submodules git@github.com:diffusely/cube-visualizer.git
cd cube-visualizer
```

Build
-----
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Controls
-----
- **Top** — rotates the top face.
- **Bottom** — rotates the bottom face.
- **Left** — rotates the left face.
- **Right** — rotates the right face.
- **Front** — rotates the front face.
- **Back** — rotates the back face.
- **Randomize** — randomly scrambles the Rubik's Cube.
- **Reset** — returns the Rubik's Cube to its solved state.


![Rubik's Cube](res/cube.png)