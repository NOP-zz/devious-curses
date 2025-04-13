Scriptname slsw_suppression extends activemagiceffect  

Spell Property pAbilityToRemove Auto
SLSW_upkeep property main auto
SLSW_mcmConfig property MCM auto
GlobalVariable property DrugPool_pd auto
GlobalVariable property DrugPool_md auto
GlobalVariable property DrugPool_mkd auto
SPELL property pd1 auto
SPELL property pd2 auto
SPELL property pd3 auto
SPELL property pd4 auto
SPELL property pd5 auto
SPELL property md1 auto
SPELL property md2 auto
SPELL property md3 auto
SPELL property md4 auto
SPELL property md5 auto
SPELL property mkd1 auto
SPELL property mkd2 auto
SPELL property mkd3 auto
SPELL property mkd4 auto
SPELL property mkd5 auto

Event OnUpdateGameTime()
	Utility.Wait(0.1)

	Game.GetPlayer().RemoveSpell(pAbilityToRemove)

;	Debug.Notification("Suppression effect has finished!")

	main.withdrawal((DrugPool_pd.getValue()), pd1, pd2, pd3, pd4, pd5)
	main.withdrawal((DrugPool_md.getValue()), md1, md2, md3, md4, md5)
	main.withdrawal((DrugPool_mkd.getValue()), mkd1, mkd2, mkd3, mkd4, mkd5)
	
EndEvent

Event OnEffectStart(Actor akTarget, Actor akCaster)
	
float[] DrugPools = new float[3]
DrugPools[0] = DrugPool_pd.getValue()
DrugPools[1] = DrugPool_md.getValue()
DrugPools[2] = DrugPool_mkd.getValue()

FindHighestPool(DrugPools)

float DecisivePool = DrugPools[2]

suppression(DecisivePool)

EndEvent

Function FindHighestPool (Float[] MyArray)
 
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

EndFunction

function suppression(float NewValue)
actor player = game.getplayer()

	If MCM.speed == "Fast"
		If NewValue < 70
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 70 && NewValue < 120
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 120 && NewValue < 180
			RegisterForSingleUpdateGameTime(7)
			Return
		elseif NewValue >= 180 && NewValue < 250
			RegisterForSingleUpdateGameTime(5.5)
			Return
		else
			RegisterForSingleUpdateGameTime(3)
			Return
		endif
	elseif MCM.speed == "Medium"
		If NewValue < 140
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 140 && NewValue < 240
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 240 && NewValue < 360	
			RegisterForSingleUpdateGameTime(7)
			Return
		elseif NewValue >= 360 && NewValue < 500
			RegisterForSingleUpdateGameTime(5.5)
			Return
		else
			RegisterForSingleUpdateGameTime(3)
			Return
		endif
	else
		If NewValue < 210
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 210 && NewValue < 360
			RegisterForSingleUpdateGameTime(8)
			Return
		elseif NewValue >= 360 && NewValue < 540	
			RegisterForSingleUpdateGameTime(7)
			Return
		elseif NewValue >= 540 && NewValue < 750
			RegisterForSingleUpdateGameTime(5.5)
			Return
		else
			RegisterForSingleUpdateGameTime(3)
			Return
		endif
	endif
endfunction