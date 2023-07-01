precision mediump float;

varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform0;

varying vec4 v_Wnorm;
varying vec4 v_posfrag;
varying vec3 v_camera_pos;

vec3 dirReflect;
vec4 vectCam;

uniform samplerCube u_cubetextureuniform;
void main()
{   
    vectCam = v_posfrag - vec4(v_camera_pos,0.0);
    dirReflect = normalize(reflect(normalize(vectCam.xyz),normalize(v_Wnorm.xyz)));
    vec4 c_reflexie = textureCube(u_cubetextureuniform, -dirReflect);

    vec4 c_proprie= texture2D(u_textureuniform0, v_uv);

    vec4 c_final= c_reflexie * 0.7 + c_proprie * 0.3;
    c_final.a=1.0;

    gl_FragColor = c_final;
}
