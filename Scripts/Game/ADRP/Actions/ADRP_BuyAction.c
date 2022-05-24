/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_BuyAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being buy")]
	private string m_BuyItemDisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is buy")]
	private ResourceName m_BuyItemPrefab;
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if (inventoryManager)
			inventoryManager.TrySpawnPrefabToStorage(m_BuyItemPrefab);
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Buy %1", m_BuyItemDisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
}