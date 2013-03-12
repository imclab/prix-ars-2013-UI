#include "ArsUIRoboCam.h"

ArsUIRoboCam::ArsUIRoboCam(float _x, float _y, int _bid, ofPoint _fuji,float _angle):ArsUIButton(_x,_y,_bid,_fuji,_angle){
    ArsUIButton::mark.loadImage("markyellow.png");
}

void ArsUIRoboCam::update(){
    ArsUIButton::update();
}

void ArsUIRoboCam::draw(){
    //status: 0:default 1:select
    
    ofColor c;
    ofColor c0(200,200,200,250);
    ofColor c1(255,255,255,250);
    ofColor c3(100,100,100,250);
    int times = 3.5;
    int lineLength = 100;
    
    float distanceToFuji = sqrt((x-fuji.x)*(x-fuji.x) + (y-fuji.y)*(y-fuji.y));
    distanceToFuji +=100;
    ofPath path;
    path.setCurveResolution(60);
    path.setColor( ofColor(255, 255, 0,40));
    path.moveTo(x,y);
    float angle1 = 360 -( 360 * currentDirection/(PI*2) + viewAngle/2) ;
    float angle2 = 360 - (360 * currentDirection/(PI*2) - viewAngle/2) ;
    path.arc(x,y,distanceToFuji,distanceToFuji,angle1,angle2);
    
    
    if(status ==0){
        c = c0;
    }else if (status == 1){
        c = c1;
        radius *= 1.5;
        lineLength =200;
        path.draw();
    }
    
    ofSetColor(255, 255, 255,200);
    ofLine(x, y, x + cos(currentDirection) *lineLength  ,y - sin(currentDirection)*lineLength);
     //ofDrawBitmapString(ofToString(bid), x,y+50);
    
    ofSetColor(c);
    //ofCircle(x, y, radius);
    ofPushMatrix();
    ofTranslate(x, y, 0);
    ofRotateZ((bcnt/2)%360);
    markShadow.draw( - radius/2 ,  - radius /2 -2 ,radius, radius);
    mark.draw( - radius/2 +2,  - radius /2 ,radius, radius);
    
    if(status ==1){
      ofSetColor(c3);
      mark.draw( - radius*times/2  ,  - radius*times/2  ,radius*times, radius*times);
    }
    
    ofSetColor(255, 255, 255, 255);
    ofPopMatrix();
     if(status ==1){
      ofSetColor(50, 50, 50,200);
      ofCircle(x + cos(currentDirection) * times * radius /2.7  , y - sin(currentDirection) * times *radius /2.7, times *radius / 12);
     }
    ofSetColor(255, 255, 255);


}

int ArsUIRoboCam::tapped(float _x, float _y){
   int _bid = ArsUIButton::tapped(_x,_y);
    if (_bid != -1 && status ==1){
        setDefaultAngle();
    }
    return _bid;
}

void ArsUIRoboCam::dragAngle(float _x, float _y){
    if(status == 1){
        float distance = sqrt((x - _x) * (x - _x) + (y - _y) *(y - _y) );
        if (distance  > radius && distance < radius *1.5) {
            ofPoint p1 = ofPoint(x,y);
            ofPoint p2 = ofPoint(_x,_y);
            float newAngle = ArsUIButton::calcDirection(&p1,&p2);
        //    if(newAngle < directionToFuji + 0.8 && newAngle > directionToFuji - 0.8 ){
                currentDirection = newAngle;
          //  }
        }
    }
}

bool ArsUIRoboCam::dragAngleEnded (float _x, float _y){
    if(status == 1){
        float distance = sqrt((x - _x) * (x - _x) + (y - _y) *(y - _y) );
        if (distance  > radius && distance < radius *1.5) {
            return true;
            
        }
    }
    return false;
}

void ArsUIRoboCam::setDefaultAngle(){
    currentDirection = directionToFuji;
}

void ArsUIRoboCam::setRoboStatus(string _udid, double _lat, double _long, double _robox, double _roboy, double _buttery, bool _living){
    udid = _udid;
    latitude = _lat;
    longtitude = _long;
    xpos = _robox;
    ypos = _roboy;
    buttery = _buttery;
    living = _living;
    ofPoint p = GPStoXY(latitude, longtitude);
    x = p.x;
    y = p.y;
}

