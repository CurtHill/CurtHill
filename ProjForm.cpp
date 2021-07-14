/*
  Program designed for VCSU planetarium.
  To project a different full screen video on 1,2,4 screens

 Version history.
 1.0 - 6/3/2019
   Installer created and posted on website.
 1.01 - 6/3/2019 - After first install file created.
   When console is shifted, move the mouse close to it.
 1.02 - 6/11/2019
   Set a timer when a video starts. When it finishes the window is closed.
   WMV files were added to possible videos.
 1.03 - 3/18/2020
   After Planetarium was rewired there were many issues - most not mine.
   However, four movies thing did not work.
   Added diagnose to get coordinates, since the monitors were oddly numbered.
   There was an abort after movie finished - caused by a timer not shut off.
   Display much more on the memo than before.
   Ender was changed not to stop something that should stop itself
 1.04 - 7/8/2021
   Not so small maintenance upgrade in preparation for having a big push to
   use all four monitors correctly. Added Refresh and CheckMonitors.
   Projection screen now checks that the extension is correct. Change the Display
   menu, to a Load videos and then add a Play to start them.
   If there are more monitors than videos, move the console and mouse to last
   one. MP4 do not work so remove them from filter.
   Apparently a minimized MediaPlayer will play the audio but not the video,
   therfore the player is minimized during preparation and maximized when started.
 1.05 - 7/12/2021
   Generalized the load videos into event handlers and loop driven initializer.
*/


#include <vcl.h>
#pragma hdrstop

#include "ProjForm.h"
#include "D:\\projects_2\\Objects\\About\\Curt_About.h"
#include "D:\\projects_2\\Objects\\userlog\\userlog.h"
#include <highlevelmonitorconfigurationapi.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

const AnsiString version = "1.05";

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
	#ifdef PFORMDEBUG
	  , // Yes we need this
	  pflog(L"d:\\projects_2\\planetarium\\PForm.log")
	  #endif
{
 Form1->Caption = String(L"Planetarium Projection - Version: ") + version;
 // Some generalities that may come in handy
 int count = ParamCount();
 Memo1->Lines->Add(String("Number of parameters: ")+count);
 // ParamStr(0) is path and exec file name
 myPath = ParamStr(0);
 if(count) {
   for(int i = 0;i<=count;i++) {
	 String st = ParamStr(i);
	 Memo1->Lines->Add(String()+i+": "+st);
	 if(st[1] == '-' || st[1] == '/'){
		// a commandline directive
		}
	 else {
		// Probably a file name
	 }
   } // for processing parameters
 } // if checking for parameters
 int pos = myPath.LastDelimiter("\\");
 myPath = myPath.SubString(1,pos);
 #ifdef PFORMDEBUG
   Memo1->Lines->Add("Program: "+myPath);
   Memo1->Lines->Add("Originating directory: "+myPath);
   #endif
 CheckMonitors();
 forms[0] = ProjectionForm;
 form_counts=1;
 for(int i = 1;i<FORMMAX;i++)
	forms[i] = NULL;
}


void __fastcall TForm1::CheckMonitors(){
 console_monitor = 0;
 Memo1->Lines->Add(String("Monitors: ")+Screen->MonitorCount);
 for (int i = 0; i < Screen->MonitorCount; i++){
   Memo1->Lines->Add(String(" ")+Screen->Monitors[i]->MonitorNum+":   Width: "+Screen->Monitors[i]->Width+
			", Height: "+Screen->Monitors[i]->Height+", "+(Screen->Monitors[i]->Primary?"Primary":"Not primary"));
   } // for
}


