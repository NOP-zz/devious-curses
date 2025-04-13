;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname PF_SLSW_PPClientLeavesMK_030378C4 Extends Package Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(Actor akActor)
;BEGIN CODE
Client.GetRef().MoveTo(Marker)
if SLSW_PlayerProstitution.getStage() != 0
	SLSW_PlayerProstitution.Reset()
	SLSW_PlayerProstitution.SetStage(10)
endif
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

Quest Property SLSW_PlayerProstitution  Auto  

ReferenceAlias Property Client  Auto  

ObjectReference Property Marker  Auto  
