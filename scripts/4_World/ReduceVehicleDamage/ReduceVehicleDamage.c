modded class CarScript 
{
	override void OnContact( string zoneName, vector localPos, IEntity other, Contact data )
	{
		float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().dmgModifier;
		float rvd_mindmg = ReduceVehicleDamageSettings.Get().mindmg;
		bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;

		if ( GetGame().IsServer() && zoneName != "" && m_dmgContactCoef > 0 )
		{		
			if(ReduceVehicleDamageSettings.Get().debugLogs){
				Print("[ReduceVehicleDamage] Called CarScript OnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse);
			}
			float dmg = data.Impulse * m_dmgContactCoef;
			float rvd_orgdmg = dmg;
			if ( dmg < rvd_mindmg){
				if(ReduceVehicleDamageSettings.Get().debugLogs && dmg > 100){
					Print("[ReduceVehicleDamage] Finished CarScript OnContact - Damage is less than min - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse);
				}
				return;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
				if(ReduceVehicleDamageSettings.Get().debugLogs){
					Print("[ReduceVehicleDamage] Finished CarScript OnContact - Engine is off - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse);
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
					Print("[ReduceVehicleDamage] Finished CarScript OnContact - Damage Less than one - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse);
				}
				return;
			}
			data.Impulse = dmg / m_dmgContactCoef;
			if(ReduceVehicleDamageSettings.Get().debugLogs){
				Print("[ReduceVehicleDamage] Finished CarScript OnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + data.Impulse);
			}
		}
		super.OnContact(zoneName, localPos, other, data);
	}
}