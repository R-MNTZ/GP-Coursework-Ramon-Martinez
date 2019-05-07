#version 330 core
//This isn't the 3rd shader specified for the coursework, this was kept in so the environment mapping shader
// had something to reflect
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;


uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}  