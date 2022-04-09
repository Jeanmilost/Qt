/****************************************************************************
 * ==> CFI_LinkProxy -------------------------------------------------------*
 ****************************************************************************
 * Description: Link proxy between qml view and application engine          *
 * Developer:   Jean-Milost Reymond                                         *
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

#include "CFI_LinkProxy.h"

//---------------------------------------------------------------------------
// CFI_LinkProxy
//---------------------------------------------------------------------------
CFI_LinkProxy::CFI_LinkProxy(QObject* pParent) :
    CFI_Proxy(pParent)
{}
//---------------------------------------------------------------------------
CFI_LinkProxy::~CFI_LinkProxy()
{}
//---------------------------------------------------------------------------
QString CFI_LinkProxy::getTitle() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetTitle());
}
//---------------------------------------------------------------------------
QString CFI_LinkProxy::getDescription() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetDescription());
}
//---------------------------------------------------------------------------
QString CFI_LinkProxy::getComments() const
{
    if (!m_pLink)
        return "";

    return QString::fromStdWString(m_pLink->GetComments());
}
//---------------------------------------------------------------------------
void CFI_LinkProxy::setTitle(const QString& title)
{
    if (!m_pLink)
        return;

    m_pLink->SetTitle(title.toStdWString());

    emit titleChanged(title);
}
//---------------------------------------------------------------------------
void CFI_LinkProxy::setDescription(const QString& description)
{
    if (!m_pLink)
        return;

    m_pLink->SetDescription(description.toStdWString());

    emit descriptionChanged(description);
}
//---------------------------------------------------------------------------
void CFI_LinkProxy::setComments(const QString& comments)
{
    if (!m_pLink)
        return;

    m_pLink->SetComments(comments.toStdWString());

    emit commentsChanged(comments);
}
//---------------------------------------------------------------------------
CFI_Link* CFI_LinkProxy::GetLink() const
{
    return m_pLink;
}
//---------------------------------------------------------------------------
void CFI_LinkProxy::SetLink(CFI_Link* pLink)
{
    m_pLink = pLink;
}
//---------------------------------------------------------------------------
