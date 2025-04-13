Scriptname SLSW_PPClient extends ReferenceAlias  

ReferenceAlias Property Alias_Client Auto
ObjectReference Property COCmarker auto

Event OnDeath(Actor akKiller)
RegisterForSingleUpdate(1)
endEvent

Event OnUpdate()
If Game.GetPlayer().HasLOS(Alias_Client.GetRef() as actor) != true
	(Alias_Client.GetRef() as actor).MoveTo(COCmarker)
	getOwningQuest().reset()
	getOwningQuest().setStage(10)
else
	RegisterForSingleUpdate(1)
endif
endEvent