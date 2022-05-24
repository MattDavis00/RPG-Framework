class ADRP_MapFilter : SCR_MapUIBaseComponent
{
	protected Widget filter_widget;
	
	override void OnMapOpen(MapConfiguration config)
	{
		super.OnMapOpen(config);
		
		if (filter_widget)
		{
			return;
		}
		
		filter_widget = GetGame().GetWorkspace().CreateWidgets("{3513CA0C0C83D2E3}UI/layouts/Menu/phone/Home.layout");
		Print("Phone Open");
	}
}