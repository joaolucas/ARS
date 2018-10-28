import QtQuick 2.3
import QtQuick.Layouts 1.1

Item
{
    id: rootId
    property string presetTitle : "Preset"
    property string labelFont : "Impact"
    property string presetFontFamily: "Tahoma"
    property int presetFontSize: 16
    property real velocity
    property real distance
    property int digits : 1

    property url buttonDownSource : "images/images/preset_down.png"
    property url buttonUpSource : "images/images/preset_up.png"
    property url imageSource : buttonUpSource
    property var distanceControl
    property var velocityControl
    property real hoverOpacity :.1

    height : presetLayout.height
    width : presetLayout.width

    function sendPreset(mouse)
    {
        print ("Sending "+ velocity + " " +distance)
        distanceControl.knobCurrentValue = distance
        velocityControl.knobCurrentValue = velocity
        MainViewMgr.distance = distance
        MainViewMgr.velocity = velocity
    }

    ColumnLayout{
        id : presetLayout
        Text
        {
         text: presetTitle
         Layout.alignment: Qt.AlignCenter
         color : "white"
         font.family: labelFont
         font.pointSize: 16
        }

        Image{
            id : buttonImage
            source : imageSource
            MouseArea{
                id : mouseAreaForButton
                anchors.fill:  parent
                onClicked : sendPreset(mouse)
                onPressed: imageSource = buttonDownSource
                onReleased: imageSource = buttonUpSource
                hoverEnabled: true
                onHoveredChanged: parent.opacity = containsMouse ?  hoverOpacity :  1.0
            }

            Column{
                width : parent.width
                anchors
                {
                    top : parent.top
                    topMargin : 5
                }
                spacing : 5
                Text{

                    width : parent.width
                    text : velocity.toFixed(digits) +  " KPH"
                    font.family : presetFontFamily
                    font.weight : Font.Bold
                    font.pointSize: presetFontSize
                    color :"black"
                    horizontalAlignment: Qt.AlignHCenter
                }
                Text{
                    width : parent.width
                    text : distance.toFixed(digits) +  " M"
                    font.family : presetFontFamily
                    font.pointSize: presetFontSize
                    font.weight : Font.Bold
                    color : "ghostwhite"
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }
    }
}
