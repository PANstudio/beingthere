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
    vec4 col_s = texture2D(tex0,texCoord + vec2(floor(sin(texCoordVarying.t/30.0*rand+rand*rand))*30.0*rand,0));
    
    col = col_s;
	gl_FragColor.rgba = col.rgba;
}
