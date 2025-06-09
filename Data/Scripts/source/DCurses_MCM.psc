;THIS SCRIPT IS AUTO GENERATED
Scriptname DCurses_MCM extends SKI_ConfigBase

function UpdateSKSE() global Native
bool function CheckSTNG() global Native
bool function CheckLM() global Native

Bool Property ModSuspended = False Auto Hidden

Function StartTimer()
	Debug.trace("DCurses Timer Started")
	UnregisterForUpdate()
	RegisterForUpdate(1)
	RegisterForModEvent("HookAnimationStart", "OnSexStart")
	RegisterForModEvent("HookAnimationEnd", "OnSexEnd")
	RegisterForModEvent("dhlp-Suspend", "OnDhlpSuspend")
	RegisterForModEvent("dhlp-Resume", "OnDhlpResume")
EndFunction

Event OnUpdate()
	DCursesLib.OnUpdate()
EndEvent

Event OnSexEnd(int tid, bool HasPlayer)
	If HasPlayer
		SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
		sslThreadController thread = sexlab.GetController(tid)
		Actor[] positions = thread.positions
		DCursesLib.SexEnded(positions)
	EndIf
EndEvent

Event OnSexStart(int tid, bool HasPlayer)
	If HasPlayer
		SexLabFramework sexlab = Game.GetFormFromFile(0x0d62, "SexLab.esm") as SexLabFramework
		sslThreadController thread = sexlab.GetController(tid)
		Actor[] positions = thread.positions
		DCursesLib.SexStarted(positions)
	EndIf
EndEvent

;dhlp event handlers
Event OnDhlpSuspend( string eventName, string strArg, float numArg, Form sender )
    ModSuspended = True
EndEvent

Event OnDhlpResume( string eventName, string strArg, float numArg, Form sender )
    ModSuspended = False
EndEvent


Int Property minGoldRequired = 20 Auto
Int minGoldRequiredOID
Int Property eventScalingMod = 15 Auto
Int eventScalingModOID
Int Property minRestraints = 1 Auto
Int minRestraintsOID
Int Property maxRestraints = 3 Auto
Int maxRestraintsOID
Int Property bossAditionalRestraints = 2 Auto
Int bossAditionalRestraintsOID
Int Property restraintCap = 7 Auto
Int restraintCapOID
Int Property minArousal = 10 Auto
Int minArousalOID
Int Property beltWeight = 40 Auto
Int beltWeightOID
Int Property braWeight = 30 Auto
Int braWeightOID
Int Property plugsWeight = 50 Auto
Int plugsWeightOID
Int Property lockingPlugsWeight = 30 Auto
Int lockingPlugsWeightOID
Int Property inflatablePlugsWeight = 15 Auto
Int inflatablePlugsWeightOID
Int Property nipplePiercingsWeight = 50 Auto
Int nipplePiercingsWeightOID
Int Property vaginalPiercingsWeight = 50 Auto
Int vaginalPiercingsWeightOID
Int Property corsetWeight = 40 Auto
Int corsetWeightOID
Int Property beltedCorsetsWeight = 30 Auto
Int beltedCorsetsWeightOID
Int Property slaveHarnessWeight = 50 Auto
Int slaveHarnessWeightOID
Int Property chastityHarnessWeight = 40 Auto
Int chastityHarnessWeightOID
Int Property armbinderWeight = 30 Auto
Int armbinderWeightOID
Int Property elbowbinderWeight = 20 Auto
Int elbowbinderWeightOID
Int Property yokeWeight = 10 Auto
Int yokeWeightOID
Int Property shacklesWeight = 20 Auto
Int shacklesWeightOID
Int Property straitjacketWeight = 30 Auto
Int straitjacketWeightOID
Int Property straitjacketLegbinderWeight = 15 Auto
Int straitjacketLegbinderWeightOID
Int Property petSuitWeight = 10 Auto
Int petSuitWeightOID
Int Property collarWeight = 60 Auto
Int collarWeightOID
Int Property armCuffsWeight = 60 Auto
Int armCuffsWeightOID
Int Property legCuffsWeight = 60 Auto
Int legCuffsWeightOID
Int Property gagWeight = 35 Auto
Int gagWeightOID
Int Property ringGagWeight = 45 Auto
Int ringGagWeightOID
Int Property largeGagWeight = 30 Auto
Int largeGagWeightOID
Int Property largeRingGagWeight = 30 Auto
Int largeRingGagWeightOID
Int Property blindfoldWeight = 20 Auto
Int blindfoldWeightOID
Int Property hoodBothWeight = 20 Auto
Int hoodBothWeightOID
Int Property hoodGagWeight = 20 Auto
Int hoodGagWeightOID
Int Property hoodBlindWeight = 20 Auto
Int hoodBlindWeightOID
Int Property hoodNoneWeight = 20 Auto
Int hoodNoneWeightOID
Int Property catsuitWeight = 30 Auto
Int catsuitWeightOID
Int Property hobbleSkirtWeight = 20 Auto
Int hobbleSkirtWeightOID
Int Property hobbleSkirtDifficulty = 50 Auto
Int hobbleSkirtDifficultyOID
Int Property bootsWeight = 30 Auto
Int bootsWeightOID
Int Property glovesWeight = 30 Auto
Int glovesWeightOID
Int Property mittensWeight = 0 Auto
Int mittensWeightOID
Int Property minKeysLooted = 1 Auto
Int minKeysLootedOID
Int Property maxKeysLooted = 1 Auto
Int maxKeysLootedOID
Int Property maxHeldKeys = 3 Auto
Int maxHeldKeysOID
Int Property restraintsKeyWeight = 80 Auto
Int restraintsKeyWeightOID
Int Property chastityKeyWeight = 50 Auto
Int chastityKeyWeightOID
Int Property piercingToolWeight = 20 Auto
Int piercingToolWeightOID
Int Property eventStandardWeight = 100 Auto
Int eventStandardWeightOID
Int Property eventStandardBossReduction = 20 Auto
Int eventStandardBossReductionOID
Int Property eventOppressiveWeight = 15 Auto
Int eventOppressiveWeightOID
Int Property eventContraptionWeight = 25 Auto
Int eventContraptionWeightOID
Int Property eventContDeviceOverride = 0 Auto
Int eventContDeviceOverrideOID
Int Property eventTattooWeight = 15 Auto
Int eventTattooWeightOID
Int Property eventTattooMin = 1 Auto
Int eventTattooMinOID
Int Property eventTattooMax = 3 Auto
Int eventTattooMaxOID
Int Property eventTattooCap = 8 Auto
Int eventTattooCapOID
Int Property eventLewdMarkWeight = 10 Auto
Int eventLewdMarkWeightOID
Int Property eventSimpleSlaveryWeight = 0 Auto
Int eventSimpleSlaveryWeightOID
Int Property eventSSMinRestraints = 6 Auto
Int eventSSMinRestraintsOID
Int Property LMAllureWeight = 10 Auto
Int LMAllureWeightOID
Int Property LMAllureMod = 5 Auto
Int LMAllureModOID
Int Property LMAllureSex = 25 Auto
Int LMAllureSexOID
Int Property LMHeatWeight = 10 Auto
Int LMHeatWeightOID
Int Property LMHeatMod = 30 Auto
Int LMHeatModOID
Int Property LMHeatContainerCount = 50 Auto
Int LMHeatContainerCountOID
Int Property LMBrandingWeight = 10 Auto
Int LMBrandingWeightOID
Int Property LMBrndingTotal = 12 Auto
Int LMBrndingTotalOID
Int Property LMBondageWeight = 5 Auto
Int LMBondageWeightOID
Int Property LMBondageDeviceCount = 8 Auto
Int LMBondageDeviceCountOID
Int Property LMNudityWeight = 15 Auto
Int LMNudityWeightOID
Int Property LMNudityTalkTimes = 35 Auto
Int LMNudityTalkTimesOID
Int Property oppSummonerCollarWeight = 20 Auto
Int oppSummonerCollarWeightOID
Int Property oppSummonerSexCount = 15 Auto
Int oppSummonerSexCountOID
Int Property oppSMinSummonArousal = 90 Auto
Int oppSMinSummonArousalOID
Int Property oppDwarvenCuirassWeight = 15 Auto
Int oppDwarvenCuirassWeightOID
Int Property oppDwarvenValueNeeded = 200 Auto
Int oppDwarvenValueNeededOID
Int Property oppDwarvenArousal = 25 Auto
Int oppDwarvenArousalOID
Int Property oppLivingLatexWeight = 20 Auto
Int oppLivingLatexWeightOID
Int Property oppLivingLatexStartTime = 15 Auto
Int oppLivingLatexStartTimeOID
Int Property consSexWeight = 15 Auto
Int consSexWeightOID
Int Property consFineWeight = 10 Auto
Int consFineWeightOID
Int Property consFineAmount = 100 Auto
Int consFineAmountOID
Int Property consRandomBondageWeight = 10 Auto
Int consRandomBondageWeightOID
Int Property consMercyWeight = 5 Auto
Int consMercyWeightOID
Int Property sexCooldown = 30 Auto
Int sexCooldownOID
Int Property sexChance = 50 Auto
Int sexChanceOID
Int Property sexChanceCreature = 30 Auto
Int sexChanceCreatureOID
Int Property sexBaseArousal = 90 Auto
Int sexBaseArousalOID
Int Property sexArousalNightModifier = 5 Auto
Int sexArousalNightModifierOID
Int Property sexArousalNudeModifier = 15 Auto
Int sexArousalNudeModifierOID
Int Property sexArousalCollarModifier = 5 Auto
Int sexArousalCollarModifierOID
Int Property sexArousalHeavyModifier = 10 Auto
Int sexArousalHeavyModifierOID
Int Property sexArousalBlindModifier = 5 Auto
Int sexArousalBlindModifierOID
Int Property sexArousalBootsModifier = 0 Auto
Int sexArousalBootsModifierOID
Int Property sexArousalHobbleModifier = 0 Auto
Int sexArousalHobbleModifierOID
Int Property sexArousalVisibleModifier = 5 Auto
Int sexArousalVisibleModifierOID
Int Property sexArousalCreatureModifier = 0 Auto
Int sexArousalCreatureModifierOID
Int Property sexArousalFollowerModifier = 10 Auto
Int sexArousalFollowerModifierOID
Int Property sexArousalSpouseModifier = 20 Auto
Int sexArousalSpouseModifierOID
Int Property sexArousalSummonModifier = 0 Auto
Int sexArousalSummonModifierOID
Int Property sexSearchInterval = 5 Auto
Int sexSearchIntervalOID
Int Property sexRequiredPlayerArousal = 0 Auto
Int sexRequiredPlayerArousalOID
Int Property sexRequiredPlayerTattoos = 0 Auto
Int sexRequiredPlayerTattoosOID
Int Property sexChanceFollower = -1 Auto
Int sexChanceFollowerOID
Int Property sexChanceSpouse = -1 Auto
Int sexChanceSpouseOID
Int Property sexChanceSummon = -1 Auto
Int sexChanceSummonOID
Float Property baseChance = 6.5 Auto
Int baseChanceOID
Float Property containerModifier = 1.0 Auto
Int containerModifierOID
Float Property bossContainerModifier = 2.0 Auto
Int bossContainerModifierOID
Float Property deadBodyModifier = 1.3 Auto
Int deadBodyModifierOID
Float Property pickpocketModifier = 1.3 Auto
Int pickpocketModifierOID
Float Property doorModifier = 1.0 Auto
Int doorModifierOID
Float Property lockedModifier = 2.0 Auto
Int lockedModifierOID
Float Property lockDifficultyModifier = 1.3 Auto
Int lockDifficultyModifierOID
Float Property arousalModifier = 1.4 Auto
Int arousalModifierOID
Float Property keyLossChance = 80.0 Auto
Int keyLossChanceOID
Float Property keyChance = 7.0 Auto
Int keyChanceOID
Float Property keyBonus = 1.0 Auto
Int keyBonusOID
Float Property keyPickpocketBonus = 2.0 Auto
Int keyPickpocketBonusOID
Float Property magicKeyChance = 10.0 Auto
Int magicKeyChanceOID
Float Property eventContraptionTime = 4.0 Auto
Int eventContraptionTimeOID
Float Property LMBrandingChance = 1.5 Auto
Int LMBrandingChanceOID
Float Property LMBondageChance = 5.0 Auto
Int LMBondageChanceOID
Float Property oppSummonChance = 1.5 Auto
Int oppSummonChanceOID
Float Property oppLivingLatexMore = 0.0 Auto
Int oppLivingLatexMoreOID
Float Property playerHomeModifier = 0.0 Auto
Int playerHomeModifierOID
Float Property cityModifier = 0.0 Auto
Int cityModifierOID
Float Property townModifier = 0.0 Auto
Int townModifierOID
Float Property banditModifier = 1.1 Auto
Int banditModifierOID
Float Property draugrModifier = 1.2 Auto
Int draugrModifierOID
Float Property lockedLocationBypass = 0.6 Auto
Int lockedLocationBypassOID
Float Property theftLocationBypass = 1.1 Auto
Int theftLocationBypassOID
Float Property dwarvenModifier = 1.2 Auto
Int dwarvenModifierOID
Float Property falmerModifier = 1.3 Auto
Int falmerModifierOID
Float Property forswornModifier = 1.1 Auto
Int forswornModifierOID
Float Property vampireModifier = 1.5 Auto
Int vampireModifierOID
Float Property warlockModifier = 1.5 Auto
Int warlockModifierOID
Float Property dragonLairModifier = 2.0 Auto
Int dragonLairModifierOID
Float Property apocryphaModifier = 2.0 Auto
Int apocryphaModifierOID
Float Property wildernessModifier = 0.9 Auto
Int wildernessModifierOID
Float Property rDeviceBaseChance = 1.5 Auto
Int rDeviceBaseChanceOID
Float Property tatSolventChance = 0.5 Auto
Int tatSolventChanceOID
Float Property consTriggerNude = 15.0 Auto
Int consTriggerNudeOID
Float Property consTriggerRestrained = 50.0 Auto
Int consTriggerRestrainedOID
Float Property consTriggerSex = 10.0 Auto
Int consTriggerSexOID
Float Property sexArousalTattooModifier = 1.0 Auto
Int sexArousalTattooModifierOID
Float Property sexSearchRadius = 2000.0 Auto
Int sexSearchRadiusOID
Bool Property onlyLockedDoors = true Auto
Int onlyLockedDoorsOID
Bool Property eventScaling = true Auto
Int eventScalingOID
Bool Property bossOnlyHeavy = true Auto
Int bossOnlyHeavyOID
Bool Property stripPlayerOnEvent = true Auto
Int stripPlayerOnEventOID
Bool Property beltPlugs = true Auto
Int beltPlugsOID
Bool Property noBeltPiercing = false Auto
Int noBeltPiercingOID
Bool Property plugsDontCount = true Auto
Int plugsDontCountOID
Bool Property onlyUseUnforgivingDevices = false Auto
Int onlyUseUnforgivingDevicesOID
Bool Property allowLegShackles = false Auto
Int allowLegShacklesOID
Bool Property keyForgiveness = true Auto
Int keyForgivenessOID
Bool Property preferRelevantKeys = true Auto
Int preferRelevantKeysOID
Bool Property vanishingKeys = true Auto
Int vanishingKeysOID
Bool Property eventContDevices = true Auto
Int eventContDevicesOID
Bool Property eventContAllDevices = false Auto
Int eventContAllDevicesOID
Bool Property LMBrandingPunish = true Auto
Int LMBrandingPunishOID
Bool Property LMNudityChestOnly = false Auto
Int LMNudityChestOnlyOID
Bool Property oppSCollarDrainsMagicka = true Auto
Int oppSCollarDrainsMagickaOID
Bool Property oppDwarvenHeavyRestraint = false Auto
Int oppDwarvenHeavyRestraintOID
Bool Property oppDwarvenRequireLoc = true Auto
Int oppDwarvenRequireLocOID
Bool Property oppLivingLatexHeavy = false Auto
Int oppLivingLatexHeavyOID
Bool Property oppLivingLatexRequireRem = true Auto
Int oppLivingLatexRequireRemOID
Bool Property oppLivingLatexOpen = false Auto
Int oppLivingLatexOpenOID
Bool Property useLocationModifiers = true Auto
Int useLocationModifiersOID
Bool Property enableQuestInteractions = true Auto
Int enableQuestInteractionsOID
Bool Property enableQISaarthal = true Auto
Int enableQISaarthalOID
Bool Property enableQIDwemerMuseum = true Auto
Int enableQIDwemerMuseumOID
Bool Property enableQIMalkoran = true Auto
Int enableQIMalkoranOID
Bool Property enableQISanguine = true Auto
Int enableQISanguineOID
Bool Property noMessageBoxes = false Auto
Int noMessageBoxesOID
Bool Property bossChestUseModelPath = true Auto
Int bossChestUseModelPathOID
Bool Property dragonHoard = true Auto
Int dragonHoardOID
Bool Property bossExtraGold = true Auto
Int bossExtraGoldOID
Bool Property useThemes = false Auto
Int useThemesOID
Bool Property enableSlowStrip = false Auto
Int enableSlowStripOID
Bool Property resumeEvents = false Auto
Int resumeEventsOID
Bool Property setAllDefaultSettings = false Auto
Int setAllDefaultSettingsOID
Bool Property consAllowFollowers = false Auto
Int consAllowFollowersOID
Bool Property consAllowCreatures = false Auto
Int consAllowCreaturesOID
Bool Property consUseRelationships = true Auto
Int consUseRelationshipsOID
Bool Property consRelationBondage = false Auto
Int consRelationBondageOID
Bool Property consFallthrough = false Auto
Int consFallthroughOID
Bool Property consRandomHeavyBondage = false Auto
Int consRandomHeavyBondageOID
Bool Property consBondageIgnoreMax = false Auto
Int consBondageIgnoreMaxOID
Bool Property sexEnabled = false Auto
Int sexEnabledOID
Bool Property sexAggressiveAnims = false Auto
Int sexAggressiveAnimsOID
Bool Property sexRandomEnabled = false Auto
Int sexRandomEnabledOID
Bool Property sexAllowMale = true Auto
Int sexAllowMaleOID
Bool Property sexAllowFemale = true Auto
Int sexAllowFemaleOID
Bool Property sexAllowFuta = true Auto
Int sexAllowFutaOID
Bool Property sexAllowCreature = false Auto
Int sexAllowCreatureOID
Bool Property sexAllowFarmAnimals = false Auto
Int sexAllowFarmAnimalsOID
Bool Property sexRequireAll = false Auto
Int sexRequireAllOID
Bool Property sexRequireBindings = true Auto
Int sexRequireBindingsOID
Bool Property sexRequireCollar = false Auto
Int sexRequireCollarOID
Bool Property sexRequireHeavy = false Auto
Int sexRequireHeavyOID
Bool Property sexRequireNude = true Auto
Int sexRequireNudeOID
Bool Property sexAlwaysAllowFollowers = true Auto
Int sexAlwaysAllowFollowersOID
Bool Property sexAlwaysAllowSpouse = true Auto
Int sexAlwaysAllowSpouseOID
Bool Property sexAlwaysAllowSummons = false Auto
Int sexAlwaysAllowSummonsOID
Int Property LMAllureColor = 0xcf11c5 Auto
Int LMAllureColorOID
Int Property LMHeatColor = 0xe3143a Auto
Int LMHeatColorOID
Int Property LMBrandingColor = 0x220022 Auto
Int LMBrandingColorOID
Int Property LMBondageColor = 0x7908cf Auto
Int LMBondageColorOID
Int Property LMNudityColor = 0xd676cb Auto
Int LMNudityColorOID
String Property LMNudityAditionalForms = "" Auto
Int LMNudityAditionalFormsOID

