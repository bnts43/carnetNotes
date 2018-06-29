#include "facade.h"

Facade::Facade(QObject *parent) : QObject(parent) { }

void Facade::append(Note *note)
{
    emit preItemAppended();

    int position = count();
    connect(note, &Note::noteChanged, this, [=]() { emit Facade::itemChanged(position); } );
    listeNotes.append(note);

    emit postItemAppended();
}

QList<Note *> Facade::getListeNotes() const
{
    return listeNotes;
}

void Facade::setListeNotes(const QList<Note *> &value)
{
    listeNotes = value;
}

int Facade::count() const
{
    return listeNotes.count();
}

void Facade::createNote(QString noteID)
{
    append(new Note(noteID));
}

void Facade::removeNote(int position)
{
    emit preItemRemoved(position);
    disconnect(listeNotes[position], &Note::noteChanged, this, 0);

    listeNotes.removeAt(position);

    for ( ; position < count() ; ++position ) {
        disconnect ( listeNotes[position], &Note::noteChanged, this, 0);
        connect( listeNotes[position], &Note::noteChanged, this, [=](){
            emit Facade::itemChanged( position ); } );
    }
    emit postItemRemoved();
}

Note *Facade::at(int place) const
{
    return listeNotes.at(place);
}
