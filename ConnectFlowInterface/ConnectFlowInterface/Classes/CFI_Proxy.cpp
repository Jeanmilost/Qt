/****************************************************************************
 * ==> CFI_Proxy -----------------------------------------------------------*
 ****************************************************************************
 * Description: Proxy between qml view and application engine               *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - Connect FLow Interface                                     *
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

#include "CFI_Proxy.h"

// qt classes
#include "CFI_ProxyDictionary.h"

//---------------------------------------------------------------------------
// CFI_Proxy
//---------------------------------------------------------------------------
CFI_Proxy::CFI_Proxy(QObject* pParent) :
    QObject(pParent)
{}
//---------------------------------------------------------------------------
CFI_Proxy::~CFI_Proxy()
{
    CFI_ProxyDictionary::Instance()->Unregister(m_UID);
}
//---------------------------------------------------------------------------
QString CFI_Proxy::getUID() const
{
    return QString::fromStdString(m_UID);
}
//---------------------------------------------------------------------------
void CFI_Proxy::setUID(const QString& uid)
{
    m_UID = uid.toStdString();

    // register the instance in the proxy dictionary
    CFI_ProxyDictionary::Instance()->Register(m_UID, this);
}
//---------------------------------------------------------------------------
