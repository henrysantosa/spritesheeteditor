#include "mainwindow.h"

#include <exception>

std::experimental::filesystem::path imagePath(R"(C:\Dev\test.png)");
std::string serializedFile = imagePath.filename().string() + "_spritesheet";

MainWindow::MainWindow()
    : sheet(imagePath)
{
   auto pixMap = loadImage(imagePath);
   sheet.setImage(pixMap);

   scene = std::make_unique<SpriteSheet::SpriteSheetScene>(sheet);

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

QPixmap MainWindow::loadImage(const std::experimental::filesystem::path& filePath)
{
   if(!std::experimental::filesystem::exists(filePath))
   {
      throw new std::exception("Unable to open file.");
   }

   QImageReader reader(tr(filePath.string().c_str()));
   reader.setAutoTransform(true);
   image = reader.read();
   return QPixmap::fromImage(image);
}
