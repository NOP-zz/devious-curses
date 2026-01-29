#pragma once

#include "Scripting.hpp"
#include "Serializer.hpp"
#include "Json.hpp"
#include "Utils.hpp"

#include <stdlib.h>

using namespace SKSE;

typedef int color;
typedef int keycode;
typedef std::string text;

constexpr auto SETTINGS_FILE = "Data/SKSE/Plugins/DeviousCurses.json";

namespace DCURSES {

	struct Settings {


		//MCM_START
		//Flag flag_SlaveTats					//CheckSTNG()
		//Flag flag_LewdMarks					//CheckLM() && CheckSTNG()
		//Flag flag_RapeTats					//ESP:RapeTattoos.esp && CheckSTNG()
		//Flag flag_RT_LM						//ESP:RapeTattoos.esp && CheckSTNG() && CheckLM()
		//Flag flag_SimpleSlavery				//ESP:SimpleSlavery.esp
		//Flag flag_UnforgivingDevices			//ESP:UnforgivingDevices.esp
		//Flag flag_SGO							//ESP:Sgo4IF.esp
		//Flag flag_LockOppDevice_Menu			//!oppDeviceAntiCheat || !WearingOppressiveDevice() 
		//Flag flag_WickedDevices				//ESP:Devious Wicked Devices.esp
		//Flag flag_AND							//ESP:Advanced Nudity Detection.esp
		
		//Page Main								
		//Header Chances
		float baseChance = 6.5f;				//Base Event Chance//How likely are you to trigger a trap before modifiers.//{1}%//(0,100,0.1)
		float containerModifier = 1.0f;			//Container Modifier//Modifier for containers.//{1}x//(0,10,0.1)
		float bossContainerModifier = 2.0f;		//Boss Chest Modifier//Modifier for boss chests.\nIs applied with the container modifier.//{1}x//(0,10,0.1)
		float deadBodyModifier = 1.3f;			//Dead Body Modifier//Modifier for corpses.//{1}x//(0,10,0.1)
		float pickpocketModifier = 1.3f;		//Pickpocket Modifier//Modifier for pickpocketing.//{1}x//(0,10,0.1)
		float doorModifier = 1.0f;				//Door Modifier//Modifier for doors.//{1}x//(0,10,0.1)
		bool onlyLockedDoors = true;			//Only Locked Doors//Only trigger events when the door is locked.
		float lockedModifier = 2.0f;			//Locked Modifier//Modifier for locked doors and chests.\nThis will not apply if the lock requires a key or you already have the key to the lock.//{1}x//(0,10,0.1)
		float lockDifficultyModifier = 1.3f;	//Lock Difficulty Modifier//If this is greater than 1, locked things will have a higher chance to cause a curse the harder the lock is to pick.\nIf set to 10 a master level lock will multiply the chance by 10 while an adept lock would multiply the chance by 5.//{1}//(1,10,0.1)
		int minGoldRequired = 20;				//Container Gold Value//Requires a container to have at least this total value of items in it to trigger any events.//{0}//(0,5000,10)
		bool eventScaling = true;				//Event Scaling//Make events less likely right after triggering one, and more likely if not triggered in a while.
		int eventScalingMod = 15;				//Event Scaling Target//The number of events before traps start becoming more likely.//{0}//(1,50,1)
		//Column
		//Header Parameters
		int minRestraints = 1;					//Min Restraints//Minimum number of restraints.//{0}//(1,15,1)
		int maxRestraints = 3;					//Max Restraints//Maximum number of restraints.//{0}//(1,15,1)
		int bossAditionalRestraints = 2;		//Boss Restraints//Added restraints when opening a boss chest.//{0}//(0,10,1)
		bool bossOnlyHeavy = true;				//Boss Heavy Restraints//Heavy restraints can only be applied from boss chests.
		int restraintCap = 7;					//Restraints Cap//Events won't happen if you have more than this many restraints.//{0}//(1,15,1)
		bool stripPlayerOnEvent = true;			//Strip Player//Toggle to choose if the player should be stripped on any event.\nIf a heavy bondage device is equipped the player will be stripped anyway.
		bool stripOnlyKeywords = true;			//Strip Armor Keywords//This will only remove items that are tagged as armor or clothing through keywords.\nThis may cause some modded items to not be unequipped.
		//Header Arousal
		float arousalModifier = 1.4f;			//Arousal Modifier//If this is greater than 1, curses will me more likely the more aroused the player is.\nIf set to 10 with full arousal will multiply the chance by 10 while half arousal would multiply the chance by 5.//{1}//(1,10,0.1)
		int minArousal = 10;					//Minimum Arousal//Curses won't trigger if the player is below this arousal level.//{0}//(0,100,1)
		
		//Page Devices
		//Header Chastity
		int beltWeight = 40;					//Belts Weight//Chance to be equipped with a chastity belt.//{0}//(0,100,1)
		bool beltPlugs = true;					//Belt Plugs//Equip plugs with all belts.
		int chastityPiercingWeight = 20;		//Chastity Piercing Weight//Chance to be equipped with a chastity piercing.\nWill only matter if you have a mod like Devious Chastity Piercings.//{0}//(0,100,1)
		bool useGenderedChastity = true;		//Use Gendered Chastity//Equip futa characters with cock cages instead of regular belts. Will also prevent female characters from getting cages.\nWill do nothing without Vivis Cockcages Devious Patch.		**RECALC
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
		
		//Page Events
		//Header Bondage Curse
		int eventStandardWeight = 100;			//Bondage Curse Weight//Chance to receive a bondage device event.//{0}//(0,500,1)
		int eventStandardBossReduction = 20;	//Standard Boss Reduction//If the container is a boss chest, the standard event weight will be reduced by this amount.//{0}//(0,500,1)
		//Header Oppresive Curse
		int eventOppressiveWeight = 15;			//Oppressive Curse Weight//Chance to receive an oppressive device event.//{0}//(0,500,1)
		//Header Contraption Curse
		int eventContraptionWeight = 25;		//Contraption Curse Weight//Chance to be bound in a contraption from DDC.//{0}//(0,500,1)																											
		float eventContraptionTime = 4.0f;		//Contraption Release Time//Will be automatically released after this many in game hours. Set to 0 to disable automatic release.//{1}//(0,24,0.1)													
		bool eventContDevices = true;			//Contraption Devices//Will allow certain devices such as collars, gags, cuffs, and plugs to be equipped when triggering a contraption event.\nWill follow all other rules set for devices.			
		bool eventContAllDevices = false;		//Use All Devices//Will allow any device other than heavy bondage to be equipped when triggering a contraption event.\nWill follow all other rules set for devices.									
		int eventContDeviceOverride = 0;		//Device Count Override//When equipping devices for contraption events this number will be used instead of the min / max on the main page.\nSet to 0 to use the default number of devices.//{0}//(0,10,1)
		//Header Wicked Curse
		int eventWickedWeight = 15;				//Wicked Curse Weight//Chance to be bound in a device from Devious Wicked Devices.//{0}//(0,500,1)							?:? flag_WickedDevices
		//Header Tattoo Curse
		int eventTattooWeight = 15;				//Tattoo Curse Weight//Chance to receive random tattoos.\nRequires Rape Tattoos.//{0}//(0,500,1)							?:? flag_RapeTats
		int eventTattooMin = 1;					//Tattoo Curse Min//Minimum number of tattoos that can be put on.//{0}//(1,10,1)											?:? flag_RapeTats
		int eventTattooMax = 3;					//Tattoo Curse Max//Maximum number of tattoos that can be put on.//{0}//(1,10,1)											?:? flag_RapeTats
		int eventTattooCap = 8;					//Tattoo Curse Cap//If you have this many tattoos already you won't get any more.//{0}//(0,20,1)							?:? flag_RapeTats
		//Column
		bool allowFollowerEvents = false;		//Follower Events//Allow followers to be affected by curses. Currently only applies to the Bondage Curse and Tattoo Curse.
		bool onlyFemaleFollowers = true;		//Only Female Followers//Follower events will only trigger if the follower uses a female body (female & futa).
		text excludedFollowers = "";			//Excluded Followers//List of followers that are excluded from events. Names should be comma-separated.\nThis will check to see if any part of their name matches.\nExample: "Lydia, J'zargo"
		bool followerHeavyRestraints = false;	//Follower Heavy Restraints//Will allow events to equip heavy restraints on followers.
		int followerDeviceModifier = 0;			//Follower Device Modifier//Will add (or subtrace) this many devices when equipping followers with devices.\nFollowers will always be equipped with at least one device.//{0}//(-10,10,1)
		//Header Mark Curse
		int eventLewdMarkWeight = 10;			//Lewd Mark Weight//Chance to receive a lewd mark.//{0}//(0,500,1) ?:? flag_LewdMarks
		//Header Slavery Curse
		int eventSimpleSlaveryWeight = 0;		//Simple Slavery Weight//Chance to trigger a Simple Slavery auction.//{0}//(0,500,1) ?:? flag_SimpleSlavery					**RELOAD
		int eventSSMinRestraints = 6;			//Minimum Restraints//Minimum restraints that need to be equipped for a Simple Slavery auction to start.//{0}//(0,10,1)		?:? flag_SimpleSlavery
		//Header Abadon Curse
		int eventAbadonWeight = 5;				//Abadon Plug Weight//Chance to be equipped with an Abadon Plug. This will trigger exactly the same as the quest from UD.//{0}//(0,500,1)						?:? flag_UnforgivingDevices
		//Header Abadon Sets
		int eventAbadonWarriorWeight = 10;		//Abadon Warrior Weight//Chance to be equipped with devices from the Abadon Warrior set.//{0}//(0,500,1)														?:? flag_UnforgivingDevices
		int eventAbadonWarriorCount = 5;		//Abadon Warrior Count//Number of Warrior devices that will be equipped durring the event//{0}//(1,10,1)														?:? flag_UnforgivingDevices
		int eventAbadonScoutWeight = 10;		//Abadon Scout Weight//Chance to be equipped with devices from the Abadon Scout set.//{0}//(0,500,1)															?:? flag_UnforgivingDevices
		int eventAbadonScoutCount = 5;			//Abadon Scout Count//Number of Scout devices that will be equipped durring the event//{0}//(1,10,1)															?:? flag_UnforgivingDevices
		int eventAbadonWitchWeight = 10;		//Abadon Witch Weight//Chance to be equipped with devices from the Abadon Witch set.//{0}//(0,500,1)															?:? flag_UnforgivingDevices
		int eventAbadonWitchCount = 5;			//Abadon Witch Count//Number of Witch devices that will be equipped durring the event//{0}//(1,10,1)															?:? flag_UnforgivingDevices
		
		//Page Unforgiving Devices
		bool onlyUseUnforgivingDevices = true;	//Only Unforgiving Devices//Only register devices to the mod that are converted to work with UD.\n(Will cause lag on menu close)													?:? flag_UnforgivingDevices  **RECALC
		bool udUseAbadon = false;				//Allow Abadon Devices//Allow Abadon devices to be enabled in the normal random device search. Will not equip the Abadon Plug even if enabled.\n(Will cause lag on menu close)		?:? flag_UnforgivingDevices  **RECALC
		bool udUseAbadonSets = false;			//Allow Abadon Sets//Allow Abadon Sets like Warrior and Witch to be enabled in the normal random device search.\n(Will cause lag on menu close)										?:? flag_UnforgivingDevices  **RECALC
		bool udUseMisc = true;					//Allow Misc Unforgiving Devices//Allow devices like chargable plugs, punisher items, etc. to be enabled in the normal random device search\n(Will cause lag on menu close)			?:? flag_UnforgivingDevices  **RECALC
		
		//Page Advanced Nudity Detection
		//Header Nudity Sex
		bool ANDSexTopless = true;				//Topless Trigger//Sex nudity modifier will apply when topless.																?:? flag_AND
		bool ANDSexBottomless = true;			//Bottomless Trigger//Sex nudity modifier will apply when bottomless.														?:? flag_AND
		bool ANDSexShowingChest = true;			//Chest Trigger//Sex nudity modifier will apply when showing chest.															?:? flag_AND
		bool ANDSexShowingGenitals = true;		//Genitals Trigger//Sex nudity modifier will apply when showing genitals.													?:? flag_AND
		bool ANDSexShowingAss = false;			//Ass Trigger//Sex nudity modifier will apply when showing ass.																?:? flag_AND
		bool ANDSexShowingBra = false;			//Bra Trigger//Sex nudity modifier will apply when showing bra.																?:? flag_AND
		bool ANDSexShowingUnderwear = false;	//Underwear Trigger//Sex nudity modifier will apply when showing underwear.													?:? flag_AND
		//Column
		//Header Nudity Consequence
		bool ANDConsTopless = true;				//Topless Trigger//Nudity consequence will trigger when topless.															?:? flag_AND
		bool ANDConsBottomless = true;			//Bottomless Trigger//Nudity consequence will trigger when bottomless.														?:? flag_AND
		bool ANDConsShowingChest = true;		//Chest Trigger//Nudity consequence will trigger when showing chest.														?:? flag_AND
		bool ANDConsShowingGenitals = true;		//Genitals Trigger//Nudity consequence will trigger when showing genitals.													?:? flag_AND
		bool ANDConsShowingAss = false;			//Ass Trigger//Nudity consequence will trigger when showing ass.															?:? flag_AND
		bool ANDConsShowingBra = false;			//Bra Trigger//Nudity consequence will trigger when showing bra.															?:? flag_AND
		bool ANDConsShowingUnderwear = false;	//Underwear Trigger//Nudity consequence will trigger when showing underwear.												?:? flag_AND
		
		//Page Lewd Marks
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
		//Header Branding
		int LMBrandingWeight = 10;				//Branding Mark//This mark will force you to have a certain number of tattoos!//{0}//(0,500,1)								?:? flag_RT_LM
		float LMBrandingChance = 1.5f;			//Chance//How likely you are to receive a random tattoo per 15 seconds.\nRequires Rape Tattoos//{1}%//(0,100,0.1)			?:? flag_RT_LM
		int LMBrandingTotal = 12;				//Total Tattoos//How many tattoos you need before the mark releases. The mark itself counts as 2.//{0}//(1,20,1)			?:? flag_RT_LM
		bool LMBrandingPunish = true;			//Punishment//You will be punished by loosing gold if your total tattoo count decreases.									?:? flag_RT_LM
		color LMBrandingColor = 0x220022;		//Color//Color for mark.																									?:? flag_RT_LM
		//Column
		//Header Bondage
		int LMBondageWeight = 5;				//Bondage Mark//With this mark devices that are in your inventory might equip themselves.//{0}//(0,500,1)					?:? flag_LewdMarks
		float LMBondageChance = 5.0f;			//Chance//How likely an item might be equipped per 15 seconds.//{1}%//(0,100,0.1)											?:? flag_LewdMarks
		int LMBondageDeviceCount = 8;			//Device Count//How many devices need to be equipped before the mark will fade.//{0}//(1,50,1)								?:? flag_LewdMarks
		color LMBondageColor = 0x7908cf;		//Color//Color for mark.																									?:? flag_LewdMarks
		//Header Nudity
		//Flag flag_LMStripBody					//LMNudityChestOnly && flag_LewdMarks == 0
		int LMNudityWeight = 15;				//Nudity Mark//With this mark you will be unable to wear any clothes.//{0}//(0,500,1)										?:? flag_LewdMarks
		bool LMNudityChestOnly = false;			//Chest Only//With this enabled only chest armor will be checked and removed. Otherwise all armor will be unequipped.		?:? flag_LewdMarks **RELOAD
		text LMNudityAditionalForms = "";		//Strip Slots//A comma separated list of additional slots to strip. Will not strip devices.\nFor example: 46,47,49,52.		?:? flag_LMStripBody
		int LMNudityTalkTimes = 35;				//Dialogue Times//How many times you have to talk to different characters before the mark will fade.//{0}//(3,100,1)		?:? flag_LewdMarks
		color LMNudityColor = 0xd676cb;			//Color//Color for mark.																									?:? flag_LewdMarks
		//Header Healslut
		int LMHealslutWeight = 5;				//Healslut Mark//With this mark you won't be able to deal damage and must heal your allies instead.//{0}//(0,500,1)			?:? flag_LewdMarks
		int LMHealslutHealing = 2000;			//Healing Amount//How much you have to heal your followers to remove the mark. This works if your followers are at full health.//{0}//(1000,100000,1000)		?:? flag_LewdMarks
		color LMHealslutColor = 0xffbb45;		//Color//Color for mark.																									?:? flag_LewdMarks
		
		//Page Oppressive Devices
		bool oppOneAtATime = true;				//Only One//With this enabled you will not be equipped with an Oppressive Device if you are already wearing one\nThis restriction is ignored for Quest Interactions.
		//Header Summoner Collar
		int oppSummonerCollarWeight = 20;		//Weight//How likely that you will be equipped with a collar that makes you have sex with your summons.\nRequires creatures to be enabled for sex.//{0}//(0,500,1)
		int oppSummonerSexCount = 15;			//Sex Count//How may time you need to have sex with your summons before the collar will unlock.//{0}//(1,100,1)
		bool oppSCollarDrainsMagicka = true;	//Magicka Drain//The collar will drain all of your magicka when summoning.
		bool oppSCollarAutoRemove = true;		//Auto Remove//Remove the collar as soon as the requirements are met instead of just giving the key for it.
		int oppSMinSummonArousal = 90;			//Summon Arousal//Will change the arousal of all of your summons to be at least this value.//{0}//(0,100,1)
		float oppSummonChance = 1.5f;			//Summon Chance//The chance per second that the collar summons an atronach to have sex with you.\nThis won't happen if you already have a different summon.//{1}%//(0,100,0.1)
		//Header Dwarven Cuirass
		int oppDwarvenCuirassWeight = 15;		//Weight//How likely that you will be equipped with a devious dwarven cuirass that will control your actions.//{0}//(0,500,1)
		int oppDwarvenValueNeeded = 200;		//Dwarven Parts Value//How much value of dwarven parts like gears and gyros the dwarven cuirass needs to take before it is removed.\nDoes not count ingots, centurion dynamos, or pots, pans, cups, etc.//{0}//(30,2000,10)
		bool oppDwarvenHeavyRestraint = false;	//Heavy Restraint//The cuirass will count as a heavy bondage like a straitjacket. This will make removing the device much harder.\nWill only affect the cuirass before it is equipped.
		bool oppDwarvenRequireLoc = true;		//Require Location//The cuirass can only be found in dwarven locations.
		int oppDwarvenArousal = 25;				//Masturbation Arousal//If your arousal is above this there is a chance that the dwarven cuirass will force you to masturbate!\nSet to 100 to disable//{0}//(10,100,1)
		//Header Nocturnal Piercings
		int oppNocturnalWeight = 10;			//Weight//How likely that you will be equipped with a piercing that can grant invisibility.//{0}//(0,500,1)
		int oppNocturnalSexCount = 3;			//Public Sex Count//How many times you need to have sex in front of people before the piercing is removed.//{0}//(1,100,1)
		int oppNocturnalPeople = 7;				//Spectators//How many people need to watch you have sex for it to count.\nFollowers are not counted for this.//{0}//(2,15,1)
		int oppNocturnalArousal = 35;			//Arousal//At what arousal will the invisibility automatically drop.//{0}//(10,95,1)
		float oppNocturnalHandChance = 3.5f;	//Shadow Hand Chance//The chance per second that an invisible hand will touch you.//{1}%//(0,50,0.1)
		float oppNocturnalRecastChance = 33.3f;	//Recast Chance//The chance that an invisible hand will touch you every time the spell is recast.//{1}%//(10,100,0.1)
		//Column
		//Empty
		//Header Living Latex
		int oppLivingLatexWeight = 20;			//Weight//How likely that you will be encased in latex that will bind you with ebonite.//{0}//(0,500,1)
		int oppLivingLatexStartTime = 15;		//Start Time//How long in minutes do you have to wear the latex before it isn't dormant.\n//{0}//(1,60,1)
		float oppLivingLatexGem = 6.0f;			//Volatile Gem Chance//The chance to find a gem on dead mages and warlocks that will shock the latex when hit with a weapon.//{1}//(0,100,0.1)
		bool oppLivingLatexHeavy = false;		//Heavy Bondage//The latex will bind you with heavy bondage devices.\nWarning: this will happen in combat.
		float oppLivingLatexMore = 0.0f;		//Periodic Devices//How frequently in minutes the latex will bind you when active. Set to 0 to disable.\nWarning: this will happen in combat.//{1}//(0,10,0.1)
		bool oppLivingLatexRequireRem = true;	//Clinging//The latex will cling to your other devices, requiring you to remove all of them before it will dissapear.
		bool oppLivingLatexOpen = false;		//Use Open Catsuit//Will replace the default catsuit with the open variant. Will only work if you don't have the device yet.
		//Header Madness Plug
		int oppMadnessPlugWeight = 25;			//Weight//How likely you will be equipped with a plug that will try to drive you mad.//{0}//(0,500,1)
		int oppMadnessPlugIterations = 5;		//Number of Events//How many events the plug will do before it is removed.//{0}//(1,20,1)
		int oppMadnessplugOrgasms = 6;			//Orgasms Per Event//How many times the plug must make you orgasm per event.\nThis only counts orgasms caused by devious devices.//{0}//(1,100,1)
		bool oppMadnessAllOrgasms = false;		//Include Sex//This will increase the counter for orgasms after having sex instead of only using device orgasms.
		bool oppMadnessBeltFilter = true;		//Belt Filter//The plug will only be equipped if you are not wearing a belt (or vaginal plug) that can't be removed.
		bool oppMadnessChaos = false;			//True Madness//Will remove the restrictions on what events can happen. These events may result in PERMANENT changes to your character (Lowering your health, magicka, or stamina).
		
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
		
