Scriptname SLSW_BlackoutUpkeep extends Quest  

SLSW_mcmConfig Property MCM  auto
GlobalVariable Property SLSW_DoseCounter  auto
GlobalVariable Property SLSW_Dose1  auto
GlobalVariable Property SLSW_Dose2  auto
GlobalVariable Property SLSW_Dose3  auto
GlobalVariable Property SLSW_Dose4  auto
GlobalVariable Property SLSW_Dose5  auto
GlobalVariable Property SLSW_Dose6  auto
GlobalVariable Property SLSW_Dose7  auto
GlobalVariable Property SLSW_Dose8  auto
GlobalVariable Property SLSW_Dose9  auto
GlobalVariable Property SLSW_Dose10  auto
GlobalVariable Property SLSW_Dose11  auto
GlobalVariable Property SLSW_Dose12  auto
GlobalVariable Property SLSW_Dose13  auto
GlobalVariable Property SLSW_Dose14  auto
GlobalVariable Property SLSW_Dose15  auto
GlobalVariable Property SLSW_Dose16  auto
GlobalVariable Property SLSW_Dose17  auto
GlobalVariable Property SLSW_Dose18  auto
GlobalVariable Property SLSW_Dose19  auto
GlobalVariable Property SLSW_Dose20  auto
GlobalVariable Property GameHour  auto
GlobalVariable Property GameDay  auto
GlobalVariable Property GameMonth  auto
GlobalVariable Property GameYear  auto
ImageSpaceModifier Property FadeToBlack  auto
ImageSpaceModifier Property FadeToBlackHold  auto
ImageSpaceModifier Property Woozy  auto
Idle Property WakeUp  auto
SLSW_scum Property SleepScript Auto
WorldSpace Property WhiterunWorld auto
WorldSpace Property WindhelmWorld auto
WorldSpace Property SolitudeWorld auto
WorldSpace Property RiftenWorld auto
WorldSpace Property MarkarthWorld auto
ObjectReference Property WRMarker Auto
ObjectReference Property MKMarker Auto
ObjectReference Property WHMarker Auto
ObjectReference Property SOMarker Auto
ObjectReference Property RFMarker Auto
ObjectReference Property DSMarker Auto
ObjectReference Property MTMarker Auto
ObjectReference Property WHoMarker Auto
ObjectReference Property FKMarker Auto
ObjectReference Property DSCenterObject Auto
ObjectReference Property MTCenterObject Auto
ObjectReference Property FKCenterObject Auto
ObjectReference Property WHoCenterObject Auto
ObjectReference Property WHdoor Auto
ObjectReference Property WRdoor Auto
ObjectReference Property SOdoor Auto
ObjectReference Property RFdoor Auto
ObjectReference Property MTdoor Auto
ObjectReference Property DSdoor Auto
ObjectReference Property FKdoor Auto
SexLabFrameWork Property SexLab Auto
ReferenceAlias Property Alias_Stranger1 Auto
Location Property SolitudeLocation auto
Location Property MarkarthLocation auto
Location Property RiftenLocation auto
Location Property WhiterunLocation auto
Location Property WindhelmLocation auto
Location Property DawnstarLocation auto
Location Property MorthalLocation auto
Location Property WinterholdLocation auto
Location Property FalkreathLocation auto
SPELL Property slsw_ISMRemovalSpell auto

Event OnInit()
RegisterForModEvent("AnimationEnd_Blackout", "WhatANight")
endEvent

Event WhatANight(string eventName, string argString, float argNum, form sender)
Utility.Wait(1)
FadeToBlack.Apply(1.0)
Game.DisablePlayerControls(ablooking = True, abCamSwitch = True)
Game.ForceFirstPerson()
FadeToBlackHold.Apply(1.0)
Alias_Stranger1.getRef().Disable()
Utility.Wait(2)
WakeUp()
endEvent

Function Overdose(float DrugTime)

