#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QVector>
#include <QGraphicsRectItem>
#include <QPixmap>

#include <memory>

namespace SpriteSheet
{
   class Box
   {
      public:
         Box(std::string guid, QGraphicsRectItem& boxRect);
         ~Box() = default;

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
         Box() = delete;
         int frameLen;
         std::string nextFrameGuid;
   };

   class Frame : public QObject
   {
      Q_OBJECT

      public:
         Frame(std::string sourceImageName);
         Frame() = delete;
         ~Frame() = default;

         std::map<std::string, std::unique_ptr<Box>> boxes;

         const Box* const getBox(std::string guid) const;
         void removeBox(const std::string& guid);
         int getSize() const;
         void serialize();
         void setImage(QPixmap pixmap);
         const QPixmap& getImage() const;

      public slots:
         void addNewBox(std::string& guid, QGraphicsRectItem& boxRect);

      signals:
         void boxAdded(Box& box);
         void boxRemoved(Box& box);

      private:
         int size;
         QPixmap image;
         std::string sourceImageName;
   };

}

#endif // SPRITESHEETMODEL_H
