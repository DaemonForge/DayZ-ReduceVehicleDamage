modded class ExpansionHelicopterScript
{
	override void EOnContact( IEntity other, Contact extra ) 
	{
		if ( IsMissionHost() && m_dmgContactCoef > 0 && extra.Impulse > 0)
		{

		        float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().heliDmgModifier;
		        float rvd_mindmg = ReduceVehicleDamageSettings.Get().heliMinDmg;
		        bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		        bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;
		        bool rvd_debug = ReduceVehicleDamageSettings.Get().debugLogs;

			float dmg = extra.Impulse * m_dmgContactCoef;
			
			if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Called ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }

			float rvd_orgdmg = dmg;
			if ( dmg < rvd_mindmg){
				if ( rvd_debug  && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than Min Damage - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				return;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
				if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Engine is off - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
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
				if ( rvd_debug ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than one - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				return;
			}
			extra.Impulse = dmg / m_dmgContactCoef;
			bool rvd_dmgBeforeExplode = ReduceVehicleDamageSettings.Get().dmgBeforeExplode;
			
			if ( rvd_dmgBeforeExplode && extra.Impulse > m_BodyMass * 11 * 2 && GetVelocity(this).Length() > 2.5)
			{
				dmg  = dmg *rvd_dmgModifier; //Reduceing Damage again to pervent too much damage
				AddHealth( "", "Health", -dmg);
				float newHealth = GetHealth("", "");
				float fivePercent = GetMaxHealth() * 0.05;
				if ( newHealth > fivePercent )
				{
					if ( rvd_debug){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Vechile took " + dmg + " damage - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
					return;
				}else{
					if ( rvd_debug){ Print("[ReduceVehicleDamage] ExpansionHelicopterScript EOnContact - Vechile took " + dmg + " damage continuing to super - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				}
			}
			
			if ( rvd_debug && dmg > 150){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
		}
		
		super.EOnContact( other, extra);
	}
}
