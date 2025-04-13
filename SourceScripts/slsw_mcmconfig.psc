Scriptname SLSW_mcmConfig extends SKI_ConfigBase

SLSW_Effects Property EffectsScript Auto
GlobalVariable Property DrugPool_pd auto
GlobalVariable Property DrugPool_md auto
GlobalVariable Property DrugPool_mkd auto
GlobalVariable Property ClientCount auto
GlobalVariable Property SLSW_Comment auto
SPELL Property pd1 auto
SPELL Property pd2 auto
SPELL Property pd3 auto
SPELL Property pd4 auto
SPELL Property pd5 auto
SPELL Property md1 auto
SPELL Property md2 auto
SPELL Property md3 auto
SPELL Property md4 auto
SPELL Property md5 auto
SPELL Property mkd1 auto
SPELL Property mkd2 auto
SPELL Property mkd3 auto
SPELL Property mkd4 auto
SPELL Property mkd5 auto
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
Potion Property HerbTea auto
Potion Property PurifingSolution auto
Potion Property DDSkooma auto
Book Property SLSW_Recipe_Skooma Auto
Book Property SLSW_Recipe_BoethiasDeception Auto
Book Property SLSW_Recipe_ThiefsDelight Auto
Book Property SLSW_Recipe_TheSecondBrain Auto
Book Property SLSW_Recipe_ElendirsFlask Auto
Book Property SLSW_Recipe_TheContortionist Auto
Book Property SLSW_Recipe_MorgulsTouch Auto
Book Property SLSW_Recipe_ToughFlesh Auto
Book Property SLSW_Recipe_OcatosPallatine Auto
Book Property SLSW_Recipe_MagesFriend Auto
Book Property SLSW_Recipe_TheArchMage Auto
Book Property SLSW_Recipe_VerminasPrice Auto
Book Property SLSW_Recipe_LeafSkooma Auto
Book Property SLSW_Recipe_PurifyingSolution Auto
Book Property SLSW_Recipe_DDSkooma Auto

; OIDs

int speedOID
int reduceOID
int resetOID
int brothelOID
int blackoutOID
int blackoutthresholdOID
int starterkitOID
int forcefeedOID
int forcefeedchanceOID
int vp_lightOID
int mf_lightOID
int tam_lightOID
int EffectIntervalOID
int EffectsOID
int highriskOID
int hrchanceOID
int scumOID
int commentsOID
int visualsOID

; Toggle states

string property speed = "Fast" auto
float property reduce = 5.0 auto
string property reset = "Reset" auto
string property brothel = "Reset" auto
bool property blackout = true  auto
float property blackoutthreshold = 5.0 auto
string property starterkit = "Starter Kit" auto
float property forcefeedchance = 30.0 auto
bool property forcefeed = true  auto
string property vp_light = "Normal" auto
string property mf_light = "Normal" auto
string property tam_light = "Normal" auto
float property Effectinterval = 1.0 auto
bool property Effects = true auto
bool property highrisk = true auto
float property hrchance = 1.0 auto
bool property scum = true auto
bool property comments = true auto
bool property visuals = true auto

; MCM

int function GetVersion()
    return 3
endFunction

event OnVersionUpdate(int a_version)
	if (a_version >= 2 && CurrentVersion < 2)
	Pages = new string[2]
	Pages[0] = "General Settings"
	Pages[1] = "Effects"
	endIf
endEvent

event OnConfigInit()
	Pages = new string[2]
	Pages[0] = "General Settings"
	Pages[1] = "Effects"
endevent
    
event OnPageReset(string Page)

SetCursorFillMode(TOP_TO_BOTTOM)

