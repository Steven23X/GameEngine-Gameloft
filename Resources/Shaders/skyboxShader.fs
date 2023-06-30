precision mediump float;
varying vec3 v_coord;
uniform samplerCube u_cubetextureuniform;
void main()
{
    vec4 vfinal = textureCube(u_cubetextureuniform, v_coord);
	gl_FragColor = vfinal;
}