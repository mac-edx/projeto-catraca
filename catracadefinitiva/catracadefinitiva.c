#include <string.h>
#include "inc/ssd1306.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <stdio.h>
#include "matriz.h"

#define I2C_PORT i2c1

char *text = ""; //texto do menu
int button_pressed = 0;  // Variável para sinalizar que o botão foi pressionado
const uint I2C_SDA = 14;     // Pino SDA do barramento I2C
const uint I2C_SCL = 15;     // Pino SCL do barramento I2C
int menuselct = 1;                       // Variável para armazenar o menu selecionado
ssd1306_t disp;
uint pos_y=14;


const int JSY = 26; // Pino de leitura do eixo Y do joystick (conectado ao ADC)
uint16_t JSY_value; // Variáveis para armazenar os valores do joystick (eixos X e Y) e botão

int GR, HO, DI = 0;
int PT = 1;

int BUTAOA = 5; // Pino do botão A
int RED_LED_PIN = 13; // Pino do LED vermelho
int GREEN_LED_PIN = 11; // Pino do LED verde

void joyconfig(){
    // Inicializa o ADC e os pinos de entrada analógica
    adc_init();         // Inicializa o módulo ADC
    adc_gpio_init(JSY); // Configura o pino VRY (eixo Y) para entrada ADC

  }
  
  void joy_leitura(uint16_t *JSY_value)
  {
    // Leitura do valor do eixo Y do joystick
    adc_select_input(0);             // Seleciona o canal ADC para o eixo Y
    sleep_us(2);                     // Pequeno delay para estabilidade
    *JSY_value = adc_read();               // Lê o valor do eixo Y (0-4095)
  
  }
  




void initmenu(){
    stdio_init_all();   // Inicializa os tipos stdio padrão presentes ligados ao binário

    // Inicialização do i2c
    i2c_init(I2C_PORT, 400*1000);// I2C Inicialização. Usando 400Khz.
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    gpio_set_dir(BUTAOA, GPIO_IN); // Configura o botão A como entrada
    gpio_pull_up(BUTAOA);
   
    //configuração do LED
    gpio_init(RED_LED_PIN);
    gpio_init(GREEN_LED_PIN);
  
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);


    disp.external_vcc=false;

    // Processo de inicialização completo do OLED SSD1306
    ssd1306_init(&disp, 128, 64, 0x3C, I2C_PORT);
}


//função escrita no display.
void print_texto(char *msg, uint pos_x, uint pos_y, uint scale){
    ssd1306_draw_string(&disp, pos_x, pos_y, scale, msg);//desenha texto
    ssd1306_show(&disp);//apresenta no Oled


}
void GRp(){
    static int prev_state = 1; // Variável estática para armazenar o estado anterior do botão
    int btn = gpio_get(BUTAOA); // Lê o estado atual do botão
    if(prev_state == 1 && btn == 0){ // Verifica se o botão foi pressionado

        GR = !GR;
        sleep_ms(200);
    }
    prev_state = btn; // Atualiza o estado anterior do botão
    ssd1306_clear(&disp);//Limpa a tela
    print_texto("edite o valor", 34, 2, 1);
    print_texto("GR", 28, 32, 2);
if(GR == 1){
        print_texto("1", 60, 32, 2);
        npSetLED(4, 0, 255, 0); // Verde
   
}
else {
    print_texto("0", 60, 32, 2);
    npSetLED(4, 255, 0, 0); // Vermelho
}
}

void HOp(){
    static int prev_state2 = 1; // Variável estática para armazenar o estado anterior do botão
    int btn2 = gpio_get(BUTAOA); // Lê o estado atual do botão
    if(prev_state2 == 1 && btn2 == 0){ // Verifica se o botão foi pressionado

        HO = !HO;
        sleep_ms(200);
    }
    prev_state2 = btn2; // Atualiza o estado anterior do botão

    ssd1306_clear(&disp);//Limpa a tela
    print_texto("edite o valor", 34, 2, 1);
    print_texto("HO", 28, 32, 2);

if(HO == 1){
        print_texto("1", 60, 32, 2);
        npSetLED(3, 0, 255, 0); // Verde
}
else {
    print_texto("0", 60, 32, 2);
    npSetLED(3, 255, 0, 0); // Vermelho
}
}

void DIp(){
    static int prev_state3 = 1; // Variável estática para armazenar o estado anterior do botão
    int btn3 = gpio_get(BUTAOA); // Lê o estado atual do botão
    if(prev_state3 == 1 && btn3 == 0){ // Verifica se o botão foi pressionado

        DI = !DI;
        sleep_ms(200);
    }
    prev_state3 = btn3; // Atualiza o estado anterior do botão

    ssd1306_clear(&disp);//Limpa a tela
    print_texto("edite o valor", 34, 2, 1);
    print_texto("DI", 28, 32, 2);

if(DI == 1){
        print_texto("1", 60, 32, 2);
        npSetLED(2, 0, 255, 0); // Verde
}
else {
    print_texto("0", 60, 32, 2);
    npSetLED(2, 255, 0, 0); // Vermelho
}}

void PTp(){
    static int prev_state4 = 1; // Variável estática para armazenar o estado anterior do botão
    int btn4 = gpio_get(BUTAOA); // Lê o estado atual do botão
    if(prev_state4 == 1 && btn4 == 0){ // Verifica se o botão foi pressionado

        PT = !PT;
        sleep_ms(200);
       
    }
    prev_state4 = btn4; // Atualiza o estado anterior do botão
    

    ssd1306_clear(&disp);//Limpa a tela
    print_texto("edite o valor", 34, 2, 1);
    print_texto("PT", 28, 32, 2);

if(PT == 1){
        print_texto("1", 60, 32, 2);
        npSetLED(1, 0, 255, 0); // Verde
}
else {
    print_texto("0", 60, 32, 2);
}
}
void CT(){
    //texto do Menu

    if (!PT || (DI && HO && GR)) { // Verifica se ambos os botões estão pressionados
   
        gpio_put(GREEN_LED_PIN, 1); // Liga o LED verde
        gpio_put(RED_LED_PIN, 0); // Desliga o LED vermelho
    } else {
      
        gpio_put(GREEN_LED_PIN, 0); // Desliga o LED verde
        gpio_put(RED_LED_PIN, 1); // Liga o LED vermelho
    }

  
}


void MenuJoy(){    
       
            
            if (menuselct == 1) {
                
                    GRp ();  // Função associada ao Menu 1
            
            }
                else if (menuselct == 2) {
              
                 
                    HOp();  // Função associada ao Menu 2
                   
                }
               else if (menuselct == 3) {
              
               
                    DIp();  // Função associada ao Menu 46
              
               }

              else if (menuselct == 4) {
                
       
                    PTp(); //função associada ao Menu 4
             
                   }

     
        
        joy_leitura(&JSY_value); // Lê os valores dos eixos do joystick     


        if (JSY_value < 100) {
            menuselct +=1;
            sleep_ms(200);  // Delay para evitar mudanças rápidas
            if (menuselct > 4) {
                menuselct = 1;
            
            }
            }
        
        else if (JSY_value > 3000) {
            menuselct -=1;
            sleep_ms(200);  // Delay para evitar mudanças rápidas
            if (menuselct < 1) {
                menuselct = 4;
            }
        }
    }
        
    

int main(){ // Função principal
    // Inicializa o sistema e os periféricos
    ssd1306_clear(&disp); 
    initmenu();
    joyconfig();
    
    while (1)
{
    CT();
    MenuJoy();
}
}