		//Page Keys
		float keyLossChance = 80.0f;			//Key Loss Chance//How likely you are to lose your keys during an event.//{1}%//(0,100,0.1)
		float keyChance = 7.0f;					//Key Find Chance//How likely you are to find a key in a container.//{1}%//(0,100,0.1)
		int minKeysLooted = 1;					//Min Keys//The minimum number of keys that can be found at a time.//{0}//(1,10,1)
		int maxKeysLooted = 1;					//Max Keys//The maximum number of keys that can be found at a time.//{0}//(1,10,1)
		float keyBonus = 1.0f;					//Bonus Chance Per Device//A bonus chance to get a key per locking device worn.//{1}%//(0,10,0.1)
		bool keyForgiveness = true;				//Key Forgiveness//Make keys more likely if it has been a while since you got any.
		float keyPickpocketBonus = 2.0f;		//Pickpocket Bonus//Multiplier to key chance when pickpocketing someone.\nSet to 0 to disable keys when pickpocketing.//{1}x//(0,10,0.1)
		int maxHeldKeys = 3;					//Max Held Keys//Sets the maximum allowed amount of keys that you can carry while still finding more.\nWith this enabled no devices will be equipped that require more keys than you can find.\nFor example if you have two restraint keys and one chastity key and this is set to three you will no longer find keys.\nSet to 0 to disable.//{0}//(0,100,1) **RECALC
		//Column
		int restraintsKeyWeight = 80;			//Restraints Key Weight//Chance to find a restraints key.//{0}//(0,100,1)
		int chastityKeyWeight = 50;				//Chastity Key Weight//Chance to find a chastity key.//{0}//(0,100,1)
		int piercingToolWeight = 20;			//Piercing Tool Weight//Chance to find a piercing removal tool.//{0}//(0,100,1)
		//Empty
		float magicKeyChance = 20.0f;			//Magic Key Chance//Chance that magic keys will be found in boss chests. They will destroy all restraints you are wearing.\nYou can only have a max of one at a time and they can never be lost.\nSet to 0 to disable//{1}//(0,50,0.1)
		bool magicKeyOppressive = false;		//Magic Keys Remove Oppressive//Magic keys will remove one random oppressive device when used.
		bool preferRelevantKeys = true;			//Prefer Relevant Keys//You will only find keys that would unlock items you are wearing.
		bool vanishingKeys = true;				//Vanishing Keys//Keys will be removed from containers after you close the menu.
		float keyLuckyBonus = 1.75f;			//Lucky Bonus//Keys chance will be multiplied by this value if you are lucky.//{2}//(1,10,0.01)
		
		//Page Quest Interactions
		//Flag flag_enable_qi					//enableQuestInteractions
		bool enableQuestInteractions = true;	//Quest Interactions//Certain quests may have some additional events tied to them.\n The mod page has more information about each quest.		**RELOAD
		//Header Quest Toggles
		bool enableQIMalkoran = true;			//Malkoran//									?:? flag_enable_qi
		bool enableQISanguine = true;			//Sanguine//									?:? flag_enable_qi
		bool enableQIBlackStar = true;			//Black Star//									?:? flag_enable_qi
		bool enableQIMindOfMadness = true;		//Sheogorath//									?:? flag_enable_qi
		bool enableQILaidToRest = true;			//Laid To Rest//								?:? flag_enable_qi
		bool enableQICriedWolf = true;			//The Man Who Cried Wolf//						?:? flag_enable_qi
		//Column
		//Empty
		//Empty
		bool enableQIProvingHonor = true;		//Proving Honor//								?:? flag_enable_qi
		bool enableQISaarthal = true;			//Saarthal//									?:? flag_enable_qi
		bool enableQIBrelyna = true;			//Brelyna's Practice//							?:? flag_enable_qi
		bool enableQIDwemerMuseum = true;		//Dwemer Museum//								?:? flag_enable_qi
		bool enableQITrinityRestored = true;	//Trinity Restored//							?:? flag_enable_qi
		bool enableQIThalmorEmbassy = true;		//Thalmor Embassy//								?:? flag_enable_qi
		bool enableQIRingmaker = true;			//Ringmaker//									?:? flag_enable_qi
		
		//Page Misc
		//Flag flag_events_disabled				//ModSuspended
		//Flag flag_wearingOppDevice			//!WearingOppressiveDevice()
		bool oppDeviceAntiCheat = true;			//Lock Oppressive Devices Menu//Lock the Oppressive Devices menu when wearing an oppressive device.		?:? flag_wearingOppDevice
		bool generalDeviceAntiCheat = false;	//Lock Menus While Restrained//All menus will be disabled while you are wearing any devices.
		bool noMessageBoxes = false;			//Remove Message Boxes//No message boxes will be shown.
		bool bossChestUseModelPath = true;		//Boss Chest Models//Use the model of chests to determine if they are a boss chest.\nThere will be a higher chance for non-vanilla chests being marked correctly, but also for some non-boss chests to be treated like one.\nThis includes the models for standard, dwarven, falmer, apocrypha, soul cairn, and snow elf boss chests.
		float rDeviceBaseChance = 1.5f;			//Device Base Chance//Chance to loot a random bondage item from a container or a dead body.//{1}%//(0,100,0.1)
		float rDeviceLuckyBonus = 2.5f;			//Device Lucky Bonus//Device base chance will be multiplied by this value if you are lucky.//{2}//(1,10,0.01)
		bool dragonHoard = true;				//Dragon Hoards//Dragons will drop more gold, but the gold they carry is likely to be cursed.\nWith this enabled some settings might be ignored when looting dragons.
		bool bossExtraGold = true;				//Boss Chest Extra Gold//Boss chests will have extra gold.
		bool useThemes = false;					//Use Device Themes//Events that equip the player with devices will try to keep all devices equipped to a consistent theme.\nWARNING: this will increase the time taken to run each event and may cause lag spikes.
		//Column
		keycode setDebugKey = -1;				//Debug Menu Key//
		bool disableForce3rdPerson = true;		//Disable 3rd Person//This mod will not force the player into 3rd person.
		bool enableSlowStrip = false;			//Use Sexlab Strip//Replace the built in stripping algorithm with the one from sexlab.\nCan fix rare cases of crashing on stripping and also give more control over what gets stripped.
		float tatSolventChance = 0.5f;			//Universal Solvent Chance//Chance to find universal solvent when looting dead bodies. Universal solvent will remove all lewd marks and tattoos.\nHaving more tattoos will slightly increase the chance of finding one.\nSet to 0 to disable.//{1}//(0,50,0.1)
		float arousalPotionChance = 5.0f;		//Frigid Wash Chance//Chance to find a potion that will reduce your arousal. The chance increases slightly with high arousal.\nYou can only cary a max of 3 at a time.//{1}//(0,100,0.1)
		float arousalPotionLibido = 10.0f;		//Frigid Wash Libido//How much your libido will decrease when drinking a frigid wash. Only works if OSLAroused is installed.//{1}//(0,100,0.1)
		bool resumeEvents = false;				//Resume Events//Events have been disabled by another mod. Enable this and exit the MCM to re-enable events.				?:? flag_events_disabled
		bool saveDependentSettings = false;		//Save Dependent Settings//If enabled your settings for this save will not be synced with all of your other saves.
		bool setAllDefaultSettings = false;		//Return to Default [WARNING]//If you exit the menu with this enabled all settings in the MCM will be reset to default.
		
		//Page Consequences
		//Header Triggers
		float consTriggerNude = 15.0f;			//Nudity//Chance for a consequence when talking to someone while nude.//{1}%//(0,100,0.1)
		float consTriggerRestrained = 50.0f;	//Restrained//Chance for a consequence when talking to someone while in heavy restraints.//{1}%//(0,100,0.1)
		float consTriggerSex = 10.0f;			//Sex//Chance for a consequence after having sex with an actor.\nWill be triggered by any scene, not just those started by this mod.//{1}%//(0,100,0.1)
		//Empty
		bool consAllowFollowers = false;		//Allow Followers//Talking to or having sex with followers can trigger consequences.
		bool consAllowCreatures = false;		//Allow Creatures//Talking to or having sex with creatures can trigger consequences.
		//Empty
		bool consUseRelationships = true;		//Use Relationships//The relationship rank of the target actor will affect how they treat you. You are less likely to see all consequences except mercy when the relationship is better.
		bool consRelationBondage = false;		//Relationship Bondage//Your friends want to tie you up so this is affected like mercy when Use Relationships is on.
		//Empty
		bool consFallthrough = false;			//Try All Consequences//With this enabled if a consequence can't trigger it will try all the other consequences.\nThis will make it so that consequences are more likely to happen, but consequences with low weights might also be more common.
		//Column
		//Header Results
		int consSexWeight = 15;					//Sex Weight//Chance for an actor to have sex with the player.\nFollows the Allowed Actors set on the Sex page.//{0}//(0,100,1)
		//Empty
		int consFineWeight = 10;				//Fine Weight//Chance for you to receive a fine.\nMust be in a town or have guards around.//{0}//(0,100,1)
		int consFineAmount = 100;				//Fine Amount//How much you will owe.//{0}//(50,1000,10)
		//Empty
		int consRandomBondageWeight = 10;		//Random Bondage Weight//Chance for a random item to be equipped.\nNothing will happen if no device can be equipped.//{0}//(0,100,1)
		bool consRandomHeavyBondage = false;	//Allow Heavy Bondage//Allow for heavy bondage to be equipped.
		bool consBondageIgnoreMax = false;		//Ignore Restraint Cap//Will ignore the restraint cap set on the main page.
		//Empty
		int consMercyWeight = 5;				//Mercy Weight//Chance that a character will feel bad for you and unlock a device, give you a key, or give you something mildly useful.//{0}//(0,100,1)
		
		//Page Sex
		//Flag flag_enable_sex					//sexEnabled
		//Flag flag_enable_random_sex			//sexRandomEnabled
		//Flag flag_sex_slave_tats				//sexRandomEnabled && CheckSTNG()
		//Header General
		bool sexEnabled = false;				//Enabled//Toggles sex on or off.\nSex will only occur from friendly characters.																						**RELOAD
		bool sexAggressiveAnims = false;		//Prefer Aggressive Animations//Prefer using aggressive animations for all sex started by this mod.																		?:? flag_enable_sex
		bool sexFilterFuta = true;				//Filter Futa Animations//This will prevent FF tagged animations for female & futa and prevent MF for female & female.\nOnly works for sexlab SE and not Sexlab P+		?:? flag_enable_sex
		bool sexRandomEnabled = false;			//Random Sex//Characters that you encounter on your journey might have sex with you!																					**RELOAD
		int sexCooldown = 30;					//Cooldown//How long in seconds after a scene ends before another can trigger.//{0}//(5,300,1)																			?:? flag_enable_random_sex
		int sexChance = 50;						//Chance//How likely a potential actor will have sex with the player.//{0}%//(0,100,1)																					?:? flag_enable_random_sex
		int sexChanceCreature = 30;				//Creature Chance//How likely a potential creature actor will have sex with the player.//{0}%//(0,100,1)																?:? flag_enable_random_sex
		//Header Arousal
		int sexBaseArousal = 90;				//Base Arousal//Minimum arousal required before modifications.\nSetting this above 100 will require modifications for any sex to occur.//{0}//(0,150,1)					?:? flag_enable_random_sex
		int sexArousalNightModifier = 5;		//Night Modifier//Modifier for arousal if it's night.//-{0}//(0,50,1)																									?:? flag_enable_random_sex
		int sexArousalNudeModifier = 15;		//Nude Modifier//Modifier for arousal if the player is nude.//-{0}//(0,50,1)																							?:? flag_enable_random_sex
		int sexArousalCollarModifier = 5;		//Collar Modifier//Modifier for arousal if a collar is worn.//-{0}//(0,50,1)																							?:? flag_enable_random_sex
		int sexArousalHeavyModifier = 10;		//Heavy Restraints Modifier//Modifier for arousal if wearing heavy restraints.//-{0}//(0,50,1)																			?:? flag_enable_random_sex
		int sexArousalBlindModifier = 5;		//Blindfold Modifier//Modifier for arousal if wearing a blindfold.//-{0}//(0,50,1)																						?:? flag_enable_random_sex
		int sexArousalBootsModifier = 0;		//Boots Modifier//Modifier for arousal if wearing restraining boots.//-{0}//(0,50,1)																					?:? flag_enable_random_sex
		int sexArousalHobbleModifier = 0;		//Hobbled Modifier//Modifier for arousal if unable to run.\nThis can be because of a device or being over-encumbered.//-{0}//(0,50,1)									?:? flag_enable_random_sex
		int sexArousalVisibleModifier = 5;		//Visible Devices Modifier//Modifier for arousal if the player has any visible devices.//-{0}//(0,50,1)																	?:? flag_enable_random_sex
		float sexArousalTattooModifier = 1.0f;	//Tattoo Modifier//Modifier for arousal for each tattoo the player has.//-{1}//(0,10,0.1)																					?:? flag_sex_slave_tats
		int sexArousalCreatureModifier = 0;		//Creature Modifier//Modifier for arousal if the aggressor is a creature.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		int sexArousalFollowerModifier = 10;	//Follower Modifier//Modifier for arousal if the aggressor is your follower.//-{0}//(0,50,1)																			?:? flag_enable_random_sex
		int sexArousalSpouseModifier = 20;		//Spouse Modifier//Modifier for arousal if the aggressor is your spouse.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		int sexArousalSummonModifier = 0;		//Summon Modifier//Modifier for arousal if the aggressor is your summon.//-{0}//(0,50,1)																				?:? flag_enable_random_sex
		//Header Search
		int sexSearchRadius = 2000;				//Search Radius//How far away can actors be from the player.//{0}//(100,10000,100)																						?:? flag_enable_random_sex
		int sexSearchInterval = 5;				//Search Interval//How often the actor search happens in seconds.//{0}//(5,120,1)																						?:? flag_enable_random_sex
		//Column
		//Header Allowed Actors
		bool sexAllowMale = true;				//Allow Male Actors//Male actors will be allowed.																														?:? flag_enable_sex
		bool sexAllowFemale = true;				//Allow Female Actors//Female actors will be allowed.																													?:? flag_enable_sex
		bool sexAllowFuta = true;				//Allow Futa Actors//Futa actors will be allowed.\nFuta actors have a female body while being defined as male in sexlab.												?:? flag_enable_sex
		bool sexAllowCreature = false;			//Allow Creature Actors//Creature actors will be allowed.																												?:? flag_enable_sex
		bool sexAllowFarmAnimals = false;		//Allow Farm Animals//Creatures like chickens, cows, and goats will be available in scenes.																				?:? flag_enable_sex
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
		
		//Page LOCKED
		//Header MCM is Locked!
		//Header Remove all of your restraints to unlock.
		//MCM_END
	} settings;

	void PlayerMessage(Translator trans) {
		auto scriptManager = ScriptingManager();
		if (settings.noMessageBoxes) {
			scriptManager.DBGNotification(trans);
		}
		else {
			scriptManager.DBGMessageBox(trans);
		}
	}

	bool GetFilterFuta() {
		return settings.sexFilterFuta;
	}

	std::string GetExcludedFollowers() {
		return settings.excludedFollowers;
	}

	bool ShouldUseGenderedChastity() {
		auto vivis = StaticDataHolder::GetSingleton()->LookupModByName("VivisCockcageSE_TRX_CBBE_devious_patch.esp");
		return settings.useGenderedChastity && vivis;
	}

	void RecalculateDeviceLists();
	void EventsCheckModIntergations();

