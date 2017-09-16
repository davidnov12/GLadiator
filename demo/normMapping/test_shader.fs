#version 450
#extension GL_ARB_bindless_texture : require

uniform sampler2D diff;
uniform int meshID;
uniform vec3 viewPos;

in vec3 normal;
in vec2 tex_coord;
in vec3 fragmentPos;
flat in uint tex;
in mat3 TBN;

out vec4 color;

struct material{
	sampler2D diffuseTexture;
	//sampler2D specularTexture;
	sampler2D normalTexture;
};

layout (std430, binding = 0) buffer textures{	
	//sampler2D diffuseTex[];
	material maters[];
};

layout (std430, binding = 1) buffer texts{
	sampler2D pumTex[];
};


void main(){
	//color = texture(diffuse, tex_coord);
	//color = vec4(0.2, 0.8, 0.6, 1.0);
	//vec3 norml = normal;
	vec3 col = texture(maters[tex].diffuseTexture, tex_coord).rgb;
	vec3 norml = texture(maters[tex].normalTexture, tex_coord).xyz;
	norml = normalize(norml * 2.0 - 1.0);
	norml = normalize(TBN * norml);
	//norml = normal;
	//vec3 lightPos = vec3(0.0, 0.5, 0.0);
	vec3 lightPos = vec3(0.0, 1.0, 1.5);
	vec3 lightDir = normalize(lightPos - fragmentPos);
	//vec3 viewPos = vec3(0.0, 0.0, 0.0);
	vec3 viewDir = normalize(viewPos - fragmentPos);
	vec3 reflectDir = reflect(lightDir, norml);

	//vec3 ambient = vec3(0.1);
	vec3 ambient = 0.1 * col;

	//vec3 diffuse = vec3(1.0) * max(dot(lightDir, normal), 0.0);
	vec3 diffuse = 0.7 * max(dot(lightDir, norml), 0.01) * col;

	vec3 specular = 0.4 * pow(max(0.0, dot(viewDir, reflectDir)), 32) * vec3(1.0);
	//vec3 spec = 0 * 0.3 * specular * vec3(1.0);
	
	//if(meshID == 1) color = vec4(vec3(ambient + diffuse), 1.0) * max(texture(maters[tex].diffuseTexture, tex_coord), vec4(0.9));
	 //color = vec4(vec3(ambient + diffuse), 1.0) * max(texture(maters[tex].diffuseTexture, tex_coord), vec4(0.9));
	 //color = texture(maters[tex].diffuseTexture, tex_coord);

	 color = vec4(ambient + diffuse + specular, 1.0);

	//color = vec4(norml, 1.0);

	/*if(tg.x == 0 && tg.y == 0 && tg.z == 0)
		color = vec4(0, 1, 1, 1);*/
	
	//color = vec4(norml, 1.0);
	//color = vec4(0.8, 0.4, 0.1, 1.0);

	//color = vec4(vec3(ambient + diffuse), 1.0) * vec4(0.1, 0.7, 0.5, 1.0);
	//else if(meshID == 2) color = vec4(vec3(ambient + diffuse), 1.0) * max(texture(diffuseTex[tex + 12], tex_coord), vec4(0.2)) + vec4(spec, 1.0);
	//else color = vec4(vec3(ambient + diffuse), 1.0) *  vec4(0.2, 0.5, 0.7, 1.0) + vec4(spec, 1.0);
	//color = texture(diff, tex_coord);
	//color = vec4((ambient + diffuse), 1.0) * texture(diff, tex_coord);
	//color = vec4((ambient + diffuse) * vec3(0.2, 0.8, 0.6), 1.0);
	//color = vec4((ambient + diffuse) * vec3(0.5, 0.9, 0.1), 1.0);
	//color = vec4((ambient + diffuse) * vec3(0.1, 0.45, 0.85), 1.0);
}