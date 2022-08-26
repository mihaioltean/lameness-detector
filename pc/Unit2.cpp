// ---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit2.h"
#include "serial.h"
#include "uValues.h"

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define NO_ACC_DATA 100000

double max_sensitivity[4] =
{282.0, 141.0, 71.0, 35.0}; // 35.0};
double G[4] =
{2.0, 4.0, 8.0, 16.0};

int max_g = 1;

TForm2 *Form2;

CSerial serial_left_fata, serial_right_fata, serial_left_spate, serial_right_spate;

short x_ox_left_fata, x_oy_left_fata, x_oz_left_fata, x_ox_left_spate, x_oy_left_spate, x_oz_left_spate;
short x_ox_right_fata, x_oy_right_fata, x_oz_right_fata, x_ox_right_spate, x_oy_right_spate, x_oz_right_spate;

bool first_point_x_left_fata, first_point_y_left_fata, first_point_z_left_fata, first_point_x_left_spate, first_point_y_left_spate, first_point_z_left_spate;
bool first_point_x_right_fata, first_point_y_right_fata, first_point_z_right_fata, first_point_x_right_spate, first_point_y_right_spate, first_point_z_right_spate;

TLista acc_list_left_fata, acc_list_right_fata, acc_list_left_spate, acc_list_right_spate;

int text_height = 11;
//-------------------------------------------------------
struct acc_data
{
  TTime moment;
	int x, y, z;

	acc_data()
	{
		x = y = z = NO_ACC_DATA;
	}
};

acc_data *acc;

// ---------------------------------------------------------------------------
String GetExeDirectoryWithTrails(void)
{
	wchar_t buffer[4096];
	buffer[0] = 0;
	GetModuleFileNameW(NULL, buffer, 4096);
	String path = ExtractFilePath(buffer);
	long length = path.Length();
	if (path[length] != '\\')
	{
		path += " \\ ";
	}
	else
		if (path[length - 1] == '.')
		{
			path.Delete(length - 2, 2);
		}

	return path;
}

// ---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner)
{
	x_ox_left_fata = x_oy_left_fata = x_oz_left_fata = 0;
	x_ox_right_fata = x_oy_right_fata = x_oz_right_fata = 0;
	x_ox_left_spate = x_oy_left_spate = x_oz_left_spate = 0;
	x_ox_right_spate = x_oy_right_spate = x_oz_right_spate = 0;
}

// ---------------------------------------------------------------------------
bool Open(void)
{
	LONG lLastError = ERROR_SUCCESS;

	// left fata

	lLastError = serial_left_fata.Open(String("//./" + Form2->cbCOMLeftFata->Text.Trim()).c_str(), 0, 0, false);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to open " + Form2->cbCOMLeftFata->Text);
		return false;
	}
	// Setup the serial1 port (9600,N81) using hardware handshaking
	lLastError = serial_left_fata.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set COM-port setting: " + Form2->cbCOMLeftFata->Text);
		return false;
	}
	// Setup handshaking
	lLastError = serial_left_fata.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set COM-port handshaking: " + Form2->cbCOMLeftFata->Text);
		return false;
	}
	// right fata
	lLastError = serial_right_fata.Open(String("//./" + Form2->cbCOMRightFata->Text.Trim()).c_str(), 0, 0, false);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to open " + Form2->cbCOMRightFata->Text);
		return false;
	}
	lLastError = serial_right_fata.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set port setting: " + Form2->cbCOMRightFata->Text);
		return false;
	}
	lLastError = serial_right_fata.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set COM-port handshaking " + Form2->cbCOMRightFata->Text);
		return false;
	}

	// spate left
	lLastError = serial_left_spate.Open(String("//./" + Form2->cbCOMLeftSpate->Text.Trim()).c_str(), 0, 0, false);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to open " + Form2->cbCOMLeftSpate->Text);
		return false;
	}
	lLastError = serial_left_spate.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set port setting: " + Form2->cbCOMLeftSpate->Text);
		return false;
	}
	lLastError = serial_left_spate.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set COM-port handshaking " + Form2->cbCOMLeftSpate->Text);
		return false;
	}

	// spate right
	lLastError = serial_right_spate.Open(String("//./" + Form2->cbCOMRightSpate->Text.Trim()).c_str(), 0, 0, false);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to open " + Form2->cbCOMRightSpate->Text);
		return false;
	}
	lLastError = serial_right_spate.Setup(CSerial::EBaud9600, CSerial::EData8, CSerial::EParNone, CSerial::EStop1);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set port setting: " + Form2->cbCOMRightSpate->Text);
		return false;
	}
	lLastError = serial_right_spate.SetupHandshaking(CSerial::EHandshakeHardware);
	if (lLastError != ERROR_SUCCESS)
	{
		ShowMessage("Unable to set COM-port handshaking " + Form2->cbCOMRightSpate->Text);
		return false;
	}
	return true;
}

