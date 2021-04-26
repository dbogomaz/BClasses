#include "btimeeditdelegate.h"

BTimeEditDelegate::BTimeEditDelegate()
{

}


void BTimeEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    opt.displayAlignment = opt.displayAlignment | Qt::AlignCenter;
    QStyledItemDelegate::paint(painter, opt, index);
}

QWidget *BTimeEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTimeEdit *timeEditor = new QTimeEdit(parent);
    return timeEditor;
}

void BTimeEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QTime value = index.model()->data(index, Qt::EditRole).toTime();
    QTimeEdit *timeEditor = static_cast<QTimeEdit*>(editor);
    timeEditor->setTime(value);
}

void BTimeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTimeEdit *timeEditor = static_cast<QTimeEdit*>(editor);
    QTime value = timeEditor->time();
    model->setData(index, value);
}

QString BTimeEditDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QTime time = value.toTime();
    return time.toString("hh:mm");
}
