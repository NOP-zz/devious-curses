Scriptname slsw_ID_death extends ReferenceAlias  

Event OnHit(ObjectReference akAggressor, Form akSource, Projectile akProjectile, bool abPowerAttack, bool abSneakAttack, bool abBashAttack, bool abHitBlocked)
If akAggressor == Game.getPlayer()
	self.getOwningQuest().stop()
endif
endevent

Event OnDeath(Actor akKiller)
self.getOwningQuest().stop()
endevent