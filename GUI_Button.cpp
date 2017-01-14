#include "GUI_Button.h"

CButton::CButton(CWidget * a_pParent,Vector2D a_vecPosition,std::string a_strCaption)
:CWidget(a_pParent,a_vecPosition)
{
    m_strCaption = a_strCaption;
    SetBorderStyle(bsRAISED);
    SetWidgetType(wtBUTTON);
}

CButton::CButton(CWidget * a_pParent,Vector2D a_vecPosition,int a_nWidth, int a_nHeight,std::string a_strCaption)
:CWidget(a_pParent,a_vecPosition,a_nWidth, a_nHeight)
{
    m_strCaption = a_strCaption;
    SetBorderStyle(bsRAISED);
    SetWidgetType(wtBUTTON);
}

CButton::CButton(CWidget * a_pParent,int a_nX, int a_nY,std::string a_strCaption)
:CWidget(a_pParent,a_nX, a_nY)
{
    m_strCaption = a_strCaption;
    SetBorderStyle(bsRAISED);
    SetWidgetType(wtBUTTON);
}

CButton::CButton(CWidget * a_pParent, int a_nX, int a_nY, int a_nWidth, int a_nHeight,std::string a_strCaption)
:CWidget(a_pParent, a_nX, a_nY, a_nWidth, a_nHeight )
{
    m_strCaption = a_strCaption;
    SetBorderStyle(bsRAISED);
    SetWidgetType(wtBUTTON);
}

CButton::~CButton()
{

}

void CButton::SetCaption(std::string a_strCaption)
{
    m_strCaption = a_strCaption;
}

void CButton::SetCaption(const char * a_szCaption)
{
   m_strCaption.assign(a_szCaption);
}


void CButton::DrawClient()
{
    CWidget::DrawClient();
    if (TextFont!=NULL)
    {
        int nOffset;
        if (GetBorderStyle()==bsLOWERED)
        {
            nOffset =2;
        }
        else
        {
            nOffset =0;
        }

        al_draw_text(TextFont,
                     clShadow,
                     m_nAbsoluteX + (m_nWidth/2)+nOffset, m_nAbsoluteY + ((m_nHeight/2)-(FontHeight)+nOffset),
                     ALLEGRO_ALIGN_CENTRE,
                     m_strCaption.c_str());
    }
}

bool CButton::HandleEvents(ALLEGRO_EVENT * pEvent, CWidget * a_pWidget)
{
    switch (pEvent->type)
           {
                case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                     if (pEvent->mouse.button == 1)
                     {
                         OnLButtonDown(pEvent->mouse.x-m_nAbsoluteX, pEvent->mouse.y-m_nAbsoluteY,0);
                     }
                     return true;
                break;

                case ALLEGRO_EVENT_MOUSE_BUTTON_UP:

                     if (pEvent->mouse.button == 1)
                     {
                         OnLButtonUp(pEvent->mouse.x-m_nAbsoluteX, pEvent->mouse.y-m_nAbsoluteY,0);
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
                    return true;
            }

}

void CButton::OnLButtonDown(int a_nX, int a_nY,int a_nState)
{
     SetBorderStyle(bsLOWERED);
}

void CButton::OnLButtonUp(int a_nX, int a_nY,int a_nState)
{
     SetBorderStyle(bsRAISED);
}



