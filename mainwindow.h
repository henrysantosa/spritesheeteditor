#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "frameattributewidget.h"
#include "animationdrawerwidget.h"
#include "animationdrawerwindow.h"
#include "framescene.h"

#include <experimental/filesystem>

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow();

private:
   void setupSignalsAndSlots();
   void open();
   bool init(QString imagePath);
   QPixmap loadImage(const std::experimental::filesystem::path& filePath);

private:
   std::unique_ptr<SpriteSheet::SpriteSheetScene> sheetScene;
   std::unique_ptr<QGraphicsView> sheetView;
   std::unique_ptr<SpriteSheet::FrameAttributeWidget> boxAttributeWidget;
   std::unique_ptr<SpriteSheet::AnimationDrawerWindow> animationDrawerWindow;
   std::unique_ptr<SpriteSheet::FrameScene> frameScene;
   std::unique_ptr<QGraphicsView> frameView; // TODO replace with window with the box attribute widget

   SpriteSheet::Sheet sheet;
   QImage image;

protected:
   void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
