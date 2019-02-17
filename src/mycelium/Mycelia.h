//
//  Mycelia.h
//  moldApp
//
//  Created by Nuno on 16/02/2019.
//

#ifndef Mycelia_hpp
#define Mycelia_hpp

#include "Mycelium.h"

struct MyceliaStats {
  int myceliaCount = 0;
  int hyphaCount = 0;
  int conidiumCount = 0;
};

class Mycelia {
private:
  MyceliumSettings settings;
  std::list<Mycelium*> elements;
  
public:
  Mycelia(MyceliumSettings settings);
  ~Mycelia();

  void drawHyphae();
  void drawConidia();

  void update();
  bool isAlive() const {return true;}
  
  void add(ofVec3f pos, Ink *conidiaInk);
  MyceliaStats getStats();
};

#endif /* Mycelia_h */