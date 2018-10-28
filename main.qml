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

    property real minVelocity : -250
    property real maxVelocity : 250
    property real minDistance  : 70
    property real maxDistance : 200
    //Preset properties
    property var velocities : [MainViewMgr.velocityPreset1,
        MainViewMgr.velocityPreset2,
        MainViewMgr.velocityPreset3,
        MainViewMgr.velocityPreset4]

    property var distances : [MainViewMgr.distancePreset1,
        MainViewMgr.distancePreset2,
        MainViewMgr.distancePreset3,
        MainViewMgr.distancePreset4]


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
        Feedback{
            NumberAnimation on opacity {
                from: 0
                to: .85
                duration: 2000
                easing.type: Easing.OutQuad
            }
        }

        //---- Controls Area -----
        RowLayout{
            enabled: MainViewMgr.instrumentControlsEnabled
            id: powerKnobRowId
            anchors{
                top: headerId.bottom
                topMargin: 15
                left: parent.left
                right: parent.right
                leftMargin: rowLeftMargin
            }
            RfPower{}
            KnobControl{
                id: velocityId
                knobMinValue: minVelocity
                knobMaxValue: maxVelocity
                labelText: "Velocity"
                unitsText: "KPH"
                knobCurrentValue: MainViewMgr.velocity
                onKnobCurrentValueChanged: MainViewMgr.velocity = knobCurrentValue
            }
            KnobControl{
                id: distanceId
                knobMinValue: minDistance
                knobMaxValue: maxDistance
                labelText: "Distance"
                unitsText: "M"
                knobCurrentValue: MainViewMgr.distance
                onKnobCurrentValueChanged: MainViewMgr.distance = knobCurrentValue
            }

        }

             //        Preset Buttons Row
        RowLayout{
            id: presetRowId
            enabled: MainViewMgr.instrumentControlsEnabled
            anchors{
                bottom : parent.bottom
                bottomMargin: 10
                left : parent.left
                right : parent.right
                leftMargin: 30
            }
            Layout.alignment: Qt.AlignBottom

            PresetButton{
                presetTitle: "Preset 1"
                labelFont : boldLabelFont
                velocity :velocities[0]
                distance: distances[0]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOpacity: mainViewWindow.hoverOpacity
            }
            PresetButton{
                presetTitle: "Preset 2"
                labelFont : boldLabelFont
                velocity :velocities[1]
                distance: distances[1]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOpacity: mainViewWindow.hoverOpacity
            }
            PresetButton{
                presetTitle: "Preset 3"
                labelFont : boldLabelFont
                velocity :velocities[2]
                distance: distances[2]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOpacity: mainViewWindow.hoverOpacity
            }
            PresetButton{
                presetTitle: "Preset 4"
                labelFont : boldLabelFont
                velocity :velocities[3]
                distance: distances[3]
                velocityControl: velocityId
                distanceControl: distanceId
                hoverOpacity: mainViewWindow.hoverOpacity
            }

        }
        //Four PresetButton QML Components
    }

}
