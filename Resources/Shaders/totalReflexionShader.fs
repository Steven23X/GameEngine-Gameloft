precision mediump float;

varying vec3 v_color;
varying vec2 v_uv;

varying vec4 v_Wnorm;
varying vec4 v_posfrag;
varying vec3 v_camera_pos;

vec3 dirReflect;
vec4 vectCam;

uniform vec3 u_fogcolor;
uniform float u_sradius;
uniform float u_bradius;

uniform samplerCube u_cubetextureuniform;

float d;
float alpha;
void main()
{
    d =distance(v_posfrag,vec4(v_camera_pos,0.0));
    d = (d - u_sradius) / (u_bradius-u_sradius);

    alpha= clamp(d,0.0,1.0);

    vectCam = v_posfrag - vec4(v_camera_pos,0.0);
    dirReflect = normalize(reflect(normalize(vectCam.xyz),normalize(v_Wnorm.xyz)));
    vec4 c_final_object = textureCube(u_cubetextureuniform, -dirReflect);
    c_final_object.a=1.0;

    vec4 vfinal=alpha * vec4(u_fogcolor,1.0) + (1.0-alpha) * c_final_object;

    gl_FragColor = vfinal;
}