;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname SLSW_TIF__03035D7E Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
GetOwningQuest().SetStage(35)
Game.GetPlayer().RemoveItem(Gold001, (SLSW_WhoreGold.getValue() as Int))

actor[] sexActors = new actor[2]
	sexActors[0] = akSpeaker
	sexActors[1] = Game.GetPlayer()

sslBaseAnimation[] anims
if Main.WhoreAction == 1
	anims = SexLab.GetAnimationsByTags(2, "Vaginal", TagSuppress = "Aggressive", RequireAll = false)
elseif Main.WhoreAction == 2
	anims = SexLab.GetAnimationsByTags(2, "Anal", TagSuppress = "Aggressive", RequireAll = false)
elseif Main.WhoreAction == 3
	anims = SexLab.GetAnimationsByTags(2, "Blowjob", TagSuppress = "Aggressive", RequireAll = false)
elseif Main.WhoreAction == 4
	anims = SexLab.GetAnimationsByTags(2, "Handjob", TagSuppress = "Aggressive", RequireAll = false)
else
	anims = SexLab.GetAnimationsByTags(2, "Footjob", TagSuppress = "Aggressive", RequireAll = false)
endif

SexLab.StartSex(sexActors, anims, hook = "PlayersTurn")
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment
GlobalVariable Property SLSW_WhoreGold Auto
SLSW_DenWhoresUpkeep Property Main Auto
SexLabFrameWork Property SexLab auto
MiscObject Property Gold001  Auto  
