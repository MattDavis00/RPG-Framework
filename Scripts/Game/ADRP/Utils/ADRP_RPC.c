/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

[ComponentEditorProps(category: "Game/ADRP/Utils", description: "", color: "0 0 255 255")]
class ADRP_RPCClass: ScriptComponentClass
{};

class ADRP_RPC: ScriptComponent
{
	
	protected static ADRP_RPC _instance;
	
	static ADRP_RPC GetInstance()
	{
		if (_instance)
			return _instance;
		
		GetGame().GetWorld().QueryEntitiesBySphere("0 0 0", 5, QueryEntitiesCallback);
		
		return null;	
	}
	
	protected static bool QueryEntitiesCallback(IEntity entity)
	{
		ADRP_RPC temp = ADRP_RPC.Cast(entity.FindComponent(ADRP_RPC));
		if (temp)
			_instance = temp;

		return true;
	}
}