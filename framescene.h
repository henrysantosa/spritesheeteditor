#pragma once

#include "spritesheetmodel.h"

#include <string>
#include <QObject>
#include <QGraphicsScene>

namespace SpriteSheet
{

class FrameScene : public QGraphicsScene
{
   Q_OBJECT

public:
   FrameScene(SpriteSheet::Sheet& sheet, const std::string& id);
   virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
public slots:
    void switchFrame(const SpriteSheet::Frame& frame);
    void switchFrame(const std::string& id);
    void switchBoxTypeMode(const Box::BoxType& boxTypeMode);
private:
   Sheet& sheet;
   std::string curId;
   QGraphicsPixmapItem* framePixmapItem;
   float scale;
private:
   void setScale(qreal scale);
   Qt::GlobalColor getColor(Box::BoxType type);

   Box::BoxType boxTypeMode;
};

}
