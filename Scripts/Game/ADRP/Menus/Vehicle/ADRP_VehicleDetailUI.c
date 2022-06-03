/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/
class VehicleDetailUI: ChimeraMenuBase
{
	override void OnMenuOpen()
	{
		super.OnMenuOpen();
		Print("Vehicle Detail Open");
	}
	
	override void OnMenuClose()
	{
		super.OnMenuClose();
		Print("Menu Close");
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Print("clicked");
		
		if (w.GetName() == "Buy") 
		{
			Print("Buy");
			ADRP_BuyVehicleButton.test();
			
		}
			
		if (w.GetName() == "Exit") 
		{
			super.Close();
		}
		
		return true;
	}
}