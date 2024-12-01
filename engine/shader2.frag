#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;


void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    finalColor = vec4(vec3(1.,1.,1.)-texelColor.xyz, 1.0);
}
