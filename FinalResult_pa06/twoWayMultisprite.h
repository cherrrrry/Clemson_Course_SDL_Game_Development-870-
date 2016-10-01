#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class twoWayMultiSprite : public Drawable {
public:
  twoWayMultiSprite(const std::string&, const std::vector<Frame*>&);
  twoWayMultiSprite(const std::string&);//
  virtual ~twoWayMultiSprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;
  bool directionRight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  twoWayMultiSprite(const twoWayMultiSprite&);
  twoWayMultiSprite& operator=(const twoWayMultiSprite&);
};
#endif
