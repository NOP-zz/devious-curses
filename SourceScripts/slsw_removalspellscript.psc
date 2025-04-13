Scriptname slsw_RemovalSpellScript extends activemagiceffect  

ImageSpaceModifier property slsw_tam_ISM auto
ImageSpaceModifier property slsw_tamlight_ISM auto
ImageSpaceModifier property slsw_tc_ism auto
ImageSpaceModifier property slsw_vp_ism auto
ImageSpaceModifier property slsw_vplight_ism auto
ImageSpaceModifier property slsw_mf_ism auto
ImageSpaceModifier property slsw_mflight_ism auto
ImageSpaceModifier property slsw_bd auto
ImageSpaceModifier property slsw_ef_ism auto
ImageSpaceModifier property slsw_mt_ism auto
ImageSpaceModifier property slsw_roa_ism auto
ImageSpaceModifier property slsw_sk_ism auto
ImageSpaceModifier property slsw_td auto
ImageSpaceModifier property slsw_tf_ism auto

Event OnEffectStart(Actor akTarget, Actor akCaster)
slsw_tam_ISM.Remove()
slsw_tamlight_ISM.Remove()
slsw_tc_ism.Remove()
slsw_vp_ism.Remove()
slsw_vplight_ism.Remove()
slsw_mf_ism.Remove()
slsw_mflight_ism.Remove()
slsw_bd.Remove()
slsw_ef_ism.Remove()
slsw_mt_ism.Remove()
slsw_roa_ism.Remove()
slsw_sk_ism.Remove()
slsw_td.Remove()
slsw_tf_ism.Remove()

EndEvent