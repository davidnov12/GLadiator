#version 450
#extension GL_ARB_bindless_texture : require

in vec3 normal;
in vec2 tex_coord;
in vec3 fragmentPos;
in float tex;

out vec4 color;

layout (std430, binding = 1) buffer air{
	sampler2D airTex[];
};

void main(){
	//color = texture(diffuse, tex_coord);
	//color = vec4(0.2, 0.8, 0.6, 1.0);
	vec3 lightPos = vec3(0.0, 0.5, 0.0);
	
	
	//vec3 ambient = vec3(0.1);
	float ambient = 0.1;

	vec3 lightDir = normalize(lightPos - fragmentPos);
	//vec3 diffuse = vec3(1.0) * max(dot(lightDir, normal), 0.0);
	float diffuse = max(dot(lightDir, normal), 0.0);

	color = vec4(vec3(ambient + diffuse), 1.0) * max(texture(airTex[int(tex)], tex_coord), vec4(0.2));
/*
	if(tex == 0){
		color = (ambient + diffuse) * vec4(0.0, 1.0, 0.0, 1.0);
	}
	else if(tex == 2){
		color = (ambient + diffuse) * vec4(0.0, 0.0, 1.0, 1.0);
	}
		//color = (ambient + diffuse) * vec4(0.0, 0.0, 1.0, 1.0);
	*/	

	//color = texture(diff, tex_coord);
	//color = vec4((ambient + diffuse), 1.0) * texture(diff, tex_coord);
	//color = vec4((ambient + diffuse) * vec3(0.2, 0.8, 0.6), 1.0);
	//color = vec4((ambient + diffuse) * vec3(0.5, 0.9, 0.1), 1.0);
	//color = vec4((ambient + diffuse) * vec3(0.1, 0.45, 0.85), 1.0);
}