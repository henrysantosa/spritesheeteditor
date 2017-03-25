#include "spritesheetscene.h"

using namespace SpriteSheet;

SpriteSheetScene::SpriteSheetScene(SpriteSheet::Sheet& sheet)
   : sheet(sheet)
   , scale(1.0)
{
   scenePixmapItem = addPixmap(sheet.getImage());

   QPen outlinePen(Qt::red);
   for(auto it = sheet.frames.begin(); it != sheet.frames.end(); it++)
   {
      it->second->boxRect = addRect(it->second->sRect.x,
                                    it->second->sRect.y,
                                    it->second->sRect.width,
                                    it->second->sRect.height, outlinePen);
   }
}

void SpriteSheetScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   auto downPos = event->buttonDownScenePos(event->button());
   auto upPos   = event->scenePos();

   auto width = abs(upPos.x() - downPos.x()) / scale;
   auto height = abs(upPos.y() - downPos.y()) / scale;

   auto x = std::min(upPos.x(), downPos.x()) / scale;
   auto y = std::min(upPos.y(), downPos.y()) / scale;

   QPen outlinePen(Qt::red);

   if(width == 0 || height == 0)
    return;

   auto rectangle = addRect(x, y, width, height, outlinePen);
   rectangle->setScale(scale);

//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
//    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
//    rectangle->setFlag(QGraphicsItem::ItemIsFocusable);

   sheet.addNewFrame(std::to_string(sheet.getSize()), *rectangle);

   event->accept();
}

void SpriteSheetScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
   auto numDegrees = event->delta();

   if(numDegrees > 0)
   {
      scale += 0.1;
   }
   else
   {
      scale -= 0.1;
   }

   setScale(scale);
}

void SpriteSheetScene::setScale(qreal scale)
{
   scenePixmapItem->setScale(scale);

   for(const auto& framePair : sheet.frames)
   {
      const auto& frame = framePair.second;

      if(frame != nullptr && frame->boxRect != nullptr)
         frame->boxRect->setScale(scale);
   }
}

void SpriteSheetScene::removeFrame(SpriteSheet::Frame &frame)
{
   removeItem(frame.boxRect);
}
