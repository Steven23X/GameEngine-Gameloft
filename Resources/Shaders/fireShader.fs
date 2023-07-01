precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform0;
uniform sampler2D u_textureuniform1;
uniform sampler2D u_textureuniform2;

uniform vec3 u_fogcolor;
uniform float u_sradius;
uniform float u_bradius;

varying vec4 v_Wnorm;
varying vec4 v_posfrag;
varying vec3 v_camera_pos;

float d;
float alpha;

uniform float u_time;
uniform float u_dispmax;

void main()
{   
    d =distance(v_posfrag,vec4(v_camera_pos,0.0));
    d = (d - u_sradius) / (u_bradius-u_sradius);

    alpha= clamp(d,0.0,1.0);

    vec2 disp = texture2D(u_textureuniform0, vec2(v_uv.x, v_uv.y + u_time)).rg;
    vec2 offset = vec2(u_dispmax * (2.0 * disp.x - 1.0), u_dispmax * (2.0 * disp.y - 1.0));
    vec2 v_uv_displaced = v_uv + offset;

    vec4 c_fire = texture2D(u_textureuniform1, v_uv_displaced);
    vec4 c_alpha = texture2D(u_textureuniform2, v_uv);
    c_fire.a *= c_alpha.r;
    vec4 vobject = texture2D(u_textureuniform0, v_uv);

    vec4 vfinal=alpha * vec4(u_fogcolor,1.0) + (1.0-alpha) * c_fire;

    gl_FragColor = vfinal;
}
