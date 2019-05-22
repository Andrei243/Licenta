precision mediump float;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec2 v_uv;
void main()
{
//gl_FragColor=texture2D(u_texture,v_uv);
vec4 color1=texture2D(u_texture0,v_uv);
vec4 color2=texture2D(u_texture1,v_uv);
vec4 color3=texture2D(u_texture2,v_uv);
vec4 blend=texture2D(u_texture3,v_uv);
vec4 color=color1*blend.x+color2*blend.y+color3*blend.z;
color.a=1.0;
gl_FragColor=color;
//gl_FragColor=vec4(0.0,0.0,1.0,1.0);
}
