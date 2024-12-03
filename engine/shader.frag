#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

out vec4 finalColor;


void main()
{
    vec3 world_pos = gl_FragCoord.xyz;
    vec4 texelColor = texture(texture0, fragTexCoord)*colDiffuse*fragColor;

    float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));

    vec3 n = vec3(world_pos.x / (world_pos.x + world_pos.y + world_pos.z), world_pos.y / (world_pos.x + world_pos.y + world_pos.z), world_pos.x / (world_pos.x + world_pos.y + world_pos.z));
    
    float l = -sqrt(n.x * n.x + n.y * n.y + n.z * n.z) + 1;

    finalColor = vec4(vec3(texelColor.x + l, texelColor.y + l, texelColor.z + l ), texelColor.a);
}
