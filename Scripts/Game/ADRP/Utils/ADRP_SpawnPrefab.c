/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : Zomblard & TheSam
|	Desc : SpawnPrefab
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_SpawnPrefab
{
	static IEntity SpawnPrefab(IEntity player, ResourceName prefabRessourceName, vector spawnPoint)
	{
		// server only
		if (RplSession.Mode() == RplMode.Client)
			return null;
		
		if (!player)
			return null;
		
		ArmaReforgerScripted game = GetGame();
		if (!game)
			return null;
		
		if (!game.InPlayMode())
			return null;

		Resource resource = Resource.Load(prefabRessourceName);
		if (!resource)
			return null;
		
		ref EntitySpawnParams params = new EntitySpawnParams();
		params.TransformMode = ETransformMode.WORLD;
		Math3D.AnglesToMatrix("0 0 0", params.Transform);
		params.Transform[3] = spawnPoint;
		
		return game.SpawnEntityPrefab(resource, player.GetWorld(), params);
	}
}