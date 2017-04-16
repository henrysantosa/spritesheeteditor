#include "spritesheetmodel.h"
#include "SpriteSheet.h"

#include <iostream>
#include <fstream>
#include <exception>

using namespace SpriteSheet;

const float MS_PER_FRAME = 1000.0f/60.0f;

Frame::Frame(std::string guid, QGraphicsRectItem* boxRect, SerializedRectangle sRect = SerializedRectangle{0,0,0,0} )
   : guid(guid)
   , boxRect(boxRect)
   , xOffset(0)
   , yOffset(0)
   , frameLen(0)
   , sRect(sRect)
{
}

const std::string& Frame::getGuid() const
{
   return guid;
}

void Frame::setGuid(const std::string &guid)
{
   this->guid = guid;
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

Sheet::Sheet()
   : frames()
   , size(0)
{
}

void Sheet::setImagePath(std::experimental::filesystem::path sourceImagePath)
{
   serializedFile = sourceImagePath.filename().string() + "_spritesheet";
   deserialize(serializedFile);
   this->sourceImagePath = sourceImagePath;
}

const Frame* const Sheet::getFrame(std::string guid) const
{
   auto it = frames.find(guid);
   if(it == frames.end())
   {
      return nullptr;
   }
   else
   {
      return it->second.get();
   }
}

void Sheet::addNewFrame(std::string& guid, QGraphicsRectItem& boxRect)
{
   frames[guid] = std::make_unique<Frame>(guid, &boxRect);

   // this is how you move a rect
   //frames["0"]->boxRect->setRect(100 + size*10, 100, 100, 100);

   ++size;
   emit frameAdded(*frames[guid]);
}

void Sheet::removeFrame(const std::string& guid)
{
   emit frameRemoved(*frames[guid]);
   frames.erase(guid);

   for(const auto& framePair : frames)
   {
      if((framePair.second.get()) != nullptr)
      {
         Frame frame = *(framePair.second);
         if(frame.getNextFrameGuid() == guid)
         {
            frame.setNextFrameGuid("");
         }
      }
   }

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

void Sheet::deserialize(std::experimental::filesystem::path filePath)
{
   SDLBase::Serialize::SpriteSheet deserialized;

   try
   {
      std::ifstream ifs(filePath);
      boost::archive::text_iarchive ia(ifs);
      ia >> deserialized;
   }
   catch (std::exception& ex)
   {
      //TODO: exception handling
   }

   for(std::pair<std::string, SDLBase::Serialize::Frame> it : deserialized.frameMap)
   {
      SDLBase::Serialize::Frame curSFrame = it.second;

      auto curFrame = new Frame(it.first, nullptr, SerializedRectangle{curSFrame.x, curSFrame.y, curSFrame.width, curSFrame.height});
      curFrame->setFrameLen(curSFrame.frameLenMs);
      curFrame->setNextFrameGuid(curSFrame.nextFrameGuid);
      curFrame->xOffset = curSFrame.xOffset;
      curFrame->yOffset = curSFrame.yOffset;

      frames[it.first] = std::unique_ptr<Frame>(curFrame);
      ++size;
   }
}

void Sheet::serialize()
{
   SDLBase::Serialize::SpriteSheet spriteSheet;

   spriteSheet.fileName = sourceImagePath.filename().string();

   for(auto it = frames.begin(); it != frames.end(); it++)
   {
      std::string guid = (*it).first;
      Frame* curFrame = (*it).second.get();

      if(curFrame == nullptr)
         continue;

      SDLBase::Serialize::Frame sFrame{
         static_cast<int>(curFrame->boxRect->rect().x()),
         static_cast<int>(curFrame->boxRect->rect().y()),
         static_cast<int>(curFrame->boxRect->rect().width()),
         static_cast<int>(curFrame->boxRect->rect().height()),
         curFrame->xOffset,
         curFrame->yOffset,
         curFrame->getFrameLen(),
         curFrame->guid,
         curFrame->getNextFrameGuid()
      };

      spriteSheet.frameMap[guid] = sFrame;
   }

   std::ofstream ofs(serializedFile);
   {
      boost::archive::text_oarchive oa(ofs);
      oa << spriteSheet;
   }
}
