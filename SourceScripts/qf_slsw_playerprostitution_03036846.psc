;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 9
Scriptname QF_SLSW_PlayerProstitution_03036846 Extends Quest Hidden

;BEGIN ALIAS PROPERTY Client
;ALIAS PROPERTY TYPE ReferenceAlias
ReferenceAlias Property Alias_Client Auto
;END ALIAS PROPERTY

;BEGIN FRAGMENT Fragment_2
Function Fragment_2()
;BEGIN CODE
; Player working
RegisterForSingleUpdate(60)
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_8
Function Fragment_8()
;BEGIN CODE
; client leaves
(Alias_Client.getRef() as actor).EvaluatePackage()
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_6
Function Fragment_6()
;BEGIN CODE
; action
(Alias_Client.getRef() as actor).EvaluatePackage()
Main.Action()
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_5
Function Fragment_5()
;BEGIN CODE
; client followes
(Alias_Client.getRef() as actor).EvaluatePackage()
Main.ClientCount +=1
Main.AllGold += (Main.Gold * Main.Cut) as int
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_4
Function Fragment_4()
;BEGIN CODE
; barter price
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_3
Function Fragment_3()
;BEGIN CODE
; client comes
(Alias_Client.getRef() as actor).EvaluatePackage()
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_0
Function Fragment_0()
;BEGIN CODE
;waiting
UnregisterForUpdate()
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
SLSW_PlayerProstitutionUpkeep Property Main auto
