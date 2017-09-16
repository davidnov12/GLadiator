#version 450

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nrm;
layout (location = 2) in vec3 tng;
layout (location = 3) in vec3 btg;
layout (location = 4) in vec2 uvs;
layout (location = 5) in uint t_id;

uniform mat4 model, view, projection;

out vec3 normal;
out vec3 fragmentPos;
out vec2 tex_coord;
flat out uint tex;
out mat3 TBN;

void main(){
	normal = nrm;
	tex_coord = uvs;
	tex = t_id;
	fragmentPos = vec3(model * vec4(pos, 1.0));

	//tg = tng;

	vec3 T = normalize(vec3(model * vec4(tng, 0.0)));
	vec3 B = normalize(vec3(model * vec4(btg, 0.0)));
	vec3 N = normalize(vec3(model * vec4(nrm, 0.0)));
	TBN = mat3(T, B, N);

	gl_Position = projection * view * model * vec4(pos, 1.0);

}