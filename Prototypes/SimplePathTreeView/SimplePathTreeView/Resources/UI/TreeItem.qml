import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Templates 2.15 as T

/**
* Generic tree item
*@author Jean-Milost Reymond
*/
Item
{
    // declared properties
    property var    m_Model:           undefined
    property var    m_Item:            ldMain.item
    property var    m_SourceComponent: undefined
    property string m_ID

    // common properties
    id: itItem

    /**
    * Item component
    */
    Component
    {
        // common properties
        id: cpItem

        /**
        * Item column layout
        */
        Column
        {
            // aliases
            property alias children: rpChildren

            // declared properties
            property var m_Content:       ldItem.item
            property int m_Level:         0
            property int m_ChildrenCount: 0

            // common properties
            id: clItem

            /**
            * Item row layout
            */
            Row
            {
                // common properties
                id: rwItem

                /**
                * Item content loader
                */
                Loader
                {
                    // common properties
                    id: ldItem
                    objectName: "ldItem"
                    sourceComponent: itItem.m_SourceComponent
                    width: fcTreeView.width
                    height: fcTreeView.m_ItemHeight

                    /// Called when component is loaded
                    Component.onCompleted:
                    {
                        if (m_Model)
                        {
                            ldItem.item.m_Text  = m_Model.getText(m_ID);
                            ldItem.item.m_Level = m_Level;
                        }
                    }
                }
            }

            onM_LevelChanged:
            {
                ldItem.item.m_Level = m_Level;
            }

            /**
            * Item children repeater
            */
            Repeater
            {
                // common properties
                id: rpChildren
                model: m_ChildrenCount
                delegate: cpItem
            }
        }
    }

    /**
    * Item main loader
    */
    Loader
    {
        // common properties
        id: ldMain
        objectName: "ldMain"
        sourceComponent: cpItem
    }

    function getNb2()
    {
        return m_Item.children.itemAt(1).m_Content;
    }

    function changeNb2(count)
    {
        return m_Item.children.itemAt(2).m_ChildrenCount = count;
    }

    function changeTo5()
    {
        m_Item.m_ChildrenCount = 5;

        for (let i = 0; i < m_Item.children.count; ++i)
            m_Item.children.itemAt(i).m_Level = m_Item.m_Level + 1;
    }
}
