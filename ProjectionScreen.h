//---------------------------------------------------------------------------

#ifndef ProjectionScreenH
#define ProjectionScreenH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.MPlayer.hpp>
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TProjectionForm : public TForm
{
__published:	// IDE-managed Components
	TMediaPlayer *MediaPlayer1;
	TMemo *Memo1;
	TTimer *Timer1;
	void __fastcall Sizing(TObject *Sender);
	void __fastcall Clicker(TObject *Sender, TMPBtnType Button, bool &DoDefault);
	void __fastcall KillMe(TObject *Sender);
	void __fastcall TimerFired(TObject *Sender);
private:	// User declarations
	int HResolution, VResolution,ID;
	bool Started, valid;

	void __fastcall DisplayAPIError(String context, DWORD err=0);
	void __fastcall SetTimerLength();
	bool __fastcall SetType(String filename);
public:		// User declarations
	__fastcall TProjectionForm(TComponent* Owner);
	bool __fastcall SetVideo(String name1);
	void __fastcall SetResolution(int w,int h);
	int __fastcall GetWidth(){ return HResolution; }
	bool __fastcall Prepare(int left,String & error);
	bool __fastcall Start();
	void __fastcall StopIt();
	void __fastcall SetID(int);
	// Need to figure this one out
	void __fastcall Mute(bool mute);
};
//---------------------------------------------------------------------------
extern PACKAGE TProjectionForm *ProjectionForm;
typedef  TProjectionForm * FormPtr;
//---------------------------------------------------------------------------
#endif