float[] DoseTracking = new float[20]
DoseTracking[0] = SLSW_Dose1.getValue()
DoseTracking[1] = SLSW_Dose2.getValue()
DoseTracking[2] = SLSW_Dose3.getValue()
DoseTracking[3] = SLSW_Dose4.getValue()
DoseTracking[4] = SLSW_Dose5.getValue()
DoseTracking[5] = SLSW_Dose6.getValue()
DoseTracking[6] = SLSW_Dose7.getValue()
DoseTracking[7] = SLSW_Dose8.getValue()
DoseTracking[8] = SLSW_Dose9.getValue()
DoseTracking[9] = SLSW_Dose10.getValue()
DoseTracking[10] = SLSW_Dose11.getValue()
DoseTracking[11] = SLSW_Dose12.getValue()
DoseTracking[12] = SLSW_Dose13.getValue()
DoseTracking[13] = SLSW_Dose14.getValue()
DoseTracking[14] = SLSW_Dose15.getValue()
DoseTracking[15] = SLSW_Dose16.getValue()
DoseTracking[16] = SLSW_Dose17.getValue()
DoseTracking[17] = SLSW_Dose18.getValue()
DoseTracking[18] = SLSW_Dose19.getValue()
DoseTracking[19] = SLSW_Dose20.getValue()

UpdateDoseTracking(DoseTracking)

SortDoseTracking(DoseTracking)

int x = DoseTracking.rfind(0)
DoseTracking[x] = (DrugTime*24)

float Doses = SLSW_DoseCounter.getValue()

	if Doses > MCM.BlackoutThreshold && Game.GetPlayer().IsInCombat() == false

		if Utility.RandomInt(1, 100) <= ((Doses - MCM.BlackoutThreshold) * 10)
			
			FadeToBlack.Apply(1.0)
			FadeToBlackHold.Apply(1.0)
			utility.wait(3)
			Debug.messagebox("You blacked out due to an overdose!")
			 
			Game.DisablePlayerControls(ablooking = True, abCamSwitch = True)
			Game.ForceFirstPerson()
			If Game.GetPlayer().getworldSpace() == WhiterunWorld || Game.GetPlayer().IsInLocation(WhiterunLocation)
				Game.GetPlayer().MoveTo(WRMarker)
				WRdoor.setOpen(true)
				WakeUp()
			ElseIf Game.GetPlayer().getworldSpace() == WindhelmWorld || Game.GetPlayer().IsInLocation(WindhelmLocation)
				Game.GetPlayer().MoveTo(WHMarker)
				WHdoor.setOpen(true)
				WakeUp()
			ElseIf Game.GetPlayer().getworldSpace() == RiftenWorld || Game.GetPlayer().IsInLocation(RiftenLocation)
				Game.GetPlayer().MoveTo(RFMarker)
				RFdoor.setOpen(true)
				WakeUp()
			ElseIf Game.GetPlayer().getworldSpace() == SolitudeWorld || Game.GetPlayer().IsInLocation(SolitudeLocation)
				Game.GetPlayer().MoveTo(SOMarker)
				SOdoor.setOpen(true)
				WakeUp()
			ElseIf Game.GetPlayer().getworldSpace() == MarkarthWorld || Game.GetPlayer().IsInLocation(MarkarthLocation)
				Game.GetPlayer().MoveTo(MKMarker)
				WakeUp()
			else
				if Game.GetPlayer().getDistance(MTCenterObject) <= 5000 || Game.GetPlayer().IsInLocation(MorthalLocation)
					Game.GetPlayer().MoveTo(MTMarker)
					MTdoor.setOpen(true)
					WakeUp()
				elseif Game.GetPlayer().getDistance(DSCenterObject) <= 5000 || Game.GetPlayer().IsInLocation(DawnstarLocation)
					Game.GetPlayer().MoveTo(DSMarker)
					DSdoor.setOpen(true)
					WakeUp()
				elseif Game.GetPlayer().getDistance(FKCenterObject) <= 5000 || Game.GetPlayer().IsInLocation(FalkreathLocation)
					Game.GetPlayer().MoveTo(FKMarker)
					FKdoor.setOpen(true)
					WakeUp()
				elseif Game.GetPlayer().getDistance(WHoCenterObject) <= 5000 || Game.GetPlayer().IsInLocation(WinterholdLocation)
					Game.GetPlayer().MoveTo(WHoMarker)
					WakeUp()
				else
					int Random = Utility.RandomInt(1, 100)
					if Random <= 33
						Alias_Stranger1.getRef().moveTo(Game.GetPlayer())
						Alias_Stranger1.getRef().Enable()
						(Alias_Stranger1.getRef() as actor).setAV("Aggression", 0)
						Game.ForceThirdPerson()
						Game.EnablePlayerControls()
						FadeToBlackHold.Remove()
						Woozy.Apply()
						actor[] sexActors = new actor[2]
						sexActors[0] = Game.GetPlayer()
						sexActors[1] = Alias_Stranger1.getRef() as actor
						sslBaseAnimation[] anims
						anims = SexLab.GetAnimationsByTags(2, "Sleeping", RequireAll = false)
						SexLab.StartSex(sexActors, anims, victim = Game.GetPlayer(), allowBed=false, hook="blackout")
					else
						WakeUp()
					endif
				endif
			endif
		endif
	endif

