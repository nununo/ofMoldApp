//
//  Border.h
//  hyphaeApp
//
//  Created by Nuno on 17/02/2019.
//

#ifndef Border_h
#define Border_h

#include <vector>
#include "Settings.h"
#include "HyphaeParams.h"

class Border {
private:
  BorderParams params;
  std::vector<float> radiuses;
  ofColor backgroundColor;
  bool drawn = false;
  
  void generateRadiuses();
  float calcRatioForAngle(float angle) const;
public:
  Border(const BorderParams params, ofColor backgroundColor);
  float getRatio(float angle) const;
  float getRadius(float angle) const {return getRatio(angle)*params.radius;}
  bool isOutside(ofVec2f pos) const;
  void draw();
  
};

#endif /* Border_h */
