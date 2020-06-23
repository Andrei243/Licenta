
precision mediump float;
uniform samplerCube u_cube_texture;
varying vec3 v_coord;
void main()
{

gl_FragColor=textureCube(u_cube_texture,v_coord);
}

