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

void main (void)
{
    vec2 texCoord = texCoordVarying;

    vec4 col = texture2D(tex0,texCoord);
    vec4 col_r = texture2D(tex0,texCoord + vec2(-35.0*rand,0));
    vec4 col_l = texture2D(tex0,texCoord + vec2( 35.0*rand,0));
    vec4 col_g = texture2D(tex0,texCoord + vec2( -7.5*rand,0));
    

    col.b = col.b + col_r.b*max(1.0,sin(texCoordVarying.y*1.2)*2.5)*rand;
    col.r = col.r + col_l.r*max(1.0,sin(texCoordVarying.y*1.2)*2.5)*rand;
    col.g = col.g + col_g.g*max(1.0,sin(texCoordVarying.y*1.2)*2.5)*rand;

    gl_FragColor.rgba = col.rgba;
}