	void ResetMCMSettings() {
		//CODEGEN_START_RESET
		settings.minGoldRequired = 20;
		SetMCMInt("minGoldRequired",settings.minGoldRequired);
		settings.eventScalingMod = 15;
		SetMCMInt("eventScalingMod",settings.eventScalingMod);
		settings.minRestraints = 1;
		SetMCMInt("minRestraints",settings.minRestraints);
		settings.maxRestraints = 3;
		SetMCMInt("maxRestraints",settings.maxRestraints);
		settings.bossAditionalRestraints = 2;
		SetMCMInt("bossAditionalRestraints",settings.bossAditionalRestraints);
		settings.restraintCap = 7;
		SetMCMInt("restraintCap",settings.restraintCap);
		settings.minArousal = 10;
		SetMCMInt("minArousal",settings.minArousal);
		settings.beltWeight = 40;
		SetMCMInt("beltWeight",settings.beltWeight);
		settings.chastityPiercingWeight = 20;
		SetMCMInt("chastityPiercingWeight",settings.chastityPiercingWeight);
		settings.braWeight = 30;
		SetMCMInt("braWeight",settings.braWeight);
		settings.plugsWeight = 50;
		SetMCMInt("plugsWeight",settings.plugsWeight);
		settings.lockingPlugsWeight = 30;
		SetMCMInt("lockingPlugsWeight",settings.lockingPlugsWeight);
		settings.inflatablePlugsWeight = 15;
		SetMCMInt("inflatablePlugsWeight",settings.inflatablePlugsWeight);
		settings.nipplePiercingsWeight = 50;
		SetMCMInt("nipplePiercingsWeight",settings.nipplePiercingsWeight);
		settings.vaginalPiercingsWeight = 50;
		SetMCMInt("vaginalPiercingsWeight",settings.vaginalPiercingsWeight);
		settings.corsetWeight = 40;
		SetMCMInt("corsetWeight",settings.corsetWeight);
		settings.beltedCorsetsWeight = 30;
		SetMCMInt("beltedCorsetsWeight",settings.beltedCorsetsWeight);
		settings.slaveHarnessWeight = 50;
		SetMCMInt("slaveHarnessWeight",settings.slaveHarnessWeight);
		settings.chastityHarnessWeight = 40;
		SetMCMInt("chastityHarnessWeight",settings.chastityHarnessWeight);
		settings.armbinderWeight = 30;
		SetMCMInt("armbinderWeight",settings.armbinderWeight);
		settings.elbowbinderWeight = 20;
		SetMCMInt("elbowbinderWeight",settings.elbowbinderWeight);
		settings.yokeWeight = 10;
		SetMCMInt("yokeWeight",settings.yokeWeight);
		settings.shacklesWeight = 20;
		SetMCMInt("shacklesWeight",settings.shacklesWeight);
		settings.straitjacketWeight = 30;
		SetMCMInt("straitjacketWeight",settings.straitjacketWeight);
		settings.straitjacketLegbinderWeight = 15;
		SetMCMInt("straitjacketLegbinderWeight",settings.straitjacketLegbinderWeight);
		settings.petSuitWeight = 10;
		SetMCMInt("petSuitWeight",settings.petSuitWeight);
		settings.collarWeight = 60;
		SetMCMInt("collarWeight",settings.collarWeight);
		settings.armCuffsWeight = 60;
		SetMCMInt("armCuffsWeight",settings.armCuffsWeight);
		settings.legCuffsWeight = 60;
		SetMCMInt("legCuffsWeight",settings.legCuffsWeight);
		settings.gagWeight = 35;
		SetMCMInt("gagWeight",settings.gagWeight);
		settings.ringGagWeight = 45;
		SetMCMInt("ringGagWeight",settings.ringGagWeight);
		settings.largeGagWeight = 30;
		SetMCMInt("largeGagWeight",settings.largeGagWeight);
		settings.largeRingGagWeight = 30;
		SetMCMInt("largeRingGagWeight",settings.largeRingGagWeight);
		settings.blindfoldWeight = 20;
		SetMCMInt("blindfoldWeight",settings.blindfoldWeight);
		settings.hoodBothWeight = 20;
		SetMCMInt("hoodBothWeight",settings.hoodBothWeight);
		settings.hoodGagWeight = 20;
		SetMCMInt("hoodGagWeight",settings.hoodGagWeight);
		settings.hoodBlindWeight = 20;
		SetMCMInt("hoodBlindWeight",settings.hoodBlindWeight);
		settings.hoodNoneWeight = 20;
		SetMCMInt("hoodNoneWeight",settings.hoodNoneWeight);
		settings.catsuitWeight = 30;
		SetMCMInt("catsuitWeight",settings.catsuitWeight);
		settings.hobbleSkirtWeight = 20;
		SetMCMInt("hobbleSkirtWeight",settings.hobbleSkirtWeight);
		settings.hobbleSkirtDifficulty = 50;
		SetMCMInt("hobbleSkirtDifficulty",settings.hobbleSkirtDifficulty);
		settings.bootsWeight = 30;
		SetMCMInt("bootsWeight",settings.bootsWeight);
		settings.glovesWeight = 30;
		SetMCMInt("glovesWeight",settings.glovesWeight);
		settings.mittensWeight = 0;
		SetMCMInt("mittensWeight",settings.mittensWeight);
		settings.eventStandardWeight = 100;
		SetMCMInt("eventStandardWeight",settings.eventStandardWeight);
		settings.eventStandardBossReduction = 20;
		SetMCMInt("eventStandardBossReduction",settings.eventStandardBossReduction);
		settings.eventOppressiveWeight = 15;
		SetMCMInt("eventOppressiveWeight",settings.eventOppressiveWeight);
		settings.eventContraptionWeight = 25;
		SetMCMInt("eventContraptionWeight",settings.eventContraptionWeight);
		settings.eventContDeviceOverride = 0;
		SetMCMInt("eventContDeviceOverride",settings.eventContDeviceOverride);
		settings.eventWickedWeight = 15;
		SetMCMInt("eventWickedWeight",settings.eventWickedWeight);
		settings.eventTattooWeight = 15;
		SetMCMInt("eventTattooWeight",settings.eventTattooWeight);
		settings.eventTattooMin = 1;
		SetMCMInt("eventTattooMin",settings.eventTattooMin);
		settings.eventTattooMax = 3;
		SetMCMInt("eventTattooMax",settings.eventTattooMax);
		settings.eventTattooCap = 8;
		SetMCMInt("eventTattooCap",settings.eventTattooCap);
		settings.followerDeviceModifier = 0;
		SetMCMInt("followerDeviceModifier",settings.followerDeviceModifier);
		settings.eventLewdMarkWeight = 10;
		SetMCMInt("eventLewdMarkWeight",settings.eventLewdMarkWeight);
		settings.eventSimpleSlaveryWeight = 0;
		SetMCMInt("eventSimpleSlaveryWeight",settings.eventSimpleSlaveryWeight);
		settings.eventSSMinRestraints = 6;
		SetMCMInt("eventSSMinRestraints",settings.eventSSMinRestraints);
		settings.eventAbadonWeight = 5;
		SetMCMInt("eventAbadonWeight",settings.eventAbadonWeight);
		settings.eventAbadonWarriorWeight = 10;
		SetMCMInt("eventAbadonWarriorWeight",settings.eventAbadonWarriorWeight);
		settings.eventAbadonWarriorCount = 5;
		SetMCMInt("eventAbadonWarriorCount",settings.eventAbadonWarriorCount);
		settings.eventAbadonScoutWeight = 10;
		SetMCMInt("eventAbadonScoutWeight",settings.eventAbadonScoutWeight);
		settings.eventAbadonScoutCount = 5;
		SetMCMInt("eventAbadonScoutCount",settings.eventAbadonScoutCount);
		settings.eventAbadonWitchWeight = 10;
		SetMCMInt("eventAbadonWitchWeight",settings.eventAbadonWitchWeight);
		settings.eventAbadonWitchCount = 5;
		SetMCMInt("eventAbadonWitchCount",settings.eventAbadonWitchCount);
		settings.LMAllureWeight = 10;
		SetMCMInt("LMAllureWeight",settings.LMAllureWeight);
		settings.LMAllureMod = 5;
		SetMCMInt("LMAllureMod",settings.LMAllureMod);
		settings.LMAllureSex = 25;
		SetMCMInt("LMAllureSex",settings.LMAllureSex);
		settings.LMHeatWeight = 10;
		SetMCMInt("LMHeatWeight",settings.LMHeatWeight);
		settings.LMHeatMod = 30;
		SetMCMInt("LMHeatMod",settings.LMHeatMod);
		settings.LMHeatContainerCount = 50;
		SetMCMInt("LMHeatContainerCount",settings.LMHeatContainerCount);
		settings.LMBrandingWeight = 10;
		SetMCMInt("LMBrandingWeight",settings.LMBrandingWeight);
		settings.LMBrandingTotal = 12;
		SetMCMInt("LMBrandingTotal",settings.LMBrandingTotal);
		settings.LMBondageWeight = 5;
		SetMCMInt("LMBondageWeight",settings.LMBondageWeight);
		settings.LMBondageDeviceCount = 8;
		SetMCMInt("LMBondageDeviceCount",settings.LMBondageDeviceCount);
		settings.LMNudityWeight = 15;
		SetMCMInt("LMNudityWeight",settings.LMNudityWeight);
		settings.LMNudityTalkTimes = 35;
		SetMCMInt("LMNudityTalkTimes",settings.LMNudityTalkTimes);
		settings.LMHealslutWeight = 5;
		SetMCMInt("LMHealslutWeight",settings.LMHealslutWeight);
		settings.LMHealslutHealing = 2000;
		SetMCMInt("LMHealslutHealing",settings.LMHealslutHealing);
		settings.oppSummonerCollarWeight = 20;
		SetMCMInt("oppSummonerCollarWeight",settings.oppSummonerCollarWeight);
		settings.oppSummonerSexCount = 15;
		SetMCMInt("oppSummonerSexCount",settings.oppSummonerSexCount);
		settings.oppSMinSummonArousal = 90;
		SetMCMInt("oppSMinSummonArousal",settings.oppSMinSummonArousal);
		settings.oppDwarvenCuirassWeight = 15;
		SetMCMInt("oppDwarvenCuirassWeight",settings.oppDwarvenCuirassWeight);
		settings.oppDwarvenValueNeeded = 200;
		SetMCMInt("oppDwarvenValueNeeded",settings.oppDwarvenValueNeeded);
		settings.oppDwarvenArousal = 25;
		SetMCMInt("oppDwarvenArousal",settings.oppDwarvenArousal);
		settings.oppNocturnalWeight = 10;
		SetMCMInt("oppNocturnalWeight",settings.oppNocturnalWeight);
		settings.oppNocturnalSexCount = 3;
		SetMCMInt("oppNocturnalSexCount",settings.oppNocturnalSexCount);
		settings.oppNocturnalPeople = 7;
		SetMCMInt("oppNocturnalPeople",settings.oppNocturnalPeople);
		settings.oppNocturnalArousal = 35;
		SetMCMInt("oppNocturnalArousal",settings.oppNocturnalArousal);
		settings.oppLivingLatexWeight = 20;
		SetMCMInt("oppLivingLatexWeight",settings.oppLivingLatexWeight);
		settings.oppLivingLatexStartTime = 15;
		SetMCMInt("oppLivingLatexStartTime",settings.oppLivingLatexStartTime);
		settings.oppMadnessPlugWeight = 25;
		SetMCMInt("oppMadnessPlugWeight",settings.oppMadnessPlugWeight);
		settings.oppMadnessPlugIterations = 5;
		SetMCMInt("oppMadnessPlugIterations",settings.oppMadnessPlugIterations);
		settings.oppMadnessplugOrgasms = 6;
		SetMCMInt("oppMadnessplugOrgasms",settings.oppMadnessplugOrgasms);
		settings.minKeysLooted = 1;
		SetMCMInt("minKeysLooted",settings.minKeysLooted);
		settings.maxKeysLooted = 1;
		SetMCMInt("maxKeysLooted",settings.maxKeysLooted);
		settings.maxHeldKeys = 3;
		SetMCMInt("maxHeldKeys",settings.maxHeldKeys);
		settings.restraintsKeyWeight = 80;
		SetMCMInt("restraintsKeyWeight",settings.restraintsKeyWeight);
		settings.chastityKeyWeight = 50;
		SetMCMInt("chastityKeyWeight",settings.chastityKeyWeight);
		settings.piercingToolWeight = 20;
		SetMCMInt("piercingToolWeight",settings.piercingToolWeight);
		settings.consSexWeight = 15;
		SetMCMInt("consSexWeight",settings.consSexWeight);
		settings.consFineWeight = 10;
		SetMCMInt("consFineWeight",settings.consFineWeight);
		settings.consFineAmount = 100;
		SetMCMInt("consFineAmount",settings.consFineAmount);
		settings.consRandomBondageWeight = 10;
		SetMCMInt("consRandomBondageWeight",settings.consRandomBondageWeight);
		settings.consMercyWeight = 5;
		SetMCMInt("consMercyWeight",settings.consMercyWeight);
		settings.sexCooldown = 30;
		SetMCMInt("sexCooldown",settings.sexCooldown);
		settings.sexChance = 50;
		SetMCMInt("sexChance",settings.sexChance);
		settings.sexChanceCreature = 30;
		SetMCMInt("sexChanceCreature",settings.sexChanceCreature);
		settings.sexBaseArousal = 90;
		SetMCMInt("sexBaseArousal",settings.sexBaseArousal);
		settings.sexArousalNightModifier = 5;
		SetMCMInt("sexArousalNightModifier",settings.sexArousalNightModifier);
		settings.sexArousalNudeModifier = 15;
		SetMCMInt("sexArousalNudeModifier",settings.sexArousalNudeModifier);
		settings.sexArousalCollarModifier = 5;
		SetMCMInt("sexArousalCollarModifier",settings.sexArousalCollarModifier);
		settings.sexArousalHeavyModifier = 10;
		SetMCMInt("sexArousalHeavyModifier",settings.sexArousalHeavyModifier);
		settings.sexArousalBlindModifier = 5;
		SetMCMInt("sexArousalBlindModifier",settings.sexArousalBlindModifier);
		settings.sexArousalBootsModifier = 0;
		SetMCMInt("sexArousalBootsModifier",settings.sexArousalBootsModifier);
		settings.sexArousalHobbleModifier = 0;
		SetMCMInt("sexArousalHobbleModifier",settings.sexArousalHobbleModifier);
		settings.sexArousalVisibleModifier = 5;
		SetMCMInt("sexArousalVisibleModifier",settings.sexArousalVisibleModifier);
		settings.sexArousalCreatureModifier = 0;
		SetMCMInt("sexArousalCreatureModifier",settings.sexArousalCreatureModifier);
		settings.sexArousalFollowerModifier = 10;
		SetMCMInt("sexArousalFollowerModifier",settings.sexArousalFollowerModifier);
		settings.sexArousalSpouseModifier = 20;
		SetMCMInt("sexArousalSpouseModifier",settings.sexArousalSpouseModifier);
		settings.sexArousalSummonModifier = 0;
		SetMCMInt("sexArousalSummonModifier",settings.sexArousalSummonModifier);
		settings.sexSearchRadius = 2000;
		SetMCMInt("sexSearchRadius",settings.sexSearchRadius);
		settings.sexSearchInterval = 5;
		SetMCMInt("sexSearchInterval",settings.sexSearchInterval);
		settings.sexRequiredPlayerArousal = 0;
		SetMCMInt("sexRequiredPlayerArousal",settings.sexRequiredPlayerArousal);
		settings.sexRequiredPlayerTattoos = 0;
		SetMCMInt("sexRequiredPlayerTattoos",settings.sexRequiredPlayerTattoos);
		settings.sexChanceFollower = -1;
		SetMCMInt("sexChanceFollower",settings.sexChanceFollower);
		settings.sexChanceSpouse = -1;
		SetMCMInt("sexChanceSpouse",settings.sexChanceSpouse);
		settings.sexChanceSummon = -1;
		SetMCMInt("sexChanceSummon",settings.sexChanceSummon);
		settings.LMAllureColor = 0xcf11c5;
		SetMCMInt("LMAllureColor",settings.LMAllureColor);
		settings.LMHeatColor = 0xe3143a;
		SetMCMInt("LMHeatColor",settings.LMHeatColor);
		settings.LMBrandingColor = 0x220022;
		SetMCMInt("LMBrandingColor",settings.LMBrandingColor);
		settings.LMBondageColor = 0x7908cf;
		SetMCMInt("LMBondageColor",settings.LMBondageColor);
		settings.LMNudityColor = 0xd676cb;
		SetMCMInt("LMNudityColor",settings.LMNudityColor);
		settings.LMHealslutColor = 0xffbb45;
		SetMCMInt("LMHealslutColor",settings.LMHealslutColor);
		settings.setDebugKey = -1;
		SetMCMInt("setDebugKey",settings.setDebugKey);
		settings.baseChance = 6.5f;
		SetMCMFloat("baseChance",settings.baseChance);
		settings.containerModifier = 1.0f;
		SetMCMFloat("containerModifier",settings.containerModifier);
		settings.bossContainerModifier = 2.0f;
		SetMCMFloat("bossContainerModifier",settings.bossContainerModifier);
		settings.deadBodyModifier = 1.3f;
		SetMCMFloat("deadBodyModifier",settings.deadBodyModifier);
		settings.pickpocketModifier = 1.3f;
		SetMCMFloat("pickpocketModifier",settings.pickpocketModifier);
		settings.doorModifier = 1.0f;
		SetMCMFloat("doorModifier",settings.doorModifier);
		settings.lockedModifier = 2.0f;
		SetMCMFloat("lockedModifier",settings.lockedModifier);
		settings.lockDifficultyModifier = 1.3f;
		SetMCMFloat("lockDifficultyModifier",settings.lockDifficultyModifier);
		settings.arousalModifier = 1.4f;
		SetMCMFloat("arousalModifier",settings.arousalModifier);
		settings.eventContraptionTime = 4.0f;
		SetMCMFloat("eventContraptionTime",settings.eventContraptionTime);
		settings.LMBrandingChance = 1.5f;
		SetMCMFloat("LMBrandingChance",settings.LMBrandingChance);
		settings.LMBondageChance = 5.0f;
		SetMCMFloat("LMBondageChance",settings.LMBondageChance);
		settings.oppSummonChance = 1.5f;
		SetMCMFloat("oppSummonChance",settings.oppSummonChance);
		settings.oppNocturnalHandChance = 3.5f;
		SetMCMFloat("oppNocturnalHandChance",settings.oppNocturnalHandChance);
		settings.oppNocturnalRecastChance = 33.3f;
		SetMCMFloat("oppNocturnalRecastChance",settings.oppNocturnalRecastChance);
		settings.oppLivingLatexGem = 6.0f;
		SetMCMFloat("oppLivingLatexGem",settings.oppLivingLatexGem);
		settings.oppLivingLatexMore = 0.0f;
		SetMCMFloat("oppLivingLatexMore",settings.oppLivingLatexMore);
		settings.playerHomeModifier = 0.0f;
		SetMCMFloat("playerHomeModifier",settings.playerHomeModifier);
		settings.cityModifier = 0.0f;
		SetMCMFloat("cityModifier",settings.cityModifier);
		settings.townModifier = 0.0f;
		SetMCMFloat("townModifier",settings.townModifier);
		settings.banditModifier = 1.1f;
		SetMCMFloat("banditModifier",settings.banditModifier);
		settings.draugrModifier = 1.2f;
		SetMCMFloat("draugrModifier",settings.draugrModifier);
		settings.lockedLocationBypass = 0.6f;
		SetMCMFloat("lockedLocationBypass",settings.lockedLocationBypass);
		settings.theftLocationBypass = 1.1f;
		SetMCMFloat("theftLocationBypass",settings.theftLocationBypass);
		settings.dwarvenModifier = 1.2f;
		SetMCMFloat("dwarvenModifier",settings.dwarvenModifier);
		settings.falmerModifier = 1.3f;
		SetMCMFloat("falmerModifier",settings.falmerModifier);
		settings.forswornModifier = 1.1f;
		SetMCMFloat("forswornModifier",settings.forswornModifier);
		settings.vampireModifier = 1.5f;
		SetMCMFloat("vampireModifier",settings.vampireModifier);
		settings.warlockModifier = 1.5f;
		SetMCMFloat("warlockModifier",settings.warlockModifier);
		settings.dragonLairModifier = 2.0f;
		SetMCMFloat("dragonLairModifier",settings.dragonLairModifier);
		settings.apocryphaModifier = 2.0f;
		SetMCMFloat("apocryphaModifier",settings.apocryphaModifier);
		settings.wildernessModifier = 0.9f;
		SetMCMFloat("wildernessModifier",settings.wildernessModifier);
		settings.keyLossChance = 80.0f;
		SetMCMFloat("keyLossChance",settings.keyLossChance);
		settings.keyChance = 7.0f;
		SetMCMFloat("keyChance",settings.keyChance);
		settings.keyBonus = 1.0f;
		SetMCMFloat("keyBonus",settings.keyBonus);
		settings.keyPickpocketBonus = 2.0f;
		SetMCMFloat("keyPickpocketBonus",settings.keyPickpocketBonus);
		settings.magicKeyChance = 20.0f;
		SetMCMFloat("magicKeyChance",settings.magicKeyChance);
		settings.keyLuckyBonus = 1.75f;
		SetMCMFloat("keyLuckyBonus",settings.keyLuckyBonus);
		settings.rDeviceBaseChance = 1.5f;
		SetMCMFloat("rDeviceBaseChance",settings.rDeviceBaseChance);
		settings.rDeviceLuckyBonus = 2.5f;
		SetMCMFloat("rDeviceLuckyBonus",settings.rDeviceLuckyBonus);
		settings.tatSolventChance = 0.5f;
		SetMCMFloat("tatSolventChance",settings.tatSolventChance);
		settings.arousalPotionChance = 5.0f;
		SetMCMFloat("arousalPotionChance",settings.arousalPotionChance);
		settings.arousalPotionLibido = 10.0f;
		SetMCMFloat("arousalPotionLibido",settings.arousalPotionLibido);
		settings.consTriggerNude = 15.0f;
		SetMCMFloat("consTriggerNude",settings.consTriggerNude);
		settings.consTriggerRestrained = 50.0f;
		SetMCMFloat("consTriggerRestrained",settings.consTriggerRestrained);
		settings.consTriggerSex = 10.0f;
		SetMCMFloat("consTriggerSex",settings.consTriggerSex);
		settings.sexArousalTattooModifier = 1.0f;
		SetMCMFloat("sexArousalTattooModifier",settings.sexArousalTattooModifier);
		settings.onlyLockedDoors = true;
		SetMCMBool("onlyLockedDoors",settings.onlyLockedDoors);
		settings.eventScaling = true;
		SetMCMBool("eventScaling",settings.eventScaling);
		settings.bossOnlyHeavy = true;
		SetMCMBool("bossOnlyHeavy",settings.bossOnlyHeavy);
		settings.stripPlayerOnEvent = true;
		SetMCMBool("stripPlayerOnEvent",settings.stripPlayerOnEvent);
		settings.stripOnlyKeywords = true;
		SetMCMBool("stripOnlyKeywords",settings.stripOnlyKeywords);
		settings.beltPlugs = true;
		SetMCMBool("beltPlugs",settings.beltPlugs);
		settings.useGenderedChastity = true;
		SetMCMBool("useGenderedChastity",settings.useGenderedChastity);
		settings.plugsDontCount = true;
		SetMCMBool("plugsDontCount",settings.plugsDontCount);
		settings.allowLegShackles = false;
		SetMCMBool("allowLegShackles",settings.allowLegShackles);
		settings.eventContDevices = true;
		SetMCMBool("eventContDevices",settings.eventContDevices);
		settings.eventContAllDevices = false;
		SetMCMBool("eventContAllDevices",settings.eventContAllDevices);
		settings.allowFollowerEvents = false;
		SetMCMBool("allowFollowerEvents",settings.allowFollowerEvents);
		settings.onlyFemaleFollowers = true;
		SetMCMBool("onlyFemaleFollowers",settings.onlyFemaleFollowers);
		settings.followerHeavyRestraints = false;
		SetMCMBool("followerHeavyRestraints",settings.followerHeavyRestraints);
		settings.onlyUseUnforgivingDevices = true;
		SetMCMBool("onlyUseUnforgivingDevices",settings.onlyUseUnforgivingDevices);
		settings.udUseAbadon = false;
		SetMCMBool("udUseAbadon",settings.udUseAbadon);
		settings.udUseAbadonSets = false;
		SetMCMBool("udUseAbadonSets",settings.udUseAbadonSets);
		settings.udUseMisc = true;
		SetMCMBool("udUseMisc",settings.udUseMisc);
		settings.ANDSexTopless = true;
		SetMCMBool("ANDSexTopless",settings.ANDSexTopless);
		settings.ANDSexBottomless = true;
		SetMCMBool("ANDSexBottomless",settings.ANDSexBottomless);
		settings.ANDSexShowingChest = true;
		SetMCMBool("ANDSexShowingChest",settings.ANDSexShowingChest);
		settings.ANDSexShowingGenitals = true;
		SetMCMBool("ANDSexShowingGenitals",settings.ANDSexShowingGenitals);
		settings.ANDSexShowingAss = false;
		SetMCMBool("ANDSexShowingAss",settings.ANDSexShowingAss);
		settings.ANDSexShowingBra = false;
		SetMCMBool("ANDSexShowingBra",settings.ANDSexShowingBra);
		settings.ANDSexShowingUnderwear = false;
		SetMCMBool("ANDSexShowingUnderwear",settings.ANDSexShowingUnderwear);
		settings.ANDConsTopless = true;
		SetMCMBool("ANDConsTopless",settings.ANDConsTopless);
		settings.ANDConsBottomless = true;
		SetMCMBool("ANDConsBottomless",settings.ANDConsBottomless);
		settings.ANDConsShowingChest = true;
		SetMCMBool("ANDConsShowingChest",settings.ANDConsShowingChest);
		settings.ANDConsShowingGenitals = true;
		SetMCMBool("ANDConsShowingGenitals",settings.ANDConsShowingGenitals);
		settings.ANDConsShowingAss = false;
		SetMCMBool("ANDConsShowingAss",settings.ANDConsShowingAss);
		settings.ANDConsShowingBra = false;
		SetMCMBool("ANDConsShowingBra",settings.ANDConsShowingBra);
		settings.ANDConsShowingUnderwear = false;
		SetMCMBool("ANDConsShowingUnderwear",settings.ANDConsShowingUnderwear);
		settings.LMBrandingPunish = true;
		SetMCMBool("LMBrandingPunish",settings.LMBrandingPunish);
		settings.LMNudityChestOnly = false;
		SetMCMBool("LMNudityChestOnly",settings.LMNudityChestOnly);
		settings.oppOneAtATime = true;
		SetMCMBool("oppOneAtATime",settings.oppOneAtATime);
		settings.oppSCollarDrainsMagicka = true;
		SetMCMBool("oppSCollarDrainsMagicka",settings.oppSCollarDrainsMagicka);
		settings.oppSCollarAutoRemove = true;
		SetMCMBool("oppSCollarAutoRemove",settings.oppSCollarAutoRemove);
		settings.oppDwarvenHeavyRestraint = false;
		SetMCMBool("oppDwarvenHeavyRestraint",settings.oppDwarvenHeavyRestraint);
		settings.oppDwarvenRequireLoc = true;
		SetMCMBool("oppDwarvenRequireLoc",settings.oppDwarvenRequireLoc);
		settings.oppLivingLatexHeavy = false;
		SetMCMBool("oppLivingLatexHeavy",settings.oppLivingLatexHeavy);
		settings.oppLivingLatexRequireRem = true;
		SetMCMBool("oppLivingLatexRequireRem",settings.oppLivingLatexRequireRem);
		settings.oppLivingLatexOpen = false;
		SetMCMBool("oppLivingLatexOpen",settings.oppLivingLatexOpen);
		settings.oppMadnessAllOrgasms = false;
		SetMCMBool("oppMadnessAllOrgasms",settings.oppMadnessAllOrgasms);
		settings.oppMadnessBeltFilter = true;
		SetMCMBool("oppMadnessBeltFilter",settings.oppMadnessBeltFilter);
		settings.oppMadnessChaos = false;
		SetMCMBool("oppMadnessChaos",settings.oppMadnessChaos);
		settings.useLocationModifiers = true;
		SetMCMBool("useLocationModifiers",settings.useLocationModifiers);
		settings.keyForgiveness = true;
		SetMCMBool("keyForgiveness",settings.keyForgiveness);
		settings.magicKeyOppressive = false;
		SetMCMBool("magicKeyOppressive",settings.magicKeyOppressive);
		settings.preferRelevantKeys = true;
		SetMCMBool("preferRelevantKeys",settings.preferRelevantKeys);
		settings.vanishingKeys = true;
		SetMCMBool("vanishingKeys",settings.vanishingKeys);
		settings.enableQuestInteractions = true;
		SetMCMBool("enableQuestInteractions",settings.enableQuestInteractions);
		settings.enableQIMalkoran = true;
		SetMCMBool("enableQIMalkoran",settings.enableQIMalkoran);
		settings.enableQISanguine = true;
		SetMCMBool("enableQISanguine",settings.enableQISanguine);
		settings.enableQIBlackStar = true;
		SetMCMBool("enableQIBlackStar",settings.enableQIBlackStar);
		settings.enableQIMindOfMadness = true;
		SetMCMBool("enableQIMindOfMadness",settings.enableQIMindOfMadness);
		settings.enableQILaidToRest = true;
		SetMCMBool("enableQILaidToRest",settings.enableQILaidToRest);
		settings.enableQICriedWolf = true;
		SetMCMBool("enableQICriedWolf",settings.enableQICriedWolf);
		settings.enableQIProvingHonor = true;
		SetMCMBool("enableQIProvingHonor",settings.enableQIProvingHonor);
		settings.enableQISaarthal = true;
		SetMCMBool("enableQISaarthal",settings.enableQISaarthal);
		settings.enableQIBrelyna = true;
		SetMCMBool("enableQIBrelyna",settings.enableQIBrelyna);
		settings.enableQIDwemerMuseum = true;
		SetMCMBool("enableQIDwemerMuseum",settings.enableQIDwemerMuseum);
		settings.enableQITrinityRestored = true;
		SetMCMBool("enableQITrinityRestored",settings.enableQITrinityRestored);
		settings.enableQIThalmorEmbassy = true;
		SetMCMBool("enableQIThalmorEmbassy",settings.enableQIThalmorEmbassy);
		settings.enableQIRingmaker = true;
		SetMCMBool("enableQIRingmaker",settings.enableQIRingmaker);
		settings.oppDeviceAntiCheat = true;
		SetMCMBool("oppDeviceAntiCheat",settings.oppDeviceAntiCheat);
		settings.generalDeviceAntiCheat = false;
		SetMCMBool("generalDeviceAntiCheat",settings.generalDeviceAntiCheat);
		settings.noMessageBoxes = false;
		SetMCMBool("noMessageBoxes",settings.noMessageBoxes);
		settings.bossChestUseModelPath = true;
		SetMCMBool("bossChestUseModelPath",settings.bossChestUseModelPath);
		settings.dragonHoard = true;
		SetMCMBool("dragonHoard",settings.dragonHoard);
		settings.bossExtraGold = true;
		SetMCMBool("bossExtraGold",settings.bossExtraGold);
		settings.useThemes = false;
		SetMCMBool("useThemes",settings.useThemes);
		settings.disableForce3rdPerson = true;
		SetMCMBool("disableForce3rdPerson",settings.disableForce3rdPerson);
		settings.enableSlowStrip = false;
		SetMCMBool("enableSlowStrip",settings.enableSlowStrip);
		settings.resumeEvents = false;
		SetMCMBool("resumeEvents",settings.resumeEvents);
		settings.saveDependentSettings = false;
		SetMCMBool("saveDependentSettings",settings.saveDependentSettings);
		settings.setAllDefaultSettings = false;
		SetMCMBool("setAllDefaultSettings",settings.setAllDefaultSettings);
		settings.consAllowFollowers = false;
		SetMCMBool("consAllowFollowers",settings.consAllowFollowers);
		settings.consAllowCreatures = false;
		SetMCMBool("consAllowCreatures",settings.consAllowCreatures);
		settings.consUseRelationships = true;
		SetMCMBool("consUseRelationships",settings.consUseRelationships);
		settings.consRelationBondage = false;
		SetMCMBool("consRelationBondage",settings.consRelationBondage);
		settings.consFallthrough = false;
		SetMCMBool("consFallthrough",settings.consFallthrough);
		settings.consRandomHeavyBondage = false;
		SetMCMBool("consRandomHeavyBondage",settings.consRandomHeavyBondage);
		settings.consBondageIgnoreMax = false;
		SetMCMBool("consBondageIgnoreMax",settings.consBondageIgnoreMax);
		settings.sexEnabled = false;
		SetMCMBool("sexEnabled",settings.sexEnabled);
		settings.sexAggressiveAnims = false;
		SetMCMBool("sexAggressiveAnims",settings.sexAggressiveAnims);
		settings.sexFilterFuta = true;
		SetMCMBool("sexFilterFuta",settings.sexFilterFuta);
		settings.sexRandomEnabled = false;
		SetMCMBool("sexRandomEnabled",settings.sexRandomEnabled);
		settings.sexAllowMale = true;
		SetMCMBool("sexAllowMale",settings.sexAllowMale);
		settings.sexAllowFemale = true;
		SetMCMBool("sexAllowFemale",settings.sexAllowFemale);
		settings.sexAllowFuta = true;
		SetMCMBool("sexAllowFuta",settings.sexAllowFuta);
		settings.sexAllowCreature = false;
		SetMCMBool("sexAllowCreature",settings.sexAllowCreature);
		settings.sexAllowFarmAnimals = false;
		SetMCMBool("sexAllowFarmAnimals",settings.sexAllowFarmAnimals);
		settings.sexRequireAll = false;
		SetMCMBool("sexRequireAll",settings.sexRequireAll);
		settings.sexRequireBindings = true;
		SetMCMBool("sexRequireBindings",settings.sexRequireBindings);
		settings.sexRequireCollar = false;
		SetMCMBool("sexRequireCollar",settings.sexRequireCollar);
		settings.sexRequireHeavy = false;
		SetMCMBool("sexRequireHeavy",settings.sexRequireHeavy);
		settings.sexRequireNude = true;
		SetMCMBool("sexRequireNude",settings.sexRequireNude);
		settings.sexAlwaysAllowFollowers = true;
		SetMCMBool("sexAlwaysAllowFollowers",settings.sexAlwaysAllowFollowers);
		settings.sexAlwaysAllowSpouse = true;
		SetMCMBool("sexAlwaysAllowSpouse",settings.sexAlwaysAllowSpouse);
		settings.sexAlwaysAllowSummons = false;
		SetMCMBool("sexAlwaysAllowSummons",settings.sexAlwaysAllowSummons);
		settings.excludedFollowers = "";
		SetMCMString("excludedFollowers",settings.excludedFollowers);
		settings.LMNudityAditionalForms = "";
		SetMCMString("LMNudityAditionalForms",settings.LMNudityAditionalForms);
		//CODEGEN_END_RESET
	}

