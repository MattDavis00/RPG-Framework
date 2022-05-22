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
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		auto inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		inventoryManager.TrySpawnPrefabToStorage(m_GatherItemPrefab);
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Gather %1", m_GatherItemDisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
}