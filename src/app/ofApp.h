#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "Hyphae.h"
#include "HyphaeParamsBuilder.h"
#include "OSD.h"
#include "Steps.h"

class ofApp : public ofBaseApp{

private:
  unique_ptr<Settings> settings;
  unique_ptr<OSD> osd;
  unique_ptr<Steps> steps;

  int mourningFrames = 0;
  int fadeoutFrames = 0;
  int fadeoutFramesPeriod = 0;
  bool paused = false;
  
  void clearScreen();

public:
  void setup();
  void update();
  void draw();
  
  void togglePaused() {paused=!paused;}

  void keyPressed(int key);
  void keyReleased(int key) {}
  void mouseMoved(int x, int y ) {}
  void mouseDragged(int x, int y, int button) {}
  void mousePressed(int x, int y, int button) {}
  void mouseReleased(int x, int y, int button) {}
  void mouseEntered(int x, int y) {}
  void mouseExited(int x, int y) {}
  void windowResized(int w, int h) {}
  void dragEvent(ofDragInfo dragInfo) {}
  void gotMessage(ofMessage msg) {}
};
