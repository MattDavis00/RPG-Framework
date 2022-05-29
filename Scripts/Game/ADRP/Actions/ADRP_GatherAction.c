/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_GatherAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being gathered")]
	private string m_GatherItemDisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is gathered")]
	private ResourceName m_GatherItemPrefab;
	
	private int _numberGathered = 10;
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{

		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if (inventoryManager) 
			inventoryManager.TrySpawnPrefabToStorage(m_GatherItemPrefab);
		
		/*while (_numberGathered != 0)
		{
			Print ("test: " + _numberGathered);
			_numberGathered - 1;
		}*/
		
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_GatherDecription " + _numberGathered + " " + m_GatherItemDisplayName, "#A4D_GatherTitle", 5.0 ); 
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_GatherAction %1", m_GatherItemDisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
}