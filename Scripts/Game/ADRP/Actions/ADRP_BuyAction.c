/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc :
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_BuyAction: ScriptedUserAction {

	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "ID of item", enums: ParamEnumArray.FromEnum(ItemsId))]
	protected ItemsId _itemID;

	private SCR_InventoryStorageManagerComponent _inventoryManager;
	private ADRP_ItemPriceInfo _itemInfo;

	private string _validMessage;
	private string _actionMessage;

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (!_inventoryManager)
			_inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));

		bool valid = _inventoryManager.TrySpawnPrefabToStorage(_itemInfo.GetItemPrefab());

		if (valid)
			SCR_HintManagerComponent.GetInstance().ShowCustomHint(_validMessage, "#A4D_BuyTitle", 5.0 );
	}

	override bool GetActionNameScript(out string outName)
	{
		outName = _actionMessage;
		return true;
	}

	override bool CanBePerformedScript(IEntity user)
 	{
		if (!_inventoryManager)
			_inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));

		if (!_itemInfo)
			SetItemInfo();

		if (!_validMessage && _itemInfo)
			_validMessage = string.Format("#A4D_BuyDescription %1 #A4D_For %2 #A4D_Currency", _itemInfo.GetName(), GetFloatPrice());

		if (!_actionMessage && _itemInfo)
			_actionMessage = string.Format("#A4D_BuyAction %1 #A4D_For %2 #A4D_Currency", _itemInfo.GetName(), GetFloatPrice());

		return true;
 	}

	private void SetItemInfo()
	{
		ADRP_ItemPriceList itemPriceList = ADRP_ItemPriceList.GetInstance();

		if (!itemPriceList)
			return;

		array<ref ADRP_ItemPriceInfo> itemList = new array<ref ADRP_ItemPriceInfo>();
		itemPriceList.GetItemsList(itemList);

		foreach (ref ADRP_ItemPriceInfo item : itemList)
		{
			if (!item || item.GetItemID() != _itemID)
				continue;

			_itemInfo = item;
			break;
		}
	}

	private float GetFloatPrice()
	{
		float price = _itemInfo.GetSell();
		price = price / 100;
		return price;
	}
}
