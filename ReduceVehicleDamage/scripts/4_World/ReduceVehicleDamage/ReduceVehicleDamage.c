modded class CarScript 
{
	override void OnContact( string zoneName, vector localPos, IEntity other, Contact data )
	{
		bool addedGodMod = false;
		float dmg = data.Impulse * m_dmgContactCoef;
		float rvd_orgdmg = dmg;
		if ( GetGame().IsServer() && zoneName != "" && m_dmgContactCoef > 0 && data.Impulse > 0 )
		{	
		        float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().dmgModifier;
		        float rvd_mindmg = ReduceVehicleDamageSettings.Get().mindmg;
		        bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		        bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;
				
		        bool rvd_debug = ReduceVehicleDamageSettings.Get().debugLogs;
				if (rvd_mindmg < 150){ //since the default Min Damage is 150 want to make sure I don't cause issues
					rvd_mindmg = 150;
				}
			//if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Called CarScript OnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse); }

			if ( dmg < rvd_mindmg){
				if( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished CarScript OnContact - Damage is less than min - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse); }
				dmg = 50;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
				if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished CarScript OnContact - Engine is off - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse); }
				dmg = 50;
			}
			if (rvd_subtractmindmg)
			{
				dmg = dmg - rvd_mindmg;
				dmg = dmg * rvd_dmgModifier;
			}
			else
			{
				dmg = dmg * rvd_dmgModifier;
			}
			if (dmg < 1) 
			{
				if ( rvd_debug ){ Print("[ReduceVehicleDamage] Finished CarScript OnContact - Damage Less than one - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse); }
				dmg = 50;
			}
			data.Impulse = dmg / m_dmgContactCoef;
			//if ( rvd_debug && dmg > 150 ) { Print("[ReduceVehicleDamage] Finished CarScript OnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse); }
		}
		super.OnContact(zoneName, localPos, other, data);
        if ( GetGame().IsServer() && zoneName != "" && m_dmgContactCoef > 0 && data.Impulse > 0 && IsRuined() )
		{	
			float rvd_post_perventcarruined = ReduceVehicleDamageSettings.Get().perventCarRuined;
	        float post_dmg = data.Impulse * m_dmgContactCoef;
	        if ( post_dmg >= 750 && rvd_post_perventcarruined ){
				float fivePercent = GetMaxHealth() * 0.05;
				AddHealth( "", "", fivePercent );
			}
        }
		        
	}

	override void Explode( int damageType, string ammoType = "" )
	{
		if ( GetGame().IsServer() )
		{
			bool rvd_noexplodeifoff = ReduceVehicleDamageSettings.Get().noExplodeIfOff;
			if (!EngineIsOn() && rvd_noexplodeifoff && !IsRuined())
			{
				return;
			}
		}
		super.Explode(damageType, ammoType);
	}
}
