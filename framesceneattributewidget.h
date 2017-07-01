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
   explicit FrameSceneAttributeWidget(SpriteSheet::Sheet& sheet, std::string curId, QWidget *parent = 0);

private:
   SpriteSheet::Sheet& sheet;
   std::string curFrameGuid;
   std::string curBoxGuid;

   std::unique_ptr<QComboBox> curBoxComboBox;
   std::unique_ptr<QDoubleSpinBox> boxWidthSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxHeightSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxXPosSpinBox;
   std::unique_ptr<QDoubleSpinBox> boxYPosSpinBox;
   std::unique_ptr<QComboBox> boxTypeBox;
   std::unique_ptr<QPushButton> deleteBoxButton;

private:
   void setupSignalAndSlots();
   void switchBox(Box& box);

signals:
   void switchBoxType(Box::BoxType type);
   void boxDeleted();

public slots:
   void switchFrame(std::string& guid);
   void switchBox(std::string& guid);
   void addNewBox(Box& box);

private slots:
   void deleteBox();
};

}
