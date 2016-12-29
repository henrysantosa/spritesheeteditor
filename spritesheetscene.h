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
       SpriteSheetScene(SpriteSheet::Frame& frame);
       void loadImage(QPixmap& pixmap);
       virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

   public slots:
       void removeBox(SpriteSheet::Box& box);

   private:
       SpriteSheet::Frame& frame;
       QImage image;
   };

}
#endif // SPRITESHEETSCENE_H
