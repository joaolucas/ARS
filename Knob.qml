import QtQuick 2.3

Rectangle
{

    //Knob area properties
    property int knobCenterX: knobImageId.x + knobImageId.width/2
    property int knobCenterY: knobImageId.y + knobImageId.height/2
    property real knobScale: .75
    property int knobBgPad: 4
    property int startRotation: 195

    property real degreesPerRadian : 180.0/Math.PI
    property real radiansPerRev : 2 * Math.PI


    property real maxValue: 999
    property real minValue: -999
    property real midValue : minValue + (maxValue - minValue)/2
    property real maxAllowedChange : maxValue / 4
    property real maxFwdAngle : 75
    property real maxRevAngle : 105
    property real totalAngle : 330
    property int digits : 1
    property real incrementPerDeg : ((maxValue-minValue)/totalAngle)+ .02
    property real oldValue : minValue

    property real currentValue : minValue

    function getEventAngle(event)
    {
        var angle = Math.atan2(event.y - knobCenterY, event.x - knobCenterY);
        if(angle < 0) angle += radiansPerRev;
        return angle;
    }

    function getValueFromAngle(angle)
    {
        var result = angle * incrementPerDeg + midValue
        if (result > maxValue) result = maxValue
        if (result < minValue)result = minValue
        return result.toFixed(digits)
    }

    function handleKnobMove(mouseEvent)
    {
        var angle = getEventAngle(mouseEvent)
        var rotDeg = angle * degreesPerRadian
        if (rotDeg > maxFwdAngle && rotDeg < maxRevAngle) return

        var for_conversion = rotDeg - 270
        if (rotDeg < 90) for_conversion = rotDeg + 90

        var new_value = getValueFromAngle(for_conversion)
        var delta = Math.abs(new_value - oldValue)
        if (delta < maxAllowedChange)
        {
            currentValue = new_value
            knobImageId.rotation = rotDeg + 90.0
            oldValue = new_value
        }
     }

    id: knobBgId
    width : knobImageId.width * knobScale + knobBgPad
    height : width
    radius : width/2
    color: "gainsboro"
    anchors.horizontalCenter: parent.horizontalCenter

    Image{
        id: knobImageId
        source: "images/images/knob.png"
        scale: knobScale
        rotation: startRotation
        anchors.centerIn: parent
    }
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        onMouseXChanged: if (pressedButtons === Qt.LeftButton) handleKnobMove(mouse)
        onMouseYChanged: if (pressedButtons === Qt.LeftButton) handleKnobMove(mouse)
        onHoveredChanged: knobImageId.opacity = containsMouse ?  hoverOpacity :  1.0
    }

}