// ----------------------------------------------------------------------------
/*
 void TForm2::ClearPanels()
 {

 }
 */
// ----------------------------------------------------------------------------
void TForm2::ClearImage(TImage *img, String a)
{
	img->Canvas->Brush->Color = clWhite;
	img->Canvas->Rectangle(0, 0, img->Width, img->Height);
	img->Canvas->Pen->Color = clRed;
	img->Canvas->MoveTo(0, img->Height / 2);
	img->Canvas->LineTo(img->Width, img->Height / 2);
	img->Canvas->Pen->Color = clBlack;
	img->Canvas->TextOutW(3, 2, a);
}
// ----------------------------------------------------------------------------
void TForm2::MakeAxis(void)
{

	x_ox_left_fata = 0;
	x_oy_left_fata = 0;
	x_oz_left_fata = 0;

	x_ox_right_fata = 0;
	x_oy_right_fata = 0;
	x_oz_right_fata = 0;

	first_point_x_right_fata = true;
	first_point_y_right_fata = true;
	first_point_z_right_fata = true;

	first_point_x_left_fata = true;
	first_point_y_left_fata = true;
	first_point_z_left_fata = true;


	x_ox_left_spate = 0;
	x_oy_left_spate = 0;
	x_oz_left_spate = 0;

	x_ox_right_spate = 0;
	x_oy_right_spate = 0;
	x_oz_right_spate = 0;

	first_point_x_right_spate = true;
	first_point_y_right_spate = true;
	first_point_z_right_spate = true;

	first_point_x_left_spate = true;
	first_point_y_left_spate = true;
	first_point_z_left_spate = true;

	ClearImage(ixLeftFata, "X");
	ClearImage(iyLeftFata, "Y");
	ClearImage(izLeftFata, "Z");

	ClearImage(ixRightFata, "X");
	ClearImage(iyRightFata, "Y");
	ClearImage(izRightFata, "Z");

	ClearImage(ixLeftSpate, "X");
	ClearImage(iyLeftSpate, "Y");
	ClearImage(izLeftSpate, "Z");

	ClearImage(ixRightSpate, "X");
	ClearImage(iyRightSpate, "Y");
	ClearImage(izRightSpate, "Z");

/*
	ixLeft->Canvas->Brush->Color = clWhite;
	ixLeft->Canvas->Rectangle(0, 0, ixLeft->Width, ixLeft->Height);
	ixLeft->Canvas->Pen->Color = clRed;
	ixLeft->Canvas->MoveTo(0, ixLeft->Height / 2);
	ixLeft->Canvas->LineTo(ixLeft->Width, ixLeft->Height / 2);
	ixLeft->Canvas->Pen->Color = clBlack;
	ixLeft->Canvas->TextOutW(3, 2, "X");

	iyLeft->Canvas->Brush->Color = clWhite;
	iyLeft->Canvas->Rectangle(0, 0, iyLeft->Width, iyLeft->Height);
	iyLeft->Canvas->Pen->Color = clRed;
	iyLeft->Canvas->MoveTo(0, iyLeft->Height / 2);
	iyLeft->Canvas->LineTo(iyLeft->Width, iyLeft->Height / 2);
	iyLeft->Canvas->Pen->Color = clBlack;
	iyLeft->Canvas->TextOutW(3, 2, "Y");

	izLeft->Canvas->Brush->Color = clWhite;
	izLeft->Canvas->Rectangle(0, 0, izLeft->Width, izLeft->Height);
	izLeft->Canvas->Pen->Color = clRed;
	izLeft->Canvas->MoveTo(0, izLeft->Height / 2);
	izLeft->Canvas->LineTo(izLeft->Width, izLeft->Height / 2);
	izLeft->Canvas->Pen->Color = clBlack;
	izLeft->Canvas->TextOutW(3, 2, "Z");

	ixRight->Canvas->Brush->Color = clWhite;
	ixRight->Canvas->Rectangle(0, 0, ixRight->Width, ixRight->Height);
	ixRight->Canvas->Pen->Color = clRed;
	ixRight->Canvas->MoveTo(0, ixRight->Height / 2);
	ixRight->Canvas->LineTo(ixRight->Width, ixRight->Height / 2);
	ixRight->Canvas->Pen->Color = clBlack;
	ixRight->Canvas->TextOutW(3, 2, "X");

	iyRight->Canvas->Brush->Color = clWhite;
	iyRight->Canvas->Rectangle(0, 0, iyRight->Width, iyRight->Height);
	iyRight->Canvas->Pen->Color = clRed;
	iyRight->Canvas->MoveTo(0, iyRight->Height / 2);
	iyRight->Canvas->LineTo(iyRight->Width, iyRight->Height / 2);
	iyRight->Canvas->Pen->Color = clBlack;
	iyRight->Canvas->TextOutW(3, 2, "Y");

	izRight->Canvas->Brush->Color = clWhite;
	izRight->Canvas->Rectangle(0, 0, izRight->Width, izRight->Height);
	izRight->Canvas->Pen->Color = clRed;
	izRight->Canvas->MoveTo(0, izRight->Height / 2);
	izRight->Canvas->LineTo(izRight->Width, izRight->Height / 2);
	izRight->Canvas->Pen->Color = clBlack;
	izRight->Canvas->TextOutW(3, 2, "Z");
*/
	text_height = ixLeftFata->Canvas->TextHeight("0") + 2;
}
// ----------------------------------------------------------------------------

