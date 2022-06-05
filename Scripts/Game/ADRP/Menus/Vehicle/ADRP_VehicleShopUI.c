/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/
modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	VehicleDetail
}

class VehicleShopUI: ChimeraMenuBase
{
	override void OnMenuOpen()
	{
		super.OnMenuOpen();
		Print("Vahicle Shop Menu Open");
	}
	
	override void OnMenuClose()
	{
		super.OnMenuClose();
		Print("Menu Close");
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Print("clicked");
		if (w.GetName() == "Exit") 
			super.Close();
		
		if (w.GetName() == "Car1") 
		{
			MenuManager menuManager = GetGame().GetMenuManager();
			menuManager.OpenMenu(ChimeraMenuPreset.VehicleDetail);
		}
			
		return true;
	}
}