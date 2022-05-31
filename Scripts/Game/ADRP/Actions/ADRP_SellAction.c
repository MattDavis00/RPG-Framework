/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_SellAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being sell")]
	private string m_SellItemDisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is buy")]
	private ResourceName m_SellItemPrefab;
	
	[Attribute("", UIWidgets.EditBox, desc: "Price")]
	private int m_ItemSellPrice;
	
	private int _numberToSell = 1;
	private int _itemTotalPrice = 0;
	

	override void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent) 
	{
		//Doit compter le nombre qu'il en as sur lui pour tout vendre
		/*
		_numberToSell = compte le nombre dans l'inventaire.
		*/
				
		/*SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
			if (inventoryManager)
			{
				//Doit supprimer le nombre qu'il en vend
				//Quelque choses comme sa ? : inventoryManager.TryDeleteItem(m_SellItemDisplayName);
			}*/
		
		_itemTotalPrice = _numberToSell * m_ItemSellPrice;
	}
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (_numberToSell > 0)
		{
			SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
			if (inventoryManager)
			{
				//Doit supprimer le nombre qu'il en vend
				//inventoryManager.TryDeleteItem(m_SellItemPrefab);
			}
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_SellDescription " + _numberToSell + " " + m_SellItemDisplayName + " #A4D_For " + _itemTotalPrice + " #A4D_Currency", "#A4D_SellTitle", 5.0 ); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_NothingToSell", "#A4D_SellTitle", 5.0 );
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		
		if (_numberToSell > 0)
		{
			outName = string.Format("#A4D_SellAction %1 %2 #A4D_For %3 #A4D_Currency", _numberToSell, m_SellItemDisplayName, _itemTotalPrice);
			return true;
		} else {
			outName = string.Format("#A4D_SellActionNot %1 #A4D_ToSell", m_SellItemDisplayName);
			return true;
		}
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
}