#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;
uniform mat4 transform;

attribute vec4 a_position;
attribute vec2 a_texcoord;

varying vec2 v_texcoord;
varying vec3 v_color;



uniform vec3 a_color;
uniform sampler2D heightmap;
uniform sampler2D texture;
uniform sampler2D snow;
uniform sampler2D rock;



//! [0]
void main()
{
   // float height = texture2D(heightmap, a_texcoord).p;

    // Calculate vertex position in screen space

    gl_Position = mvp_matrix * transform * vec4(a_position.x, a_position.y, a_position.z , 1.0);

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    v_color = a_color;

}
//! [0]
