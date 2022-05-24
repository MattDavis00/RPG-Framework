/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : Advanced foundry system
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_ReleaseFoundryAction: ScriptedUserAction 
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
		_foundryComponent.SetFoundryActive(false);
		_foundryComponent.ReleaseFoundry();
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("The foundry no longer belongs to you.", "Foundry", 5.0 , true); 
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Release foundry");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{		
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.IsOwner(user);
 	}
}