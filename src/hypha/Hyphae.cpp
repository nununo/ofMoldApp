//
//  Hyphae.cpp
//  moldApp
//
//  Created by Nuno on 26/01/2019.
//

#include "Hyphae.h"

Hyphae::Hyphae(const HyphaeParams params) {
  this->params = params;
  this->border.reset(new Border(params.border));
}

Hyphae::~Hyphae() {
  removeAllHypha();
}

void Hyphae::add(ofVec2f pos, ofVec2f dir, int generation) {
  if (!sterile && !dying) {
    wasAlive = true;
    elements.push_back(Hypha(pos, dir, border.get(), params.hypha, generation));
    ofAddListener(elements.back().forkEvent, this, &Hyphae::onHyphaFork);
  }
}

void Hyphae::generatePrimalHyphas() {
  if (sterile || dying) {
    return; // If maximum possible hypha count reached, don't create more primal hypha
  }
  if (primalHyphaCount < params.primalHyphaCount &&
      (params.newPrimalHyphaFramesPeriod == 0 ||
       ofGetFrameNum() % params.newPrimalHyphaFramesPeriod == 0)) {
    ofVec2f dir = ofVec2f(1,0).getRotated(ofRandom(0,360));
    ofVec2f pos = ofVec2f(params.creationAreaSize*ofRandom(0,1)).getRotated(ofRandom(0,360));
    add(pos, dir, 0);
    primalHyphaCount++;
  }
}

void Hyphae::removeAllHypha() {
  for(auto itr = elements.begin(); itr != elements.end(); ++itr ) {
    ofRemoveListener(itr->forkEvent, this, &Hyphae::onHyphaFork);
    itr = elements.erase(itr);
  }
}

void Hyphae::updateLifecycle() {
  for(auto itr = elements.begin(); itr != elements.end(); ++itr ) {
    if (itr->isAlive()) {
      itr->update();
    } else {
      ofRemoveListener(itr->forkEvent, this, &Hyphae::onHyphaFork);
      itr = elements.erase(itr);
    }
  }
  if (elements.size() >= params.maxHyphaCount) {
    sterile = true;
  }
}

void Hyphae::onHyphaFork(HyphaForkEventArgs &e) {
  add(e.pos, e.dir, e.generation);
}

HyphaeStats Hyphae::getStats() const {
  HyphaeStats stats;
  stats.hyphaCount = elements.size();
  stats.primalHyphaCount = this->primalHyphaCount;
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
  for(auto &itr: elements) {
    itr.draw();
  }
  ofPopStyle();
  ofPopMatrix();
}
