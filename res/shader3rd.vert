//Version Number
#version 400

//The layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoord;
layout (location = 2) in vec3 VertexNormal;

//Uniform variable
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;


out vec2 texCoords;
out vec3 normal;
out vec3 FragPos;



void main()
{
    texCoords = VertexTexCoord;
    FragPos = VertexPosition;

	// Sets the position of the current vertex
	gl_Position = transform *  vec4(VertexPosition, 1.0);

	//Sets normal
	normal = VertexNormal;

	
}
  