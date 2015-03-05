#version 440 core

in vec4 pos;
in vec4 col;

in vec3 N;
in vec3 v;

out vec4 fragData;

void main()
{
	vec3 lightDirection = -normalize(vec3(1,-2,3));
	fragData = vec4(clamp(col.rgb * dot(N,lightDirection), -1.0, 1.0), col.a);
	fragData = (fragData/2) + (col/2);
}