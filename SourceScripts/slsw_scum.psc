Scriptname SLSW_scum extends ReferenceAlias  

Spell property SLSW_ISMRemovalSpell Auto
SLSW_mcmconfig property MCM auto
SLSW_upkeep property main auto
quest property scumquest auto
quest property InnDemands auto
WorldSpace Property Tamriel Auto
keyword Property LoctypeInn auto
GlobalVariable Property slsw_addictionIndicator auto
SPELL property slsw_bd_stage1 auto
SPELL property slsw_bd_stage2 auto
SPELL property slsw_bd_stage3 auto
SPELL property slsw_bd_stage4 auto
SPELL property slsw_bd_sideeffect auto
SPELL property slsw_ddsk_1 auto
SPELL property slsw_ddsk_2 auto
SPELL property slsw_ddsk_3 auto
SPELL property slsw_ddsk_4 auto
SPELL property slsw_ddsk_kj_1 auto
SPELL property slsw_ddsk_kj_2 auto
SPELL property slsw_ddsk_kj_3 auto
SPELL property slsw_ddsk_kj_4 auto
SPELL property slsw_ef_stage1 auto
SPELL property slsw_ef_stage2 auto
SPELL property slsw_ef_stage3 auto
SPELL property slsw_ef_stage4 auto
SPELL property slsw_leafskooma_1 auto
SPELL property slsw_leafskooma_2 auto
SPELL property slsw_leafskooma_3 auto
SPELL property slsw_leafskooma_4 auto
SPELL property slsw_leafskooma_kj_1 auto
SPELL property slsw_leafskooma_kj_2 auto
SPELL property slsw_leafskooma_kj_3 auto
SPELL property slsw_leafskooma_kj_4 auto
SPELL property slsw_mf_stage1 auto
SPELL property slsw_mf_stage2 auto
SPELL property slsw_mf_stage3 auto
SPELL property slsw_mf_stage4 auto
SPELL property slsw_mt_stage1 auto
SPELL property slsw_mt_stage2 auto
SPELL property slsw_mt_stage3 auto
SPELL property slsw_mt_stage4 auto
SPELL property slsw_op_stage1 auto
SPELL property slsw_op_stage2 auto
SPELL property slsw_op_stage3 auto
SPELL property slsw_op_stage4 auto
SPELL property slsw_skooma_1 auto
SPELL property slsw_skooma_2 auto
SPELL property slsw_skooma_3 auto
SPELL property slsw_skooma_4 auto
SPELL property slsw_skooma_kj_1 auto
SPELL property slsw_skooma_kj_2 auto
SPELL property slsw_skooma_kj_3 auto
SPELL property slsw_skooma_kj_4 auto
SPELL property slsw_tam_stage1 auto
SPELL property slsw_tam_stage2 auto
SPELL property slsw_tam_stage3 auto
SPELL property slsw_tam_stage4 auto
SPELL property slsw_tc_stage1 auto
SPELL property slsw_tc_stage2 auto
SPELL property slsw_tc_stage3 auto
SPELL property slsw_tc_stage4 auto
SPELL property slsw_td_stage1 auto
SPELL property slsw_td_stage2 auto
SPELL property slsw_td_stage3 auto
SPELL property slsw_td_stage4 auto
SPELL property slsw_tf_stage1 auto
SPELL property slsw_tf_stage2 auto
SPELL property slsw_tf_stage3 auto
SPELL property slsw_tf_stage4 auto
SPELL property slsw_tsb_stage1 auto
SPELL property slsw_tsb_stage2 auto
SPELL property slsw_tsb_stage3 auto
SPELL property slsw_tsb_stage4 auto

Event OnCellLoad()

If mcm.scum == true && (slsw_addictionIndicator.getvalue()) >= 4
	Utility.Wait(2)
	If Game.GetPlayer().GetWorldSpace() != Tamriel
		If Game.GetPlayer().GetCurrentLocation().Haskeyword(LoctypeInn) == True
			If InnDemands.isrunning() != true
				InnDemands.Start()
			endif
		elseIf Game.GetPlayer().IsInInterior() != true
			if scumQuest.isrunning() != true
				scumQuest.start()
			endif
		endif
	endif
