/****************************************************************************
 * ==> CFI_Link ------------------------------------------------------------*
 ****************************************************************************
 * Description: Link                                                        *
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
#include "CFI_Item.h"

// class prototype
class CFI_LinkProxy;

/**
* Link
*@author Jean-Milost Reymond
*/
class CFI_Link: public CFI_Item
{
    public:
        /**
        * Constructor
        *@param pParent - parent owning this component
        */
        CFI_Link(CFI_Item* pParent);

        virtual ~CFI_Link();

        /**
        * Gets the link title
        *@return the link title
        */
        virtual inline std::wstring GetTitle() const;

        /**
        * Gets the link description
        *@return the link description
        */
        virtual inline std::wstring GetDescription() const;

        /**
        * Gets the link comments
        *@return the link comments
        */
        virtual inline std::wstring GetComments() const;

        /**
        * Sets the link title
        *@param title - the link title
        */
        virtual inline void SetTitle(const std::wstring& title);

        /**
        * Sets the link description
        *@return the link description
        */
        virtual inline void SetDescription(const std::wstring& description);

        /**
        * Sets the link comments
        *@return the link comments
        */
        virtual inline void SetComments(const std::wstring& comments);

        /**
        * Gets the link proxy
        *@return the link proxy, nullptr if no proxy
        */
        virtual inline CFI_LinkProxy* GetProxy() const;

        /**
        * Sets the link proxy
        *@param pProxy - the link proxy
        */
        virtual inline void SetProxy(CFI_LinkProxy* pProxy);

    private:
        CFI_LinkProxy* m_pProxy = nullptr;
        std::wstring   m_Title;
        std::wstring   m_Description;
        std::wstring   m_Comments;
};

//---------------------------------------------------------------------------
// CFI_Link
//---------------------------------------------------------------------------
std::wstring CFI_Link::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
std::wstring CFI_Link::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
std::wstring CFI_Link::GetComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void CFI_Link::SetTitle(const std::wstring& title)
{
    m_Title = title;
}
//---------------------------------------------------------------------------
void CFI_Link::SetDescription(const std::wstring& description)
{
    m_Description = description;
}
//---------------------------------------------------------------------------
void CFI_Link::SetComments(const std::wstring& comments)
{
    m_Comments = comments;
}
//---------------------------------------------------------------------------
CFI_LinkProxy* CFI_Link::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void CFI_Link::SetProxy(CFI_LinkProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
