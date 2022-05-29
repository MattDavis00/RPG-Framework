/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_BuyAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being buy")]
	private string m_BuyItemDisplayName;
	
	[Attribute("", UIWidgets.EditBox, desc: "Price")]
	private int m_ItemBuyPrice;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is buy")]
	private ResourceName m_BuyItemPrefab;
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		if (inventoryManager)
			inventoryManager.TrySpawnPrefabToStorage(m_BuyItemPrefab);
		
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_BuyDescription " + m_BuyItemDisplayName + " #A4D_For " + m_ItemBuyPrice + " #A4D_Currency", "#A4D_BuyTitle", 5.0 ); 
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_BuyAction %1 #A4D_For %2 #A4D_Currency", m_BuyItemDisplayName, m_ItemBuyPrice);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
}