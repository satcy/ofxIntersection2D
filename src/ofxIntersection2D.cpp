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
        
        ofVec2f vectorAC = ofVec2f( c.x - a.x, c.y - a.y );
        double dR = ( ( d.y - c.y ) * vectorAC.x - ( d.x - c.x ) * vectorAC.y ) / bundo;
        double dS = ( ( b.y - a.y ) * vectorAC.x - ( b.x - a.x ) * vectorAC.y ) / bundo;
        
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
};