/****************************************************************************
 * ==> TreeItem ------------------------------------------------------------*
 ****************************************************************************
 * Description: Tree item                                                   *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - The Simple Path                                            *
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
#include <vector>
#include <string>

/**
* Tree item
*@author Jean-Milost Reymond
*/
class TreeItem
{
    public:
        TreeItem();

        /**
        * Constructor
        *@param name - item name
        */
        TreeItem(const std::wstring& name);

        virtual ~TreeItem();

        /**
        * Gets the item name
        *@return the item name
        */
        virtual std::wstring GetName() const;

        /**
        * Sets the item name
        *@param name - the item name
        */
        virtual void SetName(const std::wstring& name);

        /**
        * Gets the item parent
        *@return the item parent, nullptr if no parent
        */
        virtual TreeItem* GetParent() const;

        /**
        * Adds an item as a child of this item
        *@return newly added tree item, nullptr on error
        */
        virtual TreeItem* Add();

        /**
        * Adds an item as a child of this item
        *@param name - item name
        *@return newly added tree item, nullptr on error
        */
        virtual TreeItem* Add(const std::wstring& name);

        /**
        * Deletes a child item from this item
        *@param pItem - child item to delete
        *@param recursive - if true, the item to delete will also be searched in the children items
        *@return true on success, otherwise false
        */
        virtual bool Delete(TreeItem* pItem, bool recursive = true);

        /**
        * Deletes a child item from this item at index
        *@param index - child item index to delete
        */
        virtual void DeleteAt(std::size_t index);

        /**
        * Deletes all children
        */
        virtual void DeleteAll();

        /**
        * Gets the child item at index
        *@return the child item at index, nullptr if not found or on error
        */
        virtual TreeItem* GetChildAt(std::size_t index) const;

        /**
        * Gets the child count
        *@return the child count
        */
        virtual std::size_t GetChildCount() const;

        /**
        * Gets if this item is a leaf
        *@return true if this item is a leaf, otherwise false
        */
        virtual bool IsLeaf() const;

        /**
        * Gets the item level
        *@return the item level
        */
        virtual std::size_t GetLevel() const;

        /**
        * Sets the item as collapsed
        *@param value - if true, item is collapsed
        */
        virtual void SetCollapsed(bool value);

        /**
        * Checks if item is collapsed
        *@return true if item is collapsed, otherwise false
        */
        virtual bool IsCollapsed() const;

    private:
        typedef std::vector<TreeItem*> IChildren;

        std::wstring m_Name;
        TreeItem*    m_pParent   = nullptr;
        IChildren    m_Children;
        std::size_t  m_Index     = 0;
        bool         m_Collapsed = false;
};
