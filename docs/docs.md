https://www.khronos.org/opengl/wiki/Getting_Started#Downloading_OpenGL

```c
/*
 * Some platforms would rather your program operate in chunks. 
 * Most of the time, games tend to look like this at the highest level:
 */

int main(int argc, char **argv)
{
    initialize();
    while (keep_running()) {
        handle_new_events();
        do_one_frame_of_stuff();
    }
    deinitialize();
}
```

https://wiki.libsdl.org/SDL3/SDL_GL_CreateContext
https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideoopengl.html

tutorial
sibras.github.io/OpenGL4-Tutorials/docs/Tutorials/01-Tutorial1/

initializing glad and SDL
https://bcmpinc.wordpress.com/2015/08/18/creating-an-opengl-4-5-context-using-sdl2-and-glad/
