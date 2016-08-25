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
    mediump float newTime = time * 2.0;

    vec2 newTexCoord;
    newTexCoord.s = texCoordVarying.s + (cos(newTime + (texCoordVarying.s*10.0)) * 0.01);
    newTexCoord.t = texCoordVarying.t + (sin(newTime + (texCoordVarying.t*10.0)) * 0.01);

    mediump vec2 texCoordRed    = newTexCoord;
    mediump vec2 texCoordGreen  = newTexCoord;
    mediump vec2 texCoordBlue   = newTexCoord;

    texCoordRed     += vec2( cos((newTime * 2.76)), sin((newTime * 2.12)) )* 0.01;
    texCoordGreen   += vec2( cos((newTime * 2.23)), sin((newTime * 2.40)) )* 0.01;
    texCoordBlue    += vec2( cos((newTime * 2.98)), sin((newTime * 2.82)) )* 0.01;

    mediump float colorR = texture2D( tex0, texCoordRed ).r;
    mediump float colorG = texture2D( tex0, texCoordGreen).g;
    mediump float colorB = texture2D( tex0, texCoordBlue).b;
    mediump float colorA = texture2D( tex0, texCoordBlue).a;
    mediump vec4 outColor = vec4( colorR, colorG, colorB, colorA);

    gl_FragColor = outColor;
}

//
//uniform sampler2DRect image;
//uniform int imgWidth,imgHeight;
//uniform float rand;
//uniform int flags;
//uniform vec2 blur_vec;
//uniform float timer;
//int flgs;
//float pix_w,pix_h;
//varying vec3 pos;
//
//void main (void)
//{
//    pix_w = 1.0;
//    pix_h = 1.0;
//    flgs = flags;
//    
//    vec2 texCoord = vec2(pos.x,pos.y);
//    vec4 col = texture2DRect(image,texCoord);
//    vec4 col_s = texture2DRect(image,texCoord + vec2(sin(pos.y*0.03+timer*20.0)*(6.0+12.0*rand),0));
//    
//    col = col_s;
////    col.r = col.r * sin(rand);
////	col.g = col.g * sin(rand*1.34+pos.y);
////	col.b = col.b * cos(rand*1.56+pos.x*pos.y);
//	
//    gl_FragColor.rgba = col.rgba;
//}
