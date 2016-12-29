#include "mainwindow.h"

const std::string imageName = "C:\\Dev\\test.png";

MainWindow::MainWindow()
    : frame(imageName)
{
   auto pixMap = loadImage(imageName);
   frame.setImage(pixMap);

   scene = std::make_unique<SpriteSheet::SpriteSheetScene>(frame);
   scene->loadImage(pixMap);

   graphicsView = std::make_unique<QGraphicsView>(scene.get());

   hitboxList = std::make_unique<BoxListWidget>(frame);

   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(frame);

   animationDrawerWidget = std::make_unique<SpriteSheet::AnimationDrawerWidget>(frame);
   animationDrawerWidget->curFrameGuid = "0";

   setupSignalsAndSlots();

   setCentralWidget(graphicsView.get());
   setWindowTitle(tr("Spritesheet Editor"));
}

void MainWindow::setupSignalsAndSlots()
{
   QObject::connect(&frame, &SpriteSheet::Frame::boxAdded,
                    hitboxList.get(), &BoxListWidget::addToList);

   QObject::connect(&frame, &SpriteSheet::Frame::boxRemoved,
                    scene.get(), &SpriteSheet::SpriteSheetScene::removeBox);

   QObject::connect(hitboxList.get(), &BoxListWidget::itemClicked,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::setNewBox);
}

void MainWindow::render()
{
   show();
   hitboxList->show();
   boxAttributeWidget->show();
   animationDrawerWidget->show();
}

void MainWindow::closeEvent(QCloseEvent*)
{
   hitboxList->close();
   boxAttributeWidget->close();
   animationDrawerWidget->close();
   QMainWindow::close();
}

QPixmap MainWindow::loadImage(const std::string &path)
{
   QImageReader reader(tr(path.c_str()));
   reader.setAutoTransform(true);
   image = reader.read();
   return QPixmap::fromImage(image);
}
