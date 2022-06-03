/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_SellAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being sell")]
	private string _sellItemDisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is buy")]
	private ResourceName _sellItemPrefab;
	
	[Attribute("", UIWidgets.EditBox, desc: "Price")]
	private int _itemSellPrice;
	
	private int _numberToSell = 1;
	private int _itemTotalPrice = 0;
	
	private string _itemsName;
	
	private SCR_InventoryStorageManagerComponent _inventoryManager;
	
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
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_SellDescription " + _numberToSell + " " + _sellItemDisplayName + " #A4D_For " + _itemTotalPrice + " #A4D_Currency", "#A4D_SellTitle", 5.0 ); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_NothingToSell", "#A4D_SellTitle", 5.0 );
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		
		if (_numberToSell > 0)
		{
			outName = string.Format("#A4D_SellAction %1 %2 #A4D_For %3 #A4D_Currency", _numberToSell, _sellItemDisplayName, _itemTotalPrice);
			return true;
		} else {
			outName = string.Format("#A4D_SellActionNot %1 #A4D_ToSell", _sellItemDisplayName);
			return true;
		}
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{	
		if(!ADRP_RPC.GetInstance())
			return false;
		
		if (!_inventoryManager)
			_inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		
		if (!_itemsName)
		{
			ADRP_RPC.GetInstance().Rpc(RPC_ADRP_SERVER_SellAction_SetItemName, user);
			return false;
		}
			
		array<IEntity> temp = new array<IEntity>();

		_inventoryManager.GetItems(temp);
		_numberToSell = 0;
		_itemTotalPrice = 0;
			
		foreach (IEntity currentElement : temp)
		{
			InventoryItemComponent pInvComp = InventoryItemComponent.Cast(currentElement.FindComponent(InventoryItemComponent));
			if (pInvComp)
			{

				ItemAttributeCollection attribs = pInvComp.GetAttributes();
				if(!attribs)
					break;
				
				if (attribs.GetUIInfo().GetName() == _itemsName)
					_numberToSell = _numberToSell + 1;
			}
		}

		if(_numberToSell > 0)
			_itemTotalPrice = _numberToSell * _itemSellPrice;
		
		return true;
 	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RPC_ADRP_CLIENT_SellAction_UpdateItemName(string data)
	{
		_itemsName = data;
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RPC_ADRP_SERVER_SellAction_SetItemName(IEntity user)
	{
		// server only
		if (RplSession.Mode() == RplMode.Client || !ADRP_RPC.GetInstance())
			return;
		
		// If the item name is already defined
		if (_itemsName)
			ADRP_RPC.GetInstance().Rpc(RPC_ADRP_CLIENT_SellAction_UpdateItemName, _itemsName);
		
		IEntity items = ADRP_SpawnPrefab.SpawnPrefab(user, _sellItemPrefab, "0 0 0");
		if (!items) 
			ADRP_RPC.GetInstance().Rpc(RPC_ADRP_CLIENT_SellAction_UpdateItemName, "");

		InventoryItemComponent pInvComp = InventoryItemComponent.Cast(items.FindComponent(InventoryItemComponent));
		if (!pInvComp)
			ADRP_RPC.GetInstance().Rpc(RPC_ADRP_CLIENT_SellAction_UpdateItemName, "");

		ItemAttributeCollection attribs = pInvComp.GetAttributes();
		if(attribs)
			_itemsName = attribs.GetUIInfo().GetName();

		SCR_EntityHelper.DeleteEntityAndChildren(items);

		if(_itemsName && _itemsName != "")
			ADRP_RPC.GetInstance().Rpc(RPC_ADRP_CLIENT_SellAction_UpdateItemName, _itemsName);
	}
}