	void SaveMCMSettings() {
		if (settings.saveDependentSettings) {
			return;
		}

		std::ofstream o(SETTINGS_FILE);
		nlohmann::json j = nlohmann::json{
			//CODEGEN_START_TOJSON
			{"minGoldRequired", settings.minGoldRequired},
			{"eventScalingMod", settings.eventScalingMod},
			{"minRestraints", settings.minRestraints},
			{"maxRestraints", settings.maxRestraints},
			{"bossAditionalRestraints", settings.bossAditionalRestraints},
			{"restraintCap", settings.restraintCap},
			{"minArousal", settings.minArousal},
			{"beltWeight", settings.beltWeight},
			{"chastityPiercingWeight", settings.chastityPiercingWeight},
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
			{"eventStandardWeight", settings.eventStandardWeight},
			{"eventStandardBossReduction", settings.eventStandardBossReduction},
			{"eventOppressiveWeight", settings.eventOppressiveWeight},
			{"eventContraptionWeight", settings.eventContraptionWeight},
			{"eventContDeviceOverride", settings.eventContDeviceOverride},
			{"eventWickedWeight", settings.eventWickedWeight},
			{"eventTattooWeight", settings.eventTattooWeight},
			{"eventTattooMin", settings.eventTattooMin},
			{"eventTattooMax", settings.eventTattooMax},
			{"eventTattooCap", settings.eventTattooCap},
			{"followerDeviceModifier", settings.followerDeviceModifier},
			{"eventLewdMarkWeight", settings.eventLewdMarkWeight},
			{"eventSimpleSlaveryWeight", settings.eventSimpleSlaveryWeight},
			{"eventSSMinRestraints", settings.eventSSMinRestraints},
			{"eventAbadonWeight", settings.eventAbadonWeight},
			{"eventAbadonWarriorWeight", settings.eventAbadonWarriorWeight},
			{"eventAbadonWarriorCount", settings.eventAbadonWarriorCount},
			{"eventAbadonScoutWeight", settings.eventAbadonScoutWeight},
			{"eventAbadonScoutCount", settings.eventAbadonScoutCount},
			{"eventAbadonWitchWeight", settings.eventAbadonWitchWeight},
			{"eventAbadonWitchCount", settings.eventAbadonWitchCount},
			{"LMAllureWeight", settings.LMAllureWeight},
			{"LMAllureMod", settings.LMAllureMod},
			{"LMAllureSex", settings.LMAllureSex},
			{"LMHeatWeight", settings.LMHeatWeight},
			{"LMHeatMod", settings.LMHeatMod},
			{"LMHeatContainerCount", settings.LMHeatContainerCount},
			{"LMBrandingWeight", settings.LMBrandingWeight},
			{"LMBrandingTotal", settings.LMBrandingTotal},
			{"LMBondageWeight", settings.LMBondageWeight},
			{"LMBondageDeviceCount", settings.LMBondageDeviceCount},
			{"LMNudityWeight", settings.LMNudityWeight},
			{"LMNudityTalkTimes", settings.LMNudityTalkTimes},
			{"LMHealslutWeight", settings.LMHealslutWeight},
			{"LMHealslutHealing", settings.LMHealslutHealing},
			{"oppSummonerCollarWeight", settings.oppSummonerCollarWeight},
			{"oppSummonerSexCount", settings.oppSummonerSexCount},
			{"oppSMinSummonArousal", settings.oppSMinSummonArousal},
			{"oppDwarvenCuirassWeight", settings.oppDwarvenCuirassWeight},
			{"oppDwarvenValueNeeded", settings.oppDwarvenValueNeeded},
			{"oppDwarvenArousal", settings.oppDwarvenArousal},
			{"oppNocturnalWeight", settings.oppNocturnalWeight},
			{"oppNocturnalSexCount", settings.oppNocturnalSexCount},
			{"oppNocturnalPeople", settings.oppNocturnalPeople},
			{"oppNocturnalArousal", settings.oppNocturnalArousal},
			{"oppLivingLatexWeight", settings.oppLivingLatexWeight},
			{"oppLivingLatexStartTime", settings.oppLivingLatexStartTime},
			{"oppMadnessPlugWeight", settings.oppMadnessPlugWeight},
			{"oppMadnessPlugIterations", settings.oppMadnessPlugIterations},
			{"oppMadnessplugOrgasms", settings.oppMadnessplugOrgasms},
			{"minKeysLooted", settings.minKeysLooted},
			{"maxKeysLooted", settings.maxKeysLooted},
			{"maxHeldKeys", settings.maxHeldKeys},
			{"restraintsKeyWeight", settings.restraintsKeyWeight},
			{"chastityKeyWeight", settings.chastityKeyWeight},
			{"piercingToolWeight", settings.piercingToolWeight},
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
			{"sexSearchRadius", settings.sexSearchRadius},
			{"sexSearchInterval", settings.sexSearchInterval},
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
			{"eventContraptionTime", settings.eventContraptionTime},
			{"LMBrandingChance", settings.LMBrandingChance},
			{"LMBondageChance", settings.LMBondageChance},
			{"oppSummonChance", settings.oppSummonChance},
			{"oppNocturnalHandChance", settings.oppNocturnalHandChance},
			{"oppNocturnalRecastChance", settings.oppNocturnalRecastChance},
			{"oppLivingLatexGem", settings.oppLivingLatexGem},
			{"oppLivingLatexMore", settings.oppLivingLatexMore},
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
			{"keyLossChance", settings.keyLossChance},
			{"keyChance", settings.keyChance},
			{"keyBonus", settings.keyBonus},
			{"keyPickpocketBonus", settings.keyPickpocketBonus},
			{"magicKeyChance", settings.magicKeyChance},
			{"keyLuckyBonus", settings.keyLuckyBonus},
			{"rDeviceBaseChance", settings.rDeviceBaseChance},
			{"rDeviceLuckyBonus", settings.rDeviceLuckyBonus},
			{"tatSolventChance", settings.tatSolventChance},
			{"arousalPotionChance", settings.arousalPotionChance},
			{"arousalPotionLibido", settings.arousalPotionLibido},
			{"consTriggerNude", settings.consTriggerNude},
			{"consTriggerRestrained", settings.consTriggerRestrained},
			{"consTriggerSex", settings.consTriggerSex},
			{"sexArousalTattooModifier", settings.sexArousalTattooModifier},
			{"onlyLockedDoors", settings.onlyLockedDoors},
			{"eventScaling", settings.eventScaling},
			{"bossOnlyHeavy", settings.bossOnlyHeavy},
			{"stripPlayerOnEvent", settings.stripPlayerOnEvent},
			{"stripOnlyKeywords", settings.stripOnlyKeywords},
			{"beltPlugs", settings.beltPlugs},
			{"useGenderedChastity", settings.useGenderedChastity},
			{"plugsDontCount", settings.plugsDontCount},
			{"allowLegShackles", settings.allowLegShackles},
			{"eventContDevices", settings.eventContDevices},
			{"eventContAllDevices", settings.eventContAllDevices},
			{"allowFollowerEvents", settings.allowFollowerEvents},
			{"onlyFemaleFollowers", settings.onlyFemaleFollowers},
			{"followerHeavyRestraints", settings.followerHeavyRestraints},
			{"onlyUseUnforgivingDevices", settings.onlyUseUnforgivingDevices},
			{"udUseAbadon", settings.udUseAbadon},
			{"udUseAbadonSets", settings.udUseAbadonSets},
			{"udUseMisc", settings.udUseMisc},
			{"ANDSexTopless", settings.ANDSexTopless},
			{"ANDSexBottomless", settings.ANDSexBottomless},
			{"ANDSexShowingChest", settings.ANDSexShowingChest},
			{"ANDSexShowingGenitals", settings.ANDSexShowingGenitals},
			{"ANDSexShowingAss", settings.ANDSexShowingAss},
			{"ANDSexShowingBra", settings.ANDSexShowingBra},
			{"ANDSexShowingUnderwear", settings.ANDSexShowingUnderwear},
			{"ANDConsTopless", settings.ANDConsTopless},
			{"ANDConsBottomless", settings.ANDConsBottomless},
			{"ANDConsShowingChest", settings.ANDConsShowingChest},
			{"ANDConsShowingGenitals", settings.ANDConsShowingGenitals},
			{"ANDConsShowingAss", settings.ANDConsShowingAss},
			{"ANDConsShowingBra", settings.ANDConsShowingBra},
			{"ANDConsShowingUnderwear", settings.ANDConsShowingUnderwear},
			{"LMBrandingPunish", settings.LMBrandingPunish},
			{"LMNudityChestOnly", settings.LMNudityChestOnly},
			{"oppOneAtATime", settings.oppOneAtATime},
			{"oppSCollarDrainsMagicka", settings.oppSCollarDrainsMagicka},
			{"oppSCollarAutoRemove", settings.oppSCollarAutoRemove},
			{"oppDwarvenHeavyRestraint", settings.oppDwarvenHeavyRestraint},
			{"oppDwarvenRequireLoc", settings.oppDwarvenRequireLoc},
			{"oppLivingLatexHeavy", settings.oppLivingLatexHeavy},
			{"oppLivingLatexRequireRem", settings.oppLivingLatexRequireRem},
			{"oppLivingLatexOpen", settings.oppLivingLatexOpen},
			{"oppMadnessAllOrgasms", settings.oppMadnessAllOrgasms},
			{"oppMadnessBeltFilter", settings.oppMadnessBeltFilter},
			{"oppMadnessChaos", settings.oppMadnessChaos},
			{"useLocationModifiers", settings.useLocationModifiers},
			{"keyForgiveness", settings.keyForgiveness},
			{"magicKeyOppressive", settings.magicKeyOppressive},
			{"preferRelevantKeys", settings.preferRelevantKeys},
			{"vanishingKeys", settings.vanishingKeys},
			{"enableQuestInteractions", settings.enableQuestInteractions},
			{"enableQIMalkoran", settings.enableQIMalkoran},
			{"enableQISanguine", settings.enableQISanguine},
			{"enableQIBlackStar", settings.enableQIBlackStar},
			{"enableQIMindOfMadness", settings.enableQIMindOfMadness},
			{"enableQILaidToRest", settings.enableQILaidToRest},
			{"enableQICriedWolf", settings.enableQICriedWolf},
			{"enableQIProvingHonor", settings.enableQIProvingHonor},
			{"enableQISaarthal", settings.enableQISaarthal},
			{"enableQIBrelyna", settings.enableQIBrelyna},
			{"enableQIDwemerMuseum", settings.enableQIDwemerMuseum},
			{"enableQITrinityRestored", settings.enableQITrinityRestored},
			{"enableQIThalmorEmbassy", settings.enableQIThalmorEmbassy},
			{"enableQIRingmaker", settings.enableQIRingmaker},
			{"oppDeviceAntiCheat", settings.oppDeviceAntiCheat},
			{"generalDeviceAntiCheat", settings.generalDeviceAntiCheat},
			{"noMessageBoxes", settings.noMessageBoxes},
			{"bossChestUseModelPath", settings.bossChestUseModelPath},
			{"dragonHoard", settings.dragonHoard},
			{"bossExtraGold", settings.bossExtraGold},
			{"useThemes", settings.useThemes},
			{"disableForce3rdPerson", settings.disableForce3rdPerson},
			{"enableSlowStrip", settings.enableSlowStrip},
			{"resumeEvents", settings.resumeEvents},
			{"saveDependentSettings", settings.saveDependentSettings},
			{"setAllDefaultSettings", settings.setAllDefaultSettings},
			{"consAllowFollowers", settings.consAllowFollowers},
			{"consAllowCreatures", settings.consAllowCreatures},
			{"consUseRelationships", settings.consUseRelationships},
			{"consRelationBondage", settings.consRelationBondage},
			{"consFallthrough", settings.consFallthrough},
			{"consRandomHeavyBondage", settings.consRandomHeavyBondage},
			{"consBondageIgnoreMax", settings.consBondageIgnoreMax},
			{"sexEnabled", settings.sexEnabled},
			{"sexAggressiveAnims", settings.sexAggressiveAnims},
			{"sexFilterFuta", settings.sexFilterFuta},
			{"sexRandomEnabled", settings.sexRandomEnabled},
			{"sexAllowMale", settings.sexAllowMale},
			{"sexAllowFemale", settings.sexAllowFemale},
			{"sexAllowFuta", settings.sexAllowFuta},
			{"sexAllowCreature", settings.sexAllowCreature},
			{"sexAllowFarmAnimals", settings.sexAllowFarmAnimals},
			{"sexRequireAll", settings.sexRequireAll},
			{"sexRequireBindings", settings.sexRequireBindings},
			{"sexRequireCollar", settings.sexRequireCollar},
			{"sexRequireHeavy", settings.sexRequireHeavy},
			{"sexRequireNude", settings.sexRequireNude},
			{"sexAlwaysAllowFollowers", settings.sexAlwaysAllowFollowers},
			{"sexAlwaysAllowSpouse", settings.sexAlwaysAllowSpouse},
			{"sexAlwaysAllowSummons", settings.sexAlwaysAllowSummons},
			{"LMAllureColor", settings.LMAllureColor},
			{"LMHeatColor", settings.LMHeatColor},
			{"LMBrandingColor", settings.LMBrandingColor},
			{"LMBondageColor", settings.LMBondageColor},
			{"LMNudityColor", settings.LMNudityColor},
			{"LMHealslutColor", settings.LMHealslutColor},
			{"setDebugKey", settings.setDebugKey},
			{"excludedFollowers", settings.excludedFollowers},
			{"LMNudityAditionalForms", settings.LMNudityAditionalForms},
			//CODEGEN_END_TOJSON
		};
		log::trace("Wrote settings to file {}", SETTINGS_FILE);
		o << std::setw(4) << j << std::endl;
	}

