#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif


uniform sampler2D texture;
uniform sampler2D Hground;
uniform sampler2D Hmid;
uniform sampler2D Htop;
uniform mat4 mvp_matrix;
uniform mat4 transform;
uniform mat3 normals_rotation;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_normal;
varying vec3 curPos;
uniform vec3 a_color;

float height(sampler2D HM, vec2 atexcoord)
{
    return texture2D(HM,atexcoord).z;

}

//! [0]
void main()
{

    curPos = vec3(transform *  vec4(a_position.x, a_position.y, a_position.z , 1.0))+vec3(height(texture,a_texcoord)*25.0f,0.0f,0.0f);
    gl_Position = mvp_matrix * vec4(curPos, 1.0);
    v_texcoord = a_texcoord;
    v_color = a_color;
    v_normal = vec3(transform* vec4(a_normal,1.0))+vec3(height(texture,a_texcoord)*25.0f,0.0f,0.0f);
    //v_normal = a_normal;

}
//! [0]
