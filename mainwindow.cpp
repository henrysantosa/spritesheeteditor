#include "mainwindow.h"
#include <memory>
#include <QListWidgetItem>

MainWindow::MainWindow()
    : spriteSheetModel()
    , frame()
{
   scene = std::make_unique<SpriteSheetScene>(frame);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   scene->loadImage("C:\\Dev\\test.png");

   hitboxList = std::make_unique<HitboxList>(frame);

   QObject::connect(&frame, &SpriteSheet::Frame::boxAdded,
                    hitboxList.get(), &HitboxList::addToList);

   QObject::connect(&frame, &SpriteSheet::Frame::boxRemoved,
                    scene.get(), &SpriteSheetScene::removeBox);
}

void MainWindow::render()
{
   graphicsView->show();
   hitboxList->show();
}
