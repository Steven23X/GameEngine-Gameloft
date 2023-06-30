attribute vec3 a_posL;

varying vec3 v_coord;

uniform mat4 u_projectionmatrix;
uniform mat4 u_modelmatrix;
uniform mat4 u_viewmatrix;

void main()
{
gl_Position = u_projectionmatrix * u_viewmatrix * u_modelmatrix * vec4(a_posL, 1.0);

v_coord = a_posL;
}