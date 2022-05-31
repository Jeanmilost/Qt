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
// TreeModel::ItemList
//---------------------------------------------------------------------------
/*REM
TreeModel::ItemList::ItemList()
{}
*/
//---------------------------------------------------------------------------
/*REM
TreeModel::ItemList::~ItemList()
{
    m_Root.DeleteAll();
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::SetRootName(const std::wstring& name)
{
    m_Root.SetName(name);
}
*/
//---------------------------------------------------------------------------
/*REM
TreeItem* TreeModel::ItemList::Add(int index)
{
    TreeItem* pParent = GetItem(index);

    if (!pParent)
        return nullptr;

    return pParent->Add();
}
*/
//---------------------------------------------------------------------------
/*REM
TreeItem* TreeModel::ItemList::Add(TreeItem* pItem)
{
    if (!pItem)
        return nullptr;

    return pItem->Add();
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::Delete(int index)
{
    Delete(GetItem(index));
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::Delete(TreeItem* pItem)
{
    if (!pItem)
        return;

    TreeItem* pParent = pItem->GetParent();

    if (!pParent)
        return;

    pParent->Delete(pItem, false);
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::DeleteAll()
{
    m_Root.DeleteAll();
}
*/
//---------------------------------------------------------------------------
/*REM
TreeItem* TreeModel::ItemList::GetItem(int index)
{
    std::size_t count = 0;

    return const_cast<TreeItem*>(GetItem(index, &m_Root, count));
}
*/
//---------------------------------------------------------------------------
/*REM
int TreeModel::ItemList::GetIndex(TreeItem* pItem)
{
    std::size_t count = 0;

    return GetIndex(pItem, &m_Root, count);
}
*/
//---------------------------------------------------------------------------
/*REM
QVariant TreeModel::ItemList::GetData(const QModelIndex& index, int role) const
{
          std::size_t count = 0;
    const TreeItem*   pItem = GetItem(index.row(), &m_Root, count);

    if (!pItem)
        return QVariant();

    // search for item data role to get
    switch ((TreeModel::IEDataRole)role)
    {
        case TreeModel::IEDataRole::IE_DR_ItemName:
            return QString::fromStdWString(pItem->GetName());

        case TreeModel::IEDataRole::IE_DR_ItemLevel:
            return pItem->GetLevel();

        case TreeModel::IEDataRole::IE_DR_ItemIsCollapsed:
            return pItem->IsCollapsed();

        case TreeModel::IEDataRole::IE_DR_ItemIsLeaf:
            return pItem->IsLeaf();
    }

    return QVariant();
}
*/
//---------------------------------------------------------------------------
/*REM
std::size_t TreeModel::ItemList::GetRootCount() const
{
    std::size_t count = 0;

    GetCount(&m_Root, count);

    return count;
}
*/
//---------------------------------------------------------------------------
/*REM
std::size_t TreeModel::ItemList::GetCount(int parentIndex) const
{
    if (parentIndex < 0)
        return GetRootCount();

          std::size_t count = 0;
    const TreeItem*   pItem = GetItem(parentIndex, &m_Root, count);

    if (!pItem)
        return GetRootCount();

    count = 0;

    GetCount(pItem, count);

    return count;
}
*/
//---------------------------------------------------------------------------
/*REM
bool TreeModel::ItemList::IsLeaf(int index) const
{
          std::size_t count = 0;
    const TreeItem*   pItem = GetItem(index, &m_Root, count);

    if (!pItem)
        return false;

    return pItem->IsLeaf();
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::SetCollapsed(int index, bool value)
{
    std::size_t count = 0;
    TreeItem*   pItem = const_cast<TreeItem*>(GetItem(index, &m_Root, count));

    if (!pItem)
        return;

    pItem->SetCollapsed(value);
}
*/
//---------------------------------------------------------------------------
/*REM
bool TreeModel::ItemList::IsCollapsed(int index) const
{
          std::size_t count = 0;
    const TreeItem*   pItem = GetItem(index, &m_Root, count);

    if (!pItem)
        return false;

    return pItem->IsCollapsed();
}
*/
//---------------------------------------------------------------------------
/*REM
#ifdef _DEBUG
    void TreeModel::ItemList::LogToOutput() const
    {
        LogToOutput(&m_Root);
    }
#endif
*/
//---------------------------------------------------------------------------
/*REM
const TreeItem* TreeModel::ItemList::GetItem(int index, const TreeItem* pCurrent, std::size_t& count) const
{
    if (index == count)
        return pCurrent;

    ++count;

    const std::size_t childCount = pCurrent->GetChildCount();

    for (std::size_t i = 0; i < childCount; ++i)
    {
        const TreeItem* pFound = GetItem(index, pCurrent->GetChildAt(i), count);

        if (pFound)
            return pFound;
    }

    return nullptr;
}
*/
//---------------------------------------------------------------------------
/*REM
int TreeModel::ItemList::GetIndex(TreeItem* pItem, TreeItem* pCurrent, std::size_t& count) const
{
    if (pItem == pCurrent)
        return count;

    ++count;

    const std::size_t childCount = pCurrent->GetChildCount();

    for (std::size_t i = 0; i < childCount; ++i)
    {
        const int found = GetIndex(pItem, pCurrent->GetChildAt(i), count);

        if (found >= 0)
            return found;
    }

    return -1;
}
*/
//---------------------------------------------------------------------------
/*REM
void TreeModel::ItemList::GetCount(const TreeItem* pCurrent, std::size_t& count) const
{
    ++count;

    const std::size_t childCount = pCurrent->GetChildCount();

    for (std::size_t i = 0; i < childCount; ++i)
        GetCount(pCurrent->GetChildAt(i), count);
}
*/
//---------------------------------------------------------------------------
/*REM
#ifdef _DEBUG
    void TreeModel::ItemList::LogToOutput(const TreeItem* pCurrent) const
    {
        const std::size_t level = pCurrent->GetLevel();

        std::wostringstream sstr;

        for (std::size_t i = 0; i < level; ++i)
            sstr << L"  ";

        sstr << L"(" << level << L") - " << pCurrent->GetName() << L"\r\n";

        ::OutputDebugString(sstr.str().c_str());

        const std::size_t childCount = pCurrent->GetChildCount();

        for (std::size_t i = 0; i < childCount; ++i)
            LogToOutput(pCurrent->GetChildAt(i));
    }
#endif
*/
//---------------------------------------------------------------------------
// TreeModel
//---------------------------------------------------------------------------
TreeModel::TreeModel(QObject* pParent) :
    QAbstractListModel(pParent)//REM,
    //REM m_pRoot(new TreeItem())
{
    //REM m_ItemList.SetRootName(L"Root");
}
//---------------------------------------------------------------------------
TreeModel::~TreeModel()
{
    /*REM
    if (m_pRoot)
        delete m_pRoot;
    */
    for each (auto pItem in m_Items)
        delete pItem;
}
//---------------------------------------------------------------------------
TreeItem* TreeModel::AddItem(TreeItem* pParent, const std::wstring& name)
{
          TreeItem* pNewItem  = nullptr;
    const int       itemCount = GetItemCount();

    beginInsertRows(QModelIndex(), itemCount, itemCount);

    try
    {
        if (!pParent)
        {
            std::unique_ptr<TreeItem> pItem = std::make_unique<TreeItem>(name);
            m_Items.push_back(pItem.get());
            pNewItem = pItem.release();

            emit addItemToView(nullptr, pNewItem);
        }
        else
        {
            pNewItem = pParent->Add(name);

            emit addItemToView(pParent, pNewItem);
        }
    }
    catch (...)
    {}

    endInsertRows();

    return pNewItem;
}
//---------------------------------------------------------------------------
void TreeModel::DeleteItem(TreeItem* pItem)
{
    //beginRemoveRows();
    //endRemoveRows();

    for (std::size_t i = 0; i < m_Items.size(); ++i)
    {
        if (m_Items[i] == pItem)
        {
            delete m_Items[i];
            m_Items.erase(m_Items.begin() + i);
            return;
        }

        if (m_Items[i]->Delete(pItem))
            return;
    }
}
//---------------------------------------------------------------------------
void TreeModel::onAddItemClicked(int parentIndex)
{
    //REM addItem(parentIndex);
}
//---------------------------------------------------------------------------
void TreeModel::onDeleteItemClicked(int index)
{
    //REM deleteItem(index);
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
QString TreeModel::getText(const QString& id) const
{
    const std::string itemId = id.toStdString();

    for each (auto pItem in m_Items)
    {
        const std::wstring text = GetText(pItem, itemId);

        if (!text.empty())
            return QString::fromStdWString(text);
    }

    return QString();
}
//---------------------------------------------------------------------------
/*REM
bool TreeModel::addItem(int parentIndex)
{
    TreeItem* pParent = m_ItemList.GetItem(parentIndex);

    if (!pParent)
        return false;

    const int childCount = m_ItemList.GetCount(parentIndex);

    // add item to view
    beginInsertRows(QModelIndex(), parentIndex + childCount, parentIndex + childCount);

    // create a new item
    TreeItem* pItem = m_ItemList.Add(pParent);

    if (pItem)
    {
        // build item name
        std::wostringstream sstr;
        sstr << L"Item";

        if (m_ItemGenCount)
            sstr << L" (" << m_ItemGenCount << L")";

        pItem->SetName(sstr.str());

        ++m_ItemGenCount;
    }

    endInsertRows();

    emit treeContentChanged(parentIndex);

    #ifdef _DEBUG
        m_ItemList.LogToOutput();
    #endif

    return true;
}
*/
//---------------------------------------------------------------------------
/*REM
bool TreeModel::deleteItem(int index)
{
    // root item or invalid item
    if (index <= 0)
        return false;

    TreeItem* pItem = m_ItemList.GetItem(index);

    if (!pItem)
        return false;

    const int parentIndex = m_ItemList.GetIndex(pItem->GetParent());

    // single item to release?
    if (pItem->IsLeaf())
        // remove item from view
        beginRemoveRows(QModelIndex(), index, index);
    else
    {
        const int childCount = m_ItemList.GetCount(index);

        // remove item from view
        beginRemoveRows(QModelIndex(), index, index + (childCount - 1));
    }

    m_ItemList.Delete(index);
    endRemoveRows();

    emit treeContentChanged(parentIndex);

    #ifdef _DEBUG
        m_ItemList.LogToOutput();
    #endif

    return true;
}
*/
//---------------------------------------------------------------------------
bool TreeModel::isLeaf(int index) const
{
    return false;// m_ItemList.IsLeaf(index);
}
//---------------------------------------------------------------------------
void TreeModel::setCollapsed(int index, bool value)
{
    /*REM
    m_ItemList.SetCollapsed(index, value);

    const std::size_t childCount = m_ItemList.GetCount(index);

    emit collapseStateChanged(index, true, value);

    for (std::size_t i = 1; i < childCount; ++i)
        emit collapseStateChanged(index + i, false, value);
    */
}
//---------------------------------------------------------------------------
bool TreeModel::isCollapsed(int index) const
{
    return false;// m_ItemList.IsCollapsed(index);
}
//---------------------------------------------------------------------------
int TreeModel::rowCount(const QModelIndex& parent) const
{
    return GetItemCount();
}
//---------------------------------------------------------------------------
QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    return QVariant();//REM  m_ItemList.GetData(index, role);
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
std::wstring TreeModel::GetText(const TreeItem* pItem, const std::string& id) const
{
    if (!pItem)
        return L"";

    if (id == pItem->getId().toStdString())
        return pItem->getName().toStdWString();

    const std::size_t childCount = pItem->GetChildCount();

    for (std::size_t i = 0; i < childCount; ++i)
    {
        const std::wstring childName = GetText(pItem->GetChildAt(i), id);

        if (!childName.empty())
            return childName;
    }

    return L"";
}
//---------------------------------------------------------------------------
std::size_t TreeModel::GetItemCount() const
{
    std::size_t count = m_Items.size();

    for each (auto pItem in m_Items)
    {
    }

    return count;
}
//---------------------------------------------------------------------------
std::size_t TreeModel::GetChildrenCount(const TreeItem* pItem) const
{
    std::size_t count = 0;

    for each (auto pItem in m_Items)
    {
    }

    return count;
}
//---------------------------------------------------------------------------
