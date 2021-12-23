#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec4 light_color;


void main()
{
    // Set fragment color from texture
    gl_FragColor = light_color;
}
//! [0]

