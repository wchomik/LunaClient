import QtQuick 2.0

ShaderEffect {
    property int size: 40
    width: size
    height: size


    transform: Translate {
        x: -size / 2
        y: -size / 2
    }

    property color color: "white"
    vertexShader: "
        uniform highp mat4 qt_Matrix;
        attribute highp vec4 qt_Vertex;
        attribute highp vec2 qt_MultiTexCoord0;
        varying highp vec2 coord;
        void main() {
            coord = qt_MultiTexCoord0 * 2.0 - 1.0;
            gl_Position = qt_Matrix * qt_Vertex;
        }"
    fragmentShader: "
        varying highp vec2 coord;
        uniform lowp vec4 color;
        void main() {
            float d2 = sqrt(dot(coord, coord));
            lowp float c = max(0.0, 0.05 * (1.0 / d2 - 1.0));
            vec4 ret = c * color;
            ret.a = 0.0;
            gl_FragColor = ret;
        }"
}
