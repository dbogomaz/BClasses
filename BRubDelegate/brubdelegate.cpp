#include "brubdelegate.h"
#include <QDoubleSpinBox>
#include <QPainter>

BRubDelegate::BRubDelegate()
{

}

const QString BRubDelegate::CURRENCY = " руб.";// определение статической константы, определяющей валюту

// преобразует int копейки в финансовый рублевый формат
QString BRubDelegate::toRub(int value)
{
    const int COMMA_POS = 2; // позиция запятой справа от конца строки
    const int SPACE_STEP = 4; // шаг через который ставится пробел

    QString str = QString::number(value);

    if (str.size() == 1) {
        str.insert(0, "00");
    }

    if (str.size() == 2) {
        str.insert(0, "0");
    }

    str.insert(str.size() - COMMA_POS, ",");

//    int i = COMMA_POS + SPACE_STEP;
//    while (str.size() - i > 0) {
//        str.insert(str.size() - i, " ");
//        i += SPACE_STEP;
//    }

    for (int i = COMMA_POS + SPACE_STEP; (str.size() - i) > 0; i += SPACE_STEP) {
        str.insert(str.size() - i, " ");
    }

    str.append(CURRENCY);

    return str;
}

QString BRubDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    return toRub(value.toInt());
}

void BRubDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    if (index.data().toInt() < 0) {// для отрицательных чисел цвет будет красный
        QPalette pal;
        pal.setColor(QPalette::Text, Qt::red);
        opt.palette = pal;
    }
    opt.displayAlignment = opt.displayAlignment | Qt::AlignRight;
    QStyledItemDelegate::paint(painter, opt, index);
}

QWidget *BRubDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent);
    spinBox->setMaximum(static_cast<double>(MAX_VALUE) / 100);
    spinBox->setMinimum(-1 * static_cast<double>(MAX_VALUE) / 100);
    spinBox->setSuffix(CURRENCY);
    spinBox->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    return spinBox;
}

void BRubDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    double value = index.data().toDouble() / 100;
    spinBox->setValue(value);
}

void BRubDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox *spinBox = static_cast<QDoubleSpinBox*>(editor);
    int value = spinBox->value() * 100;
    model->setData(index, value);
}
