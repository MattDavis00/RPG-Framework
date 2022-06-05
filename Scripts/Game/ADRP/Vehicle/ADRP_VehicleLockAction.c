class ADRP_VehicleLockAction : ScriptedUserAction
{
	
	
	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		
		
		//Get the vehicles locking class
		auto vehicleLock = SCR_BaseLockComponent.Cast(pOwnerEntity.FindComponent(SCR_BaseLockComponent));
		
		//Swap islocked
		vehicleLock.m_IsLocked = !vehicleLock.m_IsLocked;
		
		//Hints
		if (vehicleLock.m_IsLocked) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_VehicleLocked", "#A4D_Vehicle", 5.0, false, EFieldManualEntryId.NONE, true);
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("#A4D_VehicleUnlocked", "#A4D_Vehicle", 5.0, false, EFieldManualEntryId.NONE, true);
		};
	}
	
	override bool GetActionNameScript(out string outName)
	{
		outName = string.Format("#A4D_VehicleLockUnlock #A4D_Vehicle");
		return true;
	}
	
	override bool CanBePerformedScript(IEntity user)
 	{
		//Get the users inventory
		auto inventoryManager = SCR_InventoryStorageManagerComponent.Cast(user.FindComponent(SCR_InventoryStorageManagerComponent));
		
		//Get the users IEntity
		array<IEntity> inventoryItems = new array<IEntity>();
		inventoryManager.GetItems(inventoryItems);
		
		
		//Loop through items
		foreach (IEntity item : inventoryItems)
		{
			
			//Read the inventory item
			InventoryItemComponent pInvComp = InventoryItemComponent.Cast(item.FindComponent(InventoryItemComponent));
			if (pInvComp)
			{
				
				//Make sure there is item attributes
				ItemAttributeCollection attribs = pInvComp.GetAttributes();
				if( !attribs )
					break;
			
				
				//Get the keys key component
				auto keyComponent = ADRP_CarKeyComponent.Cast(item.FindComponent(ADRP_CarKeyComponent));
				
				//Check if the key is valid
				if (keyComponent) 
					if (keyComponent.m_LockableItem == SCR_BaseLockComponent.Cast(this.GetOwner().FindComponent(SCR_BaseLockComponent)))
							return true;
			}
		}
		
		//Set the cant be feformed reason
		SetCannotPerformReason("Missing Key");
		
		return false;
 	}
	
	
}
