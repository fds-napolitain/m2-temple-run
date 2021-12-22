#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 transform;

attribute vec4 a_position;

varying vec3 v_color;
uniform vec3 a_color;


//! [0]
void main()
{
    gl_Position = mvp_matrix * transform * a_position;
}
//! [0]
