precision mediump float;
varying vec3 v_color;
varying vec2 v_uv;
uniform sampler2D u_textureuniform0;
void main()
{
    gl_FragColor = texture2D(u_textureuniform0, v_uv);
}
