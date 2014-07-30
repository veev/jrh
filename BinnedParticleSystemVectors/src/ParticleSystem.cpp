#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() :
timeStep(1) {
}

void ParticleSystem::setup(int width, int height, int k) {
    this->width = width;
    this->height = height;
    this->k = k;
    binSize = 1 << k;
    xBins = (int) ceilf((float) width / (float) binSize);
    yBins = (int) ceilf((float) height / (float) binSize);
    bins.resize(xBins * yBins);
}

void ParticleSystem::setTimeStep(float timeStep) {
    this->timeStep = timeStep;
}

void ParticleSystem::add(Particle particle) {
    particles.push_back(particle);
}

unsigned ParticleSystem::size() const {
    return particles.size();
}

Particle& ParticleSystem::operator[](unsigned i) {
    return particles[i];
}

vector<Particle*> ParticleSystem::getNeighbors(Particle& particle, float radius) {
    return getNeighbors(particle.loc, radius);
}

vector<Particle*> ParticleSystem::getNeighbors(ofVec2f location, float radius) {
    vector<Particle*> region = getRegion(
                                         (int) (location.x - radius),
                                         (int) (location.y - radius),
                                         (int) (location.x + radius),
                                         (int) (location.y + radius));
    vector<Particle*> neighbors;
    int n = region.size();
    float xd, yd, rsq, maxrsq;
    maxrsq = radius * radius;
    for(int i = 0; i < n; i++) {
        Particle& cur = *region[i];
        xd = cur.loc.x - location.x;
        yd = cur.loc.y - location.y;
        rsq = xd * xd + yd * yd;
        if(rsq < maxrsq)
            neighbors.push_back(region[i]);
    }
    return neighbors;
}

vector<Particle*> ParticleSystem::getRegion(unsigned minX, unsigned minY, unsigned maxX, unsigned maxY) {
    vector<Particle*> region;
    back_insert_iterator< vector<Particle*> > back = back_inserter(region);
    unsigned minXBin = minX >> k;
    unsigned maxXBin = maxX >> k;
    unsigned minYBin = minY >> k;
    unsigned maxYBin = maxY >> k;
    maxXBin++;
    maxYBin++;
    if(maxXBin > xBins)
        maxXBin = xBins;
    if(maxYBin > yBins)
        maxYBin = yBins;
    for(int y = minYBin; y < maxYBin; y++) {
        for(int x = minXBin; x < maxXBin; x++) {
            vector<Particle*>& cur = bins[y * xBins + x];
            copy(cur.begin(), cur.end(), back);
        }
    }
    return region;
}

void ParticleSystem::setupForces() {
    int n = bins.size();
    for(int i = 0; i < n; i++) {
        bins[i].clear();
    }
    n = particles.size();
    unsigned xBin, yBin, bin;
    for(int i = 0; i < n; i++) {
        Particle& cur = particles[i];
        cur.resetForce();
        xBin = ((unsigned) cur.loc.x) >> k;
        yBin = ((unsigned) cur.loc.y) >> k;
        bin = yBin * xBins + xBin;
        if(xBin < xBins && yBin < yBins)
            bins[bin].push_back(&cur);
    }
}

void ParticleSystem::addRepulsionForce(const Particle& particle, float radius, float scale) {
    addRepulsionForce(particle.loc, radius, scale);
}

void ParticleSystem::addRepulsionForce(ofVec2f location, float radius, float scale) {
    addForce(location, radius, scale);
}

void ParticleSystem::addAttractionForce(const Particle& particle, float radius, float scale) {
    addAttractionForce(particle.loc, radius, scale);
}

void ParticleSystem::addAttractionForce(ofVec2f location, float radius, float scale) {
    addForce(location, radius, -scale);
}

void ParticleSystem::addForce(const Particle& particle, float radius, float scale) {
    addForce(particle.loc, radius, -scale);
}

void ParticleSystem::returnToOrigin(const Particle& particle, float radius, float scale) {
    addForce(particle.origin, radius, scale);
}

void ParticleSystem::returnToOrigin(ofVec2f origin, float radius, float scale) {
    addForce(origin, radius, scale);
}

void ParticleSystem::addForce(ofVec2f targetLoc, float radius, float scale) {
    float minX = targetLoc.x - radius;
    float minY = targetLoc.y - radius;
    float maxX = targetLoc.x + radius;
    float maxY = targetLoc.y + radius;
    if(minX < 0)
        minX = 0;
    if(minY < 0)
        minY = 0;
    unsigned minXBin = ((unsigned) minX) >> k;
    unsigned minYBin = ((unsigned) minY) >> k;
    unsigned maxXBin = ((unsigned) maxX) >> k;
    unsigned maxYBin = ((unsigned) maxY) >> k;
    maxXBin++;
    maxYBin++;
    if(maxXBin > xBins)
        maxXBin = xBins;
    if(maxYBin > yBins)
        maxYBin = yBins;
    float xd, yd, length, maxrsq;
#ifdef USE_INVSQRT
    float xhalf;
    int lengthi;
#else
    float effect;
#endif
    maxrsq = radius * radius;
    for(int y = minYBin; y < maxYBin; y++) {
        for(int x = minXBin; x < maxXBin; x++) {
            vector<Particle*>& curBin = bins[y * xBins + x];
            int n = curBin.size();
            for(int i = 0; i < n; i++) {
                Particle& curParticle = *(curBin[i]);
                xd = curParticle.loc.x - targetLoc.x;
                yd = curParticle.loc.y - targetLoc.y;
                length = xd * xd + yd * yd;
                if(length > 0 && length < maxrsq) {
#ifdef DRAW_FORCES
                    glVertex2f(targetLoc.x, targetLoc.y);
                    glVertex2f(curParticle.loc.x, curParticle.loc.y);
#endif
#ifdef USE_INVSQRT
                    xhalf = 0.5f * length;
                    lengthi = *(int*) &length;
                    lengthi = 0x5f3759df - (lengthi >> 1);
                    length = *(float*) &lengthi;
                    length *= 1.5f - xhalf * length * length;
                    xd *= length;
                    yd *= length;
                    length *= radius;
                    length = 1 / length;
                    length = (1 - length);
                    length *= scale;
                    xd *= length;
                    yd *= length;
                    curParticle.acc.x += xd;
                    curParticle.acc.y += yd;
#else
                    length = sqrtf(length);
                    xd /= length;
                    yd /= length;
                    effect = (1 - (length / radius)) * scale;
                    curParticle.acc.x += xd * effect;
                    curParticle.acc.y += yd * effect;
#endif
                }
            }
        }
    }
}

void ParticleSystem::update() {
    int n = particles.size();
    for(int i = 0; i < n; i++)
        particles[i].updatePosition(timeStep);
}

void ParticleSystem::draw() {
    int n = particles.size();
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(1.5);
    glBegin(GL_POINTS);
    for(int i = 0; i < n; i++)
        particles[i].draw();
    glEnd();
}