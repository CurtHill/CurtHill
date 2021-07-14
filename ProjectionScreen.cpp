//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProjectionScreen.h"
#include "projform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProjectionForm *ProjectionForm;
//---------------------------------------------------------------------------
__fastcall TProjectionForm::TProjectionForm(TComponent* Owner)
	: TForm(Owner)
{
 HResolution=768*2;
 VResolution = 1024*2;
 valid = false;
 ID = -1;
}
//---------------------------------------------------------------------------

bool __fastcall TProjectionForm::SetVideo(String name1){

  if(name1 != NULL){
	if(!SetType(name1))
	  return false;
	MediaPlayer1->FileName = name1;
	valid = true;
	}
  else {
	Memo1->Lines->Add(L"A NULL received a null name1");
	valid = false;
	}
  return valid;
}

bool __fastcall TProjectionForm::SetType(String filename){
 int pos = filename.LastDelimiter(L".");
 if(pos < 1){
   MediaPlayer1->DeviceType = dtAutoSelect;
   return true;
   }
 String ext = filename.SubString(pos+1,10).UpperCase();
 if(ext == L"MP4"){
   MediaPlayer1->DeviceType = dtMMMovie;
   return false;
   }
 return true;
}

void __fastcall TProjectionForm::SetResolution(int h,int v){
 HResolution = h;
 VResolution = v;
}

void __fastcall TProjectionForm::DisplayAPIError(String context, DWORD err){
   if(err == -3) return;
   if(err == 0)
	 err = GetLastError();
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

void __fastcall TProjectionForm::Mute(bool mute){
 /* This one did not work - mutes whole thing
 if(mute){
   INPUT inp[1];
   inp[0].type = INPUT_KEYBOARD;
   inp[0].ki.wVk = vkVolumeMute;
   inp[0].ki.dwFlags = 0;
   inp[0].ki.time = 0;
   UINT result = SendInput(1, // number of keys sent
						   inp,
						   sizeof (INPUT));
   }
 */
}

bool __fastcall TProjectionForm::Prepare(int left,String & error){
   Top = 0;
   Left = left;
   WindowState = wsMinimized;
   //ClientHeight = VResolution;
   //ClientWidth = HResolution;
   Height = VResolution;
   Width = HResolution;
   //MediaPlayer1->Top = Top;
   //MediaPlayer1->Left = Left;
   MediaPlayer1->Height = Height;
   MediaPlayer1->Width = Width;
   MediaPlayer1->Wait = true;
   try{
	 MediaPlayer1->Open();
	 if(MediaPlayer1->Error != 0){
	   error = MediaPlayer1->ErrorMessage;
       return false;
	   }
	 //MediaPlayer1->Play();
	 MediaPlayer1->Wait = false;
	 //MediaPlayer1->Pause();
   }
   catch (...){
	 int err = GetLastError();
	 DisplayAPIError(L"The open problem: ",err);
	 String temp = L"Could not open ";
	 temp = temp + MediaPlayer1->ErrorMessage;
	 error = temp;
	 //Application->MessageBoxW(temp.c_str(),L"Now what?",MB_OK);
	 BorderStyle = bsSizeable;
	 WindowState = wsMinimized;
	 Close();
	 return false;
	 }
  MediaPlayer1->Wait = true;
  return true;
}


bool __fastcall TProjectionForm::Start(){
   BorderStyle = bsNone;
   WindowState = wsMaximized;
   MediaPlayer1->Wait = false;
   Memo1->Visible = false;
   // Debug
   String x = MediaPlayer1->FileName;
   try{
	MediaPlayer1->Play();
   }
   catch (...){
	 DisplayAPIError(L"Play failed: ");
	 Application->MessageBoxW(L"Could not play",L"Now what?",MB_OK);
	 return false;
	 }
//   MediaPlayer1->Notify = true;
//   Started = true;
   SetTimerLength();
   return true;
}

void __fastcall TProjectionForm::Sizing(TObject *Sender)
{
   Memo1->Height = Height;
   Memo1->Width = Width;
}
//---------------------------------------------------------------------------

void __fastcall TProjectionForm::Clicker(TObject *Sender, TMPBtnType Button, bool &DoDefault)

{
 MediaPlayer1->Stop();
 BorderStyle = bsSizeable;
 WindowState = wsNormal;
 Form1->Ended(this);
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TProjectionForm::KillMe(TObject *Sender)
{
 //MediaPlayer1->Stop();

 Close();
}
//---------------------------------------------------------------------------

void __fastcall TProjectionForm::StopIt(){
  //MediaPlayer1->Stop();
  Close();
}

void __fastcall TProjectionForm::SetID(int i){
  ID = i;
  Memo1->Clear();
  Memo1->Lines->Add(String(L"")+ID);
}


void __fastcall TProjectionForm::SetTimerLength(){
  int len = MediaPlayer1->Length;
  switch(MediaPlayer1->TimeFormat){
	case tfHMS:
	  len = (len&0x00FF) *60*60*1000 + ((len>>8)&0x00ff)*60*1000 + ((len>>16)&0x00FF)*1000;
	  break;
	case tfMSF:
	  len = len & 0x00ffff;
	  len = (len&0x00ff)*60*1000 + ((len>>8)&0x00FF)*1000;
	  break;
	/*
	case tfMilliseconds:
	  break;
	case tfFrames:
	  break;
	case tfSMPTE24:
	  break;
	case tfSMPTE25:
	  break;
	case tfSMPTE30:
	  break;
	case tfSMPTE30Drop:
	  break;
	case tfBytes:
	  break;
	case tfSamples:
	  break;
	case tfTMSF:
	  break;
	default:
	  ;
	*/
	} // Switch
  Timer1->Interval = len+1000;
  Timer1->Enabled = true;
}

void __fastcall TProjectionForm::TimerFired(TObject *Sender)
{
 // Close off things
   Timer1->Enabled = false;
   BorderStyle = bsSizeable;
   WindowState = wsNormal;
   MediaPlayer1->Visible = false;
   Memo1->Visible = true;
   MediaPlayer1->Close();
   Form1->Ended(this);
   Close();
}
//---------------------------------------------------------------------------

