;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname TIF__030063C7 Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
Utility.Wait(1)
Game.GetPlayer().addItem(Skooma)

actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = akSpeaker

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Vaginal", TagSuppress = "Aggressive", RequireAll = true)

SexLab.StartSex(sexActors, anims)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

Potion Property Skooma  Auto  

SexLabFramework Property SexLab  Auto  
