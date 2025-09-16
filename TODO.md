# TODO

TODO refactor texture + renderer + atlas

QUAD IS RECTANGULAR? check model matrix and quad mesh

fix texture atlas to display correct sprite
- issue (setting sprite size doesn't actually work)
    - if our sprite size is 16x16, it'll show us an extremely zoomed in
     tile, which necessitates making the sprite_size almost 128x128+ which is
     NOT NORMAL
double free or corruption (out)

understand what VBO and VAO are in terms of buffers?
or vertex shaders, currently what i do understand is that

the vertex shader takes in vertices based on the glBufferData
and  i assume that this data is binded to the VBO? (why?)

the vertex shader is what creates the vertices and primitive shapes

---

for the actual architecture, learn about Data-Oriented Design especially since
it wraps around Entity Component System for the game engine architecture
