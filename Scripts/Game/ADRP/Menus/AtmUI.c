/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class AtmUI: ChimeraMenuBase
{
	override void OnMenuOpen()
	{
		super.OnMenuOpen();
		Print("ATM Menu Open");
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
		
		if (w.GetName() == "Withdraw")
			Print("Withdraw Button Clicked");
		
		if (w.GetName() == "Deposit")
			Print("Deposit Button Clicked");
		
		if (w.GetName() == "Tansfert")
			Print("Tansfert Button Clicked");
		
		return true;
	}
}