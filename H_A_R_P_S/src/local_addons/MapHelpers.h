//
//  MapHelpers.h
//  H_A_R_P_S
//
//  Created by David Haylock on 11/11/2015.
//
//

#ifndef MapHelpers_h
#define MapHelpers_h

#include <stdio.h>
#include "ofMain.h"

struct MapDetails {
    string Difficulty;
    int numberOfLevels;
};

struct Map {
    string difficulty;
    int level;
    int timeNeededToSolveMap;
    int width;
    int height;
    int offsetEdge;
    int tileSize;
    int numberOfClouds;
    int smoothingValue;
    int growthLoops;
    int seedValue;
    bool useRandomSeed;
    int dangerAreaSize;
    int dangerAreaToxicity;
    int deadAreaToxicity;
    int redThreshold;
    int greenThreshold;
    ofPoint startingPosition;
    ofPoint endPosition;
    
    void printDetails() {
        cout << "-------------------------" << endl;
        cout << "Difficulty " << difficulty << endl;
        cout << "Level " << level << endl;
        cout << "Time Needed to Solve Map " << timeNeededToSolveMap << endl;
        cout << "Width " << width << endl;
        cout << "Height " << height << endl;
        cout << "Offset Edge " << offsetEdge << endl;
        cout << "Tile Size " << tileSize << endl;
        cout << "Number Of Clouds " << numberOfClouds << endl;
        cout << "SmoothingValue " << smoothingValue << endl;
        cout << "GrowthLoops " << growthLoops << endl;
        cout << "SeedValue " << seedValue << endl;
        cout << "UseRandomSeed " << useRandomSeed << endl;
        cout << "DangerAreaSize "  << dangerAreaSize << endl;
        cout << "Dead Area Toxicity "  << deadAreaToxicity << endl;
        cout << "Danger Area Toxicity "  << dangerAreaToxicity << endl;
        cout << "Starting Position " << startingPosition << endl;
        cout << "End Position " << endPosition << endl;
        cout << "Red Threshold " << redThreshold << endl;
        cout << "Green Threshold " << greenThreshold << endl;
    }
    stringstream MapDetailsString() {
        stringstream str;
        str << "Difficulty " << difficulty << endl;
        str << "Level " << level << endl;
        str << "Time Needed to Solve Map " << timeNeededToSolveMap << endl;
        str << "Width " << width << endl;
        str << "Height " << height << endl;
        str << "Offset Edge " << offsetEdge << endl;
        str << "Tile Size " << tileSize << endl;
        str << "Number Of Clouds " << numberOfClouds << endl;
        str << "Smoothing Value " << smoothingValue << endl;
        str << "Growth Loops " << growthLoops << endl;
        str << "Seed Value " << seedValue << endl;
        str << "Use Random Seed " << useRandomSeed << endl;
        str << "Danger Area Size "  << dangerAreaSize << endl;
        str << "Dead Area Toxicity "  << deadAreaToxicity << endl;
        str << "Danger Area Toxicity "  << dangerAreaToxicity << endl;
        str << "Starting Position " << startingPosition << endl;
        str << "End Position " << endPosition << endl;
        str << "Red Threshold " << redThreshold << endl;
        str << "Green Threshold " << greenThreshold << endl;
        return str;
    }
};

#endif /* MapHelpers_h */
