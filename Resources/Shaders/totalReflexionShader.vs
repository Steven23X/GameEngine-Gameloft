attribute vec3 a_posL;
attribute vec3 a_color;
attribute vec3 a_norm;
attribute vec2 a_uv;

varying vec3 v_color;
varying vec2 v_uv;

varying vec4 vectCam;
varying vec4 v_Wnorm;

uniform mat4 u_projectionmatrix;
uniform mat4 u_modelmatrix;
uniform mat4 u_viewmatrix;

void main()
{
gl_Position = u_projectionmatrix * u_viewmatrix * u_modelmatrix * vec4(a_posL, 1.0);

vectCam = u_modelmatrix * vec4(a_posL,1.0);
v_Wnorm = u_modelmatrix * vec4(a_norm,1.0);
v_color = a_color;
v_uv=a_uv;
}
   