#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QImageReader>
#include <QGraphicsView>

#include <QListWidget>
#include <QListWidgetItem>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "hitboxlist.h"
#include "boxattributewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() = default;

    void render();

private:
    std::unique_ptr<SpriteSheetScene> scene;
    std::unique_ptr<QGraphicsView> graphicsView;
    std::unique_ptr<HitboxList> hitboxList;
    std::unique_ptr<SpriteSheet::BoxAttributeWidget> boxAttributeWidget;

    SpriteSheet::SpriteSheetModel spriteSheetModel;
    SpriteSheet::Frame frame; // TODO make multi frame implementation
};

#endif // MAINWINDOW_H
