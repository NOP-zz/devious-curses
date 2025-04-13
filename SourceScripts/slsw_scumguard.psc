Scriptname SLSW_scumGuard extends Quest  

float property Time auto
WorldSpace property WhiterunWorld auto
WorldSpace property SolitudeWorld auto
WorldSpace property RiftenWorld auto
WorldSpace property MarkarthWorld auto
WorldSpace property WindhelmWorld auto
ReferenceAlias Property Guard auto
SexLabFrameWork Property SexLab Auto

Function Leave()
	RegisterForUpdateGameTime(0.0833)
	Return
EndFunction

Event OnUpdateGameTime()
Utility.Wait(0.1)
if self.getStage() == 20 || self.getStage() == 10
	If (Guard.getRef() as actor).getDistance(Game.getPlayer()) <= 4096
		If  (Game.GetPlayer().GetWorldSpace() == WhiterunWorld)
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				(Guard.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
				(Guard.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
				self.stop()
			elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
				self.stop()
			endif
		elseif   (Game.GetPlayer().GetWorldSpace() == SolitudeWorld)
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				(Guard.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
				(Guard.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
				self.stop()
			elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
				self.stop()
			endif
		elseif   (Game.GetPlayer().GetWorldSpace() == RiftenWorld)
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				(Guard.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
				(Guard.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
				self.stop()
			elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
				self.stop()
			endif
		elseif   (Game.GetPlayer().GetWorldSpace() == WindhelmWorld)
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				(Guard.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
				(Guard.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
				self.stop()
			elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
				self.stop()
			endif
		elseif   (Game.GetPlayer().GetWorldSpace() == MarkarthWorld)
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				(Guard.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
				(Guard.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
				self.stop()
			elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
				self.stop()
			endif
		else
			If ((Utility.GetCurrentGameTime() * 24) - Time >= 1.25)
				self.stop()
			endif
		endif
	else
		self.stop()
	endIf
else
	If ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
		self.stop()
	endif
endif
EndEvent

Function PrepareAction()
RegisterForModEvent("AnimationEnd_Guard", "Guard")
return
Endfunction

Event Guard(string eventName, string argString, float argNum, form sender)
self.reset()
self.stop()
EndEvent

function Action()
SexLab.QuickStart(Game.GetPlayer(), Guard.GetRef() as actor)
endfunction