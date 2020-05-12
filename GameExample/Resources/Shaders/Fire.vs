attribute vec3 a_posL;
uniform mat4 u_rotation;
attribute vec2 a_uv;
varying vec2 v_uv;
varying vec3 pos;
uniform mat4 model;
void main()
{
v_uv=a_uv;
vec4 posL = vec4(a_posL, 1.0);
pos=vec3(model*posL);
gl_Position = u_rotation * posL;
}
   