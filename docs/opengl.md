opengl is a state machine

which means it provides two different types of functions

state setting and state using.

to be able to change the state of an object, we must first set it or bind it
to the opengl pipeline then use a state using function to change whatever value
or attribute which is changed on the next draw call

this is really strange because it doesn't really mimick how hardware works

for example setting the uniforms of shaders requires us to first bind the shader
program object to be able to access it but a program object id is really just
a label that represents THAT specific object in memory, meaning, we need such an
such overhead of "binding" the shader first before using it and then sending it
to a function that'll translate it to its corresponding memory address anyways
