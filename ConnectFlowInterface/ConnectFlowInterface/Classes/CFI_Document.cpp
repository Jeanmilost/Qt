/****************************************************************************
 * ==> CFI_Document --------------------------------------------------------*
 ****************************************************************************
 * Description: Document                                                    *
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

#include "CFI_Document.h"

// std
#include <sstream>

// classes
#include "CFI_PageProxy.h"
#include "CFI_DocumentModel.h"
#include "CFI_ProxyDictionary.h"

//---------------------------------------------------------------------------
// CFI_Document
//---------------------------------------------------------------------------
CFI_Document::CFI_Document()
{}
//---------------------------------------------------------------------------
CFI_Document::~CFI_Document()
{
    for each (auto pPage in m_Pages)
        delete pPage;
}
//---------------------------------------------------------------------------
CFI_DocumentModel* CFI_Document::GetModel() const
{
    return m_pModel;
}
//---------------------------------------------------------------------------
void CFI_Document::SetModel(CFI_DocumentModel* pModel)
{
    m_pModel = pModel;
}
//---------------------------------------------------------------------------
CFI_Page* CFI_Document::AddPage()
{
    std::wostringstream sstr;

    sstr << "page";

    const std::size_t pageCount = GetPageCount();

    if (pageCount)
        sstr << L" (" << std::to_wstring(pageCount) << L")";

    return AddPage(sstr.str());
}
//---------------------------------------------------------------------------
CFI_Page* CFI_Document::AddPage(const std::wstring& name)
{
    if (!m_pModel)
        return nullptr;

    // add a new page in document
    std::unique_ptr<CFI_Page> pPage = std::make_unique<CFI_Page>();
    pPage->SetName(name);

    // create page view and adds it on the user interface
    m_pModel->beginAddPage();
    const bool success = CreatePageView(pPage.get());
    m_pModel->endAddPage();

    // succeeded?
    if (!success)
        return nullptr;

    m_Pages.push_back(pPage.get());

    return pPage.release();
}
//---------------------------------------------------------------------------
void CFI_Document::RemovePage(std::size_t index)
{
    if (!m_pModel)
        return;

    // is index out of bounds?
    if (index >= m_Pages.size())
        return;

    // remove the page from the view
    m_pModel->beginRemovePage();
    m_pModel->removePage(QString::fromStdString(m_Pages[index]->GetUID()));
    m_pModel->endRemovePage();

    // delete the page
    delete m_Pages[index];
    m_Pages.erase(m_Pages.begin() + index);
}
//---------------------------------------------------------------------------
void CFI_Document::RemovePage(CFI_Page* pPage)
{
    if (!pPage)
        return;

    if (!m_pModel)
        return;

    // remove the page from the view
    m_pModel->beginRemovePage();
    m_pModel->removePage(QString::fromStdString(pPage->GetUID()));
    m_pModel->endRemovePage();

    // search for page to remove
    for (std::size_t i = 0; i < m_Pages.size(); ++i)
        // found it?
        if (m_Pages[i] == pPage)
        {
            // delete the page
            delete m_Pages[i];
            m_Pages.erase(m_Pages.begin() + i);
            return;
        }
}
//---------------------------------------------------------------------------
CFI_Page* CFI_Document::GetPage(std::size_t index) const
{
    if (index >= m_Pages.size())
        return nullptr;

    return m_Pages[index];
}
//---------------------------------------------------------------------------
CFI_Page* CFI_Document::GetPage(const std::string& uid) const
{
    // search for atlas matching with the uid
    for (IPages::const_iterator it = m_Pages.begin(); it != m_Pages.end(); ++it)
        // found it?
        if ((*it)->GetUID() == uid)
            return (*it);

    return nullptr;
}
//---------------------------------------------------------------------------
std::size_t CFI_Document::GetPageCount() const
{
    return m_Pages.size();
}
//---------------------------------------------------------------------------
bool CFI_Document::CreatePageView(CFI_Page* pPage)
{
    if (!pPage)
        return false;

    if (!m_pModel)
        return false;

    // get page unique identifier
    const std::string uid = pPage->GetUID();

    // add page on the document view
    m_pModel->addPage(QString::fromStdString(uid));

    // get the newly added page proxy
    CFI_PageProxy* pProxy = static_cast<CFI_PageProxy*>(CFI_ProxyDictionary::Instance()->GetProxy(uid));

    if (!pProxy)
        return false;

    // link the page and the proxy
    pPage->SetProxy(pProxy);
    pProxy->SetPage(pPage);

    return true;
}
//---------------------------------------------------------------------------
