Scriptname SLSW_DenWhoresUpkeep extends Quest

Cell Property DenWH auto
Cell Property DenWR auto
Cell Property DenRF auto
Cell Property DenSO auto
Cell Property DenMK auto
ObjectReference Property MarkerWH Auto
ObjectReference Property MarkerWR Auto
ObjectReference Property MarkerSO Auto
ObjectReference Property MarkerRF Auto
ObjectReference Property MarkerMK Auto
ObjectReference Property COCMarker Auto
ReferenceAlias Property Client Auto
Actor Property SLSW_Client1 auto
Actor Property SLSW_Client11 auto
Actor Property SLSW_Client12 auto
Actor Property SLSW_Client14 auto
Actor Property SLSW_Client16 auto
Actor Property SLSW_Client17 auto
Actor Property SLSW_Client18 auto
Actor Property SLSW_Client19 auto
Actor Property SLSW_Client2 auto
Actor Property SLSW_Client20 auto
Actor Property SLSW_Client21 auto
Actor Property SLSW_Client22 auto
Actor Property SLSW_Client23 auto
Actor Property SLSW_Client24 auto
Actor Property SLSW_Client25 auto
Actor Property SLSW_Client26 auto
Actor Property SLSW_Client27 auto
Actor Property SLSW_Client28 auto
SexLabFramework Property SexLab auto
int Property Den auto hidden
actor Property whoreWR auto
actor Property whoreWH auto
actor Property whoreSO auto
actor Property whoreRF auto
actor Property whoreMK auto
int property whoreaction auto hidden 

Event OnInit()
RegisterForModEvent("AnimationEnd_SLSW", "Finished")
RegisterForModEvent("AnimationEnd_PlayersTurn", "PlayerFinished")
endEvent

Event OnUpdate()
Utility.Wait(0.1)
If Game.GetPlayer().getParentCell() == DenWH
	if getStage() == 0
		den = 1
		GetClient()
		Client.getRef().MoveTo(MarkerWH)
		SetStage(10)
	endif
elseIF Game.GetPlayer().getParentCell() == DenWR
	if getStage() == 0
		den = 2
		GetClient()
		Client.getRef().MoveTo(MarkerWR)
		SetStage(10)
	endif
elseIF Game.GetPlayer().getParentCell() == DenSO
	if getStage() == 0
		den = 3
		GetClient()
		Client.getRef().MoveTo(MarkerSO)
		SetStage(10)
	endif
elseIF Game.GetPlayer().getParentCell() == DenRF
	if getStage() == 0
		den = 4
		GetClient()
		Client.getRef().MoveTo(MarkerRF)
		SetStage(10)
	endif
elseIF Game.GetPlayer().getParentCell() == DenMK
	if getStage() == 0
		den = 5
		GetClient()
		Client.getRef().MoveTo(MarkerMK)
		SetStage(10)
	endif
else
	if getStage() == 0
		RegisterForSingleUpdate(300)
	else
		Client.getRef().MoveTo(CocMarker)
			if (Client.getRef() as actor).isDead() == true
				(Client.getRef() as actor).Resurrect()
			endif
		setStage(40)
	endif
endif
endEvent

Function GetClient()
int Random = Utility.RandomInt(1, 18)
if Random == 1
	Client.ForceRefto(SLSW_Client1)
elseif Random == 2
	Client.ForceRefto(SLSW_Client11)
elseif Random == 3
	Client.ForceRefto(SLSW_Client12)
elseif Random == 4
	Client.ForceRefto(SLSW_Client14)
elseif Random == 5
	Client.ForceRefto(SLSW_Client16)
elseif Random == 6
	Client.ForceRefto(SLSW_Client17)
elseif Random == 7
	Client.ForceRefto(SLSW_Client18)
elseif Random == 8
	Client.ForceRefto(SLSW_Client19)
elseif Random == 9
	Client.ForceRefto(SLSW_Client2)
elseif Random == 10
	Client.ForceRefto(SLSW_Client20)
elseif Random == 11
	Client.ForceRefto(SLSW_Client21)
elseif Random == 12
	Client.ForceRefto(SLSW_Client22)
elseif Random == 13
	Client.ForceRefto(SLSW_Client23)
elseif Random == 14
	Client.ForceRefto(SLSW_Client24)
elseif Random == 15
	Client.ForceRefto(SLSW_Client25)
elseif Random == 16
	Client.ForceRefto(SLSW_Client26)
elseif Random == 17
	Client.ForceRefto(SLSW_Client27)
else
	Client.ForceRefto(SLSW_Client28)
endif
return
endFunction

Function Action()
actor[] sexActors = new actor[2]
sslBaseAnimation[] anims
if Den == 1
    sexActors[0] = WhoreWH
    sexActors[1] = Client.getRef() as actor
elseif Den == 2
    sexActors[0] = WhoreWR
    sexActors[1] = Client.getRef() as actor
elseif Den == 3
    sexActors[0] = WhoreSO
    sexActors[1] = Client.getRef() as actor
elseif Den == 4
    sexActors[0] = WhoreRF
    sexActors[1] = Client.getRef() as actor
elseif Den == 5
    sexActors[0] = WhoreMK
    sexActors[1] = Client.getRef() as actor
endif
SexLab.StartSex(sexActors, anims, hook="SLSW")
endfunction

event Finished (string eventName, string argString, float argNum, form sender)
	SetStage(30)
endEvent

event PlayerFinished (string eventName, string argString, float argNum, form sender)
	setStage(40)
endEvent