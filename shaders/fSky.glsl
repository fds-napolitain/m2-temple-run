#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


uniform vec4 light_color;
uniform samplerCube skybox;

varying vec3 v_texcoord;


void main()
{
    // Set fragment color from texture
    gl_FragColor = texture(skybox, v_texcoord);
}
//! [0]

