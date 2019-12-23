///// Programa que mide la temperatura de un termistor  /////
///// Se mide con el canal 0 del ADC         /////

#include <18F4550.h>             // Librer�a de registros y direcciones del micro
#fuses   HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV3,VREGEN,NOICPRT,NOPBADEN
#device  adc=10;                 // Configura ADC a 10 bits
#use     delay(clock=24000000)   // Las funciones delay()utilizan el oscilador a 24MHz
#include <lcd2.c>                // Librer�a para uso del LCD
#include <math.h>                // Librer�a para uso de funciones matem�ticas

// Variables globales *************************************************************
unsigned int16 dato;             // Dato resultante del ADC 
float grados;                     // Voltaje a medir

// FUNCI�N LEE GRADOS *************************************************************
void voltaje (void)
{
   dato = read_adc();            // Lee resultado de la conversi�n del canal 0 
// Calcula la temperatura con la f�rmula
   grados = ((float)5* (dato*7.3313*exp(0.447)) )/1023; // Para exp() se usa math.h
}

// *************************** PROGRAMA PRINCIPAL *********************************
void main()
{
// CONFIGURA ADC Y LCD ************************************************************
   setup_adc(ADC_CLOCK_INTERNAL);               
// Configura ADC, se debe esperear 10ms antes de iniciar una conversi�n
   set_adc_channel(0);                          
// Inicia conversi�n canal 0 
   lcd_init();                                  
// Inicializa LCD  
   
    for(;;)
   {
      voltaje();                                
// Lee el voltaje   
      lcd_gotoxy(1,1);                          
// Escribe en el LCD la variable a medir
      printf(lcd_putc,"Temperatura: "); 
      lcd_gotoxy(1,2);
      printf(lcd_putc,"T=      %2.2f     �C",grados);
//Escribe el voltaje en formato de dos enteros y dos decimales
      delay_ms(500);
   }
}
// *************************** FIN PROGRAMA PRINCIPAL ******************************
