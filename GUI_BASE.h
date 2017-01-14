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



#ifndef _GUI_BASE
#define _GUI_BASE

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <exception>
#include <string>
#include <vector>
#include "MathVectors.h"

#define DEF_WIDTH   100
#define DEF_HEIGHT  100



class CWidget;

/// Event handler types
typedef bool (*MouseButtonEventHandler)(int a_nMouseButton, int a_nX, int a_nY, CWidget * a_pWidget);
typedef bool (*MouseMoveEventHandler)(int a_nX, int a_nY, CWidget * a_pWidget);
typedef bool (*KeyEventHandler)(int a_nChar, unsigned int a_nModifiers,CWidget * a_pWidget);
typedef bool (*ClickEventHandler)(CWidget * a_pWidget);

/// Border style
enum BorderStyle
{
    bsLOWERED,
    bsRAISED,
    bsFLAT,
    bsNONE
};


/// Widget Type ( for runtime type information)
enum WidgetType
{
    wtNONE,
    wtWINDOW,
    wtPANEL,
    wtBUTTON,
    wtEND
};



/**
 * \class CWidget
 * Widget base class.
 * All widgets derive from this class,
 * Events are sent from the Main widget to it's children.
 * If a child cannot handle an event (completely) it can pass the event back to itś parent to handle it there.
 */

class CWidget
{
    public:

    /** \brief
    * Initialize the GUI system,
    */
    static void INIT_GUI(ALLEGRO_FONT * a_pFont);

    // Constructors
    /** \brief
    * Constructor for base Widget
    * \param CWidget * a_pParent
    *  Parent widget, can be NULL
    * \param Vector2D a_vecPosition
    * Left-Top position of widget
    */
    CWidget(CWidget * a_pParent,Vector2D a_vecPosition);

    /** \brief
    * Constructor for base Widget
    * \param CWidget * a_pParent
    *  Parent widget, can be NULL
    * \param Vector2D a_vecPosition
    * Left-Top position of widget
    * \param int a_nWidth
    * Width of the widget
    * \param int a_nHeight
    * Height of the Widget
    */
    CWidget(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight);


    /** \brief
    * Constructor for base Widget
    * \param CWidget * a_pParent
    *  Parent widget, can be NULL
    * \param int a_nX
    *  Left position of the widget
    * \param int a_nY
    *  Top position of the Widget
    */
    CWidget(CWidget * a_pParent,int a_nX, int a_nY);

    /** \brief
    * Constructor for base Widget
    * \param CWidget * a_pParent
    *  Parent widget, can be NULL
    * \param int a_nX
    *  Left position of the widget
    * \param int a_nY
    *  Top position of the Widget
    * \param int a_nWidth
    * Width of the widget
    * \param int a_nHeight
    * Height of the Widget
    */
    CWidget(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight);

    // destructor
    virtual ~CWidget();


    /** \brief
    * Register a handler for a MouseButton Down event
    * \param MouseButtonEventHandler a_pEventHandler
    * Event handler Functionpointer
    */
    void RegisterOnMouseDownHandler(MouseButtonEventHandler a_pEventHandler);

    /** \brief
    * Register a handler for a MouseButton Up event
    * \param MouseButtonEventHandler a_pEventHandler
    * Event handler Functionpointer
    */
    void RegisterOnMouseUpHandler(MouseButtonEventHandler a_pEventHandler);

    /** \brief
    * Register a handler for a Click event
    * \param ClickEventHandler a_pEventHandler
    * Event handler Functionpointer
    */
    void RegisterOnClickHandler(ClickEventHandler a_pEventHandler);

    /** \brief
    * Register a handler for a Mouse Move event
    * \param MouseMoveEventHandler a_pEventHandler
    * Event handler Functionpointer
    */
    void RegisterOnMouseMoveHandler(MouseMoveEventHandler a_pEventHandler);

    /** \brief
    * Register a handler for a KeyPressed event
    * \param KeyEventHandler a_pEventHandler
    * Event handler Functionpointer
    */
    void RegisterOnKeyHandler(KeyEventHandler a_pEventHandler);


    /** \brief
    * Send event to this widget and all it's children
    * \param ALLEGRO_EVENT * pEvent
    * Pointer to an event
    */
    bool          SendEvents(ALLEGRO_EVENT * pEvent);

    /** \brief
    * Add a childwidget to this widget
    * \param CWidget * a_pWidget
    * Pointer to a Widget
    */
    void          AddChild(CWidget * a_pWidget);

    /** \brief
    * Let this widget take focus
    */
    void          GetFocus();

    /** \brief
    * Set the Client area color of this Widget
    * \param ALLEGRO_COLOR a_color
    * A color
    */
    void          SetColor(ALLEGRO_COLOR a_color);

    /** \brief
    * Set the Client area to transperant
    */
    void          SetTransparentBackground();

    /** \brief
    * Set the Client area to solid
    */
    void          SetSolidBackground();

    /** \brief
    * Set the Borderstyle
    * \param BorderStyle a_BorderStyle
    * A Borderstyle [bsFLAT, bsLOWERED,bsRAISED]
    */
    void          SetBorderStyle(BorderStyle a_BorderStyle);
    WidgetType    GetWidgetType();

    /** \brief
    * Get the color of the Client area
    */
    ALLEGRO_COLOR GetColor();

    /** \brief
    * true if this widget has focus
    */
    bool          HasFocus();

    /** \brief
    * Draw this Widget
    * VIRTUAL
    * \param int a_nOffsetX
    * An X offset from origin, default is 0
    * \param int a_nOffsetY
    * An Y offset from origin, default is 0
    */
    virtual void Draw(int a_nOffsetX = 0, int a_nOffsetY =0 );

    /** \brief
    * Draw the children,
    * with an offset to the client area position
    */
    void DrawChildren();



    protected:
    virtual bool    HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget) = 0;

    void            Signal(ALLEGRO_EVENT * a_pEvent, CWidget * a_pWidget);
    void            Init(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight, bool a_blVisible);
    void            RearrangeChildren(CWidget * a_pWidget);
    void            LooseFocus();
    virtual void    DrawClient();
    void            DrawBorder(BorderStyle a_BorderStyle);

    MouseButtonEventHandler m_evMouseDown;
    MouseButtonEventHandler m_evMouseUp;
    MouseMoveEventHandler   m_evMouseMove;
    KeyEventHandler         m_evKeyPressed;
    ClickEventHandler       m_evClicked;

    int  m_nAbsoluteX;
    int  m_nAbsoluteY;
    int  m_nWidth;
    int  m_nHeight;
    bool m_blHasFocus;

    bool Clicked();
    BorderStyle GetBorderStyle();
    void SetWidgetType(WidgetType a_WidgetType);

    static ALLEGRO_FONT * TextFont;
    static ALLEGRO_COLOR clHighLight;
    static ALLEGRO_COLOR clShadow;
    static ALLEGRO_COLOR clGray;
    static int           FontHeight;

    private:
    bool CatchMouseEvent(ALLEGRO_EVENT * pEvent);
    bool CatchKeyboardEvent(ALLEGRO_EVENT * pEvent);

    int  m_nX;
    int  m_nY;

    int  m_nBorderWidth;
    bool m_blVisible;
    bool m_blDestroyed;
    bool m_blTransparentBackground;
    bool m_blWasPressed;
    BorderStyle m_Border;
    ALLEGRO_COLOR m_color;
    CWidget * m_pParent;
    WidgetType m_WidgetType;
    vector<CWidget *> m_vChildren;


};








#endif // _GUI_BASE
