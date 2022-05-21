[ComponentEditorProps(category: "Game/ADRP/BDD", description: "TOTO", color: "0 0 255 255")]
class ADRP_BDD_PlayerPositionClass: ScriptComponentClass
{};

class ADRP_BDD_PlayerPosition : ScriptComponent
{

	private SCR_CharacterControllerComponent _localComponent;
	private ChimeraCharacter _localCharacter;

	// TODO REMOVE
	private vector _pos = {9675.97,14.3117,1553.91};
	private vector _rot = {153.601,0,-0};
	private float _scale = 1;
	private vector _aimRot = {144.526,-25.7246,0};

	//------------------------------------------------------------------------------------------------
	//! Send event for set player position

	// TODO : Remove Args
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RPC_ADRP_BDD_SERVER_SetPositionOfPlayer(vector pos, vector rot, float scale, vector aimRot)
	{

		// get api not work : https://feedback.bistudio.com/T164859
		RestCallback cbx1 = new CallRest;
		RestContext ctx = g_Game.GetRestApi().GetContext("http://feedback.bistudio.com");

		Print(g_Game.GetRestApi());

		Print(ctx);
		if (!ctx)
			Print("ERROR in API", LogLevel.FATAL);
		else if (ctx.Type() == RestContext)
			ctx.GET(cbx1, "getPosition.php");

		// send to owner new position
		Rpc(RPC_ADRP_BDD_CLIENT_SetPositionOfPlayer, pos, rot, scale, aimRot);
	}

	//------------------------------------------------------------------------------------------------
	//! Set Player position from server event
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RPC_ADRP_BDD_CLIENT_SetPositionOfPlayer(vector pos, vector rot, float scale, vector aimRot)
	{
		ChimeraCharacter character = GetCharater();

		if (!character)
			return;

		if (GetCharaterController().IsDead())
			return;

		// set new position
		character.SetOrigin(pos);
		character.SetYawPitchRoll(rot);
		character.SetScale(scale);
		GetCharaterController().SetAimingAngles(aimRot[0], aimRot[1]);
	}

	//------------------------------------------------------------------------------------------------
	//! Get CharaterController from Game.PlayerController
	private SCR_CharacterControllerComponent GetCharaterController()
	{
		if (_localComponent)
		return _localComponent;

		if (!GetGame() || !GetGame().GetPlayerController() || !GetGame().GetPlayerController().GetControlledEntity())
			return null;

		IEntity playerPrefab = GetGame().GetPlayerController().GetControlledEntity();

		SCR_CharacterControllerComponent controllerComponent = SCR_CharacterControllerComponent.Cast(
			playerPrefab.FindComponent(SCR_CharacterControllerComponent)
		);

		if (!controllerComponent)
			return null;

		_localComponent = controllerComponent;
		return controllerComponent;
	}

	//------------------------------------------------------------------------------------------------
	//! Get Charater from GetCharaterController()
	private ChimeraCharacter GetCharater()
	{
		if(_localCharacter)
			return _localCharacter;

		SCR_CharacterControllerComponent controllerComponent = GetCharaterController();

		if (!controllerComponent || !controllerComponent.GetCharacter())
			return null;

		_localCharacter = controllerComponent.GetCharacter();
		return controllerComponent.GetCharacter();
	}

	// TODO : Auto on start
	void test()
	{
		// TODO: Remove args
		Rpc(RPC_ADRP_BDD_SERVER_SetPositionOfPlayer, _pos, _rot, _scale, _aimRot);
	}
}

class CallRest: RestCallback {
	override void OnError( int errorCode )
	{
		Print(" !!! OnError() ");
	};

	override void OnSuccess( string data, int dataSize )
	{
		Print(" !!! OnSuccess() size=" + dataSize );
		if( dataSize > 0 )
			Print(data); // !!! NOTE: Print() will not output string longer than 1024b, check your dataSize !!!
	};
}
