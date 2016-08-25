#version 120
//varying vec3 pos;
void main(void)
{
//    pos = gl_Vertex.xyz;
    gl_Position = ftransform();
    gl_TexCoord[0] = gl_MultiTexCoord0;
}
