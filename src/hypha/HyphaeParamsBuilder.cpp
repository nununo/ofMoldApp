//
//  HyphaeParamsBuilderParamsBuilder.cpp
//  moldApp
//
//  Created by Nuno on 19/02/2019.
//

#include "HyphaeParamsBuilder.h"
#include "Tools.h"

HyphaeParams HyphaeParamsBuilder::create(const Settings &settings) {
  HyphaeParams params;
  HyphaeSettings hyphaeSettings = settings.hyphae;
  params.seed = (int)ofRandom(999999);
  ofSeedRandom(params.seed);

  params.position = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
  params.creationAreaSize = Tools::randomInRange(hyphaeSettings.creationAreaSize);
  params.maxHyphaCount = (int)Tools::randomInSet(hyphaeSettings.maxHyphaCount);
  params.primalHyphaCount = (int)Tools::randomInSet(hyphaeSettings.primalHyphaCount);
  params.newPrimalHyphaFramesPeriod = settings.canvas.framerate * Tools::randomInRange(hyphaeSettings.newPrimalHyphaPeriod);
  params.dyingFrames = settings.canvas.framerate * hyphaeSettings.dyingTime;

  params.border.noiseOffset = ofRandom(99999);
  params.border.distortion = Tools::randomInRange(hyphaeSettings.border.distortion);
  params.border.radius = Tools::randomInRange(hyphaeSettings.border.radius);
  params.border.ratioVariation = hyphaeSettings.border.ratioVariation;

  params.hypha.color = hyphaeSettings.hypha.color;
  params.hypha.noiseOffset = ofVec2f(ofRandom(99999), ofRandom(99999));
  params.hypha.speed = Tools::randomInRange(hyphaeSettings.hypha.speed);
  params.hypha.speedVariation = Tools::randomInRange(hyphaeSettings.hypha.speedVariation);
  params.hypha.maxForkAngle = Tools::randomInRange(hyphaeSettings.hypha.maxForkAngle);
  params.hypha.maxBendAngle = Tools::randomInRange(hyphaeSettings.hypha.maxBendAngle);
  params.hypha.maxBentAngle = Tools::randomInRange(hyphaeSettings.hypha.maxBentAngle);
  params.hypha.pixelOverlap = Tools::randomInRange(hyphaeSettings.hypha.pixelOverlap);

  return params;
}
