Scriptname SLSW_IDScript extends Quest  

float property time auto
ReferenceAlias Property InnKeeper auto
Keyword Property LocTypeInn auto

Function Leave()
RegisterForUpdateGameTime(0.25)
return
EndFunction

Event OnUpdateGameTime()
Utility.Wait(0.1)
If ((Utility.GetCurrentGameTime() * 24) - Time >= 1) && (Game.GetPlayer().GetCurrentLocation().HasKeyWord(LocTypeInn) == true) && self.GetStage() == 20
	(InnKeeper.getRef() as actor).GetCrimeFaction().ModCrimeGold(25, true)
	(InnKeeper.getRef() as actor).SendTrespassAlarm(Game.GetPlayer())
	self.stop()
elseif ((Utility.GetCurrentGameTime() * 24) - Time >= 5)
	self.stop()
endif
EndEvent