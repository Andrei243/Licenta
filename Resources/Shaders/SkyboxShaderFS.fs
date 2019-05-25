
precision mediump float;
uniform samplerCube u_cube_texture;
varying vec3 v_coord;
void main()
{

gl_FragColor=textureCube(u_cube_texture,v_coord);
//gl_FragColor=vec4(1.0,1.0,1.0,1.0);
//gl_FragColor=vec4(v_coord.x,v_coord.y,v_coord.z,1.0);
}

