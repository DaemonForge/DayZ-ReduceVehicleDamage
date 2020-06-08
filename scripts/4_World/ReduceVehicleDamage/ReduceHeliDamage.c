modded class ExpansionHelicopterScript
{
	override void EOnContact( IEntity other, Contact extra ) 
	{
		float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().helidmgModifier;
		float rvd_mindmg = ReduceVehicleDamageSettings.Get().helimindmg;
		bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;

		if ( IsMissionHost())
		{
			if(ReduceVehicleDamageSettings.Get().debugLogs){
				Print("[ReduceVehicleDamage] Called ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse);
			}
			float dmg = extra.Impulse * m_dmgContactCoef;
			float rvd_orgdmg = dmg;
			if ( dmg < rvd_mindmg){
				if(ReduceVehicleDamageSettings.Get().debugLogs && dmg > 100){
					Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than Min Damage - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse);
				}
				return;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
				if(ReduceVehicleDamageSettings.Get().debugLogs){
					Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Engine is off - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse);
				}
				return;
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
				if(ReduceVehicleDamageSettings.Get().debugLogs){
					Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than one - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse);
				}
				return;
			}
			extra.Impulse = dmg / m_dmgContactCoef;
			if(ReduceVehicleDamageSettings.Get().debugLogs){
				Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse);
			}
		}
		
		super.EOnContact( other, extra);
	}
}