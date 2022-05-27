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
        *@param parentId - parent item identifier in which item should be added
        *@param id - newly added item identifier
        */
        void addItemToView(const QString& parentId, const QString& id);

    public:
        /**
        * Data roles
        */
        enum class IEDataRole
        {
            IE_DR_ItemName = 0,
            IE_DR_ItemLevel,
            IE_DR_ItemIsCollapsed,
            IE_DR_ItemIsLeaf
        };

        /**
        * Constructor
        *@param pParent - parent object owning this object
        */
        explicit TreeModel(QObject* pParent = nullptr);

        virtual ~TreeModel();

        TreeItem* AddItem(TreeItem* pParent, const std::wstring& name);

        void DeleteItem(TreeItem* pItem);

        /**
        * Called when the add item button was clicked on the tree view
        *@param parentIndex - item index which will own the new item
        */
        virtual Q_INVOKABLE void onAddItemClicked(int parentIndex);

        /**
        * Called when the delete item button was clicked on the tree view
        *@param index - item index to delete
        */
        virtual Q_INVOKABLE void onDeleteItemClicked(int index);

        /**
        * Called when a process is double-clicked
        *@param index - item index which was double-clicked
        */
        virtual Q_INVOKABLE void onItemDblClicked(int index);

        /**
        * Clears the view content
        */
        virtual Q_INVOKABLE void clear();

        virtual Q_INVOKABLE QString getText(const QString& id) const;

        /**
        * Adds an item
        *@param parentIndex - item index which will own the new item
        *@return true on success, otherwise false
        */
        //REM virtual Q_INVOKABLE bool addItem(int parentIndex);

        /**
        * Deletes an item
        *@param index - item index to delete
        *@return true on success, otherwise false
        */
        //REM virtual Q_INVOKABLE bool deleteItem(int index);

        /**
        * Checks if an item is a leaf
        *@param index - item index
        *@return true if the item is a leaf, otherwise false
        */
        virtual Q_INVOKABLE bool isLeaf(int index) const;

        /**
        * Sets the item as collapsed
        *@param index - item index
        *@param value - if true, item is collapsed
        */
        virtual Q_INVOKABLE void setCollapsed(int index, bool value);

        /**
        * Checks if item is collapsed
        *@param index - item index
        *@return true if item is collapsed, otherwise false
        */
        virtual Q_INVOKABLE bool isCollapsed(int index) const;

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

    private:
        typedef std::vector<TreeItem*> IItems;

        IItems m_Items;

        /*REM
        class ItemList
        {
            public:
                ItemList();
                ~ItemList();

                void SetRootName(const std::wstring& name);

                TreeItem* Add(int index);
                TreeItem* Add(TreeItem* pItem);

                void Delete(int index);
                void Delete(TreeItem* pItem);

                / **
                * Deletes all items
                * /
                void DeleteAll();

                TreeItem* GetItem(int index);

                int GetIndex(TreeItem* pItem);

                QVariant GetData(const QModelIndex& index, int role) const;

                std::size_t GetRootCount() const;
                std::size_t GetCount(int parentIndex) const;

                / **
                * Checks if an item is a leaf
                *@param index - item index
                *@return true if the item is a leaf, otherwise false
                * /
                bool IsLeaf(int index) const;

                / **
                * Sets the item as collapsed
                *@param index - item index
                *@param value - if true, item is collapsed
                * /
                void SetCollapsed(int index, bool value);

                / **
                * Checks if item is collapsed
                *@param index - item index
                *@return true if item is collapsed, otherwise false
                * /
                bool IsCollapsed(int index) const;

                #ifdef _DEBUG
                    void LogToOutput() const;
                #endif

            private:
                TreeItem m_Root;

                const TreeItem* GetItem(int index, const TreeItem* pCurrent, std::size_t& count) const;

                int GetIndex(TreeItem* pItem, TreeItem* pCurrent, std::size_t& count) const;

                void GetCount(const TreeItem* pCurrent, std::size_t& count) const;

                #ifdef _DEBUG
                    void LogToOutput(const TreeItem* pCurrent) const;
                #endif
        };
        */

        //REM TreeItem    m_Root;
        //REM ItemList    m_ItemList;
        //REM std::size_t m_ItemGenCount = 0;

        //REM TreeItem* IndexToItem(int index, std::size_t& count, TreeItem* pItem = nullptr);

        //REM int ItemToIndex(TreeItem* pItem, TreeItem* pCurrent, std::size_t& count);

        /*REM
        TreeItem* GetFirst();
        TreeItem* GetLast();
        TreeItem* GetPrev(TreeItem* pItem);
        TreeItem* GetNext(TreeItem* pItem);
        */
        //REM TreeItem* GetAt(int index, std::size_t& count);

        std::wstring GetText(const TreeItem* pItem, const std::string& id) const;

        /**
        * Gets the item count (including all children)
        *@return the item count
        */
        std::size_t GetItemCount() const;

        /**
        * Gets the item children count
        *@param pItem - item from which children should be counted
        *@return the item children count
        */
        std::size_t GetChildrenCount(const TreeItem* pItem) const;
};
