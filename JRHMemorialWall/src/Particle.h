#pragma once

#include "ofGraphics.h"

class Particle {
public:
	float x, y;
	float xv, yv;
	float xf, yf;
    float _particleBrightnessShift;
    
	Particle(float _x = 0, float _y = 0,
		float _xv = 0, float _yv = 0) :
		x(_x), y(_y),
		xv(_xv), yv(_yv) {
            //white by default
           // color.set(255);
	}
	void updatePosition(float timeStep) {
		// f = ma, m = 1, f = a, v = int(a)
		xv += xf;
		yv += yf;
		x += xv * timeStep;
		y += yv * timeStep;
	}
    
    void updateColor(float particleBrightnessShift){
        _particleBrightnessShift = particleBrightnessShift;
    }
    
	void resetForce() {
		xf = 0;
		yf = 0;
	}
	void bounceOffWalls(float left, float top, float right, float bottom, float damping = .3) {
		bool collision = false;

		if (x > right){
			x = right;
			xv *= -1;
			collision = true;
		} else if (x < left){
			x = left;
			xv *= -1;
			collision = true;
		}

		if (y > bottom){
			y = bottom;
			yv *= -1;
			collision = true;
		} else if (y < top){
			y = top;
			yv *= -1;
			collision = true;
		}

		if (collision == true){
			xv *= damping;
			yv *= damping;
		}
	}
    
    //when particle reaches edge of particle field, loop is around to the other side
    void loopAround(float left, float top, float right, float bottom, float damping = .3) {
		//bool collision = false;
        
		if (x > right){
			x = left;
			//xv *= -1;
			//collision = true;
		} else if (x < left){
			x = right;
			//xv *= -1;
			//collision = true;
		}
        
		if (y > bottom){
			y = top;
			//yv *= -1;
			//collision = true;
		} else if (y < top){
			y = bottom;
			//yv *= -1;
			//collision = true;
		}
        
	}
    
	void addDampingForce(float damping = .01) {
		xf = xf - xv * damping;
        yf = yf - yv * damping;
	}
	void draw() {
        //set color of particle based on it's speed?
      //  ofSetColor(255-(abs(yv)*abs(xv))*10);
       // cout<<"xv: "<<xv<<" yv: "<<yv<<endl;
        //ofSetColor(xf,255,yf);
    
        float b = ofClamp(1-(abs(yv)+abs(xv))/_particleBrightnessShift, 0, 1);
       // cout<<"b: "<<b<<endl;
        glColor3f(b, b, b);
		glVertex2f(x, y);
	}
    
    void applyForce(ofVec2f f){
        xv += f.x;
        yv += f.y;
    }
    
    void stop(){
        xv = 0;
        yv = 0;
        resetForce();
    }
};
