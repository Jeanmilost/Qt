pragma Singleton

import QtQuick 2.15

/**
* Qml common style properties
*@author Jean-Milost Reymond
*/
QtObject
{
    // color properties
    readonly property string m_DocumentBgColor:          "white"
    readonly property string m_DarkTextColor:            "#202020"
    readonly property string m_LightTextColor:           "white"
    readonly property string m_HighlightColor:           "#4e8cde"
    readonly property string m_HandleBgColor:            "#c0c0c0"
    readonly property string m_HandleBorderColor:        "black"
    readonly property string m_HandleControlBorderColor: "#202020"
    readonly property string m_ConnectorBgColor:         "white"
    readonly property string m_ConnectorBorderColor:     "#c0c0c0"
    readonly property string m_BoxHandleBgColor:         "#c0c0c0"
    readonly property string m_BoxHandleBorderColor:     "black"
    readonly property string m_BoxBgColor:               "white"
    readonly property string m_BoxBorderColor:           "#202020"
    readonly property string m_LinkBgColor:              "white"
    readonly property string m_LinkBorderColor:          "#202020"
    readonly property string m_CheckBoxDefault:          "#e0e0e0"
    readonly property string m_CheckBoxPressed:          "#808080"

    // skinning properties
    readonly property int m_HandleWidth:          7
    readonly property int m_HandleHeight:         7
    readonly property int m_HandleBorderWidth:    1
    readonly property int m_HandleRadius:         3
    readonly property int m_ConnectorWidth:       14
    readonly property int m_ConnectorHeight:      14
    readonly property int m_ConnectorBorderWidth: 3
    readonly property int m_ConnectorRadius:      7
    readonly property int m_BoxBorderWidth:       1
    readonly property int m_BoxRadius:            3
    readonly property int m_BoxTextMargin:        2
    readonly property int m_LinkBorderWidth:      1
    readonly property int m_LinkRadius:           3
    readonly property int m_LinkTextMargin:       2

    // component font properties
    readonly property QtObject m_ComponentFont: QtObject
    {
        readonly property string m_Family: "Arial"
        readonly property int    m_Size:   9
    }

    // interface properties
    property bool m_UseCurvedLines: false
}
