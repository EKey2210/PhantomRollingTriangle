#version 150

#define PI 3.14159265359
#define TWO_PI 6.28318530718
const int shapeNum = 40;

uniform vec2 resolution;
uniform float time;
uniform vec2 positions[shapeNum];
uniform vec3 colors[shapeNum];
uniform float velocity[shapeNum];
uniform float radius[shapeNum];
uniform sampler2DRect fbo;

out vec4 outputColor;

mat2 rotate(float a){  //回転行列
  float c = cos(a);
  float s = sin(a);
  return mat2(c,-s,s,c);
}

vec3 triangle(vec2 p,float size,float interval){  //三角形描画
  float a = atan(p.x,p.y)+PI;
  float r = TWO_PI/3.0;
  float d = cos(floor(.5+a/r)*r-a)*length(p);
  return vec3(1.0-smoothstep(size,size+interval,d));
}

void main() {
  vec2 center = (gl_FragCoord.xy*2.0-resolution)/min(resolution.x,resolution.y);

  vec3 color = vec3(0.0);

  for(int i = 0; i < shapeNum; i++){
    float r = radius[i];
    vec2 pos = vec2(positions[i].x, -positions[i].y) / min(resolution.x, resolution.y) * 2.0;
    pos.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);
    vec2 p = pos-center;
    float rotateV = velocity[i]/3.0;
    color += triangle(p * rotate(time*(-rotateV)),r,0.1) * colors[i];
  }

  vec4 fbo_value = texture(fbo, vec2(gl_FragCoord.x, gl_FragCoord.y));
  outputColor = vec4(color,1.0) + fbo_value * 0.95;
}
