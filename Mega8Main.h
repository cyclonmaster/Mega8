/***************************************************************
 * Name:      Mega8Main.h
 * Purpose:   Defines Application Frame
 * Author:    Junta (junta@hotmail.be)
 * Created:   2014-07-24
 * Copyright: Junta (http://www.ready4next.be)
 * License:
 **************************************************************/

#ifndef Mega8MAIN_H
#define Mega8MAIN_H

//(*Headers(Mega8Frame)
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <wx/wx.h>
#include <wx/string.h>
#include "Chip8/Chip8.h"
#include "include/Chip8GL.h"
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <math.h>

// declare a new type of event, to be used by our CpuThread class:
wxDECLARE_EVENT(wxEVT_COMMAND_CPUTHREAD_COMPLETED, wxThreadEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_CPUTHREAD_UPDATE, wxThreadEvent);

const float FREQ_MENU_INDEX[] = { 1, 2, 10, 40, 80, 160, 320, 640, 1280, 10240, 40960 };
const int   SIZE_MENU_INDEX[] = { 1, 2, 3, 4, 5, 10 };

class Mega8Frame;

class CPUThreadHandler: public wxThread
{
public:
    CPUThreadHandler(Mega8Frame *handler): wxThread(wxTHREAD_DETACHED) { _handler = handler; }
    ~CPUThreadHandler();
protected:
    virtual ExitCode Entry();
    Mega8Frame *_handler;
};

class Mega8Frame: public wxFrame
{
    friend class CPUThreadHandler;

    public:

        Mega8Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Mega8Frame();

        void OnKeyDown(wxKeyEvent& event);
        void OnKeyUp(wxKeyEvent& event);

    protected:

        Chip8 *_machine;
        long _frequency;
        int _freqCoeff;
        CPUThreadHandler *_CPUThread;
        wxCriticalSection _CPUThreadCS;       // Protect the thread

        void DoStartCPUThread();
        void DoPauseCPUThread();
        void DoResumeCPUThread();
        void OnCPUThreadUpdate(wxThreadEvent&);
        void OnCPUThreadCompletion(wxThreadEvent&);
        void DeleteCPUThread();
        void updateFrequency(int Multiplicator);

        void DoOpen();
        void Reset();
        void CloseRom();
        void updateStatus();
        void SetSyncClock(bool value);
        void SetFiltered(bool value);

        void onIdle(wxIdleEvent &event);
        void OnPaint(wxPaintEvent &event);

    private:

        wxString CurrentRomPath;
        wxString CurrentRomDir;
        bool _Paused;
        bool _FullScreen;
        wxWindow *_parent;

        //(*Handlers(Mega8Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnCPUCycleTrigger(wxTimerEvent& event);
        void OnRendererTrigger(wxTimerEvent& event);
        void OnFilter(wxCommandEvent& event);
        void OnReset(wxCommandEvent& event);
        void OnPause(wxCommandEvent& event);
        void OnMenuClose(wxCommandEvent& event);
        void OnMenuSpeedSelected(wxCommandEvent& event);
        void OnMenuSizeSelected(wxCommandEvent& event);
        void OnMenuSyncClock(wxCommandEvent& event);
        void OnChooseColorTheme(wxCommandEvent& event);
        void OnMenuColorInverse(wxCommandEvent& event);
        void OnMenuDisplayHUDSelected(wxCommandEvent& event);
        void OnMenuCheckKeypadSelected(wxCommandEvent& event);
        //*)



        //(*Identifiers(Mega8Frame)
        static const long idMenuOpen;
        static const long idMenuClose;
        static const long idMenuQuit;
        static const long idMenuReset;
        static const long idMenuPause;
        static const long idMenuCTDefault;
        static const long idMenuCTC64;
        static const long idMenuCTGameBoy;
        static const long idMenuCTRed;
        static const long idMenuCTGreen;
        static const long idMenuCTBlue;
        static const long idMenuCTInverse;
        static const long ID_MENUITEM3;
        static const long idMenuSpeedAuto;
        static const long idMenuSpeedDiv40;
        static const long idMenuSpeedDiv20;
        static const long idMenuSpeedDiv4;
        static const long idMenuSpeed1;
        static const long idMenuSpeed2;
        static const long idMenuSpeed4;
        static const long idMenuSpeed8;
        static const long idMenuSpeed16;
        static const long idMenuSpeed32;
        static const long idMenuSpeed256;
        static const long idMenuSpeed1024;
        static const long idSyncToBase;
        static const long idMenuSpeed;
        static const long idMenuDisplayHUD;
        static const long idMenuFiltered;
        static const long idMenuSize1x1;
        static const long idMenuSize2x2;
        static const long idMenuSize3x3;
        static const long idMenuSize4x4;
        static const long idMenuSize5x5;
        static const long idMenuSize10x10;
        static const long idMenuFullScreen;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM2;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        static const long idChipGLCanvas;
        static const int StatusBarFieldsStatus;
        static const int StatusBarFieldsMode;
        static const int StatusBarFieldsResolution;
        static const int StatusBarFieldsFrequency;
        static const int StatusBarFieldsSound;
        static const int StatusBarFieldsFramePerSec;

        //(*Declarations(Mega8Frame)
        wxMenuItem* MenuSpeed256;
        wxMenuItem* MenuSpeed1024;
        wxMenuItem* MenuSpeedDiv20;
        wxMenuItem* MenuItem16;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuSpeedDiv4;
        wxMenu* Menu3;
        wxMenuItem* MenuItem19;
        wxMenuItem* MenuItem20;
        wxMenuItem* MenuSpeedDiv40;
        wxMenuItem* MenuItem15;
        wxMenuItem* MnuSyncClock;
        wxMenuItem* MenuItem21;
        wxMenuItem* MenuItem17;
        wxMenuItem* MenuSpeed2;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem9;
        wxMenu* Menu4;
        wxMenu* MenuItem5;
        wxMenuItem* MenuSpeed8;
        wxMenuItem* MenuSize1;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuSpeedAuto;
        wxMenuItem* MnuFilter;
        wxMenuItem* MenuDisplayHUD;
        wxMenuBar* MenuBar1;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem18;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuSpeed32;
        wxStatusBar* StatusBar;
        wxMenuItem* MenuItem13;
        wxMenuItem* MenuCheckKeypad;
        wxMenuItem* MenuSpeed1;
        wxMenu* MenuItem8;
        wxMenuItem* MenuSpeed4;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuSpeed16;
        //*)

        Chip8GL *GLDisplay;

        DECLARE_EVENT_TABLE()
};

#endif // Mega8MAIN_H
