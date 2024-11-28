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
		Serial.print("############################ STATE_CONSTANT_CURRENT\n");
		if (global_io < NULL_CURRENT)
			set_duty(DUTY_CHARGE_INIT);
		else
		{
			if (global_io <= (float)(CHARGE_CONST_I * 0.3))
				set_duty((float)(global_duty + (float)0.01)); // estado inicial - ajuste grueso
			else if (global_io >= (float)(CHARGE_CONST_I * 1.3))
				set_duty((float)(global_duty - (float)0.01));
			else if (global_io <= (float)(CHARGE_CONST_I * 0.85))
				set_duty((float)(global_duty + (float)0.001)); // en permante - ajuste fino - 0.001 minimo paso posible con pwm_res
			else if (global_io >= (float)(CHARGE_CONST_I * 1.15))
				set_duty((float)(global_duty - (float)0.001));
		}
		if (global_vo >= CVCC_THRESHOLD)
				present_state = STATE_CONSTANT_VOLTAGE;
		break;

	case STATE_CONSTANT_VOLTAGE:
		Serial.print("############################ STATE_CONSTANT_VOLTAGE\r\n");
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
		present_state = STATE_ERROR;
		//Serial.print("############################ BATERIA CARGADA");
		/*
		if (flag_discharge)
			present_state = STATE_DISCHARGE;
		else if (global_vo < NONIMAL_V)
			present_state = STATE_CONSTANT_CURRENT;
		break;
		*/
	case STATE_DISCHARGE:
	//Serial.print("############################ STATE_DISCHARGE\r\n");
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