	void P_UpdateSKSE(RE::StaticFunctionTag*);

	bool LoadSettingsFile() {
		if (settings.saveDependentSettings) {
			return false;
		}


		std::ifstream i(SETTINGS_FILE);
		nlohmann::json j = nlohmann::json::parse("{}");
		if (!std::filesystem::exists(SETTINGS_FILE)) {
			log::info("Settings store file does not exist.");
			return false;
		}

		try {
			i >> j;
		}
		catch (...) {
			log::error("Settings store file has garbled data.");
			return false;
		}

		//CODEGEN_START_FROMJSON
		settings.minGoldRequired = static_cast<int>(j.value("minGoldRequired", 20));
		settings.eventScalingMod = static_cast<int>(j.value("eventScalingMod", 15));
		settings.minRestraints = static_cast<int>(j.value("minRestraints", 1));
		settings.maxRestraints = static_cast<int>(j.value("maxRestraints", 3));
		settings.bossAditionalRestraints = static_cast<int>(j.value("bossAditionalRestraints", 2));
		settings.restraintCap = static_cast<int>(j.value("restraintCap", 7));
		settings.minArousal = static_cast<int>(j.value("minArousal", 10));
		settings.beltWeight = static_cast<int>(j.value("beltWeight", 40));
		settings.chastityPiercingWeight = static_cast<int>(j.value("chastityPiercingWeight", 20));
		settings.braWeight = static_cast<int>(j.value("braWeight", 30));
		settings.plugsWeight = static_cast<int>(j.value("plugsWeight", 50));
		settings.lockingPlugsWeight = static_cast<int>(j.value("lockingPlugsWeight", 30));
		settings.inflatablePlugsWeight = static_cast<int>(j.value("inflatablePlugsWeight", 15));
		settings.nipplePiercingsWeight = static_cast<int>(j.value("nipplePiercingsWeight", 50));
		settings.vaginalPiercingsWeight = static_cast<int>(j.value("vaginalPiercingsWeight", 50));
		settings.corsetWeight = static_cast<int>(j.value("corsetWeight", 40));
		settings.beltedCorsetsWeight = static_cast<int>(j.value("beltedCorsetsWeight", 30));
		settings.slaveHarnessWeight = static_cast<int>(j.value("slaveHarnessWeight", 50));
		settings.chastityHarnessWeight = static_cast<int>(j.value("chastityHarnessWeight", 40));
		settings.armbinderWeight = static_cast<int>(j.value("armbinderWeight", 30));
		settings.elbowbinderWeight = static_cast<int>(j.value("elbowbinderWeight", 20));
		settings.yokeWeight = static_cast<int>(j.value("yokeWeight", 10));
		settings.shacklesWeight = static_cast<int>(j.value("shacklesWeight", 20));
		settings.straitjacketWeight = static_cast<int>(j.value("straitjacketWeight", 30));
		settings.straitjacketLegbinderWeight = static_cast<int>(j.value("straitjacketLegbinderWeight", 15));
		settings.petSuitWeight = static_cast<int>(j.value("petSuitWeight", 10));
		settings.collarWeight = static_cast<int>(j.value("collarWeight", 60));
		settings.armCuffsWeight = static_cast<int>(j.value("armCuffsWeight", 60));
		settings.legCuffsWeight = static_cast<int>(j.value("legCuffsWeight", 60));
		settings.gagWeight = static_cast<int>(j.value("gagWeight", 35));
		settings.ringGagWeight = static_cast<int>(j.value("ringGagWeight", 45));
		settings.largeGagWeight = static_cast<int>(j.value("largeGagWeight", 30));
		settings.largeRingGagWeight = static_cast<int>(j.value("largeRingGagWeight", 30));
		settings.blindfoldWeight = static_cast<int>(j.value("blindfoldWeight", 20));
		settings.hoodBothWeight = static_cast<int>(j.value("hoodBothWeight", 20));
		settings.hoodGagWeight = static_cast<int>(j.value("hoodGagWeight", 20));
		settings.hoodBlindWeight = static_cast<int>(j.value("hoodBlindWeight", 20));
		settings.hoodNoneWeight = static_cast<int>(j.value("hoodNoneWeight", 20));
		settings.catsuitWeight = static_cast<int>(j.value("catsuitWeight", 30));
		settings.hobbleSkirtWeight = static_cast<int>(j.value("hobbleSkirtWeight", 20));
		settings.hobbleSkirtDifficulty = static_cast<int>(j.value("hobbleSkirtDifficulty", 50));
		settings.bootsWeight = static_cast<int>(j.value("bootsWeight", 30));
		settings.glovesWeight = static_cast<int>(j.value("glovesWeight", 30));
		settings.mittensWeight = static_cast<int>(j.value("mittensWeight", 0));
		settings.eventStandardWeight = static_cast<int>(j.value("eventStandardWeight", 100));
		settings.eventStandardBossReduction = static_cast<int>(j.value("eventStandardBossReduction", 20));
		settings.eventOppressiveWeight = static_cast<int>(j.value("eventOppressiveWeight", 15));
		settings.eventContraptionWeight = static_cast<int>(j.value("eventContraptionWeight", 25));
		settings.eventContDeviceOverride = static_cast<int>(j.value("eventContDeviceOverride", 0));
		settings.eventWickedWeight = static_cast<int>(j.value("eventWickedWeight", 15));
		settings.eventTattooWeight = static_cast<int>(j.value("eventTattooWeight", 15));
		settings.eventTattooMin = static_cast<int>(j.value("eventTattooMin", 1));
		settings.eventTattooMax = static_cast<int>(j.value("eventTattooMax", 3));
		settings.eventTattooCap = static_cast<int>(j.value("eventTattooCap", 8));
		settings.followerDeviceModifier = static_cast<int>(j.value("followerDeviceModifier", 0));
		settings.eventLewdMarkWeight = static_cast<int>(j.value("eventLewdMarkWeight", 10));
		settings.eventSimpleSlaveryWeight = static_cast<int>(j.value("eventSimpleSlaveryWeight", 0));
		settings.eventSSMinRestraints = static_cast<int>(j.value("eventSSMinRestraints", 6));
		settings.eventAbadonWeight = static_cast<int>(j.value("eventAbadonWeight", 5));
		settings.eventAbadonWarriorWeight = static_cast<int>(j.value("eventAbadonWarriorWeight", 10));
		settings.eventAbadonWarriorCount = static_cast<int>(j.value("eventAbadonWarriorCount", 5));
		settings.eventAbadonScoutWeight = static_cast<int>(j.value("eventAbadonScoutWeight", 10));
		settings.eventAbadonScoutCount = static_cast<int>(j.value("eventAbadonScoutCount", 5));
		settings.eventAbadonWitchWeight = static_cast<int>(j.value("eventAbadonWitchWeight", 10));
		settings.eventAbadonWitchCount = static_cast<int>(j.value("eventAbadonWitchCount", 5));
		settings.LMAllureWeight = static_cast<int>(j.value("LMAllureWeight", 10));
		settings.LMAllureMod = static_cast<int>(j.value("LMAllureMod", 5));
		settings.LMAllureSex = static_cast<int>(j.value("LMAllureSex", 25));
		settings.LMHeatWeight = static_cast<int>(j.value("LMHeatWeight", 10));
		settings.LMHeatMod = static_cast<int>(j.value("LMHeatMod", 30));
		settings.LMHeatContainerCount = static_cast<int>(j.value("LMHeatContainerCount", 50));
		settings.LMBrandingWeight = static_cast<int>(j.value("LMBrandingWeight", 10));
		settings.LMBrandingTotal = static_cast<int>(j.value("LMBrandingTotal", 12));
		settings.LMBondageWeight = static_cast<int>(j.value("LMBondageWeight", 5));
		settings.LMBondageDeviceCount = static_cast<int>(j.value("LMBondageDeviceCount", 8));
		settings.LMNudityWeight = static_cast<int>(j.value("LMNudityWeight", 15));
		settings.LMNudityTalkTimes = static_cast<int>(j.value("LMNudityTalkTimes", 35));
		settings.LMHealslutWeight = static_cast<int>(j.value("LMHealslutWeight", 5));
		settings.LMHealslutHealing = static_cast<int>(j.value("LMHealslutHealing", 2000));
		settings.oppSummonerCollarWeight = static_cast<int>(j.value("oppSummonerCollarWeight", 20));
		settings.oppSummonerSexCount = static_cast<int>(j.value("oppSummonerSexCount", 15));
		settings.oppSMinSummonArousal = static_cast<int>(j.value("oppSMinSummonArousal", 90));
		settings.oppDwarvenCuirassWeight = static_cast<int>(j.value("oppDwarvenCuirassWeight", 15));
		settings.oppDwarvenValueNeeded = static_cast<int>(j.value("oppDwarvenValueNeeded", 200));
		settings.oppDwarvenArousal = static_cast<int>(j.value("oppDwarvenArousal", 25));
		settings.oppNocturnalWeight = static_cast<int>(j.value("oppNocturnalWeight", 10));
		settings.oppNocturnalSexCount = static_cast<int>(j.value("oppNocturnalSexCount", 3));
		settings.oppNocturnalPeople = static_cast<int>(j.value("oppNocturnalPeople", 7));
		settings.oppNocturnalArousal = static_cast<int>(j.value("oppNocturnalArousal", 35));
		settings.oppLivingLatexWeight = static_cast<int>(j.value("oppLivingLatexWeight", 20));
		settings.oppLivingLatexStartTime = static_cast<int>(j.value("oppLivingLatexStartTime", 15));
		settings.oppMadnessPlugWeight = static_cast<int>(j.value("oppMadnessPlugWeight", 25));
		settings.oppMadnessPlugIterations = static_cast<int>(j.value("oppMadnessPlugIterations", 5));
		settings.oppMadnessplugOrgasms = static_cast<int>(j.value("oppMadnessplugOrgasms", 6));
		settings.minKeysLooted = static_cast<int>(j.value("minKeysLooted", 1));
		settings.maxKeysLooted = static_cast<int>(j.value("maxKeysLooted", 1));
		settings.maxHeldKeys = static_cast<int>(j.value("maxHeldKeys", 3));
		settings.restraintsKeyWeight = static_cast<int>(j.value("restraintsKeyWeight", 80));
		settings.chastityKeyWeight = static_cast<int>(j.value("chastityKeyWeight", 50));
		settings.piercingToolWeight = static_cast<int>(j.value("piercingToolWeight", 20));
		settings.consSexWeight = static_cast<int>(j.value("consSexWeight", 15));
		settings.consFineWeight = static_cast<int>(j.value("consFineWeight", 10));
		settings.consFineAmount = static_cast<int>(j.value("consFineAmount", 100));
		settings.consRandomBondageWeight = static_cast<int>(j.value("consRandomBondageWeight", 10));
		settings.consMercyWeight = static_cast<int>(j.value("consMercyWeight", 5));
		settings.sexCooldown = static_cast<int>(j.value("sexCooldown", 30));
		settings.sexChance = static_cast<int>(j.value("sexChance", 50));
		settings.sexChanceCreature = static_cast<int>(j.value("sexChanceCreature", 30));
		settings.sexBaseArousal = static_cast<int>(j.value("sexBaseArousal", 90));
		settings.sexArousalNightModifier = static_cast<int>(j.value("sexArousalNightModifier", 5));
		settings.sexArousalNudeModifier = static_cast<int>(j.value("sexArousalNudeModifier", 15));
		settings.sexArousalCollarModifier = static_cast<int>(j.value("sexArousalCollarModifier", 5));
		settings.sexArousalHeavyModifier = static_cast<int>(j.value("sexArousalHeavyModifier", 10));
		settings.sexArousalBlindModifier = static_cast<int>(j.value("sexArousalBlindModifier", 5));
		settings.sexArousalBootsModifier = static_cast<int>(j.value("sexArousalBootsModifier", 0));
		settings.sexArousalHobbleModifier = static_cast<int>(j.value("sexArousalHobbleModifier", 0));
		settings.sexArousalVisibleModifier = static_cast<int>(j.value("sexArousalVisibleModifier", 5));
		settings.sexArousalCreatureModifier = static_cast<int>(j.value("sexArousalCreatureModifier", 0));
		settings.sexArousalFollowerModifier = static_cast<int>(j.value("sexArousalFollowerModifier", 10));
		settings.sexArousalSpouseModifier = static_cast<int>(j.value("sexArousalSpouseModifier", 20));
		settings.sexArousalSummonModifier = static_cast<int>(j.value("sexArousalSummonModifier", 0));
		settings.sexSearchRadius = static_cast<int>(j.value("sexSearchRadius", 2000));
		settings.sexSearchInterval = static_cast<int>(j.value("sexSearchInterval", 5));
		settings.sexRequiredPlayerArousal = static_cast<int>(j.value("sexRequiredPlayerArousal", 0));
		settings.sexRequiredPlayerTattoos = static_cast<int>(j.value("sexRequiredPlayerTattoos", 0));
		settings.sexChanceFollower = static_cast<int>(j.value("sexChanceFollower", -1));
		settings.sexChanceSpouse = static_cast<int>(j.value("sexChanceSpouse", -1));
		settings.sexChanceSummon = static_cast<int>(j.value("sexChanceSummon", -1));
		settings.LMAllureColor = static_cast<int>(j.value("LMAllureColor", 0xcf11c5));
		settings.LMHeatColor = static_cast<int>(j.value("LMHeatColor", 0xe3143a));
		settings.LMBrandingColor = static_cast<int>(j.value("LMBrandingColor", 0x220022));
		settings.LMBondageColor = static_cast<int>(j.value("LMBondageColor", 0x7908cf));
		settings.LMNudityColor = static_cast<int>(j.value("LMNudityColor", 0xd676cb));
		settings.LMHealslutColor = static_cast<int>(j.value("LMHealslutColor", 0xffbb45));
		settings.setDebugKey = static_cast<int>(j.value("setDebugKey", -1));
		settings.baseChance = static_cast<float>(j.value("baseChance", 6.5));
		settings.containerModifier = static_cast<float>(j.value("containerModifier", 1.0));
		settings.bossContainerModifier = static_cast<float>(j.value("bossContainerModifier", 2.0));
		settings.deadBodyModifier = static_cast<float>(j.value("deadBodyModifier", 1.3));
		settings.pickpocketModifier = static_cast<float>(j.value("pickpocketModifier", 1.3));
		settings.doorModifier = static_cast<float>(j.value("doorModifier", 1.0));
		settings.lockedModifier = static_cast<float>(j.value("lockedModifier", 2.0));
		settings.lockDifficultyModifier = static_cast<float>(j.value("lockDifficultyModifier", 1.3));
		settings.arousalModifier = static_cast<float>(j.value("arousalModifier", 1.4));
		settings.eventContraptionTime = static_cast<float>(j.value("eventContraptionTime", 4.0));
		settings.LMBrandingChance = static_cast<float>(j.value("LMBrandingChance", 1.5));
		settings.LMBondageChance = static_cast<float>(j.value("LMBondageChance", 5.0));
		settings.oppSummonChance = static_cast<float>(j.value("oppSummonChance", 1.5));
		settings.oppNocturnalHandChance = static_cast<float>(j.value("oppNocturnalHandChance", 3.5));
		settings.oppNocturnalRecastChance = static_cast<float>(j.value("oppNocturnalRecastChance", 33.3));
		settings.oppLivingLatexGem = static_cast<float>(j.value("oppLivingLatexGem", 6.0));
		settings.oppLivingLatexMore = static_cast<float>(j.value("oppLivingLatexMore", 0.0));
		settings.playerHomeModifier = static_cast<float>(j.value("playerHomeModifier", 0.0));
		settings.cityModifier = static_cast<float>(j.value("cityModifier", 0.0));
		settings.townModifier = static_cast<float>(j.value("townModifier", 0.0));
		settings.banditModifier = static_cast<float>(j.value("banditModifier", 1.1));
		settings.draugrModifier = static_cast<float>(j.value("draugrModifier", 1.2));
		settings.lockedLocationBypass = static_cast<float>(j.value("lockedLocationBypass", 0.6));
		settings.theftLocationBypass = static_cast<float>(j.value("theftLocationBypass", 1.1));
		settings.dwarvenModifier = static_cast<float>(j.value("dwarvenModifier", 1.2));
		settings.falmerModifier = static_cast<float>(j.value("falmerModifier", 1.3));
		settings.forswornModifier = static_cast<float>(j.value("forswornModifier", 1.1));
		settings.vampireModifier = static_cast<float>(j.value("vampireModifier", 1.5));
		settings.warlockModifier = static_cast<float>(j.value("warlockModifier", 1.5));
		settings.dragonLairModifier = static_cast<float>(j.value("dragonLairModifier", 2.0));
		settings.apocryphaModifier = static_cast<float>(j.value("apocryphaModifier", 2.0));
		settings.wildernessModifier = static_cast<float>(j.value("wildernessModifier", 0.9));
		settings.keyLossChance = static_cast<float>(j.value("keyLossChance", 80.0));
		settings.keyChance = static_cast<float>(j.value("keyChance", 7.0));
		settings.keyBonus = static_cast<float>(j.value("keyBonus", 1.0));
		settings.keyPickpocketBonus = static_cast<float>(j.value("keyPickpocketBonus", 2.0));
		settings.magicKeyChance = static_cast<float>(j.value("magicKeyChance", 20.0));
		settings.keyLuckyBonus = static_cast<float>(j.value("keyLuckyBonus", 1.75));
		settings.rDeviceBaseChance = static_cast<float>(j.value("rDeviceBaseChance", 1.5));
		settings.rDeviceLuckyBonus = static_cast<float>(j.value("rDeviceLuckyBonus", 2.5));
		settings.tatSolventChance = static_cast<float>(j.value("tatSolventChance", 0.5));
		settings.arousalPotionChance = static_cast<float>(j.value("arousalPotionChance", 5.0));
		settings.arousalPotionLibido = static_cast<float>(j.value("arousalPotionLibido", 10.0));
		settings.consTriggerNude = static_cast<float>(j.value("consTriggerNude", 15.0));
		settings.consTriggerRestrained = static_cast<float>(j.value("consTriggerRestrained", 50.0));
		settings.consTriggerSex = static_cast<float>(j.value("consTriggerSex", 10.0));
		settings.sexArousalTattooModifier = static_cast<float>(j.value("sexArousalTattooModifier", 1.0));
		settings.onlyLockedDoors = static_cast<bool>(j.value("onlyLockedDoors", true));
		settings.eventScaling = static_cast<bool>(j.value("eventScaling", true));
		settings.bossOnlyHeavy = static_cast<bool>(j.value("bossOnlyHeavy", true));
		settings.stripPlayerOnEvent = static_cast<bool>(j.value("stripPlayerOnEvent", true));
		settings.stripOnlyKeywords = static_cast<bool>(j.value("stripOnlyKeywords", true));
		settings.beltPlugs = static_cast<bool>(j.value("beltPlugs", true));
		settings.useGenderedChastity = static_cast<bool>(j.value("useGenderedChastity", true));
		settings.plugsDontCount = static_cast<bool>(j.value("plugsDontCount", true));
		settings.allowLegShackles = static_cast<bool>(j.value("allowLegShackles", false));
		settings.eventContDevices = static_cast<bool>(j.value("eventContDevices", true));
		settings.eventContAllDevices = static_cast<bool>(j.value("eventContAllDevices", false));
		settings.allowFollowerEvents = static_cast<bool>(j.value("allowFollowerEvents", false));
		settings.onlyFemaleFollowers = static_cast<bool>(j.value("onlyFemaleFollowers", true));
		settings.followerHeavyRestraints = static_cast<bool>(j.value("followerHeavyRestraints", false));
		settings.onlyUseUnforgivingDevices = static_cast<bool>(j.value("onlyUseUnforgivingDevices", true));
		settings.udUseAbadon = static_cast<bool>(j.value("udUseAbadon", false));
		settings.udUseAbadonSets = static_cast<bool>(j.value("udUseAbadonSets", false));
		settings.udUseMisc = static_cast<bool>(j.value("udUseMisc", true));
		settings.ANDSexTopless = static_cast<bool>(j.value("ANDSexTopless", true));
		settings.ANDSexBottomless = static_cast<bool>(j.value("ANDSexBottomless", true));
		settings.ANDSexShowingChest = static_cast<bool>(j.value("ANDSexShowingChest", true));
		settings.ANDSexShowingGenitals = static_cast<bool>(j.value("ANDSexShowingGenitals", true));
		settings.ANDSexShowingAss = static_cast<bool>(j.value("ANDSexShowingAss", false));
		settings.ANDSexShowingBra = static_cast<bool>(j.value("ANDSexShowingBra", false));
		settings.ANDSexShowingUnderwear = static_cast<bool>(j.value("ANDSexShowingUnderwear", false));
		settings.ANDConsTopless = static_cast<bool>(j.value("ANDConsTopless", true));
		settings.ANDConsBottomless = static_cast<bool>(j.value("ANDConsBottomless", true));
		settings.ANDConsShowingChest = static_cast<bool>(j.value("ANDConsShowingChest", true));
		settings.ANDConsShowingGenitals = static_cast<bool>(j.value("ANDConsShowingGenitals", true));
		settings.ANDConsShowingAss = static_cast<bool>(j.value("ANDConsShowingAss", false));
		settings.ANDConsShowingBra = static_cast<bool>(j.value("ANDConsShowingBra", false));
		settings.ANDConsShowingUnderwear = static_cast<bool>(j.value("ANDConsShowingUnderwear", false));
		settings.LMBrandingPunish = static_cast<bool>(j.value("LMBrandingPunish", true));
		settings.LMNudityChestOnly = static_cast<bool>(j.value("LMNudityChestOnly", false));
		settings.oppOneAtATime = static_cast<bool>(j.value("oppOneAtATime", true));
		settings.oppSCollarDrainsMagicka = static_cast<bool>(j.value("oppSCollarDrainsMagicka", true));
		settings.oppSCollarAutoRemove = static_cast<bool>(j.value("oppSCollarAutoRemove", true));
		settings.oppDwarvenHeavyRestraint = static_cast<bool>(j.value("oppDwarvenHeavyRestraint", false));
		settings.oppDwarvenRequireLoc = static_cast<bool>(j.value("oppDwarvenRequireLoc", true));
		settings.oppLivingLatexHeavy = static_cast<bool>(j.value("oppLivingLatexHeavy", false));
		settings.oppLivingLatexRequireRem = static_cast<bool>(j.value("oppLivingLatexRequireRem", true));
		settings.oppLivingLatexOpen = static_cast<bool>(j.value("oppLivingLatexOpen", false));
		settings.oppMadnessAllOrgasms = static_cast<bool>(j.value("oppMadnessAllOrgasms", false));
		settings.oppMadnessBeltFilter = static_cast<bool>(j.value("oppMadnessBeltFilter", true));
		settings.oppMadnessChaos = static_cast<bool>(j.value("oppMadnessChaos", false));
		settings.useLocationModifiers = static_cast<bool>(j.value("useLocationModifiers", true));
		settings.keyForgiveness = static_cast<bool>(j.value("keyForgiveness", true));
		settings.magicKeyOppressive = static_cast<bool>(j.value("magicKeyOppressive", false));
		settings.preferRelevantKeys = static_cast<bool>(j.value("preferRelevantKeys", true));
		settings.vanishingKeys = static_cast<bool>(j.value("vanishingKeys", true));
		settings.enableQuestInteractions = static_cast<bool>(j.value("enableQuestInteractions", true));
		settings.enableQIMalkoran = static_cast<bool>(j.value("enableQIMalkoran", true));
		settings.enableQISanguine = static_cast<bool>(j.value("enableQISanguine", true));
		settings.enableQIBlackStar = static_cast<bool>(j.value("enableQIBlackStar", true));
		settings.enableQIMindOfMadness = static_cast<bool>(j.value("enableQIMindOfMadness", true));
		settings.enableQILaidToRest = static_cast<bool>(j.value("enableQILaidToRest", true));
		settings.enableQICriedWolf = static_cast<bool>(j.value("enableQICriedWolf", true));
		settings.enableQIProvingHonor = static_cast<bool>(j.value("enableQIProvingHonor", true));
		settings.enableQISaarthal = static_cast<bool>(j.value("enableQISaarthal", true));
		settings.enableQIBrelyna = static_cast<bool>(j.value("enableQIBrelyna", true));
		settings.enableQIDwemerMuseum = static_cast<bool>(j.value("enableQIDwemerMuseum", true));
		settings.enableQITrinityRestored = static_cast<bool>(j.value("enableQITrinityRestored", true));
		settings.enableQIThalmorEmbassy = static_cast<bool>(j.value("enableQIThalmorEmbassy", true));
		settings.enableQIRingmaker = static_cast<bool>(j.value("enableQIRingmaker", true));
		settings.oppDeviceAntiCheat = static_cast<bool>(j.value("oppDeviceAntiCheat", true));
		settings.generalDeviceAntiCheat = static_cast<bool>(j.value("generalDeviceAntiCheat", false));
		settings.noMessageBoxes = static_cast<bool>(j.value("noMessageBoxes", false));
		settings.bossChestUseModelPath = static_cast<bool>(j.value("bossChestUseModelPath", true));
		settings.dragonHoard = static_cast<bool>(j.value("dragonHoard", true));
		settings.bossExtraGold = static_cast<bool>(j.value("bossExtraGold", true));
		settings.useThemes = static_cast<bool>(j.value("useThemes", false));
		settings.disableForce3rdPerson = static_cast<bool>(j.value("disableForce3rdPerson", true));
		settings.enableSlowStrip = static_cast<bool>(j.value("enableSlowStrip", false));
		settings.resumeEvents = static_cast<bool>(j.value("resumeEvents", false));
		settings.saveDependentSettings = static_cast<bool>(j.value("saveDependentSettings", false));
		settings.setAllDefaultSettings = static_cast<bool>(j.value("setAllDefaultSettings", false));
		settings.consAllowFollowers = static_cast<bool>(j.value("consAllowFollowers", false));
		settings.consAllowCreatures = static_cast<bool>(j.value("consAllowCreatures", false));
		settings.consUseRelationships = static_cast<bool>(j.value("consUseRelationships", true));
		settings.consRelationBondage = static_cast<bool>(j.value("consRelationBondage", false));
		settings.consFallthrough = static_cast<bool>(j.value("consFallthrough", false));
		settings.consRandomHeavyBondage = static_cast<bool>(j.value("consRandomHeavyBondage", false));
		settings.consBondageIgnoreMax = static_cast<bool>(j.value("consBondageIgnoreMax", false));
		settings.sexEnabled = static_cast<bool>(j.value("sexEnabled", false));
		settings.sexAggressiveAnims = static_cast<bool>(j.value("sexAggressiveAnims", false));
		settings.sexFilterFuta = static_cast<bool>(j.value("sexFilterFuta", true));
		settings.sexRandomEnabled = static_cast<bool>(j.value("sexRandomEnabled", false));
		settings.sexAllowMale = static_cast<bool>(j.value("sexAllowMale", true));
		settings.sexAllowFemale = static_cast<bool>(j.value("sexAllowFemale", true));
		settings.sexAllowFuta = static_cast<bool>(j.value("sexAllowFuta", true));
		settings.sexAllowCreature = static_cast<bool>(j.value("sexAllowCreature", false));
		settings.sexAllowFarmAnimals = static_cast<bool>(j.value("sexAllowFarmAnimals", false));
		settings.sexRequireAll = static_cast<bool>(j.value("sexRequireAll", false));
		settings.sexRequireBindings = static_cast<bool>(j.value("sexRequireBindings", true));
		settings.sexRequireCollar = static_cast<bool>(j.value("sexRequireCollar", false));
		settings.sexRequireHeavy = static_cast<bool>(j.value("sexRequireHeavy", false));
		settings.sexRequireNude = static_cast<bool>(j.value("sexRequireNude", true));
		settings.sexAlwaysAllowFollowers = static_cast<bool>(j.value("sexAlwaysAllowFollowers", true));
		settings.sexAlwaysAllowSpouse = static_cast<bool>(j.value("sexAlwaysAllowSpouse", true));
		settings.sexAlwaysAllowSummons = static_cast<bool>(j.value("sexAlwaysAllowSummons", false));
		settings.excludedFollowers = j.value("excludedFollowers", "");
		settings.LMNudityAditionalForms = j.value("LMNudityAditionalForms", "");
		//CODEGEN_END_FROMJSON

		log::trace("Read settings from file {}", SETTINGS_FILE);

		return true;
	}

