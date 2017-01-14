#include "spritesheetscene.h"

using namespace SpriteSheet;

SpriteSheetScene::SpriteSheetScene(SpriteSheet::Sheet& sheet)
   : sheet(sheet)
{
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

void SpriteSheetScene::loadImage(QPixmap& pixmap)
{
   this->addPixmap(pixmap);
}
