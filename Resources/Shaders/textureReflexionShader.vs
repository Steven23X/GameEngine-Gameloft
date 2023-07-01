attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec3 a_norm;
attribute vec2 a_uv;

varying vec3 v_color;
varying vec3 v_camera_pos;
varying vec2 v_uv;

varying vec4 v_posfrag;
varying vec4 v_Wnorm;

uniform mat4 u_projectionmatrix;
uniform mat4 u_modelmatrix;
uniform mat4 u_viewmatrix;

uniform vec3 u_cameraposuniform;

void main()
{
gl_Position = u_projectionmatrix * u_viewmatrix * u_modelmatrix * vec4(a_posL, 1.0);
v_posfrag = u_modelmatrix * vec4(a_posL,1.0);
v_Wnorm = u_modelmatrix * vec4(a_norm,0.0);

v_color = a_color;
v_camera_pos = u_cameraposuniform;
v_uv=a_uv;
}
   