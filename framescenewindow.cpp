#include "framescenewindow.h"

namespace SpriteSheet
{

FrameSceneWindow::FrameSceneWindow(Sheet& sheet, QWidget *parent)
   : sheet(sheet)
   , QWidget(parent)
{
   frameSceneAttributeWidget = std::make_unique<FrameSceneAttributeWidget>(sheet);
   frameScene = std::make_unique<FrameScene>(sheet, "0");

   frameView = std::make_unique<QGraphicsView>(frameScene.get());
   frameView->setDragMode(QGraphicsView::RubberBandDrag);

   QGroupBox *sceneGroup = new QGroupBox(tr("Frame"));
   QHBoxLayout* sceneLayout = new QHBoxLayout();
   sceneLayout->addWidget(frameView.get());
   sceneGroup->setLayout(sceneLayout);

   QGroupBox *sceneControlGroup = new QGroupBox(tr("Attribute"));
   QHBoxLayout* sceneControlLayout = new QHBoxLayout();
   sceneControlLayout->addWidget(frameSceneAttributeWidget.get());
   sceneControlGroup->setLayout(sceneControlLayout);

   QHBoxLayout *layout = new QHBoxLayout;
   layout->addWidget(sceneGroup);
   layout->addWidget(sceneControlGroup);
   setLayout(layout);

   QObject::connect(frameSceneAttributeWidget.get(), &FrameSceneAttributeWidget::switchBoxType,
                    frameScene.get(), &FrameScene::switchBoxTypeMode);
}

void FrameSceneWindow::switchFrame(std::string frameGuid)
{
   frameScene->switchFrame(frameGuid);
}

}
