#include "mainwindow.h"

MainWindow::MainWindow()
    : spriteSheetModel()
    , frame()
{
   scene = std::make_unique<SpriteSheetScene>(frame);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   scene->loadImage("C:\\Dev\\test.png");

   hitboxList = std::make_unique<BoxListWidget>(frame);

   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(frame);

   QObject::connect(&frame, &SpriteSheet::Frame::boxAdded,
                    hitboxList.get(), &BoxListWidget::addToList);

   QObject::connect(&frame, &SpriteSheet::Frame::boxRemoved,
                    scene.get(), &SpriteSheetScene::removeBox);

   QObject::connect(hitboxList.get(), &BoxListWidget::itemClicked,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::setNewBox);

   setCentralWidget(graphicsView.get());

   setWindowTitle(tr("Spritesheet Editor"));
}

void MainWindow::render()
{
   show();
   hitboxList->show();
   boxAttributeWidget->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   hitboxList->close();
   boxAttributeWidget->close();
   QMainWindow::close();
}
