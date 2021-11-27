#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform sampler2D heightmap;
uniform sampler2D rock;
uniform sampler2D snow;
varying vec2 v_texcoord;
varying vec3 v_position;


//! [0]
//void main()
//{
//    float height = texture2D(heightmap, v_texcoord).p;
//    if(height > 0.7){
//        gl_FragColor = texture2D(snow, v_texcoord);
//    }
//    else if(height > 0.5){
//        gl_FragColor = texture2D(rock, v_texcoord);
//    }
//    else{
//        gl_FragColor = texture2D(texture, v_texcoord);
//    }
//    // Set fragment color from texture

//}
void main()
{
    // Set fragment color from texture
    gl_FragColor = texture2D(texture, v_texcoord);
}
//! [0]
