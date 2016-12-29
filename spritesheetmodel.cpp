#include "spritesheetmodel.h"

using namespace SpriteSheet;

const float SEC_IN_FRAME = 1/60;

Box::Box(std::string guid, QGraphicsRectItem& boxRect)
   : guid(guid)
   , boxRect(&boxRect)
{
}

const Box* const Frame::getBox(std::string guid) const
{
   auto it = boxes.find(guid);
   if(it == boxes.end())
      return nullptr;
   else
      return it->second.get();
}

void Box::setFrameLen(int numOfFrames)
{
   frameLen = numOfFrames;
}

int Box::getFrameLen() const
{
   return frameLen;
}

int Box::getFrameLenInMs() const
{
   return static_cast<int>(frameLen * SEC_IN_FRAME);
}

void Box::setNextFrameGuid(const std::string& guid)
{
   nextFrameGuid = guid;
}

const std::string& Box::getNextFrameGuid() const
{
   return nextFrameGuid;
}

Frame::Frame(std::string sourceImageName)
   : boxes()
   , size(0)
   , sourceImageName(sourceImageName)
{
}

void Frame::addNewBox(std::string& guid, QGraphicsRectItem& boxRect)
{
   boxes[guid] = std::make_unique<Box>(guid, boxRect);

   // this is how you move a rect
   //boxes["0"]->boxRect->setRect(100 + size*10, 100, 100, 100);

   ++size;
   emit boxAdded(*boxes[guid]);
}

void Frame::removeBox(const std::string& guid)
{
   emit boxRemoved(*boxes[guid]);
   boxes.erase(guid);
//   --size; // don't want to overwrite until we figure out how to get GUIDs working
}

int Frame::getSize() const
{
   return size;
}

void Frame::setImage(QPixmap pixmap)
{
   image = pixmap;
}

const QPixmap& Frame::getImage() const
{
   return image;
}
