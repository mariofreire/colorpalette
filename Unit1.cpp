//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SkinCtrls"
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;
using namespace std;
BYTE palette[256][3];
BYTE gradientstartindex=0,gradientendindex=0;
BOOL gradientfill=FALSE;
char filename[1024];
#define calcoffset(_x, _y, _h) ((_h * _y) + _x)
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  strcpy(filename,"Def_RGB.act");
  OpenDialog1->FileName = filename;
  FILE *fp = fopen(filename,"rb");
  if (!fp) return;
  fread(&palette[0][0],768,1,fp);
  fclose(fp);
    /*
  for (int i=0;i<256;i++)
  {
    palette[i][0] = rand()%255;
    palette[i][1] = rand()%255;
    palette[i][2] = rand()%255;
  }            */
}
//---------------------------------------------------------------------------
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
TRect R = Rect;
int borderspace = 2;
R.Left+=borderspace;
R.Right-=borderspace;
R.Top+=borderspace;
R.Bottom-=borderspace;
RECT r=R;
r.left=R.Left-borderspace;
r.top=R.Top-borderspace;
r.right=R.Right+borderspace;
r.bottom=R.Bottom+borderspace;
DrawEdge(DrawGrid1->Canvas->Handle,&r,BDR_SUNKENOUTER,BF_RECT);
R.Left--;
R.Top--;
R.Right++;
R.Bottom++;
BYTE c_r=0,c_g=0,c_b=0;
c_r=palette[calcoffset(ACol,ARow,16)][0];
c_g=palette[calcoffset(ACol,ARow,16)][1];
c_b=palette[calcoffset(ACol,ARow,16)][2];
DrawGrid1->Canvas->Brush->Color = TColor(RGB(c_r,c_g,c_b));
DrawGrid1->Canvas->FillRect(R);
//if (DrawGrid1->Focused())
/*{
if (State.Contains(gdSelected))
{
DrawGrid1->Canvas->Pen->Color = TColor(RGB(0,0,0));
DrawGrid1->Canvas->DrawFocusRect(R);
}
}  */
/*
if (SpeedButton4->Down)
{
if (State.Contains(gdSelected))
{
DrawGrid1->Canvas->Pen->Color = TColor(RGB(0,0,0));
DrawGrid1->Canvas->DrawFocusRect(R);  
}
}
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
RECT r;
r.left=10;
r.top=10;
r.right=200;
r.bottom=200;
//DrawEdge(Canvas->Handle,&r, BDR_SUNKENOUTER ,  BF_RECT); //BDR_SUNKENINNER,BF_SOFT|BF_RECT);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
//Image1->Canvas->StretchDraw(Rect(0,0,ClientWidth*3,ClientHeight*3),GetFormImage());
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DrawGrid1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
BYTE c_r=0,c_g=0,c_b=0;
int ACol=0,ARow=0;
DrawGrid1->MouseToCell(X,Y,ACol,ARow);
if (SpeedButton4->Down)
{

}
else
{
//ACol = DrawGrid1->Col;
//ARow = DrawGrid1->Row;
c_r=palette[calcoffset(ACol,ARow,16)][0];
c_g=palette[calcoffset(ACol,ARow,16)][1];
c_b=palette[calcoffset(ACol,ARow,16)][2];
COLORREF color = RGB(c_r,c_g,c_b);
if (Button == mbLeft)
{
  FGShape->Brush->Color = TColor(color);
} else
if (Button == mbMiddle)
{

} else
if (Button == mbRight)
{
  BGShape->Brush->Color = TColor(color);
}

if (FGShape->Brush->Color == TColor(clBlack))
 FGShape->Pen->Color = TColor(clWhite);
else
 FGShape->Pen->Color = TColor(clBlack);

if (BGShape->Brush->Color == TColor(clBlack))
 BGShape->Pen->Color = TColor(clWhite);
else
 BGShape->Pen->Color = TColor(clBlack);
}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::DrawGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
if (SpeedButton3->Down)
{
BYTE c_r=0,c_g=0,c_b=0;
c_r=palette[calcoffset(ACol,ARow,16)][0];
c_g=palette[calcoffset(ACol,ARow,16)][1];
c_b=palette[calcoffset(ACol,ARow,16)][2];
COLORREF color = RGB(c_r,c_g,c_b);
ColorDialog1->Color = TColor(color);
if (ColorDialog1->Execute())
{
palette[calcoffset(ACol,ARow,16)][0] = GetRValue(ColorDialog1->Color);
palette[calcoffset(ACol,ARow,16)][1] = GetGValue(ColorDialog1->Color);
palette[calcoffset(ACol,ARow,16)][2] = GetBValue(ColorDialog1->Color);
}
}
else
if (SpeedButton4->Down)
{
if (!gradientfill) gradientstartindex = calcoffset(ACol,ARow,16);
else gradientendindex = calcoffset(ACol,ARow,16);
if (gradientfill)
{
BYTE c1_r=0,c1_g=0,c1_b=0;
BYTE c2_r=0,c2_g=0,c2_b=0;
c1_r=palette[gradientstartindex][0];
c1_g=palette[gradientstartindex][1];
c1_b=palette[gradientstartindex][2];
c2_r=palette[gradientendindex][0];
c2_g=palette[gradientendindex][1];
c2_b=palette[gradientendindex][2];
int j = 255;
float n;
BYTE c_r=0,c_g=0,c_b=0;
int k=0;
for( int i = 0; i < j; i++ )
{
n = ((float)i / (float) (j-1));
c_r = (float)c1_r * (1.0f-n) + (float)c2_r * n;
c_g = (float)c1_g * (1.0f-n) + (float)c2_g * n;
c_b = (float)c1_b * (1.0f-n) + (float)c2_b * n;
COLORREF c = RGB(c_r,c_g,c_b);
k=map(i,0,j,0,gradientendindex-gradientstartindex);
palette[gradientstartindex+k][0] = GetRValue(c);
palette[gradientstartindex+k][1] = GetGValue(c);
palette[gradientstartindex+k][2] = GetBValue(c);
}
DrawGrid1->Repaint();
SpeedButton4->Down = false;
}
gradientfill = !gradientfill;
}
}
//---------------------------------------------------------------------------





void __fastcall TForm1::BGShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
BGColor->Color = BGShape->Brush->Color;
if (BGColor->Execute())
{
BGShape->Brush->Color = BGColor->Color;

if (BGShape->Brush->Color == TColor(clBlack))
 BGShape->Pen->Color = TColor(clWhite);
else
 BGShape->Pen->Color = TColor(clBlack);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FGShapeMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
FGColor->Color = FGShape->Brush->Color;
if (FGColor->Execute())
{
FGShape->Brush->Color = FGColor->Color;

if (FGShape->Brush->Color == TColor(clBlack))
 FGShape->Pen->Color = TColor(clWhite);
else
 FGShape->Pen->Color = TColor(clBlack);
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{                                    
SaveDialog1->FileName = OpenDialog1->FileName;
if (SaveDialog1->Execute())
{
  OpenDialog1->FileName = SaveDialog1->FileName;
  strcpy(filename,OpenDialog1->FileName.c_str());
  FILE *fp = fopen(filename,"wb");
  if (!fp) return;
  fwrite(&palette[0][0],768,1,fp);
  fclose(fp); 
  DrawGrid1->Repaint();
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
OpenDialog1->FileName = filename;
if (OpenDialog1->Execute())
{
  SaveDialog1->FileName = OpenDialog1->FileName;
  strcpy(filename,OpenDialog1->FileName.c_str());
  FILE *fp = fopen(filename,"rb");
  if (!fp) return;
  fread(&palette[0][0],768,1,fp);
  fclose(fp);
  DrawGrid1->Repaint();
}
}
//---------------------------------------------------------------------------

