//---------------------------------------------------------------------------

#ifndef uValuesH
#define uValuesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfValues : public TForm
{
__published:	// IDE-managed Components
	TMemo *mValues;
private:	// User declarations
public:		// User declarations
	__fastcall TfValues(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfValues *fValues;
//---------------------------------------------------------------------------
#endif