if page == "General Settings"
	AddHeaderOption("Skooma Whore by Guffel")
	AddEmptyOption()
	speedOID = AddTextOption("Addiction speed", speed)
	reduceOID = addslideroption("Daily recovering rate", reduce, "{0}")
	blackoutOID = AddToggleOption("Enable Blackout", blackout)
	blackoutthresholdOID = addslideroption("Blackout Threshold", blackoutthreshold, "{0}")
	forcefeedOID = AddToggleOption("Enable Forced Drugging", forcefeed)
	forcefeedchanceOID = addslideroption("Forced Drugging Chance", forcefeedchance, "{0}")
	AddEmptyOption()
	;starterkitOID = AddTextOption("Starter Kit", starterkit)
	resetOID = AddTextOption("Reset addiction", reset)
	;brothelOID = AddTextOption("Reset brothel", brothel)

	SetCursorPosition(3)
	SetCursorFillMode(TOP_TO_BOTTOM)
	AddHeaderOption("Overview", OPTION_FLAG_DISABLED)
	AddHeaderOption("Drug Pool Physical Decay: " + DrugPool_pd.getValue(), OPTION_FLAG_DISABLED)
	AddHeaderOption("Drug Pool Mental Decay: " + DrugPool_md.getValue(), OPTION_FLAG_DISABLED)
	AddHeaderOption("Drug Pool Magical Decay: " + DrugPool_mkd.getValue(), OPTION_FLAG_DISABLED)
	AddHeaderOption("Addiction Stage Threshold: Fast - Medium - Slow", OPTION_FLAG_DISABLED)
	AddHeaderOption("1. Experimentation: 30 - 60 - 90", OPTION_FLAG_DISABLED)
	AddHeaderOption("2. Regular Use:        70 - 140 - 210", OPTION_FLAG_DISABLED)
	AddHeaderOption("3. Risky Use:          120 - 240 - 360", OPTION_FLAG_DISABLED)
	AddHeaderOption("4. Dependence:     180 - 360 - 540", OPTION_FLAG_DISABLED)
	AddHeaderOption("5. Addiction:          250 - 500 - 750", OPTION_FLAG_DISABLED)
	
elseif page == "Effects"

	visualsOID = AddToggleOption("Enable Visual Effects", visuals)
	If visuals == false		
		vp_lightOID = AddTextOption("Verminas Price Light", vp_light, OPTION_FLAG_DISABLED)
		mf_lightOID = AddTextOption("Mage Friend Light", mf_light, OPTION_FLAG_DISABLED)
		tam_lightOID = AddTextOption("The Arch Mage Light", tam_light, OPTION_FLAG_DISABLED)
	else
		vp_lightOID = AddTextOption("Verminas Price Light", vp_light, OPTION_FLAG_NONE)
		mf_lightOID = AddTextOption("Mage Friend Light", mf_light, OPTION_FLAG_NONE)
		tam_lightOID = AddTextOption("The Arch Mage Light", tam_light, OPTION_FLAG_NONE)
	endif
	AddEmptyOption()
	EffectsOID = AddToggleOption("Enable Active Withdrawal Effects", Effects)
	If Effects == false
		EffectIntervalOID = addslideroption("Active Withdrawal Effect Interval", EffectInterval, "{0.0}", OPTION_FLAG_DISABLED)
	else
		EffectIntervalOID = addslideroption("Active Withdrawal Effect Interval", EffectInterval, "{0.0}", OPTION_FLAG_NONE)
	endif
	AddEmptyOption()
	highriskOID = AddToggleOption("Enable High Risk", HighRisk)
	If HighRisk == false
		HRchanceOID = addslideroption("High Risk Chance", HRchance, "{0.0} %", OPTION_FLAG_DISABLED)
	else
		HRchanceOID = addslideroption("High Risk Chance", HRchance, "{0.0} %", OPTION_FLAG_NONE)
	endif
	ScumOID = AddToggleOption("Addicted are scum", Scum)
	CommentsOID = AddToggleOption("Humiliating Comments", Comments)
endif
endEvent
	
