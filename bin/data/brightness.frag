#version 150

out vec4 outputColor;

uniform sampler2DRect image;
uniform sampler2DRect lut;

in vec2 coord;

void main()
{
    vec4 color = texture(image, coord);
    float average = (color.x + color.y + color.z)/3;
    float new_x = texture(lut, vec2(color.x*256, 0)).x;
    float new_y = texture(lut, vec2(color.y*256, 0)).y;
    float new_z = texture(lut, vec2(color.z*256, 0)).z;
    outputColor = vec4(new_x, new_y, new_z, color.a);
}
