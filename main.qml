import QtQuick 2.9
import QtQuick.Window 2.2

Window {
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


    Gradient{
        id:appGradientId
        GradientStop{position: 0.0 ;color:gradientStartColor}
        GradientStop{position: 1.0 ; color: gradientEndColor }
    }

    //==== MAIN VIEW ====//
    Rectangle{
     objectName: "mainViewRect"
     id: mainViewRect

     anchors.fill: parent
     gradient: appGradientId

     //---- Header -----

     //---- Controls Area -----

    }

}
