//
//  ofxIntersection2D.h
//  Entrance
//
//  Created by satcy on 2016/11/14.
//
//

#pragma once
#include "ofMain.h"

namespace ofxIntersection2D {
    float signedTriangle(ofVec2f & a, ofVec2f & b, ofVec2f & c);
    bool crossLine(ofVec2f & a, ofVec2f & b, ofVec2f & c, ofVec2f & d);
    ofVec2f crossLinePoint(ofVec2f & a, ofVec2f & b, ofVec2f & c, ofVec2f & d);
    ofVec3f mirror(ofVec3f p, ofVec3f a, ofVec3f b);
    double distancePointToLine(const ofVec2f & p, const ofVec2f & a, const ofVec2f & b);
    vector<ofVec3f> getTriangleCircumscribedCircle(const ofVec2f & center, float radius, float start_radian, float wide_radian, float rate);
};