Event OnOptionSliderOpen(Int Option)
	if option == reduceOID
		SetSliderDialogStartValue(reduce)
		SetSliderDialogDefaultValue(10.0)
		SetSliderDialogRange(0.0, 100.0)
		SetSliderDialogInterval(0.5)
	elseif option == blackoutthresholdOID
		SetSliderDialogStartValue(blackoutthreshold)
		SetSliderDialogDefaultValue(5.0)
		SetSliderDialogRange(0.0, 10.0)
		SetSliderDialogInterval(1.0)
	elseif option == forcefeedchanceOID
		SetSliderDialogStartValue(forcefeedchance)
		SetSliderDialogDefaultValue(30.0)
		SetSliderDialogRange(1.0, 100.0)
		SetSliderDialogInterval(1.0)
	elseif option == EffectIntervalOID
		SetSliderDialogStartValue(EffectInterval)
		SetSliderDialogDefaultValue(3.0)
		SetSliderDialogRange(1.0, 10.0)
		SetSliderDialogInterval(0.5)
	elseif option == HRchanceOID
		SetSliderDialogStartValue(HRchance)
		SetSliderDialogDefaultValue(1.0)
		SetSliderDialogRange(1.0, 100.0)
		SetSliderDialogInterval(1.0)
	endif
endevent

Event OnOptionSliderAccept(Int Option, Float value)
	If Option == reduceOID
		reduce = value
		SetSliderOptionValue(reduceOID, reduce, "{0}")
	elseIf Option == blackoutthresholdOID
		blackoutthreshold = value
		SetSliderOptionValue(blackoutthresholdOID, blackoutthreshold, "{0}")
	elseIf Option == forcefeedchanceOID
		forcefeedchance = value
		SetSliderOptionValue(forcefeedchanceOID, forcefeedchance, "{0}")
	elseIf Option == EffectIntervalOID
		EffectInterval = value
		SetSliderOptionValue(EffectIntervalOID, EffectInterval, "{0.0}")
		EffectsScript.EffectsOff()
		EffectsScript.EffectsOn()
	elseIf Option == HRchanceOID
		HRchance = value
		SetSliderOptionValue(HRchanceOID, HRchance, "{0.0} %")
	endif
endevent

