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

#include "TreeModel.h"

// std
#include <sstream>

// qt
#include <QQuickItem>

// windows
#include <Windows.h>

//---------------------------------------------------------------------------
// TreeModel
//---------------------------------------------------------------------------
TreeModel::TreeModel(QObject* pParent) :
    QAbstractListModel(pParent)
{}
//---------------------------------------------------------------------------
TreeModel::~TreeModel()
{
    for each (auto pItem in m_Items)
        delete pItem;
}
//---------------------------------------------------------------------------
void TreeModel::onAddItemClicked(QObject* pSelectedItem, int level)
{
    // get the parent to add to and add new item
    TreeItem* pParent = static_cast<TreeItem*>(pSelectedItem);
    TreeItem* pItem   = AddItem(pParent, L"Item XXX");

    if (!pItem)
    {
        // todo -cFeature -oJean: log error
        return;
    }

    const std::wstring name; // = OnGetItemName();
    pItem->setName(QString::fromStdWString(name));
}
//---------------------------------------------------------------------------
void TreeModel::onDeleteItemClicked(QObject* pSelectedItem, int level)
{
    if (!pSelectedItem)
        return;

    TreeItem* pItem = static_cast<TreeItem*>(pSelectedItem);
    DeleteItem(pItem);
}
//---------------------------------------------------------------------------
void TreeModel::onItemDblClicked(int index)
{}
//---------------------------------------------------------------------------
void TreeModel::clear()
{
    beginResetModel();

    // clear the model
    for each (auto pItem in m_Items)
        delete pItem;

    endResetModel();
}
//---------------------------------------------------------------------------
int TreeModel::rowCount(const QModelIndex& parent) const
{
    // return only the root item count because on the view the children are added to existing items
    return m_Items.size();
}
//---------------------------------------------------------------------------
QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> TreeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    /*REM
    roles[(int)TreeModel::IEDataRole::IE_DR_ItemName]        = "itemName";
    roles[(int)TreeModel::IEDataRole::IE_DR_ItemLevel]       = "itemLevel";
    roles[(int)TreeModel::IEDataRole::IE_DR_ItemIsCollapsed] = "itemIsCollapsed";
    roles[(int)TreeModel::IEDataRole::IE_DR_ItemIsLeaf]      = "itemIsLeaf";
    */

    return roles;
}
//---------------------------------------------------------------------------
TreeItem* TreeModel::AddItem(TreeItem* pParent, const std::wstring& name)
{
    TreeItem* pItem     = nullptr;
    const int itemCount = m_Items.size();

    beginInsertRows(QModelIndex(), itemCount, itemCount);

    try
    {
        // is a root item?
        if (!pParent)
        {
            // create a root item and add it to list
            std::unique_ptr<TreeItem> pRoot = std::make_unique<TreeItem>(name);
            m_Items.push_back(pRoot.get());
            pItem = pRoot.release();
        }
        else
            // create a child item
            pItem = pParent->Add(name);

        // notify view that a new item was added
        emit addItemToView(pParent, pItem);
    }
    catch (...)
    {
        // todo -cFeature -oJean: Log the error
    }

    endInsertRows();

    return pItem;
}
//---------------------------------------------------------------------------
void TreeModel::DeleteItem(TreeItem* pItem)
{
    if (!pItem)
        return;

    // notify view that an item is about to be removed
    emit removeItemFromView(pItem->GetParent(), pItem);

    for (std::size_t i = 0; i < m_Items.size(); ++i)
    {
        if (m_Items[i] == pItem)
        {
            const int itemCount = m_Items.size();

            // notify interface only for root items, because only they have a corresponding
            // item in the ListView
            beginRemoveRows(QModelIndex(), itemCount - 1, itemCount - 1);
            delete m_Items[i];
            m_Items.erase(m_Items.begin() + i);
            endRemoveRows();

            return;
        }

        if (m_Items[i]->Delete(pItem))
            return;
    }
}
//---------------------------------------------------------------------------
