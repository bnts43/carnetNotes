#ifndef FACADE_H
#define FACADE_H

#include <QObject>
#include <src/note.h>

class Facade : public QObject
{
    Q_OBJECT
    QList<Note *> listeNotes;

public:
    explicit Facade(QObject *parent = nullptr);

    void append(Note* note);
    Note *at(int place) const;
    int count() const;
    void createNote(QString noteID);
    void removeNote(int position);
    QList<Note *> getListeNotes() const;
    void setListeNotes(const QList<Note *> &value);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void itemChanged(int row);

public slots:
};

#endif // FACADE_H
