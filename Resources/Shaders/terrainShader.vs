attribute vec3 a_posL;
attribute vec2 a_uv;
attribute vec2 a_uv2;

varying vec2 v_uv;
varying vec2 v_uv2;
varying vec3 v_camera_pos;
varying vec4 v_posfrag;

uniform mat4 u_projectionmatrix;
uniform mat4 u_modelmatrix;
uniform mat4 u_viewmatrix;

uniform vec3 u_height;

uniform sampler2D u_textureuniform3;
uniform vec3 u_cameraposuniform;

void main()
{
vec4 posL = vec4(a_posL, 1.0);
vec4 vblend = texture2D(u_textureuniform3, a_uv2);
vec4 pos_new = posL;

pos_new.y += vblend.r * u_height.r + vblend.g * u_height.g + vblend.b * u_height.b;
pos_new.w = 1.0;
gl_Position = u_projectionmatrix * u_viewmatrix * u_modelmatrix * pos_new;

v_posfrag = u_modelmatrix * pos_new;

v_uv = a_uv;
v_camera_pos = u_cameraposuniform;
v_uv2 = a_uv2;
}