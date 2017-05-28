#pragma once

#include <QWidget>

#include <QtWidgets>
#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <QGroupBox>

#include "spritesheetmodel.h"

namespace SpriteSheet
{

class FrameSceneAttributeWidget : public QWidget
{
   Q_OBJECT
public:
   explicit FrameSceneAttributeWidget(SpriteSheet::Sheet& sheet, QWidget *parent = 0);

private:
   SpriteSheet::Sheet& sheet;

   std::unique_ptr<QComboBox> curBoxComboBox;
   std::unique_ptr<QDoubleSpinBox> boxWidthSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxHeightSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxXPosSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxYPosSpinBox;
   std::unique_ptr<QComboBox> boxTypeBox;

private:
   void setupSignalAndSlots();

signals:
   void switchBoxType(Box::BoxType type);

public slots:
   void addNewBox(SpriteSheet::Box& box);
};

}
