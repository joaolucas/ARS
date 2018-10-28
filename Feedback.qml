import QtQuick 2.3
import QtQuick.Controls 1.2


Rectangle {
    id: rootId

    property string okButtonUpSource : "images/images/okup.png"
    property string okButtonDownSource: "images/images/okdown.png"
    property color outerRectColor: "gold"
    property color  innerRectColor: "goldenrod"
    property color backgroundColor: "black"
    property color normalText : "white"
    property color errorText : "darkred"
    property string fontFamily: "Tahoma"

    width : parent.width/1.5
    height :parent.height/1.5
    anchors.centerIn: parent
    color: backgroundColor
    border.color: outerRectColor
    border.width: 4
    z:1
    opacity: MainViewMgr.feedbackOKButtonVisible? 0.9 : 0.85
    visible: MainViewMgr.feedbackAreaVisible
    Rectangle{
        id : feedbackRect
        border.color :innerRectColor
        anchors{fill :parent
            margins: 4}
        border.width: 2
        color : parent.color
        opacity : parent.opacity
        Text{
            id : feedbackMsg
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment:Text.AlignLeft
            anchors{fill: parent; margins: 20}
            font{family: fontFamily; pointSize: 24}
            wrapMode: Text.WordWrap
            clip: true
            elide: Qt.ElideRight
            color: MainViewMgr.feedbackOKButtonVisible?
                       errorText : normalText
            text: MainViewMgr.feedbackMessage
        }  ProgressBar{
            minimumValue: 0
            maximumValue: 100
            anchors{ right : feedbackRect.right
                rightMargin: 20
                verticalCenter: feedbackRect.verticalCenter}
            indeterminate: value >= 100
            value: MainViewMgr.feedbackProgress
            visible: !MainViewMgr.feedbackOKButtonVisible
        } Image{
            source : okButtonUpSource
            anchors.bottom : parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            visible: MainViewMgr.feedbackOKButtonVisible
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onPressed: parent.source = okButtonDownSource
                onHoveredChanged:  parent.opacity = containsMouse ? hoverOpacity : 1.0
                onClicked: {MainViewMgr.feedbackAreaVisible= false
                    MainViewMgr.instrumentControlsEnabled = true}

            }
        }
    }
}
