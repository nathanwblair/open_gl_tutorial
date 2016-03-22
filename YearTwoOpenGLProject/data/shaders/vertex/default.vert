#version 150

in vec4 Position;
in vec4 Normal;
in vec4 Tangent;
in vec4 Binormal;

in vec2 TexCoords;

out vec4 vPosition;
out vec4 vNormal;
out vec4 vTangent;
out vec4 vBinormal;

out vec2 vTexCoords;


uniform mat4 Model;
uniform mat4 ProjectionView;

void main()
{
	gl_Position = ProjectionView * Model * Position;
	
    vNormal = Model * Normal;
    vTangent = Model * Tangent;
    vBinormal = Model * Binormal;
    
    vPosition = Model * Position;
    
   vTexCoords = TexCoords;
}