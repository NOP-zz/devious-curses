Scriptname slsw_bd_sideefectscript extends activemagiceffect  
SPELL Property slsw_bd_sideeffect  auto

event onEffectFinish(actor akTarget, actor akCaster)
	slsw_bd_sideeffect.Cast(Game.getPlayer(), Game.getPlayer())
endEvent