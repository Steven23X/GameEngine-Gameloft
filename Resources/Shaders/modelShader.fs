precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform0;

uniform vec3 u_fogcolor;
uniform float u_sradius;
uniform float u_bradius;

varying vec4 v_Wnorm;
varying vec4 v_posfrag;
varying vec3 v_camera_pos;

float d;
float alpha;

void main()
{   
    d =distance(v_posfrag,vec4(v_camera_pos,0.0));
    d = (d - u_sradius) / (u_bradius-u_sradius);

    alpha= clamp(d,0.0,1.0);

    vec4 vobject = texture2D(u_textureuniform0, v_uv);
    vec4 vfinal=alpha * vec4(u_fogcolor,1.0) + (1.0-alpha) * vobject;

    gl_FragColor = vfinal;
}
