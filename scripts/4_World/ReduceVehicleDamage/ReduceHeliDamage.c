modded class ExpansionHelicopterScript
{
	vector rvd_OptimalOrientation;
	bool rvd_UseOptimal = false;
	void ExpansionHelicopterScript(){
		if (GetGame().IsServer()){
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.rvd_delayedVectorUpdate, 150, false );
		}
	}
	
	override void OnEngineStop()
	{
		super.OnEngineStop();
		if (GetGame().IsServer()){
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( this.rvd_delayedVectorUpdate, 500, false );
		}

	}
	
	override void OnEngineStart()
	{
		super.OnEngineStart();
		if (GetGame().IsServer()){
			rvd_UseOptimal = false;
		}
	}
	
	void rvd_delayedVectorUpdate(){		
				
			vector rvd_OrgOrientation = GetOrientation();
			float rvd_YOrientation = rvd_OrgOrientation[1];
			float rvd_ZOrientation = rvd_OrgOrientation[2];
			if ((rvd_YOrientation < 20 && rvd_YOrientation > -20)  || rvd_YOrientation > 340){
				if ((rvd_ZOrientation < 20 && rvd_ZOrientation > -20) || rvd_ZOrientation > 340){
					rvd_OptimalOrientation = rvd_OrgOrientation;
					rvd_UseOptimal = true;
					return;
				}
			}
			rvd_UseOptimal = false;
	}
	
	override void EOnContact( IEntity other, Contact extra ) 
	{
		if ( IsMissionHost())
		{
			if (ReduceVehicleDamageSettings.Get().autoHeliStablization && !EngineIsOn() && rvd_UseOptimal && rvd_OptimalOrientation ){
				vector rvd_OrgOrientation = GetOrientation();
				float rvd_normlizedY = rvd_OrgOrientation[1];
				float rvd_normlizedZ = rvd_OrgOrientation[2];
				float rvd_normlizedOptimalY = rvd_OptimalOrientation[1];
				float rvd_normlizedOptimalZ = rvd_OptimalOrientation[2];
				if (rvd_normlizedY > 180){
					rvd_normlizedY = rvd_normlizedY - 360;
				}
				if (rvd_normlizedZ > 180){
					rvd_normlizedZ = rvd_normlizedZ - 360;
				}
				if (rvd_normlizedOptimalY > 180){
					rvd_normlizedOptimalY = rvd_normlizedOptimalY - 360;
				}
				if (rvd_normlizedOptimalZ > 180){
					rvd_normlizedOptimalZ = rvd_normlizedOptimalZ - 360;
				}
			
				float rvd_maxY = rvd_normlizedOptimalY + 5;
				float rvd_minY = rvd_normlizedOptimalY - 5;
				float rvd_maxZ = rvd_normlizedOptimalZ + 5;
				float rvd_minZ = rvd_normlizedOptimalZ - 5;
			
				bool rvd_UpdateNeeded = false;
				if ( rvd_normlizedY < rvd_minY ){
					rvd_normlizedY = rvd_normlizedY + 2.5;
					rvd_UpdateNeeded = true;
				}
				if ( rvd_normlizedY > rvd_maxY ){
					rvd_normlizedY = rvd_normlizedY - 2.5;
					rvd_UpdateNeeded = true;
				}
				if ( rvd_normlizedY < rvd_minZ ){
					rvd_normlizedY = rvd_normlizedY + 2.5;
					rvd_UpdateNeeded = true;
				}
				if ( rvd_normlizedY > rvd_maxZ ){
					rvd_normlizedY = rvd_normlizedY - 2.5;
					rvd_UpdateNeeded = true;
				}
				if (rvd_normlizedY < 0){
					rvd_normlizedY = 360 + rvd_normlizedY;
				}
				if (rvd_normlizedZ < 0){
					rvd_normlizedZ = 360 + rvd_normlizedZ;
				}
				if (rvd_UpdateNeeded){
					SetOrientation(Vector(rvd_OrgOrientation[0], rvd_normlizedY, rvd_normlizedZ));
					vector oldPosition = GetPosition();
					vector newPosition = Vector(oldPosition[0], oldPosition[1] + 0.1, oldPosition[2]);
					SetPosition( newPosition );
					SetSynchDirty();	
				}
			}
		}
		if ( IsMissionHost() && m_dmgContactCoef > 0 && extra.Impulse > 0)
		{
				
		        float rvd_dmgModifier = ReduceVehicleDamageSettings.Get().heliDmgModifier;
		        float rvd_mindmg = ReduceVehicleDamageSettings.Get().heliMinDmg;
		        bool rvd_subtractmindmg = ReduceVehicleDamageSettings.Get().subtractmindmg;
		        bool rvd_nodmgoff = ReduceVehicleDamageSettings.Get().nodmgifoff;
		        bool rvd_debug = ReduceVehicleDamageSettings.Get().debugLogs;

			float dmg = extra.Impulse * m_dmgContactCoef;
			
			//if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Called ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }

			float rvd_orgdmg = dmg;
			if ( dmg < rvd_mindmg){
				//if ( rvd_debug  && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than Min Damage - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				dmg = 50;
			}
			if (!EngineIsOn() && rvd_nodmgoff){
				//if ( rvd_debug && dmg > 150 ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Engine is off - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
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
				if ( rvd_debug ){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Damage Less than one - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				return;
			}
			extra.Impulse = dmg / m_dmgContactCoef;
			bool rvd_dmgBeforeExplode = ReduceVehicleDamageSettings.Get().dmgBeforeExplode;
			bool rvd_dmgcondition = (rvd_nodmgoff && !EngineIsOn());
			if ( rvd_dmgBeforeExplode && extra.Impulse > m_BodyMass * 11 * 2 && GetVelocity(this).Length() > 2.5 && !rvd_dmgcondition && dmg > 50)
			{
				dmg  = dmg * 0.1 * rvd_dmgModifier; //Reduceing Damage again to pervent too much damage
				AddHealth( "", "Health", -dmg);
				float newHealth = GetHealth("", "");
				float fivePercent = GetMaxHealth() * 0.05;
				if ( newHealth > fivePercent )
				{
					if ( rvd_debug){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Vechile took " + dmg + " damage - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
					dmg = 50;
					extra.Impulse = dmg / m_dmgContactCoef;

				}else{
					if ( rvd_debug){ Print("[ReduceVehicleDamage] ExpansionHelicopterScript EOnContact - Vechile took " + dmg + " damage continuing to super - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
				}
			}
			
			//if ( rvd_debug && dmg > 150){ Print("[ReduceVehicleDamage] Finished ExpansionHelicopterScript EOnContact - Vechile Name: " + GetDisplayName() + " - Position: " + GetPosition() + " - Impulse is: " + extra.Impulse); }
		}
		
		super.EOnContact( other, extra);
	}
}
