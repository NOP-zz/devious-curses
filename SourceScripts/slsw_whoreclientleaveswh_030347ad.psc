;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname SLSW_WhoreClientLeavesWH_030347AD Extends Package Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(Actor akActor)
;BEGIN CODE
Client.GetRef().MoveTo(Marker)
SLSW_DenWhores.setStage(40)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
ReferenceAlias Property Client  Auto  

ObjectReference Property Marker  Auto  

Quest Property SLSW_DenWhores  Auto 
