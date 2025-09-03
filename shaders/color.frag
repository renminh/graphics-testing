#version 460 core
out vec4 fragment_color;

uniform vec4 vertex_color;

void main() {
    fragment_color = vertex_color;
}
