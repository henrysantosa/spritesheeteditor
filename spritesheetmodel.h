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

   };

   struct Box
   {
      using BoxType = SDLBase::Serialize::Box::BoxType;

      Box(BoxType type, SerializedRectangle sRect);

      SerializedRectangle rect;
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

      int getFrameLenInMs() const;

      std::vector<std::unique_ptr<Box>> boxes;
   };

   class Sheet : public QObject
   {
      Q_OBJECT

      public:
         Sheet();
         std::map<std::string, std::unique_ptr<Frame>> frames;

         const Frame* const getFrame(std::string guid) const;
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

      private:
         int size;
         QPixmap image;
         std::experimental::filesystem::path sourceImagePath;
         std::experimental::filesystem::path serializedFile;
   };

}

#endif // SPRITESHEETMODEL_H
