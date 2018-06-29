import QtQuick 2.0
import Sailfish.Silica 1.0
import NotesModel 1.0


Page {
    property var note

    Flickable {
        id: flickable
        flickableDirection: Flickable.VerticalFlick
        anchors.fill: parent

        TextField {

            anchors.top: parent.top
            id: titleField

            text: note.title
            label: "Title"

            width: parent.width
            EnterKey.onClicked: {
                note.title = text
                contentArea.focus = true
            }
            onFocusChanged: {
                note.title = text
                text = Qt.binding( function() { return note.title} )
            }
        }

        TextArea {
            id: contentArea
            anchors.top: titleField.bottom

            text: note.content
            label: "Content"
            placeholderText: "Add your note here"

            onFocusChanged:  {
                note.content = text
                text = Qt.binding( function() { return note.content} )
            }

            MouseArea {
                anchors.fill: parent
                onClicked: TextArea.focus=true
            }
        }
    }
}
