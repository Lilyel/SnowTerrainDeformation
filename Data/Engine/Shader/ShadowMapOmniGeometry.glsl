#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 Model;

// The matrices for each cube map side.
uniform mat4 ShadowMapViewMatrix[6];
uniform mat4 ShadowMapProjectionMatrix;

out vec4 FragPos;

void main()
{
    // Cube map size.
    for( int f = 0; f < 6; f++ )
    {
        // Send to a cube map face.
        gl_Layer = f;

        // Triangle vertex.
        for( int v = 0; v < 3; v++ )
        {
            vec4 InPosition = gl_in[v].gl_Position;
            FragPos = InPosition * Model;
            gl_Position = InPosition * ( Model * ShadowMapViewMatrix[f] * ShadowMapProjectionMatrix );
            EmitVertex();
        }
        EndPrimitive();
    }
}
