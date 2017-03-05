#include "spritesheetscene.h"

using namespace SpriteSheet;

SpriteSheetScene::SpriteSheetScene(SpriteSheet::Sheet& sheet)
   : sheet(sheet)
{
   addPixmap(sheet.getImage());

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

   auto width = abs(upPos.x() - downPos.x());
   auto height = abs(upPos.y() - downPos.y());

   auto x = std::min(upPos.x(), downPos.x());
   auto y = std::min(upPos.y(), downPos.y());

   QPen outlinePen(Qt::red);

   if(width == 0 || height == 0)
    return;

   auto rectangle = addRect(x, y, width, height, outlinePen);

//    rectangle->setFlag(QGraphicsItem::ItemIsMovable);
//    rectangle->setFlag(QGraphicsItem::ItemIsSelectable);
//    rectangle->setFlag(QGraphicsItem::ItemIsFocusable);

   sheet.addNewFrame(std::to_string(sheet.getSize()), *rectangle);
}

void SpriteSheetScene::removeFrame(SpriteSheet::Frame &frame)
{
   removeItem(frame.boxRect);
}
