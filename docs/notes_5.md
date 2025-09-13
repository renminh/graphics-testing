process goes:

vertices makes meshes(polygons)
textures can be applied to meshes (during fragment shader)
meshes bundled with textures are models (sprites in 2d)

now onto the part where we must render more than one model

![Coordinate Space](pictures/coordinates.png "Coordinates Space")

first we must wrestle with some ideas

the resolution of the window is not the same as the resolution of the renderer
the renderer's resolution can be thought of as the virtual resolution, that is
the size that the models will be mapped to

there is no limitation to it being smaller, bigger, or exact to the window size
hence the window size can be whatever but the renderer resolution is the same
the renderer's resolutionn is independent of the window and is where everything
rendered by the GPU will live

if our tilesheet sprites are 16x16 per cell

we can determine how many sprites can be rendered and what resolution is needed

virtual width = 16 * 32 blocks = 512
virtual height = 16 * 20 blocks = 320

we thus have the location that we can model the model matrix for which maps to
the world space

next thing we need to figure out is, once we create the models, who exactly owns
it? renderer shouldn't really own it as it's not exactly a "GPU resource", it
shouldn't really manage the states of models like transformation matrices,
though it should certainly operate on them.

therefore a new component must be added that will handle the management of run
time objects: the models, in world space, or the visible screen.

this can go by any names but the one chosen will be **scene** representing the
graphical scene.

because scene holds the run time objects, we can also store the virtual
resolution inside of it

scene will therefore be a  struct containing models

to store the models, i'll be needing to use an array list because whenever
we need to destroy the model, it'll end up leaving empty gaps in the array
