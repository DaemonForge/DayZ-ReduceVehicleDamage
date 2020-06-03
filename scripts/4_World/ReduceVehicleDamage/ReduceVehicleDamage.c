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
			float dmg = data.Impulse * m_dmgContactCoef;
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
			data.Impulse = dmg / m_dmgContactCoef;
		}
		super.OnContact(zoneName, localPos, other, data);
	}
}