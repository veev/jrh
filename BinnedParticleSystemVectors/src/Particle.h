#pragma once

#include "ofGraphics.h"
#include "Perlin.h"

class Particle {
public:
    
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f origin;
    ofColor col;
    
    //float x, y;
    //float xv, yv;
    //float xf, yf;
    //Particle(float _x = 0, float _y = 0, float _xv = 0, float _yv = 0) : x(_x), y(_y), xv(_xv), yv(_yv) {
    Particle(const ofPixels &pixels, ofVec2f location, ofVec2f velocity) {
        loc = location;
        vel = velocity;
        acc = ofVec2f(0,0);
        origin = location;
        
        if ( loc.x >= 0.0 && loc.x <= (float)pixels.getWidth() - 1 &&
            loc.y >= 0.0 && loc.y <= (float) pixels.getHeight() - 1 ) {
            
            col = pixels.getColor(loc.x, loc.y);
            float brightness = col.getBrightness();
            
        } else {
            col = (255, 255, 255);
        }

    }
    
    void updatePosition(float timeStep) {
        // f = ma, m = 1, f = a, v = int(a)
        
        //xv += xf;
        //yv += yf;
        //x += xv * timeStep;
        //y += yv * timeStep;
        
        vel += acc;
        vel.limit(4);
        loc += vel; //* timeStep;
        acc *= 0;
    }
    
    void resetForce() {
        //xf = 0;
        //yf = 0;
        acc.set(0);
    }
    
    void bounceOffWalls(float left, float top, float right, float bottom, float damping = .3) {
        bool collision = false;
        
        if (loc.x > right){
            loc.x = right;
            vel.x *= -1;
            collision = true;
        } else if (loc.x < left){
            loc.x = left;
            vel.x *= -1;
            collision = true;
        }
        
        if (loc.y > bottom){
            loc.y = bottom;
            vel.y *= -1;
            collision = true;
        } else if (loc.y < top){
            loc.y = top;
            vel.y *= -1;
            collision = true;
        }
        
        if (collision == true){
            //xv *= damping;
            //yv *= damping;
            vel += damping;
        }
    }
    void addDampingForce(float damping = .01) {
        //xf = xf - xv * damping;
        //yf = yf - yv * damping;
        
        acc = acc - vel * damping;
        
    }
    
    void applyPerlinForce(const Perlin &perlin, float perlinScalar) {
        float nX = loc.x * 0.005;
        float nY = loc.y * 0.005;
        float nZ = ofGetFrameNum() * 0.0025;
        float noise = perlin.fBm( nX, nY, nZ );
        float angle = noise * 15.0;
        ofVec2f noiseVector( cos( angle ), sin( angle ));
        ofVec2f perlinNoise = noiseVector * perlinScalar;
        //perlinNoise.limit(maxForce);
        //applyForce(perlinNoise);
        vel += perlinNoise;
    }
    
    void returnToOrigin(float springFactor) {
        acc.x += springFactor * (origin.x - loc.x);
        acc.y += springFactor * (origin.y - loc.y);
    }
    
    void pullToCenter() {
        ofVec2f dirToCenter = loc - ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
        vel -= dirToCenter * 0.005;
    }
    
    void pause() {
        vel *= 0.98;
    }
    
    void draw() {
        ofPushStyle();
        ofSetColor(col, 200);
        glVertex2f(loc.x, loc.y);
        //ofCircle(loc.x, loc.y, 1.0);
        ofPopStyle();
    }
};

