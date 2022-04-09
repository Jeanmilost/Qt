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

#pragma once

// std
#include <string>
#include <vector>

// classes
#include "CFI_Item.h"
#include "CFI_Box.h"
#include "CFI_Link.h"

// class prototype
class CFI_PageProxy;

/**
* Page
*@author Jean-Milost Reymond
*/
class CFI_Page: public CFI_Item
{
    public:
        CFI_Page();
        virtual ~CFI_Page();

        /**
        * Gets the page name
        *@return the page name
        */
        virtual inline std::wstring GetName() const;

        /**
        * Sets the page name
        *@param name - the page name
        */
        virtual inline void SetName(const std::wstring& name);

        /**
        * Gets the page proxy
        *@return the page proxy, nullptr if no proxy
        */
        virtual inline CFI_PageProxy* GetProxy() const;

        /**
        * Sets the page proxy
        *@param pProxy - the page proxy
        */
        virtual inline void SetProxy(CFI_PageProxy* pProxy);

        /**
        * Creates a box and adds it in page
        *@param name - box name
        *@param description - box description
        *@param comments - box comments
        *@param x - box x position in pixels, set to default position if -1
        *@param y - box y position in pixels, set to default position if -1
        *@param width - box width in pixels
        *@param height - box height in pixels
        *@return newly created box
        */
        virtual CFI_Box* AddBox(const std::wstring& name,
                                const std::wstring& description =  L"",
                                const std::wstring& comments    =  L"",
                                      int           x           = -1,
                                      int           y           = -1,
                                      int           width       =  144,
                                      int           height      =  93);

        /**
        * Creates a link and adds it in page
        *@param name - link name
        *@param description - link description
        *@param comments - link comments
        *@param startUID - start box unique identifier from which the link is attached
        *@param startPos - start box position from which the link is attached
        *@param endUID - end box unique identifier to which the link is attached
        *@param endPos - end box position from which the link is attached
        *@param x - link x position in pixels, set to default position if -1
        *@param y - link y position in pixels, set to default position if -1
        *@param width - link width in pixels
        *@param height - link height in pixels
        *@return newly created link
        */
        virtual CFI_Link* AddLink(const std::wstring&       name,
                                  const std::wstring&       description =  L"",
                                  const std::wstring&       comments    =  L"",
                                  const std::string&        startUID    =  "",
                                        CFI_Box::IEPosition startPos    =  CFI_Box::IEPosition::IE_P_None,
                                  const std::string&        endUID      =  "",
                                        CFI_Box::IEPosition endPos      =  CFI_Box::IEPosition::IE_P_None,
                                        int                 x           = -1,
                                        int                 y           = -1,
                                        int                 width       =  100,
                                        int                 height      =  50);

        /**
        * Removes a component
        *@param uid - component unique identifier to remove
        */
        virtual void Remove(const std::string& uid);

        /**
        * Removes a component
        *@param pComponent - component to remove
        */
        virtual void Remove(CFI_Item* pComponent);

        /**
        * Gets a component
        *@param uid - component unique identifier to get
        *@return component, nullptr if not found or on error
        */
        virtual CFI_Item* Get(const std::string& uid) const;

        /**
        * Gets count of type
        *@return count of type
        */
        template <class T>
        std::size_t GetCountOf() const;

        /**
        * Gets component count
        *@return component count
        */
        virtual std::size_t GetCount() const;

    private:
        typedef std::vector<CFI_Item*> IComponents;

        CFI_PageProxy* m_pProxy = nullptr;
        IComponents    m_Components;
        std::wstring   m_Name;

        /**
        * Adds a component in page
        *@param pComponent - component to add
        *@return true on success, otherwise false
        *@note The component lifetime will be managed internally, don't try to delete it from outside
        */
        bool Add(CFI_Item* pComponent);

        /**
        * Creates a new box view and adds it to the user interface
        *@param pBox - box for which the view should be added
        *@param type - box type to create
        *@param x - box x position in pixels
        *@param y - box y position in pixels
        *@param width - box width in pixels
        *@param height - box height in pixels
        */
        bool AddBoxView(CFI_Box* pBox, const std::string& type, int x, int y, int width, int height);

        /**
        * Creates a new link view and adds it to the user interface
        *@param pLink - link for which the view should be added
        *@param type - link type to create
        *@param startUID - start box unique identifier from which the link is attached
        *@param startPos - start box position from which the link is attached
        *@param endUID - end box unique identifier to which the link is attached
        *@param endPos - end box position from which the link is attached
        *@param x - link label x position in pixels
        *@param y - link label y position in pixels
        *@param width - link width in pixels
        *@param height - link height in pixels
        */
        bool AddLinkView(      CFI_Link*           pLink,
                         const std::string&        type,
                         const std::string&        startUID,
                               CFI_Box::IEPosition startPos,
                         const std::string&        endUID,
                               CFI_Box::IEPosition endPos,
                               int                 x,
                               int                 y,
                               int                 width,
                               int                 height);

        /**
        * Removes a component view from the user interface
        *@param uid - component unique identifier to remove
        */
        void RemoveComponentView(const std::string& uid);
};

//---------------------------------------------------------------------------
// CFI_Page
//---------------------------------------------------------------------------
std::wstring CFI_Page::GetName() const
{
    return m_Name;
}
//---------------------------------------------------------------------------
void CFI_Page::SetName(const std::wstring& name)
{
    m_Name = name;
}
//---------------------------------------------------------------------------
CFI_PageProxy* CFI_Page::GetProxy() const
{
    return m_pProxy;
}
//---------------------------------------------------------------------------
void CFI_Page::SetProxy(CFI_PageProxy* pProxy)
{
    m_pProxy = pProxy;
}
//---------------------------------------------------------------------------
template <class T>
std::size_t CFI_Page::GetCountOf() const
{
    std::size_t count = 0;

    for each (auto pComponent in m_Components)
        if (dynamic_cast<T*>(pComponent))
            ++count;

    return count;
}
//---------------------------------------------------------------------------
