#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "note.h"
#include "notesmodel.h"
#include "facade.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/Files.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).


    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView *view  = SailfishApp::createView();

    // Check if overwriting bindings with static javascript assignement
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    qmlRegisterType<NotesModel>("NotesModel", 1, 0, "NotesModel" );
    qmlRegisterUncreatableType<Facade>("NotesModel", 1, 0, "Facade", QStringLiteral("Don't define Facade in QML!!") );
    qmlRegisterUncreatableType<Note>("NotesModel", 1, 0, "File", QStringLiteral("Don't define Note in QML!!") );

    // TODO : define data stub here
    //
    Facade carnetNotes;

    view->rootContext()->setContextProperty("carnetNotes", &carnetNotes);

    view->setSource(SailfishApp::pathTo("qml/carnetNotes.qml"));
    view->show();

    return app->exec();
}
