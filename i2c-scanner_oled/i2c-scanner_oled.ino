#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definições do display
#define SCREEN_WIDTH 128 // OLED display width, em pixels
#define SCREEN_HEIGHT 64 // OLED display height, em pixels
#define OLED_RESET -1 // Pino de reset do OLED. Use -1 se a sua placa não tiver.

// Instancia o objeto do display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin();
  
  // Inicia o display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço 0x3C para 128x64
    for(;;); // Loop infinito se a inicialização falhar
  }
  
  // Limpa o display e mostra a mensagem de inicialização
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("I2C Scanner");
  display.println("Buscando...");
  display.display();
  
  delay(2000);
}

void loop() {
  byte error, address;
  int nDevices;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Dispositivos I2C encontrados:");
  
  nDevices = 0;
  for(address = 1; address < 127; address++ ) {
    // Inicia a transmissão I2C e verifica se o dispositivo responde
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      display.setCursor(0, display.getCursorY()); // Seta o cursor para a próxima linha
      display.print("Endereco: 0x");
      if (address < 16) {
        display.print("0");
      }
      display.println(address, HEX);
      nDevices++;
    }
  }

  // Verifica se encontrou algum dispositivo
  if (nDevices == 0) {
    display.setCursor(0, display.getCursorY());
    display.println("Nenhum dispositivo encontrado.");
  }

  display.display();
  delay(5000); // Pausa para não sobrecarregar
}
