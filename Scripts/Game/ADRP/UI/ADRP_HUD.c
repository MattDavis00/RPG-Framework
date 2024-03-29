/*--------------------------------------------------------------------------------------------------------------------------------------/
|
|	Author : TheSam
|	Desc : 
|
/--------------------------------------------------------------------------------------------------------------------------------------*/

class ADRP_HUD: ScriptedWidgetComponent
{

    //References
    protected ProgressBarWidget _progress;

    private int curentLife = 0;
    private int curentHunger = 0;
    private int curentThirs = 0;

    private SCR_CharacterDamageManagerComponent _charDamageManager;

    //======================== UPDATE HUD ===================================\\
    protected void OnHUDUpdate()
    {
        if (_progress.GetName() == "LifeBar")
		{
			#ifdef WORKBENCH
        		Print("Curent Life : " + curentLife);
        	#endif
			_progress.SetCurrent(curentLife);
		}
    }

    //======================== ATTACH/DEATTACH HANDLER ========================\\
    //On Init
    override void HandlerAttached(Widget w)
    {
        _progress = ProgressBarWidget.Cast(w);

        //Add update each second for system clock
        if (_progress)
        {
            if (_progress.GetName() == "LifeBar")
            {
                _charDamageManager = SCR_CharacterDamageManagerComponent.Cast(GetGame().GetPlayerController().GetControlledEntity().FindComponent(SCR_CharacterDamageManagerComponent));
                if (!_charDamageManager)
                {
                    Print("No Character Damage Manager Component found",
                      LogLevel.ERROR);
                    return ;
                }
                _charDamageManager.GetOnDamageStateChanged().Insert(OnDamageStateChanged);
            }
        }
        else
        {
            Print("System " + w.GetName() + " not attached to Progress Bar Widget!", LogLevel.ERROR);
        }

        // OnHUDUpdate();
        // GetGame().GetCallqueue().CallLater(OnHUDUpdate, 500, true);
    }


    //On Destroy
    override void HandlerDeattached(Widget w)
    {
        //Remove every second update System Clock
        if (_progress)
        {
            GetGame().GetCallqueue().Remove(OnHUDUpdate);
        }

        if (_charDamageManager)
          _charDamageManager.GetOnDamageStateChanged().Remove(OnDamageStateChanged);

    }

    void OnDamageStateChanged(EDamageState state)
    {
        curentLife = Math.Floor(_charDamageManager.GetHealth());
        OnHUDUpdate();
    }

}
