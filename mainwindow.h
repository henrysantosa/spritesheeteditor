#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "boxlistwidget.h"
#include "boxattributewidget.h"

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
    std::unique_ptr<BoxListWidget> hitboxList;
    std::unique_ptr<SpriteSheet::BoxAttributeWidget> boxAttributeWidget;

    SpriteSheet::SpriteSheetModel spriteSheetModel;
    SpriteSheet::Frame frame; // TODO make multi frame implementation

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
