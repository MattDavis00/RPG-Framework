[ComponentEditorProps(category: "Game/ADRP/BDD", description: "TOTO", color: "0 0 255 255")]
class ADRP_MoneyManagerClass: ScriptComponentClass
{};

class ADRP_MoneyManager: ScriptComponent
{
	// TODO : remove this for a call BDD
	private int _dataMoney = 0;		// Only server data set
	
	protected int _localMoney = 0;  // Client money
	
	//------------------------------------------------------------------------------------------------
	//! Update local money from server
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RPC_ADRP_CLIENT_MONEY_UpdateLocalMoney(int money)
	{
		if (money > 0)
			_localMoney = money;
		
		PrintString("Client New money : " + _localMoney);
		PrintString("Server New money : " + _dataMoney);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Send the update to the owner
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RPC_ADRP_SERVER_SendUpdate()
	{
		// TODO : Get Money from BDD_Money
		_dataMoney = _dataMoney + 1000;
		Rpc(RPC_ADRP_CLIENT_MONEY_UpdateLocalMoney, _dataMoney);

		PrintString("Client New money : " + _localMoney);
		PrintString("Server New money : " + _dataMoney);
	}
	
	//------------------------------------------------------------------------------------------------
	//! Get request update
	void RequestUpdate()
	{
		Rpc(RPC_ADRP_SERVER_SendUpdate)
	}
}