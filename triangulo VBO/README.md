Código referencia do tutorial https://learnopengl.com

```console
sudo apt-get install cmake xorg-dev libassimp-dev
mkdir build
cd build
cmake ..
make
./openglexample
```

If you're using mac, uncomment line 35 in game/src/main.cpp file:

```cpp
34     // Mac OS only
35     //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); <--- uncomment this
```

If you aren't on mac delete file: `game/libs/glfw/src/glfw_config.h`
