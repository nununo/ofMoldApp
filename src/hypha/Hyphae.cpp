//
//  Hyphae.cpp
//  moldApp
//
//  Created by Nuno on 26/01/2019.
//

#include "Hyphae.h"
#include "InkColor.h"

Hyphae::Hyphae(const HyphaeSettings settings, float radius) {
  this->settings = settings;
  this->radius = radius;
  this->newPrimalHyphaFramesPeriod = ofGetFrameRate() * settings.newPrimalHyphaPeriod;
  this->primalHyphaCount = 0;
  this->sterile = false;
}

void Hyphae::add(Hypha *hypha) {
  ofAddListener(hypha->forkEvent, this, &Hyphae::onHyphaFork);
  ofAddListener(hypha->dieEvent, this, &Hyphae::onHyphaDie);
  elements.push_back(*hypha);
}

void Hyphae::generatePrimalHyphas() {
  if (primalHyphaCount < settings.primalHyphaCount &&
      (newPrimalHyphaFramesPeriod == 0 || ofGetFrameNum() % newPrimalHyphaFramesPeriod == 0)) {
    float angle = ofRandom(0,360);
    ofVec3f dir = ofVec3f(1,0,0).rotate(0,0,angle);
    ofVec2f pos = ofVec2f(settings.creationAreaSize*ofRandom(0,1)).getRotated(ofRandom(0,360));
    add(new Hypha(pos, dir, this->radius, settings.hypha));
    primalHyphaCount++;
  }
}

void Hyphae::removeAllDeadHypha() {
  for(auto itr = elements.begin(); itr != elements.end(); ++itr ) {
    if (!itr->isAlive()) {
      ofRemoveListener(itr->forkEvent, this, &Hyphae::onHyphaFork);
      ofRemoveListener(itr->dieEvent, this, &Hyphae::onHyphaDie);
      itr = elements.erase(itr);
    } else {
      itr->update();
    }
  }
}

void Hyphae::sterilizeIfFull() {
  if (elements.size() >= settings.maxHyphaCount) {
    sterile = true;
  }
}

void Hyphae::onHyphaFork(HyphaForkEventArgs &e) {
  if (!sterile) {
    add(new Hypha(e.pos, e.dir, radius, settings.hypha, e.generation));
  }
}

void Hyphae::onHyphaDie(HyphaDieEventArgs &e) {
  ofNotifyEvent(this->hyphaDieEvent, e);
}

void Hyphae::update() {
  sterilizeIfFull();
  removeAllDeadHypha();
  generatePrimalHyphas();
}

void Hyphae::draw() {
  for(auto &itr: elements) {
    itr.draw();
  }
}
