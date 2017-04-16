#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "boxattributewidget.h"
#include "animationdrawerwidget.h"
#include "animationdrawerwindow.h"

#include <experimental/filesystem>

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow();
   ~MainWindow() = default;

private:
   void setupSignalsAndSlots();
   void open();
   bool init(QString imagePath);
   QPixmap loadImage(const std::experimental::filesystem::path& filePath);

   std::unique_ptr<SpriteSheet::SpriteSheetScene> scene;
   std::unique_ptr<QGraphicsView> graphicsView;
   std::unique_ptr<SpriteSheet::BoxAttributeWidget> boxAttributeWidget;
   std::unique_ptr<SpriteSheet::AnimationDrawerWindow> animationDrawerWindow;

   SpriteSheet::Sheet sheet;
   QImage image;

protected:
   void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
