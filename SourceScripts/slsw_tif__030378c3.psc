;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname SLSW_TIF__030378C3 Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
Game.GetPlayer().AddItem(gold001, Main.AllGold)
if SLSW_AddictionIndicator.getValue() == 4
	Game.GetPlayer().Additem(LeafSkooma, Main.ClientCount)
elseif SLSW_AddictionIndicator.getValue() == 5
	Main.ClientCount = (Main.ClientCount * 2) as int
	Game.GetPlayer().Additem(LeafSkooma, Main.ClientCount)
endif
Main.ClientCount = 0
Main.AllGold = 0
GetOwningQuest().Reset()
GetOwningQuest().SetStage(0)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
SLSW_PlayerProstitutionUpkeep Property Main auto

MiscObject Property Gold001  Auto  

Potion Property LeafSkooma  Auto  

GlobalVariable Property SLSW_AddictionIndicator  Auto  
