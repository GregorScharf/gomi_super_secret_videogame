#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    float red_gray = dot(texelColor.rgb, vec3(0.799, 0.587, 0.114));

    finalColor = vec4(red_gray*10, red_gray, red_gray, texelColor.a);
}