void __fastcall TForm2::bStartClick(TObject *Sender)
{

	if (!serial_left_fata.IsOpen() || !serial_right_fata.IsOpen() || !serial_left_spate.IsOpen() || !serial_right_spate.IsOpen())
	{
		Screen->Cursor = crHourGlass;
		if (!Open())
		{ // 5, 57600)){
			Screen->Cursor = crDefault;
			ShowMessage("Cannot connect!");
		}
		else
		{

			DWORD dwBytesRead = 0;
			BYTE abBuffer[10000];
			serial_left_fata.Read(abBuffer, sizeof(abBuffer), &dwBytesRead);
			serial_right_fata.Read(abBuffer, sizeof(abBuffer), &dwBytesRead);
			serial_left_spate.Read(abBuffer, sizeof(abBuffer), &dwBytesRead);
			serial_right_spate.Read(abBuffer, sizeof(abBuffer), &dwBytesRead);

			bStart->Caption = "Stop";
			Timer1->Enabled = true;
			Screen->Cursor = crDefault;

			MakeAxis();

			fValues->mValues->Clear();
			DWORD dwBytesWritten = 0;
			abBuffer[0] = cbG->ItemIndex;

			serial_left_fata.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
			serial_right_fata.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
			serial_left_spate.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
			serial_right_spate.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
			acc = new acc_data();

		}
	}
	else
	{
		Timer1->Enabled = false;
		bStart->Caption = "Start";
		serial_left_fata.Close();
		serial_right_fata.Close();
		serial_left_spate.Close();
		serial_right_spate.Close();
		// now I have to save to a file
		String date_as_string = Now().FormatString("yyyy-mm-dd-hh-nn-ss");
		String filename_left_fata = GetCurrentDir() + "\\" + date_as_string + "_left_front.csv";
		String filename_right_fata = GetCurrentDir() + "\\" + date_as_string + "_right_front.csv";

		String filename_left_spate = GetCurrentDir() + "\\" + date_as_string + "_left_back.csv";
		String filename_right_spate = GetCurrentDir() + "\\" + date_as_string + "_right_back.csv";

		// fata
		FILE *f = _wfopen(filename_left_fata.c_str(), L"w");
		while (acc_list_left_fata.head)
		{
			acc_data *a = (acc_data*)acc_list_left_fata.GetCurrentInfo(acc_list_left_fata.head);
			String moment = a->moment.FormatString("h:n:s");
			fprintf(f, "%s;%d;%d;%d\n", UTF8String(moment).c_str(), a->x, a->y, a->z);
			delete a;
			acc_list_left_fata.DeleteHead();
		}

		fclose(f);

		f = _wfopen(filename_right_fata.c_str(), L"w");
		while (acc_list_right_fata.head)
		{
			acc_data *a = (acc_data*)acc_list_right_fata.GetCurrentInfo(acc_list_right_fata.head);
			String moment = a->moment.FormatString("h:n:s");
						fprintf(f, "%s;%d;%d;%d\n", UTF8String(moment).c_str(), a->x, a->y, a->z);
			delete a;
			acc_list_right_fata.DeleteHead();
		}
		fclose(f);

		// spate
		f = _wfopen(filename_left_spate.c_str(), L"w");
		while (acc_list_left_spate.head)
		{
			acc_data *a = (acc_data*)acc_list_left_spate.GetCurrentInfo(acc_list_left_spate.head);
			String moment = a->moment.FormatString("h:n:s");
						fprintf(f, "%s;%d;%d;%d\n", UTF8String(moment).c_str(), a->x, a->y, a->z);
			delete a;
			acc_list_left_spate.DeleteHead();
		}
		fclose(f);

		f = _wfopen(filename_right_spate.c_str(), L"w");
		while (acc_list_right_spate.head)
		{
			acc_data *a = (acc_data*)acc_list_right_spate.GetCurrentInfo(acc_list_right_spate.head);
			String moment = a->moment.FormatString("h:n:s");
						fprintf(f, "%s;%d;%d;%d\n", UTF8String(moment).c_str(), a->x, a->y, a->z);
			delete a;
			acc_list_right_spate.DeleteHead();
		}

		fclose(f);


	}

}

