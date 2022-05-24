/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : Advanced foundry system
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_UseFoundryAction: ScriptedUserAction 
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
		_foundryComponent.InitFoundry(pOwnerEntity);
		bool sucess = _foundryComponent.SetCurrentOwner(pUserEntity);
		if (sucess) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("You can use this foundry.", "Foundry", 5.0 , true); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("The foundry is already in use.", "Foundry", 5.0 , false); 
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Use foundry");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.AllowChangeOwner();
 	}
}