event OnOptionSelect(int option)
	if (option == speedOID)
		If speed == "Fast"
			speed = "Medium"
		Elseif speed == "Medium"
			speed = "Slow"    
		Else
			speed = "Fast"            
		Endif
	SetTextOptionValue(speedOID, speed)
	elseif (option == starterkitOID)
		Game.Getplayer().additem(Skooma, 10, true)
		Game.Getplayer().additem(RoseOfAzura, 10, true)
		Game.Getplayer().additem(BoethiasDeception , 10, true)
		Game.Getplayer().additem(ThiefsDelight , 10, true)
		Game.Getplayer().additem(ElendrsFlask , 10, true)
		Game.Getplayer().additem(TheContortionist , 10, true)
		Game.Getplayer().additem(MorgulsTouch , 10, true)
		Game.Getplayer().additem(ToughFlesh , 10, true)
		Game.Getplayer().additem(OcatosPallatine , 10, true)
		Game.Getplayer().additem(MagesFriend , 10, true)
		Game.Getplayer().additem(TheArchMage , 10, true)
		Game.Getplayer().additem(VerminasPrice , 10, true)
		Game.Getplayer().additem(LeafSkooma , 10, true)
		Game.Getplayer().additem(HerbTea , 10, true)
		Game.Getplayer().additem(PurifingSolution , 10, true)
		Game.Getplayer().additem(DDSkooma , 10, true)
		Game.Getplayer().additem(TheSecondBrain , 10, true)
		Game.Getplayer().additem(SLSW_Recipe_Skooma, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_BoethiasDeception, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_ThiefsDelight, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_TheSecondBrain, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_ElendirsFlask, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_TheContortionist, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_MorgulsTouch, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_ToughFlesh, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_OcatosPallatine, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_MagesFriend, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_TheArchMage, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_VerminasPrice, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_LeafSkooma, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_PurifyingSolution, 1, true)
		Game.Getplayer().additem(SLSW_Recipe_DDSkooma, 1, true)
		SetTextOptionValue(starterkitOID, starterkit)
	elseIf (option == blackoutOID)
		blackout = !blackout
		SetToggleOptionValue(blackoutOID, blackout)
		if blackout == true
			SetOptionFlags(blackoutthresholdOID, OPTION_FLAG_NONE)
		else
			SetOptionFlags(blackoutthresholdOID, OPTION_FLAG_DISABLED)
		endif
	elseIf (option == forcefeedOID)
		forcefeed = !forcefeed
		SetToggleOptionValue(forcefeedOID, forcefeed)
		if forcefeed == true
			SetOptionFlags(forcefeedchanceOID, OPTION_FLAG_NONE)
		else
			SetOptionFlags(forcefeedchanceOID, OPTION_FLAG_DISABLED)
		endif
	elseif (option == resetOID)
		DrugPool_pd.setValue(0)
		DrugPool_md.setValue(0)
		DrugPool_mkd.setValue(0)
		Game.GetPlayer().removeSpell(pd5)
		Game.GetPlayer().removeSpell(pd4)
		Game.GetPlayer().removeSpell(pd3)
		Game.GetPlayer().removeSpell(pd2)
		Game.GetPlayer().removeSpell(pd1)
		Game.GetPlayer().removeSpell(md5)
		Game.GetPlayer().removeSpell(md4)
		Game.GetPlayer().removeSpell(md3)
		Game.GetPlayer().removeSpell(md2)
		Game.GetPlayer().removeSpell(md1)
		Game.GetPlayer().removeSpell(mkd5)
		Game.GetPlayer().removeSpell(mkd4)
		Game.GetPlayer().removeSpell(mkd3)
		Game.GetPlayer().removeSpell(mkd2)
		Game.GetPlayer().removeSpell(mkd1)
		Debug.Notification("Skooma Whore addiction stages have been resetted")
		SetTextOptionValue(resetOID, reset)
	elseif (option == vp_lightOID)
		if vp_light == "Normal"
			vp_light = "Light"
		elseif vp_light == "Light"
			vp_light = "Off"
		else
			vp_light = "Normal"
		endif
		SetTextOptionValue(vp_lightOID, vp_light)
	elseif (option == mf_lightOID)
		if mf_light == "Normal"
			mf_light = "Light"
		elseif mf_light == "Light"
			mf_light = "Off"
		else
			mf_light = "Normal"
		endif
		SetTextOptionValue(mf_lightOID, mf_light)
	elseif (option == tam_lightOID)
		if tam_light == "Normal"
			tam_light = "Light"
		elseif tam_light == "Light"
			tam_light = "Off"
		else
			tam_light = "Normal"
		endif
		SetTextOptionValue(tam_lightOID, tam_light)
	elseIf (option == EffectsOID)
		Effects = !Effects
		SetToggleOptionValue(EffectsOID, Effects)
		If Effects == True
			SetOptionFlags(EffectIntervalOID, OPTION_FLAG_NONE)
			EffectsScript.EffectsOn()
		else
			SetOptionFlags(EffectIntervalOID, OPTION_FLAG_DISABLED)
			EffectsScript.EffectsOff()
		endif
	elseIf (option == HighRiskOID)
		HighRisk = !HighRisk
		SetToggleOptionValue(HighRiskOID, HighRisk)
		If HighRisk == True
			SetOptionFlags(HRchanceOID, OPTION_FLAG_NONE)
		else
			SetOptionFlags(HRchanceOID, OPTION_FLAG_DISABLED)
		endif
	elseIf (option == scumOID)
		scum = !scum
		SetToggleOptionValue(scumOID, scum)
	elseIf (option == commentsOID)
		comments = !comments
		SetToggleOptionValue(commentsOID, comments)
		If comments == True
			SLSW_comment.setValue(1)
		else
			SLSW_comment.setValue(0)
		endif
	elseIf (option == visualsOID)
		visuals = !visuals
		SetToggleOptionValue(visualsOID, visuals)
		If visuals == false
			SetOptionFlags(vp_lightOID, OPTION_FLAG_DISABLED)
			SetOptionFlags(mf_lightOID, OPTION_FLAG_DISABLED)
			SetOptionFlags(tam_lightOID, OPTION_FLAG_DISABLED)
		else
			SetOptionFlags(vp_lightOID, OPTION_FLAG_NONE)
			SetOptionFlags(mf_lightOID, OPTION_FLAG_NONE)
			SetOptionFlags(tam_lightOID, OPTION_FLAG_NONE)
		endif
	endIf
