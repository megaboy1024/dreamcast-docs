VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SmallBusiness2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit
' >> L'affichage complet du module donne de meilleurs r�sultats. <<
'
' Stockage pour le num�ro ID de d�bogage.
Private mlngDebugID As Long
Implements IDebug

' L'objet Collection de type Private est un
'   peu plus fiable qu'un objet Collection
'   de type Public mais il pr�sente quelques
'   probl�mes.
Private colEmployees As New Collection

' Probl�me 1: La collection est priv�e,
'   la m�thode Add doit donc faire partie
'   de la classe SmallBusiness2. �tant donn�
'   qu'il peut y avoir diff�rents types
'   d'objets dans une proc�dure, il peut
'   exister autant de m�thodes, telles que
'   AddProduct.
'
Public Function AddEmployee(ByVal Name As String, ByVal Salary As Double) As Employee
    Dim empNew As New Employee
    Static intEmpNum As Integer
    ' Utiliser l'instruction With raccourcit les r�f�rences � la propri�t� (.ID au lieu de empNew.ID)
    ' et acc�l�re l'ex�cution.
    With empNew
        ' G�n�re un ID unique pour le nouvel employ�.
        intEmpNum = intEmpNum + 1
        .ID = "E" & Format$(intEmpNum, "00000")
        .Name = Name
        .Salary = Salary
        ' Ajoute la r�f�rence de l'objet Employee
        ' � la collection, en utilisant sa propri�t�
        ' ID comme cl�.
        colEmployees.Add empNew, .ID
    End With
    ' La m�thode AddEmployee doit renvoyer une r�f�rence
    '   au nouvel objet.
    Set AddEmployee = empNew
End Function

' Probl�me 1, la suite: Il existe �galement
'   des fonctions Count pour les autres
'   objets Business, des m�thodes
'   Delete, etc. Rien qu'avec les objets
'   Employee, la classe SmallBusiness2
'   est d�j� assez complexe.
'
Public Function EmployeeCount() As Long
    EmployeeCount = colEmployees.Count
End Function

Public Sub DeleteEmployee(ByVal Index As Variant)
    colEmployees.Remove Index
End Sub

' Probl�me 2: La m�thode Employees
'   ne peut �tre utilis�e avec l'instruction
'   For Each. Vous pouvez r�soudre ce probl�me
'   en renvoyant une r�f�rence � la collection
'   priv�e, mais il ne s'agit plus dans ce cas
'   de collection priv�e; et on en revient �
'   la maison en paille.
'
Public Function Employees(ByVal Index As Variant) As Employee
    Set Employees = colEmployees.Item(Index)
End Function

' Probl�me 3: Il est toujours possible
'   pour les erreurs de code
'   d'ajouter des objets non valides �
'   la collection, en l'occurrence dans
'   l'objet SmallBusiness qui est tr�s complexe.
Public Sub Trouble()
    Dim X As New Employee
    ' �tant donn� que l'objet Collection
    '   accepte une r�f�rence � tous les objets,
    '   il est toujours possible, pour une
    '   erreur de codage interne, d'ajouter
    '   un objet Employee non initialis�.
    colEmployees.Add X
End Sub

Private Sub Class_Initialize()
    mlngDebugID = DebugInit(Me)
End Sub

Private Sub Class_Terminate()
    DebugTerm Me
End Sub

' -------- Impl�mentation de IDebug --------
'
' IDebug.DebugID permet de distinguer
' ====== -------    les diff�rents objets. Il
'   est requis par les proc�dures de d�bogage
'   DebugInit, DebugTerm et DebugShow
'   d�clar�es dans le module modFriend.
'
Private Property Get IDebug_DebugID() As Long
    IDebug_DebugID = mlngDebugID
End Property


