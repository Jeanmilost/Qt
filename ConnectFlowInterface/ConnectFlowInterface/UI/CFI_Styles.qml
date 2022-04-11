pragma Singleton

import QtQuick 2.15

/**
* Qml common style properties
*@author Jean-Milost Reymond
*/
QtObject
{
    // color properties
    readonly property string m_DocumentBackground: "white"
    readonly property string m_DarkTextColor:      "#202020"
    readonly property string m_LightTextColor:     "white"
    readonly property string m_HighlightColor:     "#4e8cde"
    readonly property string m_CheckBoxDefault:    "#e0e0e0"
    readonly property string m_CheckBoxPressed:    "#808080"

    // font properties
    readonly property string m_FontFamily: "Arial"

    // skinning properties
    readonly property int m_ConnectorWidth:  14
    readonly property int m_ConnectorHeight: 14

    // interface properties
    property bool m_UseCurvedLines: false
}
