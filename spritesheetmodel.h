#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QVector>
#include <QGraphicsRectItem>
#include <QPixmap>

#include <memory>
#include <experimental/filesystem>

namespace SpriteSheet
{
   struct SerializedRectangle
   {
      int x;
      int y;
      int width;
      int height;
   };

   class Frame
   {
      public:
         Frame(std::string guid, QGraphicsRectItem* boxRect, SerializedRectangle sRect);

         std::string guid;
         int xOffset;
         int yOffset;
         QGraphicsRectItem* boxRect;
         SerializedRectangle sRect;

         int getFrameLen() const;
         void setFrameLen(int numOfFrames);
         int getFrameLenInMs() const;
         const std::string& getGuid() const;
         void setGuid(const std::string& guid);
         const std::string& getNextFrameGuid() const;
         void setNextFrameGuid(const std::string& guid);

      private:
         int frameLen;
         std::string nextFrameGuid;
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
