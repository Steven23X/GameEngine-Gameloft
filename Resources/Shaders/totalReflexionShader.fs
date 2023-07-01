precision mediump float;
varying vec4 v_Wnorm;
vec3 dirReflect;
varying vec4 vectCam;

uniform samplerCube u_cubetextureuniform;
void main()
{
     dirReflect = reflect(normalize(vectCam.xyz),normalize(v_Wnorm.xyz));

    vec4 vfinal = textureCube(u_cubetextureuniform, dirReflect);
	gl_FragColor = vfinal;
}