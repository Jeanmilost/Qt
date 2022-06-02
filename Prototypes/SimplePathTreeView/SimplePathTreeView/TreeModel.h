/****************************************************************************
 * ==> TreeModel -----------------------------------------------------------*
 ****************************************************************************
 * Description: Tree model                                                  *
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

// classes
#include "TreeItem.h"

// qt
#include <QObject>
#include <QAbstractListModel>

/**
* Tree model
*@author Jean-Milost Reymond
*/
class TreeModel : public QAbstractListModel
{
    Q_OBJECT

    signals:
        /**
        * Called when an item should be added to the view
        *@param pParentItem - parent item in which item should be added, root item if nullptr
        *@param pItem - newly added item
        */
        void addItemToView(QObject* pParentItem, QObject* pItem);

        /**
        * Called when an item was removed from the view
        *@param pParentItem - parent item owning the item to remove, root item if nullptr
        *@param pItem - removed item
        */
        void removeItemFromView(QObject* pParentItem, QObject* pItem);

    public:
        /**
        * Data roles
        */
        /*REM
        enum class IEDataRole
        {
            IE_DR_ItemName = 0,
            IE_DR_ItemLevel,
            IE_DR_ItemIsCollapsed,
            IE_DR_ItemIsLeaf
        };
        */

        /**
        * Constructor
        *@param pParent - parent object owning this object
        */
        explicit TreeModel(QObject* pParent = nullptr);

        virtual ~TreeModel();

        /**
        * Called when the add item button was clicked on the tree view
        *@param pSelectedItem - selected item, nullptr if no item selected
        *@param level - selected item level, -1 if no item selected
        */
        virtual Q_INVOKABLE void onAddItemClicked(QObject* pSelectedItem, int level);

        /**
        * Called when the delete item button was clicked on the tree view
        *@param pSelectedItem - selected item, nullptr if no item selected
        *@param level - selected item level, -1 if no item selected
        */
        virtual Q_INVOKABLE void onDeleteItemClicked(QObject* pSelectedItem, int level);

        /**
        * Called when a process is double-clicked
        *@param index - item index which was double-clicked
        */
        virtual Q_INVOKABLE void onItemDblClicked(int index);

        /**
        * Clears the view content
        */
        virtual Q_INVOKABLE void clear();

        /**
        * Gets row count
        *@param parent - the parent row index from which the count should be performed
        *@return the row count
        */
        virtual Q_INVOKABLE int rowCount(const QModelIndex& parent = QModelIndex()) const;

        /**
        * Gets data at row index
        *@param index - row index
        *@param role - data role
        *@return the data, empty value if not found or on error
        */
        virtual Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const;

        /**
        * Gets role names
        *@return the role names
        */
        virtual QHash<int, QByteArray> roleNames() const;

        virtual TreeItem* AddItem(TreeItem* pParent, const std::wstring& name);

        virtual void DeleteItem(TreeItem* pItem);

    private:
        typedef std::vector<TreeItem*> IItems;

        IItems m_Items;
};
