#include "checkboxheader.h"
#include <QPainter>
#include <QMouseEvent>

CheckBoxHeader::CheckBoxHeader(Qt::Orientation orientation, QWidget* parent /*= 0*/)
    : QHeaderView(orientation, parent)
{
    isChecked_1 = false;
    isChecked_2 = false;
}

void CheckBoxHeader::paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();
    if ((logicalIndex == 1)||(logicalIndex == 2))
    {
        QStyleOptionButton option;

        option.rect.setX(rect.x()+2);
        option.rect.setY(rect.y()+4);
        option.rect.setWidth(20);
        option.rect.setHeight(20);

        option.state = QStyle::State_Enabled | QStyle::State_Active;

        if (logicalIndex == 1)
        {
            if (isChecked_1)
                option.state |= QStyle::State_On;
            else
                option.state |= QStyle::State_Off;
        }

        if (logicalIndex == 2)
        {
            if (isChecked_2)
                option.state |= QStyle::State_On;
            else
                option.state |= QStyle::State_Off;
        }

        style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &option, painter);
    }
}

void CheckBoxHeader::mousePressEvent(QMouseEvent* event)
{
    int logicalIndex = logicalIndexAt(event->x(), event->y());

    if (logicalIndex == 1)
    {
        setIsChecked1(!isChecked1());
        emit checkBoxClicked1(isChecked1());
    }

    if (logicalIndex == 2)
    {
        setIsChecked2(!isChecked2());
        emit checkBoxClicked2(isChecked2());
    }
}

void CheckBoxHeader::redrawCheckBox()
{
    viewport()->update();
}

void CheckBoxHeader::setIsChecked1(bool val)
{
    if (isChecked_1 != val)
    {
        isChecked_1 = val;

        redrawCheckBox();
    }
}

void CheckBoxHeader::setIsChecked2(bool val)
{
    if (isChecked_2 != val)
    {
        isChecked_2 = val;

        redrawCheckBox();
    }
}

