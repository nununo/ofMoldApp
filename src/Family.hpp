//
//  Spot.hpp
//  moldApp
//
//  Created by Nuno on 08/01/2019.
//

#ifndef Family_hpp
#define Family_hpp

#include <list>
#include "ofMain.h"
#include "Element.hpp"
#include "IDrawable.h"
#include "Perimeter.hpp"

class Family : public IDrawable {

private:
  ofVec2f pos;
  std::list<Element> elements;
  ofFbo fbo;
  float radius;
  float growthSpeed;
  int lifespan;
  float elementDistance;
  int elementLifespan;
  float lastElementRadius;
  DistortedCircle dc;
  Perimeter per360;
  
  bool drawDC = false;

  void addElement(ofVec3f pos);
  float getElementAngleDistance(float r);
  void grow();
  void createElements();
  void destroyDeadElements();
  void updateFBO();

public:
  Family(ofVec3f pos, int size, float growthSpeed, int lifespan, int elementLifespan, float elementDistance);
  ~Family();

  // IDrawable
  void update();
  void draw();
  float getWidth() {return fbo.getWidth();}
  float getHeight() {return fbo.getHeight();}
  bool isAlive() {return this->lifespan > 0;}
};

#endif /* Family_hpp */
