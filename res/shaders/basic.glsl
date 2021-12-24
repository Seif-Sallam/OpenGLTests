#Shader Vertex
#version 330 core

layout(location = 0) in vec4 position; 
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVP;
void main() 
{
   gl_Position = u_MVP * position;
   v_TexCoords = texCoords;
}

#Shader Fragment
#version 330 core

out vec4 color;
uniform sampler2D u_Texture;
in vec2 v_TexCoords;

void main()
{
   vec4 tex = texture(u_Texture, v_TexCoords);
	color = tex;
}