/****************************************************************************
 * ==> CFI_BoxProxy --------------------------------------------------------*
 ****************************************************************************
 * Description:  Box proxy between qml view and application engine          *
 * Developer:    Jean-Milost Reymond                                        *
 ****************************************************************************
 * MIT License - Connect Flow Interface                                     *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#pragma once

// classes
#include "CFI_Proxy.h"
#include "CFI_Box.h"

// qt
#include <QObject>

/**
* Box proxy
*@author Jean-Milost Reymond
*/
class CFI_BoxProxy : public CFI_Proxy
{
    Q_OBJECT

    public:
        Q_PROPERTY(QString title       READ getTitle       WRITE setTitle       NOTIFY titleChanged)
        Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged)
        Q_PROPERTY(QString comments    READ getComments    WRITE setComments    NOTIFY commentsChanged)

    public slots:
        /**
        * Gets the box title
        *@return the box title
        */
        virtual QString getTitle() const;

        /**
        * Gets the box description
        *@return the box description
        */
        virtual QString getDescription() const;

        /**
        * Gets the box comments
        *@return the box comments
        */
        virtual QString getComments() const;

        /**
        * Sets the box title
        *@param title - the box title
        */
        virtual void setTitle(const QString& title);

        /**
        * Sets the box description
        *@return the box description
        */
        virtual void setDescription(const QString& description);

        /**
        * Sets the box comments
        *@return the box comments
        */
        virtual void setComments(const QString& comments);

    signals:
        /**
        * Called when the title changed
        *@param title - title
        */
        void titleChanged(const QString& title);

        /**
        * Called when the description changed
        *@param description - description
        */
        void descriptionChanged(const QString& description);

        /**
        * Called when the comments changed
        *@param comments - comments
        */
        void commentsChanged(const QString& comments);

        /**
        * Called when an item is added to the box
        *@param type - item type
        *@param uid - item unique identifier
        */
        void addItemToBox(const QString& type, const QString& uid);

        /**
        * Called when an item should be removed from the box
        *@param type - item type
        *@param uid - item unique identifier to remove
        */
        void removeItemFromBox(const QString& type, const QString& uid);

    public:
        /**
        * Constructor
        *@param pParent - object which will be the parent of this object
        */
        explicit CFI_BoxProxy(QObject* pParent = nullptr);

        virtual ~CFI_BoxProxy();

        /**
        * Gets the linked box
        *@return the linked box, nullptr if no box
        */
        virtual CFI_Box* GetBox() const;

        /**
        * Sets the linked box
        *@param pBox - the linked box
        */
        virtual void SetBox(CFI_Box* pBox);

        /**
        * Adds an item to the box
        *@param type - item type
        *@param uid - item unique identifier
        *@return true on success, otherwise false
        */
        virtual bool AddItem(const QString& type, const QString& uid);

        /**
        * Removes an item from the box
        *@param type - item type
        *@param uid - item unique identifier to remove
        */
        virtual void RemoveItem(const QString& type, const QString& uid);

        /**
        * Notify that an item was added
        *@param success - if true, the item was added successfully
        */
        virtual Q_INVOKABLE void onItemAdded(bool success);

    private:
        CFI_Box* m_pBox      = nullptr;
        bool     m_ItemAdded = false;
};