Function Initialize()
	Pages = new String[11]
	Pages[0] = "$DCURSES_PAGE_Main"
	Pages[1] = "$DCURSES_PAGE_Devices"
	Pages[2] = "$DCURSES_PAGE_Keys"
	Pages[3] = "$DCURSES_PAGE_Events"
	Pages[4] = "$DCURSES_PAGE_LewdMarks"
	Pages[5] = "$DCURSES_PAGE_OppressiveDevices"
	Pages[6] = "$DCURSES_PAGE_Locations"
	Pages[7] = "$DCURSES_PAGE_QuestInteractions"
	Pages[8] = "$DCURSES_PAGE_Misc"
	Pages[9] = "$DCURSES_PAGE_Consequences"
	Pages[10] = "$DCURSES_PAGE_Sex"
EndFunction

Event OnConfigInit()
	StartTimer()
	Initialize()
EndEvent

Event OnConfigOpen()
	StartTimer()
	Initialize()
EndEvent


Event OnConfigClose()
	UpdateSKSE()
EndEvent


Event OnPageReset(string page)
	int flag_SlaveTats = 1
	If CheckSTNG()
		flag_SlaveTats = 0
	EndIf
	int flag_LewdMarks = 1
	If CheckLM() && CheckSTNG()
		flag_LewdMarks = 0
	EndIf
	int flag_RapeTats = 1
	If Game.GetModByName("RapeTattoos.esp") != 255 && CheckSTNG()
		flag_RapeTats = 0
	EndIf
	int flag_RT_LM = 1
	If Game.GetModByName("RapeTattoos.esp") != 255 && CheckSTNG() && CheckLM()
		flag_RT_LM = 0
	EndIf
	int flag_SimpleSlavery = 1
	If Game.GetModByName("SimpleSlavery.esp") != 255
		flag_SimpleSlavery = 0
	EndIf
	int flag_UnforgivingDevices = 1
	If Game.GetModByName("UnforgivingDevices.esp") != 255
		flag_UnforgivingDevices = 0
	EndIf
	int flag_SSEnabled = 1
	If eventSimpleSlaveryWeight > 0 && Game.GetModByName("SimpleSlavery.esp") != 255
		flag_SSEnabled = 0
	EndIf
	int flag_SGO = 1
	If Game.GetModByName("Sgo4IF.esp") != 255
		flag_SGO = 0
	EndIf
	SetCursorFillMode(TOP_TO_BOTTOM)
	If page == "" || page == "$DCURSES_PAGE_Main"
		AddHeaderOption("$DCURSES_HEADER_Chances")
		baseChanceOID = AddSliderOption("$DCURSES_baseChance", baseChance, "{1}%", 0)
		containerModifierOID = AddSliderOption("$DCURSES_containerModifier", containerModifier, "{1}x", 0)
		bossContainerModifierOID = AddSliderOption("$DCURSES_bossContainerModifier", bossContainerModifier, "{1}x", 0)
		deadBodyModifierOID = AddSliderOption("$DCURSES_deadBodyModifier", deadBodyModifier, "{1}x", 0)
		pickpocketModifierOID = AddSliderOption("$DCURSES_pickpocketModifier", pickpocketModifier, "{1}x", 0)
		doorModifierOID = AddSliderOption("$DCURSES_doorModifier", doorModifier, "{1}x", 0)
		onlyLockedDoorsOID = AddToggleOption("$DCURSES_onlyLockedDoors", onlyLockedDoors, 0)
		lockedModifierOID = AddSliderOption("$DCURSES_lockedModifier", lockedModifier, "{1}x", 0)
		lockDifficultyModifierOID = AddSliderOption("$DCURSES_lockDifficultyModifier", lockDifficultyModifier, "{1}", 0)
		minGoldRequiredOID = AddSliderOption("$DCURSES_minGoldRequired", minGoldRequired, "{0}", 0)
		eventScalingOID = AddToggleOption("$DCURSES_eventScaling", eventScaling, 0)
		eventScalingModOID = AddSliderOption("$DCURSES_eventScalingMod", eventScalingMod, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_Parameters")
		minRestraintsOID = AddSliderOption("$DCURSES_minRestraints", minRestraints, "{0}", 0)
		maxRestraintsOID = AddSliderOption("$DCURSES_maxRestraints", maxRestraints, "{0}", 0)
		bossAditionalRestraintsOID = AddSliderOption("$DCURSES_bossAditionalRestraints", bossAditionalRestraints, "{0}", 0)
		bossOnlyHeavyOID = AddToggleOption("$DCURSES_bossOnlyHeavy", bossOnlyHeavy, 0)
		restraintCapOID = AddSliderOption("$DCURSES_restraintCap", restraintCap, "{0}", 0)
		stripPlayerOnEventOID = AddToggleOption("$DCURSES_stripPlayerOnEvent", stripPlayerOnEvent, 0)
		AddHeaderOption("$DCURSES_HEADER_Arousal")
		arousalModifierOID = AddSliderOption("$DCURSES_arousalModifier", arousalModifier, "{1}", 0)
		minArousalOID = AddSliderOption("$DCURSES_minArousal", minArousal, "{0}", 0)
	Elseif page == "$DCURSES_PAGE_Devices"
		AddHeaderOption("$DCURSES_HEADER_Chastity")
		beltWeightOID = AddSliderOption("$DCURSES_beltWeight", beltWeight, "{0}", 0)
		beltPlugsOID = AddToggleOption("$DCURSES_beltPlugs", beltPlugs, 0)
		noBeltPiercingOID = AddToggleOption("$DCURSES_noBeltPiercing", noBeltPiercing, 0)
		braWeightOID = AddSliderOption("$DCURSES_braWeight", braWeight, "{0}", 0)
		plugsWeightOID = AddSliderOption("$DCURSES_plugsWeight", plugsWeight, "{0}", 0)
		lockingPlugsWeightOID = AddSliderOption("$DCURSES_lockingPlugsWeight", lockingPlugsWeight, "{0}", 0)
		inflatablePlugsWeightOID = AddSliderOption("$DCURSES_inflatablePlugsWeight", inflatablePlugsWeight, "{0}", 0)
		plugsDontCountOID = AddToggleOption("$DCURSES_plugsDontCount", plugsDontCount, 0)
		AddHeaderOption("$DCURSES_HEADER_Piercings")
		nipplePiercingsWeightOID = AddSliderOption("$DCURSES_nipplePiercingsWeight", nipplePiercingsWeight, "{0}", 0)
		vaginalPiercingsWeightOID = AddSliderOption("$DCURSES_vaginalPiercingsWeight", vaginalPiercingsWeight, "{0}", 0)
		AddHeaderOption("$DCURSES_HEADER_Corsets&Harnesses")
		corsetWeightOID = AddSliderOption("$DCURSES_corsetWeight", corsetWeight, "{0}", 0)
		beltedCorsetsWeightOID = AddSliderOption("$DCURSES_beltedCorsetsWeight", beltedCorsetsWeight, "{0}", 0)
		slaveHarnessWeightOID = AddSliderOption("$DCURSES_slaveHarnessWeight", slaveHarnessWeight, "{0}", 0)
		chastityHarnessWeightOID = AddSliderOption("$DCURSES_chastityHarnessWeight", chastityHarnessWeight, "{0}", 0)
		AddHeaderOption("$DCURSES_HEADER_HeavyBondage")
		armbinderWeightOID = AddSliderOption("$DCURSES_armbinderWeight", armbinderWeight, "{0}", 0)
		elbowbinderWeightOID = AddSliderOption("$DCURSES_elbowbinderWeight", elbowbinderWeight, "{0}", 0)
		yokeWeightOID = AddSliderOption("$DCURSES_yokeWeight", yokeWeight, "{0}", 0)
		shacklesWeightOID = AddSliderOption("$DCURSES_shacklesWeight", shacklesWeight, "{0}", 0)
		straitjacketWeightOID = AddSliderOption("$DCURSES_straitjacketWeight", straitjacketWeight, "{0}", 0)
		straitjacketLegbinderWeightOID = AddSliderOption("$DCURSES_straitjacketLegbinderWeight", straitjacketLegbinderWeight, "{0}", 0)
		petSuitWeightOID = AddSliderOption("$DCURSES_petSuitWeight", petSuitWeight, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_UnforgivingDevices")
		onlyUseUnforgivingDevicesOID = AddToggleOption("$DCURSES_onlyUseUnforgivingDevices", onlyUseUnforgivingDevices, flag_UnforgivingDevices)
		AddHeaderOption("$DCURSES_HEADER_Collars&Cuffs")
		collarWeightOID = AddSliderOption("$DCURSES_collarWeight", collarWeight, "{0}", 0)
		armCuffsWeightOID = AddSliderOption("$DCURSES_armCuffsWeight", armCuffsWeight, "{0}", 0)
		legCuffsWeightOID = AddSliderOption("$DCURSES_legCuffsWeight", legCuffsWeight, "{0}", 0)
		allowLegShacklesOID = AddToggleOption("$DCURSES_allowLegShackles", allowLegShackles, 0)
		AddHeaderOption("$DCURSES_HEADER_Gags&Blindfolds")
		gagWeightOID = AddSliderOption("$DCURSES_gagWeight", gagWeight, "{0}", 0)
		ringGagWeightOID = AddSliderOption("$DCURSES_ringGagWeight", ringGagWeight, "{0}", 0)
		largeGagWeightOID = AddSliderOption("$DCURSES_largeGagWeight", largeGagWeight, "{0}", 0)
		largeRingGagWeightOID = AddSliderOption("$DCURSES_largeRingGagWeight", largeRingGagWeight, "{0}", 0)
		blindfoldWeightOID = AddSliderOption("$DCURSES_blindfoldWeight", blindfoldWeight, "{0}", 0)
		hoodBothWeightOID = AddSliderOption("$DCURSES_hoodBothWeight", hoodBothWeight, "{0}", 0)
		hoodGagWeightOID = AddSliderOption("$DCURSES_hoodGagWeight", hoodGagWeight, "{0}", 0)
		hoodBlindWeightOID = AddSliderOption("$DCURSES_hoodBlindWeight", hoodBlindWeight, "{0}", 0)
		hoodNoneWeightOID = AddSliderOption("$DCURSES_hoodNoneWeight", hoodNoneWeight, "{0}", 0)
		AddHeaderOption("$DCURSES_HEADER_Body")
		catsuitWeightOID = AddSliderOption("$DCURSES_catsuitWeight", catsuitWeight, "{0}", 0)
		hobbleSkirtWeightOID = AddSliderOption("$DCURSES_hobbleSkirtWeight", hobbleSkirtWeight, "{0}", 0)
		hobbleSkirtDifficultyOID = AddSliderOption("$DCURSES_hobbleSkirtDifficulty", hobbleSkirtDifficulty, "{0}", 0)
		bootsWeightOID = AddSliderOption("$DCURSES_bootsWeight", bootsWeight, "{0}", 0)
		glovesWeightOID = AddSliderOption("$DCURSES_glovesWeight", glovesWeight, "{0}", 0)
		mittensWeightOID = AddSliderOption("$DCURSES_mittensWeight", mittensWeight, "{0}", 0)
	Elseif page == "$DCURSES_PAGE_Keys"
		keyLossChanceOID = AddSliderOption("$DCURSES_keyLossChance", keyLossChance, "{1}%", 0)
		keyChanceOID = AddSliderOption("$DCURSES_keyChance", keyChance, "{1}%", 0)
		minKeysLootedOID = AddSliderOption("$DCURSES_minKeysLooted", minKeysLooted, "{0}", 0)
		maxKeysLootedOID = AddSliderOption("$DCURSES_maxKeysLooted", maxKeysLooted, "{0}", 0)
		keyBonusOID = AddSliderOption("$DCURSES_keyBonus", keyBonus, "{1}%", 0)
		keyForgivenessOID = AddToggleOption("$DCURSES_keyForgiveness", keyForgiveness, 0)
		keyPickpocketBonusOID = AddSliderOption("$DCURSES_keyPickpocketBonus", keyPickpocketBonus, "{1}x", 0)
		maxHeldKeysOID = AddSliderOption("$DCURSES_maxHeldKeys", maxHeldKeys, "{0}", 0)
		SetCursorPosition(1)
		restraintsKeyWeightOID = AddSliderOption("$DCURSES_restraintsKeyWeight", restraintsKeyWeight, "{0}", 0)
		chastityKeyWeightOID = AddSliderOption("$DCURSES_chastityKeyWeight", chastityKeyWeight, "{0}", 0)
		piercingToolWeightOID = AddSliderOption("$DCURSES_piercingToolWeight", piercingToolWeight, "{0}", 0)
		AddEmptyOption()
		magicKeyChanceOID = AddSliderOption("$DCURSES_magicKeyChance", magicKeyChance, "{1}", 0)
		preferRelevantKeysOID = AddToggleOption("$DCURSES_preferRelevantKeys", preferRelevantKeys, 0)
		vanishingKeysOID = AddToggleOption("$DCURSES_vanishingKeys", vanishingKeys, 0)
	Elseif page == "$DCURSES_PAGE_Events"
		AddHeaderOption("$DCURSES_HEADER_BondageCurse")
		eventStandardWeightOID = AddSliderOption("$DCURSES_eventStandardWeight", eventStandardWeight, "{0}", 0)
		eventStandardBossReductionOID = AddSliderOption("$DCURSES_eventStandardBossReduction", eventStandardBossReduction, "{0}", 0)
		AddHeaderOption("$DCURSES_HEADER_OppresiveCurse")
		eventOppressiveWeightOID = AddSliderOption("$DCURSES_eventOppressiveWeight", eventOppressiveWeight, "{0}", 0)
		AddHeaderOption("$DCURSES_HEADER_ContraptionCurse")
		eventContraptionWeightOID = AddSliderOption("$DCURSES_eventContraptionWeight", eventContraptionWeight, "{0}", 0)
		eventContraptionTimeOID = AddSliderOption("$DCURSES_eventContraptionTime", eventContraptionTime, "{1}", 0)
		eventContDevicesOID = AddToggleOption("$DCURSES_eventContDevices", eventContDevices, 0)
		eventContAllDevicesOID = AddToggleOption("$DCURSES_eventContAllDevices", eventContAllDevices, 0)
		eventContDeviceOverrideOID = AddSliderOption("$DCURSES_eventContDeviceOverride", eventContDeviceOverride, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_TattooCurse")
		eventTattooWeightOID = AddSliderOption("$DCURSES_eventTattooWeight", eventTattooWeight, "{0}", flag_RapeTats)
		eventTattooMinOID = AddSliderOption("$DCURSES_eventTattooMin", eventTattooMin, "{0}", flag_RapeTats)
		eventTattooMaxOID = AddSliderOption("$DCURSES_eventTattooMax", eventTattooMax, "{0}", flag_RapeTats)
		eventTattooCapOID = AddSliderOption("$DCURSES_eventTattooCap", eventTattooCap, "{0}", flag_RapeTats)
		AddHeaderOption("$DCURSES_HEADER_MarkCurse")
		eventLewdMarkWeightOID = AddSliderOption("$DCURSES_eventLewdMarkWeight", eventLewdMarkWeight, "{0}", flag_LewdMarks)
		AddHeaderOption("$DCURSES_HEADER_SlaveryCurse")
		eventSimpleSlaveryWeightOID = AddSliderOption("$DCURSES_eventSimpleSlaveryWeight", eventSimpleSlaveryWeight, "{0}", flag_SimpleSlavery)
		eventSSMinRestraintsOID = AddSliderOption("$DCURSES_eventSSMinRestraints", eventSSMinRestraints, "{0}", flag_SSEnabled)
	Elseif page == "$DCURSES_PAGE_LewdMarks"
		AddHeaderOption("$DCURSES_HEADER_Allure")
		LMAllureWeightOID = AddSliderOption("$DCURSES_LMAllureWeight", LMAllureWeight, "{0}", flag_LewdMarks)
		LMAllureModOID = AddSliderOption("$DCURSES_LMAllureMod", LMAllureMod, "{0}", flag_LewdMarks)
		LMAllureSexOID = AddSliderOption("$DCURSES_LMAllureSex", LMAllureSex, "{0}", flag_LewdMarks)
		LMAllureColorOID = AddColorOption("$DCURSES_LMAllureColor", LMAllureColor, flag_LewdMarks)
		AddHeaderOption("$DCURSES_HEADER_Heat")
		LMHeatWeightOID = AddSliderOption("$DCURSES_LMHeatWeight", LMHeatWeight, "{0}", flag_LewdMarks)
		LMHeatModOID = AddSliderOption("$DCURSES_LMHeatMod", LMHeatMod, "{0}", flag_LewdMarks)
		LMHeatContainerCountOID = AddSliderOption("$DCURSES_LMHeatContainerCount", LMHeatContainerCount, "{0}", flag_LewdMarks)
		LMHeatColorOID = AddColorOption("$DCURSES_LMHeatColor", LMHeatColor, flag_LewdMarks)
		AddHeaderOption("$DCURSES_HEADER_Branding")
		LMBrandingWeightOID = AddSliderOption("$DCURSES_LMBrandingWeight", LMBrandingWeight, "{0}", flag_LewdMarks)
		LMBrandingChanceOID = AddSliderOption("$DCURSES_LMBrandingChance", LMBrandingChance, "{1}%", flag_RT_LM)
		LMBrndingTotalOID = AddSliderOption("$DCURSES_LMBrndingTotal", LMBrndingTotal, "{0}", flag_LewdMarks)
		LMBrandingPunishOID = AddToggleOption("$DCURSES_LMBrandingPunish", LMBrandingPunish, flag_LewdMarks)
		LMBrandingColorOID = AddColorOption("$DCURSES_LMBrandingColor", LMBrandingColor, flag_LewdMarks)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_Bondage")
		LMBondageWeightOID = AddSliderOption("$DCURSES_LMBondageWeight", LMBondageWeight, "{0}", flag_LewdMarks)
		LMBondageChanceOID = AddSliderOption("$DCURSES_LMBondageChance", LMBondageChance, "{1}%", flag_LewdMarks)
		LMBondageDeviceCountOID = AddSliderOption("$DCURSES_LMBondageDeviceCount", LMBondageDeviceCount, "{0}", flag_LewdMarks)
		LMBondageColorOID = AddColorOption("$DCURSES_LMBondageColor", LMBondageColor, flag_LewdMarks)
		AddHeaderOption("$DCURSES_HEADER_Nudity")
		int flag_LMStripBody = 1
		If LMNudityChestOnly && flag_LewdMarks == 0
			flag_LMStripBody = 0
		EndIf
		LMNudityWeightOID = AddSliderOption("$DCURSES_LMNudityWeight", LMNudityWeight, "{0}", flag_LewdMarks)
		LMNudityChestOnlyOID = AddToggleOption("$DCURSES_LMNudityChestOnly", LMNudityChestOnly, flag_LewdMarks)
		LMNudityAditionalFormsOID = AddInputOption("$DCURSES_LMNudityAditionalForms", LMNudityAditionalForms, flag_LMStripBody)
		LMNudityTalkTimesOID = AddSliderOption("$DCURSES_LMNudityTalkTimes", LMNudityTalkTimes, "{0}", flag_LewdMarks)
		LMNudityColorOID = AddColorOption("$DCURSES_LMNudityColor", LMNudityColor, flag_LewdMarks)
	Elseif page == "$DCURSES_PAGE_OppressiveDevices"
		AddHeaderOption("$DCURSES_HEADER_SummonerCollar")
		oppSummonerCollarWeightOID = AddSliderOption("$DCURSES_oppSummonerCollarWeight", oppSummonerCollarWeight, "{0}", 0)
		oppSummonerSexCountOID = AddSliderOption("$DCURSES_oppSummonerSexCount", oppSummonerSexCount, "{0}", 0)
		oppSCollarDrainsMagickaOID = AddToggleOption("$DCURSES_oppSCollarDrainsMagicka", oppSCollarDrainsMagicka, 0)
		oppSMinSummonArousalOID = AddSliderOption("$DCURSES_oppSMinSummonArousal", oppSMinSummonArousal, "{0}", 0)
		oppSummonChanceOID = AddSliderOption("$DCURSES_oppSummonChance", oppSummonChance, "{1}%", 0)
		AddHeaderOption("$DCURSES_HEADER_DwarvenCuirass")
		oppDwarvenCuirassWeightOID = AddSliderOption("$DCURSES_oppDwarvenCuirassWeight", oppDwarvenCuirassWeight, "{0}", 0)
		oppDwarvenValueNeededOID = AddSliderOption("$DCURSES_oppDwarvenValueNeeded", oppDwarvenValueNeeded, "{0}", 0)
		oppDwarvenHeavyRestraintOID = AddToggleOption("$DCURSES_oppDwarvenHeavyRestraint", oppDwarvenHeavyRestraint, 0)
		oppDwarvenRequireLocOID = AddToggleOption("$DCURSES_oppDwarvenRequireLoc", oppDwarvenRequireLoc, 0)
		oppDwarvenArousalOID = AddSliderOption("$DCURSES_oppDwarvenArousal", oppDwarvenArousal, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_LivingLatex")
		oppLivingLatexWeightOID = AddSliderOption("$DCURSES_oppLivingLatexWeight", oppLivingLatexWeight, "{0}", 0)
		oppLivingLatexStartTimeOID = AddSliderOption("$DCURSES_oppLivingLatexStartTime", oppLivingLatexStartTime, "{0}", 0)
		oppLivingLatexHeavyOID = AddToggleOption("$DCURSES_oppLivingLatexHeavy", oppLivingLatexHeavy, 0)
		oppLivingLatexMoreOID = AddSliderOption("$DCURSES_oppLivingLatexMore", oppLivingLatexMore, "{1}", 0)
		oppLivingLatexRequireRemOID = AddToggleOption("$DCURSES_oppLivingLatexRequireRem", oppLivingLatexRequireRem, 0)
		oppLivingLatexOpenOID = AddToggleOption("$DCURSES_oppLivingLatexOpen", oppLivingLatexOpen, 0)
	Elseif page == "$DCURSES_PAGE_Locations"
		useLocationModifiersOID = AddToggleOption("$DCURSES_useLocationModifiers", useLocationModifiers, 0)
		AddEmptyOption()
		AddEmptyOption()
		playerHomeModifierOID = AddSliderOption("$DCURSES_playerHomeModifier", playerHomeModifier, "{1}x", 0)
		cityModifierOID = AddSliderOption("$DCURSES_cityModifier", cityModifier, "{1}x", 0)
		townModifierOID = AddSliderOption("$DCURSES_townModifier", townModifier, "{1}x", 0)
		banditModifierOID = AddSliderOption("$DCURSES_banditModifier", banditModifier, "{1}x", 0)
		draugrModifierOID = AddSliderOption("$DCURSES_draugrModifier", draugrModifier, "{1}x", 0)
		SetCursorPosition(1)
		lockedLocationBypassOID = AddSliderOption("$DCURSES_lockedLocationBypass", lockedLocationBypass, "{1}x", 0)
		theftLocationBypassOID = AddSliderOption("$DCURSES_theftLocationBypass", theftLocationBypass, "{1}x", 0)
		AddEmptyOption()
		dwarvenModifierOID = AddSliderOption("$DCURSES_dwarvenModifier", dwarvenModifier, "{1}x", 0)
		falmerModifierOID = AddSliderOption("$DCURSES_falmerModifier", falmerModifier, "{1}x", 0)
		forswornModifierOID = AddSliderOption("$DCURSES_forswornModifier", forswornModifier, "{1}x", 0)
		vampireModifierOID = AddSliderOption("$DCURSES_vampireModifier", vampireModifier, "{1}x", 0)
		warlockModifierOID = AddSliderOption("$DCURSES_warlockModifier", warlockModifier, "{1}x", 0)
		dragonLairModifierOID = AddSliderOption("$DCURSES_dragonLairModifier", dragonLairModifier, "{1}x", 0)
		apocryphaModifierOID = AddSliderOption("$DCURSES_apocryphaModifier", apocryphaModifier, "{1}x", 0)
		wildernessModifierOID = AddSliderOption("$DCURSES_wildernessModifier", wildernessModifier, "{1}x", 0)
	Elseif page == "$DCURSES_PAGE_QuestInteractions"
		int flag_enable_qi = 1
		If enableQuestInteractions
			flag_enable_qi = 0
		EndIf
		enableQuestInteractionsOID = AddToggleOption("$DCURSES_enableQuestInteractions", enableQuestInteractions, 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_QuestToggles")
		enableQISaarthalOID = AddToggleOption("$DCURSES_enableQISaarthal", enableQISaarthal, 0)
		enableQIDwemerMuseumOID = AddToggleOption("$DCURSES_enableQIDwemerMuseum", enableQIDwemerMuseum, 0)
		enableQIMalkoranOID = AddToggleOption("$DCURSES_enableQIMalkoran", enableQIMalkoran, 0)
		enableQISanguineOID = AddToggleOption("$DCURSES_enableQISanguine", enableQISanguine, 0)
	Elseif page == "$DCURSES_PAGE_Misc"
		int flag_events_disabled = 1
		If ModSuspended
			flag_events_disabled = 0
		EndIf
		noMessageBoxesOID = AddToggleOption("$DCURSES_noMessageBoxes", noMessageBoxes, 0)
		bossChestUseModelPathOID = AddToggleOption("$DCURSES_bossChestUseModelPath", bossChestUseModelPath, 0)
		rDeviceBaseChanceOID = AddSliderOption("$DCURSES_rDeviceBaseChance", rDeviceBaseChance, "{1}%", 0)
		dragonHoardOID = AddToggleOption("$DCURSES_dragonHoard", dragonHoard, 0)
		bossExtraGoldOID = AddToggleOption("$DCURSES_bossExtraGold", bossExtraGold, 0)
		useThemesOID = AddToggleOption("$DCURSES_useThemes", useThemes, 0)
		SetCursorPosition(1)
		enableSlowStripOID = AddToggleOption("$DCURSES_enableSlowStrip", enableSlowStrip, 0)
		tatSolventChanceOID = AddSliderOption("$DCURSES_tatSolventChance", tatSolventChance, "{1}", 0)
		resumeEventsOID = AddToggleOption("$DCURSES_resumeEvents", resumeEvents, flag_events_disabled)
		setAllDefaultSettingsOID = AddToggleOption("$DCURSES_setAllDefaultSettings", setAllDefaultSettings, 0)
	Elseif page == "$DCURSES_PAGE_Consequences"
		AddHeaderOption("$DCURSES_HEADER_Triggers")
		consTriggerNudeOID = AddSliderOption("$DCURSES_consTriggerNude", consTriggerNude, "{1}%", 0)
		consTriggerRestrainedOID = AddSliderOption("$DCURSES_consTriggerRestrained", consTriggerRestrained, "{1}%", 0)
		consTriggerSexOID = AddSliderOption("$DCURSES_consTriggerSex", consTriggerSex, "{1}%", 0)
		AddEmptyOption()
		consAllowFollowersOID = AddToggleOption("$DCURSES_consAllowFollowers", consAllowFollowers, 0)
		consAllowCreaturesOID = AddToggleOption("$DCURSES_consAllowCreatures", consAllowCreatures, 0)
		AddEmptyOption()
		consUseRelationshipsOID = AddToggleOption("$DCURSES_consUseRelationships", consUseRelationships, 0)
		consRelationBondageOID = AddToggleOption("$DCURSES_consRelationBondage", consRelationBondage, 0)
		AddEmptyOption()
		consFallthroughOID = AddToggleOption("$DCURSES_consFallthrough", consFallthrough, 0)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_Results")
		consSexWeightOID = AddSliderOption("$DCURSES_consSexWeight", consSexWeight, "{0}", 0)
		AddEmptyOption()
		consFineWeightOID = AddSliderOption("$DCURSES_consFineWeight", consFineWeight, "{0}", 0)
		consFineAmountOID = AddSliderOption("$DCURSES_consFineAmount", consFineAmount, "{0}", 0)
		AddEmptyOption()
		consRandomBondageWeightOID = AddSliderOption("$DCURSES_consRandomBondageWeight", consRandomBondageWeight, "{0}", 0)
		consRandomHeavyBondageOID = AddToggleOption("$DCURSES_consRandomHeavyBondage", consRandomHeavyBondage, 0)
		consBondageIgnoreMaxOID = AddToggleOption("$DCURSES_consBondageIgnoreMax", consBondageIgnoreMax, 0)
		AddEmptyOption()
		consMercyWeightOID = AddSliderOption("$DCURSES_consMercyWeight", consMercyWeight, "{0}", 0)
	Elseif page == "$DCURSES_PAGE_Sex"
		int flag_enable_sex = 1
		If sexEnabled
			flag_enable_sex = 0
		EndIf
		int flag_enable_random_sex = 1
		If sexRandomEnabled
			flag_enable_random_sex = 0
		EndIf
		int flag_sex_slave_tats = 1
		If sexRandomEnabled && CheckSTNG()
			flag_sex_slave_tats = 0
		EndIf
		AddHeaderOption("$DCURSES_HEADER_General")
		sexEnabledOID = AddToggleOption("$DCURSES_sexEnabled", sexEnabled, 0)
		sexAggressiveAnimsOID = AddToggleOption("$DCURSES_sexAggressiveAnims", sexAggressiveAnims, flag_enable_sex)
		sexRandomEnabledOID = AddToggleOption("$DCURSES_sexRandomEnabled", sexRandomEnabled, 0)
		sexCooldownOID = AddSliderOption("$DCURSES_sexCooldown", sexCooldown, "{0}", flag_enable_random_sex)
		sexChanceOID = AddSliderOption("$DCURSES_sexChance", sexChance, "{0}%", flag_enable_random_sex)
		sexChanceCreatureOID = AddSliderOption("$DCURSES_sexChanceCreature", sexChanceCreature, "{0}%", flag_enable_random_sex)
		AddHeaderOption("$DCURSES_HEADER_Arousal")
		sexBaseArousalOID = AddSliderOption("$DCURSES_sexBaseArousal", sexBaseArousal, "{0}", flag_enable_random_sex)
		sexArousalNightModifierOID = AddSliderOption("$DCURSES_sexArousalNightModifier", sexArousalNightModifier, "-{0}", flag_enable_random_sex)
		sexArousalNudeModifierOID = AddSliderOption("$DCURSES_sexArousalNudeModifier", sexArousalNudeModifier, "-{0}", flag_enable_random_sex)
		sexArousalCollarModifierOID = AddSliderOption("$DCURSES_sexArousalCollarModifier", sexArousalCollarModifier, "-{0}", flag_enable_random_sex)
		sexArousalHeavyModifierOID = AddSliderOption("$DCURSES_sexArousalHeavyModifier", sexArousalHeavyModifier, "-{0}", flag_enable_random_sex)
		sexArousalBlindModifierOID = AddSliderOption("$DCURSES_sexArousalBlindModifier", sexArousalBlindModifier, "-{0}", flag_enable_random_sex)
		sexArousalBootsModifierOID = AddSliderOption("$DCURSES_sexArousalBootsModifier", sexArousalBootsModifier, "-{0}", flag_enable_random_sex)
		sexArousalHobbleModifierOID = AddSliderOption("$DCURSES_sexArousalHobbleModifier", sexArousalHobbleModifier, "-{0}", flag_enable_random_sex)
		sexArousalVisibleModifierOID = AddSliderOption("$DCURSES_sexArousalVisibleModifier", sexArousalVisibleModifier, "-{0}", flag_enable_random_sex)
		sexArousalTattooModifierOID = AddSliderOption("$DCURSES_sexArousalTattooModifier", sexArousalTattooModifier, "-{1}", flag_sex_slave_tats)
		sexArousalCreatureModifierOID = AddSliderOption("$DCURSES_sexArousalCreatureModifier", sexArousalCreatureModifier, "-{0}", flag_enable_random_sex)
		sexArousalFollowerModifierOID = AddSliderOption("$DCURSES_sexArousalFollowerModifier", sexArousalFollowerModifier, "-{0}", flag_enable_random_sex)
		sexArousalSpouseModifierOID = AddSliderOption("$DCURSES_sexArousalSpouseModifier", sexArousalSpouseModifier, "-{0}", flag_enable_random_sex)
		sexArousalSummonModifierOID = AddSliderOption("$DCURSES_sexArousalSummonModifier", sexArousalSummonModifier, "-{0}", flag_enable_random_sex)
		AddHeaderOption("$DCURSES_HEADER_Search")
		sexSearchRadiusOID = AddSliderOption("$DCURSES_sexSearchRadius", sexSearchRadius, "{0}", flag_enable_random_sex)
		sexSearchIntervalOID = AddSliderOption("$DCURSES_sexSearchInterval", sexSearchInterval, "{0}", flag_enable_random_sex)
		SetCursorPosition(1)
		AddHeaderOption("$DCURSES_HEADER_AllowedActors")
		sexAllowMaleOID = AddToggleOption("$DCURSES_sexAllowMale", sexAllowMale, flag_enable_sex)
		sexAllowFemaleOID = AddToggleOption("$DCURSES_sexAllowFemale", sexAllowFemale, flag_enable_sex)
		sexAllowFutaOID = AddToggleOption("$DCURSES_sexAllowFuta", sexAllowFuta, flag_enable_sex)
		sexAllowCreatureOID = AddToggleOption("$DCURSES_sexAllowCreature", sexAllowCreature, flag_enable_sex)
		sexAllowFarmAnimalsOID = AddToggleOption("$DCURSES_sexAllowFarmAnimals", sexAllowFarmAnimals, flag_enable_sex)
		AddHeaderOption("$DCURSES_HEADER_Requirements")
		sexRequireAllOID = AddToggleOption("$DCURSES_sexRequireAll", sexRequireAll, flag_enable_random_sex)
		sexRequireBindingsOID = AddToggleOption("$DCURSES_sexRequireBindings", sexRequireBindings, flag_enable_random_sex)
		sexRequireCollarOID = AddToggleOption("$DCURSES_sexRequireCollar", sexRequireCollar, flag_enable_random_sex)
		sexRequireHeavyOID = AddToggleOption("$DCURSES_sexRequireHeavy", sexRequireHeavy, flag_enable_random_sex)
		sexRequireNudeOID = AddToggleOption("$DCURSES_sexRequireNude", sexRequireNude, flag_enable_random_sex)
		sexRequiredPlayerArousalOID = AddSliderOption("$DCURSES_sexRequiredPlayerArousal", sexRequiredPlayerArousal, "{0}", flag_enable_random_sex)
		sexRequiredPlayerTattoosOID = AddSliderOption("$DCURSES_sexRequiredPlayerTattoos", sexRequiredPlayerTattoos, "{0}", flag_sex_slave_tats)
		AddHeaderOption("$DCURSES_HEADER_RequirementExceptions")
		sexAlwaysAllowFollowersOID = AddToggleOption("$DCURSES_sexAlwaysAllowFollowers", sexAlwaysAllowFollowers, flag_enable_random_sex)
		sexAlwaysAllowSpouseOID = AddToggleOption("$DCURSES_sexAlwaysAllowSpouse", sexAlwaysAllowSpouse, flag_enable_random_sex)
		sexAlwaysAllowSummonsOID = AddToggleOption("$DCURSES_sexAlwaysAllowSummons", sexAlwaysAllowSummons, flag_enable_random_sex)
		sexChanceFollowerOID = AddSliderOption("$DCURSES_sexChanceFollower", sexChanceFollower, "{0}%", flag_enable_random_sex)
		sexChanceSpouseOID = AddSliderOption("$DCURSES_sexChanceSpouse", sexChanceSpouse, "{0}%", flag_enable_random_sex)
		sexChanceSummonOID = AddSliderOption("$DCURSES_sexChanceSummon", sexChanceSummon, "{0}%", flag_enable_random_sex)
	EndIf
EndEvent

Event OnOptionHighlight(int option)
	If option == baseChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_baseChance")
		Return
	Endif
	If option == containerModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_containerModifier")
		Return
	Endif
	If option == bossContainerModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_bossContainerModifier")
		Return
	Endif
	If option == deadBodyModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_deadBodyModifier")
		Return
	Endif
	If option == pickpocketModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_pickpocketModifier")
		Return
	Endif
	If option == doorModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_doorModifier")
		Return
	Endif
	If option == onlyLockedDoorsOID
		SetInfoText("$DCURSES_DESCRIPTION_onlyLockedDoors")
		Return
	Endif
	If option == lockedModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_lockedModifier")
		Return
	Endif
	If option == lockDifficultyModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_lockDifficultyModifier")
		Return
	Endif
	If option == minGoldRequiredOID
		SetInfoText("$DCURSES_DESCRIPTION_minGoldRequired")
		Return
	Endif
	If option == eventScalingOID
		SetInfoText("$DCURSES_DESCRIPTION_eventScaling")
		Return
	Endif
	If option == eventScalingModOID
		SetInfoText("$DCURSES_DESCRIPTION_eventScalingMod")
		Return
	Endif
	If option == minRestraintsOID
		SetInfoText("$DCURSES_DESCRIPTION_minRestraints")
		Return
	Endif
	If option == maxRestraintsOID
		SetInfoText("$DCURSES_DESCRIPTION_maxRestraints")
		Return
	Endif
	If option == bossAditionalRestraintsOID
		SetInfoText("$DCURSES_DESCRIPTION_bossAditionalRestraints")
		Return
	Endif
	If option == bossOnlyHeavyOID
		SetInfoText("$DCURSES_DESCRIPTION_bossOnlyHeavy")
		Return
	Endif
	If option == restraintCapOID
		SetInfoText("$DCURSES_DESCRIPTION_restraintCap")
		Return
	Endif
	If option == stripPlayerOnEventOID
		SetInfoText("$DCURSES_DESCRIPTION_stripPlayerOnEvent")
		Return
	Endif
	If option == arousalModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_arousalModifier")
		Return
	Endif
	If option == minArousalOID
		SetInfoText("$DCURSES_DESCRIPTION_minArousal")
		Return
	Endif
	If option == beltWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_beltWeight")
		Return
	Endif
	If option == beltPlugsOID
		SetInfoText("$DCURSES_DESCRIPTION_beltPlugs")
		Return
	Endif
	If option == noBeltPiercingOID
		SetInfoText("$DCURSES_DESCRIPTION_noBeltPiercing")
		Return
	Endif
	If option == braWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_braWeight")
		Return
	Endif
	If option == plugsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_plugsWeight")
		Return
	Endif
	If option == lockingPlugsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_lockingPlugsWeight")
		Return
	Endif
	If option == inflatablePlugsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_inflatablePlugsWeight")
		Return
	Endif
	If option == plugsDontCountOID
		SetInfoText("$DCURSES_DESCRIPTION_plugsDontCount")
		Return
	Endif
	If option == nipplePiercingsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_nipplePiercingsWeight")
		Return
	Endif
	If option == vaginalPiercingsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_vaginalPiercingsWeight")
		Return
	Endif
	If option == corsetWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_corsetWeight")
		Return
	Endif
	If option == beltedCorsetsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_beltedCorsetsWeight")
		Return
	Endif
	If option == slaveHarnessWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_slaveHarnessWeight")
		Return
	Endif
	If option == chastityHarnessWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_chastityHarnessWeight")
		Return
	Endif
	If option == armbinderWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_armbinderWeight")
		Return
	Endif
	If option == elbowbinderWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_elbowbinderWeight")
		Return
	Endif
	If option == yokeWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_yokeWeight")
		Return
	Endif
	If option == shacklesWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_shacklesWeight")
		Return
	Endif
	If option == straitjacketWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_straitjacketWeight")
		Return
	Endif
	If option == straitjacketLegbinderWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_straitjacketLegbinderWeight")
		Return
	Endif
	If option == petSuitWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_petSuitWeight")
		Return
	Endif
	If option == onlyUseUnforgivingDevicesOID
		SetInfoText("$DCURSES_DESCRIPTION_onlyUseUnforgivingDevices")
		Return
	Endif
	If option == collarWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_collarWeight")
		Return
	Endif
	If option == armCuffsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_armCuffsWeight")
		Return
	Endif
	If option == legCuffsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_legCuffsWeight")
		Return
	Endif
	If option == allowLegShacklesOID
		SetInfoText("$DCURSES_DESCRIPTION_allowLegShackles")
		Return
	Endif
	If option == gagWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_gagWeight")
		Return
	Endif
	If option == ringGagWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_ringGagWeight")
		Return
	Endif
	If option == largeGagWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_largeGagWeight")
		Return
	Endif
	If option == largeRingGagWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_largeRingGagWeight")
		Return
	Endif
	If option == blindfoldWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_blindfoldWeight")
		Return
	Endif
	If option == hoodBothWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_hoodBothWeight")
		Return
	Endif
	If option == hoodGagWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_hoodGagWeight")
		Return
	Endif
	If option == hoodBlindWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_hoodBlindWeight")
		Return
	Endif
	If option == hoodNoneWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_hoodNoneWeight")
		Return
	Endif
	If option == catsuitWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_catsuitWeight")
		Return
	Endif
	If option == hobbleSkirtWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_hobbleSkirtWeight")
		Return
	Endif
	If option == hobbleSkirtDifficultyOID
		SetInfoText("$DCURSES_DESCRIPTION_hobbleSkirtDifficulty")
		Return
	Endif
	If option == bootsWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_bootsWeight")
		Return
	Endif
	If option == glovesWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_glovesWeight")
		Return
	Endif
	If option == mittensWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_mittensWeight")
		Return
	Endif
	If option == keyLossChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_keyLossChance")
		Return
	Endif
	If option == keyChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_keyChance")
		Return
	Endif
	If option == minKeysLootedOID
		SetInfoText("$DCURSES_DESCRIPTION_minKeysLooted")
		Return
	Endif
	If option == maxKeysLootedOID
		SetInfoText("$DCURSES_DESCRIPTION_maxKeysLooted")
		Return
	Endif
	If option == keyBonusOID
		SetInfoText("$DCURSES_DESCRIPTION_keyBonus")
		Return
	Endif
	If option == keyForgivenessOID
		SetInfoText("$DCURSES_DESCRIPTION_keyForgiveness")
		Return
	Endif
	If option == keyPickpocketBonusOID
		SetInfoText("$DCURSES_DESCRIPTION_keyPickpocketBonus")
		Return
	Endif
	If option == maxHeldKeysOID
		SetInfoText("$DCURSES_DESCRIPTION_maxHeldKeys")
		Return
	Endif
	If option == restraintsKeyWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_restraintsKeyWeight")
		Return
	Endif
	If option == chastityKeyWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_chastityKeyWeight")
		Return
	Endif
	If option == piercingToolWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_piercingToolWeight")
		Return
	Endif
	If option == magicKeyChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_magicKeyChance")
		Return
	Endif
	If option == preferRelevantKeysOID
		SetInfoText("$DCURSES_DESCRIPTION_preferRelevantKeys")
		Return
	Endif
	If option == vanishingKeysOID
		SetInfoText("$DCURSES_DESCRIPTION_vanishingKeys")
		Return
	Endif
	If option == eventStandardWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventStandardWeight")
		Return
	Endif
	If option == eventStandardBossReductionOID
		SetInfoText("$DCURSES_DESCRIPTION_eventStandardBossReduction")
		Return
	Endif
	If option == eventOppressiveWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventOppressiveWeight")
		Return
	Endif
	If option == eventContraptionWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventContraptionWeight")
		Return
	Endif
	If option == eventContraptionTimeOID
		SetInfoText("$DCURSES_DESCRIPTION_eventContraptionTime")
		Return
	Endif
	If option == eventContDevicesOID
		SetInfoText("$DCURSES_DESCRIPTION_eventContDevices")
		Return
	Endif
	If option == eventContAllDevicesOID
		SetInfoText("$DCURSES_DESCRIPTION_eventContAllDevices")
		Return
	Endif
	If option == eventContDeviceOverrideOID
		SetInfoText("$DCURSES_DESCRIPTION_eventContDeviceOverride")
		Return
	Endif
	If option == eventTattooWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventTattooWeight")
		Return
	Endif
	If option == eventTattooMinOID
		SetInfoText("$DCURSES_DESCRIPTION_eventTattooMin")
		Return
	Endif
	If option == eventTattooMaxOID
		SetInfoText("$DCURSES_DESCRIPTION_eventTattooMax")
		Return
	Endif
	If option == eventTattooCapOID
		SetInfoText("$DCURSES_DESCRIPTION_eventTattooCap")
		Return
	Endif
	If option == eventLewdMarkWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventLewdMarkWeight")
		Return
	Endif
	If option == eventSimpleSlaveryWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_eventSimpleSlaveryWeight")
		Return
	Endif
	If option == eventSSMinRestraintsOID
		SetInfoText("$DCURSES_DESCRIPTION_eventSSMinRestraints")
		Return
	Endif
	If option == LMAllureWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_LMAllureWeight")
		Return
	Endif
	If option == LMAllureModOID
		SetInfoText("$DCURSES_DESCRIPTION_LMAllureMod")
		Return
	Endif
	If option == LMAllureSexOID
		SetInfoText("$DCURSES_DESCRIPTION_LMAllureSex")
		Return
	Endif
	If option == LMAllureColorOID
		SetInfoText("$DCURSES_DESCRIPTION_LMAllureColor")
		Return
	Endif
	If option == LMHeatWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_LMHeatWeight")
		Return
	Endif
	If option == LMHeatModOID
		SetInfoText("$DCURSES_DESCRIPTION_LMHeatMod")
		Return
	Endif
	If option == LMHeatContainerCountOID
		SetInfoText("$DCURSES_DESCRIPTION_LMHeatContainerCount")
		Return
	Endif
	If option == LMHeatColorOID
		SetInfoText("$DCURSES_DESCRIPTION_LMHeatColor")
		Return
	Endif
	If option == LMBrandingWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBrandingWeight")
		Return
	Endif
	If option == LMBrandingChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBrandingChance")
		Return
	Endif
	If option == LMBrndingTotalOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBrndingTotal")
		Return
	Endif
	If option == LMBrandingPunishOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBrandingPunish")
		Return
	Endif
	If option == LMBrandingColorOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBrandingColor")
		Return
	Endif
	If option == LMBondageWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBondageWeight")
		Return
	Endif
	If option == LMBondageChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBondageChance")
		Return
	Endif
	If option == LMBondageDeviceCountOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBondageDeviceCount")
		Return
	Endif
	If option == LMBondageColorOID
		SetInfoText("$DCURSES_DESCRIPTION_LMBondageColor")
		Return
	Endif
	If option == LMNudityWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_LMNudityWeight")
		Return
	Endif
	If option == LMNudityChestOnlyOID
		SetInfoText("$DCURSES_DESCRIPTION_LMNudityChestOnly")
		Return
	Endif
	If option == LMNudityAditionalFormsOID
		SetInfoText("$DCURSES_DESCRIPTION_LMNudityAditionalForms")
		Return
	Endif
	If option == LMNudityTalkTimesOID
		SetInfoText("$DCURSES_DESCRIPTION_LMNudityTalkTimes")
		Return
	Endif
	If option == LMNudityColorOID
		SetInfoText("$DCURSES_DESCRIPTION_LMNudityColor")
		Return
	Endif
	If option == oppSummonerCollarWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_oppSummonerCollarWeight")
		Return
	Endif
	If option == oppSummonerSexCountOID
		SetInfoText("$DCURSES_DESCRIPTION_oppSummonerSexCount")
		Return
	Endif
	If option == oppSCollarDrainsMagickaOID
		SetInfoText("$DCURSES_DESCRIPTION_oppSCollarDrainsMagicka")
		Return
	Endif
	If option == oppSMinSummonArousalOID
		SetInfoText("$DCURSES_DESCRIPTION_oppSMinSummonArousal")
		Return
	Endif
	If option == oppSummonChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_oppSummonChance")
		Return
	Endif
	If option == oppDwarvenCuirassWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_oppDwarvenCuirassWeight")
		Return
	Endif
	If option == oppDwarvenValueNeededOID
		SetInfoText("$DCURSES_DESCRIPTION_oppDwarvenValueNeeded")
		Return
	Endif
	If option == oppDwarvenHeavyRestraintOID
		SetInfoText("$DCURSES_DESCRIPTION_oppDwarvenHeavyRestraint")
		Return
	Endif
	If option == oppDwarvenRequireLocOID
		SetInfoText("$DCURSES_DESCRIPTION_oppDwarvenRequireLoc")
		Return
	Endif
	If option == oppDwarvenArousalOID
		SetInfoText("$DCURSES_DESCRIPTION_oppDwarvenArousal")
		Return
	Endif
	If option == oppLivingLatexWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexWeight")
		Return
	Endif
	If option == oppLivingLatexStartTimeOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexStartTime")
		Return
	Endif
	If option == oppLivingLatexHeavyOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexHeavy")
		Return
	Endif
	If option == oppLivingLatexMoreOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexMore")
		Return
	Endif
	If option == oppLivingLatexRequireRemOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexRequireRem")
		Return
	Endif
	If option == oppLivingLatexOpenOID
		SetInfoText("$DCURSES_DESCRIPTION_oppLivingLatexOpen")
		Return
	Endif
	If option == useLocationModifiersOID
		SetInfoText("$DCURSES_DESCRIPTION_useLocationModifiers")
		Return
	Endif
	If option == playerHomeModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_playerHomeModifier")
		Return
	Endif
	If option == cityModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_cityModifier")
		Return
	Endif
	If option == townModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_townModifier")
		Return
	Endif
	If option == banditModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_banditModifier")
		Return
	Endif
	If option == draugrModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_draugrModifier")
		Return
	Endif
	If option == lockedLocationBypassOID
		SetInfoText("$DCURSES_DESCRIPTION_lockedLocationBypass")
		Return
	Endif
	If option == theftLocationBypassOID
		SetInfoText("$DCURSES_DESCRIPTION_theftLocationBypass")
		Return
	Endif
	If option == dwarvenModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_dwarvenModifier")
		Return
	Endif
	If option == falmerModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_falmerModifier")
		Return
	Endif
	If option == forswornModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_forswornModifier")
		Return
	Endif
	If option == vampireModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_vampireModifier")
		Return
	Endif
	If option == warlockModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_warlockModifier")
		Return
	Endif
	If option == dragonLairModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_dragonLairModifier")
		Return
	Endif
	If option == apocryphaModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_apocryphaModifier")
		Return
	Endif
	If option == wildernessModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_wildernessModifier")
		Return
	Endif
	If option == enableQuestInteractionsOID
		SetInfoText("$DCURSES_DESCRIPTION_enableQuestInteractions")
		Return
	Endif
	If option == enableQISaarthalOID
		SetInfoText("$DCURSES_DESCRIPTION_enableQISaarthal")
		Return
	Endif
	If option == enableQIDwemerMuseumOID
		SetInfoText("$DCURSES_DESCRIPTION_enableQIDwemerMuseum")
		Return
	Endif
	If option == enableQIMalkoranOID
		SetInfoText("$DCURSES_DESCRIPTION_enableQIMalkoran")
		Return
	Endif
	If option == enableQISanguineOID
		SetInfoText("$DCURSES_DESCRIPTION_enableQISanguine")
		Return
	Endif
	If option == noMessageBoxesOID
		SetInfoText("$DCURSES_DESCRIPTION_noMessageBoxes")
		Return
	Endif
	If option == bossChestUseModelPathOID
		SetInfoText("$DCURSES_DESCRIPTION_bossChestUseModelPath")
		Return
	Endif
	If option == rDeviceBaseChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_rDeviceBaseChance")
		Return
	Endif
	If option == dragonHoardOID
		SetInfoText("$DCURSES_DESCRIPTION_dragonHoard")
		Return
	Endif
	If option == bossExtraGoldOID
		SetInfoText("$DCURSES_DESCRIPTION_bossExtraGold")
		Return
	Endif
	If option == useThemesOID
		SetInfoText("$DCURSES_DESCRIPTION_useThemes")
		Return
	Endif
	If option == enableSlowStripOID
		SetInfoText("$DCURSES_DESCRIPTION_enableSlowStrip")
		Return
	Endif
	If option == tatSolventChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_tatSolventChance")
		Return
	Endif
	If option == resumeEventsOID
		SetInfoText("$DCURSES_DESCRIPTION_resumeEvents")
		Return
	Endif
	If option == setAllDefaultSettingsOID
		SetInfoText("$DCURSES_DESCRIPTION_setAllDefaultSettings")
		Return
	Endif
	If option == consTriggerNudeOID
		SetInfoText("$DCURSES_DESCRIPTION_consTriggerNude")
		Return
	Endif
	If option == consTriggerRestrainedOID
		SetInfoText("$DCURSES_DESCRIPTION_consTriggerRestrained")
		Return
	Endif
	If option == consTriggerSexOID
		SetInfoText("$DCURSES_DESCRIPTION_consTriggerSex")
		Return
	Endif
	If option == consAllowFollowersOID
		SetInfoText("$DCURSES_DESCRIPTION_consAllowFollowers")
		Return
	Endif
	If option == consAllowCreaturesOID
		SetInfoText("$DCURSES_DESCRIPTION_consAllowCreatures")
		Return
	Endif
	If option == consUseRelationshipsOID
		SetInfoText("$DCURSES_DESCRIPTION_consUseRelationships")
		Return
	Endif
	If option == consRelationBondageOID
		SetInfoText("$DCURSES_DESCRIPTION_consRelationBondage")
		Return
	Endif
	If option == consFallthroughOID
		SetInfoText("$DCURSES_DESCRIPTION_consFallthrough")
		Return
	Endif
	If option == consSexWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_consSexWeight")
		Return
	Endif
	If option == consFineWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_consFineWeight")
		Return
	Endif
	If option == consFineAmountOID
		SetInfoText("$DCURSES_DESCRIPTION_consFineAmount")
		Return
	Endif
	If option == consRandomBondageWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_consRandomBondageWeight")
		Return
	Endif
	If option == consRandomHeavyBondageOID
		SetInfoText("$DCURSES_DESCRIPTION_consRandomHeavyBondage")
		Return
	Endif
	If option == consBondageIgnoreMaxOID
		SetInfoText("$DCURSES_DESCRIPTION_consBondageIgnoreMax")
		Return
	Endif
	If option == consMercyWeightOID
		SetInfoText("$DCURSES_DESCRIPTION_consMercyWeight")
		Return
	Endif
	If option == sexEnabledOID
		SetInfoText("$DCURSES_DESCRIPTION_sexEnabled")
		Return
	Endif
	If option == sexAggressiveAnimsOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAggressiveAnims")
		Return
	Endif
	If option == sexRandomEnabledOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRandomEnabled")
		Return
	Endif
	If option == sexCooldownOID
		SetInfoText("$DCURSES_DESCRIPTION_sexCooldown")
		Return
	Endif
	If option == sexChanceOID
		SetInfoText("$DCURSES_DESCRIPTION_sexChance")
		Return
	Endif
	If option == sexChanceCreatureOID
		SetInfoText("$DCURSES_DESCRIPTION_sexChanceCreature")
		Return
	Endif
	If option == sexBaseArousalOID
		SetInfoText("$DCURSES_DESCRIPTION_sexBaseArousal")
		Return
	Endif
	If option == sexArousalNightModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalNightModifier")
		Return
	Endif
	If option == sexArousalNudeModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalNudeModifier")
		Return
	Endif
	If option == sexArousalCollarModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalCollarModifier")
		Return
	Endif
	If option == sexArousalHeavyModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalHeavyModifier")
		Return
	Endif
	If option == sexArousalBlindModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalBlindModifier")
		Return
	Endif
	If option == sexArousalBootsModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalBootsModifier")
		Return
	Endif
	If option == sexArousalHobbleModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalHobbleModifier")
		Return
	Endif
	If option == sexArousalVisibleModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalVisibleModifier")
		Return
	Endif
	If option == sexArousalTattooModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalTattooModifier")
		Return
	Endif
	If option == sexArousalCreatureModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalCreatureModifier")
		Return
	Endif
	If option == sexArousalFollowerModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalFollowerModifier")
		Return
	Endif
	If option == sexArousalSpouseModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalSpouseModifier")
		Return
	Endif
	If option == sexArousalSummonModifierOID
		SetInfoText("$DCURSES_DESCRIPTION_sexArousalSummonModifier")
		Return
	Endif
	If option == sexSearchRadiusOID
		SetInfoText("$DCURSES_DESCRIPTION_sexSearchRadius")
		Return
	Endif
	If option == sexSearchIntervalOID
		SetInfoText("$DCURSES_DESCRIPTION_sexSearchInterval")
		Return
	Endif
	If option == sexAllowMaleOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAllowMale")
		Return
	Endif
	If option == sexAllowFemaleOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAllowFemale")
		Return
	Endif
	If option == sexAllowFutaOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAllowFuta")
		Return
	Endif
	If option == sexAllowCreatureOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAllowCreature")
		Return
	Endif
	If option == sexAllowFarmAnimalsOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAllowFarmAnimals")
		Return
	Endif
	If option == sexRequireAllOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequireAll")
		Return
	Endif
	If option == sexRequireBindingsOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequireBindings")
		Return
	Endif
	If option == sexRequireCollarOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequireCollar")
		Return
	Endif
	If option == sexRequireHeavyOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequireHeavy")
		Return
	Endif
	If option == sexRequireNudeOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequireNude")
		Return
	Endif
	If option == sexRequiredPlayerArousalOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequiredPlayerArousal")
		Return
	Endif
	If option == sexRequiredPlayerTattoosOID
		SetInfoText("$DCURSES_DESCRIPTION_sexRequiredPlayerTattoos")
		Return
	Endif
	If option == sexAlwaysAllowFollowersOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAlwaysAllowFollowers")
		Return
	Endif
	If option == sexAlwaysAllowSpouseOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAlwaysAllowSpouse")
		Return
	Endif
	If option == sexAlwaysAllowSummonsOID
		SetInfoText("$DCURSES_DESCRIPTION_sexAlwaysAllowSummons")
		Return
	Endif
	If option == sexChanceFollowerOID
		SetInfoText("$DCURSES_DESCRIPTION_sexChanceFollower")
		Return
	Endif
	If option == sexChanceSpouseOID
		SetInfoText("$DCURSES_DESCRIPTION_sexChanceSpouse")
		Return
	Endif
	If option == sexChanceSummonOID
		SetInfoText("$DCURSES_DESCRIPTION_sexChanceSummon")
		Return
	Endif
EndEvent

Event OnOptionSelect(int option)
	If option == onlyLockedDoorsOID
		onlyLockedDoors = !onlyLockedDoors
		SetToggleOptionValue(onlyLockedDoorsOID, onlyLockedDoors)
		Return
	Endif
	If option == eventScalingOID
		eventScaling = !eventScaling
		SetToggleOptionValue(eventScalingOID, eventScaling)
		Return
	Endif
	If option == bossOnlyHeavyOID
		bossOnlyHeavy = !bossOnlyHeavy
		SetToggleOptionValue(bossOnlyHeavyOID, bossOnlyHeavy)
		Return
	Endif
	If option == stripPlayerOnEventOID
		stripPlayerOnEvent = !stripPlayerOnEvent
		SetToggleOptionValue(stripPlayerOnEventOID, stripPlayerOnEvent)
		Return
	Endif
	If option == beltPlugsOID
		beltPlugs = !beltPlugs
		SetToggleOptionValue(beltPlugsOID, beltPlugs)
		Return
	Endif
	If option == noBeltPiercingOID
		noBeltPiercing = !noBeltPiercing
		SetToggleOptionValue(noBeltPiercingOID, noBeltPiercing)
		Return
	Endif
	If option == plugsDontCountOID
		plugsDontCount = !plugsDontCount
		SetToggleOptionValue(plugsDontCountOID, plugsDontCount)
		Return
	Endif
	If option == onlyUseUnforgivingDevicesOID
		onlyUseUnforgivingDevices = !onlyUseUnforgivingDevices
		SetToggleOptionValue(onlyUseUnforgivingDevicesOID, onlyUseUnforgivingDevices)
		Return
	Endif
	If option == allowLegShacklesOID
		allowLegShackles = !allowLegShackles
		SetToggleOptionValue(allowLegShacklesOID, allowLegShackles)
		Return
	Endif
	If option == keyForgivenessOID
		keyForgiveness = !keyForgiveness
		SetToggleOptionValue(keyForgivenessOID, keyForgiveness)
		Return
	Endif
	If option == preferRelevantKeysOID
		preferRelevantKeys = !preferRelevantKeys
		SetToggleOptionValue(preferRelevantKeysOID, preferRelevantKeys)
		Return
	Endif
	If option == vanishingKeysOID
		vanishingKeys = !vanishingKeys
		SetToggleOptionValue(vanishingKeysOID, vanishingKeys)
		Return
	Endif
	If option == eventContDevicesOID
		eventContDevices = !eventContDevices
		SetToggleOptionValue(eventContDevicesOID, eventContDevices)
		Return
	Endif
	If option == eventContAllDevicesOID
		eventContAllDevices = !eventContAllDevices
		SetToggleOptionValue(eventContAllDevicesOID, eventContAllDevices)
		Return
	Endif
	If option == LMBrandingPunishOID
		LMBrandingPunish = !LMBrandingPunish
		SetToggleOptionValue(LMBrandingPunishOID, LMBrandingPunish)
		Return
	Endif
	If option == LMNudityChestOnlyOID
		LMNudityChestOnly = !LMNudityChestOnly
		SetToggleOptionValue(LMNudityChestOnlyOID, LMNudityChestOnly)
		ForcePageReset()
		Return
	Endif
	If option == oppSCollarDrainsMagickaOID
		oppSCollarDrainsMagicka = !oppSCollarDrainsMagicka
		SetToggleOptionValue(oppSCollarDrainsMagickaOID, oppSCollarDrainsMagicka)
		Return
	Endif
	If option == oppDwarvenHeavyRestraintOID
		oppDwarvenHeavyRestraint = !oppDwarvenHeavyRestraint
		SetToggleOptionValue(oppDwarvenHeavyRestraintOID, oppDwarvenHeavyRestraint)
		Return
	Endif
	If option == oppDwarvenRequireLocOID
		oppDwarvenRequireLoc = !oppDwarvenRequireLoc
		SetToggleOptionValue(oppDwarvenRequireLocOID, oppDwarvenRequireLoc)
		Return
	Endif
	If option == oppLivingLatexHeavyOID
		oppLivingLatexHeavy = !oppLivingLatexHeavy
		SetToggleOptionValue(oppLivingLatexHeavyOID, oppLivingLatexHeavy)
		Return
	Endif
	If option == oppLivingLatexRequireRemOID
		oppLivingLatexRequireRem = !oppLivingLatexRequireRem
		SetToggleOptionValue(oppLivingLatexRequireRemOID, oppLivingLatexRequireRem)
		Return
	Endif
	If option == oppLivingLatexOpenOID
		oppLivingLatexOpen = !oppLivingLatexOpen
		SetToggleOptionValue(oppLivingLatexOpenOID, oppLivingLatexOpen)
		Return
	Endif
	If option == useLocationModifiersOID
		useLocationModifiers = !useLocationModifiers
		SetToggleOptionValue(useLocationModifiersOID, useLocationModifiers)
		Return
	Endif
	If option == enableQuestInteractionsOID
		enableQuestInteractions = !enableQuestInteractions
		SetToggleOptionValue(enableQuestInteractionsOID, enableQuestInteractions)
		Return
	Endif
	If option == enableQISaarthalOID
		enableQISaarthal = !enableQISaarthal
		SetToggleOptionValue(enableQISaarthalOID, enableQISaarthal)
		Return
	Endif
	If option == enableQIDwemerMuseumOID
		enableQIDwemerMuseum = !enableQIDwemerMuseum
		SetToggleOptionValue(enableQIDwemerMuseumOID, enableQIDwemerMuseum)
		Return
	Endif
	If option == enableQIMalkoranOID
		enableQIMalkoran = !enableQIMalkoran
		SetToggleOptionValue(enableQIMalkoranOID, enableQIMalkoran)
		Return
	Endif
	If option == enableQISanguineOID
		enableQISanguine = !enableQISanguine
		SetToggleOptionValue(enableQISanguineOID, enableQISanguine)
		Return
	Endif
	If option == noMessageBoxesOID
		noMessageBoxes = !noMessageBoxes
		SetToggleOptionValue(noMessageBoxesOID, noMessageBoxes)
		Return
	Endif
	If option == bossChestUseModelPathOID
		bossChestUseModelPath = !bossChestUseModelPath
		SetToggleOptionValue(bossChestUseModelPathOID, bossChestUseModelPath)
		Return
	Endif
	If option == dragonHoardOID
		dragonHoard = !dragonHoard
		SetToggleOptionValue(dragonHoardOID, dragonHoard)
		Return
	Endif
	If option == bossExtraGoldOID
		bossExtraGold = !bossExtraGold
		SetToggleOptionValue(bossExtraGoldOID, bossExtraGold)
		Return
	Endif
	If option == useThemesOID
		useThemes = !useThemes
		SetToggleOptionValue(useThemesOID, useThemes)
		Return
	Endif
	If option == enableSlowStripOID
		enableSlowStrip = !enableSlowStrip
		SetToggleOptionValue(enableSlowStripOID, enableSlowStrip)
		Return
	Endif
	If option == resumeEventsOID
		resumeEvents = !resumeEvents
		SetToggleOptionValue(resumeEventsOID, resumeEvents)
		Return
	Endif
	If option == setAllDefaultSettingsOID
		setAllDefaultSettings = !setAllDefaultSettings
		SetToggleOptionValue(setAllDefaultSettingsOID, setAllDefaultSettings)
		Return
	Endif
	If option == consAllowFollowersOID
		consAllowFollowers = !consAllowFollowers
		SetToggleOptionValue(consAllowFollowersOID, consAllowFollowers)
		Return
	Endif
	If option == consAllowCreaturesOID
		consAllowCreatures = !consAllowCreatures
		SetToggleOptionValue(consAllowCreaturesOID, consAllowCreatures)
		Return
	Endif
	If option == consUseRelationshipsOID
		consUseRelationships = !consUseRelationships
		SetToggleOptionValue(consUseRelationshipsOID, consUseRelationships)
		Return
	Endif
	If option == consRelationBondageOID
		consRelationBondage = !consRelationBondage
		SetToggleOptionValue(consRelationBondageOID, consRelationBondage)
		Return
	Endif
	If option == consFallthroughOID
		consFallthrough = !consFallthrough
		SetToggleOptionValue(consFallthroughOID, consFallthrough)
		Return
	Endif
	If option == consRandomHeavyBondageOID
		consRandomHeavyBondage = !consRandomHeavyBondage
		SetToggleOptionValue(consRandomHeavyBondageOID, consRandomHeavyBondage)
		Return
	Endif
	If option == consBondageIgnoreMaxOID
		consBondageIgnoreMax = !consBondageIgnoreMax
		SetToggleOptionValue(consBondageIgnoreMaxOID, consBondageIgnoreMax)
		Return
	Endif
	If option == sexEnabledOID
		sexEnabled = !sexEnabled
		SetToggleOptionValue(sexEnabledOID, sexEnabled)
		ForcePageReset()
		Return
	Endif
	If option == sexAggressiveAnimsOID
		sexAggressiveAnims = !sexAggressiveAnims
		SetToggleOptionValue(sexAggressiveAnimsOID, sexAggressiveAnims)
		Return
	Endif
	If option == sexRandomEnabledOID
		sexRandomEnabled = !sexRandomEnabled
		SetToggleOptionValue(sexRandomEnabledOID, sexRandomEnabled)
		ForcePageReset()
		Return
	Endif
	If option == sexAllowMaleOID
		sexAllowMale = !sexAllowMale
		SetToggleOptionValue(sexAllowMaleOID, sexAllowMale)
		Return
	Endif
	If option == sexAllowFemaleOID
		sexAllowFemale = !sexAllowFemale
		SetToggleOptionValue(sexAllowFemaleOID, sexAllowFemale)
		Return
	Endif
	If option == sexAllowFutaOID
		sexAllowFuta = !sexAllowFuta
		SetToggleOptionValue(sexAllowFutaOID, sexAllowFuta)
		Return
	Endif
	If option == sexAllowCreatureOID
		sexAllowCreature = !sexAllowCreature
		SetToggleOptionValue(sexAllowCreatureOID, sexAllowCreature)
		Return
	Endif
	If option == sexAllowFarmAnimalsOID
		sexAllowFarmAnimals = !sexAllowFarmAnimals
		SetToggleOptionValue(sexAllowFarmAnimalsOID, sexAllowFarmAnimals)
		Return
	Endif
	If option == sexRequireAllOID
		sexRequireAll = !sexRequireAll
		SetToggleOptionValue(sexRequireAllOID, sexRequireAll)
		Return
	Endif
	If option == sexRequireBindingsOID
		sexRequireBindings = !sexRequireBindings
		SetToggleOptionValue(sexRequireBindingsOID, sexRequireBindings)
		Return
	Endif
	If option == sexRequireCollarOID
		sexRequireCollar = !sexRequireCollar
		SetToggleOptionValue(sexRequireCollarOID, sexRequireCollar)
		Return
	Endif
	If option == sexRequireHeavyOID
		sexRequireHeavy = !sexRequireHeavy
		SetToggleOptionValue(sexRequireHeavyOID, sexRequireHeavy)
		Return
	Endif
	If option == sexRequireNudeOID
		sexRequireNude = !sexRequireNude
		SetToggleOptionValue(sexRequireNudeOID, sexRequireNude)
		Return
	Endif
	If option == sexAlwaysAllowFollowersOID
		sexAlwaysAllowFollowers = !sexAlwaysAllowFollowers
		SetToggleOptionValue(sexAlwaysAllowFollowersOID, sexAlwaysAllowFollowers)
		Return
	Endif
	If option == sexAlwaysAllowSpouseOID
		sexAlwaysAllowSpouse = !sexAlwaysAllowSpouse
		SetToggleOptionValue(sexAlwaysAllowSpouseOID, sexAlwaysAllowSpouse)
		Return
	Endif
	If option == sexAlwaysAllowSummonsOID
		sexAlwaysAllowSummons = !sexAlwaysAllowSummons
		SetToggleOptionValue(sexAlwaysAllowSummonsOID, sexAlwaysAllowSummons)
		Return
	Endif
EndEvent

Event OnOptionSliderOpen(int option)
	If option == minGoldRequiredOID
		SetSliderDialogStartValue(minGoldRequired)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 5000)
		SetSliderDialogInterval(10)
		Return
	Endif
	If option == eventScalingModOID
		SetSliderDialogStartValue(eventScalingMod)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(1, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == minRestraintsOID
		SetSliderDialogStartValue(minRestraints)
		SetSliderDialogDefaultValue(1)
		SetSliderDialogRange(1, 15)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == maxRestraintsOID
		SetSliderDialogStartValue(maxRestraints)
		SetSliderDialogDefaultValue(3)
		SetSliderDialogRange(1, 15)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == bossAditionalRestraintsOID
		SetSliderDialogStartValue(bossAditionalRestraints)
		SetSliderDialogDefaultValue(2)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == restraintCapOID
		SetSliderDialogStartValue(restraintCap)
		SetSliderDialogDefaultValue(7)
		SetSliderDialogRange(1, 15)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == minArousalOID
		SetSliderDialogStartValue(minArousal)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == beltWeightOID
		SetSliderDialogStartValue(beltWeight)
		SetSliderDialogDefaultValue(40)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == braWeightOID
		SetSliderDialogStartValue(braWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == plugsWeightOID
		SetSliderDialogStartValue(plugsWeight)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == lockingPlugsWeightOID
		SetSliderDialogStartValue(lockingPlugsWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == inflatablePlugsWeightOID
		SetSliderDialogStartValue(inflatablePlugsWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == nipplePiercingsWeightOID
		SetSliderDialogStartValue(nipplePiercingsWeight)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == vaginalPiercingsWeightOID
		SetSliderDialogStartValue(vaginalPiercingsWeight)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == corsetWeightOID
		SetSliderDialogStartValue(corsetWeight)
		SetSliderDialogDefaultValue(40)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == beltedCorsetsWeightOID
		SetSliderDialogStartValue(beltedCorsetsWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == slaveHarnessWeightOID
		SetSliderDialogStartValue(slaveHarnessWeight)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == chastityHarnessWeightOID
		SetSliderDialogStartValue(chastityHarnessWeight)
		SetSliderDialogDefaultValue(40)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == armbinderWeightOID
		SetSliderDialogStartValue(armbinderWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == elbowbinderWeightOID
		SetSliderDialogStartValue(elbowbinderWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == yokeWeightOID
		SetSliderDialogStartValue(yokeWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == shacklesWeightOID
		SetSliderDialogStartValue(shacklesWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == straitjacketWeightOID
		SetSliderDialogStartValue(straitjacketWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == straitjacketLegbinderWeightOID
		SetSliderDialogStartValue(straitjacketLegbinderWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == petSuitWeightOID
		SetSliderDialogStartValue(petSuitWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == collarWeightOID
		SetSliderDialogStartValue(collarWeight)
		SetSliderDialogDefaultValue(60)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == armCuffsWeightOID
		SetSliderDialogStartValue(armCuffsWeight)
		SetSliderDialogDefaultValue(60)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == legCuffsWeightOID
		SetSliderDialogStartValue(legCuffsWeight)
		SetSliderDialogDefaultValue(60)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == gagWeightOID
		SetSliderDialogStartValue(gagWeight)
		SetSliderDialogDefaultValue(35)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == ringGagWeightOID
		SetSliderDialogStartValue(ringGagWeight)
		SetSliderDialogDefaultValue(45)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == largeGagWeightOID
		SetSliderDialogStartValue(largeGagWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == largeRingGagWeightOID
		SetSliderDialogStartValue(largeRingGagWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == blindfoldWeightOID
		SetSliderDialogStartValue(blindfoldWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hoodBothWeightOID
		SetSliderDialogStartValue(hoodBothWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hoodGagWeightOID
		SetSliderDialogStartValue(hoodGagWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hoodBlindWeightOID
		SetSliderDialogStartValue(hoodBlindWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hoodNoneWeightOID
		SetSliderDialogStartValue(hoodNoneWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == catsuitWeightOID
		SetSliderDialogStartValue(catsuitWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hobbleSkirtWeightOID
		SetSliderDialogStartValue(hobbleSkirtWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == hobbleSkirtDifficultyOID
		SetSliderDialogStartValue(hobbleSkirtDifficulty)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == bootsWeightOID
		SetSliderDialogStartValue(bootsWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == glovesWeightOID
		SetSliderDialogStartValue(glovesWeight)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == mittensWeightOID
		SetSliderDialogStartValue(mittensWeight)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == minKeysLootedOID
		SetSliderDialogStartValue(minKeysLooted)
		SetSliderDialogDefaultValue(1)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == maxKeysLootedOID
		SetSliderDialogStartValue(maxKeysLooted)
		SetSliderDialogDefaultValue(1)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == maxHeldKeysOID
		SetSliderDialogStartValue(maxHeldKeys)
		SetSliderDialogDefaultValue(3)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == restraintsKeyWeightOID
		SetSliderDialogStartValue(restraintsKeyWeight)
		SetSliderDialogDefaultValue(80)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == chastityKeyWeightOID
		SetSliderDialogStartValue(chastityKeyWeight)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == piercingToolWeightOID
		SetSliderDialogStartValue(piercingToolWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventStandardWeightOID
		SetSliderDialogStartValue(eventStandardWeight)
		SetSliderDialogDefaultValue(100)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventStandardBossReductionOID
		SetSliderDialogStartValue(eventStandardBossReduction)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventOppressiveWeightOID
		SetSliderDialogStartValue(eventOppressiveWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventContraptionWeightOID
		SetSliderDialogStartValue(eventContraptionWeight)
		SetSliderDialogDefaultValue(25)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventContDeviceOverrideOID
		SetSliderDialogStartValue(eventContDeviceOverride)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventTattooWeightOID
		SetSliderDialogStartValue(eventTattooWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventTattooMinOID
		SetSliderDialogStartValue(eventTattooMin)
		SetSliderDialogDefaultValue(1)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventTattooMaxOID
		SetSliderDialogStartValue(eventTattooMax)
		SetSliderDialogDefaultValue(3)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventTattooCapOID
		SetSliderDialogStartValue(eventTattooCap)
		SetSliderDialogDefaultValue(8)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventLewdMarkWeightOID
		SetSliderDialogStartValue(eventLewdMarkWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventSimpleSlaveryWeightOID
		SetSliderDialogStartValue(eventSimpleSlaveryWeight)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == eventSSMinRestraintsOID
		SetSliderDialogStartValue(eventSSMinRestraints)
		SetSliderDialogDefaultValue(6)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMAllureWeightOID
		SetSliderDialogStartValue(LMAllureWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMAllureModOID
		SetSliderDialogStartValue(LMAllureMod)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 200)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMAllureSexOID
		SetSliderDialogStartValue(LMAllureSex)
		SetSliderDialogDefaultValue(25)
		SetSliderDialogRange(3, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMHeatWeightOID
		SetSliderDialogStartValue(LMHeatWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMHeatModOID
		SetSliderDialogStartValue(LMHeatMod)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 200)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMHeatContainerCountOID
		SetSliderDialogStartValue(LMHeatContainerCount)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(10, 200)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMBrandingWeightOID
		SetSliderDialogStartValue(LMBrandingWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMBrndingTotalOID
		SetSliderDialogStartValue(LMBrndingTotal)
		SetSliderDialogDefaultValue(12)
		SetSliderDialogRange(1, 20)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMBondageWeightOID
		SetSliderDialogStartValue(LMBondageWeight)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMBondageDeviceCountOID
		SetSliderDialogStartValue(LMBondageDeviceCount)
		SetSliderDialogDefaultValue(8)
		SetSliderDialogRange(1, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMNudityWeightOID
		SetSliderDialogStartValue(LMNudityWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == LMNudityTalkTimesOID
		SetSliderDialogStartValue(LMNudityTalkTimes)
		SetSliderDialogDefaultValue(35)
		SetSliderDialogRange(3, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppSummonerCollarWeightOID
		SetSliderDialogStartValue(oppSummonerCollarWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(1, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppSummonerSexCountOID
		SetSliderDialogStartValue(oppSummonerSexCount)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(1, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppSMinSummonArousalOID
		SetSliderDialogStartValue(oppSMinSummonArousal)
		SetSliderDialogDefaultValue(90)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppDwarvenCuirassWeightOID
		SetSliderDialogStartValue(oppDwarvenCuirassWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(1, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppDwarvenValueNeededOID
		SetSliderDialogStartValue(oppDwarvenValueNeeded)
		SetSliderDialogDefaultValue(200)
		SetSliderDialogRange(30, 2000)
		SetSliderDialogInterval(10)
		Return
	Endif
	If option == oppDwarvenArousalOID
		SetSliderDialogStartValue(oppDwarvenArousal)
		SetSliderDialogDefaultValue(25)
		SetSliderDialogRange(10, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppLivingLatexWeightOID
		SetSliderDialogStartValue(oppLivingLatexWeight)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(1, 500)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == oppLivingLatexStartTimeOID
		SetSliderDialogStartValue(oppLivingLatexStartTime)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(1, 60)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == consSexWeightOID
		SetSliderDialogStartValue(consSexWeight)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == consFineWeightOID
		SetSliderDialogStartValue(consFineWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == consFineAmountOID
		SetSliderDialogStartValue(consFineAmount)
		SetSliderDialogDefaultValue(100)
		SetSliderDialogRange(50, 1000)
		SetSliderDialogInterval(10)
		Return
	Endif
	If option == consRandomBondageWeightOID
		SetSliderDialogStartValue(consRandomBondageWeight)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == consMercyWeightOID
		SetSliderDialogStartValue(consMercyWeight)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexCooldownOID
		SetSliderDialogStartValue(sexCooldown)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(5, 300)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexChanceOID
		SetSliderDialogStartValue(sexChance)
		SetSliderDialogDefaultValue(50)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexChanceCreatureOID
		SetSliderDialogStartValue(sexChanceCreature)
		SetSliderDialogDefaultValue(30)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexBaseArousalOID
		SetSliderDialogStartValue(sexBaseArousal)
		SetSliderDialogDefaultValue(90)
		SetSliderDialogRange(0, 150)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalNightModifierOID
		SetSliderDialogStartValue(sexArousalNightModifier)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalNudeModifierOID
		SetSliderDialogStartValue(sexArousalNudeModifier)
		SetSliderDialogDefaultValue(15)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalCollarModifierOID
		SetSliderDialogStartValue(sexArousalCollarModifier)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalHeavyModifierOID
		SetSliderDialogStartValue(sexArousalHeavyModifier)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalBlindModifierOID
		SetSliderDialogStartValue(sexArousalBlindModifier)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalBootsModifierOID
		SetSliderDialogStartValue(sexArousalBootsModifier)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalHobbleModifierOID
		SetSliderDialogStartValue(sexArousalHobbleModifier)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalVisibleModifierOID
		SetSliderDialogStartValue(sexArousalVisibleModifier)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalCreatureModifierOID
		SetSliderDialogStartValue(sexArousalCreatureModifier)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalFollowerModifierOID
		SetSliderDialogStartValue(sexArousalFollowerModifier)
		SetSliderDialogDefaultValue(10)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalSpouseModifierOID
		SetSliderDialogStartValue(sexArousalSpouseModifier)
		SetSliderDialogDefaultValue(20)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexArousalSummonModifierOID
		SetSliderDialogStartValue(sexArousalSummonModifier)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexSearchIntervalOID
		SetSliderDialogStartValue(sexSearchInterval)
		SetSliderDialogDefaultValue(5)
		SetSliderDialogRange(5, 120)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexRequiredPlayerArousalOID
		SetSliderDialogStartValue(sexRequiredPlayerArousal)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexRequiredPlayerTattoosOID
		SetSliderDialogStartValue(sexRequiredPlayerTattoos)
		SetSliderDialogDefaultValue(0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexChanceFollowerOID
		SetSliderDialogStartValue(sexChanceFollower)
		SetSliderDialogDefaultValue(-1)
		SetSliderDialogRange(-1, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexChanceSpouseOID
		SetSliderDialogStartValue(sexChanceSpouse)
		SetSliderDialogDefaultValue(-1)
		SetSliderDialogRange(-1, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == sexChanceSummonOID
		SetSliderDialogStartValue(sexChanceSummon)
		SetSliderDialogDefaultValue(-1)
		SetSliderDialogRange(-1, 100)
		SetSliderDialogInterval(1)
		Return
	Endif
	If option == baseChanceOID
		SetSliderDialogStartValue(baseChance)
		SetSliderDialogDefaultValue(6.5)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == containerModifierOID
		SetSliderDialogStartValue(containerModifier)
		SetSliderDialogDefaultValue(1.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == bossContainerModifierOID
		SetSliderDialogStartValue(bossContainerModifier)
		SetSliderDialogDefaultValue(2.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == deadBodyModifierOID
		SetSliderDialogStartValue(deadBodyModifier)
		SetSliderDialogDefaultValue(1.3)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == pickpocketModifierOID
		SetSliderDialogStartValue(pickpocketModifier)
		SetSliderDialogDefaultValue(1.3)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == doorModifierOID
		SetSliderDialogStartValue(doorModifier)
		SetSliderDialogDefaultValue(1.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == lockedModifierOID
		SetSliderDialogStartValue(lockedModifier)
		SetSliderDialogDefaultValue(2.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == lockDifficultyModifierOID
		SetSliderDialogStartValue(lockDifficultyModifier)
		SetSliderDialogDefaultValue(1.3)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == arousalModifierOID
		SetSliderDialogStartValue(arousalModifier)
		SetSliderDialogDefaultValue(1.4)
		SetSliderDialogRange(1, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == keyLossChanceOID
		SetSliderDialogStartValue(keyLossChance)
		SetSliderDialogDefaultValue(80.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == keyChanceOID
		SetSliderDialogStartValue(keyChance)
		SetSliderDialogDefaultValue(7.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == keyBonusOID
		SetSliderDialogStartValue(keyBonus)
		SetSliderDialogDefaultValue(1.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == keyPickpocketBonusOID
		SetSliderDialogStartValue(keyPickpocketBonus)
		SetSliderDialogDefaultValue(2.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == magicKeyChanceOID
		SetSliderDialogStartValue(magicKeyChance)
		SetSliderDialogDefaultValue(10.0)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == eventContraptionTimeOID
		SetSliderDialogStartValue(eventContraptionTime)
		SetSliderDialogDefaultValue(4.0)
		SetSliderDialogRange(0, 24)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == LMBrandingChanceOID
		SetSliderDialogStartValue(LMBrandingChance)
		SetSliderDialogDefaultValue(1.5)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == LMBondageChanceOID
		SetSliderDialogStartValue(LMBondageChance)
		SetSliderDialogDefaultValue(5.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == oppSummonChanceOID
		SetSliderDialogStartValue(oppSummonChance)
		SetSliderDialogDefaultValue(1.5)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == oppLivingLatexMoreOID
		SetSliderDialogStartValue(oppLivingLatexMore)
		SetSliderDialogDefaultValue(0.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == playerHomeModifierOID
		SetSliderDialogStartValue(playerHomeModifier)
		SetSliderDialogDefaultValue(0.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == cityModifierOID
		SetSliderDialogStartValue(cityModifier)
		SetSliderDialogDefaultValue(0.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == townModifierOID
		SetSliderDialogStartValue(townModifier)
		SetSliderDialogDefaultValue(0.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == banditModifierOID
		SetSliderDialogStartValue(banditModifier)
		SetSliderDialogDefaultValue(1.1)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == draugrModifierOID
		SetSliderDialogStartValue(draugrModifier)
		SetSliderDialogDefaultValue(1.2)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == lockedLocationBypassOID
		SetSliderDialogStartValue(lockedLocationBypass)
		SetSliderDialogDefaultValue(0.6)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == theftLocationBypassOID
		SetSliderDialogStartValue(theftLocationBypass)
		SetSliderDialogDefaultValue(1.1)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == dwarvenModifierOID
		SetSliderDialogStartValue(dwarvenModifier)
		SetSliderDialogDefaultValue(1.2)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == falmerModifierOID
		SetSliderDialogStartValue(falmerModifier)
		SetSliderDialogDefaultValue(1.3)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == forswornModifierOID
		SetSliderDialogStartValue(forswornModifier)
		SetSliderDialogDefaultValue(1.1)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == vampireModifierOID
		SetSliderDialogStartValue(vampireModifier)
		SetSliderDialogDefaultValue(1.5)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == warlockModifierOID
		SetSliderDialogStartValue(warlockModifier)
		SetSliderDialogDefaultValue(1.5)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == dragonLairModifierOID
		SetSliderDialogStartValue(dragonLairModifier)
		SetSliderDialogDefaultValue(2.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == apocryphaModifierOID
		SetSliderDialogStartValue(apocryphaModifier)
		SetSliderDialogDefaultValue(2.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == wildernessModifierOID
		SetSliderDialogStartValue(wildernessModifier)
		SetSliderDialogDefaultValue(0.9)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == rDeviceBaseChanceOID
		SetSliderDialogStartValue(rDeviceBaseChance)
		SetSliderDialogDefaultValue(1.5)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == tatSolventChanceOID
		SetSliderDialogStartValue(tatSolventChance)
		SetSliderDialogDefaultValue(0.5)
		SetSliderDialogRange(0, 50)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == consTriggerNudeOID
		SetSliderDialogStartValue(consTriggerNude)
		SetSliderDialogDefaultValue(15.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == consTriggerRestrainedOID
		SetSliderDialogStartValue(consTriggerRestrained)
		SetSliderDialogDefaultValue(50.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == consTriggerSexOID
		SetSliderDialogStartValue(consTriggerSex)
		SetSliderDialogDefaultValue(10.0)
		SetSliderDialogRange(0, 100)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == sexArousalTattooModifierOID
		SetSliderDialogStartValue(sexArousalTattooModifier)
		SetSliderDialogDefaultValue(1.0)
		SetSliderDialogRange(0, 10)
		SetSliderDialogInterval(0.1)
		Return
	Endif
	If option == sexSearchRadiusOID
		SetSliderDialogStartValue(sexSearchRadius)
		SetSliderDialogDefaultValue(2000.0)
		SetSliderDialogRange(100, 10000)
		SetSliderDialogInterval(100)
		Return
	Endif
EndEvent

Event OnOptionSliderAccept(int option, float value)

	If option == minGoldRequiredOID
		minGoldRequired = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventScalingModOID
		eventScalingMod = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == minRestraintsOID
		minRestraints = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == maxRestraintsOID
		maxRestraints = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == bossAditionalRestraintsOID
		bossAditionalRestraints = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == restraintCapOID
		restraintCap = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == minArousalOID
		minArousal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == beltWeightOID
		beltWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == braWeightOID
		braWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == plugsWeightOID
		plugsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == lockingPlugsWeightOID
		lockingPlugsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == inflatablePlugsWeightOID
		inflatablePlugsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == nipplePiercingsWeightOID
		nipplePiercingsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == vaginalPiercingsWeightOID
		vaginalPiercingsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == corsetWeightOID
		corsetWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == beltedCorsetsWeightOID
		beltedCorsetsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == slaveHarnessWeightOID
		slaveHarnessWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == chastityHarnessWeightOID
		chastityHarnessWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == armbinderWeightOID
		armbinderWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == elbowbinderWeightOID
		elbowbinderWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == yokeWeightOID
		yokeWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == shacklesWeightOID
		shacklesWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == straitjacketWeightOID
		straitjacketWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == straitjacketLegbinderWeightOID
		straitjacketLegbinderWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == petSuitWeightOID
		petSuitWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == collarWeightOID
		collarWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == armCuffsWeightOID
		armCuffsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == legCuffsWeightOID
		legCuffsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == gagWeightOID
		gagWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == ringGagWeightOID
		ringGagWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == largeGagWeightOID
		largeGagWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == largeRingGagWeightOID
		largeRingGagWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == blindfoldWeightOID
		blindfoldWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hoodBothWeightOID
		hoodBothWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hoodGagWeightOID
		hoodGagWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hoodBlindWeightOID
		hoodBlindWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hoodNoneWeightOID
		hoodNoneWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == catsuitWeightOID
		catsuitWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hobbleSkirtWeightOID
		hobbleSkirtWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == hobbleSkirtDifficultyOID
		hobbleSkirtDifficulty = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == bootsWeightOID
		bootsWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == glovesWeightOID
		glovesWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == mittensWeightOID
		mittensWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == minKeysLootedOID
		minKeysLooted = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == maxKeysLootedOID
		maxKeysLooted = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == maxHeldKeysOID
		maxHeldKeys = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == restraintsKeyWeightOID
		restraintsKeyWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == chastityKeyWeightOID
		chastityKeyWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == piercingToolWeightOID
		piercingToolWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventStandardWeightOID
		eventStandardWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventStandardBossReductionOID
		eventStandardBossReduction = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventOppressiveWeightOID
		eventOppressiveWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventContraptionWeightOID
		eventContraptionWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventContDeviceOverrideOID
		eventContDeviceOverride = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventTattooWeightOID
		eventTattooWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventTattooMinOID
		eventTattooMin = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventTattooMaxOID
		eventTattooMax = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventTattooCapOID
		eventTattooCap = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventLewdMarkWeightOID
		eventLewdMarkWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == eventSimpleSlaveryWeightOID
		eventSimpleSlaveryWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		ForcePageReset()
		Return
	Endif
	If option == eventSSMinRestraintsOID
		eventSSMinRestraints = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMAllureWeightOID
		LMAllureWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMAllureModOID
		LMAllureMod = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMAllureSexOID
		LMAllureSex = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMHeatWeightOID
		LMHeatWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMHeatModOID
		LMHeatMod = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMHeatContainerCountOID
		LMHeatContainerCount = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMBrandingWeightOID
		LMBrandingWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMBrndingTotalOID
		LMBrndingTotal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMBondageWeightOID
		LMBondageWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMBondageDeviceCountOID
		LMBondageDeviceCount = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMNudityWeightOID
		LMNudityWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == LMNudityTalkTimesOID
		LMNudityTalkTimes = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppSummonerCollarWeightOID
		oppSummonerCollarWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppSummonerSexCountOID
		oppSummonerSexCount = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppSMinSummonArousalOID
		oppSMinSummonArousal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppDwarvenCuirassWeightOID
		oppDwarvenCuirassWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppDwarvenValueNeededOID
		oppDwarvenValueNeeded = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppDwarvenArousalOID
		oppDwarvenArousal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppLivingLatexWeightOID
		oppLivingLatexWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == oppLivingLatexStartTimeOID
		oppLivingLatexStartTime = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == consSexWeightOID
		consSexWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == consFineWeightOID
		consFineWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == consFineAmountOID
		consFineAmount = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == consRandomBondageWeightOID
		consRandomBondageWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == consMercyWeightOID
		consMercyWeight = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexCooldownOID
		sexCooldown = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexChanceOID
		sexChance = value as int
		SetSliderOptionValue(option, value, "{0}%")
		
		Return
	Endif
	If option == sexChanceCreatureOID
		sexChanceCreature = value as int
		SetSliderOptionValue(option, value, "{0}%")
		
		Return
	Endif
	If option == sexBaseArousalOID
		sexBaseArousal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexArousalNightModifierOID
		sexArousalNightModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalNudeModifierOID
		sexArousalNudeModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalCollarModifierOID
		sexArousalCollarModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalHeavyModifierOID
		sexArousalHeavyModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalBlindModifierOID
		sexArousalBlindModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalBootsModifierOID
		sexArousalBootsModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalHobbleModifierOID
		sexArousalHobbleModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalVisibleModifierOID
		sexArousalVisibleModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalCreatureModifierOID
		sexArousalCreatureModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalFollowerModifierOID
		sexArousalFollowerModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalSpouseModifierOID
		sexArousalSpouseModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexArousalSummonModifierOID
		sexArousalSummonModifier = value as int
		SetSliderOptionValue(option, value, "-{0}")
		
		Return
	Endif
	If option == sexSearchIntervalOID
		sexSearchInterval = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexRequiredPlayerArousalOID
		sexRequiredPlayerArousal = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexRequiredPlayerTattoosOID
		sexRequiredPlayerTattoos = value as int
		SetSliderOptionValue(option, value, "{0}")
		
		Return
	Endif
	If option == sexChanceFollowerOID
		sexChanceFollower = value as int
		SetSliderOptionValue(option, value, "{0}%")
		
		Return
	Endif
	If option == sexChanceSpouseOID
		sexChanceSpouse = value as int
		SetSliderOptionValue(option, value, "{0}%")
		
		Return
	Endif
	If option == sexChanceSummonOID
		sexChanceSummon = value as int
		SetSliderOptionValue(option, value, "{0}%")
		
		Return
	Endif
	If option == baseChanceOID
		baseChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == containerModifierOID
		containerModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == bossContainerModifierOID
		bossContainerModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == deadBodyModifierOID
		deadBodyModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == pickpocketModifierOID
		pickpocketModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == doorModifierOID
		doorModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == lockedModifierOID
		lockedModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == lockDifficultyModifierOID
		lockDifficultyModifier = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == arousalModifierOID
		arousalModifier = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == keyLossChanceOID
		keyLossChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == keyChanceOID
		keyChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == keyBonusOID
		keyBonus = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == keyPickpocketBonusOID
		keyPickpocketBonus = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == magicKeyChanceOID
		magicKeyChance = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == eventContraptionTimeOID
		eventContraptionTime = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == LMBrandingChanceOID
		LMBrandingChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == LMBondageChanceOID
		LMBondageChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == oppSummonChanceOID
		oppSummonChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == oppLivingLatexMoreOID
		oppLivingLatexMore = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == playerHomeModifierOID
		playerHomeModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == cityModifierOID
		cityModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == townModifierOID
		townModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == banditModifierOID
		banditModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == draugrModifierOID
		draugrModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == lockedLocationBypassOID
		lockedLocationBypass = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == theftLocationBypassOID
		theftLocationBypass = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == dwarvenModifierOID
		dwarvenModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == falmerModifierOID
		falmerModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == forswornModifierOID
		forswornModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == vampireModifierOID
		vampireModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == warlockModifierOID
		warlockModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == dragonLairModifierOID
		dragonLairModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == apocryphaModifierOID
		apocryphaModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == wildernessModifierOID
		wildernessModifier = value
		SetSliderOptionValue(option, value, "{1}x")
		Return
	Endif
	If option == rDeviceBaseChanceOID
		rDeviceBaseChance = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == tatSolventChanceOID
		tatSolventChance = value
		SetSliderOptionValue(option, value, "{1}")
		Return
	Endif
	If option == consTriggerNudeOID
		consTriggerNude = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == consTriggerRestrainedOID
		consTriggerRestrained = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == consTriggerSexOID
		consTriggerSex = value
		SetSliderOptionValue(option, value, "{1}%")
		Return
	Endif
	If option == sexArousalTattooModifierOID
		sexArousalTattooModifier = value
		SetSliderOptionValue(option, value, "-{1}")
		Return
	Endif
	If option == sexSearchRadiusOID
		sexSearchRadius = value
		SetSliderOptionValue(option, value, "{0}")
		Return
	Endif
EndEvent

Event OnOptionInputOpen(int option)
	If option == LMNudityAditionalFormsOID
		SetInputDialogStartText(LMNudityAditionalForms)
		Return
	Endif
EndEvent

Event OnOptionInputAccept(int option, string value)

	If option == LMNudityAditionalFormsOID
		LMNudityAditionalForms = value
		SetInputOptionValue(option, value)
		Return
	Endif
EndEvent

Event OnOptionColorOpen(int option)
	If option == LMAllureColorOID
		SetColorDialogStartColor(LMAllureColor)
		SetColorDialogDefaultColor(0xcf11c5)
		Return
	Endif
	If option == LMHeatColorOID
		SetColorDialogStartColor(LMHeatColor)
		SetColorDialogDefaultColor(0xe3143a)
		Return
	Endif
	If option == LMBrandingColorOID
		SetColorDialogStartColor(LMBrandingColor)
		SetColorDialogDefaultColor(0x220022)
		Return
	Endif
	If option == LMBondageColorOID
		SetColorDialogStartColor(LMBondageColor)
		SetColorDialogDefaultColor(0x7908cf)
		Return
	Endif
	If option == LMNudityColorOID
		SetColorDialogStartColor(LMNudityColor)
		SetColorDialogDefaultColor(0xd676cb)
		Return
	Endif
EndEvent

Event OnOptionColorAccept(int option, int color)
	If option == LMAllureColorOID
		LMAllureColor = color as int
		SetColorOptionValue(option, color)
		Return
	Endif
	If option == LMHeatColorOID
		LMHeatColor = color as int
		SetColorOptionValue(option, color)
		Return
	Endif
	If option == LMBrandingColorOID
		LMBrandingColor = color as int
		SetColorOptionValue(option, color)
		Return
	Endif
	If option == LMBondageColorOID
		LMBondageColor = color as int
		SetColorOptionValue(option, color)
		Return
	Endif
	If option == LMNudityColorOID
		LMNudityColor = color as int
		SetColorOptionValue(option, color)
		Return
	Endif
EndEvent