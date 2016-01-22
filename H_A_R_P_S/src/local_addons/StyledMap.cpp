//
//  StyledMap.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 19/12/2015.
//
//

#include "StyledMap.hpp"
//--------------------------------------------------------------
void StyledMap::setup(int width, int height)
{
    blur.setup(width, height);
    blur1.setup(width, height);
    deadlyMask.allocate(width, height);
    deadlyMask.begin();
    ofClear(0);
    deadlyMask.end();
    
    dangerMask.allocate(width, height);
    dangerMask.begin();
    ofClear(0);
    dangerMask.end();
    
    masks.allocate(width, height);
    masks.begin();
    ofClear(0);
    masks.end();
    
    test.allocate(width,height);
    test.begin();
    ofClear(0);
    test.end();
    
    test1.allocate(width,height);
    test1.begin();
    ofClear(0);
    test1.end();
    
    string fragment = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect maskTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    float mask = texture2DRect(maskTex, pos).r;\
    \
    gl_FragColor = vec4( src , mask);\
    }";
    
    maskDeadlyShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
    maskDeadlyShader.bindDefaults();
    maskDeadlyShader.linkProgram();
    
    
    string fragment1 = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect maskTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    float mask = texture2DRect(maskTex, pos).r;\
    \
    gl_FragColor = vec4( src , mask);\
    }";
    
    maskDangerShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment1);
    maskDeadlyShader.bindDefaults();
    maskDangerShader.linkProgram();
    
    fontSmall.load("ofxdatgui_assets/font-verdana.ttf", 9);
    
    text.clear();
    
    for (int i = 0; i < 1000; i++) {
        text.push_back(textLine(ofRandom(360), ofRandom(0, width), ofRandom(0,height), "Emotion " + ofToString(i)));
    }
}
//--------------------------------------------------------------
void StyledMap::update()
{
    test.begin();
    ofClear(0, 0, 0);
    ofSetColor(ofColor::red);
    ofDrawRectangle(0, 0, 500, 500);
    test.end();
    
    test1.begin();
    ofClear(0, 0, 0);
    for (int i = 0; i < text.size()/4; i++) {
        ofSetColor(ofColor::red);
        ofPushMatrix();
        ofTranslate(text[i]._x,text[i]._y);
        ofPushMatrix();
        ofRotateZ(text[i]._rotation);
        ofSetColor(255,255);
        fontSmall.drawString(text[i]._text, 0, 0);
        ofPopMatrix();
        ofPopMatrix();
    }
//    ofSetColor(ofColor::yellow);
//    ofDrawRectangle(0, 0, 500, 500);
    test1.end();
    
    ofSetCircleResolution(500);
    deadlyMask.begin();
    ofSetColor(0, 0, 0);
    ofDrawRectangle(0, 0, deadlyMask.getWidth(), deadlyMask.getHeight());
    ofSetColor(ofColor::white);
    ofPushStyle();
    ofSetColor(ofColor::white);
    if (!deadlyShapes.empty()) {
        for (int i = 0; i < deadlyShapes.size(); i++) {
        ofFill();
        ofBeginShape();
            for (int e = 0; e < deadlyShapes[i].size(); e++) {
                ofVertex(deadlyShapes[i][e].x, deadlyShapes[i][e].y);
            }
        ofEndShape(false);
        

        }
    }
    ofPopStyle();
    deadlyMask.end();
    
    dangerMask.begin();

    blur.begin(2,1);
    ofSetColor(ofColor::white);
    if (!dangerShapes.empty()) {
        for (int i = 0; i < dangerShapes.size(); i++) {
            ofFill();
            ofBeginShape();
            for (int e = 0; e < dangerShapes[i].size(); e++) {
                ofVertex(dangerShapes[i][e].x, dangerShapes[i][e].y);
            }
            ofEndShape(false);
            
            ofPopStyle();
        }
    }
    blur.end();
    dangerMask.end();
}
//--------------------------------------------------------------
void StyledMap::setShapes(vector<ofPolyline> deadly,vector <ofPolyline> danger)
{
    deadlyShapes.clear();
    dangerShapes.clear();
    deadlyShapes = deadly;
    dangerShapes = danger;
}
//--------------------------------------------------------------
void StyledMap::drawStyledMap(int x, int y)
{
    
    ofSetColor(ofColor::white);
    for (int i = 0; i < dangerShapes.size(); i++) {
        ofMesh m;
        m.setMode(OF_PRIMITIVE_TRIANGLES);
//        for (int x = 0; x < dangerShapes[i].size(); x++) {
            m.addVertices(dangerShapes[i].getVertices());
            m.drawWireframe();
//        }
    }
    //    masks.begin();
//    ofClear(0);
////    blur.begin(1,1);
//    ofClear(0);
//    ofPushStyle();
//    maskDangerShader.begin();
//    maskDangerShader.setUniformTexture("maskTex", dangerMask.getTexture(), 1);
//    test1.draw(0, 0);
//    maskDangerShader.end();
//    ofPopStyle();
//    
//    ofPushStyle();
//    maskDeadlyShader.begin();
//    maskDeadlyShader.setUniformTexture("maskTex", deadlyMask.getTexture(), 1);
//    test.draw(0, 0);
//    maskDeadlyShader.end();
//    ofPopStyle();
////    blur.end();
//    masks.end();
//    
//    masks.draw(x, y);
}