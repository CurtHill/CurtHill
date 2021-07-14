object ProjectionForm: TProjectionForm
  Left = 0
  Top = 0
  Caption = 'Dual Screen Projection'
  ClientHeight = 631
  ClientWidth = 966
  Color = clBtnFace
  DefaultMonitor = dmPrimary
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClick = KillMe
  OnResize = Sizing
  PixelsPerInch = 96
  TextHeight = 13
  object MediaPlayer1: TMediaPlayer
    Left = 6
    Top = 0
    Width = 253
    Height = 50
    Margins.Left = 1
    Margins.Top = 1
    Margins.Right = 1024
    Margins.Bottom = 768
    DoubleBuffered = True
    Display = MediaPlayer1
    Shareable = True
    Visible = False
    ParentDoubleBuffered = False
    TabOrder = 0
    OnClick = Clicker
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 966
    Height = 631
    Align = alClient
    Alignment = taCenter
    Color = clGrayText
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -64
    Font.Name = 'Tahoma'
    Font.Style = []
    Lines.Strings = (
      '?')
    ParentFont = False
    TabOrder = 1
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = TimerFired
    Left = 624
    Top = 88
  end
end
