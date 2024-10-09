#include <mde.h>

extern float 	SOC;
extern float 	Iout;
extern float 	Vout;
extern float 	duty;
extern int		descarga;

int flag_descarga = FALSE;

void maquina_de_estados()
{
	static enum Estado estado_actual = ESTADO_CORRIENTE_CTE;

	switch( estado_actual )
	{
		case ESTADO_CORRIENTE_CTE:
			if( get_i0() < 0.00001 )	set_duty( (float)0.64 );
			else
			{
				if(get_i0() <= 0.3)       set_duty( (float)( get_duty() - (float)0.01 ) );
				else if(get_i0() <= 0.6)  set_duty( (float)( get_duty() - (float)0.001 ) );		// por seguridad
				else if(get_i0() <= 0.85) set_duty( (float)( get_duty() - (float)0.0001 ) );	// minimo en permante
				else if(get_i0() >= 1.35) set_duty( (float)( get_duty() + (float)0.01 ) );
				else if(get_i0() >= 1.25) set_duty( (float)( get_duty() + (float)0.001 ) );		// por seguridad
				else if(get_i0() >= 1.15) set_duty( (float)( get_duty() + (float)0.0001 ) );	// maximo en permanete
			} 
			if( SOC >= SOC_BAJA )
				estado_actual = ESTADO_TENSION_CTE;
			break;
			
		case ESTADO_TENSION_CTE:
			if(get_vo() <= 4 && get_vo()>=0)        set_duty( (float)( get_duty() + (float)0.001 ) );
			else if(get_vo() <= 4.1 && get_vo()>=0) set_duty( (float)( get_duty() + (float)0.0001 ) );
			else if(get_i0() >= 4.5)            	set_duty( (float)( get_duty() - (float)0.001 ) );
			else if(get_i0() >= 4.3)            	set_duty( (float)( get_duty() - (float)0.0001 ) );
			if( SOC >= SOC_ALTA )
				estado_actual = ESTADO_CARGADO;
			break;
			
		case ESTADO_CARGADO:
			if ( flag_descarga )		estado_actual = ESTADO_DESCARGA;
			else if ( SOC < SOC_BAJA )	estado_actual = ESTADO_CORRIENTE_CTE;
			else if( SOC < SOC_FULL )	estado_actual = ESTADO_TENSION_CTE;
			break;
			
		case ESTADO_DESCARGA:
			set_duty( (float)0.348 );
			if ( !flag_descarga || get_vo()<3 ) estado_actual = ESTADO_CORRIENTE_CTE;
			break;
		
		default: estado_actual = ESTADO_CORRIENTE_CTE;
	}
}
