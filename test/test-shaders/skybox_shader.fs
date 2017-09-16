#version 450

out vec4 color;

in vec3 tc;

uniform samplerCube cubemap;

void main(){
	color = texture(cubemap, tc);
}