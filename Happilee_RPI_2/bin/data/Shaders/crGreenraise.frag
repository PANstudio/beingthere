precision highp float;
uniform sampler2D tex0;
uniform float useTexture;
uniform float useColors;
uniform vec4 color;
uniform vec2 resolution;

varying float depth;
varying vec4 colorVarying;
varying vec2 texCoordVarying;
uniform float time;
uniform float rand;

float pix_w;
float pix_h;

void main (void)
{
    float e = 2.718281828459045235360287471352;
    vec2 texCoord = texCoordVarying;
    vec4 col = texture2D(tex0,texCoord);
    
    vec3 k =   vec3(0.2,0.4,0.2);
    vec3 min = vec3(0.0,1.0,0.0);
    vec3 max = vec3(1.0,0.0,1.0);
    
    col.r = (1.0/(1.0+pow(e,(-k.r*((col.r*2.0)-1.0)*20.0)))*(max.r-min.r)+min.r);
    col.g = (1.0/(1.0+pow(e,(-k.g*((col.g*2.0)-1.0)*20.0)))*(max.g-min.g)+min.g);
    col.b = (1.0/(1.0+pow(e,(-k.b*((col.b*2.0)-1.0)*20.0)))*(max.b-min.b)+min.b);
    
    gl_FragColor.rgba = col.rgba;
}