	void PushSettingsToMCM() {
		//CODEGEN_START_PUSHMCM
		SetMCMInt("minGoldRequired",settings.minGoldRequired);
		SetMCMInt("eventScalingMod",settings.eventScalingMod);
		SetMCMInt("minRestraints",settings.minRestraints);
		SetMCMInt("maxRestraints",settings.maxRestraints);
		SetMCMInt("bossAditionalRestraints",settings.bossAditionalRestraints);
		SetMCMInt("restraintCap",settings.restraintCap);
		SetMCMInt("minArousal",settings.minArousal);
		SetMCMInt("beltWeight",settings.beltWeight);
		SetMCMInt("chastityPiercingWeight",settings.chastityPiercingWeight);
		SetMCMInt("braWeight",settings.braWeight);
		SetMCMInt("plugsWeight",settings.plugsWeight);
		SetMCMInt("lockingPlugsWeight",settings.lockingPlugsWeight);
		SetMCMInt("inflatablePlugsWeight",settings.inflatablePlugsWeight);
		SetMCMInt("nipplePiercingsWeight",settings.nipplePiercingsWeight);
		SetMCMInt("vaginalPiercingsWeight",settings.vaginalPiercingsWeight);
		SetMCMInt("corsetWeight",settings.corsetWeight);
		SetMCMInt("beltedCorsetsWeight",settings.beltedCorsetsWeight);
		SetMCMInt("slaveHarnessWeight",settings.slaveHarnessWeight);
		SetMCMInt("chastityHarnessWeight",settings.chastityHarnessWeight);
		SetMCMInt("armbinderWeight",settings.armbinderWeight);
		SetMCMInt("elbowbinderWeight",settings.elbowbinderWeight);
		SetMCMInt("yokeWeight",settings.yokeWeight);
		SetMCMInt("shacklesWeight",settings.shacklesWeight);
		SetMCMInt("straitjacketWeight",settings.straitjacketWeight);
		SetMCMInt("straitjacketLegbinderWeight",settings.straitjacketLegbinderWeight);
		SetMCMInt("petSuitWeight",settings.petSuitWeight);
		SetMCMInt("collarWeight",settings.collarWeight);
		SetMCMInt("armCuffsWeight",settings.armCuffsWeight);
		SetMCMInt("legCuffsWeight",settings.legCuffsWeight);
		SetMCMInt("gagWeight",settings.gagWeight);
		SetMCMInt("ringGagWeight",settings.ringGagWeight);
		SetMCMInt("largeGagWeight",settings.largeGagWeight);
		SetMCMInt("largeRingGagWeight",settings.largeRingGagWeight);
		SetMCMInt("blindfoldWeight",settings.blindfoldWeight);
		SetMCMInt("hoodBothWeight",settings.hoodBothWeight);
		SetMCMInt("hoodGagWeight",settings.hoodGagWeight);
		SetMCMInt("hoodBlindWeight",settings.hoodBlindWeight);
		SetMCMInt("hoodNoneWeight",settings.hoodNoneWeight);
		SetMCMInt("catsuitWeight",settings.catsuitWeight);
		SetMCMInt("hobbleSkirtWeight",settings.hobbleSkirtWeight);
		SetMCMInt("hobbleSkirtDifficulty",settings.hobbleSkirtDifficulty);
		SetMCMInt("bootsWeight",settings.bootsWeight);
		SetMCMInt("glovesWeight",settings.glovesWeight);
		SetMCMInt("mittensWeight",settings.mittensWeight);
		SetMCMInt("eventStandardWeight",settings.eventStandardWeight);
		SetMCMInt("eventStandardBossReduction",settings.eventStandardBossReduction);
		SetMCMInt("eventOppressiveWeight",settings.eventOppressiveWeight);
		SetMCMInt("eventContraptionWeight",settings.eventContraptionWeight);
		SetMCMInt("eventContDeviceOverride",settings.eventContDeviceOverride);
		SetMCMInt("eventWickedWeight",settings.eventWickedWeight);
		SetMCMInt("eventTattooWeight",settings.eventTattooWeight);
		SetMCMInt("eventTattooMin",settings.eventTattooMin);
		SetMCMInt("eventTattooMax",settings.eventTattooMax);
		SetMCMInt("eventTattooCap",settings.eventTattooCap);
		SetMCMInt("followerDeviceModifier",settings.followerDeviceModifier);
		SetMCMInt("eventLewdMarkWeight",settings.eventLewdMarkWeight);
		SetMCMInt("eventSimpleSlaveryWeight",settings.eventSimpleSlaveryWeight);
		SetMCMInt("eventSSMinRestraints",settings.eventSSMinRestraints);
		SetMCMInt("eventAbadonWeight",settings.eventAbadonWeight);
		SetMCMInt("eventAbadonWarriorWeight",settings.eventAbadonWarriorWeight);
		SetMCMInt("eventAbadonWarriorCount",settings.eventAbadonWarriorCount);
		SetMCMInt("eventAbadonScoutWeight",settings.eventAbadonScoutWeight);
		SetMCMInt("eventAbadonScoutCount",settings.eventAbadonScoutCount);
		SetMCMInt("eventAbadonWitchWeight",settings.eventAbadonWitchWeight);
		SetMCMInt("eventAbadonWitchCount",settings.eventAbadonWitchCount);
		SetMCMInt("LMAllureWeight",settings.LMAllureWeight);
		SetMCMInt("LMAllureMod",settings.LMAllureMod);
		SetMCMInt("LMAllureSex",settings.LMAllureSex);
		SetMCMInt("LMHeatWeight",settings.LMHeatWeight);
		SetMCMInt("LMHeatMod",settings.LMHeatMod);
		SetMCMInt("LMHeatContainerCount",settings.LMHeatContainerCount);
		SetMCMInt("LMBrandingWeight",settings.LMBrandingWeight);
		SetMCMInt("LMBrandingTotal",settings.LMBrandingTotal);
		SetMCMInt("LMBondageWeight",settings.LMBondageWeight);
		SetMCMInt("LMBondageDeviceCount",settings.LMBondageDeviceCount);
		SetMCMInt("LMNudityWeight",settings.LMNudityWeight);
		SetMCMInt("LMNudityTalkTimes",settings.LMNudityTalkTimes);
		SetMCMInt("LMHealslutWeight",settings.LMHealslutWeight);
		SetMCMInt("LMHealslutHealing",settings.LMHealslutHealing);
		SetMCMInt("oppSummonerCollarWeight",settings.oppSummonerCollarWeight);
		SetMCMInt("oppSummonerSexCount",settings.oppSummonerSexCount);
		SetMCMInt("oppSMinSummonArousal",settings.oppSMinSummonArousal);
		SetMCMInt("oppDwarvenCuirassWeight",settings.oppDwarvenCuirassWeight);
		SetMCMInt("oppDwarvenValueNeeded",settings.oppDwarvenValueNeeded);
		SetMCMInt("oppDwarvenArousal",settings.oppDwarvenArousal);
		SetMCMInt("oppNocturnalWeight",settings.oppNocturnalWeight);
		SetMCMInt("oppNocturnalSexCount",settings.oppNocturnalSexCount);
		SetMCMInt("oppNocturnalPeople",settings.oppNocturnalPeople);
		SetMCMInt("oppNocturnalArousal",settings.oppNocturnalArousal);
		SetMCMInt("oppLivingLatexWeight",settings.oppLivingLatexWeight);
		SetMCMInt("oppLivingLatexStartTime",settings.oppLivingLatexStartTime);
		SetMCMInt("oppMadnessPlugWeight",settings.oppMadnessPlugWeight);
		SetMCMInt("oppMadnessPlugIterations",settings.oppMadnessPlugIterations);
		SetMCMInt("oppMadnessplugOrgasms",settings.oppMadnessplugOrgasms);
		SetMCMInt("minKeysLooted",settings.minKeysLooted);
		SetMCMInt("maxKeysLooted",settings.maxKeysLooted);
		SetMCMInt("maxHeldKeys",settings.maxHeldKeys);
		SetMCMInt("restraintsKeyWeight",settings.restraintsKeyWeight);
		SetMCMInt("chastityKeyWeight",settings.chastityKeyWeight);
		SetMCMInt("piercingToolWeight",settings.piercingToolWeight);
		SetMCMInt("consSexWeight",settings.consSexWeight);
		SetMCMInt("consFineWeight",settings.consFineWeight);
		SetMCMInt("consFineAmount",settings.consFineAmount);
		SetMCMInt("consRandomBondageWeight",settings.consRandomBondageWeight);
		SetMCMInt("consMercyWeight",settings.consMercyWeight);
		SetMCMInt("sexCooldown",settings.sexCooldown);
		SetMCMInt("sexChance",settings.sexChance);
		SetMCMInt("sexChanceCreature",settings.sexChanceCreature);
		SetMCMInt("sexBaseArousal",settings.sexBaseArousal);
		SetMCMInt("sexArousalNightModifier",settings.sexArousalNightModifier);
		SetMCMInt("sexArousalNudeModifier",settings.sexArousalNudeModifier);
		SetMCMInt("sexArousalCollarModifier",settings.sexArousalCollarModifier);
		SetMCMInt("sexArousalHeavyModifier",settings.sexArousalHeavyModifier);
		SetMCMInt("sexArousalBlindModifier",settings.sexArousalBlindModifier);
		SetMCMInt("sexArousalBootsModifier",settings.sexArousalBootsModifier);
		SetMCMInt("sexArousalHobbleModifier",settings.sexArousalHobbleModifier);
		SetMCMInt("sexArousalVisibleModifier",settings.sexArousalVisibleModifier);
		SetMCMInt("sexArousalCreatureModifier",settings.sexArousalCreatureModifier);
		SetMCMInt("sexArousalFollowerModifier",settings.sexArousalFollowerModifier);
		SetMCMInt("sexArousalSpouseModifier",settings.sexArousalSpouseModifier);
		SetMCMInt("sexArousalSummonModifier",settings.sexArousalSummonModifier);
		SetMCMInt("sexSearchRadius",settings.sexSearchRadius);
		SetMCMInt("sexSearchInterval",settings.sexSearchInterval);
		SetMCMInt("sexRequiredPlayerArousal",settings.sexRequiredPlayerArousal);
		SetMCMInt("sexRequiredPlayerTattoos",settings.sexRequiredPlayerTattoos);
		SetMCMInt("sexChanceFollower",settings.sexChanceFollower);
		SetMCMInt("sexChanceSpouse",settings.sexChanceSpouse);
		SetMCMInt("sexChanceSummon",settings.sexChanceSummon);
		SetMCMInt("LMAllureColor",settings.LMAllureColor);
		SetMCMInt("LMHeatColor",settings.LMHeatColor);
		SetMCMInt("LMBrandingColor",settings.LMBrandingColor);
		SetMCMInt("LMBondageColor",settings.LMBondageColor);
		SetMCMInt("LMNudityColor",settings.LMNudityColor);
		SetMCMInt("LMHealslutColor",settings.LMHealslutColor);
		SetMCMInt("setDebugKey",settings.setDebugKey);
		SetMCMFloat("baseChance",settings.baseChance);
		SetMCMFloat("containerModifier",settings.containerModifier);
		SetMCMFloat("bossContainerModifier",settings.bossContainerModifier);
		SetMCMFloat("deadBodyModifier",settings.deadBodyModifier);
		SetMCMFloat("pickpocketModifier",settings.pickpocketModifier);
		SetMCMFloat("doorModifier",settings.doorModifier);
		SetMCMFloat("lockedModifier",settings.lockedModifier);
		SetMCMFloat("lockDifficultyModifier",settings.lockDifficultyModifier);
		SetMCMFloat("arousalModifier",settings.arousalModifier);
		SetMCMFloat("eventContraptionTime",settings.eventContraptionTime);
		SetMCMFloat("LMBrandingChance",settings.LMBrandingChance);
		SetMCMFloat("LMBondageChance",settings.LMBondageChance);
		SetMCMFloat("oppSummonChance",settings.oppSummonChance);
		SetMCMFloat("oppNocturnalHandChance",settings.oppNocturnalHandChance);
		SetMCMFloat("oppNocturnalRecastChance",settings.oppNocturnalRecastChance);
		SetMCMFloat("oppLivingLatexGem",settings.oppLivingLatexGem);
		SetMCMFloat("oppLivingLatexMore",settings.oppLivingLatexMore);
		SetMCMFloat("playerHomeModifier",settings.playerHomeModifier);
		SetMCMFloat("cityModifier",settings.cityModifier);
		SetMCMFloat("townModifier",settings.townModifier);
		SetMCMFloat("banditModifier",settings.banditModifier);
		SetMCMFloat("draugrModifier",settings.draugrModifier);
		SetMCMFloat("lockedLocationBypass",settings.lockedLocationBypass);
		SetMCMFloat("theftLocationBypass",settings.theftLocationBypass);
		SetMCMFloat("dwarvenModifier",settings.dwarvenModifier);
		SetMCMFloat("falmerModifier",settings.falmerModifier);
		SetMCMFloat("forswornModifier",settings.forswornModifier);
		SetMCMFloat("vampireModifier",settings.vampireModifier);
		SetMCMFloat("warlockModifier",settings.warlockModifier);
		SetMCMFloat("dragonLairModifier",settings.dragonLairModifier);
		SetMCMFloat("apocryphaModifier",settings.apocryphaModifier);
		SetMCMFloat("wildernessModifier",settings.wildernessModifier);
		SetMCMFloat("keyLossChance",settings.keyLossChance);
		SetMCMFloat("keyChance",settings.keyChance);
		SetMCMFloat("keyBonus",settings.keyBonus);
		SetMCMFloat("keyPickpocketBonus",settings.keyPickpocketBonus);
		SetMCMFloat("magicKeyChance",settings.magicKeyChance);
		SetMCMFloat("keyLuckyBonus",settings.keyLuckyBonus);
		SetMCMFloat("rDeviceBaseChance",settings.rDeviceBaseChance);
		SetMCMFloat("rDeviceLuckyBonus",settings.rDeviceLuckyBonus);
		SetMCMFloat("tatSolventChance",settings.tatSolventChance);
		SetMCMFloat("arousalPotionChance",settings.arousalPotionChance);
		SetMCMFloat("arousalPotionLibido",settings.arousalPotionLibido);
		SetMCMFloat("consTriggerNude",settings.consTriggerNude);
		SetMCMFloat("consTriggerRestrained",settings.consTriggerRestrained);
		SetMCMFloat("consTriggerSex",settings.consTriggerSex);
		SetMCMFloat("sexArousalTattooModifier",settings.sexArousalTattooModifier);
		SetMCMBool("onlyLockedDoors",settings.onlyLockedDoors);
		SetMCMBool("eventScaling",settings.eventScaling);
		SetMCMBool("bossOnlyHeavy",settings.bossOnlyHeavy);
		SetMCMBool("stripPlayerOnEvent",settings.stripPlayerOnEvent);
		SetMCMBool("stripOnlyKeywords",settings.stripOnlyKeywords);
		SetMCMBool("beltPlugs",settings.beltPlugs);
		SetMCMBool("useGenderedChastity",settings.useGenderedChastity);
		SetMCMBool("plugsDontCount",settings.plugsDontCount);
		SetMCMBool("allowLegShackles",settings.allowLegShackles);
		SetMCMBool("eventContDevices",settings.eventContDevices);
		SetMCMBool("eventContAllDevices",settings.eventContAllDevices);
		SetMCMBool("allowFollowerEvents",settings.allowFollowerEvents);
		SetMCMBool("onlyFemaleFollowers",settings.onlyFemaleFollowers);
		SetMCMBool("followerHeavyRestraints",settings.followerHeavyRestraints);
		SetMCMBool("onlyUseUnforgivingDevices",settings.onlyUseUnforgivingDevices);
		SetMCMBool("udUseAbadon",settings.udUseAbadon);
		SetMCMBool("udUseAbadonSets",settings.udUseAbadonSets);
		SetMCMBool("udUseMisc",settings.udUseMisc);
		SetMCMBool("ANDSexTopless",settings.ANDSexTopless);
		SetMCMBool("ANDSexBottomless",settings.ANDSexBottomless);
		SetMCMBool("ANDSexShowingChest",settings.ANDSexShowingChest);
		SetMCMBool("ANDSexShowingGenitals",settings.ANDSexShowingGenitals);
		SetMCMBool("ANDSexShowingAss",settings.ANDSexShowingAss);
		SetMCMBool("ANDSexShowingBra",settings.ANDSexShowingBra);
		SetMCMBool("ANDSexShowingUnderwear",settings.ANDSexShowingUnderwear);
		SetMCMBool("ANDConsTopless",settings.ANDConsTopless);
		SetMCMBool("ANDConsBottomless",settings.ANDConsBottomless);
		SetMCMBool("ANDConsShowingChest",settings.ANDConsShowingChest);
		SetMCMBool("ANDConsShowingGenitals",settings.ANDConsShowingGenitals);
		SetMCMBool("ANDConsShowingAss",settings.ANDConsShowingAss);
		SetMCMBool("ANDConsShowingBra",settings.ANDConsShowingBra);
		SetMCMBool("ANDConsShowingUnderwear",settings.ANDConsShowingUnderwear);
		SetMCMBool("LMBrandingPunish",settings.LMBrandingPunish);
		SetMCMBool("LMNudityChestOnly",settings.LMNudityChestOnly);
		SetMCMBool("oppOneAtATime",settings.oppOneAtATime);
		SetMCMBool("oppSCollarDrainsMagicka",settings.oppSCollarDrainsMagicka);
		SetMCMBool("oppSCollarAutoRemove",settings.oppSCollarAutoRemove);
		SetMCMBool("oppDwarvenHeavyRestraint",settings.oppDwarvenHeavyRestraint);
		SetMCMBool("oppDwarvenRequireLoc",settings.oppDwarvenRequireLoc);
		SetMCMBool("oppLivingLatexHeavy",settings.oppLivingLatexHeavy);
		SetMCMBool("oppLivingLatexRequireRem",settings.oppLivingLatexRequireRem);
		SetMCMBool("oppLivingLatexOpen",settings.oppLivingLatexOpen);
		SetMCMBool("oppMadnessAllOrgasms",settings.oppMadnessAllOrgasms);
		SetMCMBool("oppMadnessBeltFilter",settings.oppMadnessBeltFilter);
		SetMCMBool("oppMadnessChaos",settings.oppMadnessChaos);
		SetMCMBool("useLocationModifiers",settings.useLocationModifiers);
		SetMCMBool("keyForgiveness",settings.keyForgiveness);
		SetMCMBool("magicKeyOppressive",settings.magicKeyOppressive);
		SetMCMBool("preferRelevantKeys",settings.preferRelevantKeys);
		SetMCMBool("vanishingKeys",settings.vanishingKeys);
		SetMCMBool("enableQuestInteractions",settings.enableQuestInteractions);
		SetMCMBool("enableQIMalkoran",settings.enableQIMalkoran);
		SetMCMBool("enableQISanguine",settings.enableQISanguine);
		SetMCMBool("enableQIBlackStar",settings.enableQIBlackStar);
		SetMCMBool("enableQIMindOfMadness",settings.enableQIMindOfMadness);
		SetMCMBool("enableQILaidToRest",settings.enableQILaidToRest);
		SetMCMBool("enableQICriedWolf",settings.enableQICriedWolf);
		SetMCMBool("enableQIProvingHonor",settings.enableQIProvingHonor);
		SetMCMBool("enableQISaarthal",settings.enableQISaarthal);
		SetMCMBool("enableQIBrelyna",settings.enableQIBrelyna);
		SetMCMBool("enableQIDwemerMuseum",settings.enableQIDwemerMuseum);
		SetMCMBool("enableQITrinityRestored",settings.enableQITrinityRestored);
		SetMCMBool("enableQIThalmorEmbassy",settings.enableQIThalmorEmbassy);
		SetMCMBool("enableQIRingmaker",settings.enableQIRingmaker);
		SetMCMBool("oppDeviceAntiCheat",settings.oppDeviceAntiCheat);
		SetMCMBool("generalDeviceAntiCheat",settings.generalDeviceAntiCheat);
		SetMCMBool("noMessageBoxes",settings.noMessageBoxes);
		SetMCMBool("bossChestUseModelPath",settings.bossChestUseModelPath);
		SetMCMBool("dragonHoard",settings.dragonHoard);
		SetMCMBool("bossExtraGold",settings.bossExtraGold);
		SetMCMBool("useThemes",settings.useThemes);
		SetMCMBool("disableForce3rdPerson",settings.disableForce3rdPerson);
		SetMCMBool("enableSlowStrip",settings.enableSlowStrip);
		SetMCMBool("resumeEvents",settings.resumeEvents);
		SetMCMBool("saveDependentSettings",settings.saveDependentSettings);
		SetMCMBool("setAllDefaultSettings",settings.setAllDefaultSettings);
		SetMCMBool("consAllowFollowers",settings.consAllowFollowers);
		SetMCMBool("consAllowCreatures",settings.consAllowCreatures);
		SetMCMBool("consUseRelationships",settings.consUseRelationships);
		SetMCMBool("consRelationBondage",settings.consRelationBondage);
		SetMCMBool("consFallthrough",settings.consFallthrough);
		SetMCMBool("consRandomHeavyBondage",settings.consRandomHeavyBondage);
		SetMCMBool("consBondageIgnoreMax",settings.consBondageIgnoreMax);
		SetMCMBool("sexEnabled",settings.sexEnabled);
		SetMCMBool("sexAggressiveAnims",settings.sexAggressiveAnims);
		SetMCMBool("sexFilterFuta",settings.sexFilterFuta);
		SetMCMBool("sexRandomEnabled",settings.sexRandomEnabled);
		SetMCMBool("sexAllowMale",settings.sexAllowMale);
		SetMCMBool("sexAllowFemale",settings.sexAllowFemale);
		SetMCMBool("sexAllowFuta",settings.sexAllowFuta);
		SetMCMBool("sexAllowCreature",settings.sexAllowCreature);
		SetMCMBool("sexAllowFarmAnimals",settings.sexAllowFarmAnimals);
		SetMCMBool("sexRequireAll",settings.sexRequireAll);
		SetMCMBool("sexRequireBindings",settings.sexRequireBindings);
		SetMCMBool("sexRequireCollar",settings.sexRequireCollar);
		SetMCMBool("sexRequireHeavy",settings.sexRequireHeavy);
		SetMCMBool("sexRequireNude",settings.sexRequireNude);
		SetMCMBool("sexAlwaysAllowFollowers",settings.sexAlwaysAllowFollowers);
		SetMCMBool("sexAlwaysAllowSpouse",settings.sexAlwaysAllowSpouse);
		SetMCMBool("sexAlwaysAllowSummons",settings.sexAlwaysAllowSummons);
		SetMCMString("excludedFollowers",settings.excludedFollowers);
		SetMCMString("LMNudityAditionalForms",settings.LMNudityAditionalForms);
		//CODEGEN_END_PUSHMCM

		log::trace("Updated MCM settings");
	}

