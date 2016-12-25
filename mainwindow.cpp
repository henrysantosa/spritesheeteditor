#include "mainwindow.h"


MainWindow::MainWindow()
    : spriteSheetModel()
    , frame()
{
   scene = std::make_unique<SpriteSheetScene>(frame);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   scene->loadImage("C:\\Dev\\test.png");

   hitboxList = std::make_unique<HitboxList>(frame);

   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(frame);

   QObject::connect(&frame, &SpriteSheet::Frame::boxAdded,
                    hitboxList.get(), &HitboxList::addToList);

   QObject::connect(&frame, &SpriteSheet::Frame::boxRemoved,
                    scene.get(), &SpriteSheetScene::removeBox);

   QObject::connect(hitboxList.get(), &HitboxList::itemClicked,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::setNewBox);
}

void MainWindow::render()
{
   graphicsView->show();
   hitboxList->show();
   boxAttributeWidget->show();
}
