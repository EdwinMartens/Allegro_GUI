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


#ifndef _GUI_PANEL
#define _GUI_PANEL

#include "GUI_BASE.h"



class CPanel:public CWidget
{
    public:
    CPanel(CWidget * a_pParent,Vector2D a_vecPosition);
    CPanel(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight);
    CPanel(CWidget * a_pParent,int a_nX, int a_nY);
    CPanel(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight);

    virtual ~CPanel();

    protected:
    virtual bool HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget);
    virtual void OnLButtonDown(int a_nX, int a_nY,int a_nState);

    private:

};


#endif // _GUI_PANEL
