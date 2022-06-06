class ADRP_FoundryComponentClass: GameComponentClass
{
};

class ADRP_FoundryComponent: GameComponent
{
	private IEntity _currentOwner;
	private IEntity _foundry;
	private bool _isActive = false;
	private SCR_InventoryStorageManagerComponent _inventory;
	private float _maxDistance = 1000.0;
	
	override void _WB_OnInit(IEntity owner, inout vector mat[4], IEntitySource src) 
	{
		_foundry = owner;
		
		_inventory = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
		
		if (!_inventory)
			Print("Inventory component not found !", LogLevel.ERROR);
	}
	
	bool IsFoundryActive() 
	{
		return _isActive;
	}
	
	void SetFoundryActive(bool active)
	{
		if (Replication.IsClient())
			return;
		
		_isActive = active;
	}
	
	bool SetCurrentOwner(IEntity owner)
	{
		if (Replication.IsClient())
			return false;
		
		bool valide = AllowChangeOwner();
		
		#ifdef WORKBENCH
		Print("Current Owner : " + _currentOwner);
		#endif
		
		if (valide) 
			_currentOwner = owner;
		
		#ifdef WORKBENCH
		Print("New Owner : " + _currentOwner);
		#endif
		
		return valide;
	}
	
	bool AllowChangeOwner()
	{
		if (Replication.IsClient())
			return false;
		
		if (!_currentOwner)
			return true;
		
		if (!_foundry)
			return false;
		
		vector foundryPosition [4];
		vector ownerPosition [4];
		
		_foundry.GetTransform(foundryPosition);
		_currentOwner.GetTransform(ownerPosition);
		
		
		Print("--------------------------------");
		Print(_foundry);
		Print("--------------------------------");
		Print(foundryPosition);
		Print("--------------------------------");
		Print(_currentOwner);
		Print("--------------------------------");
		Print(ownerPosition);
		Print("--------------------------------");
		
		float distance = vector.Distance(foundryPosition,ownerPosition);
		
		return distance < _maxDistance;
	}
	
	bool IsOwner(IEntity owner) 
	{
		return owner == _currentOwner;	
	}
	
	void ReleaseFoundry() 
	{
		_currentOwner = null;
	}
	
	void OpenInventory() 
	{
		if (!_inventory)
		{
			Print ("No inventory available", LogLevel.ERROR);
			return;
		}
		
		_inventory.OpenInventory();
		
	}
	
	void InitFoundry(IEntity owner)
	{
		if (_foundry) 
			return;
		
		_foundry = owner;
		
		if (_inventory) 
			return;
		
		_inventory = SCR_InventoryStorageManagerComponent.Cast(owner.FindComponent(SCR_InventoryStorageManagerComponent));
		
		if (!_inventory)
			Print("Inventory component not found !", LogLevel.ERROR);
	}
	
	/* TODO 
	[RplRpc(RplChannel.Reliable,RplRcver.Server)]
	protected void RPC_ADRP_SERVER_USEFOUNDRY_SetOwner(IEntity owner)
	{
		if (!_foundryComponent) 
		{
			Print("Foundry component not found", LogLevel.ERROR);
			Rpc(RPC_ADRP_CLIENT_USEFOUNDRY_IsOwner, false);
			return;
		}
		
		bool sucess = _foundryComponent.SetCurrentOwner(pUserEntity);
		
		Rpc(RPC_ADRP_CLIENT_USEFOUNDRY_IsOwner, sucess);
	}
	
	protected void RPC_ADRP_CLIENT_USEFOUNDRY_IsOwner(bool sucess)
	{
		Print("Sucess : " + sucess);
		if (sucess) {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("You can use this foundry.", "Foundry", 5.0 , true); 
		} else {
			SCR_HintManagerComponent.GetInstance().ShowCustomHint("The foundry is already in use.", "Foundry", 5.0 , false); 
		}
		
	}
	*/
	
};