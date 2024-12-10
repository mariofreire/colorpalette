//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "SkinCtrls.hpp"
#include "CGRID.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TDrawGrid *DrawGrid1;
  TPanel *Panel1;
  TShape *BGShape;
  TShape *FGShape;
  TSpeedButton *SpeedButton3;
  TColorDialog *ColorDialog1;
  TOpenDialog *OpenDialog1;
  TSaveDialog *SaveDialog1;
  TColorDialog *FGColor;
  TColorDialog *BGColor;
  TSpeedButton *SpeedButton1;
  TSpeedButton *SpeedButton2;
  TSpeedButton *SpeedButton4;
  void __fastcall DrawGrid1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall FormPaint(TObject *Sender);
  void __fastcall Button1Click(TObject *Sender);
  void __fastcall DrawGrid1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall DrawGrid1SelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
  void __fastcall BGShapeMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall FGShapeMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
  void __fastcall SpeedButton2Click(TObject *Sender);
  void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
