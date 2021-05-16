
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
const int botonAmarillo= 0;
const int botonRojo= 0;
const int botonAzul= 0;
const int botonVerde= 0;
const int botonBlanco = 0;
const int BUTTON_YELLOW = 10;
const int LED_YELLOW = 2;
const int BUTTON_RED = 3;
const int LED_RED = 4;
const int BUTTON_BLUE = 5;
const int LED_BLUE = 8;
const int BUTTON_GREEN = 6;
const int LED_GREEN = 12;
const int BUTTON_WHITE = 9;
const int LED_WHITE = 13;
unsigned long tiempoInicio = 0;
unsigned long tiempoFin = 0;
unsigned long tiempoActual = 0;
unsigned long tiempoPrueba = 0;
unsigned long tiempoRecord25 = 20;
unsigned long tiempoRecord50 = 35;
int recordPulsaciones30 = 30;
int recordPulsaciones60 = 60;
String opciones [] = {"Modo Facil", "Modo Medio", "Modo Dificil", "Modo Mejor 25", "Modo Mejor 50", "30 segundos", "60 segundos"};

int buzzerPin = 7;

const int PRESSED = 0;
const int RELEASED = 1;

void setup() {

 lcd.init();
 lcd.backlight();
 delay(250);
 lcd.noBacklight();
 delay(1000);
 lcd.backlight();
 delay(1000);
  
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_WHITE, INPUT_PULLUP);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT); //inicializo el pin del altavoz para que sea salida

  randomSeed(analogRead(0));
}

void loop() {
  apagarBotones();
  lcd.setCursor(0, 0);
   lcd.print(" Bienvenido al ");
   lcd.setCursor(0, 1);
   lcd.print("    juego");
   delay(4000);
   lcd.clear();
   lcd.setCursor(0, 0);
   lcd.print("Pulsa el blanco ");
   lcd.setCursor(0, 1);
   lcd.print(" para ver menu");
   
   digitalWrite(LED_WHITE, HIGH);
   while (digitalRead(BUTTON_WHITE) == RELEASED){}
   digitalWrite(LED_WHITE, LOW);
   tone(buzzerPin, 261, 200);
   lcd.clear(); 
   delay(500);
   
   int modo = 0;
   boolean elegido = false;  
   lcd.setCursor(0, 0);
   lcd.print(opciones[0]);
   digitalWrite(LED_RED, HIGH);
   digitalWrite(LED_GREEN, HIGH);
   delay(500);
   while(!elegido){
    int verdePulsado = digitalRead(BUTTON_GREEN);
    int rojoPulsado = digitalRead(BUTTON_RED);
    int blancoPulsado = digitalRead(BUTTON_WHITE);
    if(verdePulsado == PRESSED && modo<6){
      lcd.clear();
      tone(buzzerPin, 261, 200); //envío un tono al pin del altavoz con frecuencia 261 (do) y duración 200 milisegundos. 
      modo = modo + 1;
      lcd.setCursor(0,0);
      lcd.print(opciones[modo]);
      delay(500);
    }
    if(rojoPulsado == PRESSED && modo> 0){
      lcd.clear();
      tone(buzzerPin, 261, 200); //envío un tono al pin del altavoz con frecuencia 261 (do) y duración 200 milisegundos. 
      modo = modo -1;
      lcd.setCursor(0,0);
      lcd.print(opciones[modo]);
      delay(500);
    }
    if(blancoPulsado == PRESSED){
      lcd.clear();
      tone(buzzerPin, 261, 200); //envío un tono al pin del altavoz con frecuencia 261 (do) y duración 200 milisegundos. 
      elegido = true;
    }
   }
   digitalWrite(LED_RED, LOW);
   digitalWrite(LED_GREEN, LOW);
   
   lcd.setCursor(0, 0);
   lcd.print("  Comienza en");
   lcd.setCursor(0, 1);
   lcd.print("      3");
   tone(buzzerPin, 510, 200);
   delay(1000);
   lcd.setCursor(0, 1);
   lcd.print("      2");
   tone(buzzerPin, 510, 200);
   delay(1000);
   lcd.setCursor(0, 1);
   lcd.print("      1");
   tone(buzzerPin, 510, 200);
   delay(1000);
   lcd.clear();
   tone(buzzerPin, 987, 400);
   
   boolean terminado = modoDeJuego(modo);
  
}

