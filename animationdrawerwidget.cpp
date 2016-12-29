#include "animationdrawerwidget.h"

AnimationDrawerWidget::AnimationDrawerWidget(SpriteSheet::Frame& model)
   : frame(model)
{
   setWindowTitle(tr("Animation Drawer"));
}

AnimationDrawerWidget::AnimationDrawerWidget(SpriteSheet::Frame& model, QWidget *parent)
   : frame(model)
   , QWidget(parent)
{
   setWindowTitle(tr("Animation Drawer"));
}

void AnimationDrawerWidget::paintEvent(QPaintEvent*)
{
   const SpriteSheet::Box* curFrame = frame.getBox(curFrameGuid);

   if(curFrame != nullptr)
   {
      QPainter painter(this);

      QPixmap curImage = frame.getImage();
      painter.drawPixmap(0, 0, curFrame->boxRect->rect().width(), curFrame->boxRect->rect().height(),
                         curImage,
                         curFrame->boxRect->rect().x(),
                         curFrame->boxRect->rect().y(),
                         curFrame->boxRect->rect().width(),
                         curFrame->boxRect->rect().height());


//      QTimer::singleShot(curFrame->getFrameLenInMs(), this, SLOT(update()));
      // curFrameGuid = curFrame->getNextFrameGuid();
   }
   else
   {
      QPainter painter(this);
      painter.setPen(Qt::blue);
      painter.setFont(QFont("Arial", 30));
      painter.drawText(rect(), Qt::AlignCenter, "Qt2");
      QTimer::singleShot(1000, this, SLOT(update()));
   }
}
