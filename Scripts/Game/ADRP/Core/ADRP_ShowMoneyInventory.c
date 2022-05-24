/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : Show money on inventory
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_ShowMoneyInventory : SCR_InventoryMenuUI
{
	void OpenInventory()
	{
		GetGame().GetWorkspace().CreateWidgets("{5968FAE6F3EC3B1D}UI/layouts/GPS/PlayerMapIndicator.layout");
		Print("Inventory Open");
	}
}