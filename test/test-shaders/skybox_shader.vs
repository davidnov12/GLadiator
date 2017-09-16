#version 450

layout (location = 0) in vec3 pos;

out vec3 tc;

uniform mat4 view;
uniform mat4 projection;

void main(){
	tc = pos;
	//vec4 p = view * vec4(pos, 1.0);
	//gl_Position = p.xyww;
	gl_Position = projection * view * vec4(pos, 1.0);
}