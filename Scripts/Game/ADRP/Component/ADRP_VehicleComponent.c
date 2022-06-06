class ADRP_VehicleComponentClass: GameComponentClass
{
};

class ADRP_VehicleComponent: GameComponent
{
	private IEntity _currentVehicle;
		
	bool AllowFlipVehicle()
	{
		vector ActualPosition[4];
		_currentVehicle.GetTransform(ActualPosition);
		vector angles = Math3D.MatrixToAngles(ActualPosition);
		Print("-------------------------------");
		Print(ActualPosition);
		Print(angles);
		Print("-------------------------------");
				
		return true;
	}

};