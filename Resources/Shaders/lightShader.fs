precision mediump float;

varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform0;

varying vec4 v_Wnorm;
varying vec4 v_posfrag;
varying vec3 v_camera_pos;

uniform vec3 u_fogcolor;
uniform float u_sradius;
uniform float u_bradius;

vec3 dirReflect;
vec4 vectCam;

uniform samplerCube u_cubetextureuniform;

float d;
float alpha;


uniform vec3 u_ambcolor;
uniform float u_ambratio;
uniform float u_specpower;

uniform vec3 u_diffusecolor;
uniform vec3 u_specularcolor;
uniform vec3 u_direction;

void main()
{   
    d =distance(v_posfrag,vec4(v_camera_pos,0.0));
    d = (d - u_sradius) / (u_bradius-u_sradius);
    alpha= clamp(d,0.0,1.0);

    vectCam = v_posfrag - vec4(v_camera_pos,0.0);
    dirReflect = normalize(reflect(normalize(vectCam.xyz),normalize(v_Wnorm.xyz)));

    vec4 c_final_object= texture2D(u_textureuniform0, v_uv);
    c_final_object.a=1.0;

    vec4 vfinal=alpha * vec4(u_fogcolor,1.0) + (1.0-alpha) * c_final_object;

    vec3 ambientalComponent = vfinal.rgb * u_ambcolor, viewDirection = normalize(v_camera_pos-v_posfrag.xyz);
    vec3 halfWayDirection, specularComponent = vec3(0.0, 0.0, 0.0), diffuseComponent = vec3(0.0, 0.0, 0.0), direction;
    float spec;

    halfWayDirection = normalize(-normalize(u_direction) + viewDirection);
	spec = pow(max(dot(normalize(v_Wnorm.xyz), halfWayDirection), 0.0), u_specpower);
	specularComponent = specularComponent + u_specularcolor * spec;
	diffuseComponent = diffuseComponent + vfinal.rgb * u_diffusecolor * max(dot(normalize(v_Wnorm.xyz), -normalize(u_direction)), 0.0);
    
	vfinal = vec4(u_ambratio * ambientalComponent + (1.0 - u_ambratio) * (diffuseComponent + specularComponent), vfinal.a);

    gl_FragColor = vfinal;
}
