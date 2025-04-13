Scriptname SLSW_PlayerProstitutionUpkeep extends Quest conditional 

SexLabFramework Property SexLab auto
float Property Cut auto hidden
int Property Gold auto hidden
int Property AllGold auto hidden
int Property ClientCount auto hidden
int Property ClientAction auto conditional hidden
Cell Property WRden Auto
Cell Property WHden Auto
Cell Property SOden Auto
Cell Property RFden Auto
Cell Property MKden Auto
ObjectReference Property WRmarker Auto
ObjectReference Property WHmarker Auto
ObjectReference Property SOmarker Auto
ObjectReference Property RFmarker Auto
ObjectReference Property MKmarker Auto
ReferenceAlias Property Alias_Client Auto
Actor Property Client29 Auto
Actor Property Client3 Auto
Actor Property Client30 Auto
Actor Property Client31 Auto
Actor Property Client32 Auto
Actor Property Client33 Auto
Actor Property Client34 Auto
Actor Property Client35 Auto
Actor Property Client36 Auto
Actor Property Client37 Auto
Actor Property Client38 Auto
Actor Property Client4 Auto
Actor Property Client40 Auto
Actor Property Client5 Auto
Actor Property Client6 Auto
Actor Property Client7 Auto
Actor Property Client9 Auto
Actor Property Client39 Auto

event OnInit()
RegisterForModEvent("AnimationEnd_PPend", "YouCanLeaveNow")
endevent

event OnUpdate()
If Game.getPlayer().getParentCell() == WRden
	GetClient()
	(Alias_Client.GetRef() as Actor).MoveTo(WRmarker)
	SetStage(20)
elseIf Game.getPlayer().getParentCell() == WHden
	GetClient()
	(Alias_Client.GetRef() as Actor).MoveTo(WHmarker)
	SetStage(20)
elseIf Game.getPlayer().getParentCell() == SOden
	GetClient()
	(Alias_Client.GetRef() as Actor).MoveTo(SOmarker)
	SetStage(20)
elseIf Game.getPlayer().getParentCell() == RFden
	GetClient()
	(Alias_Client.GetRef() as Actor).MoveTo(RFmarker)
	SetStage(20)
elseIf Game.getPlayer().getParentCell() == MKden
	GetClient()
	(Alias_Client.GetRef() as Actor).MoveTo(MKmarker)
	SetStage(20)
else
	RegisterForSingleUpdate(60)
endif
EndEvent

Function GetClient()
Int Random = Utility.RandomInt(1, 18)
if Random == 1
	Alias_Client.ForceRefTo(Client29)
elseif Random == 2
	Alias_Client.ForceRefTo(Client3)
elseif Random == 3
 	Alias_Client.ForceRefTo(Client30)
elseif Random == 4
 	Alias_Client.ForceRefTo(Client31)
elseif Random == 5
 	Alias_Client.ForceRefTo(Client32)
elseif Random == 6
 	Alias_Client.ForceRefTo(Client33)
elseif Random == 7
 	Alias_Client.ForceRefTo(Client34)
elseif Random == 8
 	Alias_Client.ForceRefTo(Client35)
elseif Random == 9
 	Alias_Client.ForceRefTo(Client36)
elseif Random == 10
 	Alias_Client.ForceRefTo(Client37)
elseif Random == 11
 	Alias_Client.ForceRefTo(Client38)
elseif Random == 12
 	Alias_Client.ForceRefTo(Client39)
elseif Random == 13
 	Alias_Client.ForceRefTo(Client4)
elseif Random == 14
 	Alias_Client.ForceRefTo(Client40)
elseif Random == 15
 	Alias_Client.ForceRefTo(Client5)
elseif Random == 16
 	Alias_Client.ForceRefTo(Client6)
elseif Random == 17
 	Alias_Client.ForceRefTo(Client7)
elseif Random == 18
 	Alias_Client.ForceRefTo(Client9)
endif
return 
endFunction

Function Action()
actor[] sexActors = new actor[2]
	sexActors[0] = Game.GetPlayer()
	sexActors[1] = (Alias_Client.GetRef() as Actor)

sslBaseAnimation[] anims
if ClientAction == 1
	anims = SexLab.GetAnimationsByTags(2, "Vaginal", TagSuppress = "Aggressive", RequireAll = false)
elseif ClientAction == 2
	anims = SexLab.GetAnimationsByTags(2, "Anal", TagSuppress = "Aggressive", RequireAll = false)
elseif ClientAction == 3
	anims = SexLab.GetAnimationsByTags(2, "Blowjob", TagSuppress = "Aggressive", RequireAll = false)
elseif ClientAction == 4
	anims = SexLab.GetAnimationsByTags(2, "Handjob", TagSuppress = "Aggressive", RequireAll = false)
else
	anims = SexLab.GetAnimationsByTags(2, "Footjob", TagSuppress = "Aggressive", RequireAll = false)
endif

SexLab.StartSex(sexActors, anims, hook = "PPend")
return
endfunction

Event YouCanLeaveNow(string eventName, string argString, float argNum, form sender)
	SetStage(60)
endevent