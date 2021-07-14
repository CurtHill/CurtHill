//---------------------------------------------------------------------------

#ifndef ProjFormH
#define ProjFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include "projectionscreen.h"
#include <Vcl.MPlayer.hpp>
#include <Vcl.ComCtrls.hpp>
#define FORMMAX 6

//#define PFORMDEBUG


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Clear1;
	TMenuItem *Save1;
	TMenuItem *Exit1;
	TMenuItem *Help1;
	TMenuItem *Warranty1;
	TMenuItem *Contribute1;
	TMenuItem *About1;
	TSaveDialog *SaveDialog1;
	TMenuItem *Display1;
	TOpenDialog *OpenDialog1;
	TMenuItem *One1;
	TMenuItem *wo1;
	TMenuItem *Four1;
	TMenuItem *Diagnose1;
	TMenuItem *Diagnose2;
	TMenuItem *Shiftconsole2;
	TMenuItem *Reverseshiftconsole1;
	TMenuItem *hree1;
	TMenuItem *Refresh1;
	TMenuItem *Play1;
	TMenuItem *Userguide1;
	TRichEdit *Memo1;
	TMenuItem *fIve1;
	TMenuItem *Six1;
	void __fastcall AboutMe(TObject *Sender);
	void __fastcall WarrantyClick(TObject *Sender);
	void __fastcall Contrib(TObject *Sender);
	void __fastcall Clarity(TObject *Sender);
	void __fastcall SaveMemo(TObject *Sender);
	void __fastcall Sizing(TObject *Sender);
	void __fastcall DoTwoDisplay(TObject *Sender);
	void __fastcall DoOneDisplay(TObject *Sender);
	void __fastcall DoFourDisplays(TObject *Sender);
	void __fastcall AllDone(TObject *Sender);
	void __fastcall Shifter(TObject *Sender);
	void __fastcall StartMovies(TObject *Sender);
	void __fastcall Diagnoser(TObject *Sender);
	void __fastcall DeShifter(TObject *Sender);
	void __fastcall ReallyThree(TObject *Sender);
	void __fastcall Refresh(TObject *Sender);
	void __fastcall Instructions(TObject *Sender);
	void __fastcall FiveDisplays(TObject *Sender);
	void __fastcall Sixer(TObject *Sender);

private:	// User declarations
		String myPath,error_message;
		FormPtr forms[FORMMAX];
		int form_counts, mix_count;
		int active_monitors;
		int console_monitor;
		int running;
	  #ifdef PFORMDEBUG
		logger pflog;
		#endif
		void __fastcall DisplayAPIError(String context);
		void __fastcall MouseMover(unsigned x, unsigned y);
		void __fastcall ShiftFarRight();
		void __fastcall CheckMonitors();
		void __fastcall LoadVideos(int count);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall Ended(TProjectionForm *);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
