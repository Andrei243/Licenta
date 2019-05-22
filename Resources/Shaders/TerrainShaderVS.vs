attribute vec3 a_posL;
uniform mat4 u_rotation;
uniform sampler2D u_texture3;

attribute vec2 a_uv;
varying vec2 v_uv;
uniform int u_var0;

uniform int u_var1;
uniform int u_var2;
uniform int u_var3;

uniform int u_var4;
uniform int u_var5;
void main()
{

vec2 aux=a_uv;
aux.x+=float(u_var4)/float(u_var0);
aux.y+=float(u_var5)/float(u_var0);
v_uv=aux;

vec2 uv_temp=v_uv*float(u_var0);
vec4 blend=texture2D(u_texture3,uv_temp);

vec4 posL = vec4(a_posL, 1.0);
//posL.y=float(-100);
posL.y+=blend.r*float(u_var1)+blend.g*float(u_var2)+blend.b*float(u_var3);
//posL.y=float(0);
gl_Position =u_rotation*posL;
}
   