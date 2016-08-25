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

    vec4 col = texture2D(tex0,texCoord);

    vec4 col_s[5],col_s2[5];
    for (int i = 0;i < 5;i++){
        col_s[i] = texture2D(tex0,texCoord +  vec2(-800.0*float(i)*2.0 ,-pix_h*float(i)*2.0));
        col_s2[i] = texture2D(tex0,texCoord + vec2( 800*float(i)*2.0 , 480.0*float(i)*blur_vec.y));
    }
    col_s[0] = (col_s[0] + col_s[1] + col_s[2] + col_s[3] + col_s[4])/5.0;
    col_s2[0]= (col_s2[0]+ col_s2[1]+ col_s2[2]+ col_s2[3]+ col_s2[4])/5.0;
    col = (col_s[0] + col_s2[0]) / 2.0;
        
    gl_FragColor.rgba = col.rgba;
}
