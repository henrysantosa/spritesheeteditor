#ifndef BOXATTRIBUTEWIDGET_H
#define BOXATTRIBUTEWIDGET_H

#include <QtWidgets>
#include <QDoubleSpinBox>
#include <QListWidgetItem>
#include <QGroupBox>

#include "limits.h"

#include "spritesheetmodel.h"
#include "boxattributewidget.h"

namespace SpriteSheet {
   class BoxAttributeWidget : public QWidget
   {
      Q_OBJECT

   public:
      BoxAttributeWidget(SpriteSheet::Frame& frame);

   public slots:
      void setNewBox(int pos);
      void addNewFrame(SpriteSheet::Box& box);

   private slots:
      void updateBoxWidth(double width);
      void updateBoxHeight(double width);
      void updateBoxXPos(double width);
      void updateBoxYPos(double width);
      void updateBoxFrameLen(double frameLen);
      void updateBoxNextFrame(int entry);

   private:
      std::unique_ptr<QComboBox> boxCurFrameComboBox;
      std::unique_ptr<QDoubleSpinBox> boxWidthSpinBox;
      std::unique_ptr<QDoubleSpinBox> boxHeightSpinBox;
      std::unique_ptr<QDoubleSpinBox> boxXPosSpinBox;
      std::unique_ptr<QDoubleSpinBox> boxYPosSpinBox;
      std::unique_ptr<QDoubleSpinBox> boxFrameLenSpinBox;
      std::unique_ptr<QComboBox> boxNextFrameComboBox;

      std::unique_ptr<QGroupBox> boxSpinBoxesGroup;

      SpriteSheet::Frame& frame;
      std::string curBoxGuid;
   };
}

#endif // BOXATTRIBUTEWIDGET_H
