Scriptname SLSW_Effects extends Quest  

SLSW_mcmconfig property MCM auto
MagicEffect property WithdrawalSuppression auto
Potion Property Skooma auto
Potion Property RoseOfAzura auto
Potion Property BoethiasDeception auto
Potion Property ThiefsDelight auto
Potion Property TheSecondBrain auto
Potion Property ElendrsFlask auto
Potion Property TheContortionist auto
Potion Property MorgulsTouch auto
Potion Property ToughFlesh auto
Potion Property OcatosPallatine auto
Potion Property MagesFriend auto
Potion Property TheArchMage auto
Potion Property VerminasPrice auto
Potion Property LeafSkooma auto
Potion Property DDSkooma auto
Idle Property IdleForceDefaultState auto
Idle Property BleedOutStart auto
Idle Property BleedOutStop auto
Idle Property IdleNervous auto
Idle Property IdleDrinkPotion auto
GlobalVariable Property SLSW_AddictionIndicator auto
ImageSpaceModifier Property slsw_BlurryISM auto
SexLabFramework Property SexLab auto

Event OnInit()

RegisterForUpdateGameTime(MCM.EffectInterval)

EndEvent

Event OnUpdateGameTime()

Utility.Wait(0.1)

If MCM.Effects == True && SLSW_AddictionIndicator.getValue() >= 3 && Game.GetPlayer().HasMagicEffect(WithdrawalSuppression) != true && Game.getPlayer().IsInCombat() != true && Game.getPlayer().IsOnMount() != true && Game.getPlayer().IsSwimming() != true && SexLab.IsActorActive(Game.getPlayer()) != true && Game.getPlayer().GetDialogueTarget() == none
	slsw_BlurryISM.apply(1.0)
	Utility.Wait(6)
	If Utility.RandomInt(1,100) <= 40
		;trip
		Debug.SendAnimationEvent(Game.GetPlayer(), "IdleForceDefaultState")
		Debug.SendAnimationEvent(Game.GetPlayer(), "BleedOutStart")
		Utility.Wait(2)
		Debug.SendAnimationEvent(Game.GetPlayer(), "BleedOutStop")
		Utility.Wait(2)
		Debug.SendAnimationEvent(Game.GetPlayer(), "IdleForceDefaultState")
	else
		int DrugCount = 0
		If Game.GetPlayer().GetItemCount(Skooma) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(RoseOfAzura) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(BoethiasDeception) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(ThiefsDelight) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(TheSecondBrain) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(ElendrsFlask) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(TheContortionist) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(VerminasPrice) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(MorgulsTouch) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(ToughFlesh) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(OcatosPallatine) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(MagesFriend) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(TheArchMage) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(LeafSkooma) > 0
			DrugCount += 1
		endIf
		If Game.GetPlayer().GetItemCount(DDSkooma) > 0
			DrugCount += 1
		endIf
			
		If DrugCount != 0
			;drink
			
			string[] drugs
			
			if DrugCount == 1
				drugs = new string[1]
			elseIf DrugCount == 2
				drugs = new string[2]
			elseIf DrugCount == 3
				drugs = new string[3]
			elseIf DrugCount == 4
				drugs = new string[4]
			elseIf DrugCount == 5
				drugs = new string[5]
			elseIf DrugCount == 6
				drugs = new string[6]
			elseIf DrugCount == 7
				drugs = new string[7]
			elseIf DrugCount == 8
				drugs = new string[8]
			elseIf DrugCount == 9
				drugs = new string[9]
			elseIf DrugCount == 10
				drugs = new string[10]
			elseIf DrugCount == 11
				drugs = new string[11]
			elseIf DrugCount == 12
				drugs = new string[12]
			elseIf DrugCount == 13
				drugs = new string[13]
			elseIf DrugCount == 14
				drugs = new string[14]
			elseIf DrugCount == 15
				drugs = new string[15]
			endif
			
			int pos = 0
			
			If Game.GetPlayer().GetItemCount(Skooma) > 0
				drugs[pos] = "Skooma"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(RoseOfAzura) > 0
				drugs[pos] = "RoseOfAzura"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(BoethiasDeception) > 0
				drugs[pos] = "BoethiasDeception"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(ThiefsDelight) > 0
				drugs[pos] = "ThiefsDelight"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(TheSecondBrain) > 0
				drugs[pos] = "TheSecondBrain"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(ElendrsFlask) > 0
				drugs[pos] = "ElendrsFlask"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(TheContortionist) > 0
				drugs[pos] = "TheContortionist"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(VerminasPrice) > 0
				drugs[pos] = "VerminasPrice"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(MorgulsTouch) > 0
				drugs[pos] = "MorgulsTouch"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(ToughFlesh) > 0
				drugs[pos] = "ToughFlesh"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(OcatosPallatine) > 0
				drugs[pos] = "OcatosPallatine"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(MagesFriend) > 0
				drugs[pos] = "MagesFriend"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(TheArchMage) > 0
				drugs[pos] = "TheArchMage"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(LeafSkooma) > 0
				drugs[pos] = "LeafSkooma"
				pos += 1
			endIf
			If Game.GetPlayer().GetItemCount(DDSkooma) > 0
				drugs[pos] = "DDSkooma"
			endIf
					
				int iDrug = Utility.RandomInt(0, (drugs.length - 1))
			Utility.Wait(1)
			
			if (drugs[iDrug]) == "Skooma"
				Game.GetPlayer().EquipItem(Skooma)
			elseif (drugs[iDrug]) == "RoseOfAzura"
				Game.GetPlayer().EquipItem(RoseOfAzura)			
			elseif (drugs[iDrug]) == "BoethiasDeception"
				Game.GetPlayer().EquipItem(BoethiasDeception)			
			elseif (drugs[iDrug]) == "ThiefsDelight"
				Game.GetPlayer().EquipItem(ThiefsDelight)			
			elseif (drugs[iDrug]) == "TheSecondBrain"
				Game.GetPlayer().EquipItem(TheSecondBrain)			
			elseif (drugs[iDrug]) == "ElendrsFlask"
				Game.GetPlayer().EquipItem(ElendrsFlask)			
			elseif (drugs[iDrug]) == "TheContortionist"
				Game.GetPlayer().EquipItem(TheContortionist)
			elseif (drugs[iDrug]) == "VerminasPrice"
				Game.GetPlayer().EquipItem(VerminasPrice)
			elseif (drugs[iDrug]) == "MorgulsTouch"
				Game.GetPlayer().EquipItem(MorgulsTouch)
			elseif (drugs[iDrug]) == "ToughFlesh"
				Game.GetPlayer().EquipItem(ToughFlesh)
			elseif (drugs[iDrug]) == "OcatosPallatine"
				Game.GetPlayer().EquipItem(OcatosPallatine)
			elseif (drugs[iDrug]) == "MagesFriend"
				Game.GetPlayer().EquipItem(MagesFriend)
			elseif (drugs[iDrug]) == "TheArchMage"
				Game.GetPlayer().EquipItem(TheArchMage)
			elseif (drugs[iDrug]) == "LeafSkooma"
				Game.GetPlayer().EquipItem(LeafSkooma)
			elseif (drugs[iDrug]) == "DDSkooma"
				Game.GetPlayer().EquipItem(DDSkooma)
			endif
			
			Game.GetPlayer().SheatheWeapon()
			Debug.SendAnimationEvent(Game.GetPlayer(), "IdleForceDefaultState")
			Game.GetPlayer().PlayIdle(IdleDrinkPotion)
			Utility.Wait(6)
			Debug.SendAnimationEvent(Game.GetPlayer(), "IdleForceDefaultState")
			
		EndIf
	EndIf
EndIF
EndEvent

Function EffectsOff()
UnregisterForUpdateGameTime()
Return
EndFunction

Function EffectsOn()
RegisterForUpdateGameTime(MCM.EffectInterval)
Return
EndFunction