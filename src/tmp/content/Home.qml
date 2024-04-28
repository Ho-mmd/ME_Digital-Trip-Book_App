import QtQuick 2.15
import QtQuick.Controls

Item {
    id: home

    width: parent.width
    height: parent.height * 0.87
    anchors.top: parent.top

    Rectangle {
        id: blank_user_name

        width: parent.width
        height: parent.height * 0.07
        anchors.top: parent.top

        //color: "black"

        Rectangle {
            width: parent.width * 0.08
            height: parent.height
            anchors.right: parent.right

            Image {
                source: "images/setting.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("setting")
                    }
                }
            }
        }
    }

    Rectangle {
        id: user_name

        width: parent.width * 0.39
        height: parent.height * 0.05
        anchors.top: blank_user_name.bottom

        Text {
            text: "Hello, User!"
            font.pointSize: 30
            font.weight: Font.Black
            anchors.centerIn: parent
        }
    }

    Rectangle {
        id: blank_model_name

        width: parent.width
        height: parent.height * 0.05
        anchors.top: user_name.bottom

        //color: "black"
    }

    Rectangle {
        id: car_model_name

        width: parent.width * 0.4
        height: parent.height * 0.05
        anchors.top: blank_model_name.bottom

        color: "black"

        Image {
            source: "images/car_model_name.png"
            anchors.fill: parent
        }

        Text {
            text: "MINI Cooper SE"
            font.pointSize: 22
            font.weight: Font.Black
            anchors.centerIn: parent
        }

    }

    Rectangle {
        id: car_model_image

        width: parent.width
        height: parent.height * 0.5
        anchors.top: car_model_name.bottom

        //color: "black"

        Image {
            source: "images/car_demo.png"
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
        }
    }

    Rectangle {
        id: update_bar

        width: parent.width
        height: parent.height * 0.03

        anchors.top: car_model_image.bottom

        Rectangle {
            width: parent.width * 0.27
            height: parent.height
            anchors.left: parent.left

            Text {
                text: "Update at 00:00"

                anchors.centerIn: parent
            }
        }

        Rectangle {
            width: parent.width * 0.08
            height: parent.height
            anchors.right: parent.right

            Image {
                source: "images/home_update.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit

                MouseArea {
                   anchors.fill: parent
                   onClicked: {
                       console.log("update")
                   }
               }
            }
        }

    }

    Rectangle {
        id: status

        width: parent.width
        height: parent.height * 0.2
        anchors.top: update_bar.bottom

        Rectangle {
            id: total_dist

            width: parent.width * 0.333
            height: parent.height
            anchors.left: parent.left

            Image {
                source: "images/home_td.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Text {
                text: "??? km"
                x: 80
                y: 70
            }
        }

        Rectangle {
            id: possible_dist

            width: parent.width * 0.333
            height: parent.height
            anchors.left: total_dist.right

            Image {
                source: "images/home_pd.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Text {
                text: "??? km"
                x: 80
                y: 70
            }
        }

        Rectangle {
            id: battery

            width: parent.width * 0.333
            height: parent.height
            anchors.left: possible_dist.right

            Image {
                source: "images/home_battery.png"
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
            }

            Text {
                text: "??? %"
                x: 83
                y: 70
            }
        }
    }

    Rectangle {
        id: blank_menu

        width: parent.width
        height: parent.height * 0.05
        anchors.top: status.bottom

        //color: "black"
    }
}
