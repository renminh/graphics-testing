# on the architecture of scene

scene must hold all the runtime entities, therefore a normal array cannot be
used due to the fact that we either waste resources we don't use or a buffer
overflow because we cannot fit all the entities

a dynamic array in this case would be the perfect solution that handles resizing
the array whenever we are about to run out of resources

however another architectural problem comes by, that is, we know that scene will
hold the entities, we also know that scene handles holding the models as well,

instead of attaching a reference to the models inside the entity struct (which
is costly and comes with safety issues like dangling pointeres), we instead
store in the model id which is indexed to the scene's models array
this models array will be static (because of the nature that we don't need to
deal with user generated models) and we can determine in compile time the amount
of models that we'll need.

now that entities contain a model id, a transform struct which simply holds
position, scale, and rotation, we also need to deal with the fact problem of
accessing entities or specific entities in the entities array list.

an issue appears, during the runtime, we can create entities and reference them
via their memory address in the array list, but if we were to remove a specific
entity in the array, items get shifted down due to the nature of array lists

this means that all the memory addresses of the entities get shifted down
and whichever component was making use of entities now has a mismatch, and
possibly referencing a null entity !! THIS IS AN ISSUE !!

therefore, it is not enough to just store the entities in the array list but
we must be able to index them and access them even if their positions in memory
were to change. this means every entity must be unique (which it normally is
in games anyways)

this requires setting up an id for each entity that allows us to query the
specific entity only using an unsigned int instead of passing around pointers

the issue then arises with how this will be implemented? how will an entity
receive their id?

if they are received based on the index of where they were appended, we return
to the same issue of mismatch and possible null entities if we decide to destroy
an entity.

we are then represented with these:
1. an entity must have a stable id to reference it safely
2. we cannot rely on indexing based on IDs, especially if entities were to be
   destroyed during the middle of a something
3. we must investigate another approach to designing this architecture that is
  radically different

the naive approach would be to continue "indexing" via the ids but instead to
store the entities in a hashmap.

although this is very efficient in terms of access being O(1), and insertion +
deletion being O(1), it is NOT CPU nor GPU friendly. Why? Memory addressing.

The benefit of using an array is that all data is contigous, that means that
CPUs and GPUs can easily operate on them as they don't need to do any sort of
branching or dereferncing. Not only that but because of how memory is organized
and how modern day CPUs work, we don't operate on memory but instead cache the
local area that we work with (which then gets put into registers). Caches are 
extermely important for the fact future data can be served faster because 
the caches are right next to the processors. When data is read from a cache,
we call that a cache hit, else a cache miss occurs. We want to program for
cache hits especially when games run computationally expensive for both the CPU
and GPU. 

https://en.wikipedia.org/wiki/Cache_(computing)

Hashmaps in this case cannot guarantee that every new element added
will be contigous, thus increasing cache misses. A whole more optimizations 
also play in due to the fact that CPUs are not sequential machines anymore but
perform a lot of predictions (so much so that it had to be lowered down because
of the spectre & meltdown vulnerability)

https://www.infosecinstitute.com/resources/malware-analysis/meltdown-spectre-patches-story-delays-lies-failures/

In any case, even if hashmaps could guarantee cache hits, architectural wise, it will simply
devolve us into chasing pointers, dereferincing them, and still the issues of 
dangling pointers will exist. Iterations over them will move to a snails place 
as having to operate on them requires to derefernce elements over and over again
which again leads to cache misses. Therefore a contigous array of elements is needed
but the limitation of arrays are present

So we'll keep the array list but the change will be in the design

not only that but the overhead of having to alloc entities, set them up, then
destroy them at the end of their life time is a complete waste of resources
when scaled larger. Take for example a bullet hell game where bullets are 
entities each with their own transformation matrix and model. With this
architecture, each bullet that is shot is created, and each bullet that hits a
target/wall/or goes out of bounds is destroyed. It is a misuse of CPU resources
and can lead to memory fragmentation due to the amount of holes caused by alloc
and free

The equivalence of it can be described as having to buy a new pen everytime
we wish to write then throwing it away right after

entities are also just containers for the model is uses and transformation matrix
there is nothing particularly unique about them and anything can be changed to
any other entity.

Thus a breakaway from typical object oriented philosophy must be made
Thus we approach a data-oriented design, away from OOP land, which will solve
both problems of entity access and memory usage

an entity cannot really be thought of as a self contained object, with its own
methods and lifecycle. if this was done, we fall back to object oriented design

but CPUs and GPUs don't operate on objects, but sequential and contigous data

from the book game engine architecture
![Memory](pictures/gea.png "Memory")

