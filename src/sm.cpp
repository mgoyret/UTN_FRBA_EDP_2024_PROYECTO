#include <sm.h>

void state_machine()
{
	static enum State present_state = STATE_CONSTANT_CURRENT;

	if (security_error())
	{
		set_duty_off();
		present_state = STATE_ERROR;
	}
	switch (present_state)
	{
	case STATE_CONSTANT_CURRENT:
		if (global_io < NULL_CURRENT || global_duty <= 0.5)
			set_duty(DUTY_CHARGE_INIT);
		else
		{
			if (global_io <= (float)(CHARGE_CONST_I * 0.3))
				set_duty((float)(global_duty - (float)0.01)); // estado inicial - ajuste grueso
			else if (global_io >= (float)(CHARGE_CONST_I * 1.3))
				set_duty((float)(global_duty + (float)0.01));
			else if (global_io <= (float)(CHARGE_CONST_I * (1.0 - 0.15)))
				set_duty((float)(global_duty - (float)0.001)); // en permante - ajuste fino - 0.001 minimo paso posible con pwm_res
			else if (global_io >= (float)(CHARGE_CONST_I * (1.0 + 0.15)))
				set_duty((float)(global_duty + (float)0.001));
		}
		if (global_vo >= CVCC_THRESHOLD) // COMPLETAR, creo que es asi, con corriente llega hasta el pico de tension y ahi cambio
										// en teoria es asi, pero en la realidad habria que ver si no es hasta que llegue al 99.9%
			present_state = STATE_CONSTANT_VOLTAGE;
		break;

	case STATE_CONSTANT_VOLTAGE:
		if (global_vo >= (float)(CHARGE_CONST_V * (1.0 + 0.07)))
			set_duty((float)(global_duty - (float)0.001));
		else if (global_vo <= (float)(CHARGE_CONST_V * (1.0 - 0.07)) && global_vo >= 0)
			set_duty((float)(global_duty + (float)0.001));
		else if (global_vo >= (float)(CHARGE_CONST_V * (1.0 + 0.02)))
			set_duty((float)(global_duty - (float)0.001));
		else if (global_vo <= (float)(CHARGE_CONST_V * (1.0 - 0.02)) && global_vo >= 0)
			set_duty((float)(global_duty + (float)0.001));
		if (global_io <= CHARGE_CUTOFF_I)
			present_state = STATE_CHARGED;
		break;

	case STATE_CHARGED:
		if (flag_discharge)
			present_state = STATE_DISCHARGE;
		else if (global_vo < NONIMAL_V)
			present_state = STATE_CONSTANT_CURRENT;
		break;

	case STATE_DISCHARGE:
		if (global_duty >= 0.5)
			set_duty(DUTY_DISCHARGE_INIT);
		else
		{ // COMPLETAR chequear bien los <= o >=
			if (global_io >= (float)(DISCHARGE_I * 0.3))
				set_duty(1.0- (float)(global_duty - (float)0.01));
			else if (global_io <= (float)(DISCHARGE_I * 1.3))
				set_duty(1.0- (float)(global_duty + (float)0.01));
			else if (global_io >= (float)(DISCHARGE_I * (1.0 - 0.15)))
				set_duty(1.0- (float)(global_duty - (float)0.001));
			else if (global_io <= (float)(DISCHARGE_I * (1.0 + 0.15)))
				set_duty(1.0- (float)(global_duty + (float)0.001));
		}
		if (!flag_discharge || global_vo <= DISCHARGE_CUTOFF_V)
			present_state = STATE_CONSTANT_CURRENT;
		break;

	case STATE_ERROR:
		Serial.print("Electrical error\n");
		while (!flag_reset);
		reset();
		present_state = STATE_CONSTANT_CURRENT;
		break;

	default:
		present_state = STATE_CONSTANT_CURRENT;
	}
}
