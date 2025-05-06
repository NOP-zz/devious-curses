;THIS SCRIPT IS AUTO GENERATED
Scriptname DCurses_MCM extends SKI_ConfigBase

function UpdateSKSE() global Native
bool function CheckSTNG() global Native
bool function CheckLM() global Native

Function StartTimer()
	Debug.trace("DCurses Timer Started")
	UnregisterForUpdate()
	RegisterForUpdate(1)
	RegisterForModEvent("HookAnimationStart", "OnSexStart")
	RegisterForModEvent("HookAnimationEnd", "OnSexEnd")
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
Float Property eventContraptionTime = 0.0 Auto
Int eventContraptionTimeOID
Float Property LMBrandingChance = 1.5 Auto
Int LMBrandingChanceOID
Float Property LMBondageChance = 5.0 Auto
Int LMBondageChanceOID
Float Property oppSummonChance = 1.5 Auto
Int oppSummonChanceOID
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
Bool Property LMBrandingPunish = true Auto
Int LMBrandingPunishOID
Bool Property LMNudityChestOnly = false Auto
Int LMNudityChestOnlyOID
Bool Property oppSCollarDrainsMagicka = true Auto
Int oppSCollarDrainsMagickaOID
Bool Property useLocationModifiers = true Auto
Int useLocationModifiersOID
Bool Property enableQuestInteractions = true Auto
Int enableQuestInteractionsOID
Bool Property enableQISaarthal = true Auto
Int enableQISaarthalOID
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
Bool Property setAllDefaultSettings = false Auto
Int setAllDefaultSettingsOID
Bool Property consAllowFollowers = false Auto
Int consAllowFollowersOID
Bool Property consUseRelationships = true Auto
Int consUseRelationshipsOID
Bool Property consRelationBondage = false Auto
Int consRelationBondageOID
Bool Property consRandomHeavyBondage = false Auto
Int consRandomHeavyBondageOID
Bool Property sexEnabled = false Auto
Int sexEnabledOID
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
	Pages[0] = "Main "
	Pages[1] = "Devices "
	Pages[2] = "Keys "
	Pages[3] = "Events "
	Pages[4] = "Lewd Marks "
	Pages[5] = "Oppressive Devices "
	Pages[6] = "Locations "
	Pages[7] = "Quest Interactions "
	Pages[8] = "Misc "
	Pages[9] = "Consequences "
	Pages[10] = "Sex "
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
	If page == "" || page == "Main "
		AddHeaderOption("Chances ")
		baseChanceOID = AddSliderOption("Base Event Chance  ", baseChance, "{1}%", 0)
		containerModifierOID = AddSliderOption("Container Modifier  ", containerModifier, "{1}x", 0)
		bossContainerModifierOID = AddSliderOption("Boss Chest Modifier  ", bossContainerModifier, "{1}x", 0)
		deadBodyModifierOID = AddSliderOption("Dead Body Modifier  ", deadBodyModifier, "{1}x", 0)
		pickpocketModifierOID = AddSliderOption("Pickpocket Modifier  ", pickpocketModifier, "{1}x", 0)
		doorModifierOID = AddSliderOption("Door Modifier  ", doorModifier, "{1}x", 0)
		onlyLockedDoorsOID = AddToggleOption("Only Locked Doors  ", onlyLockedDoors, 0)
		lockedModifierOID = AddSliderOption("Locked Modifier  ", lockedModifier, "{1}x", 0)
		lockDifficultyModifierOID = AddSliderOption("Lock Difficulty Modifier  ", lockDifficultyModifier, "{1}", 0)
		eventScalingOID = AddToggleOption("Event Scaling  ", eventScaling, 0)
		eventScalingModOID = AddSliderOption("Event Scaling Target  ", eventScalingMod, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("Parameters ")
		minRestraintsOID = AddSliderOption("Min Restraints  ", minRestraints, "{0}", 0)
		maxRestraintsOID = AddSliderOption("Max Restraints  ", maxRestraints, "{0}", 0)
		bossAditionalRestraintsOID = AddSliderOption("Boss Restraints  ", bossAditionalRestraints, "{0}", 0)
		bossOnlyHeavyOID = AddToggleOption("Boss Heavy Restraints  ", bossOnlyHeavy, 0)
		restraintCapOID = AddSliderOption("Restraints Cap  ", restraintCap, "{0}", 0)
		stripPlayerOnEventOID = AddToggleOption("Strip Player  ", stripPlayerOnEvent, 0)
		AddHeaderOption("Arousal ")
		arousalModifierOID = AddSliderOption("Arousal Modifier  ", arousalModifier, "{1}", 0)
		minArousalOID = AddSliderOption("Minimum Arousal  ", minArousal, "{0}", 0)
	Elseif page == "Devices "
		AddHeaderOption("Chastity ")
		beltWeightOID = AddSliderOption("Belts Weight  ", beltWeight, "{0}", 0)
		beltPlugsOID = AddToggleOption("Belt Plugs  ", beltPlugs, 0)
		noBeltPiercingOID = AddToggleOption("No Chastity Piercings  ", noBeltPiercing, 0)
		braWeightOID = AddSliderOption("Bras Weight  ", braWeight, "{0}", 0)
		plugsWeightOID = AddSliderOption("Plugs Weight  ", plugsWeight, "{0}", 0)
		lockingPlugsWeightOID = AddSliderOption("Locking Plugs Weight  ", lockingPlugsWeight, "{0}", 0)
		inflatablePlugsWeightOID = AddSliderOption("Inflatable Plugs Weight  ", inflatablePlugsWeight, "{0}", 0)
		plugsDontCountOID = AddToggleOption("Free Plugs  ", plugsDontCount, 0)
		AddHeaderOption("Piercings ")
		nipplePiercingsWeightOID = AddSliderOption("Nipple Piercings Weight  ", nipplePiercingsWeight, "{0}", 0)
		vaginalPiercingsWeightOID = AddSliderOption("Vaginal Piercing Weight  ", vaginalPiercingsWeight, "{0}", 0)
		AddHeaderOption("Corsets & Harnesses ")
		corsetWeightOID = AddSliderOption("Corset Weight  ", corsetWeight, "{0}", 0)
		beltedCorsetsWeightOID = AddSliderOption("Belted Corset Weight  ", beltedCorsetsWeight, "{0}", 0)
		slaveHarnessWeightOID = AddSliderOption("Open Harness Weight  ", slaveHarnessWeight, "{0}", 0)
		chastityHarnessWeightOID = AddSliderOption("Chastity Harness Weight  ", chastityHarnessWeight, "{0}", 0)
		AddHeaderOption("Heavy Bondage ")
		armbinderWeightOID = AddSliderOption("Armbinder Weight  ", armbinderWeight, "{0}", 0)
		elbowbinderWeightOID = AddSliderOption("Elbowbinder Weight  ", elbowbinderWeight, "{0}", 0)
		yokeWeightOID = AddSliderOption("Yoke Weight  ", yokeWeight, "{0}", 0)
		shacklesWeightOID = AddSliderOption("Shackles Weight  ", shacklesWeight, "{0}", 0)
		straitjacketWeightOID = AddSliderOption("Straitjacket Weight  ", straitjacketWeight, "{0}", 0)
		straitjacketLegbinderWeightOID = AddSliderOption("Hobbling Straitjacket Weight  ", straitjacketLegbinderWeight, "{0}", 0)
		petSuitWeightOID = AddSliderOption("Pet Suit Weight  ", petSuitWeight, "{0}", 0)
		SetCursorPosition(1)
		AddHeaderOption("Unforgiving Devices ")
		onlyUseUnforgivingDevicesOID = AddToggleOption("Only Unforgiving Devices  ", onlyUseUnforgivingDevices, flag_UnforgivingDevices)
		AddHeaderOption("Collars & Cuffs ")
		collarWeightOID = AddSliderOption("Collar Weight  ", collarWeight, "{0}", 0)
		armCuffsWeightOID = AddSliderOption("Arm Cuffs Weight  ", armCuffsWeight, "{0}", 0)
		legCuffsWeightOID = AddSliderOption("Leg Cuffs Weight  ", legCuffsWeight, "{0}", 0)
		allowLegShacklesOID = AddToggleOption("Leg Shackles  ", allowLegShackles, 0)
		AddHeaderOption("Gags & Blindfolds ")
		gagWeightOID = AddSliderOption("Gag Weight  ", gagWeight, "{0}", 0)
		ringGagWeightOID = AddSliderOption("Ring Gag Weight  ", ringGagWeight, "{0}", 0)
		largeGagWeightOID = AddSliderOption("Large Gag Weight  ", largeGagWeight, "{0}", 0)
		largeRingGagWeightOID = AddSliderOption("Large Ring Gag Weight  ", largeRingGagWeight, "{0}", 0)
		blindfoldWeightOID = AddSliderOption("Blindfold Weight  ", blindfoldWeight, "{0}", 0)
		hoodBothWeightOID = AddSliderOption("Hood Weight  ", hoodBothWeight, "{0}", 0)
		hoodGagWeightOID = AddSliderOption("Open Eyes Hood Weight  ", hoodGagWeight, "{0}", 0)
		hoodBlindWeightOID = AddSliderOption("Open Mouth Hood Weight  ", hoodBlindWeight, "{0}", 0)
		hoodNoneWeightOID = AddSliderOption("Open Hood Weight  ", hoodNoneWeight, "{0}", 0)
		AddHeaderOption("Body ")
		catsuitWeightOID = AddSliderOption("Catsuit Weight  ", catsuitWeight, "{0}", 0)
		hobbleSkirtWeightOID = AddSliderOption("Hobble Dress Weight  ", hobbleSkirtWeight, "{0}", 0)
		hobbleSkirtDifficultyOID = AddSliderOption("Hobble Dress Difficulty  ", hobbleSkirtDifficulty, "{0}", 0)
		bootsWeightOID = AddSliderOption("Boots Weight  ", bootsWeight, "{0}", 0)
		glovesWeightOID = AddSliderOption("Gloves Weight  ", glovesWeight, "{0}", 0)
		mittensWeightOID = AddSliderOption("Mittens Weight  ", mittensWeight, "{0}", 0)
	Elseif page == "Keys "
		keyLossChanceOID = AddSliderOption("Key Loss Chance  ", keyLossChance, "{1}%", 0)
		keyChanceOID = AddSliderOption("Key Find Chance  ", keyChance, "{1}%", 0)
		keyBonusOID = AddSliderOption("Bonus Chance Per Device  ", keyBonus, "{1}%", 0)
		keyForgivenessOID = AddToggleOption("Key Forgiveness  ", keyForgiveness, 0)
		keyPickpocketBonusOID = AddSliderOption("Pickpocket Bonus  ", keyPickpocketBonus, "{1}x", 0)
		maxHeldKeysOID = AddSliderOption("Max Held Keys  ", maxHeldKeys, "{0}", 0)
		SetCursorPosition(1)
		restraintsKeyWeightOID = AddSliderOption("Restraints Key Weight  ", restraintsKeyWeight, "{0}", 0)
		chastityKeyWeightOID = AddSliderOption("Chastity Key Weight  ", chastityKeyWeight, "{0}", 0)
		piercingToolWeightOID = AddSliderOption("Piercing Tool Weight  ", piercingToolWeight, "{0}", 0)
		AddEmptyOption()
		magicKeyChanceOID = AddSliderOption("Magic Key Chance  ", magicKeyChance, "{1}", 0)
		preferRelevantKeysOID = AddToggleOption("Prefer Relevant Keys  ", preferRelevantKeys, 0)
		vanishingKeysOID = AddToggleOption("Vanishing Keys  ", vanishingKeys, 0)
	Elseif page == "Events "
		AddHeaderOption("Bondage Curse ")
		eventStandardWeightOID = AddSliderOption("Bondage Curse Weight  ", eventStandardWeight, "{0}", 0)
		eventStandardBossReductionOID = AddSliderOption("Standard Boss Reduction  ", eventStandardBossReduction, "{0}", 0)
		AddHeaderOption("Oppresive Curse ")
		eventOppressiveWeightOID = AddSliderOption("Oppressive Curse Weight  ", eventOppressiveWeight, "{0}", 0)
		AddHeaderOption("Contraption Curse ")
		eventContraptionWeightOID = AddSliderOption("Contraption Curse Weight  ", eventContraptionWeight, "{0}", 0)
		eventContraptionTimeOID = AddSliderOption("Contraption Release Time  ", eventContraptionTime, "{1}", 0)
		AddHeaderOption("Tattoo Curse ")
		eventTattooWeightOID = AddSliderOption("Tattoo Curse Weight  ", eventTattooWeight, "{0}", flag_RapeTats)
		eventTattooMinOID = AddSliderOption("Tattoo Curse Min  ", eventTattooMin, "{0}", flag_RapeTats)
		eventTattooMaxOID = AddSliderOption("Tattoo Curse Max  ", eventTattooMax, "{0}", flag_RapeTats)
		eventTattooCapOID = AddSliderOption("Tattoo Curse Cap  ", eventTattooCap, "{0}", flag_RapeTats)
		AddHeaderOption("Mark Curse ")
		eventLewdMarkWeightOID = AddSliderOption("Lewd Mark Weight  ", eventLewdMarkWeight, "{0}", flag_LewdMarks)
		AddHeaderOption("Slavery Curse ")
		eventSimpleSlaveryWeightOID = AddSliderOption("Simple Slavery Weight  ", eventSimpleSlaveryWeight, "{0}", flag_SimpleSlavery)
		eventSSMinRestraintsOID = AddSliderOption("Minimum Restraints  ", eventSSMinRestraints, "{0}", flag_SSEnabled)
	Elseif page == "Lewd Marks "
		AddHeaderOption("Allure ")
		LMAllureWeightOID = AddSliderOption("Allure Mark Weight  ", LMAllureWeight, "{0}", flag_LewdMarks)
		LMAllureModOID = AddSliderOption("Allure Arousal  ", LMAllureMod, "{0}", flag_LewdMarks)
		LMAllureSexOID = AddSliderOption("Sex Count  ", LMAllureSex, "{0}", flag_LewdMarks)
		LMAllureColorOID = AddColorOption("Color  ", LMAllureColor, flag_LewdMarks)
		AddHeaderOption("Heat ")
		LMHeatWeightOID = AddSliderOption("Heat Mark  ", LMHeatWeight, "{0}", flag_LewdMarks)
		LMHeatModOID = AddSliderOption("Heat Arousal  ", LMHeatMod, "{0}", flag_LewdMarks)
		LMHeatContainerCountOID = AddSliderOption("Container Count  ", LMHeatContainerCount, "{0}", flag_LewdMarks)
		LMHeatColorOID = AddColorOption("Color  ", LMHeatColor, flag_LewdMarks)
		AddHeaderOption("Branding ")
		LMBrandingWeightOID = AddSliderOption("Branding Mark  ", LMBrandingWeight, "{0}", flag_LewdMarks)
		LMBrandingChanceOID = AddSliderOption("Chance  ", LMBrandingChance, "{1}%", flag_RT_LM)
		LMBrndingTotalOID = AddSliderOption("Total Tattoos  ", LMBrndingTotal, "{0}", flag_LewdMarks)
		LMBrandingPunishOID = AddToggleOption("Punishment  ", LMBrandingPunish, flag_LewdMarks)
		LMBrandingColorOID = AddColorOption("Color  ", LMBrandingColor, flag_LewdMarks)
		SetCursorPosition(1)
		AddHeaderOption("Bondage ")
		LMBondageWeightOID = AddSliderOption("Bondage Mark  ", LMBondageWeight, "{0}", flag_LewdMarks)
		LMBondageChanceOID = AddSliderOption("Chance  ", LMBondageChance, "{1}%", flag_LewdMarks)
		LMBondageDeviceCountOID = AddSliderOption("Device Count  ", LMBondageDeviceCount, "{0}", flag_LewdMarks)
		LMBondageColorOID = AddColorOption("Color  ", LMBondageColor, flag_LewdMarks)
		AddHeaderOption("Nudity ")
		int flag_LMStripBody = 1
		If LMNudityChestOnly && flag_LewdMarks == 0
			flag_LMStripBody = 0
		EndIf
		LMNudityWeightOID = AddSliderOption("Nudity Mark  ", LMNudityWeight, "{0}", flag_LewdMarks)
		LMNudityChestOnlyOID = AddToggleOption("Chest Only  ", LMNudityChestOnly, flag_LewdMarks)
		LMNudityAditionalFormsOID = AddInputOption("Strip Slots  ", LMNudityAditionalForms, flag_LMStripBody)
		LMNudityTalkTimesOID = AddSliderOption("Dialogue Times  ", LMNudityTalkTimes, "{0}", flag_LewdMarks)
		LMNudityColorOID = AddColorOption("Color  ", LMNudityColor, flag_LewdMarks)
	Elseif page == "Oppressive Devices "
		AddHeaderOption("Summoner Collar ")
		oppSummonerCollarWeightOID = AddSliderOption("Weight  ", oppSummonerCollarWeight, "{0}", 0)
		oppSummonerSexCountOID = AddSliderOption("Sex Count  ", oppSummonerSexCount, "{0}", 0)
		oppSCollarDrainsMagickaOID = AddToggleOption("Magicka Drain  ", oppSCollarDrainsMagicka, 0)
		oppSMinSummonArousalOID = AddSliderOption("Summon Arousal  ", oppSMinSummonArousal, "{0}", 0)
		oppSummonChanceOID = AddSliderOption("Summon Chance  ", oppSummonChance, "{1}%", 0)
	Elseif page == "Locations "
		useLocationModifiersOID = AddToggleOption("Use Location Modifiers  ", useLocationModifiers, 0)
		AddEmptyOption()
		AddEmptyOption()
		playerHomeModifierOID = AddSliderOption("Player Home Modifier  ", playerHomeModifier, "{1}x", 0)
		cityModifierOID = AddSliderOption("City Modifier  ", cityModifier, "{1}x", 0)
		townModifierOID = AddSliderOption("Town Modifier  ", townModifier, "{1}x", 0)
		banditModifierOID = AddSliderOption("Bandit Modifier  ", banditModifier, "{1}x", 0)
		draugrModifierOID = AddSliderOption("Draugr Modifier  ", draugrModifier, "{1}x", 0)
		SetCursorPosition(1)
		lockedLocationBypassOID = AddSliderOption("Lock Bypass  ", lockedLocationBypass, "{1}x", 0)
		theftLocationBypassOID = AddSliderOption("Theft Bypass  ", theftLocationBypass, "{1}x", 0)
		AddEmptyOption()
		dwarvenModifierOID = AddSliderOption("Dwarven Modifier  ", dwarvenModifier, "{1}x", 0)
		falmerModifierOID = AddSliderOption("Falmer Modifier  ", falmerModifier, "{1}x", 0)
		forswornModifierOID = AddSliderOption("Forsworn Modifier  ", forswornModifier, "{1}x", 0)
		vampireModifierOID = AddSliderOption("Vampire Modifier  ", vampireModifier, "{1}x", 0)
		warlockModifierOID = AddSliderOption("Warlock Modifier  ", warlockModifier, "{1}x", 0)
		dragonLairModifierOID = AddSliderOption("Dragon Lair Modifier  ", dragonLairModifier, "{1}x", 0)
		apocryphaModifierOID = AddSliderOption("Apocrypha Modifier  ", apocryphaModifier, "{1}x", 0)
		wildernessModifierOID = AddSliderOption("Wilderness Modifier  ", wildernessModifier, "{1}x", 0)
	Elseif page == "Quest Interactions "
		int flag_enable_qi = 1
		If enableQuestInteractions
			flag_enable_qi = 0
		EndIf
		enableQuestInteractionsOID = AddToggleOption("Quest Interactions  ", enableQuestInteractions, 0)
		SetCursorPosition(1)
		AddHeaderOption("Quest Toggles ")
		enableQISaarthalOID = AddToggleOption("Saarthal  ", enableQISaarthal, 0)
		enableQIMalkoranOID = AddToggleOption("Malkoran  ", enableQIMalkoran, 0)
		enableQISanguineOID = AddToggleOption("Sanguine  ", enableQISanguine, 0)
	Elseif page == "Misc "
		noMessageBoxesOID = AddToggleOption("Remove Message Boxes  ", noMessageBoxes, 0)
		bossChestUseModelPathOID = AddToggleOption("Boss Chest Models  ", bossChestUseModelPath, 0)
		rDeviceBaseChanceOID = AddSliderOption("Device Base Chance  ", rDeviceBaseChance, "{1}%", 0)
		dragonHoardOID = AddToggleOption("Dragon Hoards  ", dragonHoard, 0)
		bossExtraGoldOID = AddToggleOption("Boss Chest Extra Gold  ", bossExtraGold, 0)
		useThemesOID = AddToggleOption("Use Device Themes  ", useThemes, 0)
		SetCursorPosition(1)
		enableSlowStripOID = AddToggleOption("Use Sexlab Strip  ", enableSlowStrip, 0)
		tatSolventChanceOID = AddSliderOption("Universal Solvent Chance  ", tatSolventChance, "{1}", 0)
		setAllDefaultSettingsOID = AddToggleOption("Return to Default [WARNING]  ", setAllDefaultSettings, 0)
	Elseif page == "Consequences "
		AddHeaderOption("Triggers ")
		consTriggerNudeOID = AddSliderOption("Nudity  ", consTriggerNude, "{1}%", 0)
		consTriggerRestrainedOID = AddSliderOption("Restrained  ", consTriggerRestrained, "{1}%", 0)
		consTriggerSexOID = AddSliderOption("Sex  ", consTriggerSex, "{1}%", 0)
		AddEmptyOption()
		consAllowFollowersOID = AddToggleOption("Allow Followers  ", consAllowFollowers, 0)
		AddEmptyOption()
		consUseRelationshipsOID = AddToggleOption("Use Relationships  ", consUseRelationships, 0)
		consRelationBondageOID = AddToggleOption("Relationship Bondage  ", consRelationBondage, 0)
		SetCursorPosition(1)
		AddHeaderOption("Results ")
		consSexWeightOID = AddSliderOption("Sex Weight  ", consSexWeight, "{0}", 0)
		AddEmptyOption()
		consFineWeightOID = AddSliderOption("Fine Weight  ", consFineWeight, "{0}", 0)
		consFineAmountOID = AddSliderOption("Fine Amount  ", consFineAmount, "{0}", 0)
		AddEmptyOption()
		consRandomBondageWeightOID = AddSliderOption("Random Bondage Weight  ", consRandomBondageWeight, "{0}", 0)
		consRandomHeavyBondageOID = AddToggleOption("Allow Heavy Bondage  ", consRandomHeavyBondage, 0)
		AddEmptyOption()
		consMercyWeightOID = AddSliderOption("Mercy Weight  ", consMercyWeight, "{0}", 0)
	Elseif page == "Sex "
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
		AddHeaderOption("General ")
		sexEnabledOID = AddToggleOption("Enabled  ", sexEnabled, 0)
		sexRandomEnabledOID = AddToggleOption("Random Sex  ", sexRandomEnabled, 0)
		sexCooldownOID = AddSliderOption("Cooldown  ", sexCooldown, "{0}", flag_enable_random_sex)
		sexChanceOID = AddSliderOption("Chance  ", sexChance, "{0}%", flag_enable_random_sex)
		sexChanceCreatureOID = AddSliderOption("Creature Chance  ", sexChanceCreature, "{0}%", flag_enable_random_sex)
		AddHeaderOption("Arousal ")
		sexBaseArousalOID = AddSliderOption("Base Arousal  ", sexBaseArousal, "{0}", flag_enable_random_sex)
		sexArousalNightModifierOID = AddSliderOption("Night Modifier  ", sexArousalNightModifier, "-{0}", flag_enable_random_sex)
		sexArousalNudeModifierOID = AddSliderOption("Nude Modifier  ", sexArousalNudeModifier, "-{0}", flag_enable_random_sex)
		sexArousalCollarModifierOID = AddSliderOption("Collar Modifier  ", sexArousalCollarModifier, "-{0}", flag_enable_random_sex)
		sexArousalHeavyModifierOID = AddSliderOption("Heavy Restraints Modifier  ", sexArousalHeavyModifier, "-{0}", flag_enable_random_sex)
		sexArousalBlindModifierOID = AddSliderOption("Blindfold Modifier  ", sexArousalBlindModifier, "-{0}", flag_enable_random_sex)
		sexArousalBootsModifierOID = AddSliderOption("Boots Modifier  ", sexArousalBootsModifier, "-{0}", flag_enable_random_sex)
		sexArousalHobbleModifierOID = AddSliderOption("Hobbled Modifier  ", sexArousalHobbleModifier, "-{0}", flag_enable_random_sex)
		sexArousalVisibleModifierOID = AddSliderOption("Visible Devices Modifier  ", sexArousalVisibleModifier, "-{0}", flag_enable_random_sex)
		sexArousalTattooModifierOID = AddSliderOption("Tattoo Modifier  ", sexArousalTattooModifier, "-{1}", flag_sex_slave_tats)
		sexArousalCreatureModifierOID = AddSliderOption("Creature Modifier  ", sexArousalCreatureModifier, "-{0}", flag_enable_random_sex)
		sexArousalFollowerModifierOID = AddSliderOption("Follower Modifier  ", sexArousalFollowerModifier, "-{0}", flag_enable_random_sex)
		sexArousalSpouseModifierOID = AddSliderOption("Spouse Modifier  ", sexArousalSpouseModifier, "-{0}", flag_enable_random_sex)
		sexArousalSummonModifierOID = AddSliderOption("Summon Modifier  ", sexArousalSummonModifier, "-{0}", flag_enable_random_sex)
		AddHeaderOption("Search ")
		sexSearchRadiusOID = AddSliderOption("Search Radius  ", sexSearchRadius, "{0}", flag_enable_random_sex)
		sexSearchIntervalOID = AddSliderOption("Search Interval  ", sexSearchInterval, "{0}", flag_enable_random_sex)
		SetCursorPosition(1)
		AddHeaderOption("Allowed Actors ")
		sexAllowMaleOID = AddToggleOption("Allow Male Actors  ", sexAllowMale, flag_enable_sex)
		sexAllowFemaleOID = AddToggleOption("Allow Female Actors  ", sexAllowFemale, flag_enable_sex)
		sexAllowFutaOID = AddToggleOption("Allow Futa Actors  ", sexAllowFuta, flag_enable_sex)
		sexAllowCreatureOID = AddToggleOption("Allow Creature Actors  ", sexAllowCreature, flag_enable_sex)
		AddHeaderOption("Requirements ")
		sexRequireAllOID = AddToggleOption("Require All  ", sexRequireAll, flag_enable_random_sex)
		sexRequireBindingsOID = AddToggleOption("Bondage  ", sexRequireBindings, flag_enable_random_sex)
		sexRequireCollarOID = AddToggleOption("Collar  ", sexRequireCollar, flag_enable_random_sex)
		sexRequireHeavyOID = AddToggleOption("Heavy Restraints  ", sexRequireHeavy, flag_enable_random_sex)
		sexRequireNudeOID = AddToggleOption("Nudity  ", sexRequireNude, flag_enable_random_sex)
		sexRequiredPlayerArousalOID = AddSliderOption("Player Arousal  ", sexRequiredPlayerArousal, "{0}", flag_enable_random_sex)
		sexRequiredPlayerTattoosOID = AddSliderOption("Player Tattoos  ", sexRequiredPlayerTattoos, "{0}", flag_sex_slave_tats)
		AddHeaderOption("Requirement Exceptions ")
		sexAlwaysAllowFollowersOID = AddToggleOption("Always Allow Followers  ", sexAlwaysAllowFollowers, flag_enable_random_sex)
		sexAlwaysAllowSpouseOID = AddToggleOption("Always Allow Spouse  ", sexAlwaysAllowSpouse, flag_enable_random_sex)
		sexAlwaysAllowSummonsOID = AddToggleOption("Always Allow Summons  ", sexAlwaysAllowSummons, flag_enable_random_sex)
		sexChanceFollowerOID = AddSliderOption("Follower Chance  ", sexChanceFollower, "{0}%", flag_enable_random_sex)
		sexChanceSpouseOID = AddSliderOption("Spouse Chance  ", sexChanceSpouse, "{0}%", flag_enable_random_sex)
		sexChanceSummonOID = AddSliderOption("Summon Chance  ", sexChanceSummon, "{0}%", flag_enable_random_sex)
	EndIf
EndEvent

Event OnOptionHighlight(int option)
	If option == baseChanceOID
		SetInfoText("How likely are you to trigger a trap before modifiers.")
		Return
	Endif
	If option == containerModifierOID
		SetInfoText("Modifier for containers.")
		Return
	Endif
	If option == bossContainerModifierOID
		SetInfoText("Modifier for boss chests.\nIs applied with the container modifier.")
		Return
	Endif
	If option == deadBodyModifierOID
		SetInfoText("Modifier for corpses.")
		Return
	Endif
	If option == pickpocketModifierOID
		SetInfoText("Modifier for pickpocketing.")
		Return
	Endif
	If option == doorModifierOID
		SetInfoText("Modifier for doors.")
		Return
	Endif
	If option == onlyLockedDoorsOID
		SetInfoText("Only trigger events when the door is locked.")
		Return
	Endif
	If option == lockedModifierOID
		SetInfoText("Modifier for locked doors and chests.\nThis will not apply if the lock requires a key or you already have the key to the lock.")
		Return
	Endif
	If option == lockDifficultyModifierOID
		SetInfoText("If this is greater than 1, locked things will have a higher chance to cause a curse the harder the lock is to pick.\nIf set to 10 a master level lock will multiply the chance by 10 while an adept lock would multiply the chance by 5.")
		Return
	Endif
	If option == eventScalingOID
		SetInfoText("Make events less likely right after triggering one, and more likely if not triggered in a while.")
		Return
	Endif
	If option == eventScalingModOID
		SetInfoText("The number of events before traps start becoming more likely.")
		Return
	Endif
	If option == minRestraintsOID
		SetInfoText("Minimum number of restraints.")
		Return
	Endif
	If option == maxRestraintsOID
		SetInfoText("Maximum number of restraints.")
		Return
	Endif
	If option == bossAditionalRestraintsOID
		SetInfoText("Added restraints when opening a boss chest.")
		Return
	Endif
	If option == bossOnlyHeavyOID
		SetInfoText("Heavy restraints can only be applied from boss chests.")
		Return
	Endif
	If option == restraintCapOID
		SetInfoText("Events won't happen if you have more than this many restraints.")
		Return
	Endif
	If option == stripPlayerOnEventOID
		SetInfoText("Toggle to choose if the player should be stripped on any event.\nIf a heavy bondage device is equipped the player will be stripped anyway.")
		Return
	Endif
	If option == arousalModifierOID
		SetInfoText("If this is greater than 1, curses will me more likely the more aroused the player is.\nIf set to 10 with full arousal will multiply the chance by 10 while half arousal would multiply the chance by 5.")
		Return
	Endif
	If option == minArousalOID
		SetInfoText("Curses won't trigger if the player is below this arousal level.")
		Return
	Endif
	If option == beltWeightOID
		SetInfoText("Chance to be equipped with a chastity belt.")
		Return
	Endif
	If option == beltPlugsOID
		SetInfoText("Equip plugs with all belts.")
		Return
	Endif
	If option == noBeltPiercingOID
		SetInfoText("Prevent chastity belts that also function as clitoral piercings. None of these devices exist within base DD.")
		Return
	Endif
	If option == braWeightOID
		SetInfoText("Chance to be equipped with a chastity bra.")
		Return
	Endif
	If option == plugsWeightOID
		SetInfoText("Chance to be equipped with plugs when no belt is worn.")
		Return
	Endif
	If option == lockingPlugsWeightOID
		SetInfoText("Chance to be equipped with plugs that can lock.")
		Return
	Endif
	If option == inflatablePlugsWeightOID
		SetInfoText("Chance to be equipped with plugs that are inflatable.")
		Return
	Endif
	If option == plugsDontCountOID
		SetInfoText("Plugs won't be considered for device limits.\nSo if a plug is rolled and the max devices is 1, another device can still be added.")
		Return
	Endif
	If option == nipplePiercingsWeightOID
		SetInfoText("Chance to be equipped with nipple piercings.")
		Return
	Endif
	If option == vaginalPiercingsWeightOID
		SetInfoText("Chance to be equipped with a vaginal piercing.")
		Return
	Endif
	If option == corsetWeightOID
		SetInfoText("Chance to be equipped with a restrictive corset.")
		Return
	Endif
	If option == beltedCorsetsWeightOID
		SetInfoText("Chance to be equipped with a restrictive corset that has an attached belt.")
		Return
	Endif
	If option == slaveHarnessWeightOID
		SetInfoText("Chance to be equipped with an open harness.\nThis will not act as a chastity belt.")
		Return
	Endif
	If option == chastityHarnessWeightOID
		SetInfoText("Chance to be equipped with an open harness.\nThis will act as a chastity belt.")
		Return
	Endif
	If option == armbinderWeightOID
		SetInfoText("Chance to be equipped with an armbinder.")
		Return
	Endif
	If option == elbowbinderWeightOID
		SetInfoText("Chance to be equipped with an elbowbinder.")
		Return
	Endif
	If option == yokeWeightOID
		SetInfoText("Chance to be equipped with a yoke.")
		Return
	Endif
	If option == shacklesWeightOID
		SetInfoText("Chance to be equipped with restraining wrist shackles.")
		Return
	Endif
	If option == straitjacketWeightOID
		SetInfoText("Chance to be equipped with a straitjacket.")
		Return
	Endif
	If option == straitjacketLegbinderWeightOID
		SetInfoText("Chance to be equipped with a straitjacket that has a legbinder.")
		Return
	Endif
	If option == petSuitWeightOID
		SetInfoText("Chance to be equipped with a pet suit.")
		Return
	Endif
	If option == onlyUseUnforgivingDevicesOID
		SetInfoText("Only register devices to the mod that are converted to work with UD.")
		Return
	Endif
	If option == collarWeightOID
		SetInfoText("Chance to be equipped with a collar.")
		Return
	Endif
	If option == armCuffsWeightOID
		SetInfoText("Chance to be equipped with arm cuffs.")
		Return
	Endif
	If option == legCuffsWeightOID
		SetInfoText("Chance to be equipped with leg cuffs.")
		Return
	Endif
	If option == allowLegShacklesOID
		SetInfoText("Allow leg cuffs that slow the player.")
		Return
	Endif
	If option == gagWeightOID
		SetInfoText("Chance to be equipped with a simple gag\nThese will always block oral.")
		Return
	Endif
	If option == ringGagWeightOID
		SetInfoText("Chance to be equipped with a ring gag\nThese will never block oral.")
		Return
	Endif
	If option == largeGagWeightOID
		SetInfoText("Chance to be equipped with a large gag\nThese will always block speech.")
		Return
	Endif
	If option == largeRingGagWeightOID
		SetInfoText("Chance to be equipped with a large ring gag\nThese will always block speech and never block oral.")
		Return
	Endif
	If option == blindfoldWeightOID
		SetInfoText("Chance to be equipped with a blindfold.")
		Return
	Endif
	If option == hoodBothWeightOID
		SetInfoText("Chance to be equipped with a hood.")
		Return
	Endif
	If option == hoodGagWeightOID
		SetInfoText("Chance to be equipped with a hood that only blocks the mouth.")
		Return
	Endif
	If option == hoodBlindWeightOID
		SetInfoText("Chance to be equipped with a hood that only blocks the eyes.")
		Return
	Endif
	If option == hoodNoneWeightOID
		SetInfoText("Chance to be equipped with a hood that doesn't block the mouth or eyes.")
		Return
	Endif
	If option == catsuitWeightOID
		SetInfoText("Chance to be equipped with a catsuit.")
		Return
	Endif
	If option == hobbleSkirtWeightOID
		SetInfoText("Chance to be equipped with a hobble dress.")
		Return
	Endif
	If option == hobbleSkirtDifficultyOID
		SetInfoText("How restraining hobble dresses will be on average.\nThe higher the number the greater chance for a strict dress vs a relaxed dress.")
		Return
	Endif
	If option == bootsWeightOID
		SetInfoText("Chance to be equipped with restrictive boots.")
		Return
	Endif
	If option == glovesWeightOID
		SetInfoText("Chance to be equipped with restrictive gloves.")
		Return
	Endif
	If option == mittensWeightOID
		SetInfoText("Chance to be equipped with bondage mittens.")
		Return
	Endif
	If option == keyLossChanceOID
		SetInfoText("How likely you are to lose your keys during an event.")
		Return
	Endif
	If option == keyChanceOID
		SetInfoText("How likely you are to find a key in a container.")
		Return
	Endif
	If option == keyBonusOID
		SetInfoText("A bonus chance to get a key per locking device worn.")
		Return
	Endif
	If option == keyForgivenessOID
		SetInfoText("Make keys more likely if it has been a while since you got any.")
		Return
	Endif
	If option == keyPickpocketBonusOID
		SetInfoText("Multiplier to key chance when pickpocketing someone.\nSet to 0 to disable keys when pickpocketing.")
		Return
	Endif
	If option == maxHeldKeysOID
		SetInfoText("Sets the maximum allowed amount of keys that you can carry while still finding more.\nWith this enabled no devices will be equipped that require more keys than you can find.\nFor example if you have two restraint keys and one chastity key and this is set to three you will no longer find keys.\nSet to 0 to disable.")
		Return
	Endif
	If option == restraintsKeyWeightOID
		SetInfoText("Chance to find a restraints key.")
		Return
	Endif
	If option == chastityKeyWeightOID
		SetInfoText("Chance to find a chastity key.")
		Return
	Endif
	If option == piercingToolWeightOID
		SetInfoText("Chance to find a piercing removal tool.")
		Return
	Endif
	If option == magicKeyChanceOID
		SetInfoText("Chance that magic keys will be found in boss chests. They will destroy all restraints you are wearing.\nYou can only have a max of one at a time and they can never be lost.\nSet to 0 to disable")
		Return
	Endif
	If option == preferRelevantKeysOID
		SetInfoText("You will only find keys that would unlock items you are wearing.")
		Return
	Endif
	If option == vanishingKeysOID
		SetInfoText("Keys will be removed from containers after you close the menu.")
		Return
	Endif
	If option == eventStandardWeightOID
		SetInfoText("Chance to receive a bondage device event.")
		Return
	Endif
	If option == eventStandardBossReductionOID
		SetInfoText("If the container is a boss chest, the standard event weight will be reduced by this amount.")
		Return
	Endif
	If option == eventOppressiveWeightOID
		SetInfoText("Chance to receive an oppressive device event.")
		Return
	Endif
	If option == eventContraptionWeightOID
		SetInfoText("Chance to be bound in a contraption from DDC.")
		Return
	Endif
	If option == eventContraptionTimeOID
		SetInfoText("Will be automatically released after this many in game hours. Set to 0 to disable automatic release.")
		Return
	Endif
	If option == eventTattooWeightOID
		SetInfoText("Chance to receive random tattoos.\nRequires Rape Tattoos.")
		Return
	Endif
	If option == eventTattooMinOID
		SetInfoText("Minimum number of tattoos that can be put on.")
		Return
	Endif
	If option == eventTattooMaxOID
		SetInfoText("Maximum number of tattoos that can be put on.")
		Return
	Endif
	If option == eventTattooCapOID
		SetInfoText("If you have this many tattoos already you won't get any more.")
		Return
	Endif
	If option == eventLewdMarkWeightOID
		SetInfoText("Chance to receive a lewd mark.")
		Return
	Endif
	If option == eventSimpleSlaveryWeightOID
		SetInfoText("Chance to trigger a Simple Slavery auction.")
		Return
	Endif
	If option == eventSSMinRestraintsOID
		SetInfoText("Minimum restraints that need to be equipped for a Simple Slavery auction to start.")
		Return
	Endif
	If option == LMAllureWeightOID
		SetInfoText("This mark will make everyone around you horny all the time.")
		Return
	Endif
	If option == LMAllureModOID
		SetInfoText("How much each nearby character's arousal will change per minute.")
		Return
	Endif
	If option == LMAllureSexOID
		SetInfoText("How many times you have to have sex before the mark will fade.")
		Return
	Endif
	If option == LMAllureColorOID
		SetInfoText("Color for mark.")
		Return
	Endif
	If option == LMHeatWeightOID
		SetInfoText("This mark will constantly make you horny.")
		Return
	Endif
	If option == LMHeatModOID
		SetInfoText("How much your arousal will change per minute.")
		Return
	Endif
	If option == LMHeatContainerCountOID
		SetInfoText("How many containers you must open before the mark will fade.")
		Return
	Endif
	If option == LMHeatColorOID
		SetInfoText("Color for mark.")
		Return
	Endif
	If option == LMBrandingWeightOID
		SetInfoText("This mark will force you to have a certain number of tattoos!")
		Return
	Endif
	If option == LMBrandingChanceOID
		SetInfoText("How likely you are to receive a random tattoo per 15 seconds.\nRequires Rape Tattoos")
		Return
	Endif
	If option == LMBrndingTotalOID
		SetInfoText("How many tattoos you need before the mark releases. The mark itself counts as 2.")
		Return
	Endif
	If option == LMBrandingPunishOID
		SetInfoText("You will be punished by loosing gold if your total tattoo count decreases.")
		Return
	Endif
	If option == LMBrandingColorOID
		SetInfoText("Color for mark.")
		Return
	Endif
	If option == LMBondageWeightOID
		SetInfoText("With this mark devices that are in your inventory might equip themselves.")
		Return
	Endif
	If option == LMBondageChanceOID
		SetInfoText("How likely an item might be equipped per 15 seconds.")
		Return
	Endif
	If option == LMBondageDeviceCountOID
		SetInfoText("How many devices need to be equipped before the mark will fade.")
		Return
	Endif
	If option == LMBondageColorOID
		SetInfoText("Color for mark.")
		Return
	Endif
	If option == LMNudityWeightOID
		SetInfoText("With this mark you will be unable to wear any clothes.")
		Return
	Endif
	If option == LMNudityChestOnlyOID
		SetInfoText("With this enabled only chest armor will be checked and removed. Otherwise all armor will be unequipped.")
		Return
	Endif
	If option == LMNudityAditionalFormsOID
		SetInfoText("A comma separated list of additional slots to strip. Will not strip devices.\nFor example: 46,47,49,52.")
		Return
	Endif
	If option == LMNudityTalkTimesOID
		SetInfoText("How many times you have to talk to different characters before the mark will fade.")
		Return
	Endif
	If option == LMNudityColorOID
		SetInfoText("Color for mark.")
		Return
	Endif
	If option == oppSummonerCollarWeightOID
		SetInfoText("How likely that you will be equipped with a collar that makes you have sex with your summons.\nRequires creatures to be enabled for sex.")
		Return
	Endif
	If option == oppSummonerSexCountOID
		SetInfoText("How may time you need to have sex with your summons before the collar will unlock.")
		Return
	Endif
	If option == oppSCollarDrainsMagickaOID
		SetInfoText("The collar will drain all of your magicka when summoning.")
		Return
	Endif
	If option == oppSMinSummonArousalOID
		SetInfoText("Will change the arousal of all of your summons to be at least this value.")
		Return
	Endif
	If option == oppSummonChanceOID
		SetInfoText("The chance per second that the collar summons an atronach to have sex with you.\nThis won't happen if you already have a different summon.")
		Return
	Endif
	If option == useLocationModifiersOID
		SetInfoText("Weather or not to apply the location modifiers listed below to event chances.")
		Return
	Endif
	If option == playerHomeModifierOID
		SetInfoText("Modifier for events to happen inside of player homes.")
		Return
	Endif
	If option == cityModifierOID
		SetInfoText("Modifier for events to happen inside of walled cities.")
		Return
	Endif
	If option == townModifierOID
		SetInfoText("Modifier for events to happen inside of towns.")
		Return
	Endif
	If option == banditModifierOID
		SetInfoText("Modifier for events to happen in or near bandit hideouts.")
		Return
	Endif
	If option == draugrModifierOID
		SetInfoText("Modifier for events to happen in draugr crypts.")
		Return
	Endif
	If option == lockedLocationBypassOID
		SetInfoText("Locked containers can't have a location modifier less than this setting.\nUseful to make locked containers still trigger traps in cities.")
		Return
	Endif
	If option == theftLocationBypassOID
		SetInfoText("Stealing from containers can't have a location modifier less than this setting.\nUseful to make stealing from containers still trigger traps in cities.")
		Return
	Endif
	If option == dwarvenModifierOID
		SetInfoText("Modifier for events to happen in dwarven ruins.")
		Return
	Endif
	If option == falmerModifierOID
		SetInfoText("Modifier for events to happen in falmer hives.")
		Return
	Endif
	If option == forswornModifierOID
		SetInfoText("Modifier for events to happen in forsworn hideouts.")
		Return
	Endif
	If option == vampireModifierOID
		SetInfoText("Modifier for events to happen in vampire lairs.")
		Return
	Endif
	If option == warlockModifierOID
		SetInfoText("Modifier for events to happen in warlock lairs.")
		Return
	Endif
	If option == dragonLairModifierOID
		SetInfoText("Modifier for events to happen in dragon lairs.")
		Return
	Endif
	If option == apocryphaModifierOID
		SetInfoText("Modifier for events to happen in apocrypha.")
		Return
	Endif
	If option == wildernessModifierOID
		SetInfoText("Modifier for events to happen in the wilderness.")
		Return
	Endif
	If option == enableQuestInteractionsOID
		SetInfoText("Certain quests may have some additional events tied to them.\n The mod page has more information about each quest.")
		Return
	Endif
	If option == enableQISaarthalOID
		SetInfoText("The Saarthal event.")
		Return
	Endif
	If option == enableQIMalkoranOID
		SetInfoText("The Malkoran event.")
		Return
	Endif
	If option == enableQISanguineOID
		SetInfoText("The Sanguine events.")
		Return
	Endif
	If option == noMessageBoxesOID
		SetInfoText("No message boxes will be shown.")
		Return
	Endif
	If option == bossChestUseModelPathOID
		SetInfoText("Use the model of chests to determine if they are a boss chest.\nThere will be a higher chance for non-vanilla chests being marked correctly, but also for some non-boss chests to be treated like one.\nThis includes the models for standard, dwarven, falmer, apocrypha, soul cairn, and snow elf boss chests.")
		Return
	Endif
	If option == rDeviceBaseChanceOID
		SetInfoText("Chance to loot a random bondage item from a container or a dead body.")
		Return
	Endif
	If option == dragonHoardOID
		SetInfoText("Dragons will drop more gold, but the gold they carry is likely to be cursed.\nWith this enabled some settings might be ignored when looting dragons.")
		Return
	Endif
	If option == bossExtraGoldOID
		SetInfoText("Boss chests will have extra gold.")
		Return
	Endif
	If option == useThemesOID
		SetInfoText("Events that equip the player with devices will try to keep all devices equipped to a consistent theme.\nWARNING: this will increase the time taken to run each event and may cause lag spikes.")
		Return
	Endif
	If option == enableSlowStripOID
		SetInfoText("Replace the built in stripping algorithm with the one from sexlab.\nCan fix rare cases of crashing on stripping and also give more control over what gets stripped.")
		Return
	Endif
	If option == tatSolventChanceOID
		SetInfoText("Chance to find universal solvent when looting dead bodies. Universal solvent will remove all lewd marks and tattoos.\nHaving more tattoos will slightly increase the chance of finding one.\nSet to 0 to disable.")
		Return
	Endif
	If option == setAllDefaultSettingsOID
		SetInfoText("If you exit the menu with this enabled all settings in the MCM will be reset to default.")
		Return
	Endif
	If option == consTriggerNudeOID
		SetInfoText("Chance for a consequence when talking to someone while nude.")
		Return
	Endif
	If option == consTriggerRestrainedOID
		SetInfoText("Chance for a consequence when talking to someone while in heavy restraints.")
		Return
	Endif
	If option == consTriggerSexOID
		SetInfoText("Chance for a consequence after having sex with an actor.\nOnly applied to scenes started by this mod.")
		Return
	Endif
	If option == consAllowFollowersOID
		SetInfoText("Talking to or having sex with followers can trigger consequences.")
		Return
	Endif
	If option == consUseRelationshipsOID
		SetInfoText("The relationship rank of the target actor will affect how they treat you. You are less likely to see all consequences except mercy when the relationship is better.")
		Return
	Endif
	If option == consRelationBondageOID
		SetInfoText("Your friends want to tie you up so this is affected like mercy when Use Relationships is on.")
		Return
	Endif
	If option == consSexWeightOID
		SetInfoText("Chance for an actor to have sex with the player.")
		Return
	Endif
	If option == consFineWeightOID
		SetInfoText("Chance for you to receive a fine.")
		Return
	Endif
	If option == consFineAmountOID
		SetInfoText("How much you will owe.")
		Return
	Endif
	If option == consRandomBondageWeightOID
		SetInfoText("Chance for a random item to be equipped.")
		Return
	Endif
	If option == consRandomHeavyBondageOID
		SetInfoText("Allow for heavy bondage to be equipped.")
		Return
	Endif
	If option == consMercyWeightOID
		SetInfoText("Chance that a character will feel bad for you and unlock a device, give you a key, or give you something moderately useful.")
		Return
	Endif
	If option == sexEnabledOID
		SetInfoText("Toggles sex on or off.\nSex will only occur from friendly characters.")
		Return
	Endif
	If option == sexRandomEnabledOID
		SetInfoText("Characters that you encounter on your journey might have sex with you!")
		Return
	Endif
	If option == sexCooldownOID
		SetInfoText("How long after a scene ends before another can trigger.")
		Return
	Endif
	If option == sexChanceOID
		SetInfoText("How likely a potential actor will have sex with the player.")
		Return
	Endif
	If option == sexChanceCreatureOID
		SetInfoText("How likely a potential creature actor will have sex with the player.")
		Return
	Endif
	If option == sexBaseArousalOID
		SetInfoText("Minimum arousal required before modifications.\nSetting this above 100 will require modifications for any sex to occur.")
		Return
	Endif
	If option == sexArousalNightModifierOID
		SetInfoText("Modifier for arousal if it's night.")
		Return
	Endif
	If option == sexArousalNudeModifierOID
		SetInfoText("Modifier for arousal if the player is nude.")
		Return
	Endif
	If option == sexArousalCollarModifierOID
		SetInfoText("Modifier for arousal if a collar is worn.")
		Return
	Endif
	If option == sexArousalHeavyModifierOID
		SetInfoText("Modifier for arousal if wearing heavy restraints.")
		Return
	Endif
	If option == sexArousalBlindModifierOID
		SetInfoText("Modifier for arousal if wearing a blindfold.")
		Return
	Endif
	If option == sexArousalBootsModifierOID
		SetInfoText("Modifier for arousal if wearing restraining boots.")
		Return
	Endif
	If option == sexArousalHobbleModifierOID
		SetInfoText("Modifier for arousal if unable to run.\nThis can be because of a device or being over-encumbered.")
		Return
	Endif
	If option == sexArousalVisibleModifierOID
		SetInfoText("Modifier for arousal if the player has any visible devices.")
		Return
	Endif
	If option == sexArousalTattooModifierOID
		SetInfoText("Modifier for arousal for each tattoo the player has.")
		Return
	Endif
	If option == sexArousalCreatureModifierOID
		SetInfoText("Modifier for arousal if the aggressor is a creature.")
		Return
	Endif
	If option == sexArousalFollowerModifierOID
		SetInfoText("Modifier for arousal if the aggressor is your follower.")
		Return
	Endif
	If option == sexArousalSpouseModifierOID
		SetInfoText("Modifier for arousal if the aggressor is your spouse.")
		Return
	Endif
	If option == sexArousalSummonModifierOID
		SetInfoText("Modifier for arousal if the aggressor is your summon.")
		Return
	Endif
	If option == sexSearchRadiusOID
		SetInfoText("How far away can actors be from the player.")
		Return
	Endif
	If option == sexSearchIntervalOID
		SetInfoText("How often the actor search happens.")
		Return
	Endif
	If option == sexAllowMaleOID
		SetInfoText("Male actors will be allowed.")
		Return
	Endif
	If option == sexAllowFemaleOID
		SetInfoText("Female actors will be allowed.")
		Return
	Endif
	If option == sexAllowFutaOID
		SetInfoText("Futa actors will be allowed.\nFuta actors have a female body while being defined as male in sexlab.")
		Return
	Endif
	If option == sexAllowCreatureOID
		SetInfoText("Creature actors will be allowed.")
		Return
	Endif
	If option == sexRequireAllOID
		SetInfoText("If set sex will only happen if every requirement below is met.\nIf unset sex will happen if any requirement is met.")
		Return
	Endif
	If option == sexRequireBindingsOID
		SetInfoText("Will allow sex if the player has visible restraints.")
		Return
	Endif
	If option == sexRequireCollarOID
		SetInfoText("Will allow sex if the player is wearing a collar.")
		Return
	Endif
	If option == sexRequireHeavyOID
		SetInfoText("Will allow sex if the player is wearing heavy restraints.")
		Return
	Endif
	If option == sexRequireNudeOID
		SetInfoText("Will allow sex if the player is naked.")
		Return
	Endif
	If option == sexRequiredPlayerArousalOID
		SetInfoText("Will allow sex if the player's arousal is above the set number.\nSet to 0 to ignore player arousal.")
		Return
	Endif
	If option == sexRequiredPlayerTattoosOID
		SetInfoText("Will allow sex if the player has at least this many tattoos.\nSet to 0 to ignore player tattoos.")
		Return
	Endif
	If option == sexAlwaysAllowFollowersOID
		SetInfoText("Followers ignore requirements above.")
		Return
	Endif
	If option == sexAlwaysAllowSpouseOID
		SetInfoText("Your spouse will ignore requirements above.")
		Return
	Endif
	If option == sexAlwaysAllowSummonsOID
		SetInfoText("Your summons will ignore requirements above.")
		Return
	Endif
	If option == sexChanceFollowerOID
		SetInfoText("How likely a follower will have sex with the player.\nSet to -1 to use global chance.")
		Return
	Endif
	If option == sexChanceSpouseOID
		SetInfoText("How likely a player's spouse will have sex with them.\nSet to -1 to use global chance.")
		Return
	Endif
	If option == sexChanceSummonOID
		SetInfoText("How likely a player's summon will have sex with them.\nSet to -1 to use global creature chance.")
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
	If option == consRandomHeavyBondageOID
		consRandomHeavyBondage = !consRandomHeavyBondage
		SetToggleOptionValue(consRandomHeavyBondageOID, consRandomHeavyBondage)
		Return
	Endif
	If option == sexEnabledOID
		sexEnabled = !sexEnabled
		SetToggleOptionValue(sexEnabledOID, sexEnabled)
		ForcePageReset()
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
		SetSliderDialogDefaultValue(0.0)
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