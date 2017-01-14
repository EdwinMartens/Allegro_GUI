#include "CustomProgram.h"
#include <allegro5/allegro_primitives.h>
#include "GUI_BASE.h"
#include "GUI_Panel.h"
#include "GUI_Button.h"
#include "GUI_Edit.h"

// Forward declarations
bool OnButtonDown(CWidget * a_pWidget);
bool OnTextEntered(std::string a_strText,CWidget * a_pWidget);


CustomProgram::CustomProgram(int a_nScreenWidth, int a_nScreenheight, bool a_blFullscreen)
:A5Program(a_nScreenWidth, a_nScreenheight, a_blFullscreen,false)
{
    g_pFontPath  = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_set_path_filename(g_pFontPath,"1.ttf");
    m_pFont = al_load_ttf_font(al_path_cstr(g_pFontPath,ALLEGRO_NATIVE_PATH_SEP),10,0);


    // build widgets
    CWidget::INIT_GUI(m_pFont);

    m_pMainWidget = new CPanel(NULL,10,10,800,600);
    m_pMainWidget->SetBorderStyle(bsNONE);

    CWidget * pFlatChild = new CPanel(NULL,20,20, 600,400);
    m_pMainWidget->AddChild(pFlatChild);

    CWidget * pChild = new CPanel(NULL,0,0, 60,60);
    pChild->SetBorderStyle(bsRAISED);
    pFlatChild->AddChild(pChild);

    pChild = new CPanel(NULL,80,30, 60,60);
    pChild->SetBorderStyle(bsLOWERED);
    pFlatChild->AddChild(pChild);

    pChild = new CButton(NULL,10,200, 100,50,"OK");
    pChild->RegisterOnClickHandler(OnButtonDown);
    pFlatChild->AddChild(pChild);

    CEdit * pEdit = new CEdit(NULL,10,300,100,20);
    pEdit->RegisterOnEnterHandler(OnTextEntered);
    pFlatChild->AddChild(pEdit);

}


CustomProgram::~CustomProgram()
{
    // free used memory
    delete(m_pMainWidget);
}


void CustomProgram::DispatchEvent(ALLEGRO_EVENT * a_pEvent)
{
    //send events to widgets
    m_pMainWidget->SendEvents(a_pEvent);
}


void CustomProgram::OnKeyDown(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent)
{
    switch(a_KeyboardEvent.keycode)
    {
        case ALLEGRO_KEY_ESCAPE:
               Quit();
             break;

    }
}

void CustomProgram::OnKeyUp(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent)
{

}


void CustomProgram::OnMouseMove(const ALLEGRO_MOUSE_EVENT & a_MouseEvent)
{



}

void CustomProgram::OnMouseButtonDown(const ALLEGRO_MOUSE_EVENT & a_MouseEvent)
{

}

void CustomProgram::OnMouseButtonUp(const ALLEGRO_MOUSE_EVENT & a_MouseEvent)
{

}




void CustomProgram::OnUpdate(double a_dLagTime)
{


}



void CustomProgram::OnDraw()
{
    if (m_pMainWidget!=NULL)
    {
        m_pMainWidget->Draw();
    }
}

void CustomProgram::OnTimer()
{


}


bool OnButtonDown(CWidget * a_pWidget)
{
  if (a_pWidget->GetWidgetType()==wtBUTTON)
  {
      ((CButton *)a_pWidget)->SetCaption("I was clicked !");
  }


  return true;
}


bool OnTextEntered(std::string a_strText,CWidget * a_pWidget)
{
    std::string strTemp = a_strText;

}




