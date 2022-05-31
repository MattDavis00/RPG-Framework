modded class SCR_OpenVehicleStorageAction : SCR_InventoryAction
{
	
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
		SetCannotPerformReason("Locked");
		
		return false;
 	}
	
	
}