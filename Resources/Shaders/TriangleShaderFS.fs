precision mediump float;
uniform sampler2D u_texture0;
varying vec2 v_uv;
uniform float r;
uniform float R;
uniform vec3 fogcol;
uniform vec3 camera;
varying vec3 pos;
void main()
{
//gl_FragColor=texture2D(u_texture,v_uv);
vec4 color=texture2D(u_texture0,v_uv);

float dis=distance(pos,camera);

if(color.a<0.01){
discard;
}
float cl=clamp(dis,r,R);
float alpha=(cl - r)/(R-r);
color=alpha * vec4(fogcol,1.0) + (1.0 - alpha )* color;
gl_FragColor=color;
//gl_FragColor=vec4(0.0,0.0,1.0,1.0);
}
