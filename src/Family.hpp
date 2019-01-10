//
//  Spot.hpp
//  moldApp
//
//  Created by Nuno on 08/01/2019.
//

#ifndef Family_hpp
#define Family_hpp

#include "ofMain.h"
#include <list>
#include "Element.hpp"

class Family {

private:
  Ink *ink;
  ofVec2f pos;
  float size;
  std::list<Element> elements;
  ofFbo fbo;

public:
  Family(Ink *ink, ofVec2f pos, float size);
  void update();
  void draw();
};

#endif /* Family_hpp */