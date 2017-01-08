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
         AnimationDrawerWidget(SpriteSheet::Frame& frame);

         void paintEvent(QPaintEvent*) override;
         std::string curFrameGuid;

      signals:

      public slots:
         void changeCurFrameGuid(const QString &text);
         void nextFrame();
         void startStopAnimation();

      private:
         SpriteSheet::Frame& frame;
         bool continueAnimation;
   };

}
#endif // ANIMATIONDRAWERWIDGET_H
