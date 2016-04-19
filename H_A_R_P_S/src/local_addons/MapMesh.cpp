//
//  MapMesh.cpp
//  H_A_R_P_S
//
//  Created by David Haylock on 17/04/2016.
//
//

#include "MapMesh.h"

void MapMesh::setup()
{
    
}
void MapMesh::update()
{
    
}
void MapMesh::clear()
{
    mainMesh.clear();
//    ofVec3f camDirection(0,0,1);
//    ofVec3f centre(50,50/2.f, 255/2.f);
//    ofVec3f camDirectionRotated = camDirection.getRotated(0, ofVec3f(1,0,0));
//    ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
    
//        cam.setPosition(camPosition);
//        cam.lookAt(centre);

}
void MapMesh::draw()
{
    
    //let's move the camera when you move the mouse
//    float rotateAmount = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0, 360);
    
    
    //move the camera around the mesh
//    ofVec3f camDirection(0,0,1);
//    ofVec3f centre(50,50/2.f, 255/2.f);
//    ofVec3f camDirectionRotated = camDirection.getRotated(0, ofVec3f(1,0,0));
//    ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
//    
////    cam.setPosition(camPosition);
////    cam.lookAt(centre);
//    ofPushView();
    ofPushMatrix();

    //	vidGrabber.draw(20,20);
    
    //but we want to enable it to show the mesh
    ofEnableDepthTest();
    cam.begin();
    
    //You can either draw the mesh or the wireframe
     mainMesh.drawWireframe();
//    mainMesh.draw();
//        mainMesh.drawFaces();
    cam.end();
    ofDisableDepthTest();
    ofPopMatrix();
//    ofPopView();
}
void MapMesh::getMapImage(cv::Mat map,ofImage styledImage)
{
    int width = map.cols;
    int height = map.rows;
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex(ofPoint(x,y,0));
            mainMesh.addColor(ofFloatColor(0,0,0));
        }
    }
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);				// 0
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex(x+(y+1)*width);			// 10
            
            mainMesh.addIndex((x+1)+y*width);			// 1
            mainMesh.addIndex((x+1)+(y+1)*width);		// 11
            mainMesh.addIndex(x+(y+1)*width);			// 10
        }
    }
    
    extrusionAmount = 25.0;
    
    for (int i=0; i<width*height-2; i++){
        ofFloatColor sampleColor(map.at<uchar>(i)/255.f);
        ofFloatColor newColor(styledImage.getColor(i).r/255.f,styledImage.getColor(i).g/255.f,styledImage.getColor(i).b/255.f);
//                              styledImage.getPixels()[i*3]/255.f,
//                              styledImage.getPixels()[i*3+1]/255.f,
//                              styledImage.getPixels()[i*3+2]/255.f
        
//        );
        ofVec3f tmpVec = mainMesh.getVertex(i);
        tmpVec.z = sampleColor.getBrightness() * extrusionAmount;
        mainMesh.setVertex(i, tmpVec);
        
        mainMesh.setColor(i, newColor);
    }

    
}