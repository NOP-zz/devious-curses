#pragma once

namespace DCURSES {
	constexpr auto TRANSLATIONS_PREFIX = "Data/translations/Devious Curses_{}.json";
	constexpr auto TRANSLATIONS_PREFIX_STRINGS = "Data/translations/Devious Curses_Strings_{}.json";

	enum class Translation : uint32_t {
		//TRNASLATIONS_START
		ConsequenceRandomDevice_Sex,//While you're distracted, {} slips a {} on you before you can react!
		ConsequenceRandomDevice_Nude,//Amused with your nudity, {} slips a {} on you before you can react!
		ConsequenceRandomDevice_Restrained,//Seing you already restrained, {} decides you could add a {} to your collection!
		ConsequenceRandomDevice_Heavy,//Being in the helpless state you are, {} puts a {} on you with little resistance.
		ConsequenceRandomDevice_Tattoo,//Seeing you covered in tattoos, {} slips a {} on you before you can react!
		ConsequenceRandomDevice_Trespass,//{} catches you tresspassing and locks you in a {}!
		ConsequenceSex_Sex,//After watching you have sex, {} decides that it's their turn now!
		ConsequenceSex_Nude,//{} can't resist fucking you after seeing your naked body!
		ConsequenceSex_Restrained,//{} can't resist fucking you after seeing your bound body!
		ConsequenceSex_Heavy,//While bound and helpless you can't stop {} from fucking you!
		ConsequenceSex_Tattoos,//{} can't resist fucking you after seeing you covered in tattoos!
		ConsequenceSex_Trespass,//{} catches you trespassing and decised to have their way with you!
		ConsequenceFine_Sex,//{} saw you having sex in public and is giving you a fine!
		ConsequenceFine_SeenNude,//{} saw you naked in public and is giving you a fine!
		ConsequenceFine_TalkedNude,//You talked to a guard while nude, and now you're in trouble!
		ConsequenceFine_SeenRestrained,//{} saw you walking around in public while restrained and is giving you a fine!
		ConsequenceFine_TalkedRestrained,//You talked to a guard while restrained, and now you're in trouble!
		ConsequenceFine_SeenTattoos,//{} saw you walking around in public while covered in tattoos and is giving you a fine!
		ConsequenceFine_TalkedTattoos,//You talked to a guard while covered in tattoos, and now you're in trouble!
		ConsequenceTattoo_Sex,//You didn't notice right away, but {} branded you with a tattoo while you were having sex!
		ConsequenceTattoo_SexMultiple,//You didn't notice right away, but {} branded you with tattoos while you were having sex!
		ConsequenceTattoo_Trespass,//{} catches you tresspassing and brands you with a tattoo!
		ConsequenceTattoo_TrespassMultiple,//{} catches you tresspassing and brands you with tattoos!
		ConsequenceTattoo_Other,//You feel a sharp pain as {} brands you with a tattoo!
		ConsequenceTattoo_OtherMultiple,//You feel a sharp pain as {} brands you with tattoos!
		ConsequenceMercy_Unlock,//{} feels bad for you and unlocks your restraints.
		ConsequenceMercy_Key,//{} feels bad for you and gives you a {}.

