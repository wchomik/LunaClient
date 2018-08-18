import QtQuick 2.9
import QtCharts 2.1

ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark

    ValueAxis {
        id: axisY
        min: 0
        max: 0.01
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 512
    }

    LineSeries {
        id: lineSeries
        //name: "signal 1"
        axisX: axisX
        axisY: axisY
        useOpenGL: true
    }
}
