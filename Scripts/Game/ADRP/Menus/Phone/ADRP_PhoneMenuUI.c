/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/
modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	SmsPhoneMenu
}

class PhoneMenuUI: ChimeraMenuBase
{
	override void OnMenuOpen()
	{
		super.OnMenuOpen();
		Print("Phone Menu Open");
	}
	
	override void OnMenuClose()
	{
		super.OnMenuClose();
		Print("Menu Close");
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		Print("clicked");
		
		if (w.GetName() == "App_x0_y0")  
		{
			MenuManager menuManager = GetGame().GetMenuManager();
			menuManager.OpenMenu(ChimeraMenuPreset.SmsPhoneMenu);
		}
		
		if (w.GetName() == "App_x0_y1")  
		{
			Print("Contact");
		}
		
		if (w.GetName() == "App_x0_y2")  
		{
			Print("Key");
		}
		
		if (w.GetName() == "App_x0_y3")  
		{
			Print("bourse");
		}
		
		if (w.GetName() == "App_x1_y0")  
		{
			Print("Bank");
		}
		
		if (w.GetName() == "App_x1_y1")  
		{
			Print("XP");
		}
		
		if (w.GetName() == "App_x1_y2")  
		{
			Print("Group");
		}
		
		if (w.GetName() == "App_x1_y3")  
		{
			Print("Not used");
		}
				
		if (w.GetName() == "App_x2_y0")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x2_y1")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x2_y2")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x2_y3")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x3_y0")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x3_y1")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x3_y2")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x3_y3")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x4_y0")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x4_y1")  
		{
			Print("Not used");
		}
		
		if (w.GetName() == "App_x4_y2")  
		{
			Print("Interpol");
		}
		
		if (w.GetName() == "App_x4_y3")  
		{
			Print("Settings");
		}
		
			
		if (w.GetName() == "Exit") 
			super.Close();
		
		return true;
	}
}