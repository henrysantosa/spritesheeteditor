#include "animationdrawerwidget.h"

using namespace SpriteSheet;

AnimationDrawerWidget::AnimationDrawerWidget(SpriteSheet::Sheet& model)
   : sheet(model)
   , curFrameGuid("0")  // TODO: Make not hardcoded
   , continueAnimation(false)
{
}

void AnimationDrawerWidget::nextFrame()
{
   const SpriteSheet::Frame* curFrame = sheet.getFrame(curFrameGuid);

   if(curFrame != nullptr)
   {
      auto nextGuid = curFrame->nextFrameGuid;
      if(sheet.getFrame(curFrameGuid) != nullptr)
         curFrameGuid = nextGuid;
   }
}

void AnimationDrawerWidget::changeCurFrameGuid(const QString &text)
{
   continueAnimation = false;
   curFrameGuid = text.toStdString();
   update();
}

void AnimationDrawerWidget::startStopAnimation()
{
   update();
   continueAnimation = !continueAnimation;
}

void AnimationDrawerWidget::paintEvent(QPaintEvent*)
{
   const SpriteSheet::Frame* curFrame = sheet.getFrame(curFrameGuid);

   if(curFrame != nullptr)
   {
      QPainter painter(this);

      auto width = this->width();
      auto height = this->height();

      painter.drawLine(width/2, 0, width/2, height);
      painter.drawLine(0, height/2, width, height/2);

      const QPixmap& curImage = sheet.getImage();
      painter.drawPixmap(width/2 + curFrame->xOffset,
                         height/2 + curFrame->yOffset,
                         curFrame->boxRect->rect().width(), curFrame->boxRect->rect().height(),
                         curImage,
                         curFrame->boxRect->rect().x(),
                         curFrame->boxRect->rect().y(),
                         curFrame->boxRect->rect().width(),
                         curFrame->boxRect->rect().height());

      auto nextFrame = sheet.getFrame(curFrame->nextFrameGuid);
      if( nextFrame == nullptr )
         continueAnimation = false;
      else
         curFrameGuid = nextFrame->guid;

      if(continueAnimation)
      {
         int waitTime = curFrame->getFrameLenInMs();
         if(waitTime <= 0)
            waitTime = 1000;  // default to 1 second wait time if given an invalid wait time
         QTimer::singleShot(waitTime, this, SLOT(update()));
      }
   }
   else
   {
      QPainter painter(this);
      painter.setPen(Qt::red);
      painter.setFont(QFont("Arial", 14));
      painter.drawText(rect(), Qt::AlignCenter, "Frame Not Found: Retrying in 1 second");
   }
}
