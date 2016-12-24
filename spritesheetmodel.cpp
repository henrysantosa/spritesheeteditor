#include "spritesheetmodel.h"

using namespace SpriteSheet;

Box::Box(std::string guid, QGraphicsRectItem& boxRect)
   : guid(guid)
   , boxRect(&boxRect)
{
}

Frame::Frame()
   : boxes()
   , size(0)
{

}

void Frame::addNewBox(std::string& guid, QGraphicsRectItem& boxRect)
{
   boxes[guid] = std::make_unique<Box>(guid, boxRect);
   ++size;
   emit boxAdded(*boxes[guid]);
}

void Frame::removeBox(const std::string& guid)
{
   emit boxRemoved(*boxes[guid]);
   boxes.erase(guid);
//   --size; // don't want to overwrite until we figure out how to get GUIDs working
}

int Frame::getSize()
{
   return size;
}

SpriteSheetModel::SpriteSheetModel()
   : frames()
   , size(0)
{
}

void SpriteSheetModel::serialize()
{
   //TODO: Implement
}

void SpriteSheetModel::addNewFrame(Frame& frame)
{
   frames.emplace_back(&frame);
}

int SpriteSheetModel::getSize()
{
   return size;
}