// ---------------------------------------------------------------------------
short do_unpack(char c, char r, char *axis)
{

	*axis = c & 0x6;
	*axis >>= 1;

	c >>= 3;
	r >>= 3;
	short y = c * 0x20 + r;

	return y;
}
// ---------------------------------------------------------------------------

char is_second(char c)
{
	return (c & 1);
}

// ---------------------------------------------------------------------------
void TForm2::process_data(char *str, DWORD len, TLista &acc_list, bool& first_point_x, bool& first_point_y, bool& first_point_z, short &x_ox, short &x_oy, short &x_oz, TImage*ix, TImage*iy, TImage*iz)

{
	int i = 0;
	if (len)
		if (is_second(str[0])) // cx
					i++;

	for (; i < len; i += 2)
	{
		if (i + 1 < len)
		{
			char axis = 0;
			short y = do_unpack(str[i], str[i + 1], &axis);

			switch (axis)
			{
			case 1: // 0x
				acc->x = y;
				if (first_point_x)
				{
					ix->Canvas->MoveTo(0, y / max_sensitivity[max_g] / G[max_g] * ix->Height / 2.0 + ix->Height / 2.0);
					// pxl->
					if (cbShowValues->Checked)
						ix->Canvas->TextOut(0, ix->Height - text_height, IntToStr(y));
					first_point_x = false;
				}
				else
				{
					ix->Canvas->LineTo(++x_ox, y / max_sensitivity[max_g] / G[max_g] * ix->Height / 2.0 + ix->Height / 2.0);
					if (cbShowValues->Checked)
						if (x_ox % tbResolution->Position == 0)
							ix->Canvas->TextOut(x_ox, ix->Height - text_height, IntToStr(y));
				}

				break;
			case 2: // 0y
				acc->y = y;
				if (first_point_y)
				{
					iy->Canvas->MoveTo(0, y / max_sensitivity[max_g] / G[max_g] * iy->Height / 2.0 + iy->Height / 2.0);
					if (cbShowValues->Checked)
						iy->Canvas->TextOut(0, iy->Height - text_height, IntToStr(y));
					first_point_y = false;
				}
				else
				{
					iy->Canvas->LineTo(++x_oy, y / max_sensitivity[max_g] / G[max_g] * iy->Height / 2.0 + iy->Height / 2.0);
					if (cbShowValues->Checked)
						if (x_oy % tbResolution->Position == 0)
							iy->Canvas->TextOut(x_oy, iy->Height - text_height, IntToStr(y));
				}
				break;
			case 3: // 0z
				acc->z = y;
				if (first_point_z)
				{
					iz->Canvas->MoveTo(0, y / max_sensitivity[max_g] / G[max_g] * iz->Height / 2.0 + iz->Height / 2.0);
					if (cbShowValues->Checked)
						iz->Canvas->TextOut(0, iz->Height - text_height, IntToStr(y));
					first_point_z = false;
				}
				else
				{
					iz->Canvas->LineTo(++x_oz, y / max_sensitivity[max_g] / G[max_g] * iz->Height / 2.0 + iz->Height / 2.0);
					if (cbShowValues->Checked)
						if (x_oz % tbResolution->Position == 0)
							iz->Canvas->TextOut(x_oz, iz->Height - text_height, IntToStr(y));
				}
				break;
			}

			if ((x_ox >= ix->ClientWidth) || (x_oy >= iy->ClientWidth) || (x_oz >= iz->ClientWidth))
			{
				MakeAxis();
			}

			if ((acc->x != NO_ACC_DATA) && (acc->y != NO_ACC_DATA) && (acc->z != NO_ACC_DATA))
			{
			  acc->moment = Now();
				acc_list.Add(acc);
				acc = new acc_data();
			}

		}
	}
}

