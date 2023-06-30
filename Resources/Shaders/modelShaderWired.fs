precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform;
void main()
{
    gl_FragColor = vec4(v_color,1);
}
