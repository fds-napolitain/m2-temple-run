#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


uniform sampler2D texture;
uniform sampler2D groundH;
uniform sampler2D midH;
uniform sampler2D topH;
uniform vec4 light_color;
uniform vec3 light_position;
uniform vec3 cam_pos;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_position;
varying vec3 v_normal;
varying vec3 curPos;


float height(sampler2D HM, vec2 atexcoord)
{
    return texture2D(HM,atexcoord).z;

}

void main()
{
    float h = 0.0f;
    h = height(texture,v_texcoord);
    if (h < 0.3f)
    {
        gl_FragColor = texture2D(groundH,v_texcoord);
    }else if (h < 0.6f){
        gl_FragColor = texture2D(midH,v_texcoord);
    } else{
        gl_FragColor = texture2D(topH,v_texcoord);
    }
    

}
//! [0]
