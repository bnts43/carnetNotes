#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include "facade.h"

#include <QObject>
#include <QAbstractListModel>

class NotesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Facade *listeNotes READ listeNotes WRITE setListeNotes NOTIFY listeNotesChanged)

    Facade * m_listeNotes;

public:
    explicit NotesModel(QObject * parent = nullptr);

    Facade * listeNotes() const;
    // méthodes à redéfinir absolument
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const;
    enum {
        NoteID = Qt::UserRole,
        Title,
        Content,
        Note
    };
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Q_INVOKABLE void newElement();
    Q_INVOKABLE void removeRow(int index);

public slots:
void setListeNotes(Facade * listeNotes);

signals:
void listeNotesChanged(Facade * listeNotes);

};

#endif // NOTESMODEL_H
