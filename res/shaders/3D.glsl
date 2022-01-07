#Shader Vertex
#version 330 core 

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;

void main() 
{
   gl_Position = u_MVP * vec4(position, 1.0);
}

#Shader Fragment
#version 330 core

out vec4 color;

void main()
{
    color = vec4(0.5, 0.23, 0.78, 1.0);
}
