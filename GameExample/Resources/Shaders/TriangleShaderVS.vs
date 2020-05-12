attribute vec3 a_posL;
uniform mat4 u_rotation;
attribute vec2 a_uv;
attribute vec3 a_norm;
varying vec2 v_uv;
varying vec3 pos;
uniform mat4 model;
varying vec3 norm;


void main()
{
v_uv=a_uv;
vec4 posL = vec4(a_posL, 1.0);
pos=vec3(model*posL);
norm=vec3(model * vec4(a_norm,0.0));
gl_Position = u_rotation * posL;
}
   