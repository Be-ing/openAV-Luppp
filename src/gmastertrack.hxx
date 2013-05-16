
#ifndef LUPPP_G_MASTER_TRACK_H
#define LUPPP_G_MASTER_TRACK_H

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>

#include "avtk/avtk_dial.h"
#include "avtk/avtk_button.h"
#include "avtk/avtk_background.h"


#include "eventhandler.hxx"

using namespace std;

static void gmastertrack_button_callback(Fl_Widget *w, void *data) {
  
  
  int track = 0;
  if ( data )
   track = *(int*)data;
  
  cout << "Button " << track << " " << w->label() << " clicked" << endl;
  
  if ( strcmp( w->label() , "Rec" ) == 0 )
  {
    EventLooperState e = EventLooperState(track,Looper::STATE_RECORD_QUEUED);
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label() , "Play" ) == 0 )
  {
    EventLooperState e = EventLooperState(track,Looper::STATE_PLAY_QUEUED);
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label() , "Stop" ) == 0 )
  {
    EventLooperState e = EventLooperState(track,Looper::STATE_STOP_QUEUED);
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label() , "+" ) == 0 )
  {
    EventLooperLoopLength e = EventLooperLoopLength(track, 2);
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label() , "-" ) == 0 )
  {
    EventLooperLoopLength e = EventLooperLoopLength(track, 0.5);
    writeToDspRingbuffer( &e );
  }
  else if ( strcmp( w->label(), "Metro" ) == 0 )
  {
    Avtk::Button* b = (Avtk::Button*)w;
    b->value( !b->value() );
    EventMetronomeActive e = EventMetronomeActive( b->value() );
    writeToDspRingbuffer( &e );
  }
  else
  {
    cout << __FILE__ << __LINE__ << " Error: unknown command string" << endl;
  }
}

class GMasterTrack : public Fl_Group
{
  public:
    GMasterTrack(int x, int y, int w, int h, const char* l = 0 ) :
      Fl_Group(x, y, w, h),
      title( strdup(l) ),
      bg( x, y , w, h, title ),
      /*
      button1(x + 5, y + 24, 100, 18,"Rec"),
      button2(x + 5, y + 44, 100, 18,"Play"),
      button3(x + 5, y + 64, 100, 18,"Stop"),
      button4(x + 5, y + 84,  48, 18,"-"),
      button5(x +57, y + 84,  48, 18,"+"),
      button6(x + 5, y +104, 18, 18,"6"),
      */
      metronomeButton(x + 5,y + 24,140,30,"Metro")
      /*
      dial1(x+15, y +155, 24, 24, "A"),
      dial2(x+45, y +155, 24, 24, "B"),
      dial3(x+75, y +155, 24, 24, "C")
      */
    {
      ID = privateID++;
      /*
      button1.callback( gmastertrack_button_callback, &ID );
      button2.callback( gmastertrack_button_callback, &ID );
      button3.callback( gmastertrack_button_callback, &ID );
      button4.callback( gmastertrack_button_callback, &ID );
      button5.callback( gmastertrack_button_callback, &ID );
      button6.callback( gmastertrack_button_callback, &ID );
      */
      metronomeButton.callback( gmastertrack_button_callback, 0 );
      
      end(); // close the group
    }
    
    ~GMasterTrack()
    {
      free(title);
    }
    
  
  private:
    int ID;
    
    char* title;
    
    Avtk::Background bg;
    /*
    Avtk::Button button1;
    Avtk::Button button2;
    Avtk::Button button3;
    Avtk::Button button4;
    Avtk::Button button5;
    Avtk::Button button6;
    */
    Avtk::LightButton metronomeButton;
    /*
    Avtk::Dial dial1;
    Avtk::Dial dial2;
    Avtk::Dial dial3;
    */
    
    static int privateID;
};

#endif // LUPPP_G_MASTER_TRACK_H
