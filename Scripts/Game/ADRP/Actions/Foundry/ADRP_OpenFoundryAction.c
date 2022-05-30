/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : Advanced foundry system
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_OpenFoundryAction: ScriptedUserAction 
{
	private ADRP_FoundryComponent _foundryComponent;
	
	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		if (Replication.IsClient())
			return;
		
		_foundryComponent = ADRP_FoundryComponent.Cast(pOwnerEntity.FindComponent(ADRP_FoundryComponent));
		
		if (!_foundryComponent)
			Print("Foundry component not found", LogLevel.ERROR);
	}
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		//_foundryComponent.OpenInventory();
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_FoundryDescriptionOpen", "#A4D_FoundryTitle", 5.0 , true); 
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_FoundryOpenAction");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{		
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.IsOwner(user);
 	}
}