		ODeviceSummonerCollarStart,//As you touch the {} you feel very dizzy as a heavy collar forms around your neck and absorbs your magicka!
		ODeviceSummonerCollarRemove,//The Summoner Collar is now satisfied and dissapears from your neck!
		ODeviceSummonerCollarUnlock,//The Summoner Collar is now satisfied and you can unlock it!
		ODeviceLivingLatexStart,//As you touch the {} a ball of goo jumps out at you and covers your body!
		ODeviceLivingLatexSpread,//The latex has spread over your body!
		ODeviceLivingLatexTrigger,//"Suddenly the latex suit springs to life, covering you in ebonite! Is it trying to protect itself?"
		ODeviceLivingLatexOnHit,//The latex writhes while being shocked. It seems as if it has been weakened significantly!
		ODeviceLivingLatexOnHitFrost,//The latex writhes while being frozen. It seems as if it has been weakened significantly!
		ODeviceLivingLatexRemove,//The latex suit dissolves from your body!
		ODeviceDwarvenCuirassStart,//As you touch the {} you feel a dwarven automaton crawl onto your body!
		ODeviceDwarvenCuirassEat,//The dwarven cuirass pulls some parts from your bag!
		ODeviceDwarvenCuirassDestroyBelt,//You flinch as the dwarven cuirass reaches down and snaps your chastity belt in half!
		ODeviceDwarvenCuirassMasturbate,//You freeze as the dwarven cuirass takes control and starts masturbating you!
		ODeviceDwarvenCuirassCraft,//The dwarven cuirass makes a {} with some of it's parts and puts it on you!
		ODeviceDwarvenCuirassRemove,//Your skin crawls as the dwarven atomaton climbs off you and morphs into a {}!
		ODeviceMadnessPlugStart,//You shudder as a large plug is summoned directly into your ass!
		ODeviceMadnessPlugPiercings,//The plug summons some piercings directly into your nipples!
		ODeviceMadnessPlugDesire,//You feel the plug surge with desire, you have to orgasm an additional {} times before your next event!
		ODeviceMadnessPlugStandard,//The plug summons some devices directly onto you!
		ODeviceMadnessPlugBoss,//The plug summons many devices directly onto you!
		ODeviceMadnessPlugFullTie,//The plug summons as many devices as it can directly onto you!
		ODeviceMadnessPlugFollowers,//The plug summons some devices directly onto your followers!
		ODeviceMadnessPlugFullTieFollowers,//The plug summons as many devices as it can directly onto your followers!
		ODeviceMadnessPlugMark,//The plug brands you with a lewd mark!
		ODeviceMadnessPlugTattoos,//The plug covers you with tattoos!
		ODeviceMadnessPlugTattooFollowers,//The plug covers all of your followers with tattoos!
		ODeviceMadnessPlugStats,//The plug saps your strength and you feel much weaker!
		ODeviceMadnessPlugGold,//The plug magically destroys all of your gold!
		ODeviceMadnessPlugCrash,//The plug makes you feel incredibly unstable!
		ODeviceMadnessPlugRemove,//With a final flourish, the plug vanishes, leaving behind numerous devices!
		ODeviceMadnessPlugHunger,//You feel the plug pulse with hunger, you will need to do an extra event!
		ODeviceMadnessPlugOrgasm,//With no warning, the plug makes you orgasm instantly!
		ODeviceMadnessPlugLongVib,//You shudder as the plug activates all of your devices! You think the slow tease might last a while...
		ODeviceMadnessPlugMediumVib,//You tense as your devices start to vibrate strongly!
		ODeviceMadnessPlugSuperVib,//Your devices immediately start going at full blast!
		ODeviceMadnessDescription,//The plug still needs to make you cum <mag> times in total! (This will not count orgasms from sex scenets)
		ODeviceMadnessDescriptionSex,//You still need to orgasm <mag> times in total!
		ODeviceNocturnalPiercingStart,//As you touch the {} you sense that it was cursed by an agent of nocturnal herself!
		ODeviceNocturnalPiercingAnger,//Nocturnal seems angry with you being seen orgasming. She locks you in some restraints!
		ODeviceNocturnalPiercingRemove,//Nocturnal takes her boon from you, leaving you bound and helpless!
		ODeviceNocturnalPiercingVibrate,//You feel hands slide across your body activating some of your devices!
		ODeviceNocturnalPiercingHands,//You feel a hand gently slide across your groin!
		ODeviceNocturnalPiercingHands2,//You shudder as invisible hands trace your body!
		ODeviceNocturnalPiercingHands3,//You flush with arousal as invisible hands grope your chest and pussy!
		ODeviceNocturnalPiercingHands4,//You stifle a moan as invisible hands tease their way inside of you!
		ODeviceNocturnalPiercingHandsRecast,//As you regain your invisibility you feel hands tickling across your body!

