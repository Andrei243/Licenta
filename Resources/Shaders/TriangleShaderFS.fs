
precision mediump float;
uniform sampler2D u_texture;
varying vec2 v_uv;
void main()
{
//gl_FragColor=texture2D(u_texture,v_uv);
vec4 color=texture2D(u_texture,v_uv);
if(color.a<0.01){
discard;
}
gl_FragColor=color;

}
