#version 460 core

out vec4 frag_color;

in vec2 uvs;

uniform vec4 color;
uniform sampler2D texture_id;

void main() {
    vec4 texture_color = texture(texture_id, uvs) * color;

    if (texture_color.a < 0.1)
        discard;

    frag_color = texture_color;
}
