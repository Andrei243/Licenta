attribute vec3 a_posL;
uniform mat4 u_rotation;
uniform sampler2D u_texture3;

attribute vec2 a_uv;
varying vec2 v_uv;
varying vec2 v_uv2;
uniform int u_var0;

uniform int u_var1;
uniform int u_var2;
uniform int u_var3;

uniform int u_var4;
uniform int u_var5;

uniform mat4 model;
varying vec3 pos;
void main()
{
v_uv=a_uv;
vec2 aux=a_uv;
aux.x=aux.x/float(u_var0);
aux.y=aux.y/float(u_var0);
aux.x+=float(u_var4)/float(u_var0);
aux.y+=float(u_var5)/float(u_var0);

v_uv2=aux;


vec4 blend=texture2D(u_texture3,aux);

vec4 posL = vec4(a_posL, 1.0);
posL.y+=blend.r*float(u_var1)+blend.g*float(u_var2)+blend.b*float(u_var3);
gl_Position =u_rotation*posL;
pos = vec3(model*posL);
}
   