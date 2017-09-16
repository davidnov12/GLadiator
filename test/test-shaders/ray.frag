#version 450

out vec4 color;

in vec4 screen;

uniform vec3 viewPos;
uniform vec3 lightPos;

struct Sphere{
  vec3 center;
  float radius;
  vec3 diffuse;
};

struct Ray{
  vec3 origin;
  vec3 direction;
};

struct Collision{
  float t;
  vec3 intersection;
  vec3 normal;
  vec3 color;
};

bool collisionRaySphere(Sphere sp, Ray r, out Collision col){

	vec3 oc = r.origin-sp.center;
	float b = 2*dot(r.direction,oc);
	float c = dot(oc,oc)-sp.radius*sp.radius;
	float d = b*b-4*c;

	if(d<0)return false;
	float sd = sqrt(d);
	float t1 = (-b+sd)/2;
	float t2 = (-b-sd)/2;

	if(t1<=0&&t2<=0)return false;

	col.t=(t1>0 && t1<t2)?t1:t2;
	col.intersection = r.origin+col.t*r.direction;
	col.normal = normalize(col.intersection-sp.center);
	col.color = sp.diffuse;

	return true;
}

void main(){

  Ray r;
  r.origin = viewPos;
  r.direction = normalize(screen.xyz -  viewPos);

  Sphere s;
  s.center = vec3(0.0, 0.0, -1.5);
  s.radius = 0.3;
  s.diffuse = vec3(0.1, 0.5, 0.8);

  Collision c;

  //color = vec4(1.0);

  if(!collisionRaySphere(s, r, c))
    color = vec4(1.0);

  else{
    float ambient = 0.1;
    float diffuse = max(0.0, dot(c.normal, normalize(c.intersection - lightPos)));

    color = vec4((ambient + diffuse) * c.color, 1.0);
  }
}
