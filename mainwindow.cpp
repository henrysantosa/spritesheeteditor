#include "mainwindow.h"

const std::string imageName = "C:\\Dev\\test.png";

MainWindow::MainWindow()
    : sheet(imageName)
{
   auto pixMap = loadImage(imageName);
   sheet.setImage(pixMap);

   scene = std::make_unique<SpriteSheet::SpriteSheetScene>(sheet);
   scene->loadImage(pixMap);

   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(sheet);
   animationDrawerWindow = std::make_unique<SpriteSheet::AnimationDrawerWindow>(sheet);

   setupSignalsAndSlots();

   setCentralWidget(graphicsView.get());
   setWindowTitle(tr("Spritesheet Editor"));
}

void MainWindow::setupSignalsAndSlots()
{
   QObject::connect(&sheet, &SpriteSheet::Sheet::frameAdded,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::addNewFrame);

   QObject::connect(&sheet, &SpriteSheet::Sheet::frameRemoved,
                    scene.get(), &SpriteSheet::SpriteSheetScene::removeFrame);
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
