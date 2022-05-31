class ADRP_SpawnVehicleAction : ScriptedUserAction
{
	[Attribute("", UIWidgets.EditBox, desc: "Vehicle To Spawn")]
	private ResourceName m_Vehicle;
	
	[Attribute("", UIWidgets.EditBox, desc: "Vehicle Key")]
	private ResourceName m_Key;
	
	[Attribute("", UIWidgets.EditBox, desc: "Vehicle Spawn Position")]
	private vector m_SpawnPosition;
	
	
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		
		//Spawn the vehicle
		auto newVehicle = ADRP_VehicleSpawnEntity.SpawnEntityPrefab(m_Vehicle, m_SpawnPosition);

		//Get the users inventory
		auto inventoryManager = SCR_InventoryStorageManagerComponent.Cast(pUserEntity.FindComponent(SCR_InventoryStorageManagerComponent));
		
		//Spawn the key
		auto newKey = GetGame().SpawnEntityPrefab(Resource.Load(m_Key));
			
		auto cmpt = newKey.FindComponent(ADRP_CarKeyComponent);
			
		//Get the new keys key component
		auto keyComponent = ADRP_CarKeyComponent.Cast(cmpt);
			
		//Set the vehicle to this vehicle
		keyComponent.m_LockableItem = SCR_BaseLockComponent.Cast(newVehicle.FindComponent(SCR_BaseLockComponent));;
			
		//Add the key to the users inventory
		inventoryManager.TryInsertItem(newKey);
		
		//Tell the vehicle it has a key
		auto vehicleLock = SCR_BaseLockComponent.Cast(newVehicle.FindComponent(SCR_BaseLockComponent));
		vehicleLock.m_KeyCreated = true;
		
		SCR_HintManagerComponent.GetInstance().ShowCustomHint("Your vehicle is ready and locked.", "Vehicle", 3);
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
