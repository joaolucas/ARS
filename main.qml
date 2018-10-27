import QtQuick 2.9
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.3

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
        Rectangle{
           color :headerBgColor
           anchors {top : parent.top; left : parent.left; right:parent.right}
           height: 65

           RowLayout
           {
               id : logoGrid
               anchors {left: parent.left ;right: parent.right}
               transform: Translate{x: -20;y:-10}

               Image{
                   id : swatLogo
                   source :"images/images/swatteam.png"
                   //scale: .9
               }

               Text{
                   text: "Software and Technical\nTeam\nat Syncor Systems, Inc."
                   font{family: headerFontFamily;pointSize: companyFontSize}
                   color: companyFontColor
               }

               Text{
                   text: MainViewMgr.appName
                   font{family: headerFontFamily
                        pointSize: headerFontSize
                        weight: Font.Bold}
                   horizontalAlignment: Text.AlignHCenter
                   Layout.fillWidth: true;
                   color :gradientEndColor
               }

           }
        }

        //---- Controls Area -----

    }

}