boolean modoDeJuego(int modo){
    if(modo == 0 || modo == 1 || modo == 2){
      return modoDificultad(modo);
     }else if(modo == 3){
      return modoCantidad(25);
     } else if (modo == 4){
      return modoCantidad(50); 
     } else if (modo == 5 || modo == 6){
        return modoTiempo(modo);
      }
    
  }

boolean modoDificultad(int modo){
  int tiempoReaccion = 0;
  int repeticiones = 25;
  if(modo == 0){
    tiempoReaccion = 1000;
  }else if (modo == 1){
    tiempoReaccion = 750;
  }else if (modo == 2){
    tiempoReaccion = 500;
  }
  lcd.setCursor(0, 0);
  lcd.print("JUEGO EN PROCESO");
  delay(50);
  int contador = 0;
  while(contador < repeticiones){
    int color = random(0,5);
    if(color == 0){
      digitalWrite(LED_YELLOW, HIGH);
      boolean pulsado = false;
      boolean tiempoEncendido = true;
      tiempoInicio = millis();
      while(!pulsado && tiempoEncendido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        tiempoEncendido = tiempoActual < tiempoReaccion;
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(amarilloPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_YELLOW, LOW);
          delay(tiempoReaccion-tiempoActual);
          contador = contador + 1;
        } else if((amarilloPulsado == RELEASED) &&(verdePulsado == PRESSED || rojoPulsado == PRESSED || blancoPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        }
       }
       if(!pulsado){
         juegoPerdido();
         return false;
       }
      }else if (color == 1){
        digitalWrite(LED_RED, HIGH);
        boolean pulsado = false;
        boolean tiempoEncendido = true;
        tiempoInicio = millis();
       while(!pulsado && tiempoEncendido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        tiempoEncendido = tiempoActual < tiempoReaccion;
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(rojoPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_RED, LOW);
          delay(tiempoReaccion-tiempoActual);
          contador = contador + 1;
        }else if((rojoPulsado == RELEASED) &&(verdePulsado == PRESSED || blancoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
         }
        }
        if(!pulsado){
         juegoPerdido();
         return false;
       }
      }else if (color == 2){
      digitalWrite(LED_BLUE, HIGH);
      boolean pulsado = false;
      boolean tiempoEncendido = true;
      tiempoInicio = millis();
      while(!pulsado && tiempoEncendido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        tiempoEncendido = tiempoActual < tiempoReaccion;
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(azulPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_BLUE, LOW);
          delay(tiempoReaccion-tiempoActual);
          contador = contador +1;
        }else if ((azulPulsado == RELEASED) && (verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || blancoPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
         return false;
        }
        }
        if(!pulsado){
         juegoPerdido();
         return false;
       }
      }else if (color == 3){
        digitalWrite(LED_GREEN, HIGH);
        boolean pulsado = false;
        boolean tiempoEncendido = true;
        tiempoInicio = millis();
        while(!pulsado && tiempoEncendido){
          tiempoFin = millis();
          tiempoActual = tiempoFin - tiempoInicio;
          tiempoEncendido = tiempoActual < tiempoReaccion;
          int amarilloPulsado = digitalRead(BUTTON_YELLOW);
          int verdePulsado = digitalRead(BUTTON_GREEN);
          int rojoPulsado = digitalRead(BUTTON_RED);
          int blancoPulsado = digitalRead(BUTTON_WHITE);
          int azulPulsado = digitalRead(BUTTON_BLUE);
          if(verdePulsado == PRESSED){
            delay(250);
            pulsado = true;
            digitalWrite(LED_GREEN, LOW);
            delay(tiempoReaccion-tiempoActual);
            contador = contador +1;
          }else if((verdePulsado == RELEASED)&&(blancoPulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
           pulsado = true;
           juegoPerdido();
           return false;
          }
         }
        if(!pulsado){
         juegoPerdido();
         return false;
        }
       } else if (color == 4){
        digitalWrite(LED_WHITE, HIGH);
        boolean pulsado = false;
        boolean tiempoEncendido = true;
        tiempoInicio = millis();
        while(!pulsado && tiempoEncendido){
          tiempoFin = millis();
          tiempoActual = tiempoFin - tiempoInicio;
          tiempoEncendido = tiempoActual < tiempoReaccion;
          int amarilloPulsado = digitalRead(BUTTON_YELLOW);
          int verdePulsado = digitalRead(BUTTON_GREEN);
          int rojoPulsado = digitalRead(BUTTON_RED);
          int blancoPulsado = digitalRead(BUTTON_WHITE);
          int azulPulsado = digitalRead(BUTTON_BLUE);
          if(blancoPulsado == PRESSED){
            delay(250);
            pulsado = true;
            digitalWrite(LED_WHITE, LOW);
            delay(tiempoReaccion-tiempoActual);
            contador = contador +1;
          }else if((blancoPulsado == RELEASED)&&(verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
            pulsado = true;
            juegoPerdido();
            return false;
          } 
        }
        if(!pulsado){
         juegoPerdido();
         return false;
        }
      }
    }
    lcd.clear();
    juegoDificultadTerminado();
    lcd.clear();
    
  }

boolean modoCantidad(int repeticiones){
  tiempoInicio = millis();
  lcd.setCursor(0, 0);
  lcd.print("JUEGO EN PROCESO");
  delay(50);
  int contador = 0;
  int colorAntiguo = -1;
  while(contador < repeticiones){
    int color = random(0,5);
    while(colorAntiguo == color){
      color = random(0,5);
      }
    if(color == 0){
      colorAntiguo = 0;
      digitalWrite(LED_YELLOW, HIGH);
      boolean pulsado = false;
      while(!pulsado){
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(amarilloPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_YELLOW, LOW);
          contador = contador + 1;
        } else if((amarilloPulsado == RELEASED) &&(verdePulsado == PRESSED || rojoPulsado == PRESSED || blancoPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        }
       }
    } else if (color == 1){
      colorAntiguo = 1;
      digitalWrite(LED_RED, HIGH);
      boolean pulsado = false;
      while(!pulsado){
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(rojoPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_RED, LOW);
          contador = contador +1;
        }else if((rojoPulsado == RELEASED) &&(verdePulsado == PRESSED || blancoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
         }
        }
    } else if (color == 2){
      colorAntiguo = 2;
      digitalWrite(LED_BLUE, HIGH);
      boolean pulsado = false;
      while(!pulsado){
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(azulPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_BLUE, LOW);
          contador = contador +1;
        }else if ((azulPulsado == RELEASED) && (verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || blancoPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
         return false;
        }
        }
    } else if (color == 3){
      colorAntiguo = 3;
      digitalWrite(LED_GREEN, HIGH);
      boolean pulsado = false;
      while(!pulsado){
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(verdePulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_GREEN, LOW);
          contador = contador +1;
        }else if((verdePulsado == RELEASED)&&(blancoPulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        }
       }
    } else if (color == 4){
      colorAntiguo = 4;
      digitalWrite(LED_WHITE, HIGH);
      boolean pulsado = false;
      while(!pulsado){
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(blancoPulsado == PRESSED){
          delay(250);
          digitalWrite(LED_WHITE, LOW);
          contador = contador +1;
          pulsado = true;
        }else if((blancoPulsado == RELEASED)&&(verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        } 
       }
      }
    }
    tiempoFin = millis();
    tiempoActual = tiempoFin-tiempoInicio;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Juego terminado");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Has tardado");
    lcd.setCursor(0, 1);
    lcd.print(String(tiempoActual/1000) + String(" segundos"));
    delay(4000);
    lcd.clear();
    if(repeticiones == 25){
      if((tiempoActual/1000) < tiempoRecord25){
        nuevoRecord(tiempoActual/1000, repeticiones);  
      } else {
          lcd.setCursor(0, 0);
          lcd.print("El record esta");
          lcd.setCursor(0, 1);
          lcd.print(String("en ") + String(tiempoRecord25)+ String(" segundos"));
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Mas suerte en el");
          lcd.setCursor(0, 1);
          lcd.print("proximo intento");
          delay(4000);
          lcd.clear();
        }
    } else{
      if((tiempoActual/1000) < tiempoRecord50){
        nuevoRecord(tiempoActual/1000, repeticiones);  
      } else {
          lcd.setCursor(0, 0);
          lcd.print("El record esta");
          lcd.setCursor(0, 1);
          lcd.print(String("en ") + String(tiempoRecord50)+ String(" segundos"));
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Mas suerte en el");
          lcd.setCursor(0, 1);
          lcd.print("proximo intento");
          delay(4000);
          lcd.clear();
        }
    }
    return true;
  }

boolean modoTiempo(int modo){
  tiempoInicio = millis();
  if(modo == 5){
    tiempoPrueba = 30;
  } else {
    tiempoPrueba = 60;
  }
  int contador = 0;
  int colorAntiguo = -1;
  boolean esTiempoValido = true;
  boolean primeraDecena = true;
  while(esTiempoValido){
    tiempoFin = millis();
    tiempoActual = tiempoFin - tiempoInicio;
    esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
    int color = random(0,5);
    while(colorAntiguo == color){
      color = random(0,5);
      }
    if(color == 0){
      colorAntiguo = 0;
      digitalWrite(LED_YELLOW, HIGH);
      boolean pulsado = false;
      while(!pulsado && esTiempoValido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
        lcd.setCursor(0, 0);
        lcd.print(String("Tiempo restante: ") );
        if(tiempoPrueba -(tiempoActual/1000) == 9 && primeraDecena){
          lcd.clear();
          primeraDecena = false;
        }
        lcd.setCursor(0,1);
        lcd.print(String("       ") + String(tiempoPrueba -(tiempoActual/1000)));
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(amarilloPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_YELLOW, LOW);
          contador = contador + 1;
        } else if((amarilloPulsado == RELEASED) &&(verdePulsado == PRESSED || rojoPulsado == PRESSED || blancoPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        }
       }
    } else if (color == 1){
      colorAntiguo = 1;
      digitalWrite(LED_RED, HIGH);
      boolean pulsado = false;
      while(!pulsado && esTiempoValido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
        lcd.setCursor(0, 0);
        lcd.print(String("Tiempo restante: ") );
        if(tiempoPrueba -(tiempoActual/1000) == 9 && primeraDecena){
          lcd.clear();
          primeraDecena = false;
        }
        lcd.setCursor(0,1);
        lcd.print(String("       ") + String(tiempoPrueba -(tiempoActual/1000)));
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(rojoPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_RED, LOW);
          contador = contador +1;
        }else if((rojoPulsado == RELEASED) &&(verdePulsado == PRESSED || blancoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
         }
        }
    } else if (color == 2){
      colorAntiguo = 2;
      digitalWrite(LED_BLUE, HIGH);
      boolean pulsado = false;
      while(!pulsado && esTiempoValido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
        lcd.setCursor(0, 0);
        lcd.print(String("Tiempo restante: ") );
        if(tiempoPrueba -(tiempoActual/1000) == 9 && primeraDecena){
          lcd.clear();
          primeraDecena = false;
        }
        lcd.setCursor(0,1);
        lcd.print(String("       ") + String(tiempoPrueba -(tiempoActual/1000)));
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(azulPulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_BLUE, LOW);
          contador = contador +1;
        }else if ((azulPulsado == RELEASED) && (verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || blancoPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
         return false;
        }
        }
    } else if (color == 3){
      colorAntiguo = 3;
      digitalWrite(LED_GREEN, HIGH);
      boolean pulsado = false;
      while(!pulsado && esTiempoValido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
        lcd.setCursor(0, 0);
        lcd.print(String("Tiempo restante: ") );
        if(tiempoPrueba -(tiempoActual/1000) == 9 && primeraDecena){
          lcd.clear();
          primeraDecena = false;
        }
        lcd.setCursor(0,1);
        lcd.print(String("       ") + String(tiempoPrueba -(tiempoActual/1000)));
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(verdePulsado == PRESSED){
          delay(250);
          pulsado = true;
          digitalWrite(LED_GREEN, LOW);
          contador = contador +1;
        }else if((verdePulsado == RELEASED)&&(blancoPulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        }
       }
    } else if (color == 4){
      colorAntiguo = 4;
      digitalWrite(LED_WHITE, HIGH);
      boolean pulsado = false;
      while(!pulsado && esTiempoValido){
        tiempoFin = millis();
        tiempoActual = tiempoFin - tiempoInicio;
        esTiempoValido = ((tiempoActual/1000) < tiempoPrueba);
        lcd.setCursor(0, 0);
        lcd.print(String("Tiempo restante: ") );
        if(tiempoPrueba -(tiempoActual/1000) == 9 && primeraDecena){
          lcd.clear();
          primeraDecena = false;
        }
        lcd.setCursor(0,1);
        lcd.print(String("       ") + String(tiempoPrueba -(tiempoActual/1000)));
        int amarilloPulsado = digitalRead(BUTTON_YELLOW);
        int verdePulsado = digitalRead(BUTTON_GREEN);
        int rojoPulsado = digitalRead(BUTTON_RED);
        int blancoPulsado = digitalRead(BUTTON_WHITE);
        int azulPulsado = digitalRead(BUTTON_BLUE);
        if(blancoPulsado == PRESSED){
          delay(250);
          digitalWrite(LED_WHITE, LOW);
          contador = contador +1;
          pulsado = true;
        }else if((blancoPulsado == RELEASED)&&(verdePulsado == PRESSED || rojoPulsado == PRESSED || amarilloPulsado == PRESSED || azulPulsado == PRESSED)){
          pulsado = true;
          juegoPerdido();
          return false;
        } 
       }
      }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Juego terminado");
    encenderBotones();
    tone(buzzerPin, 900, 1000);
    delay(1000);
    apagarBotones();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Has pulsado");
    lcd.setCursor(0, 1);
    lcd.print(String(contador) + String(" botones"));
    delay(4000);
    lcd.clear();
    if(modo == 5){
      if(contador > recordPulsaciones30){
        nuevoRecordPulsaciones(contador, modo);  
      } else {
          lcd.setCursor(0, 0);
          lcd.print("El record esta");
          lcd.setCursor(0, 1);
          lcd.print(String("en ") + String(recordPulsaciones30)+ String(" pulsaciones"));
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Mas suerte en el");
          lcd.setCursor(0, 1);
          lcd.print("proximo intento");
          delay(4000);
          lcd.clear();
        }
    } else{
      if(contador > recordPulsaciones60){
        nuevoRecordPulsaciones(contador, modo);  
      } else {
          lcd.setCursor(0, 0);
          lcd.print("El record esta");
          lcd.setCursor(0, 1);
          lcd.print(String("en ") + String(recordPulsaciones60)+ String(" pulsaciones"));
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Mas suerte en el");
          lcd.setCursor(0, 1);
          lcd.print("proximo intento");
          delay(4000);
          lcd.clear();
        }
    }
    return true;
  }

void nuevoRecord(int tiempoActual, int repeticiones){
    lcd.setCursor(0, 0);
    lcd.print("  NUEVO RECORD");
    lcd.setCursor(0, 1);
    lcd.print("  ENHORABUENA !");
  for(int i=0; i<5; i++){
    encenderBotones();
    delay(400);
    apagarBotones();
    delay(400);
    }
    if(repeticiones == 25){
      tiempoRecord25 = tiempoActual;
    } else {
      tiempoRecord50 = tiempoActual;  
    }
    lcd.clear();
  }

void nuevoRecordPulsaciones(int contador, int modo){
    lcd.setCursor(0, 0);
    lcd.print("  NUEVO RECORD");
    lcd.setCursor(0, 1);
    lcd.print("  ENHORABUENA !");
  for(int i=0; i<5; i++){
    encenderBotones();
    delay(400);
    apagarBotones();
    delay(400);
    }
    if(modo == 5){
      recordPulsaciones30 = contador;
    } else {
      recordPulsaciones60 = contador;  
    }
    lcd.clear();
  }

void juegoDificultadTerminado(){
    lcd.setCursor(0, 0);
    lcd.print("NIVEL COMPLETADO");
    lcd.setCursor(0, 1);
    lcd.print("  ENHORABUENA !");
  for(int i=0; i<5; i++){
    encenderBotones();
    delay(400);
    apagarBotones();
    delay(400);
    } 
    lcd.clear();
  }
  
void juegoPerdido(){
  encenderBotones();
  //tone(buzzerPin, 261, 500); //envío un tono al pin del altavoz con frecuencia 261 (do) y duración 200 milisegundos. 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  GAME OVER!");
  delay(200);
  tone(buzzerPin, 622);
  delay(300);
  tone(buzzerPin, 587);
  delay(300);
  tone(buzzerPin, 554);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(buzzerPin, 523 + pitch);
      delay(5);
    }
  }
  noTone(buzzerPin);
  delay(500);
  apagarBotones();
  }


void encenderBotones(){
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_WHITE, HIGH);
  digitalWrite(LED_GREEN, HIGH);  
  }

void apagarBotones(){
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_WHITE, LOW);
  digitalWrite(LED_GREEN, LOW);  
  }
