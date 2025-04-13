#pragma once

#include "Scripting.hpp"
#include "Json.hpp"

#include <stdlib.h>

using namespace SKSE;

typedef int color;

constexpr auto SETTINGS_FILE = "Data/SKSE/Plugins/DeviousCurses.json";

namespace DCURSES {

	struct Settings {


		//MCM_START
		//Flag flag_SlaveTats					//CheckSTNG()
		//Flag flag_LewdMarks					//ESP:LewdMarksSlaveTats.esp, CheckSTNG()
		//Flag flag_SimpleSlavery				//ESP:SimpleSlavery.esp
		//Flag flag_SSEnabled					//VAR:eventSimpleSlaveryWeight > 0, ESP:SimpleSlavery.esp
		//Page Main
		//Header Chances
		float baseChance = 6.5;					//Base Event Chance//How likely are you to trigger a trap before modifiers.//{1}%//(0,100,0.1)
		float containerModifier = 1;			//Container Modifier//Modifier for containers.//{1}x//(0,10,0.1)
		float bossContainerModifier = 2;		//Boss Chest Modifier//Modifier for boss chests.\nIs applied with the container modifier.//{1}x//(0,10,0.1)
		float deadBodyModifier = 1.3f;			//Dead Body Modifier//Modifier for corpses.//{1}x//(0,10,0.1)
		float pickpocketModifier = 1.3f;		//Pickpocket Modifier//Modifier for pickpocketing.//{1}x//(0,10,0.1)
		float doorModifier = 1.0f;				//Door Modifier//Modifier for doors.//{1}x//(0,10,0.1)
		bool onlyLockedDoors = true;			//Only Locked Doors//Only trigger events when the door is locked.
		float lockedModifier = 2;				//Locked Modifier//Modifier for locked doors and chests.\nThis will not apply if the lock requires a key or you already have the key to the lock.//{1}x//(0,10,0.1)
		float lockDifficultyModifier = 1.3f;	//Lock Difficulty Modifier//If this is greater than 1, locked things will have a higher chance to cause a curse the harder the lock is to pick.\nIf set to 10 a master level lock will multiply the chance by 10 while an adept lock would multiply the chance by 5.//{1}//(1,10,0.1)
		bool eventScaling = true;				//Event Scaling//Make events less likely right after triggering one, and more likely if not triggered in a while.
		int eventScalingMod = 15;				//Event Scaling Target//The number of events before traps start becoming more likely.//{0}//(1,50,1)
		//Column
		//Header Parameters
		int minRestraints = 1;					//Min Restraints//Minimum number of restraints.//{0}//(1,10,1)
		int maxRestraints = 3;					//Max Restraints//Maximum number of restraints.//{0}//(1,10,1)
		int bossAditionalRestraints = 2;		//Boss Restraints//Added restraints when opening a boss chest.//{0}//(0,10,1)
		bool bossOnlyHeavy = true;				//Boss Heavy Restraints//Heavy restraints can only be applied from boss chests.
		int restraintCap = 7;					//Restraints Cap//Events won't happen if you have more than this many restraints.//{0}//(1,15,1)
		//Header Arousal
		float arousalModifier = 1.4f;			//Arousal Modifier//If this is greater than 1, curses will me more likely the more aroused the player is.\nIf set to 10 with full arousal will multiply the chance by 10 while half arousal would multiply the chance by 5.//{1}//(1,10,0.1)
		int minArousal = 10;					//Minimum Arousal//Curses won't trigger if the player is below this arousal level.//{0}//(0,100,1)
		//Page Devices
		//Header Chastity
		int beltWeight = 40;					//Belts Weight//Chance to be equipped with a chastity belt.//{0}//(0,100,1)
		bool beltPlugs = true;					//Belt Plugs//Equip plugs with all belts.
		bool noBeltPiercing = false;			//No Chastity Piercings//Prevent chastity belts that also function as clitoral piercings. None of these devices exist within base DD.
		int braWeight = 30;						//Bras Weight//Chance to be equipped with a chastity bra.//{0}//(0,100,1)
		int plugsWeight = 50;					//Plugs Weight//Chance to be equipped with plugs when no belt is worn.//{0}//(0,100,1)
		int lockingPlugsWeight = 30;			//Locking Plugs Weight//Chance to be equipped with plugs that can lock.//{0}//(0,100,1)
		int inflatablePlugsWeight = 15;			//Inflatable Plugs Weight//Chance to be equipped with plugs that are inflatable.//{0}//(0,100,1)
		bool plugsDontCount = true;				//Free Plugs//Plugs won't be considered for device limits.\nSo if a plug is rolled and the max devices is 1, another device can still be added.
		//Header Piercings
		int nipplePiercingsWeight = 50;			//Nipple Piercings Weight//Chance to be equipped with nipple piercings.//{0}//(0,100,1)
		int vaginalPiercingsWeight = 50;		//Vaginal Piercing Weight//Chance to be equipped with a vaginal piercing.//{0}//(0,100,1)
		//Header Corsets & Harnesses
		int corsetWeight = 40;					//Corset Weight//Chance to be equipped with a restrictive corset.//{0}//(0,100,1)
		//bool corsetBelts = true;				//Corset Belts//Allow corsets that also function as belts to be equipped.
		int beltedCorsetsWeight = 30;			//Belted Corset Weight//Chance to be equipped with a restrictive corset that has an attached belt.//{0}//(0,100,1)
		int slaveHarnessWeight = 50;			//Open Harness Weight//Chance to be equipped with an open harness.\nThis will not act as a chastity belt.//{0}//(0,100,1)
		int chastityHarnessWeight = 40;			//Chastity Harness Weight//Chance to be equipped with an open harness.\nThis will act as a chastity belt.//{0}//(0,100,1)
		//Header Heavy Bondage
		int armbinderWeight = 30;				//Armbinder Weight//Chance to be equipped with an armbinder.//{0}//(0,100,1)
		int elbowbinderWeight = 20;				//Elbowbinder Weight//Chance to be equipped with an elbowbinder.//{0}//(0,100,1)
		int yokeWeight = 10;					//Yoke Weight//Chance to be equipped with a yoke.//{0}//(0,100,1)
		int shacklesWeight = 20;				//Shackles Weight//Chance to be equipped with restraining wrist shackles.//{0}//(0,100,1)
		int straitjacketWeight = 30;			//Straitjacket Weight//Chance to be equipped with a straitjacket.//{0}//(0,100,1)
		int straitjacketLegbinderWeight = 15;	//Hobbling Straitjacket Weight//Chance to be equipped with a straitjacket that has a legbinder.//{0}//(0,100,1)
		int petSuitWeight = 10;					//Pet Suit Weight//Chance to be equipped with a pet suit.//{0}//(0,100,1)
		//Column
		//Header Collars & Cuffs	
		int collarWeight = 60;					//Collar Weight//Chance to be equipped with a collar.//{0}//(0,100,1)
		int armCuffsWeight = 60;				//Arm Cuffs Weight//Chance to be equipped with arm cuffs.//{0}//(0,100,1)
		int legCuffsWeight = 60;				//Leg Cuffs Weight//Chance to be equipped with leg cuffs.//{0}//(0,100,1)
		bool allowLegShackles = false;			//Leg Shackles//Allow leg cuffs that slow the player.
		//Header Gags & Blindfolds
		int gagWeight = 35;						//Gag Weight//Chance to be equipped with a simple gag\nThese will always block oral.//{0}//(0,100,1)
		int ringGagWeight = 45;					//Ring Gag Weight//Chance to be equipped with a ring gag\nThese will never block oral.//{0}//(0,100,1)
		int largeGagWeight = 30;				//Large Gag Weight//Chance to be equipped with a large gag\nThese will always block speech.//{0}//(0,100,1)
		int largeRingGagWeight = 30;			//Large Ring Gag Weight//Chance to be equipped with a large ring gag\nThese will always block speech and never block oral.//{0}//(0,100,1)
		int blindfoldWeight = 20;				//Blindfold Weight//Chance to be equipped with a blindfold.//{0}//(0,100,1)
		int hoodBothWeight = 20;				//Hood Weight//Chance to be equipped with a hood.//{0}//(0,100,1)
		int hoodGagWeight = 20;					//Open Eyes Hood Weight//Chance to be equipped with a hood that only blocks the mouth.//{0}//(0,100,1)
		int hoodBlindWeight = 20;				//Open Mouth Hood Weight//Chance to be equipped with a hood that only blocks the eyes.//{0}//(0,100,1)
		int hoodNoneWeight = 20;				//Open Hood Weight//Chance to be equipped with a hood that doesn't block the mouth or eyes.//{0}//(0,100,1)
		//Header Body
		int catsuitWeight = 30;					//Catsuit Weight//Chance to be equipped with a catsuit.//{0}//(0,100,1)
		int hobbleSkirtWeight = 20;				//Hobble Dress Weight//Chance to be equipped with a hobble dress.//{0}//(0,100,1)
		int hobbleSkirtDifficulty = 50;			//Hobble Dress Difficulty//How restraining hobble dresses will be on average.\nThe higher the number the greater chance for a strict dress vs a relaxed dress.//{0}//(0,100,1)
		int bootsWeight = 30;					//Boots Weight//Chance to be equipped with restrictive boots.//{0}//(0,100,1)
		int glovesWeight = 30;					//Gloves Weight//Chance to be equipped with restrictive gloves.//{0}//(0,100,1)
		int mittensWeight = 0;					//Mittens Weight//Chance to be equipped with bondage mittens.//{0}//(0,100,1)
		//Page Keys
		float keyLossChance = 80;				//Key Loss Chance//How likely you are to lose your keys during an event.//{1}%//(0,100,0.1)
		float keyChance = 7;					//Key Find Chance//How likely you are to find a key in a container.//{1}%//(0,100,0.1)
		float keyBonus = 1.0f;					//Bonus Chance Per Device//A bonus chance to get a key per locking device worn.//{1}%//(0,10,0.1)
		bool keyForgiveness = true;				//Key Forgiveness//Make keys more likely if it has been a while since you got any.
		float keyPickpocketBonus = 2.0;			//Pickpocket Bonus//Multiplier to key chance when pickpocketing someone.\nSet to 0 to disable keys when pickpocketing.//{1}x//(0,10,0.1)
		int maxHeldKeys = 3;					//Max Held Keys//Sets the maximum allowed amount of keys that you can carry while still finding more.\nWith this enabled no devices will be equipped that require more keys than you can find.\nFor example if you have two restraint keys and one chastity key and this is set to three you will no longer find keys.\nSet to 0 to disable.//{0}//(0,100,1)
		//Column
		int restraintsKeyWeight = 80;			//Restraints Key Weight//Chance to find a restraints key.//{0}//(0,100,1)
		int chastityKeyWeight = 50;				//Chastity Key Weight//Chance to find a chastity key.//{0}//(0,100,1)
		int piercingToolWeight = 20;			//Piercing Tool Weight//Chance to find a piercing removal tool.//{0}//(0,100,1)
		//Empty
		bool enableMagicKeys = true;			//Magic Keys//Magic Keys will rarely be found within boss chests. They will destroy all restraints you are wearing.\nYou can only have a max of one at a time and they can never be lost.
		bool preferRelevantKeys = true;			//Prefer Relevant Keys//You will only find keys that would unlock items you are wearing.
		bool vanishingKeys = true;				//Vanishing Keys//Keys will be removed from containers after you close the menu.
		//Page Events
		//Header Bondage Curse
		int eventStandardWeight = 100;			//Bondage Curse Weight//Chance to receive a bondage device event.//{0}//(0,500,1)
		int eventStandardBossReduction = 20;	//Standard Boss Reduction//If the container is a boss chest, the standard event weight will be reduced by this amount.//{0}//(0,500,1)
		//Column
		//Header Slavery Curse
		int eventSimpleSlaveryWeight = 0;		//Simple Slavery Weight//Chance to trigger a Simple Slavery auction.//{0}//(0,500,1) ?:? flag_SimpleSlavery														**RELOAD
		int eventSSMinRestraints = 6;			//Minimum Restraints//Minimum restraints that need to be equipped for a Simple Slavery auction to start.//{0}//(0,10,1)											?:? flag_SSEnabled
		//Header Tattoo Curse
		int eventLewdMarkWeight = 10;			//Lewd Mark Weight//Chance to receive a lewd mark.//{0}//(0,500,1) ?:? flag_LewdMarks
		//Page Lewd Marks
		bool lockSlaveTats = true;				//Lock Tattoos//Tattoos will be locked in the slave tats menu.
		//Header Allure
		int LMAllureWeight = 10;				//Allure Mark Weight//This mark will make everyone around you horny all the time.//{0}//(0,500,1)							?:? flag_LewdMarks
		int LMAllureMod = 5;					//Allure Arousal//How much each nearby character's arousal will change per minute.//{0}//(0,200,1)							?:? flag_LewdMarks
		int LMAllureSex = 25;					//Sex Count//How many times you have to have sex before the mark will fade.//{0}//(3,100,1)									?:? flag_LewdMarks
		color LMAllureColor = 0xcf11c5;			//Color//Color for mark.																									?:? flag_LewdMarks
		//Header Heat
		int LMHeatWeight = 10;					//Heat Mark//This mark will constantly make you horny.//{0}//(0,500,1)														?:? flag_LewdMarks
		int LMHeatMod = 30;						//Heat Arousal//How much your arousal will change per minute.//{0}//(0,200,1)												?:? flag_LewdMarks
		int LMHeatContainerCount = 50;			//Container Count//How many containers you must open before the mark will fade.//{0}//(10,200,1)							?:? flag_LewdMarks
		color LMHeatColor = 0xe3143a;			//Color//Color for mark.																									?:? flag_LewdMarks
		//Column
		//Empty
		//Header Bondage
		int LMBondageWeight = 5;				//Bondage Mark//With this mark devices that are in your inventory might equip themselves.//{0}//(0,500,1)					?:? flag_LewdMarks
		float LMBondageChance = 5;				//Chance//How likely an item might be equipped per 15 seconds.//{1}%//(0,100,0.1)											?:? flag_LewdMarks
		int LMBondageDeviceCount = 8;			//Device Count//How many devices need to be equipped before the mark will fade.//{0}//(1,50,1)								?:? flag_LewdMarks
		color LMBondageColor = 0x7908cf;		//Color//Color for mark.																									?:? flag_LewdMarks
		//Header Nudity
		int LMNudityWeight = 15;				//Nudity Mark//With this mark you will be unable to wear any clothes.//{0}//(0,500,1)										?:? flag_LewdMarks
		bool LMNudityChestOnly = false;			//Chest Only//With this enabled only chest armor will be checked and removed. Otherwise all armor will be unequipped.		?:? flag_LewdMarks
		int LMNudityTalkTimes = 35;				//Dialogue Times//How many times you have to talk to different characters before the mark will fade.//{0}//(3,100,1)		?:? flag_LewdMarks
		color LMNudityColor = 0xd676cb;			//Color//Color for mark.																									?:? flag_LewdMarks
		//Page Locations
		bool useLocationModifiers = true;		//Use Location Modifiers//Weather or not to apply the location modifiers listed below to event chances.
		//Empty
		//Empty
		float playerHomeModifier = 0.0f;		//Player Home Modifier//Modifier for events to happen inside of player homes.//{1}x//(0,10,0.1)
		float cityModifier = 0.0f;				//City Modifier//Modifier for events to happen inside of walled cities.//{1}x//(0,10,0.1)
		float townModifier = 0.0f;				//Town Modifier//Modifier for events to happen inside of towns.//{1}x//(0,10,0.1)
		float banditModifier = 1.1f;			//Bandit Modifier//Modifier for events to happen in or near bandit hideouts.//{1}x//(0,10,0.1)
		float draugrModifier = 1.2f;			//Draugr Modifier//Modifier for events to happen in draugr crypts.//{1}x//(0,10,0.1)
		//Column
		float lockedLocationBypass = 0.6f;		//Lock Bypass//Locked containers can't have a location modifier less than this setting.\nUseful to make locked containers still trigger traps in cities.//{1}x//(0,10,0.1)
		float theftLocationBypass = 1.1f;		//Theft Bypass//Stealing from containers can't have a location modifier less than this setting.\nUseful to make stealing from containers still trigger traps in cities.//{1}x//(0,10,0.1)
		//Empty
		float dwarvenModifier = 1.2f;			//Dwarven Modifier//Modifier for events to happen in dwarven ruins.//{1}x//(0,10,0.1)
		float falmerModifier = 1.3f;			//Falmer Modifier//Modifier for events to happen in falmer hives.//{1}x//(0,10,0.1)
		float forswornModifier = 1.1f;			//Forsworn Modifier//Modifier for events to happen in forsworn hideouts.//{1}x//(0,10,0.1)
		float vampireModifier = 1.5f;			//Vampire Modifier//Modifier for events to happen in vampire lairs.//{1}x//(0,10,0.1)
		float warlockModifier = 1.5f;			//Warlock Modifier//Modifier for events to happen in warlock lairs.//{1}x//(0,10,0.1)
		float dragonLairModifier = 2.0f;		//Dragon Lair Modifier//Modifier for events to happen in dragon lairs.//{1}x//(0,10,0.1)
		float apocryphaModifier = 2.0f;			//Apocrypha Modifier//Modifier for events to happen in apocrypha.//{1}x//(0,10,0.1)
		float wildernessModifier = 0.9f;		//Wilderness Modifier//Modifier for events to happen in the wilderness.//{1}x//(0,10,0.1)
		//Page Misc
		bool noMessageBoxes = false;			//Remove Message Boxes//No message boxes will be shown.
		bool bossChestUseModelPath = true;		//Boss Chest Models//Use the model of chests to determine if they are a boss chest.\nThere will be a higher chance for non-vanilla chests being marked correctly, but also for some non-boss chests to be treated like one.\nThis includes the models for standard, dwarven, falmer, apocrypha, soul cairn, and snow elf boss chests.
		float rDeviceBaseChance = 1.5;			//Device Base Chance//Chance to loot a random bondage item from a container or a dead body.//{1}%//(0,100,0.1)
		bool dragonHoard = true;				//Dragon Hoards//Dragons will drop more gold, but the gold they carry is likely to be cursed.\nWith this enabled some settings might be ignored when looting dragons.
		bool bossExtraGold = true;				//Boss Chest Extra Gold//Boss chests will have extra gold.
		//Column
		bool DisableGasMasks = false;			//Disable Gas Masks//Gas masks will be removed from this mod completely.
		bool DisableCatsuits = false;			//Disable Catsuits//Catsuits will be removed from this mod completely.
		bool enableQuestInteractions = true;	//Quest Interactions//Enable interactions with vanilla quests. This might include sex with NPCs, equipped devices, added tattoos, and more.
		//Page Consequences
		//Header Triggers
		float consTriggerNude = 15.0;			//Nudity//Chance for a consequence when talking to someone while nude.//{1}%//(0,100,0.1)
		float consTriggerRestrained = 50.0;		//Restrained//Chance for a consequence when talking to someone while in heavy restraints.//{1}%//(0,100,0.1)
		float consTriggerSex = 10.0;			//Sex//Chance for a consequence after having sex with an actor.\nOnly applied to scenes started by this mod.//{1}%//(0,100,0.1)
		//Empty
		bool consAllowFollowers = false;		//Allow Followers//talking to or having sex with followers can trigger consequences.
		//Column
		//Header Results
		int consSexWeight = 15;					//Sex Weight//Chance for an actor to have sex with the player.//{0}//(0,100,1)
		//Empty
		int consFineWeight = 10;				//Fine Weight//Chance for you to receive a fine.//{0}//(0,100,1)
		int consFineAmount = 100;				//Fine Amount//How much you will owe.//{0}//(50,1000,10)
		//Empty
		int consRandomBondageWeight = 10;		//Random Bondage Weight//Chance for a random item to be equipped.//{0}//(0,100,1)
		bool consRandomHeavyBondage = false;	//Allow Heavy Bondage//Allow for heavy bondage to be equipped.
		//Empty
		int consMercyWeight = 5;				//Mercy Weight//Chance that a character will feel bad for you and unlock a device, give you a key, or give you something moderately useful.//{0}//(0,100,1)
		//Page Sex
		//Flag flag_enable_sex					//VAR:sexEnabled
		//Flag flag_enable_random_sex			//VAR:sexRandomEnabled
		//Flag flag_sex_slave_tats				//VAR:sexRandomEnabled, ESP:SlaveTats.esp
		//Header General
		bool sexEnabled = false;				//Enabled//Toggles sex on or off.\nSex will only occur from friendly characters.																						**RELOAD
		bool sexRandomEnabled = false;			//Random Sex//Characters that you encounter on your journey might have sex with you!																					**RELOAD
		int sexCooldown = 30;					//Cooldown//How long after a scene ends before another can trigger.//{0}//(5,300,1)																						?:? flag_enable_random_sex
		int sexChance = 50;						//Chance//How likely a potential actor will have sex with the player.//{0}%//(0,100,1)																					?:? flag_enable_random_sex
		int sexChanceCreature = 30;				//Creature Chance//How likely a potential creature actor will have sex with the player.//{0}%//(0,100,1)																?:? flag_enable_random_sex
		//Header Arousal
		int sexBaseArousal = 90;				//Base Arousal//Minimum arousal required before modifications.\nSetting this above 100 will require modifications for any sex to occur.//{1}//(0,150,1)					?:? flag_enable_random_sex
		int sexArousalNightModifier = 5;		//Night Modifier//Modifier for arousal if it's night.//-{0}//(0,50,1)																									?:? flag_enable_random_sex
		int sexArousalNudeModifier = 15;		//Nude Modifier//Modifier for arousal if the player is nude.//-{0}//(0,50,1)																							?:? flag_enable_random_sex
		int sexArousalCollarModifier = 5;		//Collar Modifier//Modifier for arousal if a collar is worn.//-{0}//(0,50,1)																							?:? flag_enable_random_sex
		int sexArousalHeavyModifier = 10;		//Heavy Restraints Modifier//Modifier for arousal if wearing heavy restraints.//-{0}//(0,50,1)																			?:? flag_enable_random_sex
		int sexArousalBlindModifier = 5;		//Blindfold Modifier//Modifier for arousal if wearing a blindfold.//-{0}//(0,50,1)																						?:? flag_enable_random_sex
		int sexArousalBootsModifier = 0;		//Boots Modifier//Modifier for arousal if wearing restraining boots.//-{0}//(0,50,1)																					?:? flag_enable_random_sex
		int sexArousalHobbleModifier = 0;		//Hobbled Modifier//Modifier for arousal if unable to run.\nThis can be because of a device or being over-encumbered.//-{0}//(0,50,1)									?:? flag_enable_random_sex
		int sexArousalVisibleModifier = 5;		//Visible Devices Modifier//Modifier for arousal if the player has any visible devices.//-{0}//(0,50,1)																	?:? flag_enable_random_sex
		float sexArousalTattooModifier = 1;		//Tattoo Modifier//Modifier for arousal for each tattoo the player has.//-{1}//(0,10,0.1)																					?:? flag_sex_slave_tats
		int sexArousalCreatureModifier = 0;		//Creature Modifier//Modifier for arousal if the aggressor is a creature.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		int sexArousalFollowerModifier = 10;	//Follower Modifier//Modifier for arousal if the aggressor is your follower.//-{0}//(0,50,1)																			?:? flag_enable_random_sex
		int sexArousalSpouseModifier = 20;		//Spouse Modifier//Modifier for arousal if the aggressor is your spouse.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		int sexArousalSummonModifier = 0;		//Summon Modifier//Modifier for arousal if the aggressor is your summon.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		//Header Search
		float sexSearchRadius = 2000;			//Search Radius//How far away can actors be from the player.//{0}//(100,10000,100)																						?:? flag_enable_random_sex
		//Column
		//Header Allowed Actors
		bool sexAllowMale = true;				//Allow Male Actors//Male actors will be allowed.																														?:? flag_enable_sex
		bool sexAllowFemale = true;				//Allow Female Actors//Female actors will be allowed.																													?:? flag_enable_sex
		bool sexAllowFuta = true;				//Allow Futa Actors//Futa actors will be allowed.\nFuta actors have a female body while being defined as male in sexlab.												?:? flag_enable_sex
		bool sexAllowCreature = false;			//Allow Creature Actors//Creature actors will be allowed.																												?:? flag_enable_sex
		//Header Requirements
		bool sexRequireAll = false;				//Require All//If set sex will only happen if every requirement below is met.\nIf unset sex will happen if any requirement is met.										?:? flag_enable_random_sex
		bool sexRequireBindings = true;			//Bondage//Will allow sex if the player has visible restraints.																											?:? flag_enable_random_sex
		bool sexRequireCollar = false;			//Collar//Will allow sex if the player is wearing a collar.																												?:? flag_enable_random_sex
		bool sexRequireHeavy = false;			//Heavy Restraints//Will allow sex if the player is wearing heavy restraints.																							?:? flag_enable_random_sex
		bool sexRequireNude = true;				//Nudity//Will allow sex if the player is naked.																														?:? flag_enable_random_sex
		int sexRequiredPlayerArousal = 0;		//Player Arousal//Will allow sex if the player's arousal is above the set number.\nSet to 0 to ignore player arousal.//{0}//(0,100,1)									?:? flag_enable_random_sex
		int sexRequiredPlayerTattoos = 0;		//Player Tattoos//Will allow sex if the player has at least this many tattoos.\nSet to 0 to ignore player tattoos.//{0}//(0,10,1)										?:? flag_sex_slave_tats
		//Header Requirement Exceptions			
		bool sexAlwaysAllowFollowers = true;	//Always Allow Followers//Followers ignore requirements above.																											?:? flag_enable_random_sex
		bool sexAlwaysAllowSpouse = true;		//Always Allow Spouse//Your spouse will ignore requirements above.																										?:? flag_enable_random_sex
		bool sexAlwaysAllowSummons = false;		//Always Allow Summons//Your summons will ignore requirements above.																									?:? flag_enable_random_sex
		int sexChanceFollower = -1;				//Follower Chance//How likely a follower will have sex with the player.\nSet to -1 to use global chance.//{0}%//(-1,100,1)												?:? flag_enable_random_sex
		int sexChanceSpouse = -1;				//Spouse Chance//How likely a player's spouse will have sex with them.\nSet to -1 to use global chance.//{0}%//(-1,100,1)												?:? flag_enable_random_sex
		int sexChanceSummon = -1;				//Summon Chance//How likely a player's summon will have sex with them.\nSet to -1 to use global creature chance.//{0}%//(-1,100,1)										?:? flag_enable_random_sex
		//MCM_END
	} settings;

