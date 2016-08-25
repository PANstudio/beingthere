precision highp float;

uniform sampler2D tex0;
uniform float useTexture;
uniform float useColors;
uniform vec4 color;
uniform vec2 resolution;

varying float depth;
varying vec4 colorVarying;
varying vec2 texCoordVarying;

void main (void)
{
    vec2 texCoord = texCoordVarying;
	vec4 col = texture2D(tex0,texCoord);;
	col.r = 1.0 - col.r;
	col.g = 1.0 - col.g;
	col.b = 1.0 - col.b;
	gl_FragColor = col;
}
