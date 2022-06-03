/*modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	PhoneMenu
}*/

class ADRP_OpenPhone: SCR_InfoDisplay {
	private InputManager inputManager;
	private SCR_CharacterControllerComponent characterController;
	private BaseWeaponManagerComponent weaponManager;
	private IEntity player;
	private BaseWeaponComponent lastWeapon;
	
	void CRSE_WeaponHolster(IEntity owner) {
		this.player = owner;
	}
	
	void Init() {
		
		inputManager.AddActionListener("OpenPhoneKey", EActionTrigger.UP, holsterKeyPressed);
		Print("Key registered succes");
		
	}

   void holsterKeyPressed() {
		/*Print("!!!!! TEST !!!!!");
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.PhoneMenu);*/
    }

}