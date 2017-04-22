#ifndef BOXATTRIBUTEWIDGET_H
#define BOXATTRIBUTEWIDGET_H

#include <QtWidgets>
#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QLineEdit>

#include "limits.h"

#include "spritesheetmodel.h"
#include "boxattributewidget.h"

namespace SpriteSheet {
   class FrameAttributeWidget : public QWidget
   {
      Q_OBJECT

   public:
      FrameAttributeWidget(SpriteSheet::Sheet& sheet);

   public slots:
      void setNewFrame(int pos);
      void addNewFrame(SpriteSheet::Frame& box);

   signals:
      void frameSwitched(std::string frameGuid);

   private slots:
      void switchNextFrame();
      void switchPrevFrame();
      void deleteFrame();
      void saveSpriteSheet();
      void editFrameName();

   private:
      void switchFrame(const Frame* oldFrame, Frame& newFrame);
      void buildGuidList();
      void setupSignalAndSlots();

   private:
      std::unique_ptr<QComboBox> frameCurFrameComboBox;
      std::unique_ptr<QDoubleSpinBox> frameWidthSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameHeightSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameXPosSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameYPosSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameXOffsetSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameYOffsetSpinBox;
      std::unique_ptr<QDoubleSpinBox> frameLenSpinBox;
      std::unique_ptr<QComboBox> nextFrameComboBox;

      std::unique_ptr<QLineEdit> frameGuidLineEdit;
      std::unique_ptr<QPushButton> frameGuidEditButton;

      std::unique_ptr<QPushButton> frameNextFrameButton;
      std::unique_ptr<QPushButton> boxPrevFrameButton;

      std::unique_ptr<QPushButton> deleteFrameButton;
      std::unique_ptr<QPushButton> saveSpriteSheetButton;

      SpriteSheet::Sheet& sheet;
      std::string curFrameGuid;
   };
}

#endif // BOXATTRIBUTEWIDGET_H
