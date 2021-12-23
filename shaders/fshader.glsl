#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform vec4 light_color;
uniform vec3 light_position;
uniform vec3 cam_pos;

varying vec2 v_texcoord;
varying vec3 v_color;
varying vec3 v_position;
varying vec3 v_normal;
varying vec3 curPos;




void main()
{
    float ambiant = 0.2f;
    vec3 normal = normalize(v_normal);
    vec3 ligthDirection = normalize(light_position - curPos);

    float diffuse = max(dot(normal, ligthDirection), 0.0f);

    float specularIntensity = 0.5f;
    vec3 viewDirection = normalize(cam_pos - curPos);
    vec3 reflectionDirection = reflect(-ligthDirection, normal);

    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8.);
    float specular =  specAmount * specularIntensity;
    gl_FragColor = texture2D(texture, v_texcoord) * vec4(v_color, 1.0) * light_color * (diffuse + ambiant + specular) ;
}
//! [0]

