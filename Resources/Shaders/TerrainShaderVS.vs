attribute vec3 a_posL;
uniform mat4 u_rotation;
uniform sampler2D u_texture3;

attribute vec2 a_uv;
varying vec2 v_uv;
uniform int u_var0;

uniform int u_var1;
uniform int u_var2;
uniform int u_var3;
void main()
{

v_uv=a_uv*float(u_var0);
vec4 blend=texture2D(u_texture3,v_uv);
vec4 posL = vec4(a_posL, 1.0);
posL.y+=blend.r*float(u_var1)+blend.g*float(u_var2)+blend.b*float(u_var3);
gl_Position = u_rotation * posL;
}
   