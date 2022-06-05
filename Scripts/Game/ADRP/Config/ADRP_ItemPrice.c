//! Config template for XP rewards in Campaign
[BaseContainerProps()]
class ADRP_ItemPriceInfo
{
	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "ID of item", enums: ParamEnumArray.FromEnum(ItemsId))]
	protected ItemsId _itemID;

	[Attribute("#ADRP_UNDEFINIED", desc: "Name of this item")]
	protected string _name;

	[Attribute(uiwidget: UIWidgets.ResourceNamePicker, desc: "Prefab what item")]
	private ResourceName _itemPrefab;

	[Attribute("0", desc: "Buy Price")]
	protected int _buy;

	[Attribute("0", desc: "Sell Price")]
	protected int _sell;

	ItemsId GetItemID()
	{
		return _itemID;
	}

	string GetName()
	{
		return _name;
	}

	int GetBuy()
	{
		return _buy;
	}

	int GetSell()
	{
		return _sell;
	}

	ResourceName GetItemPrefab()
	{
		return _itemPrefab;
	}
};

//! All Campaign ranks are stored here along with important data
[BaseContainerProps(configRoot: true)]
class ADRP_ItemPriceList
{
	[Attribute(desc: "Items list.")]
	private ref array<ref ADRP_ItemPriceInfo> _itemList;

	protected static ref ADRP_ItemPriceList _instance;

	static ADRP_ItemPriceList GetInstance()
	{
		if (!_instance)
		{
			Resource containerConfig = BaseContainerTools.LoadContainer("{56292A706688DC9C}Configs/ADRP_ItemPrice.conf");
			_instance = ADRP_ItemPriceList.Cast(BaseContainerTools.CreateInstanceFromContainer(containerConfig.GetResource().ToBaseContainer()));
		}

		return _instance;
	}

	void GetItemsList(out notnull array<ref ADRP_ItemPriceInfo> itemList)
	{
		itemList = _itemList;
	}

	ADRP_ItemPriceInfo GetItemInfoFromID(ItemsId itemID)
	{
		if (!_itemList)
			return null;

		foreach (ref ADRP_ItemPriceInfo item : _itemList)
		{
			if (!item || item.GetItemID() != itemID)
				continue;

			return item;
			break;
		}

		return null;
	}
};

enum ItemsId
{
	ENERGY_DRINK,
	WATER,
	APPEL,
	PIZZA,
	WEED_PROCESSED,
	WEED_UNTREATED,
	COPPER_PROCESSED,
	COPPER_UNTREATED,
	IRON_PROCESSED,
	IRON_UNTREATED,
	SAND_UNTREATED,
	AXE,
	PICKAXE,
	SHOVEL,
	MAP,
	BINOCULAR,
	WATCH,
	COMPASS,
	LIGHT,
	BANDAGE
};

[ComponentEditorProps(category: "Game/ADRP/Items", description: "", color: "0 0 255 255")]
class ADRP_ItemPriceComponentClass: ScriptGameComponentClass
{
};

class ADRP_ItemPriceComponent: ScriptGameComponent
{
	[Attribute(defvalue: "0", uiwidget: UIWidgets.ComboBox, desc: "ID of item", enums: ParamEnumArray.FromEnum(ItemsId))]
	protected ItemsId _itemID;

	private ADRP_ItemPriceInfo _itemInfo;

	override void OnPostInit(IEntity owner)
	{
		_itemInfo = ADRP_ItemPriceList.GetInstance().GetItemInfoFromID(_itemID);
	}

	ItemsId GetItemID()
	{
		return _itemID;
	}

	ADRP_ItemPriceInfo GetItemInfo()
	{
		return _itemInfo;
	}
}
