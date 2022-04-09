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

#pragma once

// std
#include <string>

// classes
#include "CFI_Page.h"

// class prototype
class CFI_DocumentModel;

/**
* Document
*@author Jean-Milost Reymond
*/
class CFI_Document
{
    public:
        CFI_Document();
        virtual ~CFI_Document();

        /**
        * Gets the document title
        *@return the document title
        */
        virtual inline std::wstring GetTitle() const;

        /**
        * Sets the document title
        *@param title - the document title
        */
        virtual inline void SetTitle(const std::wstring& title);

        /**
        * Gets the document model
        *@return the document model
        */
        virtual CFI_DocumentModel* GetModel() const;

        /**
        * Sets the document model
        *@param name - the document model
        */
        virtual void SetModel(CFI_DocumentModel* pModel);

        /**
        * Creates a new page and adds it in document
        *@return newly created page
        */
        virtual CFI_Page* AddPage();

        /**
        * Creates a new page and adds it in document
        *@param name - page name
        *@return newly created page
        */
        virtual CFI_Page* AddPage(const std::wstring& name);

        /**
        * Removes a page
        *@param index - page index to remove
        */
        virtual void RemovePage(std::size_t index);

        /**
        * Removes a page
        *@param pPage - page to remove
        */
        virtual void RemovePage(CFI_Page* pPage);

        /**
        * Gets page at index
        *@param index - page index to get
        *@return page, nullptr if not found or on error
        */
        virtual CFI_Page* GetPage(std::size_t index) const;

        /**
        * Gets page matching with uid
        *@param uid - page unique identifier to get
        *@return page, nullptr if not found or on error
        */
        virtual CFI_Page* GetPage(const std::string& uid) const;

        /**
        * Gets page count
        *@return page count
        */
        virtual std::size_t GetPageCount() const;

    private:
        typedef std::vector<CFI_Page*> IPages;

        CFI_DocumentModel* m_pModel = nullptr;
        IPages             m_Pages;
        std::wstring       m_Title;

        /**
        * Creates a new page view and adds it to the user interface
        *@param pPage - page for which the view should be added
        */
        bool CreatePageView(CFI_Page* pPage);
};

//---------------------------------------------------------------------------
// CFI_Document
//---------------------------------------------------------------------------
std::wstring CFI_Document::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
void CFI_Document::SetTitle(const std::wstring& title)
{
    m_Title = title;
}
//---------------------------------------------------------------------------
