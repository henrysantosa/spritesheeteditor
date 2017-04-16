#ifndef SPRITESHEETSCENE_H
#define SPRITESHEETSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImageReader>
#include <QWheelEvent>

#include <cmath>
#include <algorithm>

#include "spritesheetmodel.h"

namespace SpriteSheet
{

   class SpriteSheetScene : public QGraphicsScene
   {
   Q_OBJECT

   public:
       SpriteSheetScene(SpriteSheet::Sheet& sheet);
       virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
       virtual void wheelEvent(QGraphicsSceneWheelEvent *event) override;

   public slots:
       void removeFrame(SpriteSheet::Frame& frame);

   private:
       void setScale(qreal scale);

   private:
       SpriteSheet::Sheet& sheet;
       QImage image;
       QGraphicsPixmapItem* scenePixmapItem;
       qreal scale;
   };

}
#endif // SPRITESHEETSCENE_H
