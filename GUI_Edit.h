//      Copyright (C) 2016   E.J.M. Martens
//
//      This program is free software; you can redistribute it and/or
//      modify it under the terms of the GNU General Public License
//      as published by the Free Software Foundation; either version 2
//      of the License, or (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


#ifndef _GUI_EDIT
#define _GUI_EDIT
#include "GUI_BASE.h"

/// Event handler types
typedef bool (*EnterEventHandler)(std::string a_strInput, CWidget * a_pWidget);

class CEdit:public CWidget
{
    public:
    CEdit(CWidget * a_pParent,Vector2D a_vecPosition);
    CEdit(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight);
    CEdit(CWidget * a_pParent,int a_nX, int a_nY);
    CEdit(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight);
    std::string GetText();
    void RegisterOnEnterHandler(EnterEventHandler a_pEventHandler);
    virtual ~CEdit();



    protected:
    virtual bool HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget);
    virtual void OnLButtonDown(int a_nX, int a_nY,int a_nState);
    virtual void OnKey(int a_nChar, unsigned int a_nModifiers);
    virtual void DrawClient();

    EnterEventHandler m_evEnter;


    private:
    std::string m_strText;
    int m_nMaxLength;

};







#endif // _GUI_EDIT

