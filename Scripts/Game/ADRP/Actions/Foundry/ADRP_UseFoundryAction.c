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
		//Must check if another one is used before if so warn that the user is already using a foundry
		_foundryComponent.InitFoundry(pOwnerEntity);
		bool sucess = _foundryComponent.SetCurrentOwner(pUserEntity);
		if (sucess) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_FoundryDescriptionUse", "#A4D_FoundryTitle", 5.0, false, EFieldManualEntryId.NONE, true); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_FoundryDescriptionInUse", "#A4D_FoundryTitle", 5.0, false, EFieldManualEntryId.NONE, true); 
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_FoundryUseAction");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.AllowChangeOwner();
 	}
}