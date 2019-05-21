
precision mediump float;
uniform samplerCube u_cube_texture;
varying vec3 v_coord;
void main()
{

gl_FragColor=textureCube(u_cube_texture,v_coord);
//gl_FragColor=vec4(0.0,0.0,1.0,1.0);
}

