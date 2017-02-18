#ifndef SPRITESHEETSCENE_H
#define SPRITESHEETSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QImageReader>

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

   public slots:
       void removeFrame(SpriteSheet::Frame& frame);

   private:
       SpriteSheet::Sheet& sheet;
       QImage image;
   };

}
#endif // SPRITESHEETSCENE_H
