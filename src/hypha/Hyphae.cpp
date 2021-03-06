//
//  Hyphae.cpp
//  hyphaeApp
//
//  Created by Nuno on 26/01/2019.
//

#include "Hyphae.h"

Hyphae::Hyphae(const HyphaeParams params, ofColor backgroundColor) {
  this->params = params;
  this->border.reset(new Border(params.border, backgroundColor));
  this->painter.reset(new Painter(params.maxHyphaCount, params.hypha.color));
  this->startFrameNum = ofGetFrameNum();
}

void Hyphae::add(ofVec2f pos, float angle, int generation) {
  if (!sterile && !dying) {
    wasAlive = true;
    elements.push_back(Hypha(pos, angle, border.get(), params.hypha, generation));
    ofAddListener(elements.back().forkEvent, this, &Hyphae::onHyphaFork);
    ofAddListener(elements.back().outsideEvent, this, &Hyphae::onHyphaOutside);
  }
}

void Hyphae::removeAllHypha() {
  for(auto itr = elements.begin(); itr != elements.end(); ++itr ) {
    ofRemoveListener(itr->forkEvent, this, &Hyphae::onHyphaFork);
    ofRemoveListener(itr->outsideEvent, this, &Hyphae::onHyphaOutside);
    itr = elements.erase(itr);
  }
}

void Hyphae::generatePrimalHyphas() {
  if (sterile || dying) {
    return; // If maximum possible hypha count reached, don't create more primal hypha
  }
  if (primalHyphaCount < params.primalHyphaCount &&
      (params.newPrimalHyphaFramesPeriod == 0 ||
       ofGetFrameNum() % params.newPrimalHyphaFramesPeriod == 0)) {
    float angle = ofRandom(0,360);
    ofVec2f pos = ofVec2f(params.creationAreaSize*ofRandom(0,1)).getRotated(ofRandom(0,360));
    add(pos, angle, 0);
    primalHyphaCount++;
  }
}

void Hyphae::updateLifecycle() {
  // Iterate through all Hypha and update if alive or remove if dead
  painter->reset();
  for(auto itr = elements.begin(); itr != elements.end(); ++itr ) {
    if (itr->isAlive()) {
      itr->update();
      if (itr->isNewPixel()) {
        painter->set(itr->getPosition());
        itr->resetNewPixel();
      }
    } else {
      ofRemoveListener(itr->forkEvent, this, &Hyphae::onHyphaFork);
      ofRemoveListener(itr->outsideEvent, this, &Hyphae::onHyphaOutside);
      itr = elements.erase(itr);
    }
  }
  // If maximum hypha reached become sterile
  if (elements.size() >= params.maxHyphaCount) {
    sterile = true;
  }
  // If dying and only X% left alive, delete all (reduce time without noticeable evolution)
  if (dying && elements.size() < dyingCount*params.euthanasiaPercentage) {
    removeAllHypha();
  }
}

void Hyphae::onHyphaFork(HyphaForkEventArgs &e) {
  add(e.pos, e.angle, e.generation);
}

void Hyphae::onHyphaOutside(ofEventArgs &e) {
  // When the first Hypha goes outside the border the dying process starts:
  // - Set dying = true
  // - Set all Hypha to die with a random energy left
  if (!dying) {
    if (++outsideCount > params.dyingOutsidePercentage * count()) {
      dying = true;
      dyingCount = count();
      for( auto& element : elements ) {
        element.die(ofRandom(params.dyingPixels));
      }
    }
  }
}

HyphaeStats Hyphae::getStats() const {
  HyphaeStats stats;
  stats.hyphaCount = elements.size();
  stats.primalHyphaCount = primalHyphaCount;
  stats.outsideCount = outsideCount;
  stats.startFrameNum = startFrameNum;
  return stats;
}

void Hyphae::update() {
  updateLifecycle();
  generatePrimalHyphas();
}

void Hyphae::drawBorder() const {
  ofPushMatrix();
  ofTranslate(params.position);
  border->draw();
  ofPopMatrix();
}

void Hyphae::draw() {
  ofPushMatrix();
  ofTranslate(params.position);
  ofPushStyle();
  ofSetColor(params.hypha.color);
  painter->draw();
  ofPopStyle();
  ofPopMatrix();
}
