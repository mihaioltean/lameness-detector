//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
#include <Buttons.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

#include "lista_voidp.h"
#include <ComCtrls.hpp>

class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPanel *pxLeftFata;
	TSplitter *Splitter1;
	TPanel *pToolBar;
	TPanel *pyLeftFata;
	TSplitter *Splitter2;
	TPanel *pzLeftFata;
	TImage *iyLeftFata;
	TImage *izLeftFata;
	TBitBtn *bStart;
	TBitBtn *bRecord;
	TBitBtn *bLoad;
	TImage *ixLeftFata;
	TComboBox *cbG;
	TBitBtn *bValues;
	TSaveDialog *sdAccData;
	TPanel *pLeftFata;
	TPanel *pRightFata;
	TPanel *pxRightFata;
	TImage *ixRightFata;
	TPanel *pyRightFata;
	TImage *iyRightFata;
	TPanel *pzRightFata;
	TImage *izRightFata;
	TSplitter *Splitter3;
	TSplitter *Splitter4;
	TPanel *pFata;
	TSplitter *Splitter5;
	TStatusBar *StatusBar1;
	TComboBox *cbCOMLeftSpate;
	TComboBox *cbCOMRightSpate;
	TTrackBar *tbResolution;
	TCheckBox *cbShowValues;
	TLabel *lResolution;
	TSplitter *Splitter6;
	TPanel *pSpate;
	TSplitter *Splitter7;
	TPanel *pLeftSpate;
	TSplitter *Splitter8;
	TSplitter *Splitter9;
	TPanel *pxLeftSpate;
	TImage *ixLeftSpate;
	TPanel *pyLeftSpate;
	TImage *iyLeftSpate;
	TPanel *pzLeftSpate;
	TImage *izLeftSpate;
	TPanel *pRightSpate;
	TSplitter *Splitter10;
	TSplitter *Splitter11;
	TPanel *pxRightSpate;
	TImage *ixRightSpate;
	TPanel *pyRightSpate;
	TImage *iyRightSpate;
	TPanel *pzRightSpate;
	TImage *izRightSpate;
	TPanel *pToolBarFata;
	TComboBox *cbCOMLeftFata;
	TComboBox *cbCOMRightFata;
	TButton *bPrintScreen;
	void __fastcall bStartClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall pxLeftFataResize(TObject *Sender);
	void __fastcall pyLeftFataResize(TObject *Sender);
	void __fastcall pzLeftFataResize(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall cbGChange(TObject *Sender);
	void __fastcall bValuesClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall bPrintScreenClick(TObject *Sender);
private:	// User declarations
	void MakeAxis(void);
	void ClearImage(TImage *img, String a);
void process_data(char *str, DWORD, TLista &acc_list, bool& first_point_x, bool& first_point_y, bool& first_point_z, short &x_ox, short &x_oy, short &x_oz, TImage*ix, TImage*iy, TImage*iz);
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