	bool NeedUpdateForExclusions();

	void P_UpdateSKSE(RE::StaticFunctionTag*) {
		//CODEGEN_START_UPDATE
		bool recalculate = false;
		if (settings.maxHeldKeys != GetMCMSetting("maxHeldKeys")->GetSInt()) {recalculate = true;}
		if (settings.useGenderedChastity != GetMCMSetting("useGenderedChastity")->GetBool()) {recalculate = true;}
		if (settings.onlyUseUnforgivingDevices != GetMCMSetting("onlyUseUnforgivingDevices")->GetBool()) {recalculate = true;}
		if (settings.udUseAbadon != GetMCMSetting("udUseAbadon")->GetBool()) {recalculate = true;}
		if (settings.udUseAbadonSets != GetMCMSetting("udUseAbadonSets")->GetBool()) {recalculate = true;}
		if (settings.udUseMisc != GetMCMSetting("udUseMisc")->GetBool()) {recalculate = true;}
		settings.minGoldRequired = GetMCMSetting("minGoldRequired")->GetSInt();
		settings.eventScalingMod = GetMCMSetting("eventScalingMod")->GetSInt();
		settings.minRestraints = GetMCMSetting("minRestraints")->GetSInt();
		settings.maxRestraints = GetMCMSetting("maxRestraints")->GetSInt();
		settings.bossAditionalRestraints = GetMCMSetting("bossAditionalRestraints")->GetSInt();
		settings.restraintCap = GetMCMSetting("restraintCap")->GetSInt();
		settings.minArousal = GetMCMSetting("minArousal")->GetSInt();
		settings.beltWeight = GetMCMSetting("beltWeight")->GetSInt();
		settings.chastityPiercingWeight = GetMCMSetting("chastityPiercingWeight")->GetSInt();
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
		settings.eventStandardWeight = GetMCMSetting("eventStandardWeight")->GetSInt();
		settings.eventStandardBossReduction = GetMCMSetting("eventStandardBossReduction")->GetSInt();
		settings.eventOppressiveWeight = GetMCMSetting("eventOppressiveWeight")->GetSInt();
		settings.eventContraptionWeight = GetMCMSetting("eventContraptionWeight")->GetSInt();
		settings.eventContDeviceOverride = GetMCMSetting("eventContDeviceOverride")->GetSInt();
		settings.eventWickedWeight = GetMCMSetting("eventWickedWeight")->GetSInt();
		settings.eventTattooWeight = GetMCMSetting("eventTattooWeight")->GetSInt();
		settings.eventTattooMin = GetMCMSetting("eventTattooMin")->GetSInt();
		settings.eventTattooMax = GetMCMSetting("eventTattooMax")->GetSInt();
		settings.eventTattooCap = GetMCMSetting("eventTattooCap")->GetSInt();
		settings.followerDeviceModifier = GetMCMSetting("followerDeviceModifier")->GetSInt();
		settings.eventLewdMarkWeight = GetMCMSetting("eventLewdMarkWeight")->GetSInt();
		settings.eventSimpleSlaveryWeight = GetMCMSetting("eventSimpleSlaveryWeight")->GetSInt();
		settings.eventSSMinRestraints = GetMCMSetting("eventSSMinRestraints")->GetSInt();
		settings.eventAbadonWeight = GetMCMSetting("eventAbadonWeight")->GetSInt();
		settings.eventAbadonWarriorWeight = GetMCMSetting("eventAbadonWarriorWeight")->GetSInt();
		settings.eventAbadonWarriorCount = GetMCMSetting("eventAbadonWarriorCount")->GetSInt();
		settings.eventAbadonScoutWeight = GetMCMSetting("eventAbadonScoutWeight")->GetSInt();
		settings.eventAbadonScoutCount = GetMCMSetting("eventAbadonScoutCount")->GetSInt();
		settings.eventAbadonWitchWeight = GetMCMSetting("eventAbadonWitchWeight")->GetSInt();
		settings.eventAbadonWitchCount = GetMCMSetting("eventAbadonWitchCount")->GetSInt();
		settings.LMAllureWeight = GetMCMSetting("LMAllureWeight")->GetSInt();
		settings.LMAllureMod = GetMCMSetting("LMAllureMod")->GetSInt();
		settings.LMAllureSex = GetMCMSetting("LMAllureSex")->GetSInt();
		settings.LMHeatWeight = GetMCMSetting("LMHeatWeight")->GetSInt();
		settings.LMHeatMod = GetMCMSetting("LMHeatMod")->GetSInt();
		settings.LMHeatContainerCount = GetMCMSetting("LMHeatContainerCount")->GetSInt();
		settings.LMBrandingWeight = GetMCMSetting("LMBrandingWeight")->GetSInt();
		settings.LMBrandingTotal = GetMCMSetting("LMBrandingTotal")->GetSInt();
		settings.LMBondageWeight = GetMCMSetting("LMBondageWeight")->GetSInt();
		settings.LMBondageDeviceCount = GetMCMSetting("LMBondageDeviceCount")->GetSInt();
		settings.LMNudityWeight = GetMCMSetting("LMNudityWeight")->GetSInt();
		settings.LMNudityTalkTimes = GetMCMSetting("LMNudityTalkTimes")->GetSInt();
		settings.LMHealslutWeight = GetMCMSetting("LMHealslutWeight")->GetSInt();
		settings.LMHealslutHealing = GetMCMSetting("LMHealslutHealing")->GetSInt();
		settings.oppSummonerCollarWeight = GetMCMSetting("oppSummonerCollarWeight")->GetSInt();
		settings.oppSummonerSexCount = GetMCMSetting("oppSummonerSexCount")->GetSInt();
		settings.oppSMinSummonArousal = GetMCMSetting("oppSMinSummonArousal")->GetSInt();
		settings.oppDwarvenCuirassWeight = GetMCMSetting("oppDwarvenCuirassWeight")->GetSInt();
		settings.oppDwarvenValueNeeded = GetMCMSetting("oppDwarvenValueNeeded")->GetSInt();
		settings.oppDwarvenArousal = GetMCMSetting("oppDwarvenArousal")->GetSInt();
		settings.oppNocturnalWeight = GetMCMSetting("oppNocturnalWeight")->GetSInt();
		settings.oppNocturnalSexCount = GetMCMSetting("oppNocturnalSexCount")->GetSInt();
		settings.oppNocturnalPeople = GetMCMSetting("oppNocturnalPeople")->GetSInt();
		settings.oppNocturnalArousal = GetMCMSetting("oppNocturnalArousal")->GetSInt();
		settings.oppLivingLatexWeight = GetMCMSetting("oppLivingLatexWeight")->GetSInt();
		settings.oppLivingLatexStartTime = GetMCMSetting("oppLivingLatexStartTime")->GetSInt();
		settings.oppMadnessPlugWeight = GetMCMSetting("oppMadnessPlugWeight")->GetSInt();
		settings.oppMadnessPlugIterations = GetMCMSetting("oppMadnessPlugIterations")->GetSInt();
		settings.oppMadnessplugOrgasms = GetMCMSetting("oppMadnessplugOrgasms")->GetSInt();
		settings.minKeysLooted = GetMCMSetting("minKeysLooted")->GetSInt();
		settings.maxKeysLooted = GetMCMSetting("maxKeysLooted")->GetSInt();
		settings.maxHeldKeys = GetMCMSetting("maxHeldKeys")->GetSInt();
		settings.restraintsKeyWeight = GetMCMSetting("restraintsKeyWeight")->GetSInt();
		settings.chastityKeyWeight = GetMCMSetting("chastityKeyWeight")->GetSInt();
		settings.piercingToolWeight = GetMCMSetting("piercingToolWeight")->GetSInt();
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
		settings.sexSearchRadius = GetMCMSetting("sexSearchRadius")->GetSInt();
		settings.sexSearchInterval = GetMCMSetting("sexSearchInterval")->GetSInt();
		settings.sexRequiredPlayerArousal = GetMCMSetting("sexRequiredPlayerArousal")->GetSInt();
		settings.sexRequiredPlayerTattoos = GetMCMSetting("sexRequiredPlayerTattoos")->GetSInt();
		settings.sexChanceFollower = GetMCMSetting("sexChanceFollower")->GetSInt();
		settings.sexChanceSpouse = GetMCMSetting("sexChanceSpouse")->GetSInt();
		settings.sexChanceSummon = GetMCMSetting("sexChanceSummon")->GetSInt();
		settings.LMAllureColor = GetMCMSetting("LMAllureColor")->GetSInt();
		settings.LMHeatColor = GetMCMSetting("LMHeatColor")->GetSInt();
		settings.LMBrandingColor = GetMCMSetting("LMBrandingColor")->GetSInt();
		settings.LMBondageColor = GetMCMSetting("LMBondageColor")->GetSInt();
		settings.LMNudityColor = GetMCMSetting("LMNudityColor")->GetSInt();
		settings.LMHealslutColor = GetMCMSetting("LMHealslutColor")->GetSInt();
		settings.setDebugKey = GetMCMSetting("setDebugKey")->GetSInt();
		settings.baseChance = GetMCMSetting("baseChance")->GetFloat();
		settings.containerModifier = GetMCMSetting("containerModifier")->GetFloat();
		settings.bossContainerModifier = GetMCMSetting("bossContainerModifier")->GetFloat();
		settings.deadBodyModifier = GetMCMSetting("deadBodyModifier")->GetFloat();
		settings.pickpocketModifier = GetMCMSetting("pickpocketModifier")->GetFloat();
		settings.doorModifier = GetMCMSetting("doorModifier")->GetFloat();
		settings.lockedModifier = GetMCMSetting("lockedModifier")->GetFloat();
		settings.lockDifficultyModifier = GetMCMSetting("lockDifficultyModifier")->GetFloat();
		settings.arousalModifier = GetMCMSetting("arousalModifier")->GetFloat();
		settings.eventContraptionTime = GetMCMSetting("eventContraptionTime")->GetFloat();
		settings.LMBrandingChance = GetMCMSetting("LMBrandingChance")->GetFloat();
		settings.LMBondageChance = GetMCMSetting("LMBondageChance")->GetFloat();
		settings.oppSummonChance = GetMCMSetting("oppSummonChance")->GetFloat();
		settings.oppNocturnalHandChance = GetMCMSetting("oppNocturnalHandChance")->GetFloat();
		settings.oppNocturnalRecastChance = GetMCMSetting("oppNocturnalRecastChance")->GetFloat();
		settings.oppLivingLatexGem = GetMCMSetting("oppLivingLatexGem")->GetFloat();
		settings.oppLivingLatexMore = GetMCMSetting("oppLivingLatexMore")->GetFloat();
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
		settings.keyLossChance = GetMCMSetting("keyLossChance")->GetFloat();
		settings.keyChance = GetMCMSetting("keyChance")->GetFloat();
		settings.keyBonus = GetMCMSetting("keyBonus")->GetFloat();
		settings.keyPickpocketBonus = GetMCMSetting("keyPickpocketBonus")->GetFloat();
		settings.magicKeyChance = GetMCMSetting("magicKeyChance")->GetFloat();
		settings.keyLuckyBonus = GetMCMSetting("keyLuckyBonus")->GetFloat();
		settings.rDeviceBaseChance = GetMCMSetting("rDeviceBaseChance")->GetFloat();
		settings.rDeviceLuckyBonus = GetMCMSetting("rDeviceLuckyBonus")->GetFloat();
		settings.tatSolventChance = GetMCMSetting("tatSolventChance")->GetFloat();
		settings.arousalPotionChance = GetMCMSetting("arousalPotionChance")->GetFloat();
		settings.arousalPotionLibido = GetMCMSetting("arousalPotionLibido")->GetFloat();
		settings.consTriggerNude = GetMCMSetting("consTriggerNude")->GetFloat();
		settings.consTriggerRestrained = GetMCMSetting("consTriggerRestrained")->GetFloat();
		settings.consTriggerSex = GetMCMSetting("consTriggerSex")->GetFloat();
		settings.sexArousalTattooModifier = GetMCMSetting("sexArousalTattooModifier")->GetFloat();
		settings.onlyLockedDoors = GetMCMSetting("onlyLockedDoors")->GetBool();
		settings.eventScaling = GetMCMSetting("eventScaling")->GetBool();
		settings.bossOnlyHeavy = GetMCMSetting("bossOnlyHeavy")->GetBool();
		settings.stripPlayerOnEvent = GetMCMSetting("stripPlayerOnEvent")->GetBool();
		settings.stripOnlyKeywords = GetMCMSetting("stripOnlyKeywords")->GetBool();
		settings.beltPlugs = GetMCMSetting("beltPlugs")->GetBool();
		settings.useGenderedChastity = GetMCMSetting("useGenderedChastity")->GetBool();
		settings.plugsDontCount = GetMCMSetting("plugsDontCount")->GetBool();
		settings.allowLegShackles = GetMCMSetting("allowLegShackles")->GetBool();
		settings.eventContDevices = GetMCMSetting("eventContDevices")->GetBool();
		settings.eventContAllDevices = GetMCMSetting("eventContAllDevices")->GetBool();
		settings.allowFollowerEvents = GetMCMSetting("allowFollowerEvents")->GetBool();
		settings.onlyFemaleFollowers = GetMCMSetting("onlyFemaleFollowers")->GetBool();
		settings.followerHeavyRestraints = GetMCMSetting("followerHeavyRestraints")->GetBool();
		settings.onlyUseUnforgivingDevices = GetMCMSetting("onlyUseUnforgivingDevices")->GetBool();
		settings.udUseAbadon = GetMCMSetting("udUseAbadon")->GetBool();
		settings.udUseAbadonSets = GetMCMSetting("udUseAbadonSets")->GetBool();
		settings.udUseMisc = GetMCMSetting("udUseMisc")->GetBool();
		settings.ANDSexTopless = GetMCMSetting("ANDSexTopless")->GetBool();
		settings.ANDSexBottomless = GetMCMSetting("ANDSexBottomless")->GetBool();
		settings.ANDSexShowingChest = GetMCMSetting("ANDSexShowingChest")->GetBool();
		settings.ANDSexShowingGenitals = GetMCMSetting("ANDSexShowingGenitals")->GetBool();
		settings.ANDSexShowingAss = GetMCMSetting("ANDSexShowingAss")->GetBool();
		settings.ANDSexShowingBra = GetMCMSetting("ANDSexShowingBra")->GetBool();
		settings.ANDSexShowingUnderwear = GetMCMSetting("ANDSexShowingUnderwear")->GetBool();
		settings.ANDConsTopless = GetMCMSetting("ANDConsTopless")->GetBool();
		settings.ANDConsBottomless = GetMCMSetting("ANDConsBottomless")->GetBool();
		settings.ANDConsShowingChest = GetMCMSetting("ANDConsShowingChest")->GetBool();
		settings.ANDConsShowingGenitals = GetMCMSetting("ANDConsShowingGenitals")->GetBool();
		settings.ANDConsShowingAss = GetMCMSetting("ANDConsShowingAss")->GetBool();
		settings.ANDConsShowingBra = GetMCMSetting("ANDConsShowingBra")->GetBool();
		settings.ANDConsShowingUnderwear = GetMCMSetting("ANDConsShowingUnderwear")->GetBool();
		settings.LMBrandingPunish = GetMCMSetting("LMBrandingPunish")->GetBool();
		settings.LMNudityChestOnly = GetMCMSetting("LMNudityChestOnly")->GetBool();
		settings.oppOneAtATime = GetMCMSetting("oppOneAtATime")->GetBool();
		settings.oppSCollarDrainsMagicka = GetMCMSetting("oppSCollarDrainsMagicka")->GetBool();
		settings.oppSCollarAutoRemove = GetMCMSetting("oppSCollarAutoRemove")->GetBool();
		settings.oppDwarvenHeavyRestraint = GetMCMSetting("oppDwarvenHeavyRestraint")->GetBool();
		settings.oppDwarvenRequireLoc = GetMCMSetting("oppDwarvenRequireLoc")->GetBool();
		settings.oppLivingLatexHeavy = GetMCMSetting("oppLivingLatexHeavy")->GetBool();
		settings.oppLivingLatexRequireRem = GetMCMSetting("oppLivingLatexRequireRem")->GetBool();
		settings.oppLivingLatexOpen = GetMCMSetting("oppLivingLatexOpen")->GetBool();
		settings.oppMadnessAllOrgasms = GetMCMSetting("oppMadnessAllOrgasms")->GetBool();
		settings.oppMadnessBeltFilter = GetMCMSetting("oppMadnessBeltFilter")->GetBool();
		settings.oppMadnessChaos = GetMCMSetting("oppMadnessChaos")->GetBool();
		settings.useLocationModifiers = GetMCMSetting("useLocationModifiers")->GetBool();
		settings.keyForgiveness = GetMCMSetting("keyForgiveness")->GetBool();
		settings.magicKeyOppressive = GetMCMSetting("magicKeyOppressive")->GetBool();
		settings.preferRelevantKeys = GetMCMSetting("preferRelevantKeys")->GetBool();
		settings.vanishingKeys = GetMCMSetting("vanishingKeys")->GetBool();
		settings.enableQuestInteractions = GetMCMSetting("enableQuestInteractions")->GetBool();
		settings.enableQIMalkoran = GetMCMSetting("enableQIMalkoran")->GetBool();
		settings.enableQISanguine = GetMCMSetting("enableQISanguine")->GetBool();
		settings.enableQIBlackStar = GetMCMSetting("enableQIBlackStar")->GetBool();
		settings.enableQIMindOfMadness = GetMCMSetting("enableQIMindOfMadness")->GetBool();
		settings.enableQILaidToRest = GetMCMSetting("enableQILaidToRest")->GetBool();
		settings.enableQICriedWolf = GetMCMSetting("enableQICriedWolf")->GetBool();
		settings.enableQIProvingHonor = GetMCMSetting("enableQIProvingHonor")->GetBool();
		settings.enableQISaarthal = GetMCMSetting("enableQISaarthal")->GetBool();
		settings.enableQIBrelyna = GetMCMSetting("enableQIBrelyna")->GetBool();
		settings.enableQIDwemerMuseum = GetMCMSetting("enableQIDwemerMuseum")->GetBool();
		settings.enableQITrinityRestored = GetMCMSetting("enableQITrinityRestored")->GetBool();
		settings.enableQIThalmorEmbassy = GetMCMSetting("enableQIThalmorEmbassy")->GetBool();
		settings.enableQIRingmaker = GetMCMSetting("enableQIRingmaker")->GetBool();
		settings.oppDeviceAntiCheat = GetMCMSetting("oppDeviceAntiCheat")->GetBool();
		settings.generalDeviceAntiCheat = GetMCMSetting("generalDeviceAntiCheat")->GetBool();
		settings.noMessageBoxes = GetMCMSetting("noMessageBoxes")->GetBool();
		settings.bossChestUseModelPath = GetMCMSetting("bossChestUseModelPath")->GetBool();
		settings.dragonHoard = GetMCMSetting("dragonHoard")->GetBool();
		settings.bossExtraGold = GetMCMSetting("bossExtraGold")->GetBool();
		settings.useThemes = GetMCMSetting("useThemes")->GetBool();
		settings.disableForce3rdPerson = GetMCMSetting("disableForce3rdPerson")->GetBool();
		settings.enableSlowStrip = GetMCMSetting("enableSlowStrip")->GetBool();
		settings.resumeEvents = GetMCMSetting("resumeEvents")->GetBool();
		settings.saveDependentSettings = GetMCMSetting("saveDependentSettings")->GetBool();
		settings.setAllDefaultSettings = GetMCMSetting("setAllDefaultSettings")->GetBool();
		settings.consAllowFollowers = GetMCMSetting("consAllowFollowers")->GetBool();
		settings.consAllowCreatures = GetMCMSetting("consAllowCreatures")->GetBool();
		settings.consUseRelationships = GetMCMSetting("consUseRelationships")->GetBool();
		settings.consRelationBondage = GetMCMSetting("consRelationBondage")->GetBool();
		settings.consFallthrough = GetMCMSetting("consFallthrough")->GetBool();
		settings.consRandomHeavyBondage = GetMCMSetting("consRandomHeavyBondage")->GetBool();
		settings.consBondageIgnoreMax = GetMCMSetting("consBondageIgnoreMax")->GetBool();
		settings.sexEnabled = GetMCMSetting("sexEnabled")->GetBool();
		settings.sexAggressiveAnims = GetMCMSetting("sexAggressiveAnims")->GetBool();
		settings.sexFilterFuta = GetMCMSetting("sexFilterFuta")->GetBool();
		settings.sexRandomEnabled = GetMCMSetting("sexRandomEnabled")->GetBool();
		settings.sexAllowMale = GetMCMSetting("sexAllowMale")->GetBool();
		settings.sexAllowFemale = GetMCMSetting("sexAllowFemale")->GetBool();
		settings.sexAllowFuta = GetMCMSetting("sexAllowFuta")->GetBool();
		settings.sexAllowCreature = GetMCMSetting("sexAllowCreature")->GetBool();
		settings.sexAllowFarmAnimals = GetMCMSetting("sexAllowFarmAnimals")->GetBool();
		settings.sexRequireAll = GetMCMSetting("sexRequireAll")->GetBool();
		settings.sexRequireBindings = GetMCMSetting("sexRequireBindings")->GetBool();
		settings.sexRequireCollar = GetMCMSetting("sexRequireCollar")->GetBool();
		settings.sexRequireHeavy = GetMCMSetting("sexRequireHeavy")->GetBool();
		settings.sexRequireNude = GetMCMSetting("sexRequireNude")->GetBool();
		settings.sexAlwaysAllowFollowers = GetMCMSetting("sexAlwaysAllowFollowers")->GetBool();
		settings.sexAlwaysAllowSpouse = GetMCMSetting("sexAlwaysAllowSpouse")->GetBool();
		settings.sexAlwaysAllowSummons = GetMCMSetting("sexAlwaysAllowSummons")->GetBool();
		settings.excludedFollowers = GetMCMSetting("excludedFollowers")->GetString();
		settings.LMNudityAditionalForms = GetMCMSetting("LMNudityAditionalForms")->GetString();
		//CODEGEN_END_UPDATE
		if (settings.setAllDefaultSettings) {
			ResetMCMSettings();
		}

		if (settings.resumeEvents) {
			SetMCMBool("ModSuspended", false);
		}

		EventsCheckModIntergations();

		SaveMCMSettings();

		if (recalculate) {
			log::info("Recalculating device lists due to settings changes.");
			RecalculateDeviceLists();
		}
		if (NeedUpdateForExclusions()) {
			log::info("Recalculating device lists due to exclusions changes.");
			RecalculateDeviceLists();
		}
	}

	bool PapyrusFunctionsSettigns(RE::BSScript::IVirtualMachine* ivm) {
		ivm->RegisterFunction("UpdateSKSE", "DCurses_MCM", P_UpdateSKSE);
		return true;
	}

}