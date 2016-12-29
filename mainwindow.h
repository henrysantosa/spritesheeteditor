#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include <memory>

#include "spritesheetmodel.h"
#include "spritesheetscene.h"
#include "boxlistwidget.h"
#include "boxattributewidget.h"
#include "animationdrawerwidget.h"

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
    MainWindow();
    ~MainWindow() = default;

    void render();
    QPixmap loadImage(const std::string& path);

private:
    void setupSignalsAndSlots();

    std::unique_ptr<SpriteSheet::SpriteSheetScene> scene;
    std::unique_ptr<QGraphicsView> graphicsView;
    std::unique_ptr<BoxListWidget> hitboxList;
    std::unique_ptr<SpriteSheet::BoxAttributeWidget> boxAttributeWidget;
    std::unique_ptr<SpriteSheet::AnimationDrawerWidget> animationDrawerWidget;

    SpriteSheet::Frame frame; // TODO make multi frame implementation
    QImage image;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
