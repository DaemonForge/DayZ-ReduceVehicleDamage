modded class ExpansionHelicopterScript
{
	override void EOnContact( IEntity other, Contact extra ) 
	{
		float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().dmgModifier;
		float rvd_mindmg = ReduceVehicleDamageSettings.Get().mindmg;
		bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;
				
		if ( IsMissionHost())
		{
			float dmg = extra.Impulse * m_dmgContactCoef;
			float rvd_orgdmg = dmg;
			if ( dmg < rvd_mindmg){
				return;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
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
					return;
			}
			extra.Impulse = dmg / m_dmgContactCoef;
		}
		
		super.EOnContact( other, extra);
	}
}