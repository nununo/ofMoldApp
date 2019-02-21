#pragma once

#include "ofMain.h"
#include "Settings.h"
#include "Mycelium.h"

class ofApp : public ofBaseApp{

private:
  Settings *settings;
  Mycelium *mycelium;

  void drawOSD();
  void newMycelium();

public:
  ~ofApp();
  void setup();
  void update();
  void draw();

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
