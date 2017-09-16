#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform vec3 screenCoords[4];

out vec4 screen;

void main(){

  vec4 screens[4];
  screens[0] = vec4(-1.0, -1.0, 0.0, 1.0);
  screens[1] = vec4(-1.0, 1.0, 0.0, 1.0);
  screens[2] = vec4(1.0, -1.0, 0.0, 1.0);
  screens[3] = vec4(1.0, 1.0, 0.0, 1.0);

  for(int i = 0; i < 4; i++){
    screen = vec4(screenCoords[i], 1.0);
    gl_Position = screens[i];
    EmitVertex();
  }
  EndPrimitive();
}
