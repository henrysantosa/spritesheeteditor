#pragma once

#include <string>
#include <unordered_map>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/unordered_map.hpp>

namespace SDLBase
{
   namespace Serialize
   {
      struct Frame
      {
         int x;
         int y;
         int width;
         int height;
         int xOffset;
         int yOffset;
         int frameLenMs;
         std::string guid;
         std::string nextFrameGuid;
      };

      using FrameMap = std::unordered_map<std::string, Frame>;

      class SpriteSheet
      {
      public:
         FrameMap frameMap;
         std::string fileName;
      };
   }
}

namespace boost
{
   namespace serialization
   {
      template<class Archive>
      void serialize(Archive & ar, SDLBase::Serialize::SpriteSheet & am, const unsigned int)
      {
         ar & am.frameMap;
         ar & am.fileName;
      }

      template<class Archive>
      void serialize(Archive & ar, SDLBase::Serialize::Frame & f, const unsigned int)
      {
         ar & f.x;
         ar & f.y;
         ar & f.width;
         ar & f.height;
         ar & f.xOffset;
         ar & f.yOffset;
         ar & f.frameLenMs;
         ar & f.guid;
         ar & f.nextFrameGuid;
      }
   }// serialization
}// boost
