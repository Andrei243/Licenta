precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
varying vec2 v_uv;
uniform float r;
uniform float R;
uniform vec3 fogcol;
uniform vec3 camera;
varying vec3 pos;
uniform float u_var0;
uniform float u_var1;

void main()
vec2 disp=texture2D(u_texture2,vec2(v_uv.x,v_uv.y+u_var0)).rg;
vec2 offset = ((disp*float(2))-float(1))*float(u_var1);

vec2 uv_displ=v_uv+offset;

vec4 c_fire=texture2D(u_texture1,uv_displ);
float alpha=texture2D(u_texture0,vec2(v_uv.x,v_uv.y)).x;
c_fire.a=c_fire.a * alpha;
vec4 color=c_fire;
gl_FragColor=color;
}
