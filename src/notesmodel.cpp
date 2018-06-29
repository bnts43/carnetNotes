#include "notesmodel.h"
#include <QDateTime>

#include <QDebug>

NotesModel::NotesModel(QObject *parent)
    : QAbstractListModel(parent), m_listeNotes(nullptr)
{
}

Facade *NotesModel::listeNotes() const
{
    return m_listeNotes;
}

int NotesModel::rowCount(const QModelIndex &parent) const
{
    if ( parent.isValid())
        return 0;

    return m_listeNotes->count();
}

QVariant NotesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto note = m_listeNotes->at(index.row());

    switch (role) {
        case NoteID:
            return note->noteID();
        case Title:
            return note->title();
        case Content:    // redéfinir ici et voir s'il faut pouvoir jouer sur le contenu
            return note->content();
        case Note:
            return QVariant::fromValue(note);
        default:
            break;
    }
    return QVariant();
}

void NotesModel::setListeNotes(Facade *listeNotes)
{
    beginResetModel();

       if (m_listeNotes)
           m_listeNotes->disconnect(this);

       m_listeNotes = listeNotes;

       if (m_listeNotes) {
           connect(m_listeNotes, &Facade::preItemAppended, this, [=]() {
               const int index = m_listeNotes->count();        // Append implies end
               beginInsertRows(QModelIndex(), index, index);
           });
           connect(m_listeNotes, &Facade::postItemAppended, this, [=]() {
               endInsertRows();
           });

           connect(m_listeNotes, &Facade::preItemRemoved, this, [=](int index) {
               beginRemoveRows(QModelIndex(), index, index);
           });
           connect(m_listeNotes, &Facade::postItemRemoved, this, [=]() {
               endRemoveRows();
           });
           connect(m_listeNotes, &Facade::itemChanged,
                   this, [=](int row){ qDebug()<< "itemChanged " << row; emit NotesModel::dataChanged(this->index(row), this->index(row)); });
       }

   endResetModel();
}

QHash<int, QByteArray> NotesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NoteID]   = "idNote";
    roles[Title]    = "title";
    roles[Content]  = "content";
    roles[Note]     = "note";

    return roles;
}

bool NotesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        auto note = m_listeNotes->at(index.row());

        switch (role) {
        case NoteID:
            note->setTitle(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
        default:
            break;
        }
        return true;
    }
    return false;
}

void NotesModel::newElement()
{
    QString now = QDateTime::currentDateTime().toString("dd.MM.yyyy-hh:mm:ss.zzz");
    QString name(tr("New note")+now);
    m_listeNotes->createNote(name);
}

void NotesModel::removeRow(int index)
{
    m_listeNotes->removeNote(index);
}
