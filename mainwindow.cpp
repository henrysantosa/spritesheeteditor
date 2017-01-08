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
   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(frame);
   animationDrawerWindow = std::make_unique<SpriteSheet::AnimationDrawerWindow>(frame);

   setupSignalsAndSlots();

   setCentralWidget(graphicsView.get());
   setWindowTitle(tr("Spritesheet Editor"));
}

void MainWindow::setupSignalsAndSlots()
{
   QObject::connect(&frame, &SpriteSheet::Frame::boxAdded,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::addNewFrame);

   QObject::connect(&frame, &SpriteSheet::Frame::boxRemoved,
                    scene.get(), &SpriteSheet::SpriteSheetScene::removeBox);
}

void MainWindow::render()
{
   show();
   boxAttributeWidget->show();
   animationDrawerWindow->show();
}

void MainWindow::closeEvent(QCloseEvent*)
{
   boxAttributeWidget->close();
   animationDrawerWindow->close();
   QMainWindow::close();
}

QPixmap MainWindow::loadImage(const std::string &path)
{
   QImageReader reader(tr(path.c_str()));
   reader.setAutoTransform(true);
   image = reader.read();
   return QPixmap::fromImage(image);
}
