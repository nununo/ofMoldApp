//
//  Hypha.cpp
//  moldApp
//
//  Created by Nuno on 26/01/2019.
//

#include "Hypha.h"
#include "Tools.h"

#define OFFSET_MAX 1000

Hypha::Hypha(const ofVec2f pos, const ofVec2f dir, Border *border, const HyphaParams params, const int generation) {
  this->pos = pos;
  this->params = params;
  this->border = border;
  this->vel = getInitialVelocity(dir);
  this->generation = generation;
  this->deathRadius = calcDeathRadius();
  
  this->forkCount = 0;
  this->noiseOffset = ofVec2f(ofRandom(OFFSET_MAX), ofRandom(OFFSET_MAX));
  calcNextForkDistance();
}

float Hypha::calcDeathRadius() const {
  float angle = Tools::posToAngle(vel);
  return border->getRadius(angle) * ofRandom(1, 1+params.radiusTolerance/100.0f);
}

void Hypha::die() {
  dead = true;
}

ofVec3f Hypha::getInitialVelocity(ofVec2f dir) const {
   return dir.getNormalized() *
          ofRandom(params.speed*(1-params.speedVariation/100.0f),
                   params.speed*(1+params.speedVariation/100.0f)) *
          border->getRatio(Tools::posToAngle(dir));
}

void Hypha::updateDirection() {
  float bendAngle = 2*(ofNoise(pos.x+noiseOffset.x,
                        pos.y+noiseOffset.y)-0.5f)*params.maxBendAngle;
  vel.rotate(bendAngle, ofVec3f(0,0,1));
}

void Hypha::calcNextForkDistance() {
  float length = pos.length();
  this->nextForkDistance = 1+(int)(ofRandom(length,length*1.1)+0.5f);
}

void Hypha::fork() {
  throwForkEvent();
  this->forkCount++;
  calcNextForkDistance();
}

void Hypha::throwForkEvent() {
  HyphaForkEventArgs e;
  e.generation = this->generation + 1;
  e.pos = this->pos;
  float angle = ofRandom(-params.maxForkAngle, params.maxForkAngle);
  e.dir = this->vel.getRotated(angle, ofVec3f(0,0,1));
  ofNotifyEvent(this->forkEvent, e);
}

void Hypha::update() {
  if (isAlive()) {
    pos += vel;
    if (pos.length() > deathRadius) {
      die();
    } else {
      ofVec2f newIntPos = ofVec3f((int)(pos.x+0.5f),
                                  (int)(pos.y+0.5f));
      if (newIntPos != lastIntPos) {
        posIsNewPixel = true;
        updateDirection();
        lastIntPos = newIntPos;
        if (--nextForkDistance==0) {
          fork();
        }
      }
    }
  }
}

void Hypha::draw() {
  if (isAlive() && posIsNewPixel) {
    ofDrawRectangle(this->pos.x, this->pos.y, 1, 1);
    posIsNewPixel = false;
  }
}

