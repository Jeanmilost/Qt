/****************************************************************************
 * ==> CFI_Box -------------------------------------------------------------*
 ****************************************************************************
 * Description: Box                                                         *
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
class CFI_BoxProxy;

/**
* Box
*@author Jean-Milost Reymond
*/
class CFI_Box: public CFI_Item
{
    public:
        /**
        * Connector position
        *@note This enum is linked with the one located in TSP_Connector.
        *      Don't modify it without updating its twin
        */
        enum class IEPosition
        {
            IE_P_None = 0,
            IE_P_Left,
            IE_P_Top,
            IE_P_Right,
            IE_P_Bottom
        };

        /**
        * Constructor
        *@param pParent - parent owning this component
        */
        CFI_Box(CFI_Item* pParent);

        virtual ~CFI_Box();

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
        * Gets the box proxy
        *@return the box proxy, nullptr if no proxy
        */
        virtual inline CFI_BoxProxy* GetProxy() const;

        /**
        * Sets the box proxy
        *@param pProxy - the box proxy
        */
        virtual inline void SetProxy(CFI_BoxProxy* pProxy);

    private:
        CFI_BoxProxy* m_pProxy = nullptr;
        std::wstring  m_Title;
        std::wstring  m_Description;
        std::wstring  m_Comments;
};

//---------------------------------------------------------------------------
// CFI_Box
//---------------------------------------------------------------------------
std::wstring CFI_Box::GetTitle() const
{
    return m_Title;
}
//---------------------------------------------------------------------------
std::wstring CFI_Box::GetDescription() const
{
    return m_Description;
}
//---------------------------------------------------------------------------
std::wstring CFI_Box::GetComments() const
{
    return m_Comments;
}
//---------------------------------------------------------------------------
void CFI_Box::SetTitle(const std::wstring& title)
{
    m_Title = title;
}
//---------------------------------------------------------------------------
void CFI_Box::SetDescription(const std::wstring& description)
{
    m_Description = description;
}
//---------------------------------------------------------------------------
void CFI_Box::SetComments(const std::wstring& comments)
{
    m_Comments = comments;
}
//---------------------------------------------------------------------------
CFI_BoxProxy* CFI_Box::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void CFI_Box::SetProxy(CFI_BoxProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
