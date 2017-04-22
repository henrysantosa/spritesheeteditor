#ifndef ANIMATIONDRAWERWINDOW_H
#define ANIMATIONDRAWERWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>

#include <memory>

#include "animationdrawerwidget.h"
#include "spritesheetmodel.h"

namespace SpriteSheet
{
class AnimationDrawerWindow : public QWidget
{
   Q_OBJECT
public:
   AnimationDrawerWindow(Sheet& model);

signals:

public slots:
   void switchFrame(std::string frameGuid);

private:
   void setupAnimationWidget(Sheet& model);
   void setupAnimationControlWidget();

private:
   std::unique_ptr<AnimationDrawerWidget> animationDrawerWidget;
   std::unique_ptr<QPushButton> startAnimationButton;
   std::unique_ptr<QLineEdit> animationGuidEdit;

   QGroupBox *animationGroup;
   QGroupBox *animationControlGroup;

};
}

#endif // ANIMATIONDRAWERWINDOW_H
