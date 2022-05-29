class ADRP_FlipAction: ScriptedUserAction
{
	private ADRP_VehicleComponent _vehicleComponent;
	
	ActionsManagerComponent m_cActionsManagerComponent = null;
	Vehicle m_eVehicle = null;
	
	override event void Init(IEntity pOwnerEntity, GenericComponent pManagerComponent)
	{
		m_cActionsManagerComponent = ActionsManagerComponent.Cast(pManagerComponent);
		m_eVehicle = Vehicle.Cast(pOwnerEntity);
	}

	// Gets called when the action is complete (after the 5sec wait)
	override event void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		BaseWorld world = GetGame().GetWorld();

		if (!world || !m_eVehicle)
			return;
		
		if (m_eVehicle.IsOccupied()) return;
		
		// Get the current transform (position) of the vehicle
		vector transform[4];
		pOwnerEntity.GetTransform(transform);
		Print(transform);
		
		//--- Reset pitch and roll, but preserve yaw
		vector angles = Math3D.MatrixToAngles(transform);
		Print(angles);
		Math3D.AnglesToMatrix(Vector(angles[0], 0, 0), transform);
		
		// Teleport the vehicle 0.5 units in the air
		transform[3][1] = transform[3][1]+0.5;
		
		// Apply new transform
		pOwnerEntity.SetTransform(transform);

		// Apply slight down force to make it kick in physics wise
		pOwnerEntity.GetPhysics().ApplyImpulse("0 -1 0");
	}
	
	override event bool CanBeShownScript(IEntity user)
	{
		if (!m_eVehicle) {
			return false;
		}
		
		return !m_eVehicle.IsOccupied();
	}
	/* Besoin de sam pour continuer
	override bool CanBePerformedScript(IEntity user)
 	{
		return _vehicleComponent.AllowFlipVehicle();
 	}*/
	
}