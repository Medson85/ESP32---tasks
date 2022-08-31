#include <Arduino.h>

#define tempoLED 500

//declaração de prototipos e inicialização de variaveis

void vTask1( void * pvParameters );
void vTask2( void * pvParameters );
void vTask3( void * pvParameters );
void vTask4( void * pvParameters );

TaskHandle_t task1;
TaskHandle_t task2;
TaskHandle_t task3;
TaskHandle_t task4;

QueueHandle_t filateste;

uint8_t contador = 0;

void setup() {

  Serial.begin(115200);                               // Configura a taxa de transferência em bits por 
                                                      // segundo (baud rate) para transmissão serial.
  pinMode(LED_BUILTIN,OUTPUT);                        // Número do pino ao qual o LED on-board está 
                                                      // conectado.


  // put your setup code here, to run once:
xTaskCreatePinnedToCore(
                   vTask1,                            // Function that implements the task.
                   "task1",                           // Text name for the task.
                   configMINIMAL_STACK_SIZE + 100,    // Stack size in bytes, not words.
                   NULL,                              // Parameter passed into the task.
                   1,                                 // Priority at which the task is created.
                   &task1,
                   APP_CPU_NUM );                     // Variable to hold the task's data structure.

xTaskCreatePinnedToCore(
                   vTask2,                            // Function that implements the task.
                   "task2",                           // Text name for the task.
                   configMINIMAL_STACK_SIZE + 500,    // Stack size in bytes, not words.
                   NULL,                              // Parameter passed into the task.
                   1,                                 // Priority at which the task is created.
                   &task2,
                   APP_CPU_NUM );                     // Variable to hold the task's data structure.

xTaskCreatePinnedToCore(
                   vTask3,                            // Function that implements the task.
                   "task3",                           // Text name for the task.
                   configMINIMAL_STACK_SIZE + 500,    // Stack size in bytes, not words.
                   NULL,                              // Parameter passed into the task.
                   1,                                 // Priority at which the task is created.
                   &task3,
                   APP_CPU_NUM );                     // Variable to hold the task's data structure.

xTaskCreatePinnedToCore(
                   vTask4,                            // Function that implements the task.
                   "task4",                           // Text name for the task.
                   configMINIMAL_STACK_SIZE + 500,    // Stack size in bytes, not words.
                   NULL,                              // Parameter passed into the task.
                   1,                                 // Priority at which the task is created.
                   &task4,
                   APP_CPU_NUM );                     // Variable to hold the task's data structure.

  filateste = xQueueCreate( 10, sizeof( uint8_t )  ); // Cria nova fila
                                                      // (O número máximo de itens que a fila pode 
                                                      // conter a qualquer momento,
                                                      // O tamanho, É unsigned integer de 8 bits type, 
                                                      // necessário para manter cada item na fila.)

}

void loop() {
  // put your main code here, to run repeatedly:

}


void vTask1( void * pvParameters ){

  while(1){
    
    //Serial.print("task1 ");
    contador += 2;

    //if( uxQueueSpacesAvailable( filateste ) != 0 ){
      xQueueSend( filateste, &contador , portMAX_DELAY );   // Postar um item em uma fila. O item é enfileirado 
                                                            // por cópia, não por referência.
                                                            // O identificador para a fila na qual o item deve 
                                                            // ser postado.
                                                            // Um ponteiro para o item que deve ser colocado na
                                                            // fila.
                                                            // A quantidade máxima de tempo que a tarefa deve 
                                                            // bloquear esperando que o espaço fique disponível
                                                            // na fila, caso já esteja cheio.
    //}
    //Serial.println( "Valor do contador: " +  String( contador ) );

    vTaskDelay( 10000 );    //especifica um horário em que a tarefa deseja desbloquear em relação 
                            //ao horário em que vTaskDelay() é chamado.
  }

}

void vTask2( void * pvParameters ){

  while(1){

    //contador = 0;

    Serial.print("task2 ");
    Serial.println( "Valor do contador: " +  String( contador ) );

    vTaskDelay(5000);
  }

}

void vTask3( void * pvParameters ){

  while (1)
  {
    Serial.print("Quantidade de bytes livre - Task1: ");
    Serial.println( uxTaskGetStackHighWaterMark( task1 ) );
    Serial.print("Quantidade de bytes livre - Task2: ");
    Serial.println( uxTaskGetStackHighWaterMark( task2 ) );
    Serial.print("Quantidade de bytes livre - Task3: ");
    Serial.println( uxTaskGetStackHighWaterMark( NULL ) );
    Serial.print("Quantidade de bytes livre - Task4: ");
    Serial.println( uxTaskGetStackHighWaterMark( task4 ) );
    Serial.print( "Tamanho de um inteiro: " );                      // Teste para verificar espaço ocupado
    Serial.println( sizeof(int) );                                  // por uma variavel do tipo INT
    

    vTaskDelay(10000);
  }
  
}

void vTask4( void * pvParameters ){
  uint8_t varFila = 0;

while (1)
{
    // digitalWrite(LED_BUILTIN,HIGH);
    // vTaskDelay( tempoLED );
    // digitalWrite(LED_BUILTIN,LOW);
    // vTaskDelay( tempoLED );

    if ( uxQueueMessagesWaiting( filateste ) != 0 ){                        // Retorna o número de mensagens 
                                                                            // armazenadas em uma fila.
                                                                            
      if( xQueueReceive( filateste,&varFila,portMAX_DELAY ) == pdFALSE ){   // Receba um item de uma fila. 
                                                                            // O item é recebido por cópia, 
                                                                            // portanto, um buffer de tamanho 
                                                                            // adequado deve ser fornecido. 
                                                                            // O número de bytes copiados no 
                                                                            // buffer foi definido quando a 
                                                                            // fila foi criada.
        Serial.println("Não recebeu dados");
      } else { 
          Serial.print("Valor que estava na fila: ");
          Serial.println( varFila ); 
        }
    }

    vTaskDelay(100);       
}


}









