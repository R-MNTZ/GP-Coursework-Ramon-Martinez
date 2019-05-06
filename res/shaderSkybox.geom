#version 330 core

in VS_OUT {
    vec3 TexCoords;
} VertexIn[];

out VertexData {
    vec3 texCoord;
} VertexOut;

void main()
{    
    
		VertexOut = VertexIn;
		
}