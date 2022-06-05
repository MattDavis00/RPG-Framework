/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_SellAction: ScriptedUserAction 
{

	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "ID of item", enums: ParamEnumArray.FromEnum(ItemsId))]
	protected ItemsId _itemID;

	private SCR_InventoryStorageManagerComponent _inventoryManager;
	private ADRP_ItemPriceInfo _itemInfo;

	private int _numberToSell = 0;
	private int _itemTotalPrice = 0;
	
	private ref array<IEntity> _prefabsItem = new array<IEntity>();
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (!_inventoryManager || !pUserEntity)
			return;
		
		if (_numberToSell > 0 && _prefabsItem.Count() > 0)
		{
			foreach (IEntity currentElement : _prefabsItem)
			{
				_inventoryManager.TryDeleteItem(currentElement);
			}

			string message = string.Format("#A4D_SellDescription %1 %2 #A4D_For %3 #A4D_Currency", _numberToSell, _itemInfo.GetName(), GetFloatPriceForAll());
			SCR_HintManagerComponent.GetInstance().ShowCustomHint(message, "#A4D_SellTitle", 5.0, false, EFieldManualEntryId.NONE, true); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_NothingToSell", "#A4D_SellTitle", 5.0, false, EFieldManualEntryId.NONE, true);
		}
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = "ERROR !!";

		if (!_itemInfo)
			return false;

		if (_numberToSell > 0)
		{
			outName = string.Format("#A4D_SellAction %1 %2 #A4D_For %3 #A4D_Currency", _numberToSell, _itemInfo.GetName(), GetFloatPriceForAll());
		} else {
			outName = string.Format("#A4D_SellActionNot %1 #A4D_ToSell", _itemInfo.GetName());
		}
		return true;
	}

	override bool CanBePerformedScript(IEntity user)
 	{	
		if (!_inventoryManager)
			_inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));

		if (!_inventoryManager)
			return false;
		
		if (!_itemInfo)
			SetItemInfo();
		
		// If the variable definition did not work
		if (!_itemInfo || !_inventoryManager)
			return false;

		_itemTotalPrice = 0;
		_numberToSell = 0;
		_prefabsItem.Clear();

		array<IEntity> temp = new array<IEntity>();
		_inventoryManager.GetItems(temp);

		foreach (IEntity currentElement : temp)
		{
			ADRP_ItemPriceComponent itemComponent = ADRP_ItemPriceComponent.Cast(currentElement.FindComponent(ADRP_ItemPriceComponent));			
			if (!itemComponent || itemComponent.GetItemID() != _itemID)
				continue;
			
			_numberToSell = _numberToSell + 1;
			_prefabsItem.Insert(currentElement);
		}

		if(_numberToSell > 0)
			_itemTotalPrice = _numberToSell * _itemInfo.GetSell();

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
	
	private float GetFloatPriceForAll()
	{
		float price = GetFloatPrice();
		price = price * _numberToSell;
		return price;
	}
}