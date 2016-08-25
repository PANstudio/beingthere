precision highp float;

uniform sampler2D tex0;
uniform float useTexture;
uniform float useColors;
uniform vec4 color;
uniform vec2 resolution;

varying float depth;
varying vec4 colorVarying;
varying vec2 texCoordVarying;

float pix_w,pix_h;

void main (void)
{
    pix_w = 1.0 / float(800);
    pix_h = 1.0 / float(480);
    
	float slit_h = val3;
	
    vec2 texCoord = vec2(3.0+floor(texCoordVarying.s/slit_h)*slit_h ,texCoordVarying.t);
    vec4 col = texture2D(tex0,texCoord);
	
    gl_FragColor.rgba = col.rgba;
}
