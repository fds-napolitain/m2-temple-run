#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform vec4 light_color;
uniform vec3 light_position;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_position;
varying vec3 v_normal;
varying vec3 curPos;




void main()
{
    vec3 normal = normalize(v_normal);
    vec3 ligthDirection = normalize(light_position - curPos);

    float diffuse = dot(normal, ligthDirection);
    gl_FragColor = texture2D(texture, v_texcoord) * vec4(v_color, 1.0) * light_color * diffuse ;
}
//! [0]

