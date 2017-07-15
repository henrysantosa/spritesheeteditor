#ifndef BOXATTRIBUTEWIDGET_H
#define BOXATTRIBUTEWIDGET_H

#include <QtWidgets>
#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QLineEdit>

#include "limits.h"

#include "spritesheetmodel.h"
#include "frameattributewidget.h"

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
      std::unique_ptr<QSpinBox> frameWidthSpinBox;
      std::unique_ptr<QSpinBox> frameHeightSpinBox;
      std::unique_ptr<QSpinBox> frameXPosSpinBox;
      std::unique_ptr<QSpinBox> frameYPosSpinBox;
      std::unique_ptr<QSpinBox> frameXOffsetSpinBox;
      std::unique_ptr<QSpinBox> frameYOffsetSpinBox;
      std::unique_ptr<QSpinBox> frameLenSpinBox;
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
