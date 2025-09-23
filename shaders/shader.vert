#version 450

// Hardcoded triangle vertices in clip space
// vec2(x, y)
vec2 positions[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

// Hardcoded colors for each vertex
// vec3(r, g, b)
vec3 colors[3] = vec3[](
    vec3(1.0, 0.0, 0.0), // Red
    vec3(0.0, 1.0, 0.0), // Green
    vec3(0.0, 0.0, 1.0)  // Blue
);

// Output variable to pass color to the fragment shader
layout(location = 0) out vec3 fragColor;

void main() {
    // gl_VertexIndex is a built-in variable that contains the index of the vertex
    // being processed. We use it to get the position and color for the current vertex.
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
}
