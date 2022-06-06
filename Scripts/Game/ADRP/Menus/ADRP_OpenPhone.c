/*modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	PhoneMenu
}*/

class ADRP_OpenPhone: SCR_InfoDisplay {
	private InputManager inputManager;
	
	void Init() {
		
		inputManager.AddActionListener("OpenPhoneKey", EActionTrigger.UP, PhoneKeyPressed);
		Print("Key registered succes");
		
	}

   void PhoneKeyPressed() {
		/*Print("!!!!! TEST !!!!!");
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.PhoneMenu);*/
    }

}