endif
EndEvent

Function SleepItOff()

(Game.GetPlayer().RemoveSpell(slsw_bd_stage1))
(Game.GetPlayer().RemoveSpell(slsw_bd_stage2))
(Game.GetPlayer().RemoveSpell(slsw_bd_stage3))
(Game.GetPlayer().RemoveSpell(slsw_bd_stage4))
(Game.GetPlayer().RemoveSpell(slsw_bd_sideeffect))

(Game.GetPlayer().RemoveSpell(slsw_ddsk_1))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_2))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_3))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_4))

(Game.GetPlayer().RemoveSpell(slsw_ddsk_kj_1))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_kj_2))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_kj_3))
(Game.GetPlayer().RemoveSpell(slsw_ddsk_kj_4))

(Game.GetPlayer().RemoveSpell(slsw_ef_stage1))
(Game.GetPlayer().RemoveSpell(slsw_ef_stage2))
(Game.GetPlayer().RemoveSpell(slsw_ef_stage3))
(Game.GetPlayer().RemoveSpell(slsw_ef_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_1))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_2))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_3))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_4))

(Game.GetPlayer().RemoveSpell(slsw_leafskooma_kj_1))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_kj_2))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_kj_3))
(Game.GetPlayer().RemoveSpell(slsw_leafskooma_kj_4))
 
(Game.GetPlayer().RemoveSpell(slsw_mf_stage1))
(Game.GetPlayer().RemoveSpell(slsw_mf_stage2))
(Game.GetPlayer().RemoveSpell(slsw_mf_stage3))
(Game.GetPlayer().RemoveSpell(slsw_mf_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_mt_stage1))
(Game.GetPlayer().RemoveSpell(slsw_mt_stage2))
(Game.GetPlayer().RemoveSpell(slsw_mt_stage3))
(Game.GetPlayer().RemoveSpell(slsw_mt_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_op_stage1))
(Game.GetPlayer().RemoveSpell(slsw_op_stage2))
(Game.GetPlayer().RemoveSpell(slsw_op_stage3))
(Game.GetPlayer().RemoveSpell(slsw_op_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_skooma_1))
(Game.GetPlayer().RemoveSpell(slsw_skooma_2))
(Game.GetPlayer().RemoveSpell(slsw_skooma_3))
(Game.GetPlayer().RemoveSpell(slsw_skooma_4))
 
(Game.GetPlayer().RemoveSpell(slsw_skooma_kj_1))
(Game.GetPlayer().RemoveSpell(slsw_skooma_kj_2))
(Game.GetPlayer().RemoveSpell(slsw_skooma_kj_3))
(Game.GetPlayer().RemoveSpell(slsw_skooma_kj_4))
 
(Game.GetPlayer().RemoveSpell(slsw_tam_stage1))
(Game.GetPlayer().RemoveSpell(slsw_tam_stage2))
(Game.GetPlayer().RemoveSpell(slsw_tam_stage3))
(Game.GetPlayer().RemoveSpell(slsw_tam_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_tc_stage1))
(Game.GetPlayer().RemoveSpell(slsw_tc_stage2))
(Game.GetPlayer().RemoveSpell(slsw_tc_stage3))
(Game.GetPlayer().RemoveSpell(slsw_tc_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_td_stage1))
(Game.GetPlayer().RemoveSpell(slsw_td_stage2))
(Game.GetPlayer().RemoveSpell(slsw_td_stage3))
(Game.GetPlayer().RemoveSpell(slsw_td_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_tf_stage1))
(Game.GetPlayer().RemoveSpell(slsw_tf_stage2))
(Game.GetPlayer().RemoveSpell(slsw_tf_stage3))
(Game.GetPlayer().RemoveSpell(slsw_tf_stage4))
 
(Game.GetPlayer().RemoveSpell(slsw_tsb_stage1))
(Game.GetPlayer().RemoveSpell(slsw_tsb_stage2))
(Game.GetPlayer().RemoveSpell(slsw_tsb_stage3))
(Game.GetPlayer().RemoveSpell(slsw_tsb_stage4))
return
EndFunction