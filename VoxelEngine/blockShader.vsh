#version 440 core

out vec3 N;
out vec3 v;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 position;
in vec3 normal;
in vec4 color;
out vec4 pos;
out vec4 col;

void main()
{
	v = vec3(vec3(view * model * vec4(position.xyz, 1)));       
    N = normalize(normalize(normal));

	pos = vec4(position.xyz, 1);
	col = color;
	gl_Position = projection * view * model * pos;
}