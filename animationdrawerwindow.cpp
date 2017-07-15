#include "animationdrawerwindow.h"

#include <QBoxLayout>
#include <QFormLayout>
#include <QLabel>

namespace SpriteSheet
{

AnimationDrawerWindow::AnimationDrawerWindow(Sheet& model)
{
   setupAnimationControlWidget();
   setupAnimationWidget(model);

   QObject::connect(startAnimationButton.get(), &QPushButton::released,
                    animationDrawerWidget.get(), &SpriteSheet::AnimationDrawerWidget::startStopAnimation);
   QObject::connect(animationGuidEdit.get(), &QLineEdit::textChanged,
                    animationDrawerWidget.get(), &SpriteSheet::AnimationDrawerWidget::changeCurFrameGuid);

   QHBoxLayout *layout = new QHBoxLayout;
   layout->addWidget(animationGroup);
   layout->addWidget(animationControlGroup);
   setLayout(layout);

   setWindowTitle(tr("Animation"));

   setMinimumHeight(500);
   setMinimumWidth(500);
}

void AnimationDrawerWindow::setupAnimationControlWidget()
{
   animationControlGroup = new QGroupBox(tr("Control"));
   QFormLayout* controlLayout = new QFormLayout();

   QLabel *guidLabel = new QLabel(tr("GUID:"));
   controlLayout->addWidget(guidLabel);
   animationGuidEdit = std::make_unique<QLineEdit>(this);
   controlLayout->addWidget(animationGuidEdit.get());

   startAnimationButton = std::make_unique<QPushButton>("Start/Stop", this);
   controlLayout->addWidget(startAnimationButton.get());

   animationControlGroup->setLayout(controlLayout);
   animationControlGroup->setMaximumWidth(150);
}

void AnimationDrawerWindow::setupAnimationWidget(Sheet& model)
{
   animationGroup = new QGroupBox(tr("Animation"));
   QHBoxLayout* animationLayout = new QHBoxLayout();

   std::string firstFrameName("");
   if(model.getSize() > 0)
   {
      firstFrameName = model.firstFrame()->guid;
   }

   animationDrawerWidget = std::make_unique<AnimationDrawerWidget>(model, firstFrameName);

   animationLayout->addWidget(animationDrawerWidget.get());
   animationGroup->setLayout(animationLayout);
}

void AnimationDrawerWindow::switchFrame(std::string frameGuid)
{
   animationDrawerWidget->changeCurFrameGuid(tr(frameGuid.c_str()));
}

}
