modded class SCR_BaseLockComponent : ScriptComponent {
	
	//Is the vehicle locked?
	bool m_IsLocked = true;
	
	//Has a key been created for this vehicle?
	bool m_KeyCreated;
	
	override bool IsLocked(IEntity user, BaseCompartmentSlot compartmentSlot)
	{
		
		//Call base
		if (compartmentSlot)
			if (super.IsLocked(user, compartmentSlot))
				return true;
		
		//Dont lock vehicles without keys
		if (!m_KeyCreated)
			return false;
		
		//If the vehicle is unlocked than anyone can enter
		if (!m_IsLocked)
			return false;
		
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
							return false;
			}
		}
		
		return true;
	}
	
	override LocalizedString GetCannotPerformReason(IEntity user)
	{
		return "Locked";
	}
}