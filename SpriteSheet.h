#pragma once

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost/serialization/unordered_map.hpp>
#include <boost/serialization/vector.hpp>

namespace SDLBase
{
   namespace Serialize
   {
      struct Box
      {
         enum BoxType
         {
            HITBOX,
            HURTBOX,
            UNINITIALZED
         };

         Box() : type(UNINITIALZED) {};

         int x;
         int y;
         int xOffset;
         int yOffset;
         int width;
         int height;
         
         BoxType type;
      };

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

         std::vector<Box> boxes;
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
      void serialize(Archive & ar, SDLBase::Serialize::SpriteSheet & am, const unsigned int version)
      {
         ar & am.frameMap;
         ar & am.fileName;
      }

      template<class Archive>
      void serialize(Archive & ar, SDLBase::Serialize::Box & b, const unsigned int version)
      {
         if(version > 0)
         {
            ar & b.x;
            ar & b.y;
            ar & b.width;
            ar & b.height;
            ar & b.type;
         }
      }

      template<class Archive>
      void serialize(Archive & ar, SDLBase::Serialize::Frame & f, const unsigned int version)
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

         if (version > 0)
         {
            ar & f.boxes;
         }
      }

   }// serialization
}// boost

BOOST_CLASS_VERSION(SDLBase::Serialize::SpriteSheet, 1)
BOOST_CLASS_VERSION(SDLBase::Serialize::Frame, 1)
BOOST_CLASS_VERSION(SDLBase::Serialize::Box, 1)