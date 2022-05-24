/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	Phone
}

class ADRP_OpenPhoneKey: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is opend")]
	private string _DisplayName;
		
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{	
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.Phone);
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