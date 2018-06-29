#include "note.h"

Note::Note(QString noteID, QObject *parent) : QObject(parent), m_noteID(noteID), m_title(noteID)
{
    connect(this, &Note::titleChanged, this, &Note::noteChanged );
    connect(this, &Note::contentChanged, this, &Note::noteChanged );
    connect(this, &Note::noteIDChanged, this, &Note::noteChanged );
}

QString Note::title() const
{ return m_title; }

void Note::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged(newTitle);
}

QString Note::content() const {
    return m_content;
}

void Note::setContent(const QString &newContent)
{
    if (m_content == newContent)
        return;

    m_content = newContent;
    emit contentChanged(newContent);
}

QString Note::noteID() const
{
    return m_noteID;
}

void Note::setNoteID(QString noteID)
{
    if (m_noteID == noteID)
        return;

    m_noteID = noteID;
    emit noteIDChanged(m_noteID);
}




