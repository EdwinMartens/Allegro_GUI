#ifndef A5_PROGRAM
#define A5_PROGRAM

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <exception>
#include <string>

using namespace std;

class A5Program
{
    public:
    A5Program(int a_nScreenWidth, int a_nScreenheight, bool a_blFullscreen, bool a_blEnableSound);
    void SetTimer(int a_nTimeInterval);

    virtual ~A5Program();

    // handle all current events, returns false on program close
    bool HandleEvents();

    void Quit();

    inline ALLEGRO_DISPLAY * GetDisplay()
    {
        return m_pDisplay;
    }

    protected:

    // event handlers
    virtual void OnKeyDown(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent);
    virtual void OnKeyUp(const ALLEGRO_KEYBOARD_EVENT & a_KeyboardEvent);
    virtual void OnMouseMove(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnMouseButtonDown(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnMouseButtonUp(const ALLEGRO_MOUSE_EVENT & a_MouseEvent);
    virtual void OnTimer();
    virtual void OnDraw();
    virtual void OnUpdate(double a_dLagTime);
    virtual void DispatchEvent(ALLEGRO_EVENT * a_pEvent);

    private:

    double m_dLastTime;


    static A5Program * s_pProgram;

    // Render display
    ALLEGRO_DISPLAY     * m_pDisplay;

    // the event queue
    ALLEGRO_EVENT_QUEUE * m_pEventQueue;

    // game timer
    ALLEGRO_TIMER       * m_pTimer;

    // Shutdown game engine ?
    bool m_blExit;



};





#endif // A5_PROGRAM
