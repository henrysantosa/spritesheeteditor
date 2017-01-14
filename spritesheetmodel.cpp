#include "spritesheetmodel.h"

using namespace SpriteSheet;

const float MS_PER_FRAME = 1000.0f/60.0f;

Frame::Frame(std::string guid, QGraphicsRectItem& boxRect)
   : guid(guid)
   , boxRect(&boxRect)
   , xOffset(0)
   , yOffset(0)
   , frameLen(0)
{
}

void Frame::setFrameLen(int numOfFrames)
{
   frameLen = numOfFrames;
}

int Frame::getFrameLen() const
{
   return frameLen;
}

int Frame::getFrameLenInMs() const
{
   return static_cast<int>(frameLen * MS_PER_FRAME);
}

void Frame::setNextFrameGuid(const std::string& guid)
{
   nextFrameGuid = guid;
}

const std::string& Frame::getNextFrameGuid() const
{
   return nextFrameGuid;
}

Sheet::Sheet(std::string sourceImageName)
   : frames()
   , size(0)
   , sourceImageName(sourceImageName)
{
}

const Frame* const Sheet::getFrame(std::string guid) const
{
   auto it = frames.find(guid);
   if(it == frames.end())
      return nullptr;
   else
      return it->second.get();
}

void Sheet::addNewFrame(std::string& guid, QGraphicsRectItem& boxRect)
{
   frames[guid] = std::make_unique<Frame>(guid, boxRect);

   // this is how you move a rect
   //frames["0"]->boxRect->setRect(100 + size*10, 100, 100, 100);

   ++size;
   emit frameAdded(*frames[guid]);
}

void Sheet::removeFrame(const std::string& guid)
{
   emit frameRemoved(*frames[guid]);
   frames.erase(guid);
//   --size; // don't want to overwrite until we figure out how to get GUIDs working
}

int Sheet::getSize() const
{
   return size;
}

void Sheet::setImage(QPixmap pixmap)
{
   image = pixmap;
}

const QPixmap& Sheet::getImage() const
{
   return image;
}


void Sheet::serialize()
{
   //TODO Implement
}
