#include "GUI_Edit.h"


CEdit::CEdit(CWidget * a_pParent,Vector2D a_vecPosition)
:CWidget(a_pParent,a_vecPosition)
{
    SetWidgetType(wtPANEL);
    SetColor(al_map_rgb(255,255,255));
    SetBorderStyle(bsLOWERED);
    m_strText ="";
    m_evEnter = NULL;
}

CEdit::CEdit(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight)
:CWidget(a_pParent,a_vecPosition,a_nWidth, a_nHeight)
{
    SetWidgetType(wtPANEL);
    SetColor(al_map_rgb(255,255,255));
    SetBorderStyle(bsLOWERED);
    m_strText ="";
    m_evEnter = NULL;
}

CEdit::CEdit(CWidget * a_pParent,int a_nX, int a_nY)
:CWidget(a_pParent,a_nX, a_nY)
{
    SetWidgetType(wtPANEL);
    SetColor(al_map_rgb(255,255,255));
    SetBorderStyle(bsLOWERED);
    m_strText ="";
    m_evEnter = NULL;
}

CEdit::CEdit(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight)
:CWidget(a_pParent, a_nX, a_nY, a_nWidth, a_nHeight )
{
    SetWidgetType(wtPANEL);
    SetColor(al_map_rgb(255,255,255));
    SetBorderStyle(bsLOWERED);
    m_strText ="";
    m_evEnter = NULL;
}

CEdit::~CEdit()
{

}


std::string CEdit::GetText()
{
    return m_strText;
}


void CEdit::RegisterOnEnterHandler(EnterEventHandler a_pEventHandler)
{
    m_evEnter = a_pEventHandler;
}


void CEdit::DrawClient()
{
    CWidget::DrawClient();
    if (TextFont!=NULL)
    {
        string strTemp;
        if (m_blHasFocus)
        {
            strTemp = m_strText +"|";
        }
        else
        {
            strTemp = m_strText;
        }

        al_draw_text(TextFont,
                     clShadow,
                     m_nAbsoluteX + 2, m_nAbsoluteY + ((m_nHeight/2)-(FontHeight)),
                     ALLEGRO_ALIGN_LEFT,
                     strTemp.c_str());

    }
}



bool CEdit::HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget)
{
    switch (pEvent->type)
           {
                case ALLEGRO_EVENT_KEY_CHAR:
                     if (m_blHasFocus)
                     {
                         OnKey(pEvent->keyboard.unichar, pEvent->keyboard.modifiers);
                     }
                     return true;
                break;

                case ALLEGRO_EVENT_KEY_DOWN:
                     return true;
                break;

                case ALLEGRO_EVENT_KEY_UP:
                     return true;
                break;

                case ALLEGRO_EVENT_MOUSE_AXES:
                     if (m_evMouseMove!=NULL)
                     {
                        return m_evMouseMove(pEvent->mouse.x - m_nAbsoluteX, pEvent->mouse.y - m_nAbsoluteY, a_pWidget);
                     }
                     else return false;
                break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                     if (pEvent->mouse.button == 1)
                     {
                         OnLButtonDown( pEvent->mouse.x - m_nAbsoluteX, pEvent->mouse.y - m_nAbsoluteY,0);
                     }
                     return true;
                break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

                     if (m_evMouseDown!=NULL)
                     {
                         m_evMouseDown(pEvent->mouse.button, pEvent->mouse.x - m_nAbsoluteX, pEvent->mouse.y - m_nAbsoluteY, a_pWidget);
                     }

                     if ((pEvent->mouse.button == 1)&& Clicked())
                     {
                        if (m_evClicked!=NULL)
                        {
                            m_evClicked(a_pWidget);
                        }
                     }

                     return true;

                break;

                default:
                    return false;
            }

}

void CEdit::OnLButtonDown(int a_nX, int a_nY,int a_nState)
{
     GetFocus();
}


void CEdit::OnKey(int a_nChar, unsigned int a_nModifiers)
{
    switch (a_nChar)
    {
       case 8:
       if (!m_strText.empty())
       {
           m_strText.erase( m_strText.end()-1 );
       }
       break;

       case 13:
       if (m_evEnter!=NULL)
       {
           m_evEnter(m_strText,this);
       }
       break;

       

       default:
       if ( al_get_text_width(TextFont, m_strText.c_str()) < (m_nWidth-10))
       {
           char ch = (char )a_nChar;
           m_strText+=ch;
       }

    }

}




