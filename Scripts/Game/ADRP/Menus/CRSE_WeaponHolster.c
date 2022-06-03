modded enum ChimeraMenuPreset: ScriptMenuPresetEnum
{
	PhoneMenu
}

class CRSE_WeaponHolster: SCR_InfoDisplay {
	private InputManager inputManager;
	private SCR_CharacterControllerComponent characterController;
	private IEntity player;

	
	void CRSE_WeaponHolster(IEntity owner) {
		this.player = owner;
	}
	
	void Init() {
		characterController = SCR_CharacterControllerComponent.Cast(player.FindComponent(SCR_CharacterControllerComponent));
		this.registerEventListener();
	}

    void holsterKeyPressed() {
		Print("!!!!! TEST !!!!!");
		MenuManager menuManager = GetGame().GetMenuManager();
		menuManager.OpenMenu(ChimeraMenuPreset.PhoneMenu);
    }
	
    void registerEventListener() {
        inputManager = GetGame().GetInputManager();
		
        if(!inputManager)
            return;
		
        inputManager.AddActionListener("OpenPhoneKey", EActionTrigger.DOWN, holsterKeyPressed);
    }
	
    void unregisterEventListener() {
        inputManager.RemoveActionListener("OpenPhoneKey", EActionTrigger.DOWN, holsterKeyPressed);
    }
}