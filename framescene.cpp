#include "framescene.h"

#include <QGraphicsSceneWheelEvent>

namespace SpriteSheet
{

FrameScene::FrameScene(SpriteSheet::Sheet& sheet, const std::string& id)
   : sheet(sheet)
   , curId(id)
   , scale(1.0f)
   , boxTypeMode(Box::BoxType::HITBOX)
{
   switchFrame(id);
}

void FrameScene::switchFrame(const Frame &frame)
{
   const QRectF& rect = frame.boxRect->rect();

   clear();

   scale = 1.0f;
   addLine(-50, 0, 250, 0);
   addLine(0, -50, 0, 250);

   framePixmapItem = addPixmap(
            sheet.getImage().copy(
            rect.x(),
            rect.y(),
            rect.width(),
            rect.height()
            )
         );

   for(const auto& box : frame.boxes)
   {
      QPen outlinePen(getColor(box->type));

      box->boxRect = addRect(box->sRect.x,
              box->sRect.y,
              box->sRect.width,
              box->sRect.height,
              outlinePen);
   }
}

void FrameScene::switchFrame(const std::string &id)
{
   auto selection = sheet.frames.find(id);
   if(selection != sheet.frames.end())
   {
      switchFrame(*(selection->second));
      curId = selection->second->guid;
   }
}

void FrameScene::switchBoxTypeMode(const Box::BoxType &boxTypeMode)
{
   this->boxTypeMode = boxTypeMode;
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
   const Frame& curFrame = *(sheet.frames[curId]);

   for(const auto& box: curFrame.boxes)
   {
      box->boxRect->setScale(scale);
   }
}

Qt::GlobalColor FrameScene::getColor(Box::BoxType type)
{
   switch(type)
   {
   case Box::BoxType::HITBOX : return Qt::red;
   case Box::BoxType::HURTBOX : return Qt::blue;
   default : return Qt::black;
   }
}

void FrameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
   auto downPos = event->buttonDownScenePos(event->button());
   auto upPos   = event->scenePos();

   auto width = abs(upPos.x() - downPos.x()) / scale;
   auto height = abs(upPos.y() - downPos.y()) / scale;

   auto x = std::min(upPos.x(), downPos.x()) / scale;
   auto y = std::min(upPos.y(), downPos.y()) / scale;


   if(width == 0 || height == 0)
      return;

   Frame* curFrame = sheet.getFrame(curId);

   QPen outlinePen(getColor(boxTypeMode));
   QGraphicsRectItem* boxRect = addRect(x, y, width, height, outlinePen);
   boxRect->setScale(scale);

   auto newBox = curFrame->addBox(std::to_string(curFrame->boxes.size()+1), boxTypeMode, *boxRect);
   emit sheet.boxAdded(newBox);

   event->accept();
}

}
