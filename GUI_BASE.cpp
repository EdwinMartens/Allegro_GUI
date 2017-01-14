#include "GUI_BASE.h"
#include "Exceptions.h"

ALLEGRO_COLOR  CWidget::clHighLight;
ALLEGRO_COLOR  CWidget::clShadow;
ALLEGRO_COLOR  CWidget::clGray;
ALLEGRO_FONT * CWidget::TextFont;
int            CWidget::FontHeight;

void CWidget::INIT_GUI(ALLEGRO_FONT * a_pFont)
{
    if (a_pFont == NULL)
    {
        throw GUIException("No font available");
    }

    clHighLight = al_map_rgb(200,200,200);
    clShadow    = al_map_rgb(0,0,0);
    clGray      = al_map_rgb(50,50,50);
    TextFont    = a_pFont;
    FontHeight  = al_get_font_line_height(TextFont)/2;
}

CWidget::CWidget(CWidget * a_pParent,Vector2D a_vecPosition)
{
    Init(a_pParent,a_vecPosition.GetX(), a_vecPosition.GetY(), DEF_WIDTH, DEF_HEIGHT,true);
}

CWidget::CWidget(CWidget * a_pParent,Vector2D a_vecPosition, int a_nWidth, int a_nHeight)
{
    Init(a_pParent,a_vecPosition.GetX(), a_vecPosition.GetY(), a_nWidth, a_nHeight,true);
}


CWidget::CWidget(CWidget * a_pParent,int a_nX, int a_nY)
{
    Init(a_pParent,a_nX, a_nY, DEF_WIDTH, DEF_HEIGHT,true);
}


CWidget::CWidget(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight)
{
    Init(a_pParent,a_nX, a_nY, a_nWidth, a_nHeight,true);
}

void CWidget::Init(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight,bool a_blVisible)
{
    m_pParent = a_pParent;
    m_nX = a_nX;
    m_nY = a_nY;

    if (a_nWidth<0) a_nWidth   =0;
    if (a_nHeight<0) a_nHeight =0;

    m_nWidth = a_nWidth;
    m_nHeight = a_nHeight;

    m_blVisible   = a_blVisible;
    m_blTransparentBackground = false;
    m_blHasFocus   = false;
    m_blDestroyed  = false;
    m_blWasPressed = false;
    m_color = al_map_rgb(100,100,100);
    m_Border = bsFLAT;

    m_evKeyPressed = NULL;
    m_evMouseDown  = NULL;
    m_evMouseUp    = NULL;
    m_evMouseMove  = NULL;
    m_evClicked    = NULL;

    m_WidgetType = wtNONE;
}

CWidget::~CWidget()
{
    // Destroy children
    vector<CWidget *>::iterator I = m_vChildren.begin();
    while (I!= m_vChildren.end())
	{
		delete (*I);
		I =  m_vChildren.erase(I);
	}
}

void CWidget::SetBorderStyle(BorderStyle a_BorderStyle)
{
    m_Border = a_BorderStyle;
}

BorderStyle CWidget::GetBorderStyle()
{
   return m_Border;
}

void CWidget::Signal(ALLEGRO_EVENT * a_pEvent, CWidget * a_pWidget)
{
    if ((!HandleEvents(a_pEvent, a_pWidget))&&(m_pParent!=NULL))
    {
        m_pParent->Signal(a_pEvent, a_pWidget);
    }
}



void CWidget::AddChild(CWidget * a_pWidget)
{
    a_pWidget->m_pParent = this;
    m_vChildren.push_back(a_pWidget);
}


bool CWidget::HasFocus()
{
    return m_blHasFocus;
}


void CWidget::DrawChildren()
{
    for( size_t i=0; i<m_vChildren.size(); i++)
    {
        CWidget * pChild = m_vChildren[i];

        if ((!pChild->m_blDestroyed)&&(pChild->m_blVisible))
        {
           pChild->Draw(m_nAbsoluteX+2,m_nAbsoluteY+2);
        }
    }
}


void CWidget::Draw(int a_nOffsetX , int a_nOffsetY )
{
    m_nAbsoluteX = a_nOffsetX+m_nX;
    m_nAbsoluteY = a_nOffsetY+m_nY;

    int clipX,clipY,clipW, clipH;
    al_get_clipping_rectangle(&clipX,&clipY,&clipW, &clipH);
    al_set_clipping_rectangle(m_nAbsoluteX,m_nAbsoluteY,m_nWidth, m_nHeight);

    DrawClient();
    DrawChildren();

    // restore clipping
    al_set_clipping_rectangle(clipX,clipY,clipW, clipH);
    DrawBorder(m_Border);
}


WidgetType  CWidget::GetWidgetType()
{
    return m_WidgetType;
}

void CWidget::SetWidgetType(WidgetType a_WidgetType)
{
    m_WidgetType = a_WidgetType;
}

void CWidget::DrawClient()
{
    if (! m_blTransparentBackground)
    {
       al_draw_filled_rectangle(m_nAbsoluteX, m_nAbsoluteY,
                                m_nAbsoluteX + m_nWidth, m_nAbsoluteY + m_nHeight,
                                m_color);
    }
}