void __fastcall TForm1::Refresh(TObject *Sender)
{
 Memo1->Clear();
 CheckMonitors();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DisplayAPIError(String context){
   DWORD err = GetLastError();
   wchar_t * msg2 = new wchar_t [9000];
   FormatMessage(
	  FORMAT_MESSAGE_FROM_SYSTEM,
	  NULL,
	  err,
	  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
	  (LPTSTR) msg2, 9000, NULL);
   context += msg2;
   Application->MessageBox(context.c_str(),L"Error",MB_OK);
   delete [] msg2;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::AboutMe(TObject *Sender)
{
  CurtAbout->Copyright(1999,2021);
  CurtAbout->Version(version);
  CurtAbout->Description("This program drives the multiple screens of the VCSU Planetarium. It may drive 1, 2 or 4 screens. It must have the same number of videos as screens. Only one of these should have sound.");
  CurtAbout->Show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WarrantyClick(TObject *Sender)
{
 Application->MessageBox(L"The program is unconditionally unwarranted. In particular, since you paid nothing, if this thing wrecks your computer, your car, your stock portfolio or your relationships you have absolutely no legal rights for compensation. Is that clear enough?",L"You got to be kidding!",MB_OK);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Contrib(TObject *Sender)
{
Application->MessageBox(L"I did not create this program to make money, nor is my financial security dependent on your sending something. Anything you send will will be appreciated, even if it will not make a difference in my budget, since I do have a good position. However, if you use this program and find it useful, then a contribution for the sake of conscience is appropriate. Since I do move occasionally, Google \"Curt Hill\" and see where I may be residing these days. Thanks for the thought.",L"Is this program valuable?",MB_OK);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Clarity(TObject *Sender)
{
 Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AllDone(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveMemo(TObject *Sender)
{
 if(SaveDialog1->Execute()){
	Memo1->Lines->SaveToFile(SaveDialog1->FileName);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Sizing(TObject *Sender)
{
 //int xedge = GetSystemMetrics(SM_CXEDGE);
 //int yedge = GetSystemMetrics(SM_CYEDGE);
 int buttonHeight = 0; // Set this to put buttons at bottom
 int menuHeight = GetSystemMetrics(SM_CYMENU)+1;
 int ytitle = GetSystemMetrics(SM_CYMIN);
 int margins = GetSystemMetrics(SM_CXFIXEDFRAME);
 int xborder = GetSystemMetrics(SM_CXFRAME);
 //int yborder = GetSystemMetrics(SM_CYFRAME);
 // Resize the window
 Memo1->Width = Width - (Memo1->Left + xborder*2 + 2*margins);
 Memo1->Height = Height - (Memo1->Top + ytitle
						  + menuHeight + 2*margins + buttonHeight);

}

void __fastcall TForm1::ShiftFarRight(){
  WindowState = wsNormal;
 if(active_monitors < Screen->MonitorCount){ // last screen is console
   Form1->Left = 10; // Reset if moved
   for(int i=0;i<active_monitors;i++){
	 Form1->Left = Form1->Left + forms[i]->GetWidth();
	 } // for
   MouseMover(Form1->Left+ 30,200);
   }
}

void __fastcall TForm1::DoOneDisplay(TObject *Sender)
{
 active_monitors = 0;
 LoadVideos(1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DoTwoDisplay(TObject *Sender)
{
 active_monitors = 0;
 if(Screen->MonitorCount < 2){
   Application->MessageBoxW(L"Not enough monitors for this request",L"Entry error",MB_OK);
   return;
   }
 LoadVideos(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ReallyThree(TObject *Sender)
{
 active_monitors = 0;
 if(Screen->MonitorCount < 3){
   Application->MessageBoxW(L"Not enough monitors for this request",L"Entry error",MB_OK);
   return;
   }
 LoadVideos(3);
}

//---------------------------------------------------------------------------


void __fastcall TForm1::DoFourDisplays(TObject *Sender)
{
 if(Screen->MonitorCount < 4){
   Application->MessageBoxW(L"Not enough monitors for this request",L"Entry error",MB_OK);
   return;
   }
 LoadVideos(4);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FiveDisplays(TObject *Sender)
{
 if(Screen->MonitorCount < 5){
   Application->MessageBoxW(L"Not enough monitors for this request",L"Entry error",MB_OK);
   return;
   }
 LoadVideos(5);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Sixer(TObject *Sender)
{
 if(Screen->MonitorCount < 6){
   Application->MessageBoxW(L"Not enough monitors for this request",L"Entry error",MB_OK);
   return;
   }
 LoadVideos(6);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LoadVideos(int count){
 active_monitors = 0;

 for(int i = 0;i<count;i++)
   if(forms[i] == NULL){
	 forms[i] = new TProjectionForm(this);
	 forms[i]->SetID(i);
	 form_counts++;
	 }
 String * videonames = new String [count];
 String vname;
 bool prepared = true, unique, mute = false;
 int used_width = 1;
 for(int i = 0;i<count;i++){
   // Get a unique file name for each screen
   do {
	 OpenDialog1->FileName = "";
	 unique = true;
	 OpenDialog1->Title = String(L"Select video ")+i;
	 if(OpenDialog1->Execute()){
	   vname = OpenDialog1->FileName;
	   }
	  else {
	   Memo1->Lines->Add(L"Video load cancelled");
	   delete [] videonames;
	   return;
	   }
	 // Check that this is not duplicated - videos cannot be shared
	 for(int j = 0;j<i;j++){
	   if (videonames[j] == vname) {
		 unique = false;
		 Application->MessageBoxW(L"Each video must be unique - a video cannot be shared between two screens",L"Error",MB_OK);
		 break;
		 }
	   } // duplicate checking for
	 videonames[i] = vname;
	 if(!forms[i]->SetVideo(vname)){
		 Memo1->Lines->Add(String(L"Unsupported video type: ")+vname);
		 unique = false;
		 }
	  }
	 while(!unique);
	 Memo1->Lines->Add(vname);
	 forms[i]->SetResolution(Screen->Monitors[i]->Width,Screen->Monitors[i]->Height);
	 Memo1->Lines->Add(String(L"Monitor ")+i+L" width, height "+Screen->Monitors[i]->Width+L", "+Screen->Monitors[i]->Height);
	 forms[i]->Show();
	 bool OK = forms[i]->Prepare(used_width,error_message);
     forms[i]->Mute(mute);
	 if(!OK){
		Memo1->Lines->Add(String(L"Could not prepare monitor ")+i+L": "+error_message);
		prepared = false;
		}
	 used_width += Screen->Monitors[i]->Width;
	 mute = true;
   } // end big for

 if(!prepared){
	Memo1->Lines->Add(L"Could not start. ");
	delete [] videonames;
	return;
   }
 active_monitors = count;
 delete [] videonames;
}

void __fastcall TForm1::StartMovies(TObject *Sender)
{
  ShiftFarRight();
  WindowState = wsMinimized;
  running = 0;
  for(int i = 0;i<active_monitors;i++)
	if(!forms[i]->Start()){
	  Memo1->Lines->Add(String(L"Form ")+i+L" did not start properly.");
	  }
	else running++;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Ended(TProjectionForm * theone){
  // the one phoned home to say he had stopped
  for(int i=0;i<form_counts;i++)
	if(theone == forms[i]){
	   Memo1->Lines->Add(String(L"Screen number ")+i+L" is done");
	   running--;
	   }
   if(running < 1)
	 WindowState = wsNormal;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Shifter(TObject *Sender)
{
 // Shift console
 if(++console_monitor >= Screen->MonitorCount){
   Left = 20;
   console_monitor = 0;
   }
 else
   Left += Screen->Monitors[console_monitor]->Width;
 MouseMover(Left+50, Top-10);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeShifter(TObject *Sender)
{
 if(--console_monitor >= 1){
   Left = 20;
   console_monitor = 0;
   }
 else
   Left -= Screen->Monitors[console_monitor]->Width;
 MouseMover(Left+50, Top-10);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::MouseMover(unsigned x, unsigned y){
 x = double(x)/Screen->Monitors[console_monitor]->Width*65535;
 y = double(y)/Screen->Monitors[console_monitor]->Height*65535;
 INPUT input[4];
 input[0].type = INPUT_MOUSE;
 input[0].mi.dx = x;
 input[0].mi.dy = y;
 input[0].mi.mouseData = 0;
 input[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
 input[0].mi.time = 0;
 input[0].mi.dwExtraInfo = 0;
 unsigned res = SendInput(1, input,sizeof(INPUT));
}

void __fastcall TForm1::Diagnoser(TObject *Sender)
{
 // Display position
 Memo1->Lines->Add(String(L"Current position ")+L"("+Left+L", "+Top+L")");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Instructions(TObject *Sender)
{
 // Load the instructions into the memo
 Memo1->Lines->LoadFromFile(L".\\Projection.rtf");
}
//---------------------------------------------------------------------------


