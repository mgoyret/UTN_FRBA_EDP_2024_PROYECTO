#include <sm.h>

int flag_discharge = FALSE;

extern float global_vo, global_io, global_vi, global_ii, global_duty;

void state_machine()
{
	static enum State present_state = STATE_CONSTANT_CURRENT;

	if( security_error() )
		present_state = STATE_ERROR;
	switch( present_state )
	{
		case STATE_CONSTANT_CURRENT:
			if( global_io < NULL_CURRENT )	set_duty( DUTY_INIT );
			else
			{
				if(global_io <= 0.3)       set_duty( (float)( global_duty - (float)0.01 ) );	// estado inicial
				else if(global_io >= 1.35) set_duty( (float)( global_duty + (float)0.01 ) );
				else if(global_io <= 0.6)  set_duty( (float)( global_duty - (float)0.001 ) );	// por seguridad
				else if(global_io >= 1.25) set_duty( (float)( global_duty + (float)0.001 ) );	// por seguridad
				else if(global_io <= 0.85) set_duty( (float)( global_duty - (float)0.0001 ) );	// minimo en permante
				else if(global_io >= 1.15) set_duty( (float)( global_duty + (float)0.0001 ) );	// maximo en permanete
			} 
			if( global_vo >= VO_LOW )
				present_state = STATE_CONSTANT_VOLTAGE;
			break;

		case STATE_CONSTANT_VOLTAGE:
			if(global_vo >= 4.5)            			set_duty( (float)( global_duty - (float)0.001 ) );
			else if(global_vo <= 4 && global_vo>=0)		set_duty( (float)( global_duty + (float)0.001 ) );
			else if(global_vo >= 4.3)            		set_duty( (float)( global_duty - (float)0.0001 ) );
			else if(global_vo <= 4.1 && global_vo>=0) 	set_duty( (float)( global_duty + (float)0.0001 ) );
			if( global_vo >= VO_HIGH )
				present_state = STATE_CHARGED;
			break;

		case STATE_CHARGED:
			if ( flag_discharge )			present_state = STATE_DISCHARGE;
			else if ( global_vo < VO_LOW )	present_state = STATE_CONSTANT_CURRENT;
			else if( global_vo < VO_FULL )	present_state = STATE_CONSTANT_VOLTAGE;
			break;

		case STATE_DISCHARGE:
		// COMPLETAR monitorear tambien este duty para que la corriente de descarga sea la adecuada
			set_duty( DUTY_DISCHARGE );
			if ( !flag_discharge || global_vo<BAT_MIN_V ) present_state = STATE_CONSTANT_CURRENT;
			break;

		case STATE_ERROR:
			Serial.print("Electrical error\n");
			while(1);
			break;
		
		default:
			present_state = STATE_CONSTANT_CURRENT;
	}
}
