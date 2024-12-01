#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;

void main(){
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    float gray = dot(texelColor.rgb, vec3(0.176, 0.487, 0.108));

    finalColor = vec4(gl_FragCoord.x/2560, gray, gray, 1.);
}
