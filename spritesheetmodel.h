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
   class Frame
   {
      public:
         Frame(std::string guid, QGraphicsRectItem& boxRect);
         ~Frame() = default;

         std::string guid;
         int xOffset;
         int yOffset;
         QGraphicsRectItem* boxRect;

         void setFrameLen(int numOfFrames);
         int getFrameLen() const;
         int getFrameLenInMs() const;
         void setNextFrameGuid(const std::string& guid);
         const std::string& getNextFrameGuid() const;

      private:
         Frame() = delete;
         int frameLen;
         std::string nextFrameGuid;
   };

   class Sheet : public QObject
   {
      Q_OBJECT

      public:
         Sheet(std::experimental::filesystem::path sourceImageName);
         Sheet() = delete;
         ~Sheet() = default;

         std::map<std::string, std::unique_ptr<Frame>> frames;

         const Frame* const getFrame(std::string guid) const;
         void removeFrame(const std::string& guid);
         int getSize() const;
         void deserialize(std::experimental::filesystem::path filePath);
         void serialize();
         void setImage(QPixmap pixmap);
         const QPixmap& getImage() const;

      public slots:
         void addNewFrame(std::string& guid, QGraphicsRectItem& boxRect);

      signals:
         void frameAdded(Frame& frame);
         void frameRemoved(Frame& frame);

      private:
         int size;
         QPixmap image;
         std::experimental::filesystem::path sourceImageName;
         std::experimental::filesystem::path serializedFile;
   };

}

#endif // SPRITESHEETMODEL_H
