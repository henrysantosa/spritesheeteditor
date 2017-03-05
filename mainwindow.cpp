#include "mainwindow.h"

#include <exception>

//std::experimental::filesystem::path imagePath(R"(C:\Dev\test.png)");
//std::string serializedFile = imagePath.filename().string() + "_spritesheet";

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
   dialog.selectMimeTypeFilter("image/jpeg");
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
   if (!std::experimental::filesystem::exists(serializedFile))
   {
      return false;
   }

   sheet.setImagePath(imagePath.toStdString());

   auto pixMap = loadImage(imagePath.toStdString());
   sheet.setImage(pixMap);

   scene = std::make_unique<SpriteSheet::SpriteSheetScene>(sheet);
   graphicsView = std::make_unique<QGraphicsView>(scene.get());
   boxAttributeWidget = std::make_unique<SpriteSheet::BoxAttributeWidget>(sheet);
   animationDrawerWindow = std::make_unique<SpriteSheet::AnimationDrawerWindow>(sheet);

   setupSignalsAndSlots();

   setCentralWidget(graphicsView.get());

   boxAttributeWidget->show();
   animationDrawerWindow->show();

   return true;
}

void MainWindow::setupSignalsAndSlots()
{
   QObject::connect(&sheet, &SpriteSheet::Sheet::frameAdded,
                    boxAttributeWidget.get(), &SpriteSheet::BoxAttributeWidget::addNewFrame);

   QObject::connect(&sheet, &SpriteSheet::Sheet::frameRemoved,
                    scene.get(), &SpriteSheet::SpriteSheetScene::removeFrame);
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
