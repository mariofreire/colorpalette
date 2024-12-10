object Form1: TForm1
  Left = 232
  Top = 180
  Width = 1249
  Height = 564
  Caption = 'Color Palette           by   Mario Freire'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 64
    Width = 385
    Height = 353
  end
  object Button1: TButton
    Left = 8
    Top = 424
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object DrawGrid1: TDrawGrid
    Left = 56
    Top = 16
    Width = 512
    Height = 32
    BorderStyle = bsNone
    ColCount = 32
    DefaultColWidth = 16
    DefaultRowHeight = 16
    DefaultDrawing = False
    FixedCols = 0
    RowCount = 2
    FixedRows = 0
    GridLineWidth = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine]
    ScrollBars = ssNone
    TabOrder = 1
    OnDrawCell = DrawGrid1DrawCell
    OnMouseUp = DrawGrid1MouseUp
  end
  object Panel1: TPanel
    Left = 8
    Top = 11
    Width = 41
    Height = 42
    BevelOuter = bvLowered
    BevelWidth = 2
    TabOrder = 2
    object BGShape: TShape
      Left = 16
      Top = 16
      Width = 17
      Height = 17
      Shape = stSquare
      OnMouseDown = BGShapeMouseDown
    end
    object FGShape: TShape
      Left = 8
      Top = 8
      Width = 17
      Height = 17
      Brush.Color = clBlack
      Pen.Color = clWhite
      Shape = stSquare
      OnMouseDown = FGShapeMouseDown
    end
  end
  object FGColor: TColorDialog
    Ctl3D = True
    Options = [cdFullOpen]
    Left = 400
    Top = 64
  end
  object BGColor: TColorDialog
    Ctl3D = True
    Color = clWhite
    Options = [cdFullOpen]
    Left = 432
    Top = 64
  end
end
