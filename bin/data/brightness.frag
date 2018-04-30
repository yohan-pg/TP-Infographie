#version 150

out vec4 outputColor;

uniform sampler2DRect image;
uniform sampler2DRect lut;

in vec2 coord;

void main()
{
    vec4 color = texture(image, coord);
    float new_x = texture(lut, vec2(clamp(color.x, 0, 1.0)*256, 0)).x;
    float new_y = texture(lut, vec2(clamp(color.y, 0, 1.0)*256, 0)).y;
    float new_z = texture(lut, vec2(clamp(color.z, 0, 1.0)*256, 0)).z;
    outputColor = vec4(clamp(new_x, 0, 1.0), clamp(new_y, 0, 1.0), clamp(new_z, 0, 1.0), 1.0);
}
