/* Copyright 2018, Eric Pernia
 * All rights reserved.
 *
 * This file is part of sAPI Library.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
 
/*==================[inlcusiones]============================================*/

#include <sapi.h>        // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/

#define UART_PC        UART_USB
#define UART_BLUETOOTH UART_232


#include "Button.h"
#include "AppModel.h"
#include "AppModelRender.h"
#include "UartConnector.h"

/*==================[funcion principal]======================================*/

//Este es un handler del boton
void buttonPressed(void * appModelPointer) {
	AppModel * appModel = (AppModel *)appModelPointer;
	appModel_toggle(appModel);
}


//Este es un handler uartConnecter
void bluetoothCommandReceived(void * appModelPointer, uint8_t byte) {
	if(byte == 'h') {
		appModel_enable((AppModel *)appModelPointer);
	}
	else if(byte == 'l') {
		appModel_disable((AppModel *)appModelPointer);
	}
}

//Este es un observer del Modelo
void modelChanged(void * uartConnectorPointer, AppModel * model) {
	UartConnector * uartConnector = (UartConnector *) uartConnectorPointer;
	if(appModel_isEnabled(model)) {
		uartConnector_send(uartConnector, "LED_ON");
	}
	else {
		uartConnector_send(uartConnector, "LED_OFF");
	}
}




// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Inicializar UART_232 para conectar al modulo bluetooth
   //uartWriteString( UART_PC, "UART_BLUETOOTH para modulo Bluetooth configurada.\r\n" );
   //uartConfig( UART_BLUETOOTH, 9600 );
   
   //uint8_t data = 0;
   
   Button button;
   AppModel appModel;
   AppModelRender appModelRender;
   UartConnector uartConnector;

   appModel_init(&appModel, 0);
   appModel_setObserver(&appModel, (void *)&uartConnector, modelChanged);

   button_init(&button, TEC1, (void *)&appModel);
   button_onRelease(&button, buttonPressed);

   appModelRender_init(&appModelRender, &appModel, LED1);
   uartConnector_initBt(&uartConnector, &appModel, bluetoothCommandReceived);

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
	   button_update(&button);
	   appModelRender_update(&appModelRender);
	   uartConnector_update(&uartConnector);
	   delay(1);
   }

   return 0;
}