// ----------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
	char str[10000];
	str[0] = '\0';
	short nr;

	DWORD len = 0;
  // fata
	serial_right_fata.Read(str, sizeof(str), &len);
	str[len] = 0;
	process_data(str, len, acc_list_right_fata, first_point_x_right_fata, first_point_y_right_fata, first_point_z_right_fata, x_ox_right_fata, x_oy_right_fata, x_oz_right_fata, ixRightFata, iyRightFata, izRightFata);

	serial_left_fata.Read(str, sizeof(str), &len);
	str[len] = 0;
	process_data(str, len, acc_list_left_fata, first_point_x_left_fata, first_point_y_left_fata, first_point_z_left_fata, x_ox_left_fata, x_oy_left_fata, x_oz_left_fata, ixLeftFata, iyLeftFata, izLeftFata);
	// spate
	serial_right_spate.Read(str, sizeof(str), &len);
	str[len] = 0;
	process_data(str, len, acc_list_right_spate, first_point_x_right_spate, first_point_y_right_spate, first_point_z_right_spate, x_ox_right_spate, x_oy_right_spate, x_oz_right_spate, ixRightSpate, iyRightSpate, izRightSpate);

	serial_left_spate.Read(str, sizeof(str), &len);
	str[len] = 0;
	process_data(str, len, acc_list_left_spate, first_point_x_left_spate, first_point_y_left_spate, first_point_z_left_spate, x_ox_left_spate, x_oy_left_spate, x_oz_left_spate, ixLeftSpate, iyLeftSpate, izLeftSpate);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Timer1->Enabled = false;
	serial_left_fata.Close();
	serial_right_fata.Close();
	serial_left_spate.Close();
	serial_right_spate.Close();

	// save settings
	String dir = GetExeDirectoryWithTrails();
	FILE *f = _wfopen((dir + "settings.txt").c_str(), L"w");

	int com_left_fata = 6;
	try
	{
		com_left_fata = cbCOMLeftFata->Text.Delete(1, 3).ToInt();
	}
	catch (...)
	{
		com_left_fata = 6;
	}

	int com_right_fata = 9;
	try
	{
		com_right_fata = cbCOMRightFata->Text.Delete(1, 3).ToInt();
	}
	catch (...)
	{
		com_right_fata = 9;
	}

	//spate
	int com_left_spate = 6;
	try
	{
		com_left_spate = cbCOMLeftSpate->Text.Delete(1, 3).ToInt();
	}
	catch (...)
	{
		com_left_spate = 6;
	}

	int com_right_spate = 9;
	try
	{
		com_right_spate = cbCOMRightSpate->Text.Delete(1, 3).ToInt();
	}
	catch (...)
	{
		com_right_spate = 9;
	}


	fprintf(f, "%d\n", com_left_fata);
	fprintf(f, "%d\n", com_right_fata);
	fprintf(f, "%d\n", com_left_spate);
	fprintf(f, "%d\n", com_right_spate);
	fprintf(f, "%d\n", cbShowValues->Checked);
	fprintf(f, "%d\n", tbResolution->Position);

	fclose(f);
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::pxLeftFataResize(TObject *Sender)
{
	MakeAxis();

}
// ---------------------------------------------------------------------------

