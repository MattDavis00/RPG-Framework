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
	VehicleShop,
	PhoneMenu
}

class ADRP_OpenMenuAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is opend")]
	private string _DisplayName;
	
	[Attribute("", UIWidgets.ComboBox, desc: "The Class UI in OpenMenuAction you want to call", "", ParamEnumArray.FromEnum(ChimeraMenuPreset))]
	private ChimeraMenuPreset _UI_Class;
	
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{	
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(_UI_Class);
		Print(_UI_Class);
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_Open %1", _DisplayName);
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}
} 