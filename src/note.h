#ifndef NOTE_H
#define NOTE_H

#include <QObject>

class Note : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(QString noteID READ noteID WRITE setNoteID NOTIFY noteIDChanged)

public:
    explicit Note(QString noteID, QObject *parent = nullptr);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString content() const;
    void setContent(const QString &newContent);

    QString noteID() const;

signals:
    void titleChanged(const QString &newTitle);
    void contentChanged(const QString &newContent);
    void noteIDChanged(const QString &noteID);

    void noteChanged(const QString & newTitle);

public slots:
    void setNoteID(QString noteID);

private:
    QString m_title;
    QString m_content;
    QString m_noteID;
};

#endif // NOTE_H