SLSW_Dose1.setValue(DoseTracking[0])
SLSW_Dose2.setValue(DoseTracking[1])
SLSW_Dose3.setValue(DoseTracking[2])
SLSW_Dose4.setValue(DoseTracking[3])
SLSW_Dose5.setValue(DoseTracking[4])
SLSW_Dose6.setValue(DoseTracking[5])
SLSW_Dose7.setValue(DoseTracking[6])
SLSW_Dose8.setValue(DoseTracking[7])
SLSW_Dose9.setValue(DoseTracking[8])
SLSW_Dose10.setValue(DoseTracking[9])
SLSW_Dose11.setValue(DoseTracking[10])
SLSW_Dose12.setValue(DoseTracking[11])
SLSW_Dose13.setValue(DoseTracking[12])
SLSW_Dose14.setValue(DoseTracking[13])
SLSW_Dose15.setValue(DoseTracking[14])
SLSW_Dose16.setValue(DoseTracking[15])
SLSW_Dose17.setValue(DoseTracking[16])
SLSW_Dose18.setValue(DoseTracking[17])
SLSW_Dose19.setValue(DoseTracking[18])
SLSW_Dose20.setValue(DoseTracking[19])

endFunction

Function UpdateDoseTracking(float[] myArray)

float Doses = SLSW_DoseCounter.getValue()
int a = 0
int b = 0

While a == 0
	if b <= 19
		if (myArray[b] != 0) && ((Utility.getCurrentGameTime()*24) - myArray[b] >= 1)
			Doses -= 1
			myArray[b] = 0
			b += 1
		else
			b += 1
		endif
	else
		SLSW_DoseCounter.setValue(Doses)
		a += 1
	endif
endWhile
Return
endFunction

Function SortDoseTracking (Float[] MyArray)
 
Int Index1
Int Index2 = MyArray.Length - 1
 
	While (Index2 > 0)
		Index1 = 0
		While (Index1 < Index2)
			If (MyArray [Index1] > MyArray [Index1 + 1])
				Float SwapDummy = MyArray [Index1]
				MyArray [Index1] = MyArray [Index1 + 1]
				MyArray [Index1 + 1] = SwapDummy
			EndIf
			Index1 += 1
		EndWhile
		Index2 -= 1
	EndWhile
Return
EndFunction

Function IncreaseTime(int time)

int Hour = GameHour.getValue() as Int
Hour += time

if Hour <= 23
	GameHour.setValue(Hour)
else
	Hour = Hour - 24
	GameHour.setValue(Hour)

	int Day = GameDay.getValue() as Int
	Day += 1
	int Month = GameMonth.getValue() as Int
	if Month == 1 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(2)
	elseif Month == 2 && Day == 28
		GameDay.setValue(1)		
		GameMonth.setValue(3)
	elseif Month == 3 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(4)
	elseif Month == 4 && Day == 30
		GameDay.setValue(1)		
		GameMonth.setValue(5)
	elseif Month == 5 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(6)
	elseif Month == 6 && Day == 30
		GameDay.setValue(1)		
		GameMonth.setValue(7)
	elseif Month == 7 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(8)
	elseif Month == 8 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(9)
	elseif Month == 9 && Day == 30
		GameDay.setValue(1)		
		GameMonth.setValue(10)
	elseif Month == 10 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(11)
	elseif Month == 11 && Day == 30
		GameDay.setValue(1)		
		GameMonth.setValue(12)
	elseif Month == 12 && Day == 31
		GameDay.setValue(1)		
		GameMonth.setValue(1)
		int Year = GameYear.getValue() as Int
		Year += 1
		GameYear.setValue(Year)
	else
		GameDay.setValue(Day)
	endif
endif

endFunction

Function WakeUp()
	IncreaseTime(Utility.RandomInt(4,8))
	slsw_ISMRemovalSpell.Cast(Game.GetPlayer(), Game.GetPlayer())
	SleepScript.SleepItOff()
	FadeToBlackHold.Remove()
	Woozy.Apply()
	Game.GetPlayer().PlayIdle (WakeUp)
	Game.EnablePlayerControls()
	return
endFunction