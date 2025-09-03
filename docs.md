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
