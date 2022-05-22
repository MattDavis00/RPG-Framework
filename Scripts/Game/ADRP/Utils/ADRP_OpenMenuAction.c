modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	Garage
}

class ADRP_OpenMenuAction: ScriptedUserAction {

	[Attribute("", UIWidgets.EditBox, desc: "Display name of what is being gathered")]
	private string _DisplayName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Prefab what item is gathered")]
	private ResourceName _LayoutPrefab;
		
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{	
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.Garage);
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