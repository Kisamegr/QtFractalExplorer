import QtQuick 2.0
import MyQOpenGL 1.0


QOpenGLItem {

    width: parent.width/scale
    height: parent.height/scale
    windowWidth: width
    windowHeight: height
    scale: 1.0
    offSetX: 0
    offSetY: 0

    cameraCenterX: 0
    cameraCenterY: 0
    drawColor: "white"

    fractalIndex: 0
    iterations: 10000
    snowflakeSize: snowflakeSizeSpin.value

    onWidthChanged: { windowWidth = width}
    //cameraCenterX: mouseHandler.mouseX + x
    //cameraCenterY: mouseHandler.mouseY + y

    function changeCameraCenter() {
        //cameraCenterX = mouseHandler.mouseX + x
        //cameraCenterY = mouseHandler.mouseY + y





        console.log("x: " + cameraCenterX + "  y: " + cameraCenterY)



    }
}
