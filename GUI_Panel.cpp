#include "GUI_Panel.h"

CPanel::CPanel(CWidget * a_pParent,Vector2D a_vecPosition)
:CWidget(a_pParent,a_vecPosition)
{
    SetWidgetType(wtPANEL);
}

CPanel::CPanel(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight)
:CWidget(a_pParent,a_vecPosition,a_nWidth, a_nHeight)
{
    SetWidgetType(wtPANEL);
}

CPanel::CPanel(CWidget * a_pParent,int a_nX, int a_nY)
:CWidget(a_pParent,a_nX, a_nY)
{
    SetWidgetType(wtPANEL);
}

CPanel::CPanel(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight)
:CWidget(a_pParent, a_nX, a_nY, a_nWidth, a_nHeight )
{
    SetWidgetType(wtPANEL);
}

CPanel::~CPanel()
{

}


bool CPanel::HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget)
{
    switch (pEvent->type)
           {
                case ALLEGRO_EVENT_KEY_CHAR:
                     if (m_evKeyPressed!=NULL)
                     {
                         return m_evKeyPressed(pEvent->keyboard.unichar, pEvent->keyboard.modifiers,a_pWidget);
                     }
                     else return false;
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
                     if (m_evMouseDown!=NULL)
                     {
                         return m_evMouseDown(pEvent->mouse.button, pEvent->mouse.x - m_nAbsoluteX, pEvent->mouse.y - m_nAbsoluteY, a_pWidget);
                     }
                     else return true;
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

void CPanel::OnLButtonDown(int a_nX, int a_nY,int a_nState)
{
     GetFocus();
}



