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
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_FoundryDescriptionStart", "#A4D_FoundryTitle", 5.0 , true); 
			//Faire partir de la fumé
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_FoundryDescriptionStartFailed", "#A4D_FoundryTitle", 5.0 , false); 
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_FoundryStartAction");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		if (!_foundryComponent)
			return false;
		
		return _foundryComponent.IsOwner(user) && !_foundryComponent.IsFoundryActive();
 	}
}