void __fastcall TForm2::pyLeftFataResize(TObject *Sender)
{
	MakeAxis();

}
// ---------------------------------------------------------------------------

void __fastcall TForm2::pzLeftFataResize(TObject *Sender)
{
	MakeAxis();

}
// ---------------------------------------------------------------------------

void __fastcall TForm2::FormResize(TObject *Sender)
{
/*
	int h = ClientHeight - pLeftFata->Height - StatusBar1->Height - 2 * Splitter1->Height;
	pxLeftFata->Height = h/3;
	pyLeftFata->Height = h/3;
	pzLeftFata->Height = h/3;

	pxRightFata->Height = h/3;
	pyRightFata->Height = h/3;
	pzRightFata->Height = h/3;

	pxLeftSpate->Height = h/3;
	pyLeftSpate->Height = h/3;
	pzLeftSpate->Height = h/3;

	pxRightSpate->Height = h/3;
	pyRightSpate->Height = h/3;
	pzRightSpate->Height = h/3;

	pLeftFata->Width = pFata->Width/2 - Splitter5->Width;
	pLeftSpate->Width = pSpate->Width/2 - Splitter7->Width;

	MakeAxis();
	*/
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::cbGChange(TObject *Sender)
{
	max_g = cbG->ItemIndex;

	MakeAxis();

	DWORD dwBytesWritten = 0;
	char abBuffer[1];
	abBuffer[0] = cbG->ItemIndex;

	serial_left_fata.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
	serial_right_fata.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
	serial_left_spate.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);
	serial_right_spate.Write(abBuffer, 1, &dwBytesWritten, 0, INFINITE);

}
// ---------------------------------------------------------------------------

void __fastcall TForm2::bValuesClick(TObject *Sender)
{
	fValues->Show();
}

