#version 450

// Input variable from the vertex shader (must match 'out' variable)
layout(location = 0) in vec3 fragColor;

// Output variable for the final color
layout(location = 0) out vec4 outColor;

void main() {
    // The hardware automatically interpolates fragColor between vertices.
    // We just output it as the final color. Alpha is 1.0 (opaque).
    outColor = vec4(fragColor, 1.0);
}
