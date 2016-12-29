#ifndef ANIMATIONDRAWERWIDGET_H
#define ANIMATIONDRAWERWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QTimer>

#include "spritesheetmodel.h"

namespace SpriteSheet
{
   class AnimationDrawerWidget : public QWidget
   {
      Q_OBJECT

      public:
         explicit AnimationDrawerWidget(SpriteSheet::Frame& model, QWidget *parent);
         AnimationDrawerWidget(SpriteSheet::Frame& frame);

         void paintEvent(QPaintEvent*) override;
         std::string curFrameGuid;

      signals:

      public slots:

      private:
         SpriteSheet::Frame& frame;
   };

}
#endif // ANIMATIONDRAWERWIDGET_H
