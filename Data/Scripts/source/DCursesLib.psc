ScriptName DCursesLib

Armor function GetRandomEquipableDevice() global Native

;function OnObjectActivated(ObjectReference akTargetRef) global Native
function OnUpdate() global Native

function SexStarted(Actor[] akActors) global Native
function SexEnded(Actor[] akActors) global Native

Function PauseEvents(Bool value) global Native

string function GetAnimationFilterTags(Actor akActor) global Native
string function GetAnimationFilterTagsP(Actor akActor) global Native

int Function NumDevicesVisible(Actor akActor) global Native

Function Test() global Native

Function StartSex(Actor aggressor) global
	SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
	Actor player = Game.getPlayer()
	Actor[] positions = new Actor[2]
	positions[0] = player
	positions[1] = aggressor

	if sexlab.GetVersion() <= 16601

		sslBaseAnimation[] anims
		if sexlab.ActorLib.GetGender(aggressor) == 2
			anims = sexlab.GetCreatureAnimationsByActors(2, positions)
			anims = sexlab.RemoveTagged(anims, DCursesLib.GetAnimationFilterTags(player))
		else
			anims = sexlab.GetAnimationsByTags(2, "Aggressive", DCursesLib.GetAnimationFilterTags(player))
		endif
		if anims.Length == 0
			debug.Trace("[DCURSES] [sex] No Anims")
			return
		endif
		sexlab.StartSex(Positions, anims, hook = "DCURSES")
	else
		SexLabThread thread = sexlab.StartScene(positions, "Aggressive,"+DCursesLib.GetAnimationFilterTagsP(player), player)
		if (thread == None)
			;Attempt scene without aggressive tag if no scenes were found.
			sexlab.StartScene(positions, DCursesLib.GetAnimationFilterTagsP(player), player)
		endif
	EndIf
EndFunction

Function SlowStrip(Actor akActor) Global
	if akActor == None
		Return
	endif
	SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
	sexlab.StripActor(akActor, None, False, false)
EndFunction

; ModEvent sent on Bondage Curse
; who: Actor that the devices are equipped to. For now is always player
; what: Name of whatever caused the trap.
; device_count: The number of devices that were equipped
; devices: a comma separated list of all the device names
; device_ids: a comma separated list of all the device editor ids
Function SendModEventDevices(Actor who, String what, int device_count, String devices, String device_ids) Global
	Debug.Trace("Devious Curses: sending devices mod event")
	int handle = ModEvent.Create("DCURSES_CurseTriggeredDevices")
	if (handle)
		ModEvent.PushForm(handle, who)
		ModEvent.PushString(handle, what)
		ModEvent.PushInt(handle, device_count)
		ModEvent.PushString(handle, devices)
		ModEvent.PushString(handle, device_ids)
		ModEvent.Send(handle)
	endif
EndFunction

; ModEvent sent on LewdMark Curse
; who: Actor that the mark is given to. For now is always player
; what: Name of whatever caused the trap.
; mark_name: the name of the mark given to the actor
; mark_id: the id of the mark within LewdMarks
Function SendModEventMark(Actor who, String what, String mark_name, Int mark_id) Global
	Debug.Trace("Devious Curses: sending mark mod event")
	int handle = ModEvent.Create("DCURSES_CurseTriggeredMark")
	if (handle)
		ModEvent.PushForm(handle, who)
		ModEvent.PushString(handle, what)
		ModEvent.PushString(handle, mark_name)
		ModEvent.PushInt(handle, mark_id)
		ModEvent.Send(handle)
	endif
EndFunction

; ModEvent sent on Tattoo Curse
; who: Actor that the tattoos are given to. For now is always player
; what: Name of whatever caused the trap.
; tattoo_count: the name of the mark given to the actor
Function SendModEventTattoo(Actor who, String what, Int tattoo_count) Global
	Debug.Trace("Devious Curses: sending tattoo mod event")
	int handle = ModEvent.Create("DCURSES_CurseTriggeredTattoos")
	if (handle)
		ModEvent.PushForm(handle, who)
		ModEvent.PushString(handle, what)
		ModEvent.PushInt(handle, tattoo_count)
		ModEvent.Send(handle)
	endif
EndFunction

; ModEvent sent on Contraption Curse
; who: Actor that the tattoos are given to. For now is always player
; what: Name of whatever caused the trap.
Function SendModEventContraption(Actor who, String what) Global
	Debug.Trace("Devious Curses: sending contraption mod event")
	int handle = ModEvent.Create("DCURSES_CurseTriggeredContraption")
	if (handle)
		ModEvent.PushForm(handle, who)
		ModEvent.PushString(handle, what)
		ModEvent.Send(handle)
	endif
EndFunction