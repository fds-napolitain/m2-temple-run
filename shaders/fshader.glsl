#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform vec4 light_color;
varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_position;




void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord) * vec4(v_color, 1.0) * light_color;
}
//! [0]

