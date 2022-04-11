/****************************************************************************
 * ==> CFI_DocumentModel ---------------------------------------------------*
 ****************************************************************************
 * Description:  Document model                                             *
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

#pragma once

// std
#include <vector>

// classes
#include "CFI_Document.h"

// qt
#include <QObject>
#include <QAbstractListModel>

/**
* Document model
*@author Jean-Milost Reymond
*/
class CFI_DocumentModel : public QAbstractListModel
{
    Q_OBJECT

    signals:
        /**
        * Called when a page should be added to the document view
        *@param uid - page unique identifier
        */
        void addPageToView(const QString& uid);

        /**
        * Called when a page should be removed from the document view
        *@param uid - page unique identifier
        */
        void removePageFromView(const QString& uid);

    public:
        /**
        * Data roles
        */
        enum class IEDataRole
        {
            IE_DR_Title = 0
        };

        /**
        * Constructor
        *@param pDocument - document which owns this model
        *@param pParent - object which will be the parent of this object
        */
        explicit CFI_DocumentModel(CFI_Document* pDocument, QObject* pParent = nullptr);

        virtual ~CFI_DocumentModel();

        /**
        * Gets the main document
        *@return the main document, nullptr if not found or on error
        */
        virtual CFI_Document* GetDocument() const;

        /**
        * Notify that an page will be added
        */
        virtual Q_INVOKABLE void beginAddPage();

        /**
        * Notify that an page was added
        */
        virtual Q_INVOKABLE void endAddPage();

        /**
        * Adds a page to the view
        *@param uid - page unique identifier to add
        */
        virtual Q_INVOKABLE void addPage(const QString& uid);

        /**
        * Notify that an page will be removed
        */
        virtual Q_INVOKABLE void beginRemovePage();

        /**
        * Notify that an page was removed
        */
        virtual Q_INVOKABLE void endRemovePage();

        /**
        * Removes a page from the view
        *@param uid - page unique identifier to remove
        */
        virtual Q_INVOKABLE void removePage(const QString& uid);

        /**
        * Adds a box on the page
        */
        virtual Q_INVOKABLE void addBox();

        /**
        * Get row count
        *@param parent - the parent row index from which the count should be performed
        *@return the row count
        */
        virtual Q_INVOKABLE int rowCount(const QModelIndex& pParent = QModelIndex()) const;

        /**
        * Get data at row index
        *@param index - row index
        *@param role - data role
        *@return the data, empty value if not found or on error
        */
        virtual Q_INVOKABLE QVariant data(const QModelIndex& index, int role) const;

        /**
        * Get role names
        *@return the role names
        */
        virtual QHash<int, QByteArray> roleNames() const;

    private:
        CFI_Document* m_pDocument   = nullptr;
        std::size_t   m_BoxGenCount = 0;
};
