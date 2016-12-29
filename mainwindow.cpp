#include "mainwindow.h"

const std::string imageName = "C:\\Dev\\test.png";

MainWindow::MainWindow()
    : frame(imageName)
{
   scene = std::make_unique<SpriteSheetScene>(frame);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());

   auto pixMap = loadImage(imageName);
   scene->loadImage(pixMap);
   frame.setImage(pixMap);

   hitboxList = std::make_unique<BoxListWidget>(frame);

   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(frame);

   animationDrawerWidget = std::make_unique<AnimationDrawerWidget>(frame);
   animationDrawerWidget->curFrameGuid = "0";

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