	void PlayerMessage(std::string message) {
		if (settings.noMessageBoxes) {
			DBGNotification(message);
		}
		else {
			DBGMessageBox(message);
		}
	}

	void RecalculateDeviceLists();

	void SaveMCMSettings() {
		std::ofstream o(SETTINGS_FILE);
		nlohmann::json j = nlohmann::json{
			//CODEGEN_START_TOJSON
			{"eventScalingMod", settings.eventScalingMod},
			{"minRestraints", settings.minRestraints},
			{"maxRestraints", settings.maxRestraints},
			{"bossAditionalRestraints", settings.bossAditionalRestraints},
			{"restraintCap", settings.restraintCap},
			{"minArousal", settings.minArousal},
			{"beltWeight", settings.beltWeight},
			{"braWeight", settings.braWeight},
			{"plugsWeight", settings.plugsWeight},
			{"lockingPlugsWeight", settings.lockingPlugsWeight},
			{"inflatablePlugsWeight", settings.inflatablePlugsWeight},
			{"nipplePiercingsWeight", settings.nipplePiercingsWeight},
			{"vaginalPiercingsWeight", settings.vaginalPiercingsWeight},
			{"corsetWeight", settings.corsetWeight},
			{"beltedCorsetsWeight", settings.beltedCorsetsWeight},
			{"slaveHarnessWeight", settings.slaveHarnessWeight},
			{"chastityHarnessWeight", settings.chastityHarnessWeight},
			{"armbinderWeight", settings.armbinderWeight},
			{"elbowbinderWeight", settings.elbowbinderWeight},
			{"yokeWeight", settings.yokeWeight},
			{"shacklesWeight", settings.shacklesWeight},
			{"straitjacketWeight", settings.straitjacketWeight},
			{"straitjacketLegbinderWeight", settings.straitjacketLegbinderWeight},
			{"petSuitWeight", settings.petSuitWeight},
			{"collarWeight", settings.collarWeight},
			{"armCuffsWeight", settings.armCuffsWeight},
			{"legCuffsWeight", settings.legCuffsWeight},
			{"gagWeight", settings.gagWeight},
			{"ringGagWeight", settings.ringGagWeight},
			{"largeGagWeight", settings.largeGagWeight},
			{"largeRingGagWeight", settings.largeRingGagWeight},
			{"blindfoldWeight", settings.blindfoldWeight},
			{"hoodBothWeight", settings.hoodBothWeight},
			{"hoodGagWeight", settings.hoodGagWeight},
			{"hoodBlindWeight", settings.hoodBlindWeight},
			{"hoodNoneWeight", settings.hoodNoneWeight},
			{"catsuitWeight", settings.catsuitWeight},
			{"hobbleSkirtWeight", settings.hobbleSkirtWeight},
			{"hobbleSkirtDifficulty", settings.hobbleSkirtDifficulty},
			{"bootsWeight", settings.bootsWeight},
			{"glovesWeight", settings.glovesWeight},
			{"mittensWeight", settings.mittensWeight},
			{"maxHeldKeys", settings.maxHeldKeys},
			{"restraintsKeyWeight", settings.restraintsKeyWeight},
			{"chastityKeyWeight", settings.chastityKeyWeight},
			{"piercingToolWeight", settings.piercingToolWeight},
			{"eventStandardWeight", settings.eventStandardWeight},
			{"eventStandardBossReduction", settings.eventStandardBossReduction},
			{"eventSimpleSlaveryWeight", settings.eventSimpleSlaveryWeight},
			{"eventSSMinRestraints", settings.eventSSMinRestraints},
			{"eventLewdMarkWeight", settings.eventLewdMarkWeight},
			{"LMAllureWeight", settings.LMAllureWeight},
			{"LMAllureMod", settings.LMAllureMod},
			{"LMAllureSex", settings.LMAllureSex},
			{"LMHeatWeight", settings.LMHeatWeight},
			{"LMHeatMod", settings.LMHeatMod},
			{"LMHeatContainerCount", settings.LMHeatContainerCount},
			{"LMBondageWeight", settings.LMBondageWeight},
			{"LMBondageDeviceCount", settings.LMBondageDeviceCount},
			{"LMNudityWeight", settings.LMNudityWeight},
			{"LMNudityTalkTimes", settings.LMNudityTalkTimes},
			{"consSexWeight", settings.consSexWeight},
			{"consFineWeight", settings.consFineWeight},
			{"consFineAmount", settings.consFineAmount},
			{"consRandomBondageWeight", settings.consRandomBondageWeight},
			{"consMercyWeight", settings.consMercyWeight},
			{"sexCooldown", settings.sexCooldown},
			{"sexChance", settings.sexChance},
			{"sexChanceCreature", settings.sexChanceCreature},
			{"sexBaseArousal", settings.sexBaseArousal},
			{"sexArousalNightModifier", settings.sexArousalNightModifier},
			{"sexArousalNudeModifier", settings.sexArousalNudeModifier},
			{"sexArousalCollarModifier", settings.sexArousalCollarModifier},
			{"sexArousalHeavyModifier", settings.sexArousalHeavyModifier},
			{"sexArousalBlindModifier", settings.sexArousalBlindModifier},
			{"sexArousalBootsModifier", settings.sexArousalBootsModifier},
			{"sexArousalHobbleModifier", settings.sexArousalHobbleModifier},
			{"sexArousalVisibleModifier", settings.sexArousalVisibleModifier},
			{"sexArousalCreatureModifier", settings.sexArousalCreatureModifier},
			{"sexArousalFollowerModifier", settings.sexArousalFollowerModifier},
			{"sexArousalSpouseModifier", settings.sexArousalSpouseModifier},
			{"sexArousalSummonModifier", settings.sexArousalSummonModifier},
			{"sexRequiredPlayerArousal", settings.sexRequiredPlayerArousal},
			{"sexRequiredPlayerTattoos", settings.sexRequiredPlayerTattoos},
			{"sexChanceFollower", settings.sexChanceFollower},
			{"sexChanceSpouse", settings.sexChanceSpouse},
			{"sexChanceSummon", settings.sexChanceSummon},
			{"baseChance", settings.baseChance},
			{"containerModifier", settings.containerModifier},
			{"bossContainerModifier", settings.bossContainerModifier},
			{"deadBodyModifier", settings.deadBodyModifier},
			{"pickpocketModifier", settings.pickpocketModifier},
			{"doorModifier", settings.doorModifier},
			{"lockedModifier", settings.lockedModifier},
			{"lockDifficultyModifier", settings.lockDifficultyModifier},
			{"arousalModifier", settings.arousalModifier},
			{"keyLossChance", settings.keyLossChance},
			{"keyChance", settings.keyChance},
			{"keyBonus", settings.keyBonus},
			{"keyPickpocketBonus", settings.keyPickpocketBonus},
			{"LMBondageChance", settings.LMBondageChance},
			{"playerHomeModifier", settings.playerHomeModifier},
			{"cityModifier", settings.cityModifier},
			{"townModifier", settings.townModifier},
			{"banditModifier", settings.banditModifier},
			{"draugrModifier", settings.draugrModifier},
			{"lockedLocationBypass", settings.lockedLocationBypass},
			{"theftLocationBypass", settings.theftLocationBypass},
			{"dwarvenModifier", settings.dwarvenModifier},
			{"falmerModifier", settings.falmerModifier},
			{"forswornModifier", settings.forswornModifier},
			{"vampireModifier", settings.vampireModifier},
			{"warlockModifier", settings.warlockModifier},
			{"dragonLairModifier", settings.dragonLairModifier},
			{"apocryphaModifier", settings.apocryphaModifier},
			{"wildernessModifier", settings.wildernessModifier},
			{"rDeviceBaseChance", settings.rDeviceBaseChance},
			{"consTriggerNude", settings.consTriggerNude},
			{"consTriggerRestrained", settings.consTriggerRestrained},
			{"consTriggerSex", settings.consTriggerSex},
			{"sexArousalTattooModifier", settings.sexArousalTattooModifier},
			{"sexSearchRadius", settings.sexSearchRadius},
			{"onlyLockedDoors", settings.onlyLockedDoors},
			{"eventScaling", settings.eventScaling},
			{"bossOnlyHeavy", settings.bossOnlyHeavy},
			{"beltPlugs", settings.beltPlugs},
			{"noBeltPiercing", settings.noBeltPiercing},
			{"plugsDontCount", settings.plugsDontCount},
			{"allowLegShackles", settings.allowLegShackles},
			{"keyForgiveness", settings.keyForgiveness},
			{"enableMagicKeys", settings.enableMagicKeys},
			{"preferRelevantKeys", settings.preferRelevantKeys},
			{"vanishingKeys", settings.vanishingKeys},
			{"lockSlaveTats", settings.lockSlaveTats},
			{"LMNudityChestOnly", settings.LMNudityChestOnly},
			{"useLocationModifiers", settings.useLocationModifiers},
			{"noMessageBoxes", settings.noMessageBoxes},
			{"bossChestUseModelPath", settings.bossChestUseModelPath},
			{"dragonHoard", settings.dragonHoard},
			{"bossExtraGold", settings.bossExtraGold},
			{"DisableGasMasks", settings.DisableGasMasks},
			{"DisableCatsuits", settings.DisableCatsuits},
			{"enableQuestInteractions", settings.enableQuestInteractions},
			{"consAllowFollowers", settings.consAllowFollowers},
			{"consRandomHeavyBondage", settings.consRandomHeavyBondage},
			{"sexEnabled", settings.sexEnabled},
			{"sexRandomEnabled", settings.sexRandomEnabled},
			{"sexAllowMale", settings.sexAllowMale},
			{"sexAllowFemale", settings.sexAllowFemale},
			{"sexAllowFuta", settings.sexAllowFuta},
			{"sexAllowCreature", settings.sexAllowCreature},
			{"sexRequireAll", settings.sexRequireAll},
			{"sexRequireBindings", settings.sexRequireBindings},
			{"sexRequireCollar", settings.sexRequireCollar},
			{"sexRequireHeavy", settings.sexRequireHeavy},
			{"sexRequireNude", settings.sexRequireNude},
			{"sexAlwaysAllowFollowers", settings.sexAlwaysAllowFollowers},
			{"sexAlwaysAllowSpouse", settings.sexAlwaysAllowSpouse},
			{"sexAlwaysAllowSummons", settings.sexAlwaysAllowSummons},
			//CODEGEN_END_TOJSON
		};
		o << j << std::endl;
	}

