
#include <avr/sleep.h>
#include <avr/wdt.h>

int led = 13;
volatile int wd_counter = 0;

ISR(WDT_vect)
{
    wd_counter++;
}

void setup()
{                
    pinMode(led, OUTPUT);     
}

void loop()
{
    digitalWrite(led, HIGH);
    wd_delay(1000);
    digitalWrite(led, LOW);
    wd_delay(1000);
}

void wd_delay(unsigned long t_ms) // OJO: LA SENSIBILIDAD SERA DE 15MS (UN CAMBIO MENOR A 15MS NO SE DETECTA Y, EL VALOR MINIMO SERA DE 15MS)
{
    int num_veces = 0;
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    
    if(t_ms == 15)
    {
        setup_watchdog(WDTO_15MS);
        sleep_mode();
    }
    else if(t_ms == 30)
    {
        setup_watchdog(WDTO_30MS);
        sleep_mode();
    }
    else if(t_ms == 60)
    {
        setup_watchdog(WDTO_60MS);
        sleep_mode();
    }
    else if(t_ms == 120)
    {
        setup_watchdog(WDTO_120MS);
        sleep_mode();
    }
    else if(t_ms == 250)
    {
        setup_watchdog(WDTO_250MS);
        sleep_mode();
    }
    else if(t_ms == 500)
    {
        setup_watchdog(WDTO_500MS);
        sleep_mode();
    }
    else if(t_ms == 1000)
    {
        setup_watchdog(WDTO_1S);
        sleep_mode();
    }
    else if(t_ms == 2000)
    {
        setup_watchdog(WDTO_2S);
        sleep_mode();
    }
    else if(t_ms == 4000)
    {
        setup_watchdog(WDTO_4S);
        sleep_mode();
    }
    else if(t_ms == 8000)
    {
        setup_watchdog(WDTO_8S);
        sleep_mode();
    }
    else
    {
        num_veces = t_ms/15;
        while(wd_counter < num_veces)
        {
            setup_watchdog(WDTO_15MS);
            sleep_mode();
        }
    }
    
    wdt_disable();
    wd_counter = 0; 
}

void setup_watchdog(int timerPrescaler)
{
    if ((timerPrescaler < 0) || (timerPrescaler > 10))
        timerPrescaler = WDTO_15MS;
        
    byte bb = timerPrescaler & 7;    
    if(timerPrescaler > 7)
        bb |= (1<<5); // Establece los bits necesarios
    
    MCUSR &= ~(1<<WDRF); // Limpia el flag de reset del watchdog
    WDTCSR |= (1<<WDCE) | (1<<WDE); // Activa el watchdog
    WDTCSR = bb; // Establece el Timeout del watchdog
    WDTCSR |= _BV(WDIE); // Activa la interrupcion del watchdog
}
