VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "VisDataClass"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Attribute VB_Description = "Outils du Gestionnaire de donn�es"
'>>>>>>>>>>>>>>>>>>>>>>>>
'>>>>>>>>>>>>>>>>>>>>>>>>

Public VBInstance As VBIDE.VBE

Implements IDTExtensibility

'---------------------------------------------------
' Cette m�thode peut �tre appel�e depuis un outil
' externe de lancement ou depuis l'interface VB.
'---------------------------------------------------
Private Sub IDTExtensibility_OnConnection(ByVal VBInst As Object, ByVal ConnectMode As vbext_ConnectMode, ByVal AddInInst As VBIDE.AddIn, custom() As Variant)
  On Error GoTo LVDErr
    
  Dim rc As Long
  Set gVDClass = Me
  ' Ceci d�finit le descripteur de l'instance VB
  ' utilis� par la feuille DataFormDesigner.
  Set VBInstance = VBInst
  frmMDI.mnuUDataFormDesigner.Visible = True
  frmMDI.WindowState = vbNormal
  frmMDI.SetFocus
  
  Exit Sub
    
LVDErr:
  MsgBox Err.Description
End Sub

Private Sub IDTExtensibility_OnDisconnection(ByVal RemoveMode As vbext_DisconnectMode, custom() As Variant)
  On Error Resume Next
  Unload frmMDI
End Sub

Private Sub IDTExtensibility_OnStartupComplete(custom() As Variant)
'
End Sub

Private Sub IDTExtensibility_OnAddInsUpdate(custom() As Variant)
'
End Sub

'---------------------------------------------------
' Cette m�thode peut �tre appel�e � partir d'une
' application VB au moyen d'Automation lorsque:
'Dim x As Object
'Set x = CreateObject("VisData.VisDataClass")
'x.VDOpenDatabase "c:\vb\biblio.mdb", "", False
'---------------------------------------------------
Sub VDOpenDatabase(sDatabaseName As String, sConnect As String, bReadOnly As Integer)
  On Error GoTo RVDErr
    
  frmMDI.mnuUDataFormDesigner.Visible = False
  
  gnReadOnly = bReadOnly
  If Len(sConnect) = 0 Then
    ' Doit �tre un fichier MDB de Microsoft Access.
    gsDataType = gsMSACCESS
    gsDBName = sDatabaseName
    OpenLocalDB True
  ElseIf UCase(Left(sConnect, 5)) = gsSQLDB Then
    ' Doit �tre une base de donn�es ODBC.
    gsDataType = gsSQLDB
    ' D�finit les autres variables pour la base ODBC.
    GetODBCConnectParts sConnect
    gsDBName = sDatabaseName
    SendKeys "%FOO{Enter}"
  Else
    ' Doit �tre une base de donn�es ISAM locale.
    gsDataType = sConnect
    gsDBName = sDatabaseName
    OpenLocalDB True
  End If
  
  Exit Sub
    
RVDErr:
  MsgBox Err.Description
End Sub

'---------------------------------------------------
' Cette m�thode ferme simplement le Gestionnaire de donn�es � partir du client.
'---------------------------------------------------
Sub VDClose()
  Unload frmMDI
End Sub