		EventDevices,//As you touch the {} you see restraints magically appear and wrap themselves around you!
		EventSimpleSlavery,//As you touch the {} you see a flash of light and immediately pass out. Through intermittent consciousness you can feel someone carrying you somewhere...
		EventTattooOne,//As you touch the {} you feel a sharp pain as a tattoo appears on your body!
		EventTattooTwoThree,//As you touch the {} you feel a sharp pain as a few tattoos appear on your body!
		EventTattooMany,//As you touch the {} you feel a sharp pain as your body is covered in tattoos!
		EventContraption,//As you touch the {} you feel yourself get dizzy as you are strung up into some sort of contraption!
		EventMarkBranding,//After a sharp pain, you see that you have a mark of branding.
		EventMarkAllure,//After a sharp pain, you see that you have a mark of allure.
		EventMarkHeat,//After a sharp pain, you see that you have a mark of heat.
		EventMarkBondage,//After a sharp pain, you see that you have a mark of bondage.
		EventMarkNudity,//After a sharp pain, you see that you have a mark of nudity.
		EventMarkHealslut,//After a sharp pain, you see that you have a mark of the healslut.
		EventMarkPainslut,//After a sharp pain, you see that you have a mark of the painslut.
		EventWicked,//As you touch the {} you feel an overwhelming sense of wickedness!
		EventAbadon,//As you touch the {} you feel an evil curse seeping into you!
		EventAbadonWarrior,//As you touch the {} you feel empowered with the strength of a Warrior.
		EventAbadonScout,//As you touch the {} you feel empowered with the agility of a Scout.
		EventAbadonWitch,//As you touch the {} you feel empowered with the intelligence of a Witch.

		MarkHeatRemove,//You feel a sense of calm as the heat mark fades from your body.
		MarkAllureRemove,//You sense that people are no longer staring at you as the allure mark fades from your body.
		MarkBondageDevice,//Your mark pulses with light as your {} appears on your body!
		MarkBondageRemove,//You feel much less oppressed as the bondage mark fades from your body.
		MarkBondageCurse,//As you touch the {} your mark glows, causing restraints to magically appear and wrap themselves around you!
		MarkNudityEnforce,//As you put on your clothes, you feel compelled to take them off again!
		MarkNudityRemove,//You feel less helpless as the nudity mark fades from your body.
		MarkBrandingPunish,//You loose {} gold as punishment for loosing tattoos!
		MarkBrandingTattoo,//You feel a sharp pain as the mark brands you!
		MarkBrandingRemove,//You feel the branding mark fade from your body.
		MarkHealslutRemove,//You feel your strength return as the healslut mark fades from your body.
		MarkPainslutSex,//Seeing you in ecstasy, {} decides to stop fighting you and have some fun! 
		MarkPainslutRemove,//You feel the painslut mark fade from your body.

