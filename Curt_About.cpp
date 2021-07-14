//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Curt_About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCurtAbout *CurtAbout;
//#define CURTABOUTDEBUG
//---------------------------------------------------------------------------
__fastcall TCurtAbout::TCurtAbout(TComponent* Owner)
	: TForm(Owner)
{
 fy=ly=2018;
 ver = "1.0";
}
//---------------------------------------------------------------------------

void TCurtAbout::Copyright(int first, int last){
 fy = first;
 ly = last;
}

void TCurtAbout::Description(const String & s,int size){
 RichEdit1->Lines->Add(s);
 RichEdit1->Font->Size = size;
}


void __fastcall TCurtAbout::AboutClose(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TCurtAbout::ShowMe(TObject *Sender)
{
 //
  // Do some formatting
  CopyWLabel->Caption = String(L" © ")+String(fy)+" - "+
						 ly + " by Curt Hill";
  VerLabel->Caption = String("Version: ")+ver;
  VerLabel->Alignment = taCenter;
  #ifdef CURTABOUTDEBUG
	DebugLabel->Caption = String(L"Image Left, Width ")+Image1->Left+L", "+Image1->Width+L"  "+RichEdit1->Left;
    #endif
}
//---------------------------------------------------------------------------

void __fastcall TCurtAbout::Sizing(TObject *Sender)
{
 RichEdit1->Left = Image1->Left + Image1->Width - 60;
 RichEdit1->Width = Width - (RichEdit1->Left + 24);
}
//---------------------------------------------------------------------------

