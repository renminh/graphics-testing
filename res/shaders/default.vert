#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uvs;

out vec2 uvs;

uniform mat4 projection;
uniform mat4 model;
uniform vec4 uv;

void main() {

    // vec x,y,z, w (w part of vec4)
    // w is not used as a position in space but for something
    // called perspective division

    gl_Position = projection * model * vec4(a_pos, 1.0);
    uvs = mix(uv.xy, uv.zw, a_uvs);

}
