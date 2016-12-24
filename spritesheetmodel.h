#ifndef SPRITESHEETMODEL_H
#define SPRITESHEETMODEL_H

#include <QObject>
#include <QVector>
#include <QGraphicsRectItem>

#include <memory>

namespace SpriteSheet
{
   struct Box
   {
      Box(std::string guid, QGraphicsRectItem& boxRect);
      ~Box() = default;
      std::string guid;
      QGraphicsRectItem* boxRect;
   };

   class Frame : public QObject
   {
      Q_OBJECT

      std::map<std::string, std::unique_ptr<Box>> boxes;

      public:
         Frame();
         ~Frame() = default;

         void removeBox(const std::string& guid);
         int getSize();

      public slots:
         void addNewBox(std::string& guid, QGraphicsRectItem& boxRect);

      signals:
         void boxAdded(Box& box);
         void boxRemoved(Box& box);

      private:
         int size;
   };

   class SpriteSheetModel : public QObject
   {
      Q_OBJECT

   public:
      SpriteSheetModel();
      ~SpriteSheetModel() = default;

      void serialize();
      int getSize();

      void addNewFrame(Frame& frame);

   private:
      int size;
      std::vector<Frame*> frames;
   };

}

#endif // SPRITESHEETMODEL_H
