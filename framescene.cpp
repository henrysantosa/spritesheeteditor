#include "framescene.h"

#include <QGraphicsSceneWheelEvent>

namespace SpriteSheet
{

FrameScene::FrameScene(SpriteSheet::Sheet& sheet, const std::string& id)
   : sheet(sheet)
   , curId(id)
   , scale(1.0f)
{
   switchFrame(id);
   addLine(-50, 0, 250, 0);
   addLine(0, -50, 0, 250);
}

void FrameScene::switchFrame(const Frame &frame)
{
   const QRectF& rect = frame.boxRect->rect();

   framePixmapItem = addPixmap(
            sheet.getImage().copy(
            rect.x(),
            rect.y(),
            rect.width(),
            rect.height()
            )
         );
}

void FrameScene::switchFrame(const std::string &id)
{
   auto selection = sheet.frames.find(id);
   if(selection != sheet.frames.end())
   {
      switchFrame(*(selection->second));
   }
}

void FrameScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
   auto numDegrees = event->delta();

   if(numDegrees > 0)
   {
      scale += 0.1f;
   }
   else
   {
      scale -= 0.1f;
   }

   setScale(scale);
   event->accept();
}

void FrameScene::setScale(qreal scale)
{
   framePixmapItem->setScale(scale);

   //TODO: scale boxes when we got them
}

}
