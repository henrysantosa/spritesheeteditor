#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QImage>
#include <QImageReader>
#include <QGraphicsView>

#include <QListWidget>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "hitboxlist.h"

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
    SpriteSheetModel spriteSheetModel;
};

#endif // MAINWINDOW_H
