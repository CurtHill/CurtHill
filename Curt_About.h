//---------------------------------------------------------------------------

#ifndef Curt_AboutH
#define Curt_AboutH
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <System.RegularExpressions.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TCurtAbout : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label3;
	TLabel *CopyWLabel;
	TLabel *Label1;
	TLabel *Label2;
	TButton *Button1;
	TLabel *VerLabel;
	TImage *Image1;
	TRichEdit *RichEdit1;
	TLabel *DebugLabel;
	void __fastcall AboutClose(TObject *Sender);
	void __fastcall ShowMe(TObject *Sender);
	void __fastcall Sizing(TObject *Sender);
private:	// User declarations
        int fy,ly;

		String ver;
public:		// User declarations
	__fastcall TCurtAbout(TComponent* Owner);
		void Copyright(int first, int last);
		void Description(const String & s, int size = 12);
		void Version(const String & s){ver = s;};
};
//---------------------------------------------------------------------------
extern PACKAGE TCurtAbout *CurtAbout;
//---------------------------------------------------------------------------
#endif
