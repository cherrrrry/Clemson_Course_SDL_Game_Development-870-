#include "scaledMultiSprite.h"
#include "gamedata.h"
#include "frameFactory.h"

void ScaledMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
		currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	  }
}
ScaledMultiSprite::ScaledMultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(rand()%Gamedata::getInstance().getXmlInt("world/width")+600, 
                    rand()%Gamedata::getInstance().getXmlInt("world/height")+100), 
           Vector2f((rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speedX")),
                    (rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"/cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")))
           ),
  scale(getRandFloat(Gamedata::getInstance().getXmlFloat(name+"/scale/min"),
                   Gamedata::getInstance().getXmlFloat(name+"/scale/max"))),
  frames(FrameFactory::getInstance().getScaledFrames(name, scale)),//
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

ScaledMultiSprite::ScaledMultiSprite( const std::string& name,const Vector2f& pos, Vector2f vel) :
  Drawable(name, pos, vel ),
  scale(getRandFloat(Gamedata::getInstance().getXmlFloat(name+"/scale/min"),
                   Gamedata::getInstance().getXmlFloat(name+"/scale/max"))),
  frames(FrameFactory::getInstance().getScaledFrames(name, scale)),//
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

/*
ScaledMultiSprite::ScaledMultiSprite( const std::string& name, 
                          const std::vector<Frame*>& f) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f((rand()%2?1:-1)*getRandom()(
                    Gamedata::getInstance().getXmlInt(name+"cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speedX")),
                    (rand()%2?1:-1)*getRandom(
                    Gamedata::getInstance().getXmlInt(name+"cushion"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY")))
           ),
  scale(getRandFloat(Gamedata::getInstance().getXmlFloat(name+"scale/min"),
                   Gamedata::getInstance().getXmlFloat(name+"scale/max"))),
  frames( f ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }*/


void ScaledMultiSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void ScaledMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
  if ( Y() < 0) {
    velocityY(abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}
