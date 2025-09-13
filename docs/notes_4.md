a mesh?

a collection of vertices, edges, and faces that define a shape of a 3D object
Most popular type of polygon mesh used in computer graphics is a Triangle Mesh

vertices of a mesh are inputs to the rendering pipeline

a mesh stores information about vertices, edges, and faces

therefore, we can use create a mesh struct

to store information about a quad mesh (since pixels are the primary
unit of our game)

we can store this information to the struct where it holds a copy of a
vao, vbo, ebo, that corresponds to the quad
