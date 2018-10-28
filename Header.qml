import QtQuick 2.3
import QtQuick.Layouts 1.1

Rectangle{
   color :headerBgColor
   anchors {top : parent.top; left : parent.left; right:parent.right}
   height: 65

   RowLayout
   {
       id : logoGrid
       anchors {left: parent.left ;right: parent.right}
       transform: Translate{x: -20;y:-10}

//       Image{
//           id : swatLogo
//           source :"images/images/swatteam.png"
//           scale: .7
//       }

//       Text{
//           text: "Software and Technical\nTeam\nat Syncor Systems, Inc."
//           font{family: headerFontFamily;pointSize: companyFontSize}
//           color: companyFontColor
//       }

       Text{
           text: MainViewMgr.appName
           font{family: headerFontFamily
                pointSize: headerFontSize
                weight: Font.Bold}
           horizontalAlignment: Text.AlignHCenter
           //verticalAlignment: Text.AlignVCenter
           Layout.fillWidth: true;
           color :gradientEndColor
       }

   }
}
