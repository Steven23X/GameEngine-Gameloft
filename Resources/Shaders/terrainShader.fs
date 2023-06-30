precision mediump float;
varying vec2 v_uv;
varying vec2 v_uv2;

uniform sampler2D u_textureuniform0;
uniform sampler2D u_textureuniform1;
uniform sampler2D u_textureuniform2;
uniform sampler2D u_textureuniform3;

void main()
{
vec4 vred = texture2D(u_textureuniform0, v_uv);
vec4 vgreen = texture2D(u_textureuniform1, v_uv);
vec4 vblue = texture2D(u_textureuniform2, v_uv);

vec4 vblend = texture2D(u_textureuniform3, v_uv2);
vec4 vfinal = vblend.r * vred + vblend.g * vgreen + vblend.b * vblue;
vfinal.a = 1.0;

gl_FragColor = vfinal;
}