	void LoadMCMSettings() {
		if (!std::filesystem::exists(SETTINGS_FILE)) { return; }
		if (std::filesystem::file_size(SETTINGS_FILE) < 10) { return; }
		std::ifstream i(SETTINGS_FILE);
		nlohmann::json j;
		i >> j;

		//CODEGEN_START_FROMJSON
		SetMCMInt("eventScalingMod",static_cast<int>(j.value("eventScalingMod", 15)));
		SetMCMInt("minRestraints",static_cast<int>(j.value("minRestraints", 1)));
		SetMCMInt("maxRestraints",static_cast<int>(j.value("maxRestraints", 3)));
		SetMCMInt("bossAditionalRestraints",static_cast<int>(j.value("bossAditionalRestraints", 2)));
		SetMCMInt("restraintCap",static_cast<int>(j.value("restraintCap", 7)));
		SetMCMInt("minArousal",static_cast<int>(j.value("minArousal", 10)));
		SetMCMInt("beltWeight",static_cast<int>(j.value("beltWeight", 40)));
		SetMCMInt("braWeight",static_cast<int>(j.value("braWeight", 30)));
		SetMCMInt("plugsWeight",static_cast<int>(j.value("plugsWeight", 50)));
		SetMCMInt("lockingPlugsWeight",static_cast<int>(j.value("lockingPlugsWeight", 30)));
		SetMCMInt("inflatablePlugsWeight",static_cast<int>(j.value("inflatablePlugsWeight", 15)));
		SetMCMInt("nipplePiercingsWeight",static_cast<int>(j.value("nipplePiercingsWeight", 50)));
		SetMCMInt("vaginalPiercingsWeight",static_cast<int>(j.value("vaginalPiercingsWeight", 50)));
		SetMCMInt("corsetWeight",static_cast<int>(j.value("corsetWeight", 40)));
		SetMCMInt("beltedCorsetsWeight",static_cast<int>(j.value("beltedCorsetsWeight", 30)));
		SetMCMInt("slaveHarnessWeight",static_cast<int>(j.value("slaveHarnessWeight", 50)));
		SetMCMInt("chastityHarnessWeight",static_cast<int>(j.value("chastityHarnessWeight", 40)));
		SetMCMInt("armbinderWeight",static_cast<int>(j.value("armbinderWeight", 30)));
		SetMCMInt("elbowbinderWeight",static_cast<int>(j.value("elbowbinderWeight", 20)));
		SetMCMInt("yokeWeight",static_cast<int>(j.value("yokeWeight", 10)));
		SetMCMInt("shacklesWeight",static_cast<int>(j.value("shacklesWeight", 20)));
		SetMCMInt("straitjacketWeight",static_cast<int>(j.value("straitjacketWeight", 30)));
		SetMCMInt("straitjacketLegbinderWeight",static_cast<int>(j.value("straitjacketLegbinderWeight", 15)));
		SetMCMInt("petSuitWeight",static_cast<int>(j.value("petSuitWeight", 10)));
		SetMCMInt("collarWeight",static_cast<int>(j.value("collarWeight", 60)));
		SetMCMInt("armCuffsWeight",static_cast<int>(j.value("armCuffsWeight", 60)));
		SetMCMInt("legCuffsWeight",static_cast<int>(j.value("legCuffsWeight", 60)));
		SetMCMInt("gagWeight",static_cast<int>(j.value("gagWeight", 35)));
		SetMCMInt("ringGagWeight",static_cast<int>(j.value("ringGagWeight", 45)));
		SetMCMInt("largeGagWeight",static_cast<int>(j.value("largeGagWeight", 30)));
		SetMCMInt("largeRingGagWeight",static_cast<int>(j.value("largeRingGagWeight", 30)));
		SetMCMInt("blindfoldWeight",static_cast<int>(j.value("blindfoldWeight", 20)));
		SetMCMInt("hoodBothWeight",static_cast<int>(j.value("hoodBothWeight", 20)));
		SetMCMInt("hoodGagWeight",static_cast<int>(j.value("hoodGagWeight", 20)));
		SetMCMInt("hoodBlindWeight",static_cast<int>(j.value("hoodBlindWeight", 20)));
		SetMCMInt("hoodNoneWeight",static_cast<int>(j.value("hoodNoneWeight", 20)));
		SetMCMInt("catsuitWeight",static_cast<int>(j.value("catsuitWeight", 30)));
		SetMCMInt("hobbleSkirtWeight",static_cast<int>(j.value("hobbleSkirtWeight", 20)));
		SetMCMInt("hobbleSkirtDifficulty",static_cast<int>(j.value("hobbleSkirtDifficulty", 50)));
		SetMCMInt("bootsWeight",static_cast<int>(j.value("bootsWeight", 30)));
		SetMCMInt("glovesWeight",static_cast<int>(j.value("glovesWeight", 30)));
		SetMCMInt("mittensWeight",static_cast<int>(j.value("mittensWeight", 0)));
		SetMCMInt("maxHeldKeys",static_cast<int>(j.value("maxHeldKeys", 3)));
		SetMCMInt("restraintsKeyWeight",static_cast<int>(j.value("restraintsKeyWeight", 80)));
		SetMCMInt("chastityKeyWeight",static_cast<int>(j.value("chastityKeyWeight", 50)));
		SetMCMInt("piercingToolWeight",static_cast<int>(j.value("piercingToolWeight", 20)));
		SetMCMInt("eventStandardWeight",static_cast<int>(j.value("eventStandardWeight", 100)));
		SetMCMInt("eventStandardBossReduction",static_cast<int>(j.value("eventStandardBossReduction", 20)));
		SetMCMInt("eventSimpleSlaveryWeight",static_cast<int>(j.value("eventSimpleSlaveryWeight", 0)));
		SetMCMInt("eventSSMinRestraints",static_cast<int>(j.value("eventSSMinRestraints", 6)));
		SetMCMInt("eventLewdMarkWeight",static_cast<int>(j.value("eventLewdMarkWeight", 10)));
		SetMCMInt("LMAllureWeight",static_cast<int>(j.value("LMAllureWeight", 10)));
		SetMCMInt("LMAllureMod",static_cast<int>(j.value("LMAllureMod", 5)));
		SetMCMInt("LMAllureSex",static_cast<int>(j.value("LMAllureSex", 25)));
		SetMCMInt("LMHeatWeight",static_cast<int>(j.value("LMHeatWeight", 10)));
		SetMCMInt("LMHeatMod",static_cast<int>(j.value("LMHeatMod", 30)));
		SetMCMInt("LMHeatContainerCount",static_cast<int>(j.value("LMHeatContainerCount", 50)));
		SetMCMInt("LMBondageWeight",static_cast<int>(j.value("LMBondageWeight", 5)));
		SetMCMInt("LMBondageDeviceCount",static_cast<int>(j.value("LMBondageDeviceCount", 8)));
		SetMCMInt("LMNudityWeight",static_cast<int>(j.value("LMNudityWeight", 15)));
		SetMCMInt("LMNudityTalkTimes",static_cast<int>(j.value("LMNudityTalkTimes", 35)));
		SetMCMInt("consSexWeight",static_cast<int>(j.value("consSexWeight", 15)));
		SetMCMInt("consFineWeight",static_cast<int>(j.value("consFineWeight", 10)));
		SetMCMInt("consFineAmount",static_cast<int>(j.value("consFineAmount", 100)));
		SetMCMInt("consRandomBondageWeight",static_cast<int>(j.value("consRandomBondageWeight", 10)));
		SetMCMInt("consMercyWeight",static_cast<int>(j.value("consMercyWeight", 5)));
		SetMCMInt("sexCooldown",static_cast<int>(j.value("sexCooldown", 30)));
		SetMCMInt("sexChance",static_cast<int>(j.value("sexChance", 50)));
		SetMCMInt("sexChanceCreature",static_cast<int>(j.value("sexChanceCreature", 30)));
		SetMCMInt("sexBaseArousal",static_cast<int>(j.value("sexBaseArousal", 90)));
		SetMCMInt("sexArousalNightModifier",static_cast<int>(j.value("sexArousalNightModifier", 5)));
		SetMCMInt("sexArousalNudeModifier",static_cast<int>(j.value("sexArousalNudeModifier", 15)));
		SetMCMInt("sexArousalCollarModifier",static_cast<int>(j.value("sexArousalCollarModifier", 5)));
		SetMCMInt("sexArousalHeavyModifier",static_cast<int>(j.value("sexArousalHeavyModifier", 10)));
		SetMCMInt("sexArousalBlindModifier",static_cast<int>(j.value("sexArousalBlindModifier", 5)));
		SetMCMInt("sexArousalBootsModifier",static_cast<int>(j.value("sexArousalBootsModifier", 0)));
		SetMCMInt("sexArousalHobbleModifier",static_cast<int>(j.value("sexArousalHobbleModifier", 0)));
		SetMCMInt("sexArousalVisibleModifier",static_cast<int>(j.value("sexArousalVisibleModifier", 5)));
		SetMCMInt("sexArousalCreatureModifier",static_cast<int>(j.value("sexArousalCreatureModifier", 0)));
		SetMCMInt("sexArousalFollowerModifier",static_cast<int>(j.value("sexArousalFollowerModifier", 10)));
		SetMCMInt("sexArousalSpouseModifier",static_cast<int>(j.value("sexArousalSpouseModifier", 20)));
		SetMCMInt("sexArousalSummonModifier",static_cast<int>(j.value("sexArousalSummonModifier", 0)));
		SetMCMInt("sexRequiredPlayerArousal",static_cast<int>(j.value("sexRequiredPlayerArousal", 0)));
		SetMCMInt("sexRequiredPlayerTattoos",static_cast<int>(j.value("sexRequiredPlayerTattoos", 0)));
		SetMCMInt("sexChanceFollower",static_cast<int>(j.value("sexChanceFollower", -1)));
		SetMCMInt("sexChanceSpouse",static_cast<int>(j.value("sexChanceSpouse", -1)));
		SetMCMInt("sexChanceSummon",static_cast<int>(j.value("sexChanceSummon", -1)));
		SetMCMFloat("baseChance",static_cast<float>(j.value("baseChance", 6.5)));
		SetMCMFloat("containerModifier",static_cast<float>(j.value("containerModifier", 1.0)));
		SetMCMFloat("bossContainerModifier",static_cast<float>(j.value("bossContainerModifier", 2.0)));
		SetMCMFloat("deadBodyModifier",static_cast<float>(j.value("deadBodyModifier", 1.3)));
		SetMCMFloat("pickpocketModifier",static_cast<float>(j.value("pickpocketModifier", 1.3)));
		SetMCMFloat("doorModifier",static_cast<float>(j.value("doorModifier", 1.0)));
		SetMCMFloat("lockedModifier",static_cast<float>(j.value("lockedModifier", 2.0)));
		SetMCMFloat("lockDifficultyModifier",static_cast<float>(j.value("lockDifficultyModifier", 1.3)));
		SetMCMFloat("arousalModifier",static_cast<float>(j.value("arousalModifier", 1.4)));
		SetMCMFloat("keyLossChance",static_cast<float>(j.value("keyLossChance", 80.0)));
		SetMCMFloat("keyChance",static_cast<float>(j.value("keyChance", 7.0)));
		SetMCMFloat("keyBonus",static_cast<float>(j.value("keyBonus", 1.0)));
		SetMCMFloat("keyPickpocketBonus",static_cast<float>(j.value("keyPickpocketBonus", 2.0)));
		SetMCMFloat("LMBondageChance",static_cast<float>(j.value("LMBondageChance", 5.0)));
		SetMCMFloat("playerHomeModifier",static_cast<float>(j.value("playerHomeModifier", 0.0)));
		SetMCMFloat("cityModifier",static_cast<float>(j.value("cityModifier", 0.0)));
		SetMCMFloat("townModifier",static_cast<float>(j.value("townModifier", 0.0)));
		SetMCMFloat("banditModifier",static_cast<float>(j.value("banditModifier", 1.1)));
		SetMCMFloat("draugrModifier",static_cast<float>(j.value("draugrModifier", 1.2)));
		SetMCMFloat("lockedLocationBypass",static_cast<float>(j.value("lockedLocationBypass", 0.6)));
		SetMCMFloat("theftLocationBypass",static_cast<float>(j.value("theftLocationBypass", 1.1)));
		SetMCMFloat("dwarvenModifier",static_cast<float>(j.value("dwarvenModifier", 1.2)));
		SetMCMFloat("falmerModifier",static_cast<float>(j.value("falmerModifier", 1.3)));
		SetMCMFloat("forswornModifier",static_cast<float>(j.value("forswornModifier", 1.1)));
		SetMCMFloat("vampireModifier",static_cast<float>(j.value("vampireModifier", 1.5)));
		SetMCMFloat("warlockModifier",static_cast<float>(j.value("warlockModifier", 1.5)));
		SetMCMFloat("dragonLairModifier",static_cast<float>(j.value("dragonLairModifier", 2.0)));
		SetMCMFloat("apocryphaModifier",static_cast<float>(j.value("apocryphaModifier", 2.0)));
		SetMCMFloat("wildernessModifier",static_cast<float>(j.value("wildernessModifier", 0.9)));
		SetMCMFloat("rDeviceBaseChance",static_cast<float>(j.value("rDeviceBaseChance", 1.5)));
		SetMCMFloat("consTriggerNude",static_cast<float>(j.value("consTriggerNude", 15.0)));
		SetMCMFloat("consTriggerRestrained",static_cast<float>(j.value("consTriggerRestrained", 50.0)));
		SetMCMFloat("consTriggerSex",static_cast<float>(j.value("consTriggerSex", 10.0)));
		SetMCMFloat("sexArousalTattooModifier",static_cast<float>(j.value("sexArousalTattooModifier", 1.0)));
		SetMCMFloat("sexSearchRadius",static_cast<float>(j.value("sexSearchRadius", 2000.0)));
		SetMCMBool("onlyLockedDoors",static_cast<bool>(j.value("onlyLockedDoors", true)));
		SetMCMBool("eventScaling",static_cast<bool>(j.value("eventScaling", true)));
		SetMCMBool("bossOnlyHeavy",static_cast<bool>(j.value("bossOnlyHeavy", true)));
		SetMCMBool("beltPlugs",static_cast<bool>(j.value("beltPlugs", true)));
		SetMCMBool("noBeltPiercing",static_cast<bool>(j.value("noBeltPiercing", false)));
		SetMCMBool("plugsDontCount",static_cast<bool>(j.value("plugsDontCount", true)));
		SetMCMBool("allowLegShackles",static_cast<bool>(j.value("allowLegShackles", false)));
		SetMCMBool("keyForgiveness",static_cast<bool>(j.value("keyForgiveness", true)));
		SetMCMBool("enableMagicKeys",static_cast<bool>(j.value("enableMagicKeys", true)));
		SetMCMBool("preferRelevantKeys",static_cast<bool>(j.value("preferRelevantKeys", true)));
		SetMCMBool("vanishingKeys",static_cast<bool>(j.value("vanishingKeys", true)));
		SetMCMBool("lockSlaveTats",static_cast<bool>(j.value("lockSlaveTats", true)));
		SetMCMBool("LMNudityChestOnly",static_cast<bool>(j.value("LMNudityChestOnly", false)));
		SetMCMBool("useLocationModifiers",static_cast<bool>(j.value("useLocationModifiers", true)));
		SetMCMBool("noMessageBoxes",static_cast<bool>(j.value("noMessageBoxes", false)));
		SetMCMBool("bossChestUseModelPath",static_cast<bool>(j.value("bossChestUseModelPath", true)));
		SetMCMBool("dragonHoard",static_cast<bool>(j.value("dragonHoard", true)));
		SetMCMBool("bossExtraGold",static_cast<bool>(j.value("bossExtraGold", true)));
		SetMCMBool("DisableGasMasks",static_cast<bool>(j.value("DisableGasMasks", false)));
		SetMCMBool("DisableCatsuits",static_cast<bool>(j.value("DisableCatsuits", false)));
		SetMCMBool("enableQuestInteractions",static_cast<bool>(j.value("enableQuestInteractions", true)));
		SetMCMBool("consAllowFollowers",static_cast<bool>(j.value("consAllowFollowers", false)));
		SetMCMBool("consRandomHeavyBondage",static_cast<bool>(j.value("consRandomHeavyBondage", false)));
		SetMCMBool("sexEnabled",static_cast<bool>(j.value("sexEnabled", false)));
		SetMCMBool("sexRandomEnabled",static_cast<bool>(j.value("sexRandomEnabled", false)));
		SetMCMBool("sexAllowMale",static_cast<bool>(j.value("sexAllowMale", true)));
		SetMCMBool("sexAllowFemale",static_cast<bool>(j.value("sexAllowFemale", true)));
		SetMCMBool("sexAllowFuta",static_cast<bool>(j.value("sexAllowFuta", true)));
		SetMCMBool("sexAllowCreature",static_cast<bool>(j.value("sexAllowCreature", false)));
		SetMCMBool("sexRequireAll",static_cast<bool>(j.value("sexRequireAll", false)));
		SetMCMBool("sexRequireBindings",static_cast<bool>(j.value("sexRequireBindings", true)));
		SetMCMBool("sexRequireCollar",static_cast<bool>(j.value("sexRequireCollar", false)));
		SetMCMBool("sexRequireHeavy",static_cast<bool>(j.value("sexRequireHeavy", false)));
		SetMCMBool("sexRequireNude",static_cast<bool>(j.value("sexRequireNude", true)));
		SetMCMBool("sexAlwaysAllowFollowers",static_cast<bool>(j.value("sexAlwaysAllowFollowers", true)));
		SetMCMBool("sexAlwaysAllowSpouse",static_cast<bool>(j.value("sexAlwaysAllowSpouse", true)));
		SetMCMBool("sexAlwaysAllowSummons",static_cast<bool>(j.value("sexAlwaysAllowSummons", false)));
		//CODEGEN_END_FROMJSON
	}

