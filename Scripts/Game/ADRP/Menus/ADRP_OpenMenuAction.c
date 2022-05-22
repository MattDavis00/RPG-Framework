/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	Garage,
	AdminMenu,
	Atm,
	Clothing,
	PlayerInteraction,
	VehicleShop
}

class ADRP_OpenMenuAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is opend")]
	private string _DisplayName;
	
	[Attribute("", UIWidgets.EditBox, desc: "The Class UI in OpenMenuAction you want to call")]
	private string _UI_Class;
	
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{	
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.Garage);
		Print(_UI_Class);
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Open %1", _DisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
} 