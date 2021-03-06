/****************************************************************************
 * ==> TreeItem ------------------------------------------------------------*
 ****************************************************************************
 * Description: Tree item                                                   *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - The Simple Path                                            *
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

// std
#include <vector>
#include <string>

// qt
#include <QObject>

/**
* Tree item
*@author Jean-Milost Reymond
*/
class TreeItem : public QObject
{
    Q_OBJECT

    public:
        Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(QString uid  READ getUID)

    public slots:
        /**
        * Gets the item name
        *@return the item name
        */
        QString getName() const;

        /**
        * Sets the item name
        *@param name - the item name
        */
        void setName(const QString& name);

        /**
        * Gets the unique identifier
        *@return the unique identifier
        */
        QString getUID() const;

    signals:
        /**
        * Called when an item should be added to the view
        *@param pParentItem - parent item in which item should be added, root item if nullptr
        *@param pItem - newly added item
        */
        void addItemToView(QObject* pParentItem, QObject* pItem);

        /**
        * Called when the name changed
        *@param name - name
        */
        void nameChanged(const QString& name);

    public:
        TreeItem();

        /**
        * Constructor
        *@param name - item name
        */
        TreeItem(const std::wstring& name);

        virtual ~TreeItem();

        /**
        * Gets the item parent
        *@return the item parent, nullptr if no parent
        */
        virtual TreeItem* GetParent() const;

        /**
        * Adds an item as a child of this item
        *@return newly added tree item, nullptr on error
        */
        virtual TreeItem* Add();

        /**
        * Adds an item as a child of this item
        *@param name - item name
        *@return newly added tree item, nullptr on error
        */
        virtual TreeItem* Add(const std::wstring& name);

        /**
        * Deletes a child item from this item
        *@param pItem - child item to delete
        *@param recursive - if true, the item to delete will also be searched in the children items
        *@return true on success, otherwise false
        */
        virtual bool Delete(TreeItem* pItem, bool recursive = true);

        /**
        * Deletes all children
        */
        virtual void DeleteAll();

        /**
        * Gets the child item at index
        *@return the child item at index, nullptr if not found or on error
        */
        virtual TreeItem* GetChildAt(std::size_t index) const;

        /**
        * Gets the child count
        *@return the child count
        */
        virtual std::size_t GetChildCount() const;

    private:
        typedef std::vector<TreeItem*> IChildren;

        std::wstring m_Name;
        TreeItem*    m_pParent = nullptr;
        IChildren    m_Children;
};
