#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPixmap>

#include <map>
#include <vector>
#include <memory>
#include <experimental/filesystem>

#include "SpriteSheet.h"

namespace SpriteSheet
{
   struct SerializedRectangle
   {
      int x;
      int y;
      int width;
      int height;

      SerializedRectangle(int x, int y, int width, int height)
         : x(x)
         , y(y)
         , width(width)
         , height(height)
      {
      }
   };

   struct Box
   {
      using BoxType = SDLBase::Serialize::Box::BoxType;

      Box(const std::string& guid, const BoxType& type, SerializedRectangle& sRect);
      Box(const std::string& guid, const BoxType& type, QGraphicsRectItem& sRect);

      std::string guid;
      QGraphicsRectItem* boxRect;
      SerializedRectangle sRect;
      BoxType type = BoxType::UNINITIALIZED;
   };

   struct Frame
   {
      Frame(std::string guid, QGraphicsRectItem* boxRect, SerializedRectangle sRect);

      std::string guid;
      int xOffset;
      int yOffset;
      int frameLen;
      QGraphicsRectItem* boxRect;
      SerializedRectangle sRect;
      std::string nextFrameGuid;

      std::vector<std::unique_ptr<Box>> boxes;

      int getFrameLenInMs() const;
      const Box& addBox(std::string& guid, Box::BoxType& type, QGraphicsRectItem& boxRect);
      Box* findBox(std::string& boxGuid);
   };

   class Sheet : public QObject
   {
      Q_OBJECT

      public:
         Sheet();
         std::map<std::string, std::unique_ptr<Frame>> frames;

        Frame* const getFrame(std::string guid) const;
        Frame* const firstFrame() const;

        void setFrameName(const std::string& oldName, const std::string& newName);

         void removeFrame(const std::string& guid);
         int getSize() const;
         void deserialize(std::experimental::filesystem::path filePath);
         void serialize();
         const QPixmap& getImage() const;
         void setImage(QPixmap pixmap);
         void setImagePath(std::experimental::filesystem::path sourceImagePath);

      public slots:
         void addNewFrame(std::string& guid, QGraphicsRectItem& boxRect);

      signals:
         void frameAdded(Frame& frame);
         void frameRemoved(Frame& frame);
         void boxAdded(Box& box);

      private:
         int size;
         QPixmap image;
         std::experimental::filesystem::path sourceImagePath;
         std::experimental::filesystem::path serializedFile;
   };

}

#endif // SPRITESHEETMODEL_H
