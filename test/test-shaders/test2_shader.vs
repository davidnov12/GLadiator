#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nrm;
layout (location = 2) in vec2 uvs;
layout (location = 3) in float t_id;

uniform mat4 model, view, projection;

out vec3 normal;
out vec3 fragmentPos;
out vec2 tex_coord;
out float tex;

void main(){
	normal = nrm;
	tex_coord = uvs;
	tex = t_id;
	fragmentPos = vec3(model * vec4(pos, 1.0));
	gl_Position = model * view /* projection */* vec4(pos, 1.0);
}