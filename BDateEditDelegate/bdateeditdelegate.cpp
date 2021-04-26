#include "bdateeditdelegate.h"

BDateEditDelegate::BDateEditDelegate()
{

}

QWidget *BDateEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDateEdit *dateEditor = new QDateEdit(parent);
    return dateEditor;
//    return nullptr;
}


void BDateEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << index.model()->data(index, Qt::DisplayRole);
    QDate value = index.model()->data(index, Qt::EditRole).toDate();
//    qDebug() << value;
    QDateEdit *dateEditor = static_cast<QDateEdit*>(editor);
    dateEditor->setDate(value);
}


void BDateEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDateEdit *dateEditor = static_cast<QDateEdit*>(editor);
    QDate value = dateEditor->date();
    model->setData(index, value);
}


QString BDateEditDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    QDate date = value.toDate();
    return date.toString("dd.MM.yyyy");
}


void BDateEditDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    opt.displayAlignment = opt.displayAlignment | Qt::AlignCenter;
    QStyledItemDelegate::paint(painter, opt, index);
}
