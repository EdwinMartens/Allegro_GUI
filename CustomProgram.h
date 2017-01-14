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


#ifndef CUSTOM_PROGRAM
#define CUSTOM_PROGRAM


#include "A5Program.h"
#include "GUI_BASE.h"
#include "GUI_Panel.h"


class CustomProgram:public A5Program
{
    public:
    CustomProgram(int a_nScreenWidth, int a_nScreenheight, bool a_blFullscreen);
    virtual ~CustomProgram();


    protected:
    virtual void DispatchEvent(ALLEGRO_EVENT * a_pEvent);
    virtual void OnKeyDown(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent);
    virtual void OnKeyUp(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent);
    virtual void OnMouseMove(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnMouseButtonDown(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnMouseButtonUp(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnUpdate(double a_dLagTime);
    virtual void OnTimer();
    virtual void OnDraw();


    private:

    CWidget * m_pMainWidget;
    ALLEGRO_FONT * m_pFont;
    ALLEGRO_PATH   * g_pFontPath = NULL;



};



#endif // CUSTOM_PROGRAM

