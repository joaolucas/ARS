import QtQuick 2.3
import QtQuick.Layouts 1.1

ColumnLayout
{
    id : rootId

    property url powerOnSource : "images/images/power_on.png"
    property url powerOffSource : "images/images/power_off.png"
    property url powerSource : powerOffSource
    property bool powerOn : MainViewMgr.powerOn
    function togglePower()
    {
        print ("main.qml in togglePower with value "+ powerOn)
        powerOn = ! powerOn
        powerSource = powerOn ? powerOnSource : powerOffSource
        MainViewMgr.powerOn = powerOn
    }

    Layout.alignment: Qt.AlignTop
    Text{
        text: "RF Power"
        Layout.alignment: Qt.AlignCenter
        color:"white"
        font.pointSize: 16
        font.family: boldLabelFont
    }
    Image{
        id :powerButtonId
        source: powerSource
        Layout.preferredWidth: 64
        Layout.preferredHeight: Layout.preferredWidth
        MouseArea{
            onClicked: togglePower()
            anchors.fill: parent
            hoverEnabled: true
            onHoveredChanged: parent.opacity =
                              containsMouse ? hoverOpacity : 1.0
        }
    }
}