endEvent

event OnOptionHighlight(int option)
	if (option == speedOID)
		SetInfoText("How quick the player increases his addiction stage. \nDefault: Medium")
	elseif (option == reduceOID)
		SetInfoText("The drug pool is reduced by this value every 24 hours. \nRecommended Values: Fast = 10, Medium = 5, Slow = 3 \nDefault: 10.0")
	elseif (option == resetOID)
		SetInfoText("Resets the Drug Pool to zero and removes all addiction stages. Does not affect still running effects from Skooma. \nClose all menues after clicking this option!")
	elseif (option == brothelOID)
		SetInfoText("Reset the brothel quest and removes all clients. \nClose all menues after clicking this option!")
	elseif (option == blackoutOID)
		SetInfoText("Toggles if the player can blackout after taking to much drugs within one hour. \n10% chance per drug dose taken that exceeds the Blackout Threshold.")
	elseif (option == forcefeedOID)
		SetInfoText("Toggles if the player is forced to take one random drug after being raped.")
	elseif (option == EffectsOID)
		SetInfoText("Enables effects like tripping or automatically drinking a drug when heavily addicted.")
	elseif (option == EffectintervalOID)
		SetInfoText("Sets how often effects occur in IN-GAME hours.")
	elseif (option == HighRiskOID)
		SetInfoText("Enables the chance, when on Decay-Phase 0 or 1, of a drug having a heavily increased drug-strenght, catapulting you directly to Decay-Phase 2 or 3. \n This simulates becoming addicted on the first try.")
	elseif (option == scumOID)
		SetInfoText("When true, the player is despised and treated as scum relative to the decay stage.")
	elseif (option == commentsOID)
		SetInfoText("When true, NPC will comment you in a humiliating way, if you are on addiction stage 4 or higher.")
	elseif (option == visualsOID)
		SetInfoText("Toggles all visual effects from drugs on or off.")
	endIf
endEvent

event OnOptionDefault(int option)
	if (option == speedOID)
		speed = "Medium"
		SetTextOptionValue(speedOID, speed)
	elseif (option == blackoutOID)
		blackout = true
		SetToggleOptionValue(blackoutOID, blackout)
	elseif (option == EffectsOID)
		Effects = true
		SetToggleOptionValue(EffectsOID, Effects)
	elseif (option == forcefeedOID)
		forcefeed = true
		SetToggleOptionValue(forcefeedOID, forcefeed)
	elseif (option == vp_lightOID)
		vp_light = "Normal"
		SetTextOptionValue(vp_lightOID, vp_light)
	elseif (option == mf_lightOID)
		mf_light = "Normal"
		SetTextOptionValue(mf_lightOID, mf_light)
	elseif (option == tam_lightOID)
		tam_light = "Normal"
		SetTextOptionValue(tam_lightOID, tam_light)
	elseif (option == HighRiskOID)
		HighRisk = true
		SetTextOptionValue(HighRiskOID, HighRisk)
	elseif (option == scumOID)
		scum = true
		SetTextOptionValue(scumOID, scum)
	elseif (option == commentsOID)
		comments = true
		SetTextOptionValue(commentsOID, comments)
	elseif (option == visualsOID)
		visuals = true
		SetTextOptionValue(visualsOID, visuals)
	endIf
endEvent
