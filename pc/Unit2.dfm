object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Accelerometer - 3.3'
  ClientHeight = 685
  ClientWidth = 1212
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter6: TSplitter
    Left = 0
    Top = 314
    Width = 1212
    Height = 5
    Cursor = crVSplit
    Align = alTop
    ExplicitTop = 0
    ExplicitWidth = 774
  end
  object pToolBar: TPanel
    Left = 0
    Top = 608
    Width = 1212
    Height = 58
    Align = alBottom
    TabOrder = 0
    DesignSize = (
      1212
      58)
    object lResolution: TLabel
      Left = 632
      Top = 7
      Width = 50
      Height = 13
      Caption = 'Resolution'
    end
    object bStart: TBitBtn
      Left = 176
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Start'
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 0
      OnClick = bStartClick
    end
    object bRecord: TBitBtn
      Left = 272
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Record'
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 1
      Visible = False
    end
    object bLoad: TBitBtn
      Left = 272
      Top = 27
      Width = 75
      Height = 25
      Caption = 'Load'
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 2
      Visible = False
    end
    object cbG: TComboBox
      Left = 369
      Top = 14
      Width = 73
      Height = 21
      Style = csDropDownList
      ItemIndex = 0
      TabOrder = 3
      Text = '2G'
      Visible = False
      OnChange = cbGChange
      Items.Strings = (
        '2G'
        '4G'
        '8G'
        '16G')
    end
    object bValues: TBitBtn
      Left = 895
      Top = 10
      Width = 75
      Height = 25
      Caption = 'Values'
      DoubleBuffered = True
      ParentDoubleBuffered = False
      TabOrder = 4
      Visible = False
      OnClick = bValuesClick
    end
    object cbCOMLeftSpate: TComboBox
      Left = 16
      Top = 1
      Width = 81
      Height = 21
      TabOrder = 5
      Text = 'COM6'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14'
        'COM15'
        'COM16'
        'COM17'
        'COM18'
        'COM19'
        'COM20'
        'COM21')
    end
    object cbCOMRightSpate: TComboBox
      Left = 1136
      Top = 9
      Width = 73
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemIndex = 8
      TabOrder = 6
      Text = 'COM9'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14'
        'COM15'
        'COM16'
        'COM17'
        'COM18'
        'COM19'
        'COM20'
        'COM21')
    end
    object tbResolution: TTrackBar
      Left = 622
      Top = 22
      Width = 161
      Height = 30
      Max = 100
      Min = 10
      Frequency = 10
      Position = 40
      TabOrder = 7
    end
    object cbShowValues: TCheckBox
      Left = 448
      Top = 4
      Width = 97
      Height = 17
      Caption = 'Show Values'
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object bPrintScreen: TButton
      Left = 1000
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Print Screen'
      TabOrder = 9
      OnClick = bPrintScreenClick
    end
  end
  object pFata: TPanel
    Left = 0
    Top = 33
    Width = 1212
    Height = 281
    Align = alTop
    Caption = 'pFata'
    TabOrder = 1
    object Splitter5: TSplitter
      Left = 570
      Top = 1
      Height = 279
      ExplicitLeft = 624
      ExplicitTop = 120
      ExplicitHeight = 100
    end
    object pLeftFata: TPanel
      Left = 1
      Top = 1
      Width = 569
      Height = 279
      Align = alLeft
      TabOrder = 0
      object Splitter1: TSplitter
        Left = 1
        Top = 89
        Width = 567
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitLeft = 2
        ExplicitTop = 146
      end
      object Splitter2: TSplitter
        Left = 1
        Top = 180
        Width = 567
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 213
      end
      object pxLeftFata: TPanel
        Left = 1
        Top = 1
        Width = 567
        Height = 88
        Align = alTop
        Caption = 'x'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnResize = pxLeftFataResize
        object ixLeftFata: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 86
          Align = alClient
          ExplicitTop = 0
          ExplicitHeight = 178
        end
      end
      object pyLeftFata: TPanel
        Left = 1
        Top = 92
        Width = 567
        Height = 88
        Align = alTop
        Caption = 'y'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 1
        OnResize = pyLeftFataResize
        object iyLeftFata: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 86
          Align = alClient
          ExplicitLeft = 66
          ExplicitTop = 64
          ExplicitHeight = 116
        end
      end
      object pzLeftFata: TPanel
        Left = 1
        Top = 183
        Width = 567
        Height = 91
        Align = alTop
        Caption = 'z'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 2
        OnResize = pzLeftFataResize
        object izLeftFata: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 89
          Align = alClient
          ExplicitTop = 2
          ExplicitHeight = 135
        end
      end
    end
    object pRightFata: TPanel
      Left = 573
      Top = 1
      Width = 638
      Height = 279
      Align = alLeft
      TabOrder = 1
      object Splitter3: TSplitter
        Left = 1
        Top = 89
        Width = 636
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 138
        ExplicitWidth = 71
      end
      object Splitter4: TSplitter
        Left = 1
        Top = 180
        Width = 636
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 141
        ExplicitWidth = 68
      end
      object pxRightFata: TPanel
        Left = 1
        Top = 1
        Width = 636
        Height = 88
        Align = alTop
        Caption = 'x'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnResize = pxLeftFataResize
        object ixRightFata: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 86
          Align = alClient
          ExplicitTop = 0
          ExplicitHeight = 178
        end
      end
      object pyRightFata: TPanel
        Left = 1
        Top = 92
        Width = 636
        Height = 88
        Align = alTop
        Caption = 'y'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 1
        OnResize = pyLeftFataResize
        object iyRightFata: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 86
          Align = alClient
          ExplicitTop = 0
          ExplicitHeight = 80
        end
      end
      object pzRightFata: TPanel
        Left = 1
        Top = 183
        Width = 636
        Height = 93
        Align = alTop
        Caption = 'z'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 2
        OnResize = pzLeftFataResize
        object izRightFata: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 91
          Align = alClient
          ExplicitLeft = 2
          ExplicitTop = 2
        end
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 666
    Width = 1212
    Height = 19
    Panels = <>
  end
  object pSpate: TPanel
    Left = 0
    Top = 319
    Width = 1212
    Height = 281
    Align = alTop
    Caption = 'pSpate'
    TabOrder = 3
    object Splitter7: TSplitter
      Left = 570
      Top = 1
      Height = 279
      ExplicitLeft = 624
      ExplicitTop = 120
      ExplicitHeight = 100
    end
    object pLeftSpate: TPanel
      Left = 1
      Top = 1
      Width = 569
      Height = 279
      Align = alLeft
      TabOrder = 0
      object Splitter8: TSplitter
        Left = 1
        Top = 89
        Width = 567
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitLeft = 2
        ExplicitTop = 146
      end
      object Splitter9: TSplitter
        Left = 1
        Top = 180
        Width = 567
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 213
      end
      object pxLeftSpate: TPanel
        Left = 1
        Top = 1
        Width = 567
        Height = 88
        Align = alTop
        Caption = 'x'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnResize = pxLeftFataResize
        object ixLeftSpate: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 86
          Align = alClient
          ExplicitTop = 0
        end
      end
      object pyLeftSpate: TPanel
        Left = 1
        Top = 92
        Width = 567
        Height = 88
        Align = alTop
        Caption = 'y'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 1
        OnResize = pyLeftFataResize
        object iyLeftSpate: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 86
          Align = alClient
          ExplicitLeft = 66
          ExplicitTop = 64
          ExplicitHeight = 116
        end
      end
      object pzLeftSpate: TPanel
        Left = 1
        Top = 183
        Width = 567
        Height = 91
        Align = alTop
        Caption = 'z'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 2
        OnResize = pzLeftFataResize
        object izLeftSpate: TImage
          Left = 1
          Top = 1
          Width = 565
          Height = 89
          Align = alClient
          ExplicitTop = 2
          ExplicitHeight = 135
        end
      end
    end
    object pRightSpate: TPanel
      Left = 573
      Top = 1
      Width = 638
      Height = 279
      Align = alLeft
      TabOrder = 1
      object Splitter10: TSplitter
        Left = 1
        Top = 89
        Width = 636
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 138
        ExplicitWidth = 71
      end
      object Splitter11: TSplitter
        Left = 1
        Top = 180
        Width = 636
        Height = 3
        Cursor = crVSplit
        Align = alTop
        ExplicitTop = 141
        ExplicitWidth = 68
      end
      object pxRightSpate: TPanel
        Left = 1
        Top = 1
        Width = 636
        Height = 88
        Align = alTop
        Caption = 'x'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 0
        OnResize = pxLeftFataResize
        object ixRightSpate: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 86
          Align = alClient
          ExplicitTop = 0
          ExplicitHeight = 178
        end
      end
      object pyRightSpate: TPanel
        Left = 1
        Top = 92
        Width = 636
        Height = 88
        Align = alTop
        Caption = 'y'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 1
        OnResize = pyLeftFataResize
        object iyRightSpate: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 86
          Align = alClient
          ExplicitLeft = 2
          ExplicitTop = 0
          ExplicitHeight = 264
        end
      end
      object pzRightSpate: TPanel
        Left = 1
        Top = 183
        Width = 636
        Height = 93
        Align = alTop
        Caption = 'z'
        DoubleBuffered = True
        ParentDoubleBuffered = False
        TabOrder = 2
        OnResize = pzLeftFataResize
        object izRightSpate: TImage
          Left = 1
          Top = 1
          Width = 634
          Height = 91
          Align = alClient
          ExplicitLeft = 66
          ExplicitTop = 66
          ExplicitWidth = 555
          ExplicitHeight = 179
        end
      end
    end
  end
  object pToolBarFata: TPanel
    Left = 0
    Top = 0
    Width = 1212
    Height = 33
    Align = alTop
    TabOrder = 4
    DesignSize = (
      1212
      33)
    object cbCOMLeftFata: TComboBox
      Left = 16
      Top = 6
      Width = 81
      Height = 21
      TabOrder = 0
      Text = 'COM6'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14'
        'COM15'
        'COM16'
        'COM17'
        'COM18'
        'COM19'
        'COM20'
        'COM21')
    end
    object cbCOMRightFata: TComboBox
      Left = 1128
      Top = 8
      Width = 73
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ItemIndex = 8
      TabOrder = 1
      Text = 'COM9'
      Items.Strings = (
        'COM1'
        'COM2'
        'COM3'
        'COM4'
        'COM5'
        'COM6'
        'COM7'
        'COM8'
        'COM9'
        'COM10'
        'COM11'
        'COM12'
        'COM13'
        'COM14'
        'COM15'
        'COM16'
        'COM17'
        'COM18'
        'COM19'
        'COM20'
        'COM21')
    end
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 100
    OnTimer = Timer1Timer
    Left = 712
    Top = 440
  end
  object sdAccData: TSaveDialog
    DefaultExt = 'csv'
    Filter = 'CSV|*.csv'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 824
    Top = 112
  end
end
