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
	int step = 3;
	vec4 cols[9];/*自分の周辺のピクセルの色情報*/
    vec2 texCoord = texCoordVarying;/*自分の色情報*/

    /*周辺の色情報をピックアップして、RGBの平均値(グレースケール)をR要素に代入する*/
	for (int i = 0;i < step;i++){
		for (int j = 0;j < step;j++){
			cols[i*step+j] = texture2D(tex0,vec2((texCoordVarying.s+float(j)-2.0), (texCoordVarying.t+float(i)-2.0)));
			cols[i*step+j].r = (cols[i*step+j].r + cols[i*step+j].g + cols[i*step+j].b) / 3.0;
		}
	}

	/*取得した色の中で、輝度の最大値と最小値をピックアップする*/
	float mn = 1.0,mx = 0.0;
	for (int i = 0;i < step*step;i++){
		mn = min(cols[i].r,mn);
		mx = max(cols[i].r,mx);
	}

	/*最大・最小の差を計算して出力する*/
	float dst = abs(mx-mn);
	gl_FragColor.a = 1.0;
    gl_FragColor.rgb = vec3(dst,dst,dst);
}
