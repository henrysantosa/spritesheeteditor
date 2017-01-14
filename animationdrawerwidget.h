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
         AnimationDrawerWidget(SpriteSheet::Sheet& sheet);

         void paintEvent(QPaintEvent*) override;
         std::string curFrameGuid;

      signals:

      public slots:
         void changeCurFrameGuid(const QString &text);
         void nextFrame();
         void startStopAnimation();

      private:
         SpriteSheet::Sheet& sheet;
         bool continueAnimation;
   };

}
#endif // ANIMATIONDRAWERWIDGET_H
