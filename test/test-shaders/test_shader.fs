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
	sampler2D normalTexture;
	sampler2D roughTexture;
	sampler2D metalTexture;
	sampler2D aoTexture;
	sampler2D heightMap;
};

layout (std430, binding = 0) buffer textures{	
	material maters[];
};


vec2 parallaxMapping(vec3 viewDir, vec2 tc){
	float height = texture(maters[tex].heightMap, tc).r;
	vec2 p = (viewDir.xy / viewDir.z) * (height * 0.03);
	return tc - p;
}

void main(){
	//color = texture(diffuse, tex_coord);
	//color = vec4(0.2, 0.8, 0.6, 1.0);
	//vec3 norml = normal;
	vec3 viewDir = normalize(viewPos - fragmentPos);
	vec2 uv = parallaxMapping(viewDir, tex_coord);

	if(uv.x > 1.0 || uv.x < 0.0 || uv.y > 1.0 || uv.y < 0.0)
		discard;
	//uv = tex_coord;

	vec3 col = texture(maters[tex].diffuseTexture, uv).rgb;
	vec3 norml = texture(maters[tex].normalTexture, uv).xyz;
	norml = normalize(norml * 2.0 - 1.0);
	norml = normalize(TBN * norml);
	//norml = normal;
	//vec3 lightPos = vec3(0.0, 0.5, 0.0);
	vec3 lightPos = vec3(0.0, 1.0, 1.5);
	vec3 lightDir = normalize(lightPos - fragmentPos);
	//viewDir = normalize(viewPos - fragmentPos);
	vec3 reflectDir = reflect(lightDir, norml);

	vec3 ambient = 0.1 * col * texture(maters[tex].aoTexture, uv).r;

	vec3 diffuse = 0.7 * max(dot(lightDir, norml), 0.01) * col;

	vec3 specular = 0.4 * pow(max(0.0, dot(viewDir, reflectDir)), 32) * vec3(1.0);

	 color = vec4(ambient + diffuse + specular, 1.0);

}