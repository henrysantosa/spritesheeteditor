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
    std::unique_ptr<SpriteSheet::BoxAttributeWidget> boxAttributeWidget;
    std::unique_ptr<SpriteSheet::AnimationDrawerWindow> animationDrawerWindow;

    SpriteSheet::Frame frame; // TODO make multi frame implementation
    QImage image;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
