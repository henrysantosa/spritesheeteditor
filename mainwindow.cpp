#include "mainwindow.h"

#include <exception>

MainWindow::MainWindow()
    : sheet()
{
   setWindowTitle(tr("Spritesheet Editor"));

   QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
   QAction *openAct = fileMenu->addAction(tr("&Open..."), this, &MainWindow::open);
   openAct->setShortcut(QKeySequence::Open);

   setMinimumHeight(720);
   setMinimumWidth(1280);
   show();
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
   static bool firstDialog = true;

   if (firstDialog) {
      firstDialog = false;
      const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
      dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
   }

   QStringList mimeTypeFilters;
   const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
       ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
   foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
      mimeTypeFilters.append(mimeTypeName);
   mimeTypeFilters.sort();
   dialog.setMimeTypeFilters(mimeTypeFilters);
   dialog.selectMimeTypeFilter("image/png");
   if (acceptMode == QFileDialog::AcceptSave)
      dialog.setDefaultSuffix("png");
}

void MainWindow::open()
{
   QFileDialog dialog(this, tr("Open File"));
   initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

   while (dialog.exec() == QDialog::Accepted && !init(dialog.selectedFiles().first())) {}
}

bool MainWindow::init(QString imagePath)
{
   auto imagePathStdString = imagePath.toStdString();
   if (!std::experimental::filesystem::exists(imagePathStdString))
   {
      return false;
   }

   sheet.setImagePath(imagePathStdString);

   auto pixMap = loadImage(imagePathStdString);
   sheet.setImage(pixMap);

   sheetScene = std::make_unique<SpriteSheet::SpriteSheetScene>(sheet);
   sheetView = std::make_unique<QGraphicsView>(sheetScene.get());
   boxAttributeWidget = std::make_unique<SpriteSheet::FrameAttributeWidget>(sheet);
   animationDrawerWindow = std::make_unique<SpriteSheet::AnimationDrawerWindow>(sheet);
   frameScene = std::make_unique<SpriteSheet::FrameScene>(sheet, "0");
   frameView = std::make_unique<QGraphicsView>(frameScene.get());

   setupSignalsAndSlots();

   setCentralWidget(sheetView.get());

   boxAttributeWidget->show();
   animationDrawerWindow->show();
   frameView->show();

   return true;
}

void MainWindow::setupSignalsAndSlots()
{
   QObject::connect(boxAttributeWidget.get(), &SpriteSheet::FrameAttributeWidget::frameSwitched,
                    animationDrawerWindow.get(), &SpriteSheet::AnimationDrawerWindow::switchFrame);

   QObject::connect(&sheet, &SpriteSheet::Sheet::frameAdded,
                    boxAttributeWidget.get(), &SpriteSheet::FrameAttributeWidget::addNewFrame);

   QObject::connect(&sheet, &SpriteSheet::Sheet::frameRemoved,
                    sheetScene.get(), &SpriteSheet::SpriteSheetScene::removeFrame);
}

void MainWindow::closeEvent(QCloseEvent*)
{
   if(boxAttributeWidget != nullptr)
   {
      boxAttributeWidget->close();
   }

   if(animationDrawerWindow != nullptr)
   {
      animationDrawerWindow->close();
   }

   if(frameView != nullptr)
   {
      frameView->close();
   }

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
