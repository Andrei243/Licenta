attribute vec3 a_posL;
uniform mat4 u_rotation;
varying vec3 v_coord;
void main()
{
v_coord=a_posL;
vec4 posL = vec4(a_posL, 1.0);
gl_Position = u_rotation * posL;
}
   