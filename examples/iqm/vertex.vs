#version 330
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;
out vec2 fragTexCoord;
out vec4 fragColor;
uniform mat4 mvp;

in ivec4 vertexBone;
in vec4 vertexWeight;
#define MAX_BONE_CNT 100
uniform mat4 bindPose[MAX_BONE_CNT];

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    vec4 newVertex;
    vec4 finalPosition = vec4(vertexPosition,1.0);
    newVertex = (bindPose[vertexBone.x]*finalPosition)*vertexWeight.x;
    newVertex = (bindPose[vertexBone.y]*finalPosition)*vertexWeight.y+newVertex;
    newVertex = (bindPose[vertexBone.z]*finalPosition)*vertexWeight.z+newVertex;
    newVertex = (bindPose[vertexBone.w]*finalPosition)*vertexWeight.w+newVertex;

    gl_Position = mvp*newVertex;
}
