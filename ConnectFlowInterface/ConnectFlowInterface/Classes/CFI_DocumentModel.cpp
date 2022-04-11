/****************************************************************************
 * ==> CFI_DocumentModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  Document model                                             *
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

#include "CFI_DocumentModel.h"

// std
#include <sstream>

//---------------------------------------------------------------------------
// CFI_DocumentModel
//---------------------------------------------------------------------------
CFI_DocumentModel::CFI_DocumentModel(CFI_Document* pDocument, QObject* pParent) :
    QAbstractListModel(pParent),
    m_pDocument(pDocument)
{}
//---------------------------------------------------------------------------
CFI_DocumentModel::~CFI_DocumentModel()
{}
//---------------------------------------------------------------------------
CFI_Document* CFI_DocumentModel::GetDocument() const
{
    return m_pDocument;
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::beginAddPage()
{
    const int count = rowCount();

    beginInsertRows(QModelIndex(), count, count);
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::endAddPage()
{
    endInsertRows();
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::addPage(const QString& uid)
{
    emit addPageToView(uid);
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::beginRemovePage()
{
    const int count = rowCount();

    if (!count)
        return;

    beginRemoveRows(QModelIndex(), count - 1, count - 1);
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::endRemovePage()
{
    endRemoveRows();
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::removePage(const QString& uid)
{
    emit removePageFromView(uid);
}
//---------------------------------------------------------------------------
void CFI_DocumentModel::addBox()
{
    if (!m_pDocument)
        return;

    CFI_Page* pPage = m_pDocument->GetPage(0);

    if (!pPage)
        return;

    std::wostringstream sstr;

    sstr << "Box";

    if (m_BoxGenCount)
        sstr << L" (" << std::to_wstring(m_BoxGenCount) << L")";

    pPage->AddBox(sstr.str());

    ++m_BoxGenCount;
}
//---------------------------------------------------------------------------
int CFI_DocumentModel::rowCount(const QModelIndex& pParent) const
{
    if (!m_pDocument)
        return 0;

    return m_pDocument->GetPageCount();
}
//---------------------------------------------------------------------------
QVariant CFI_DocumentModel::data(const QModelIndex& index, int role) const
{
    if (!m_pDocument)
        return QVariant();

    // search for document data role to get (i.e not dependent from index)
    switch ((CFI_DocumentModel::IEDataRole)role)
    {
        case CFI_DocumentModel::IEDataRole::IE_DR_Title:
            // get the title
            return QString::fromStdWString(m_pDocument->GetTitle());
    }

    return QVariant();
}
//---------------------------------------------------------------------------
QHash<int, QByteArray> CFI_DocumentModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[(int)CFI_DocumentModel::IEDataRole::IE_DR_Title] = "title";

    return roles;
}
//---------------------------------------------------------------------------
