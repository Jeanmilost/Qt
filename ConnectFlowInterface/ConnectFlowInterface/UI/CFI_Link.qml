import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

// javascript
import "js/CFI_JSHelper.js" as JSHelper

// c++
import connectflow.proxys 1.0

/**
* Link (between 2 boxes)
*@author Jean-Milost Reymond
*/
Item
{
    // aliases
    property alias linkProxy:       lpLinkProxy
    property alias titleText:       txTitle
    property alias descriptionText: txDescription
    property alias commentsText:    txComments
    property alias background:      rcBackground

    // advanced properties
    property var    m_From:        undefined // box start connector at which link is attached
    property var    m_To:          undefined // box end connector at which link is attached, if undefined link is dragging
    property var    m_PageContent: undefined
    property var    m_StartPoint:  getStartPoint()
    property var    m_CenterPoint: getCenterPoint()
    property var    m_EndPoint:    getEndPoint()
    property var    m_LabelPos:    Qt.vector2d(m_StartPoint.x + (((m_EndPoint.x - m_StartPoint.x) / 2.0) - (m_LabelSize.x / 2.0)),
                                               m_StartPoint.y + (((m_EndPoint.y - m_StartPoint.y) / 2.0) - (m_LabelSize.y / 2.0)))
    property var    m_LabelSize:   Qt.vector2d(100, 50)
    property var    m_ArrowSize:   Qt.vector2d(3,   10)
    property string m_Color:       Styles.m_LinkBorderColor
    property string m_BgColor:     Styles.m_LinkBgColor
    property string m_TextColor:   Styles.m_DarkTextColor
    property string m_FontFamily:  Styles.m_ComponentFont.m_Family
    property real   m_ScaleFactor: 1
    property int    m_FontSize:    Styles.m_ComponentFont.m_Size
    property int    m_TextMargin:  Styles.m_LinkTextMargin
    property int    m_BorderWidth: Styles.m_LinkBorderWidth
    property int    m_Radius:      Styles.m_LinkRadius
    property bool   m_CurvedLines: Styles.m_UseCurvedLines

    // common properties
    id: itLink
    objectName: "itLink"
    anchors.fill: parent

    // signals
    signal bindTo(var connector)

    /**
    * Link proxy
    *@note This component will auto-create a new c++ CFI_LinkProxy instance
    */
    LinkProxy
    {
        id: lpLinkProxy
        objectName: "lpLinkProxy"
    }

    /**
    * First connection line
    */
    Shape
    {
        // common properties
        id:            shFromLine
        objectName:    "shFromLine"
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        clip:          false
        visible:       !m_CurvedLines

        /**
        * First connection line path
        */
        ShapePath
        {
            // common properties
            id:          spFromLine
            objectName:  "spFromLine"
            strokeColor: m_Color
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      m_StartPoint.x
            startY:      m_StartPoint.y

            /**
            * Line path
            */
            PathLine { x: m_CenterPoint.x; y: m_CenterPoint.y }
        }
    }

    /**
    * Second connection line
    */
    Shape
    {
        // common properties
        id:            shToLine
        objectName:    "shToLine"
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        clip:          false
        visible:       !m_CurvedLines

        /**
        * Second connection line path
        */
        ShapePath
        {
            // common properties
            id:          spToLine
            objectName:  "spToLine"
            strokeColor: m_Color
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      m_CenterPoint.x
            startY:      m_CenterPoint.y

            /**
            * Line path
            */
            PathLine { x: m_EndPoint.x; y: m_EndPoint.y }
        }

        /**
        * Arrow
        */
        ShapePath
        {
            property var m_Dir:    Qt.vector2d(m_EndPoint.x - m_CenterPoint.x, m_EndPoint.y - m_CenterPoint.y).normalized()
            property var m_DirCCW: Qt.vector2d(-m_Dir.y,  m_Dir.x)
            property var m_DirCW:  Qt.vector2d( m_Dir.y, -m_Dir.x)

            // common properties
            id:          spArrow
            objectName:  "spArrow"
            strokeColor: m_Color
            fillColor:   m_Color
            strokeWidth: 1
            startX:      m_CenterPoint.x
            startY:      m_CenterPoint.y

            /**
            * Arrow path
            */
            PathMove { x: m_EndPoint.x; y: m_EndPoint.y }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spArrow.m_Dir.x) + (m_ArrowSize.x * spArrow.m_DirCCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spArrow.m_Dir.y) + (m_ArrowSize.x * spArrow.m_DirCCW.y) }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spArrow.m_Dir.x) + (m_ArrowSize.x * spArrow.m_DirCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spArrow.m_Dir.y) + (m_ArrowSize.x * spArrow.m_DirCW.y)  }
        }
    }

    Shape
    {
        // advanced properties
        property bool m_InvertX:    m_StartPoint.x > m_EndPoint.x
        property bool m_InvertY:    m_StartPoint.y > m_EndPoint.y
        property bool m_FromIsHorz: m_From    ? (m_From.m_Position === CFI_Connector.IEPosition.IE_P_Left || m_From.m_Position === CFI_Connector.IEPosition.IE_P_Right) : false
        property bool m_ToIsHorz:   m_To      ? (m_To.m_Position   === CFI_Connector.IEPosition.IE_P_Left || m_To.m_Position   === CFI_Connector.IEPosition.IE_P_Right) : false
        property int  m_RectLeft:   m_InvertX ? m_EndPoint.x   : m_StartPoint.x
        property int  m_RectTop:    m_InvertY ? m_EndPoint.y   : m_StartPoint.y
        property int  m_RectRight:  m_InvertX ? m_StartPoint.x : m_EndPoint.x
        property int  m_RectBottom: m_InvertY ? m_StartPoint.y : m_EndPoint.y

        // common properties
        id:            shCurvedLine
        objectName:    "shCurvedLine"
        anchors.fill:  parent
        layer.samples: 8
        layer.enabled: true
        smooth:        true
        visible:       m_CurvedLines

        /**
        * Message path
        */
        ShapePath
        {
            // common properties
            id:          spCurvedLine
            objectName:  "spCurvedLine"
            strokeColor: "#202020"
            fillColor:   "transparent"
            strokeWidth: 1
            startX:      shCurvedLine.m_InvertX ? shCurvedLine.m_RectRight  : shCurvedLine.m_RectLeft
            startY:      shCurvedLine.m_InvertY ? shCurvedLine.m_RectBottom : shCurvedLine.m_RectTop

            /**
            * Message curve
            */
            PathCubic
            {
                // common properties
                x:         shCurvedLine.m_InvertX ?  shCurvedLine.m_RectLeft                                                            :  shCurvedLine.m_RectRight
                y:         shCurvedLine.m_InvertY ?  shCurvedLine.m_RectTop                                                             :  shCurvedLine.m_RectBottom
                control1X: shCurvedLine.m_InvertX ? (shCurvedLine.m_FromIsHorz ? shCurvedLine.m_RectLeft   : shCurvedLine.m_RectRight)  : (shCurvedLine.m_FromIsHorz ? shCurvedLine.m_RectRight  : shCurvedLine.m_RectLeft)
                control1Y: shCurvedLine.m_InvertY ? (shCurvedLine.m_FromIsHorz ? shCurvedLine.m_RectBottom : shCurvedLine.m_RectTop)    : (shCurvedLine.m_FromIsHorz ? shCurvedLine.m_RectTop    : shCurvedLine.m_RectBottom)
                control2X: shCurvedLine.m_InvertX ? (shCurvedLine.m_ToIsHorz   ? shCurvedLine.m_RectRight  : shCurvedLine.m_RectLeft)   : (shCurvedLine.m_ToIsHorz   ? shCurvedLine.m_RectLeft   : shCurvedLine.m_RectRight)
                control2Y: shCurvedLine.m_InvertY ? (shCurvedLine.m_ToIsHorz   ? shCurvedLine.m_RectTop    : shCurvedLine.m_RectBottom) : (shCurvedLine.m_ToIsHorz   ? shCurvedLine.m_RectBottom : shCurvedLine.m_RectTop)
            }
        }

        /**
        * Arrow
        */
        ShapePath
        {
            property var m_Dir:    Qt.vector2d(shCurvedLine.m_ToIsHorz ?       (shCurvedLine.m_InvertX ? -1.0 : 1.0) : 0.0,
                                               shCurvedLine.m_ToIsHorz ? 0.0 : (shCurvedLine.m_InvertY ? -1.0 : 1.0))
            property var m_DirCCW: Qt.vector2d(-m_Dir.y,  m_Dir.x)
            property var m_DirCW:  Qt.vector2d( m_Dir.y, -m_Dir.x)

            // common properties
            id:          spCurvedLineArrow
            objectName:  "spCurvedLineArrow"
            strokeColor: m_Color
            fillColor:   m_Color
            strokeWidth: 1
            startX:      m_CenterPoint.x
            startY:      m_CenterPoint.y

            /**
            * Arrow path
            */
            PathMove { x: m_EndPoint.x; y: m_EndPoint.y }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spCurvedLineArrow.m_Dir.x) + (m_ArrowSize.x * spCurvedLineArrow.m_DirCCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spCurvedLineArrow.m_Dir.y) + (m_ArrowSize.x * spCurvedLineArrow.m_DirCCW.y) }
            PathLine { x: m_EndPoint.x - (m_ArrowSize.y * spCurvedLineArrow.m_Dir.x) + (m_ArrowSize.x * spCurvedLineArrow.m_DirCW.x)
                       y: m_EndPoint.y - (m_ArrowSize.y * spCurvedLineArrow.m_Dir.y) + (m_ArrowSize.x * spCurvedLineArrow.m_DirCW.y)  }
        }
    }

    /**
    * Background
    */
    Rectangle
    {
        // advanced properties
        property int m_MouseStartX: 0
        property int m_MouseStartY: 0

        // common properties
        id:         rcBackground
        objectName: "rcBackground"
        x:          m_LabelPos.x
        y:          m_LabelPos.y
        width:      m_LabelSize.x
        height:     m_LabelSize.y
        color:      "transparent"
        visible:    m_From !== undefined && m_To !== undefined

        // signals
        signal moveStart()
        signal move(int deltaX, int deltaY)
        signal moveEnd()
        signal resize(int direction, int deltaX, int deltaY)
        signal dblClick()

        /**
        * Handle control
        */
        CFI_HandleControl
        {
            // common properties
            id:           hcBackground
            objectName:   "hcBackground"
            anchors.fill: parent
            z:            rcBackground.activeFocus ? 0 : -1

            // advanced properties
            m_HandleVisible: rcBackground.activeFocus
            m_Target: rcBackground

            // aliases
            handleBackground.border.color: m_Color
        }

        /**
        * Link content
        */
        Rectangle
        {
            // common properties
            id:           rcContent
            objectName:   "rcContent"
            anchors.fill: parent
            color:        m_BgColor
            border.color: m_Color
            border.width: m_BorderWidth
            radius:       m_Radius
            z:            rcBackground.activeFocus ? -1 : 0
            clip:         true

            /**
            * Title
            */
            Text
            {
                // common properties
                id:                  txTitle
                objectName:          "txTitle"
                text:                lpLinkProxy.title
                anchors.left:        parent.left
                anchors.leftMargin:  m_TextMargin
                anchors.top:         parent.top
                anchors.topMargin:   m_TextMargin
                anchors.right:       parent.right
                anchors.rightMargin: m_TextMargin
                font.family:         m_FontFamily
                font.pointSize:      m_FontSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:   Text.AlignVCenter
                wrapMode:            Text.WordWrap
                color:               m_TextColor
                clip:                true
            }

            /**
            * Description
            */
            Text
            {
                // common properties
                id:                  txDescription
                objectName:          "txDescription"
                text:                lpLinkProxy.description
                anchors.left:        parent.left
                anchors.leftMargin:  m_TextMargin
                anchors.top:         txTitle.bottom
                anchors.right:       parent.right
                anchors.rightMargin: m_TextMargin
                font.family:         m_FontFamily
                font.pointSize:      m_FontSize
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment:   Text.AlignVCenter
                wrapMode:            Text.WordWrap
                color:               m_TextColor
                clip:                true
            }

            /**
            * Comments
            */
            Text
            {
                // common properties
                id:                   txComments
                objectName:           "txComments"
                text:                 lpLinkProxy.comments
                anchors.left:         parent.left
                anchors.leftMargin:   m_TextMargin
                anchors.top:          txDescription.bottom
                anchors.right:        parent.right
                anchors.rightMargin:  m_TextMargin
                font.family:          m_FontFamily
                font.pointSize:       m_FontSize
                horizontalAlignment:  Text.AlignHCenter
                verticalAlignment:    Text.AlignVCenter
                wrapMode:             Text.WordWrap
                color:                m_TextColor
                clip:                 true
            }

            /**
            * Link mouse area
            */
            MouseArea
            {
                // common properties
                id: maMouseArea
                objectName: "maMouseArea"
                anchors.fill: parent

                /// called when the view is clicked
                onClicked:
                {
                    rcBackground.forceActiveFocus();
                }
            }
        }

        /// called when box starts to move
        onMoveStart: function()
        {
            m_MouseStartX = x;
            m_MouseStartY = y;
        }

        /// called when box is moving
        onMove: function(deltaX, deltaY)
        {
            if (!m_PageContent)
                return;

            // move box and limit it in owning page
            x += deltaX;
            x  = JSHelper.clamp(x, 0, m_PageContent.width - width);
            y += deltaY;
            y  = JSHelper.clamp(y, 0, m_PageContent.height - height);

            const linkX      = x      * m_ScaleFactor;
            const linkY      = y      * m_ScaleFactor;
            const linkWidth  = width  * m_ScaleFactor;
            const linkHeight = height * m_ScaleFactor;

            // notify that auto-scroll may be applied
            m_PageContent.doAutoScroll(linkX, linkX + linkWidth, linkY, linkY + linkHeight);
        }

        /// called when box ends to move
        onMoveEnd: function()
        {
            // was control dragged?
            if (Math.abs(x - m_MouseStartX) >= 5 || Math.abs(y - m_MouseStartY) >= 5)
                return;

            if (m_PageContent)
                m_PageContent.doDisableMoveSize(this);
        }

        /// called when box should be resized
        onResize: function(direction, deltaX, deltaY)
        {
            // resize box width
            if (deltaX)
                switch (direction)
                {
                    case CFI_Handle.IEDirection.IE_D_Left:
                    case CFI_Handle.IEDirection.IE_D_LeftTop:
                    case CFI_Handle.IEDirection.IE_D_LeftBottom:
                        x     += deltaX;
                        width -= deltaX;

                        if (x < 0 || width < 30)
                        {
                            x     -= deltaX;
                            width += deltaX;
                        }

                        break;

                    case CFI_Handle.IEDirection.IE_D_Right:
                    case CFI_Handle.IEDirection.IE_D_RightTop:
                    case CFI_Handle.IEDirection.IE_D_RightBottom:
                        width += deltaX;

                        if (width < 30)
                            width -= deltaX;

                        break;
                }

            // resize box height
            if (deltaY)
                switch (direction)
                {
                    case CFI_Handle.IEDirection.IE_D_Top:
                    case CFI_Handle.IEDirection.IE_D_LeftTop:
                    case CFI_Handle.IEDirection.IE_D_RightTop:
                        y      += deltaY;
                        height -= deltaY;

                        if (y < 0 || height < 30)
                        {
                            y      -= deltaY;
                            height += deltaY;
                        }

                        break;

                    case CFI_Handle.IEDirection.IE_D_Bottom:
                    case CFI_Handle.IEDirection.IE_D_LeftBottom:
                    case CFI_Handle.IEDirection.IE_D_RightBottom:
                        height += deltaY;

                        if (height < 30)
                            height -= deltaY;

                        break;
                }
        }

        /// Called when link label is double clicked
        onDblClick: function()
        {}
    }

    /**
    * Signal connectors
    */
    Connections
    {
        target: pageContent

        /**
        * Called when the page scale factor changed
        *@param {number} factor - scale factor
        */
        function onPageScaleChanged(factor)
        {
            m_ScaleFactor = factor;
        }
    }

    /**
    * Box proxy signal connections
    */
    Connections
    {
        // common properties
        target: lpLinkProxy

        /**
        * Called when the title changed
        *@param title - new title
        */
        function onTitleChanged(title)
        {
            if (!txTitle.visible)
                return;

            txTitle.text = title;
        }

        /**
        * Called when the description changed
        *@param description - new description
        */
        function onDescriptionChanged(description)
        {
            if (!txDescription.visible)
                return;

            txDescription.text = description;
        }

        /**
        * Called when the comments changed
        *@param comments - new comments
        */
        function onCommentsChanged(comments)
        {
            if (!txComments.visible)
                return;

            txComments.text = comments;
        }
    }

    /**
    * Called when the from connector changed
    */
    onM_FromChanged:
    {
        //console.log("onM_FromChanged");
        bindLinkToSrcBox();
    }

    /**
    * Called when the to connector changed
    */
    onM_ToChanged:
    {
        //console.log("onM_ToChanged");
        bindLinkToDstBox();
    }

    /**
    * Called when a connector should be binded to this link
    *@param {CFI_Connector} connector - connector to which this link should be binded
    */
    onBindTo: function(connector)
    {
        //console.log("onBindTo - " + connector.objectName + " - " + connector.m_Box.boxProxy.uid);

        if (!connector)
            return;

        // set the new connector
        m_To = connector;
    }

    /**
    * Bind link to source box
    */
    function bindLinkToSrcBox()
    {
        // from connector should be defined
        if (!m_From)
            return;

        // unbind link from parent box, if previously binded
        unbindLinkFromBox(m_From.m_Box);
        m_From.m_Links.push(this);
    }

    /**
    * Bind link to destination box
    */
    function bindLinkToDstBox()
    {
        // to connector should be defined
        if (!m_To)
            return;

        // unbind link from parent box, if previously binded
        unbindLinkFromBox(m_To.m_Box);
        m_To.m_Links.push(this);
    }

    /**
    * Unbinds a link from a box
    *@param {CFI_Box} box - box for which the link should be unbind
    */
    function unbindLinkFromBox(box)
    {
        if (!box)
            return 0;

        // remove all existing link instance from left connector
        for (let i = box.leftConnector.m_Links.length - 1; i >= 0; --i)
            if (box.leftConnector.m_Links[i] === this)
                box.leftConnector.m_Links.splice(i, 1);

        // remove all existing link instance from top connector
        for (let i = box.topConnector.m_Links.length - 1; i >= 0; --i)
            if (box.topConnector.m_Links[i] === this)
                box.topConnector.m_Links.splice(i, 1);

        // remove all existing link instance from right connector
        for (let i = box.rightConnector.m_Links.length - 1; i >= 0; --i)
            if (box.rightConnector.m_Links[i] === this)
                box.rightConnector.m_Links.splice(i, 1);

        // remove all existing link instance from bottom connector
        for (let i = box.bottomConnector.m_Links.length - 1; i >= 0; --i)
            if (box.bottomConnector.m_Links[i] === this)
                box.bottomConnector.m_Links.splice(i, 1);
    }

    /**
    * Gets the start point
    *@return the start point in pixels, empty point on error
    */
    function getStartPoint()
    {
        // from connector should be defined
        if (!m_From)
            return Qt.vector2d(0.0, 0.0);

        return getPoint(m_From);
    }

    /**
    * Gets the end point
    *@return the end point in pixels, empty point on error
    */
    function getEndPoint()
    {
        // to connector should be defined
        if (!m_To)
        {
            // link is dragging, get mouse position from start connector
            if (m_From)
            {
                // get the delta between the connector and its parent box
                const startDelta = getStartDelta(m_From);

                return Qt.vector2d(m_From.m_Box.x + m_From.connectorMouseArea.mouseX + startDelta.x,
                                   m_From.m_Box.y + m_From.connectorMouseArea.mouseY + startDelta.y);
            }

            return Qt.vector2d(0.0, 0.0);
        }

        return getPoint(m_To);
    }

    /**
    * Gets the center point
    *@return the center point on y axis in pixels, empty point on error
    */
    function getCenterPoint()
    {
        return Qt.vector2d(rcBackground.x + (rcBackground.width  / 2.0),
                           rcBackground.y + (rcBackground.height / 2.0));
    }

    /**
    * Gets the point centered in the connector
    *@param {CFI_Connector} connector - the connector for which the center point should be get
    *@return the point centered in the connector in pixels, empty point on error
    */
    function getPoint(connector)
    {
        // connector should be defined
        if (!connector)
            return Qt.vector2d(0.0, 0.0);

        // get the connector parent box
        const box = connector.m_Box;

        // parent box should always be defined in the connector
        if (!box)
            return Qt.vector2d(0.0, 0.0);

        // get the connector center point
        switch (connector.m_Position)
        {
            case CFI_Connector.IEPosition.IE_P_Left:
                return Qt.vector2d(box.x + (connector.x + (connector.width / 2)),
                                   box.y + (box.rectConnectors.height      / 2));

            case CFI_Connector.IEPosition.IE_P_Right:
                return Qt.vector2d(box.x +  connector.x + (connector.width / 2),
                                   box.y + (box.rectConnectors.height      / 2));

            case CFI_Connector.IEPosition.IE_P_Top:
                return Qt.vector2d(box.x + (box.rectConnectors.width        / 2),
                                   box.y + (connector.y + (connector.height / 2)));

            case CFI_Connector.IEPosition.IE_P_Bottom:
                return Qt.vector2d(box.x + (box.rectConnectors.width        / 2),
                                   box.y +  connector.y + (connector.height / 2));

            default:
                console.log("getPoint - unknown connector position - " + connector.m_Position);
                return Qt.vector2d(0.0, 0.0);
        }
    }

    /**
    * Gets the start delta to apply to mouse position
    *@param {CFI_Connector} connector - connector from which the start delta should be calculated
    *@return the start delta in pixels, empty point on error
    */
    function getStartDelta(connector)
    {
        // connector should be defined
        if (!connector)
            return Qt.vector2d(0.0, 0.0);

        // get the connector parent box
        const box = connector.m_Box;

        // parent box should always be defined in the connector
        if (!box)
            return Qt.vector2d(0.0, 0.0);

        // get the connector center point
        switch (connector.m_Position)
        {
            case CFI_Connector.IEPosition.IE_P_Left:
                return Qt.vector2d(connector.x, (box.rectConnectors.height / 2) - (connector.height / 2));

            case CFI_Connector.IEPosition.IE_P_Right:
                return Qt.vector2d(connector.x, (box.rectConnectors.height / 2) - (connector.height / 2));

            case CFI_Connector.IEPosition.IE_P_Top:
                return Qt.vector2d((box.rectConnectors.width  / 2) - (connector.width  / 2), connector.y);

            case CFI_Connector.IEPosition.IE_P_Bottom:
                return Qt.vector2d((box.rectConnectors.width  / 2) - (connector.width  / 2), connector.y);

            default:
                console.log("getStartDelta - unknown connector position - " + connector.m_Position);
                return Qt.vector2d(0.0, 0.0);
        }
    }
}
