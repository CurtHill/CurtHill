object Form1: TForm1
  Left = 100
  Top = 200
  Caption = 'Planetarium Projection'
  ClientHeight = 310
  ClientWidth = 707
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesigned
  OnResize = Sizing
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TRichEdit
    Left = 8
    Top = 0
    Width = 697
    Height = 313
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Zoom = 100
  end
  object MainMenu1: TMainMenu
    Left = 640
    Top = 32
    object File1: TMenuItem
      Caption = '&File'
      object Refresh1: TMenuItem
        Caption = '&Refresh'
        OnClick = Refresh
      end
      object Clear1: TMenuItem
        Caption = '&Clear'
        OnClick = Clarity
      end
      object Save1: TMenuItem
        Caption = '&Save'
        OnClick = SaveMemo
      end
      object Exit1: TMenuItem
        Caption = '&Exit'
        OnClick = AllDone
      end
    end
    object Display1: TMenuItem
      Caption = '&Load videos'
      object One1: TMenuItem
        Caption = '&One'
        OnClick = DoOneDisplay
      end
      object wo1: TMenuItem
        Caption = '&Two'
        OnClick = DoTwoDisplay
      end
      object hree1: TMenuItem
        Caption = 'Three'
        OnClick = ReallyThree
      end
      object Four1: TMenuItem
        Caption = '&Four'
        OnClick = DoFourDisplays
      end
      object fIve1: TMenuItem
        Caption = 'f&Ive'
        OnClick = FiveDisplays
      end
      object Six1: TMenuItem
        Caption = '&Six'
      end
    end
    object Play1: TMenuItem
      Caption = '&Play'
      OnClick = StartMovies
    end
    object Diagnose1: TMenuItem
      Caption = '&Actions'
      object Diagnose2: TMenuItem
        Caption = '&Diagnose'
        OnClick = Diagnoser
      end
      object Shiftconsole2: TMenuItem
        Caption = '&Shift console'
        OnClick = Shifter
      end
      object Reverseshiftconsole1: TMenuItem
        Caption = '&Reverse shift console'
        OnClick = DeShifter
      end
    end
    object Help1: TMenuItem
      Caption = '&Help'
      object Userguide1: TMenuItem
        Caption = '&User guide'
        OnClick = Instructions
      end
      object Warranty1: TMenuItem
        Caption = '&Warranty'
        OnClick = WarrantyClick
      end
      object Contribute1: TMenuItem
        Caption = '&Contribute'
        OnClick = Contrib
      end
      object About1: TMenuItem
        Caption = '&About'
        OnClick = AboutMe
      end
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 464
  end
  object OpenDialog1: TOpenDialog
    Filter = 
      'MPG Videos|*.MP*|Windows Media Files|*.wmv|Video files| *.mp*;*.' +
      'wmv|All Files|*.*'
    FilterIndex = 2
    Left = 520
  end
end
