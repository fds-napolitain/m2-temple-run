#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 transform;

attribute vec4 a_position;

varying vec3 v_texcoord;

//! [0]
void main()
{
    v_texcoord = vec3(a_position);
    gl_Position = mvp_matrix  * a_position;
}
//! [0]
