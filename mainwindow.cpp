#include "mainwindow.h"
#include <memory>
#include <QListWidgetItem>

MainWindow::MainWindow()
    : spriteSheetModel()
{
   scene = std::make_unique<SpriteSheetScene>(spriteSheetModel);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   scene->loadImage("C:\\Dev\\test.png");

   hitboxList = std::make_unique<HitboxList>(spriteSheetModel);
   hitboxList->updateList();

   QObject::connect(&spriteSheetModel, &SpriteSheetModel::hitboxAdded,
                    hitboxList.get(), &HitboxList::updateList);
}

void MainWindow::render()
{
   graphicsView->show();
   hitboxList->show();
}
