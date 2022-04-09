/****************************************************************************
 * ==> CFI_PageProxy -------------------------------------------------------*
 ****************************************************************************
 * Description:  Page proxy between qml view and application engine         *
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

#include "CFI_PageProxy.h"

//---------------------------------------------------------------------------
// CFI_PageProxy
//---------------------------------------------------------------------------
CFI_PageProxy::CFI_PageProxy(QObject* pParent) :
    CFI_Proxy(pParent)
{}
//---------------------------------------------------------------------------
CFI_PageProxy::~CFI_PageProxy()
{}
//---------------------------------------------------------------------------
QString CFI_PageProxy::getName() const
{
    if (!m_pPage)
        return "";

    return QString::fromStdWString(m_pPage->GetName());
}
//---------------------------------------------------------------------------
void CFI_PageProxy::setName(const QString& name)
{
    if (!m_pPage)
        return;

    m_pPage->SetName(name.toStdWString());

    emit nameChanged(name);
}
//---------------------------------------------------------------------------
CFI_Page* CFI_PageProxy::GetPage() const
{
    return m_pPage;
}
//---------------------------------------------------------------------------
void CFI_PageProxy::SetPage(CFI_Page* pPage)
{
    m_pPage = pPage;
}
//---------------------------------------------------------------------------
bool CFI_PageProxy::AddBox(const QString&      type,
                           const QString&      uid,
                                 IEBoxPosition position,
                                 int           x,
                                 int           y,
                                 int           width,
                                 int           height)
{
    m_BoxAdded = false;

    emit addBoxToView(type, uid, (int)position, x, y, width, height);

    return m_BoxAdded;
}
//---------------------------------------------------------------------------
bool CFI_PageProxy::AddLink(const QString&            type,
                            const QString&            uid,
                            const QString&            startUID,
                                  CFI_Box::IEPosition startPos,
                            const QString&            endUID,
                                  CFI_Box::IEPosition endPos,
                                  int                 x,
                                  int                 y,
                                  int                 width,
                                  int                 height)
{
    m_LinkAdded = false;

    emit addLinkToView(type, uid, startUID, (int)startPos, endUID, (int)endPos, x, y, width, height);

    return m_LinkAdded;
}
//---------------------------------------------------------------------------
void CFI_PageProxy::RemoveComponent(const QString& uid)
{
    emit removeComponentView(uid);
}
//---------------------------------------------------------------------------
void CFI_PageProxy::onBoxAdded(bool success)
{
    m_BoxAdded = success;
}
//---------------------------------------------------------------------------
QString CFI_PageProxy::onAddLinkStart(const QString& fromUID, int position)
{
    if (!m_pPage)
        return "";

    // get the page
    CFI_Page* pQmlPage = static_cast<CFI_Page*>(m_pPage);

    // found it?
    if (!pQmlPage)
        return "";

    //: New link title
    //% "New link"
    const QString defLinkTitle = qtTrId("id-new-link-title");

    // create and add a new link in the page
    CFI_Link* pLink = pQmlPage->AddLink(defLinkTitle.toStdWString(),
                                        L"",
                                        L"",
                                        fromUID.toStdString(),
                                        (CFI_Box::IEPosition)position);

    // succeeded?
    if (!pLink)
        return "";

    // get newly added link unique identifier
    return QString::fromStdString(pLink->GetUID());
}
//---------------------------------------------------------------------------
void CFI_PageProxy::onLinkAdded(bool success)
{
    m_LinkAdded = success;
}
//---------------------------------------------------------------------------
void CFI_PageProxy::onDeleteBox(const QString& uid)
{
    if (uid.isEmpty())
        return;

    if (!m_pPage)
        return;

    // remove the box from page
    m_pPage->Remove(uid.toStdString());
}
//---------------------------------------------------------------------------
void CFI_PageProxy::onDeleteLink(const QString& uid)
{
    if (uid.isEmpty())
        return;

    if (!m_pPage)
        return;

    // remove the link from page
    m_pPage->Remove(uid.toStdString());
}
//---------------------------------------------------------------------------