void CWidget::DrawBorder(BorderStyle a_BorderStyle)
{
    switch(a_BorderStyle)
    {
        case bsFLAT:
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY-1,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight+2,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX + m_nWidth, m_nAbsoluteY,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX, m_nAbsoluteY+m_nHeight+2,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX, m_nAbsoluteY+m_nHeight, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight+1, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+1,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth, m_nAbsoluteY-1, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight+1,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY-1, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+2,
                     clHighLight, 1);

        break;

        case bsRAISED:
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX + m_nWidth, m_nAbsoluteY-1,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight+2,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth, m_nAbsoluteY, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight+2,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+2,
                     clShadow, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX-2, m_nAbsoluteY+m_nHeight+1, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+1,
                     clShadow, 1);

        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX + m_nWidth-1, m_nAbsoluteY,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX, m_nAbsoluteY+m_nHeight,
                     clHighLight, 1);
        break;

        case bsLOWERED:
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX + m_nWidth, m_nAbsoluteY-1,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY-1, m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight+2,
                     clGray, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth, m_nAbsoluteY, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight+2,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+2,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX-1, m_nAbsoluteY+m_nHeight, m_nAbsoluteX + m_nWidth, m_nAbsoluteY+m_nHeight,
                     clHighLight, 1);
        al_draw_line(m_nAbsoluteX-2, m_nAbsoluteY+m_nHeight+1, m_nAbsoluteX + m_nWidth+1, m_nAbsoluteY+m_nHeight+1,
                     clHighLight, 1);

        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX + m_nWidth-1, m_nAbsoluteY,
                     clShadow, 1);
        al_draw_line(m_nAbsoluteX, m_nAbsoluteY, m_nAbsoluteX, m_nAbsoluteY+m_nHeight,
                     clShadow, 1);
        break;

        case bsNONE:
        break;
    }

}



bool CWidget::SendEvents(ALLEGRO_EVENT * pEvent)
{
    bool rValue = false;
    bool blHandled = false;
    if (!m_vChildren.empty())
    {
        size_t n = m_vChildren.size();
        while ((!blHandled) && (n > 0))
        {
            n--;
            CWidget * pChild = m_vChildren[n];

            if ((!pChild->m_blDestroyed)&&(pChild->m_blVisible))
            {
                if (pChild->SendEvents(pEvent))
                {
                    blHandled = true;
                }

            }
        }
    }

if (!blHandled)
{
    switch (pEvent->type)
            {
                case ALLEGRO_EVENT_KEY_CHAR:
                if(CatchKeyboardEvent(pEvent))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                     }
                break;

                case ALLEGRO_EVENT_KEY_DOWN:
                     if(CatchKeyboardEvent(pEvent))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                     }
                break;

                case ALLEGRO_EVENT_KEY_UP:
                     if(CatchKeyboardEvent(pEvent))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                     }
                break;

                case ALLEGRO_EVENT_MOUSE_AXES:
                     if (CatchMouseEvent(pEvent))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                     }
                break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                     if (CatchMouseEvent(pEvent))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                         if (pEvent->mouse.button == 1)
                         {
                             m_blWasPressed = true;
                         }
                     }
                break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                     if ((CatchMouseEvent(pEvent))||(m_blWasPressed))
                     {
                         Signal(pEvent,this);
                         rValue = true;
                         m_blWasPressed = false;
                     }
                break;
            }
}
else
{
    rValue = true;
}

 return rValue;
}

void CWidget::LooseFocus()
{
   m_blHasFocus = false;
   for( size_t i=0; i<m_vChildren.size(); i++)
   {
        CWidget * pChild = m_vChildren[i];

        if (!pChild->m_blDestroyed)
        {
           pChild->LooseFocus();
        }
   }
}


void CWidget::GetFocus()
{
    CWidget * pWidget = m_pParent;
    while (pWidget!= NULL)
    {
        pWidget->LooseFocus();
        pWidget = pWidget->m_pParent;
    }
    LooseFocus();
    m_blHasFocus = true;

    if (m_pParent!=NULL) m_pParent->RearrangeChildren(this);
}



bool CWidget::CatchMouseEvent(ALLEGRO_EVENT * pEvent)
{
   if ((pEvent->mouse.x>m_nAbsoluteX)&&
        (pEvent->mouse.x<(m_nAbsoluteX+m_nWidth))&&
        (pEvent->mouse.y>m_nAbsoluteY)&&
        (pEvent->mouse.y<(m_nAbsoluteY+m_nHeight)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CWidget::CatchKeyboardEvent(ALLEGRO_EVENT * pEvent)
{
    return m_blHasFocus;
}

bool CWidget::Clicked()
{
    return m_blWasPressed;
}

void CWidget::RearrangeChildren(CWidget * a_pWidget)
{
    bool blSleep = false;

    for (size_t i=0; i< m_vChildren.size();i++)
    {
        if ( m_vChildren[i] == a_pWidget)
        {
            blSleep = true;
        }

        if (blSleep)
        {
            if (i<m_vChildren.size()-1)
            {
                m_vChildren[i] = m_vChildren[i+1];
            }
            else
            {
                m_vChildren[i] = a_pWidget;
            }

        }
    }
}

void CWidget::SetColor(ALLEGRO_COLOR a_color)
{
    m_color = a_color;
}


ALLEGRO_COLOR CWidget::GetColor()
{
    return m_color;
}

void  CWidget::SetTransparentBackground()
{
    m_blTransparentBackground = true;
}

void  CWidget::SetSolidBackground()
{
    m_blTransparentBackground = false;
}



void CWidget::RegisterOnMouseDownHandler(MouseButtonEventHandler a_pEventHandler)
{
    m_evMouseDown = a_pEventHandler;
}

void CWidget::RegisterOnMouseUpHandler(MouseButtonEventHandler a_pEventHandler)
{
    m_evMouseUp = a_pEventHandler;
}

void CWidget::RegisterOnMouseMoveHandler(MouseMoveEventHandler a_pEventHandler)
{
    m_evMouseMove = a_pEventHandler;
}

void CWidget::RegisterOnKeyHandler(KeyEventHandler a_pEventHandler)
{
    m_evKeyPressed = a_pEventHandler;
}

void CWidget::RegisterOnClickHandler(ClickEventHandler a_pEventHandler)
{
    m_evClicked = a_pEventHandler;
}




