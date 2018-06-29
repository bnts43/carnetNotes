import QtQuick 2.0
import Sailfish.Silica 1.0
import NotesModel 1.0
import "../delegates"

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaListView {
        id: listView
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("Add Note")
                onClicked: listView.model.newElement()
            }
        }

        header: PageHeader { title: qsTr("My notes")   }


        model: NotesModel { listeNotes: carnetNotes }
        delegate: DelegateNote { }
        VerticalScrollDecorator {}
    }
}
