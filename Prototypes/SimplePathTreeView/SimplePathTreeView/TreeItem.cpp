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

#include "TreeItem.h"

// std
#include <memory>

//---------------------------------------------------------------------------
// TreeItem
//---------------------------------------------------------------------------
TreeItem::TreeItem() :
    QObject()
{}
//---------------------------------------------------------------------------
TreeItem::TreeItem(const std::wstring& name) :
    QObject(),
    m_Name(name)
{}
//---------------------------------------------------------------------------
TreeItem::~TreeItem()
{
    for each (auto pChild in m_Children)
        delete pChild;
}
//---------------------------------------------------------------------------
QString TreeItem::getId() const
{
    return QString::fromStdString(std::to_string(std::uintptr_t(this)));
}
//---------------------------------------------------------------------------
QString TreeItem::getName() const
{
    return QString::fromStdWString(m_Name);
}
//---------------------------------------------------------------------------
void TreeItem::setName(const QString& name)
{
    m_Name = name.toStdWString();
}
//---------------------------------------------------------------------------
TreeItem* TreeItem::GetParent() const
{
    return m_pParent;
}
//---------------------------------------------------------------------------
TreeItem* TreeItem::Add()
{
    std::unique_ptr<TreeItem> pItem = std::make_unique<TreeItem>();
    pItem->m_pParent                = this;

    m_Children.push_back(pItem.get());

    return pItem.release();
}
//---------------------------------------------------------------------------
TreeItem* TreeItem::Add(const std::wstring& name)
{
    std::unique_ptr<TreeItem> pItem = std::make_unique<TreeItem>(name);
    pItem->m_pParent                = this;

    m_Children.push_back(pItem.get());

    return pItem.release();
}
//---------------------------------------------------------------------------
bool TreeItem::Delete(TreeItem* pItem, bool recursive)
{
    for (std::size_t i = 0; i < m_Children.size(); ++i)
    {
        if (pItem == m_Children[i])
        {
            delete m_Children[i];
            m_Children.erase(m_Children.begin() + i);
            return true;
        }

        if (recursive)
            if (m_Children[i]->Delete(pItem, recursive))
                return true;
    }

    return false;
}
//---------------------------------------------------------------------------
/*REM
void TreeItem::DeleteAt(std::size_t index)
{
    if (index >= m_Children.size())
        return;

    delete m_Children[index];
    m_Children.erase(m_Children.begin() + index);
}
*/
//---------------------------------------------------------------------------
void TreeItem::DeleteAll()
{
    for each (auto pChild in m_Children)
        delete pChild;

    m_Children.clear();
}
//---------------------------------------------------------------------------
TreeItem* TreeItem::GetChildAt(std::size_t index) const
{
    if (index >= m_Children.size())
        return nullptr;

    return m_Children[index];
}
//---------------------------------------------------------------------------
std::size_t TreeItem::GetChildCount() const
{
    return m_Children.size();
}
//---------------------------------------------------------------------------
bool TreeItem::IsLeaf() const
{
    return !m_Children.size();
}
//---------------------------------------------------------------------------
std::size_t TreeItem::GetLevel() const
{
    std::size_t level   = 0;
    TreeItem*   pParent = m_pParent;

    // count the parents until reaching the root
    while (pParent)
    {
        ++level;
        pParent = pParent->m_pParent;
    }

    return level;
}
//---------------------------------------------------------------------------
void TreeItem::SetCollapsed(bool value)
{
    m_Collapsed = value;
}
//---------------------------------------------------------------------------
bool TreeItem::IsCollapsed() const
{
    if (m_Collapsed)
        return true;

    TreeItem* pParent = m_pParent;

    // check if a parent is collapsed
    while (pParent)
    {
        if (pParent->m_Collapsed)
            return true;

        pParent = pParent->m_pParent;
    }

    return false;
}
//---------------------------------------------------------------------------
