import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages"

ListItem {
    id: singleNote
    width: listView.width
    Label {
        text: title
    }

    menu: ContextMenu {
        MenuItem {
            text: "Remove from List"
            onClicked: listView.model.removeRow(index)
        }
        MenuItem {
            text: "Delete Note"
            onClicked: remorse.remorseDelete()

            RemorseItem {
                id: remorse
                function remorseDelete() {
                    var idx = index
                    remorse.execute(singleNote, "Deleting Notee", function() {
                        listView.model.removeRow(idx) }, 2000 )
                }
            }
        }
    }

    onClicked: pageStack.push( "../pages/notepage.qml", { note: note}  )

}
