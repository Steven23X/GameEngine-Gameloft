precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
void main()
{
    gl_FragColor = vec4(v_color,1);
}
