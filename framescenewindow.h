#pragma once

#include <QWidget>
#include <memory>
#include "framescene.h"
#include "framesceneattributewidget.h"
#include "spritesheetmodel.h"

namespace SpriteSheet
{

class FrameSceneWindow : public QWidget
{
   Q_OBJECT
public:
   explicit FrameSceneWindow(Sheet& sheet, QWidget *parent = 0);

signals:

public slots:
   void switchFrame(std::string frameGuid);

private:
   std::unique_ptr<FrameSceneAttributeWidget> frameSceneAttributeWidget;
   std::unique_ptr<FrameScene> frameScene;

   std::unique_ptr<QGraphicsView> frameView;

   Sheet& sheet;
};

}
