class ADRP_SpawnVehicleAction : ScriptedUserAction
{
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Vehicle To Spawn")]
	private ResourceName vehicleRessourceName;
	
	[Attribute("", UIWidgets.ResourceNamePicker, desc: "Vehicle Key")]
	private ResourceName keyRessourceName;
	
	[Attribute("", UIWidgets.Auto, desc: "Vehicle Spawn Position")]
	private vector spawnPoint;

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		if (!pUserEntity)
			return;
		
		// server only
		if (RplSession.Mode() == RplMode.Client)
			return;
		
		//Get the users inventory
		SCR_InventoryStorageManagerComponent inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		
		if (!inventoryManager)
			return;
		
		IEntity newVehicle = ADRP_SpawnPrefab.SpawnPrefab(pOwnerEntity, vehicleRessourceName, spawnPoint);
		
		if (!newVehicle)
			return;

		//Spawn the key
		IEntity newKey = ADRP_SpawnPrefab.SpawnPrefab(pOwnerEntity, keyRessourceName, spawnPoint);
		
		if (!newKey) {
			SCR_EntityHelper.DeleteEntityAndChildren(newVehicle);
			return;
		}
		
		ADRP_CarKeyComponent keyComponent = ADRP_CarKeyComponent.Cast(newKey.FindComponent(ADRP_CarKeyComponent));
		
		if (!newKey) {
			SCR_EntityHelper.DeleteEntityAndChildren(newVehicle);
			SCR_EntityHelper.DeleteEntityAndChildren(newKey);
			return;
		}
		
		//Tell the vehicle it has a key
		SCR_BaseLockComponent vehicleLock = SCR_BaseLockComponent.Cast(newVehicle.FindComponent(SCR_BaseLockComponent));
		
		if (!vehicleLock) {
			SCR_EntityHelper.DeleteEntityAndChildren(newVehicle);
			SCR_EntityHelper.DeleteEntityAndChildren(newKey);
			return;
		}
		
		//Set the vehicle to this vehicle
		keyComponent.m_LockableItem = vehicleLock;
		vehicleLock.m_KeyCreated = true;
		
		//Add the key to the users inventory
		bool isValid = inventoryManager.TryInsertItem(newKey);
		
		if (!isValid) {
			SCR_EntityHelper.DeleteEntityAndChildren(newVehicle);
			SCR_EntityHelper.DeleteEntityAndChildren(newKey);
			return;
		}

		SCR_HintManagerComponent.GetInstance().ShowCustomHint("Your vehicle is ready and locked.", "Vehicle", 5, false, EFieldManualEntryId.NONE, true);
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("Purchase UAZ");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		return true;
 	}	
}
