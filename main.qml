import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: mainViewWindow
    visible: true
    width: 1024
    height: 600
    title: qsTr(MainViewMgr.appName)

    property string headerFontFamily : "Tahoma"
    property int companyFontSize : 10
    property string companyFontColor :"darkred"
    property int headerFontSize : 18
    property string headerBgColor : "white"
    property string gradientStartColor: "skyblue"
    property string gradientEndColor: "blue"

    property int rowLeftMargin : 30
    property string boldLabelFont: "Impact"
    property real hoverOpacity : .85
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

    property real minVelocity : -250
    property real maxVelocity : 250
    property real minDistance  : 70
    property real maxDistance : 200

    Gradient{
        id:appGradientId
        GradientStop{position: 0.0 ;color:gradientStartColor}
        GradientStop{position: 1.0 ; color: gradientEndColor }
    }

    //==== MAIN VIEW ====//
    Rectangle{

        id : mainViewRect
        objectName: "mainViewRect"
        anchors.fill : parent
        gradient : appGradientId

        //---- Header -----

        Header{
            id: headerId
        }

        //---- Controls Area -----
        RowLayout{
            id: powerKnobRowId
            anchors{
                top: headerId.bottom
                topMargin: 15
                left: parent.left
                right: parent.right
                leftMargin: rowLeftMargin
            }
            ColumnLayout
            {
                id : powerAreaId
                Layout.alignment: Qt.AlignTop
                Text {
                    text: "RF Power"
                    Layout.alignment: Qt.AlignCenter
                    color:"white"
                    font.pointSize: 16
                    font.family: boldLabelFont
                }
                Image {
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
            ColumnLayout
            {
                id:velocityColumnId

            }
            ColumnLayout
            {
                id:distanceColumnId
            }
        }

        RowLayout{
            id: presetRowId
            anchors{
                bottom : parent.bottom
                bottomMargin: 10
                left : parent.left
                right : parent.right
                leftMargin: 30
            }
            Layout.alignment: Qt.AlignBottom
        }
    }

}
