/****************************************************************************
 * ==> CFI_Page ------------------------------------------------------------*
 ****************************************************************************
 * Description: Page                                                        *
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

#include "CFI_Page.h"

// std
#include <memory>

// classes
#include "CFI_BoxProxy.h"
#include "CFI_LinkProxy.h"
#include "CFI_PageProxy.h"
#include "CFI_ProxyDictionary.h"

//---------------------------------------------------------------------------
// CFI_Page
//---------------------------------------------------------------------------
CFI_Page::CFI_Page() :
    CFI_Item()
{}
//---------------------------------------------------------------------------
CFI_Page::~CFI_Page()
{
    for each (auto pComponent in m_Components)
        delete pComponent;
}
//---------------------------------------------------------------------------
CFI_Box* CFI_Page::AddBox(const std::wstring& name,
                          const std::wstring& description,
                          const std::wstring& comments,
                                int           x,
                                int           y,
                                int           width,
                                int           height)
{
    std::unique_ptr<CFI_Box> pBox = std::make_unique<CFI_Box>(this);

    // add a box on the page view
    if (!AddBoxView(pBox.get(), "box", x, y, width, height))
        return nullptr;

    // get box proxy
    CFI_BoxProxy* pBoxProxy = pBox->GetProxy();

    // found it?
    if (!pBoxProxy)
    {
        RemoveComponentView(pBox->GetUID());
        return nullptr;
    }

    // set the box data
    pBoxProxy->setTitle(QString::fromStdWString(name));
    pBoxProxy->setDescription(QString::fromStdWString(description));
    pBoxProxy->setComments(QString::fromStdWString(comments));

    // add newly created box to page
    if (!Add(pBox.get()))
    {
        RemoveComponentView(pBox->GetUID());
        return nullptr;
    }

    return pBox.release();
}
//---------------------------------------------------------------------------
CFI_Link* CFI_Page::AddLink(const std::wstring&       name,
                            const std::wstring&       description,
                            const std::wstring&       comments,
                            const std::string&        startUID,
                                  CFI_Box::IEPosition startPos,
                            const std::string&        endUID,
                                  CFI_Box::IEPosition endPos,
                                  int                 x,
                                  int                 y,
                                  int                 width,
                                  int                 height)
{
    std::unique_ptr<CFI_Link> pLink = std::make_unique<CFI_Link>(this);

    // add a link on the page view
    if (!AddLinkView(pLink.get(),
                     "link",
                     startUID,
                     startPos,
                     endUID,
                     endPos,
                     x,
                     y,
                     width,
                     height))
        return nullptr;

    // get box proxy
    CFI_LinkProxy* pLinkProxy = pLink->GetProxy();

    // found it?
    if (!pLinkProxy)
    {
        RemoveComponentView(pLink->GetUID());
        return nullptr;
    }

    // set the link data
    pLinkProxy->setTitle(QString::fromStdWString(name));
    pLinkProxy->setDescription(QString::fromStdWString(description));
    pLinkProxy->setComments(QString::fromStdWString(comments));

    // add newly created link to page
    if (!Add(pLink.get()))
    {
        RemoveComponentView(pLink->GetUID());
        return nullptr;
    }

    return pLink.release();
}
//---------------------------------------------------------------------------
void CFI_Page::Remove(const std::string& uid)
{
    if (uid.empty())
        return;

    RemoveComponentView(uid);

    Remove(Get(uid));
}
//---------------------------------------------------------------------------
void CFI_Page::Remove(CFI_Item* pComponent)
{
    if (!pComponent)
        return;

    RemoveComponentView(pComponent->GetUID());

    for (std::size_t i = 0; i < m_Components.size(); ++i)
        if (m_Components[i] == pComponent)
        {
            delete m_Components[i];
            m_Components.erase(m_Components.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
CFI_Item* CFI_Page::Get(const std::string& uid) const
{
    for each (auto pComponent in m_Components)
        if (pComponent->GetUID() == uid)
            return pComponent;

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t CFI_Page::GetCount() const
{
    return m_Components.size();
}
//---------------------------------------------------------------------------
bool CFI_Page::Add(CFI_Item* pComponent)
{
    // no component?
    if (!pComponent)
        return false;

    // check if component was already added in component list
    for each (auto pComp in m_Components)
        if (pComponent == pComp)
            return false;

    // add the component to component list
    m_Components.push_back(pComponent);

    return true;
}
//---------------------------------------------------------------------------
bool CFI_Page::AddBoxView(CFI_Box* pBox, const std::string& type, int x, int y, int width, int height)
{
    if (!pBox)
        return false;

    if (!m_pProxy)
        return false;

    // get box unique identifier
    const std::string uid = pBox->GetUID();

    // define the box position type
    CFI_PageProxy::IEBoxPosition boxPos = CFI_PageProxy::IEBoxPosition::IE_BP_Default;

    // do use a custom position?
    if (x > 0 && y > 0)
        boxPos = CFI_PageProxy::IEBoxPosition::IE_BP_Custom;

    // notify page proxy that a new box should be added
    if (!m_pProxy->AddBox(QString::fromStdString(type), QString::fromStdString(uid), boxPos, x, y, width, height))
        return false;

    // get the newly added component proxy
    CFI_BoxProxy* pProxy = static_cast<CFI_BoxProxy*>(CFI_ProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the box and its proxy
    pBox->SetProxy(pProxy);
    pProxy->SetBox(pBox);

    return true;
}
//---------------------------------------------------------------------------
bool CFI_Page::AddLinkView(      CFI_Link*           pLink,
                           const std::string&        type,
                           const std::string&        startUID,
                                 CFI_Box::IEPosition startPos,
                           const std::string&        endUID,
                                 CFI_Box::IEPosition endPos,
                                 int                 x,
                                 int                 y,
                                 int                 width,
                                 int                 height)
{
    if (!pLink)
        return false;

    if (!m_pProxy)
        return false;

    // get link unique identifier
    const std::string uid = pLink->GetUID();

    // notify page proxy that a new link should be added
    if (!m_pProxy->AddLink(QString::fromStdString(type),
                           QString::fromStdString(pLink->GetUID()),
                           QString::fromStdString(startUID),
                           startPos,
                           QString::fromStdString(endUID),
                           endPos,
                           x,
                           y,
                           width,
                           height))
        return false;

    // get the newly added component proxy
    CFI_LinkProxy* pProxy = static_cast<CFI_LinkProxy*>(CFI_ProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the link component and its proxy
    pLink->SetProxy(pProxy);
    pProxy->SetLink(pLink);

    return true;
}
//---------------------------------------------------------------------------
void CFI_Page::RemoveComponentView(const std::string& uid)
{
    if (uid.empty())
        return;

    if (!m_pProxy)
        return;

    // notify page proxy that a component should be removed
    m_pProxy->RemoveComponent(QString::fromStdString(uid));
}
//---------------------------------------------------------------------------
