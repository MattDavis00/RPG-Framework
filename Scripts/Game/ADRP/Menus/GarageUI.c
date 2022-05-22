/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class GarageUI: ChimeraMenuBase
{
	override void OnMenuOpen()
	{
		super.OnMenuOpen();
		Print("Garage Menu Open");
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
		
		return true;
	}
}