// ---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
	String dir = GetExeDirectoryWithTrails();
	FILE *f = _wfopen((dir + "settings.txt").c_str(), L"r");
	if (f)
	{

		int com_port, value;

		if (fscanf(f, "%d", &com_port))
			cbCOMLeftFata->Text = "COM" + IntToStr(com_port);

		if (fscanf(f, "%d", &com_port))
			cbCOMRightFata->Text = "COM" + IntToStr(com_port);

		if (fscanf(f, "%d", &com_port))
			cbCOMLeftSpate->Text = "COM" + IntToStr(com_port);

		if (fscanf(f, "%d", &com_port))
			cbCOMRightSpate->Text = "COM" + IntToStr(com_port);

		if (fscanf(f, "%d", &value))
			cbShowValues->Checked = value;

		if (fscanf(f, "%d", &value))
			tbResolution->Position = value;

	}

	fclose(f);
}
// ---------------------------------------------------------------------------
void __fastcall TForm2::bPrintScreenClick(TObject *Sender)
{
	Graphics::TBitmap * img = new Graphics::TBitmap();
//	img->Parent = Form2;

//	img->Visible = false;
	img->Height = ixLeftFata->Height * 6;
	img->Width = ixLeftFata->Width * 2;

//	img->Canvas->CopyMode =
// left fata
	img->Canvas->CopyRect( Rect(0, 0, ixLeftFata->Width, ixLeftFata->Height), ixLeftFata->Canvas, Rect(0, 0, ixLeftFata->Width, ixLeftFata->Height));
	img->Canvas->CopyRect(Rect(0, ixLeftFata->Height, ixLeftFata->Width, 2 * ixLeftFata->Height), iyLeftFata->Canvas, Rect(0, 0, iyLeftFata->Width, iyLeftFata->Height));
	img->Canvas->CopyRect(Rect(0, 2 * ixLeftFata->Height, ixLeftFata->Width, 3 * ixLeftFata->Height), izLeftFata->Canvas, Rect(0, 0, izLeftFata->Width, izLeftFata->Height));

	// left spate
	img->Canvas->CopyRect(Rect(0, 3 * ixLeftFata->Height, ixLeftSpate->Width, 4 * ixLeftSpate->Height), ixLeftSpate->Canvas, Rect(0, 0, ixLeftSpate->Width, ixLeftSpate->Height));
	img->Canvas->CopyRect(Rect(0, 4 * ixLeftSpate->Height, ixLeftSpate->Width, 5 * ixLeftSpate->Height), iyLeftSpate->Canvas, Rect(0, 0, iyLeftSpate->Width, iyLeftSpate->Height));
	img->Canvas->CopyRect(Rect(0, 5 * ixLeftSpate->Height, ixLeftSpate->Width, 6 * ixLeftSpate->Height), izLeftSpate->Canvas, Rect(0, 0, izLeftSpate->Width, izLeftSpate->Height));

// right fata
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, 0, 2 * ixLeftFata->Width, ixLeftFata->Height), ixRightFata->Canvas, Rect(0, 0, ixRightFata->Width, ixRightFata->Height));
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, ixLeftFata->Height, 2 * ixLeftFata->Width, 2 * ixRightFata->Height), iyRightFata->Canvas, Rect(0, 0, iyRightFata->Width, iyRightFata->Height));
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, 2 * ixLeftFata->Height, 2 * ixLeftFata->Width, 3 * ixRightFata->Height), izRightFata->Canvas, Rect(0, 0, izRightFata->Width, izRightFata->Height));

	// right spate
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, 3 * ixLeftFata->Height, 2 * ixLeftSpate->Width, 4 * ixLeftSpate->Height), ixRightSpate->Canvas, Rect(0, 0, ixRightSpate->Width, ixRightSpate->Height));
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, 4 * ixLeftSpate->Height, 2 * ixLeftSpate->Width, 5 * ixLeftSpate->Height), iyRightSpate->Canvas, Rect(0, 0, iyRightSpate->Width, iyRightSpate->Height));
	img->Canvas->CopyRect(Rect(ixLeftFata->Width, 5 * ixLeftSpate->Height, 2 * ixLeftSpate->Width, 6 * ixLeftSpate->Height), izRightSpate->Canvas, Rect(0, 0, izRightSpate->Width, izRightSpate->Height));

	String date_as_string = Now().FormatString("yyyy-mm-dd-hh-nn-ss");
	String filename_screen = GetCurrentDir() + "\\" + date_as_string + "_screen.bmp";

	img->SaveToFile(filename_screen);
}
//---------------------------------------------------------------------------

