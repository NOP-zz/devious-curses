;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 12
Scriptname QF_SLSW_DenWhores_03033CC5 Extends Quest Hidden

;BEGIN ALIAS PROPERTY Client
;ALIAS PROPERTY TYPE ReferenceAlias
ReferenceAlias Property Alias_Client Auto
;END ALIAS PROPERTY

;BEGIN FRAGMENT Fragment_8
Function Fragment_8()
;BEGIN CODE
;cleanUp
UnregisterForUpdate()
Alias_Client.Clear()
Reset()
SetStage(0)
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_4
Function Fragment_4()
;BEGIN CODE
;action
Upkeep.Action()
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_6
Function Fragment_6()
;BEGIN CODE
;client leaves
(Alias_Client.getRef() as Actor).EvaluatePackage()
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_10
Function Fragment_10()
;BEGIN CODE
;player is client
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_0
Function Fragment_0()
;BEGIN CODE
;waiting
RegisterForSingleUpdate(300)
;END CODE
EndFunction
;END FRAGMENT

;BEGIN FRAGMENT Fragment_2
Function Fragment_2()
;BEGIN CODE
;Client comes
(Alias_Client.getRef() as Actor).EvaluatePackage()
RegisterForUpdate(10)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
SLSW_DenWhoresUpkeep Property Upkeep auto
