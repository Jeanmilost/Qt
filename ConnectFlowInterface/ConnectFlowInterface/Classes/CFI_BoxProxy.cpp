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

#include "CFI_BoxProxy.h"

//---------------------------------------------------------------------------
// CFI_BoxProxy
//---------------------------------------------------------------------------
CFI_BoxProxy::CFI_BoxProxy(QObject* pParent) :
    CFI_Proxy(pParent)
{}
//---------------------------------------------------------------------------
CFI_BoxProxy::~CFI_BoxProxy()
{}
//---------------------------------------------------------------------------
QString CFI_BoxProxy::getTitle() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetTitle());
}
//---------------------------------------------------------------------------
QString CFI_BoxProxy::getDescription() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetDescription());
}
//---------------------------------------------------------------------------
QString CFI_BoxProxy::getComments() const
{
    if (!m_pBox)
        return "";

    return QString::fromStdWString(m_pBox->GetComments());
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::setTitle(const QString& title)
{
    if (!m_pBox)
        return;

    m_pBox->SetTitle(title.toStdWString());

    emit titleChanged(title);
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::setDescription(const QString& description)
{
    if (!m_pBox)
        return;

    m_pBox->SetDescription(description.toStdWString());

    emit descriptionChanged(description);
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::setComments(const QString& comments)
{
    if (!m_pBox)
        return;

    m_pBox->SetComments(comments.toStdWString());

    emit commentsChanged(comments);
}
//---------------------------------------------------------------------------
CFI_Box* CFI_BoxProxy::GetBox() const
{
    return m_pBox;
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::SetBox(CFI_Box* pBox)
{
    m_pBox = pBox;
}
//---------------------------------------------------------------------------
bool CFI_BoxProxy::AddItem(const QString& type, const QString& uid)
{
    m_ItemAdded = false;

    emit addItemToBox(type, uid);

    return m_ItemAdded;
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::RemoveItem(const QString& type, const QString& uid)
{
    emit removeItemFromBox(type, uid);
}
//---------------------------------------------------------------------------
void CFI_BoxProxy::onItemAdded(bool success)
{
    m_ItemAdded = success;
}
//---------------------------------------------------------------------------