		QIMalkoranCurse,//As you kill Malkoran he curses you with a mark of branding!
		QISanguineStart,//As you awaken you notice that you're covered in chains and have a strange mark on you. Hopefully Sam can fix this...
		QISanguineKey,//Now that your wild adventure with Sanguine is over, he gives you a magic key!
		QISanguineKeyMark,//Now that your wild adventure with Sanguine is over, he gives you a magic key and removes your nudity mark!
		QISaarthal,//Strange magic interacts with the amulet transforming it into a collar!
		QIBrelyna,//As Brelyna casts her spell you feel an additional odd sensation on your crotch!
		QIDwemerMuseum,//As you touch the stone tablet you feel a sharp pain in your crotch!
		QIDwemerMuseumCurias,//As you touch the stone tablet you feel a sharp pain in your crotch! While you're distracted, a strange dwemer creature runs up behind you and jumps on you!
		QIProvingHonor,//As you pull the lever silver objects shoot out from around you and lock on to your body!
		QIBlackStarEquip,//As you touch the black star you feel yourself being filled with soul gems summoned from oblivion!
		QIDiplomaticImmunity,//While on the cart to the Thalmor Embassy your party clothes suddenly transformed into something else!
		QIMindOfMadness,//After arriving in a strange dimension, you find yourself oddly full...
		QILaidToRest,//As you look through the journal you see a strange rune on a page that jumps out at you, literally!
		QICriedWolf,//With the Ritual Master dead, the binding magic goes haywire!
		QIRingmaker,//With the necklace, Madesi also gives you two rings. They feel lucky...
		QITrinityRestored,//After transacting your oath with Nocturnal, she bestows upon you a boon!
		QIDeliveryStart,//To help you stay motivated, {} locks you in some restraints and tells you that {} is expecting you to be wearing them!
		QIDeliveryEnd,//In appreciation of you delivering the {} without taking off your restraints, {} gives you a magic key!
		QIDeliveryEndBad,//Dissapointed in your dissobedience, {} locks you up in even more restraints!

		ItemMagicKey,//All of the devices you were wearing have magically disappeared!
		ItemMagicKeyOther,//All of the devices {} was wearing have magically disappeared!
		ItemTattooCharm,//All of your tattoos have faded from your body!
		ItemTattooCharmOther,//All of {}'s tattoos have faded from their body!
		ItemArousalPotion,//You feel your arousal fade from your body!
		ItemWardUsed,//You feel the warding charm shatter in your pack as it dispells the curse on the {}!

		EffectLivingLatexWait,//The latex suit seems to be dormant. You will probably have to wait for a while.
		EffectLivingLatexDormant,//The latex suit seems to be dormant. Maybe it would do something if it was attacked.
		EffectLivingLatexAwoken,//The latex has awoken! Maybe you can weaken it by shocking it.
		EffectLivingLatexCling,//The latex is clinging to you only by your other devices, removing them should do the trick!
		
		FastTravelUnableHeavy,//You are unable to fast travel due to your heavy bondage!
		FastTravelUnableBoots,//You are unable to fast travel due to your boots!
		FastTravelUnableBlind,//You can't fast travel while you're blinded!
		FastTravelUnableHobble,//You are unable to fast travel due to your hobble dress!
		FastTravelUnableVisible,//You can't fast travel while any of your devices are visible!
		FastTravelUnableDevices,//You can't fast travel while wearing any devious device!
		FastTravelUnableNamed,//You can't fast travel while wearing {}!

		QuestLFTrinketName,//{}'s Trinket
		//TRNASLATIONS_END
	};

	class TranslationData {
	private:
		TranslationData() {}
	public:
		std::filesystem::file_time_type lastTranslationsEditTime = std::chrono::clock_cast<std::filesystem::file_time_type::clock>(std::chrono::system_clock::now());
		std::string languageFilename = fmt::format(TRANSLATIONS_PREFIX, "ENGLISH");

		TranslationData(TranslationData const&) = delete;
		void operator=(TranslationData const&) = delete;

		static TranslationData* GetSingleton() {
			static TranslationData instance;
			return &instance;
		};
	};

	typedef std::map<std::string, std::string> TranslationsMap;

	class Translator {
	private:
		static std::string GetTranslationKeyName(Translation key);

		static std::string _GetTranslation(Translation key);

		std::string translatedString;
		Translator();
	public:
		Translator(Translation key);

		static TranslationsMap* GetTranslationsMap();

		static TranslationsMap LoadTranslationsMap(std::string langFilename);

		template<typename ...Args>
		Translator(Translation key, Args ...args) {
			translatedString = fmt::vformat(_GetTranslation(key), fmt::make_format_args(args...));
		}

		std::string GetTranslation();

		static void UpdateTranslations();
	};
}