//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

in VertexData {
   vec2 texCoord1;
} Vertex;

//Unfrom variable
uniform float randColourX;
uniform float randColourY;
uniform float randColourZ;
 
uniform sampler2D diffuse;

void main()
{


    fragcolor = vec4(texture(diffuse, Vertex.texCoord1));

	float gamma = 2.2;
     fragcolor.rgb = pow(fragcolor.rgb, vec3(1.0/gamma));
}