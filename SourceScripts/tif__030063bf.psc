;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname TIF__030063BF Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
Utility.Wait(1)
Game.GetPlayer().addItem(Skooma, 2)

actor[] sexActors = new actor[2]
    sexActors[0] = Game.GetPlayer()
    sexActors[1] = akSpeaker

sslBaseAnimation[] anims = SexLab.GetAnimationsByTags(2, "Vaginal", TagSuppress = "Aggressive", RequireAll = true)

SexLab.StartSex(sexActors, anims)
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

SexLabFramework Property SexLab  Auto  

Potion Property Skooma  Auto  