	void P_UpdateSKSE(RE::StaticFunctionTag*) {
		//CODEGEN_START_UPDATE
		settings.eventScalingMod = GetMCMSetting("eventScalingMod")->GetSInt();
		settings.minRestraints = GetMCMSetting("minRestraints")->GetSInt();
		settings.maxRestraints = GetMCMSetting("maxRestraints")->GetSInt();
		settings.bossAditionalRestraints = GetMCMSetting("bossAditionalRestraints")->GetSInt();
		settings.restraintCap = GetMCMSetting("restraintCap")->GetSInt();
		settings.minArousal = GetMCMSetting("minArousal")->GetSInt();
		settings.beltWeight = GetMCMSetting("beltWeight")->GetSInt();
		settings.braWeight = GetMCMSetting("braWeight")->GetSInt();
		settings.plugsWeight = GetMCMSetting("plugsWeight")->GetSInt();
		settings.lockingPlugsWeight = GetMCMSetting("lockingPlugsWeight")->GetSInt();
		settings.inflatablePlugsWeight = GetMCMSetting("inflatablePlugsWeight")->GetSInt();
		settings.nipplePiercingsWeight = GetMCMSetting("nipplePiercingsWeight")->GetSInt();
		settings.vaginalPiercingsWeight = GetMCMSetting("vaginalPiercingsWeight")->GetSInt();
		settings.corsetWeight = GetMCMSetting("corsetWeight")->GetSInt();
		settings.beltedCorsetsWeight = GetMCMSetting("beltedCorsetsWeight")->GetSInt();
		settings.slaveHarnessWeight = GetMCMSetting("slaveHarnessWeight")->GetSInt();
		settings.chastityHarnessWeight = GetMCMSetting("chastityHarnessWeight")->GetSInt();
		settings.armbinderWeight = GetMCMSetting("armbinderWeight")->GetSInt();
		settings.elbowbinderWeight = GetMCMSetting("elbowbinderWeight")->GetSInt();
		settings.yokeWeight = GetMCMSetting("yokeWeight")->GetSInt();
		settings.shacklesWeight = GetMCMSetting("shacklesWeight")->GetSInt();
		settings.straitjacketWeight = GetMCMSetting("straitjacketWeight")->GetSInt();
		settings.straitjacketLegbinderWeight = GetMCMSetting("straitjacketLegbinderWeight")->GetSInt();
		settings.petSuitWeight = GetMCMSetting("petSuitWeight")->GetSInt();
		settings.collarWeight = GetMCMSetting("collarWeight")->GetSInt();
		settings.armCuffsWeight = GetMCMSetting("armCuffsWeight")->GetSInt();
		settings.legCuffsWeight = GetMCMSetting("legCuffsWeight")->GetSInt();
		settings.gagWeight = GetMCMSetting("gagWeight")->GetSInt();
		settings.ringGagWeight = GetMCMSetting("ringGagWeight")->GetSInt();
		settings.largeGagWeight = GetMCMSetting("largeGagWeight")->GetSInt();
		settings.largeRingGagWeight = GetMCMSetting("largeRingGagWeight")->GetSInt();
		settings.blindfoldWeight = GetMCMSetting("blindfoldWeight")->GetSInt();
		settings.hoodBothWeight = GetMCMSetting("hoodBothWeight")->GetSInt();
		settings.hoodGagWeight = GetMCMSetting("hoodGagWeight")->GetSInt();
		settings.hoodBlindWeight = GetMCMSetting("hoodBlindWeight")->GetSInt();
		settings.hoodNoneWeight = GetMCMSetting("hoodNoneWeight")->GetSInt();
		settings.catsuitWeight = GetMCMSetting("catsuitWeight")->GetSInt();
		settings.hobbleSkirtWeight = GetMCMSetting("hobbleSkirtWeight")->GetSInt();
		settings.hobbleSkirtDifficulty = GetMCMSetting("hobbleSkirtDifficulty")->GetSInt();
		settings.bootsWeight = GetMCMSetting("bootsWeight")->GetSInt();
		settings.glovesWeight = GetMCMSetting("glovesWeight")->GetSInt();
		settings.mittensWeight = GetMCMSetting("mittensWeight")->GetSInt();
		settings.maxHeldKeys = GetMCMSetting("maxHeldKeys")->GetSInt();
		settings.restraintsKeyWeight = GetMCMSetting("restraintsKeyWeight")->GetSInt();
		settings.chastityKeyWeight = GetMCMSetting("chastityKeyWeight")->GetSInt();
		settings.piercingToolWeight = GetMCMSetting("piercingToolWeight")->GetSInt();
		settings.eventStandardWeight = GetMCMSetting("eventStandardWeight")->GetSInt();
		settings.eventStandardBossReduction = GetMCMSetting("eventStandardBossReduction")->GetSInt();
		settings.eventSimpleSlaveryWeight = GetMCMSetting("eventSimpleSlaveryWeight")->GetSInt();
		settings.eventSSMinRestraints = GetMCMSetting("eventSSMinRestraints")->GetSInt();
		settings.eventLewdMarkWeight = GetMCMSetting("eventLewdMarkWeight")->GetSInt();
		settings.LMAllureWeight = GetMCMSetting("LMAllureWeight")->GetSInt();
		settings.LMAllureMod = GetMCMSetting("LMAllureMod")->GetSInt();
		settings.LMAllureSex = GetMCMSetting("LMAllureSex")->GetSInt();
		settings.LMHeatWeight = GetMCMSetting("LMHeatWeight")->GetSInt();
		settings.LMHeatMod = GetMCMSetting("LMHeatMod")->GetSInt();
		settings.LMHeatContainerCount = GetMCMSetting("LMHeatContainerCount")->GetSInt();
		settings.LMBondageWeight = GetMCMSetting("LMBondageWeight")->GetSInt();
		settings.LMBondageDeviceCount = GetMCMSetting("LMBondageDeviceCount")->GetSInt();
		settings.LMNudityWeight = GetMCMSetting("LMNudityWeight")->GetSInt();
		settings.LMNudityTalkTimes = GetMCMSetting("LMNudityTalkTimes")->GetSInt();
		settings.consSexWeight = GetMCMSetting("consSexWeight")->GetSInt();
		settings.consFineWeight = GetMCMSetting("consFineWeight")->GetSInt();
		settings.consFineAmount = GetMCMSetting("consFineAmount")->GetSInt();
		settings.consRandomBondageWeight = GetMCMSetting("consRandomBondageWeight")->GetSInt();
		settings.consMercyWeight = GetMCMSetting("consMercyWeight")->GetSInt();
		settings.sexCooldown = GetMCMSetting("sexCooldown")->GetSInt();
		settings.sexChance = GetMCMSetting("sexChance")->GetSInt();
		settings.sexChanceCreature = GetMCMSetting("sexChanceCreature")->GetSInt();
		settings.sexBaseArousal = GetMCMSetting("sexBaseArousal")->GetSInt();
		settings.sexArousalNightModifier = GetMCMSetting("sexArousalNightModifier")->GetSInt();
		settings.sexArousalNudeModifier = GetMCMSetting("sexArousalNudeModifier")->GetSInt();
		settings.sexArousalCollarModifier = GetMCMSetting("sexArousalCollarModifier")->GetSInt();
		settings.sexArousalHeavyModifier = GetMCMSetting("sexArousalHeavyModifier")->GetSInt();
		settings.sexArousalBlindModifier = GetMCMSetting("sexArousalBlindModifier")->GetSInt();
		settings.sexArousalBootsModifier = GetMCMSetting("sexArousalBootsModifier")->GetSInt();
		settings.sexArousalHobbleModifier = GetMCMSetting("sexArousalHobbleModifier")->GetSInt();
		settings.sexArousalVisibleModifier = GetMCMSetting("sexArousalVisibleModifier")->GetSInt();
		settings.sexArousalCreatureModifier = GetMCMSetting("sexArousalCreatureModifier")->GetSInt();
		settings.sexArousalFollowerModifier = GetMCMSetting("sexArousalFollowerModifier")->GetSInt();
		settings.sexArousalSpouseModifier = GetMCMSetting("sexArousalSpouseModifier")->GetSInt();
		settings.sexArousalSummonModifier = GetMCMSetting("sexArousalSummonModifier")->GetSInt();
		settings.sexRequiredPlayerArousal = GetMCMSetting("sexRequiredPlayerArousal")->GetSInt();
		settings.sexRequiredPlayerTattoos = GetMCMSetting("sexRequiredPlayerTattoos")->GetSInt();
		settings.sexChanceFollower = GetMCMSetting("sexChanceFollower")->GetSInt();
		settings.sexChanceSpouse = GetMCMSetting("sexChanceSpouse")->GetSInt();
		settings.sexChanceSummon = GetMCMSetting("sexChanceSummon")->GetSInt();
		settings.baseChance = GetMCMSetting("baseChance")->GetFloat();
		settings.containerModifier = GetMCMSetting("containerModifier")->GetFloat();
		settings.bossContainerModifier = GetMCMSetting("bossContainerModifier")->GetFloat();
		settings.deadBodyModifier = GetMCMSetting("deadBodyModifier")->GetFloat();
		settings.pickpocketModifier = GetMCMSetting("pickpocketModifier")->GetFloat();
		settings.doorModifier = GetMCMSetting("doorModifier")->GetFloat();
		settings.lockedModifier = GetMCMSetting("lockedModifier")->GetFloat();
		settings.lockDifficultyModifier = GetMCMSetting("lockDifficultyModifier")->GetFloat();
		settings.arousalModifier = GetMCMSetting("arousalModifier")->GetFloat();
		settings.keyLossChance = GetMCMSetting("keyLossChance")->GetFloat();
		settings.keyChance = GetMCMSetting("keyChance")->GetFloat();
		settings.keyBonus = GetMCMSetting("keyBonus")->GetFloat();
		settings.keyPickpocketBonus = GetMCMSetting("keyPickpocketBonus")->GetFloat();
		settings.LMBondageChance = GetMCMSetting("LMBondageChance")->GetFloat();
		settings.playerHomeModifier = GetMCMSetting("playerHomeModifier")->GetFloat();
		settings.cityModifier = GetMCMSetting("cityModifier")->GetFloat();
		settings.townModifier = GetMCMSetting("townModifier")->GetFloat();
		settings.banditModifier = GetMCMSetting("banditModifier")->GetFloat();
		settings.draugrModifier = GetMCMSetting("draugrModifier")->GetFloat();
		settings.lockedLocationBypass = GetMCMSetting("lockedLocationBypass")->GetFloat();
		settings.theftLocationBypass = GetMCMSetting("theftLocationBypass")->GetFloat();
		settings.dwarvenModifier = GetMCMSetting("dwarvenModifier")->GetFloat();
		settings.falmerModifier = GetMCMSetting("falmerModifier")->GetFloat();
		settings.forswornModifier = GetMCMSetting("forswornModifier")->GetFloat();
		settings.vampireModifier = GetMCMSetting("vampireModifier")->GetFloat();
		settings.warlockModifier = GetMCMSetting("warlockModifier")->GetFloat();
		settings.dragonLairModifier = GetMCMSetting("dragonLairModifier")->GetFloat();
		settings.apocryphaModifier = GetMCMSetting("apocryphaModifier")->GetFloat();
		settings.wildernessModifier = GetMCMSetting("wildernessModifier")->GetFloat();
		settings.rDeviceBaseChance = GetMCMSetting("rDeviceBaseChance")->GetFloat();
		settings.consTriggerNude = GetMCMSetting("consTriggerNude")->GetFloat();
		settings.consTriggerRestrained = GetMCMSetting("consTriggerRestrained")->GetFloat();
		settings.consTriggerSex = GetMCMSetting("consTriggerSex")->GetFloat();
		settings.sexArousalTattooModifier = GetMCMSetting("sexArousalTattooModifier")->GetFloat();
		settings.sexSearchRadius = GetMCMSetting("sexSearchRadius")->GetFloat();
		settings.onlyLockedDoors = GetMCMSetting("onlyLockedDoors")->GetBool();
		settings.eventScaling = GetMCMSetting("eventScaling")->GetBool();
		settings.bossOnlyHeavy = GetMCMSetting("bossOnlyHeavy")->GetBool();
		settings.beltPlugs = GetMCMSetting("beltPlugs")->GetBool();
		settings.noBeltPiercing = GetMCMSetting("noBeltPiercing")->GetBool();
		settings.plugsDontCount = GetMCMSetting("plugsDontCount")->GetBool();
		settings.allowLegShackles = GetMCMSetting("allowLegShackles")->GetBool();
		settings.keyForgiveness = GetMCMSetting("keyForgiveness")->GetBool();
		settings.enableMagicKeys = GetMCMSetting("enableMagicKeys")->GetBool();
		settings.preferRelevantKeys = GetMCMSetting("preferRelevantKeys")->GetBool();
		settings.vanishingKeys = GetMCMSetting("vanishingKeys")->GetBool();
		settings.lockSlaveTats = GetMCMSetting("lockSlaveTats")->GetBool();
		settings.LMNudityChestOnly = GetMCMSetting("LMNudityChestOnly")->GetBool();
		settings.useLocationModifiers = GetMCMSetting("useLocationModifiers")->GetBool();
		settings.noMessageBoxes = GetMCMSetting("noMessageBoxes")->GetBool();
		settings.bossChestUseModelPath = GetMCMSetting("bossChestUseModelPath")->GetBool();
		settings.dragonHoard = GetMCMSetting("dragonHoard")->GetBool();
		settings.bossExtraGold = GetMCMSetting("bossExtraGold")->GetBool();
		settings.DisableGasMasks = GetMCMSetting("DisableGasMasks")->GetBool();
		settings.DisableCatsuits = GetMCMSetting("DisableCatsuits")->GetBool();
		settings.enableQuestInteractions = GetMCMSetting("enableQuestInteractions")->GetBool();
		settings.consAllowFollowers = GetMCMSetting("consAllowFollowers")->GetBool();
		settings.consRandomHeavyBondage = GetMCMSetting("consRandomHeavyBondage")->GetBool();
		settings.sexEnabled = GetMCMSetting("sexEnabled")->GetBool();
		settings.sexRandomEnabled = GetMCMSetting("sexRandomEnabled")->GetBool();
		settings.sexAllowMale = GetMCMSetting("sexAllowMale")->GetBool();
		settings.sexAllowFemale = GetMCMSetting("sexAllowFemale")->GetBool();
		settings.sexAllowFuta = GetMCMSetting("sexAllowFuta")->GetBool();
		settings.sexAllowCreature = GetMCMSetting("sexAllowCreature")->GetBool();
		settings.sexRequireAll = GetMCMSetting("sexRequireAll")->GetBool();
		settings.sexRequireBindings = GetMCMSetting("sexRequireBindings")->GetBool();
		settings.sexRequireCollar = GetMCMSetting("sexRequireCollar")->GetBool();
		settings.sexRequireHeavy = GetMCMSetting("sexRequireHeavy")->GetBool();
		settings.sexRequireNude = GetMCMSetting("sexRequireNude")->GetBool();
		settings.sexAlwaysAllowFollowers = GetMCMSetting("sexAlwaysAllowFollowers")->GetBool();
		settings.sexAlwaysAllowSpouse = GetMCMSetting("sexAlwaysAllowSpouse")->GetBool();
		settings.sexAlwaysAllowSummons = GetMCMSetting("sexAlwaysAllowSummons")->GetBool();
		//CODEGEN_END_UPDATE
		SaveMCMSettings();
		RecalculateDeviceLists();
	}

	bool P_CheckSTNG(RE::StaticFunctionTag*) {
		return GetModuleHandle(L"SlaveTatsNG") != nullptr;
	}

	bool PapyrusFunctionsSettigns(RE::BSScript::IVirtualMachine* ivm) {
		//ivm->RegisterFunction("UpdateDCursesSKSE_Int", "DCurses_MCM", P_UpdateSKSEInt);
		//ivm->RegisterFunction("UpdateDCursesSKSE_Float", "DCurses_MCM", P_UpdateSKSEFloat);
		//ivm->RegisterFunction("UpdateDCursesSKSE_Bool", "DCurses_MCM", P_UpdateSKSEBool);

		ivm->RegisterFunction("UpdateSKSE", "DCurses_MCM", P_UpdateSKSE);
		ivm->RegisterFunction("CheckSTNG", "DCurses_MCM", P_CheckSTNG);
		return true;
	}

}