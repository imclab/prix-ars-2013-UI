#include "ofMain.h"


class ofxArsUIButton
{
protected:
    int status,bcnt,speed,tcnt; //status 0: not selected, 1:selected, 2: broken 
    ofImage mark,markShadow;
    float x,y,radius;
    int bid;
    ofPoint fuji;
    double directionToFuji; //radian
    double currentDirection;
    double calcDirection(ofPoint *_p1, ofPoint *_p2);
    double viewAngle;
    double latitude;
    double longtitude;
    
public:
	ofxArsUIButton(float _x, float _y, int _bid, ofPoint _fuji, float _angle );
	virtual void draw();
	virtual void update();
	virtual int tapped(float _x, float _y);
    void setAngle(float _angle);
    void setStatus(int _status);
    int getStatus();
    int getId();
    void setCameraStatus(double _lat, double _lon);
    ofPoint GPStoXY(double _lat,double _lon);
};