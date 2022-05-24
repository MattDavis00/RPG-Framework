/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : Advanced foundry system
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_StartFoundryAction: ScriptedUserAction 
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
		_foundryComponent.SetFoundryActive(true);
		bool sucess = _foundryComponent.IsActive();
		if (sucess) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("The foundry is on the way do not open it while it is running.", "Foundry", 5.0 , true); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("Foundry failed to start.", "Foundry", 5.0 , false); 
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Start foundry");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.IsOwner(user) && !_foundryComponent.IsFoundryActive();
 	}
}