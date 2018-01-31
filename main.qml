import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.2

Item {
    id: appWindow
    visible: true
    width: 1280
    height: 768

   // title: qsTr("OpenGL Test")

    Rectangle {
        color: "#000000"
        opacity: 1
        anchors.fill: parent

        MyOpenGLItem {
          id: opengl

        }

        MouseArea {
            id: mouseHandler
            anchors.fill: parent

            property real maxScale: 3
            property real minScale: 0.1

            drag.target: opengl
            drag.axis: Drag.XandYAxis

            hoverEnabled: true



            onWheel: {

                //opengl.changeCameraCenter()

                moveForScale(mouseX,mouseY, wheel.angleDelta.y > 0)

            }

            function moveForScale(mouse_x, mouse_y,zoomIn) {

                var sPosX = (mouse_x - opengl.x) / opengl.scale
                var sPosY = (mouse_y - opengl.y) / opengl.scale


                //console.log("POINT:  " + (mouseX - opengl.x) + " - " + (mouseY - opengl.y))
                //console.log("STATIC: " + sPosX + " - " + sPosY)
                //console.log("SCALE:  " + opengl.scale)
                //console.log("MOUSE:  " + mouseX + " - " + mouseY)


                var step = 0.1 * opengl.scale
                console.log(step)

                if(!zoomIn) {

                    if(opengl.scale + step < maxScale)
                        opengl.scale += step
                    else
                        opengl.scale = maxScale
                }

                if(zoomIn) {
                    if(opengl.scale - step > minScale)
                        opengl.scale -= step
                    else
                        opengl.scale = minScale
                }


                var newMousePosX = opengl.x + sPosX*opengl.scale
                var newMousePosY = opengl.y + sPosY*opengl.scale

                if(fractal.currentIndex !==2) {
                    opengl.x += newMousePosX - mouseX
                    opengl.y += newMousePosY - mouseY

                }
                else {

                    opengl.offSetX -= newMousePosX - mouseX + opengl.x
                    opengl.offSetY -= newMousePosY - mouseY + opengl.y
                    console.log("NEW OFF X:  " + opengl.offSetX)
                    console.log("NEW OFF Y:  " + opengl.offSetY)

                    opengl.x = 0
                    opengl.y = 0
                }


                //console.log("NEW POINT:  " + (mouseX - opengl.x) + " - " + (mouseY - opengl.y))
                //console.log("NEW MOUSE:  " + newMousePosX + " - " + newMousePosY)

            }
        }

        ColorDialog {
            id: colorDialog
            title: "Please choose a color"
            color: "white"

            onAccepted: opengl.drawColor = color



        }

        RowLayout {
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: 20
            opacity: 0.8


            Layout.fillHeight: true
            Layout.fillWidth: true

            Button {
                id: resetBtn
                text: "RESET"
                implicitHeight: 30
                implicitWidth:60

                font.pixelSize: 9
                font.bold: true

                onPressed: reset()

                function reset() {
                    opengl.offSetX = 0
                    opengl.offSetY = 0
                    opengl.scale = 1
                    opengl.x = 0
                    opengl.y = 0

                }

            }
        }




        ColumnLayout {
            opacity: 0.9
            spacing: 10

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.margins: 20

            ColumnLayout {
                id: columnLayout1
                width: 100
                height: 100
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    color: "#ffffff"
                    text: "FRACTAL"
                    font.bold: true
                    anchors.right: parent.right
                    verticalAlignment: Text.AlignVCenter
                    anchors.left: parent.left
                    font.pixelSize: 16
                    font.family: "Arial"
                    horizontalAlignment: Text.AlignHCenter



                }

                ComboBox {
                    model: ["Barnsley's Fern","Snowflake", "Mandelbrot"]
                    id: fractal
                    opacity: 1
                    leftPadding: 12
                    enabled: true
                    spacing: 8
                    currentIndex: 0
                    textRole: qsTr("")
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 150

                    onCurrentIndexChanged: {

                        if(currentIndex===2)
                            opengl.iterations = iterationsMandel.value
                        else
                            opengl.iterations = iterations.value

                        opengl.fractalIndex = currentIndex

                        resetBtn.reset()
                    }
                }
            }
            ColumnLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true

                Label {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: "ITERATIONS"
                    font.underline: false
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "white"
                    font.family: "Arial"
                    font.pixelSize: 16

                }


                SpinBox {
                    id: iterations
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 150

                    visible: fractal.currentIndex !==2

                    from: 1
                    to: 1000000
                    value: 10000
                    stepSize: 5000
                    editable: true

                    onValueChanged: opengl.iterations = value


                }

                SpinBox {
                    id: iterationsMandel
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 150

                    visible: fractal.currentIndex === 2

                    from: 1
                    to: 1000
                    value: 100
                    stepSize: 1
                    editable: true

                    onValueChanged: opengl.iterations = value

                }



            }

            ColumnLayout {
                width: 100
                height: 100
                visible: fractal.currentIndex === 1

                Label {
                    color: "#ffffff"
                    text: "SIZE"
                    anchors.right: parent.right
                    verticalAlignment: Text.AlignVCenter
                    font.bold: true
                    anchors.left: parent.left
                    font.pixelSize: 16
                    font.underline: false
                    font.family: "Arial"
                    horizontalAlignment: Text.AlignHCenter
                }

                SpinBox {
                    id: snowflakeSizeSpin
                    to: 100
                    value: 6
                    editable: true
                    stepSize: 1
                    from: 1
                    Layout.preferredWidth: 150
                    Layout.preferredHeight: 30
                }
            }

            Button {
                text: "CHANGE COLOR"
                visible: fractal.currentIndex !== 2
                antialiasing: false
                highlighted: false
                spacing: 0
                topPadding: 6
                Layout.preferredWidth: 90
                Layout.preferredHeight: 22
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

                font.pixelSize: 9
                font.bold: true

                onPressed: colorDialog.visible = true

            }




        }

    }


}
