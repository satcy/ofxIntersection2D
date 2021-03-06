//
//  ofxIntersection2D.h
//  Entrance
//
//  Created by satcy on 2016/11/14.
//
//

#include "ofxIntersection2D.h"

namespace ofxIntersection2D {
    float signedTriangle(ofVec2f & a, ofVec2f & b, ofVec2f & c){// 時計周りならマイナス
        return (a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x);
    }
    
    bool crossLine(ofVec2f & a, ofVec2f & b, ofVec2f & c, ofVec2f & d){//交差判定
        
        double a1 = signedTriangle(a, b, d);
        double a2 = signedTriangle(a, b, c);
        
        if(!(a1 * a2 < 0.0)) return false;
        
        double a3 = signedTriangle(c, d, a);
        double a4 = signedTriangle(c, d, b);
        
        if(a3 * a4 < 0.0){
            return true;
        }
        
        return false;
    }
    
    ofVec2f crossLinePoint(ofVec2f & a, ofVec2f & b, ofVec2f & c, ofVec2f & d){//交差座標
        double bundo = ( b.x - a.x ) * ( d.y - c.y ) - ( b.y - a.y ) * ( d.x - c.x );
        if ( bundo == 0 ) {// heikou
            return ofVec2f();
        }
        double vectorAC_x = c.x - a.x;
        double vectorAC_y = c.y - a.y;
        
        double dR = ( ( d.y - c.y ) * vectorAC_x - ( d.x - c.x ) * vectorAC_y ) / bundo;
        double dS = ( ( b.y - a.y ) * vectorAC_x - ( b.x - a.x ) * vectorAC_y ) / bundo;
        
        return ofVec2f( a.x + dR * ( b.x - a.x ), a.y + dR * ( b.y - a.y ));
    }
    
    ofVec3f mirror(ofVec3f p, ofVec3f a, ofVec3f b) {
        double Angle,Slope,Hx,Hy,B;
        double Tx,Ty;
        
        Angle = atan(double(b.y-a.y)/double(b.x-a.x));
        //Angle *= (M_PI)/180.0;
        
        Slope = tan(Angle);
        B = b.y - b.x*Slope;
        
        Hx = -B*sin(2.0 * Angle);
        Hy = B*(cos(2.0 * Angle)+1.0);
        
        Tx = p.x;
        Ty = p.y;
        ofVec3f p1;
        p1.x = Tx*cos(2.0*Angle)
        + Ty*sin(2.0*Angle) + Hx;
        
        p1.y = Tx*sin(2.0*Angle)
        - Ty*cos(2.0*Angle) + Hy;
        return p1;
    }
    
    double distancePointToLine(const ofVec2f & p, const ofVec2f & a, const ofVec2f & b){
        ofVec2f v0 = b - a;
        ofVec2f v1 = p - a;
        
        double area = v1.x * v0.y - v1.y * v0.x;
        return area / hypot(v0.x, v0.y);
    }
    
    vector<ofVec3f> getTriangleCircumscribedCircle(const ofVec2f & center, float radius, float start_radian, float wide_radian, float rate) {
        float r1 = start_radian;
        float r2 = start_radian + ofClamp(wide_radian * rate, 0.1, PI-0.1);
        wide_radian = ofClamp(wide_radian, PI+0.1, r2-r1+PI-0.1);
        float r3 = start_radian + wide_radian;
        
        ofVec2f p1 = ofVec2f(cos(r1)*radius + center.x, sin(r1)*radius + center.y);
        ofVec2f p2 = ofVec2f(cos(r2)*radius + center.x, sin(r2)*radius + center.y);
        ofVec2f p3 = ofVec2f(cos(r3)*radius + center.x, sin(r3)*radius + center.y);
        const static float NEEDLE = 0xffffff;
        ofVec2f v1_1 = ofVec2f( cos(r1 + PI*0.5)*NEEDLE + p1.x, sin(r1 + PI*0.5)*NEEDLE + p1.y );
        ofVec2f v1_2 = ofVec2f( cos(r1 - PI*0.5)*NEEDLE + p1.x, sin(r1 - PI*0.5)*NEEDLE + p1.y );
        
        ofVec2f v2_1 = ofVec2f( cos(r2 + PI*0.5)*NEEDLE + p2.x, sin(r2 + PI*0.5)*NEEDLE + p2.y );
        ofVec2f v2_2 = ofVec2f( cos(r2 - PI*0.5)*NEEDLE + p2.x, sin(r2 - PI*0.5)*NEEDLE + p2.y );
        
        ofVec2f v3_1 = ofVec2f( cos(r3 + PI*0.5)*NEEDLE + p3.x, sin(r3 + PI*0.5)*NEEDLE + p3.y );
        ofVec2f v3_2 = ofVec2f( cos(r3 - PI*0.5)*NEEDLE + p3.x, sin(r3 - PI*0.5)*NEEDLE + p3.y );
        
        
        ofVec2f c1 = crossLinePoint(v1_1, v1_2, v2_1, v2_2);
        ofVec2f c2 = crossLinePoint(v1_1, v1_2, v3_1, v3_2);
        ofVec2f c3 = crossLinePoint(v3_1, v3_2, v2_1, v2_2);
        
        vector<ofVec3f> arr;
        arr.emplace_back(c1);
        arr.emplace_back(c2);
        arr.emplace_back(c3);
        
        return arr;
    }
};
