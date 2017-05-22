#include <Arduino.h>
#include <Servo.h>
/*
  FUNÃ‡Ã•ES de AÃ§Ã£o DO ROBÃ”
*/

void pararMotores() {
  analogWrite(MotorEsquerdoDianteiroFrente, 0);
  analogWrite(MotorDireitoDianteiroFrente, 0);            
  analogWrite(MotorEsquerdoDianteiroTras, 0);
  analogWrite(MotorDireitoDianteiroTras, 0);    

  /*** traseiros ***/
  analogWrite(MotorEsquerdoTraseiroFrente, 0);
  analogWrite(MotorDireitoTraseiroFrente, 0);        
  analogWrite(MotorEsquerdoTraseiroTras, 0);
  analogWrite(MotorDireitoTraseiroTras, 0);
}
/*** bloco okk ****/
void mover(int a, int b){
  if (a>0){
    a=a*2.55;
    //a=a+compensacao;
    analogWrite(MotorEsquerdoDianteiroFrente,a);
    analogWrite(MotorEsquerdoTraseiroFrente,a);
    analogWrite(MotorEsquerdoDianteiroTras,0);
    analogWrite(MotorEsquerdoTraseiroTras,0);
  }
  else if(a==0){
    analogWrite(MotorEsquerdoDianteiroFrente,0);
    analogWrite(MotorEsquerdoTraseiroFrente,0);
    analogWrite(MotorEsquerdoDianteiroTras,0);
    analogWrite(MotorEsquerdoTraseiroTras,0);
  }
  else{
    a=a*-2.55;
    analogWrite(MotorEsquerdoDianteiroFrente,0);
    analogWrite(MotorEsquerdoTraseiroFrente,0);
    analogWrite(MotorEsquerdoDianteiroTras,a);
    analogWrite(MotorEsquerdoTraseiroTras,a);
  }
  if (b>0){
    b=b*2.55;
       analogWrite(MotorDireitoDianteiroFrente,b);
    analogWrite(MotorDireitoTraseiroFrente,b);
    analogWrite(MotorDireitoDianteiroTras,0);
    analogWrite(MotorDireitoTraseiroTras,0);
  }
  else if(b==0){
       analogWrite(MotorDireitoDianteiroFrente,0);
    analogWrite(MotorDireitoTraseiroFrente,0);
    analogWrite(MotorDireitoDianteiroTras,0);
    analogWrite(MotorDireitoTraseiroTras,0);
  }
  else{
    b=b*-2.55;
       analogWrite(MotorDireitoDianteiroFrente,0);
    analogWrite(MotorDireitoTraseiroFrente,0);
    analogWrite(MotorDireitoDianteiroTras,b);
    analogWrite(MotorDireitoTraseiroTras,b);
  }  
};

/*** bloco ok ***/
void CurvaGyro(double angulo, int forca_curva){
  //MostrarLCD(CIMA, 0, "                ");
  //MostrarLCD(BAIXO, 0, "                ");
      
  if (angulo > 0) {
    grz = 0;
    while(lendoMpuGyro() <= angulo) {
      //MostrarLCD(CIMA, 0, "ANGULO: " + String(lendoMpuGyro()));
      mover(forca_curva * -1, forca_curva);
    }
  }
  if (angulo < 0) {
    grz = 0;
    while(lendoMpuGyro() >= angulo) {
      //MostrarLCD(CIMA, 0, "ANGULO: " + String(lendoMpuGyro()));
      mover(forca_curva, forca_curva * -1);
    }
    
  }
  //MostrarLCD(CIMA, 0, "                ");
  //MostrarLCD(BAIXO, 0, "                ");
  pararMotores();
}

void AjeitarNaParede() {
  pararMotores();
  delay(300);
  while(lerSharp(3) < 7) {
    mover(forca * -1, forca * -1);
  }
  mover(forca * -1, forca * -1);
  delay(600);
  pararMotores();
}

void droparVitima(int ladodrop) {
  if (ladodrop == 1) {
    myservo2.write(120);
    delay(1700);
    myservo2.write(20);
  }
  if (ladodrop == 2) {
    myservo.write(120);
    delay(1700);
    myservo.write(20);
  }
}

void alertasVitima() {
  
    Buzzer.turnOn();
    LED2.turnOn();
    LED3.turnOn();
    LED4.turnOn();
    delay(200);
    Buzzer.turnOff();
    LED2.turnOff();
    LED3.turnOff();
    LED4.turnOff();
    delay(200);
  
}

void Vitima(int ladodavitima) {
  if (ladodavitima == 1) { // Frente
    while(lerSharp(1) > 10) {
      mover(forca, forca);
    }
    delay(500);
    pararMotores();
    delay(600);
    while(lerSharp(1) < 12) {
      mover(forca_Baixa * -1, forca_Baixa * -1);
    }
    pararMotores();
    delay(600);
    for(int k; k < 15; k++) {
      alertasVitima();
    }
    droparVitima(1);
    delay(1000);
  }

  // vitima direita
  if (ladodavitima == 2) { // Direita
    CurvaGyro(-90, forca);
     pararMotores();
    delay(600);
    mover(forca_Baixa, forca_Baixa);
    delay(700);
    pararMotores();
    delay(600);
    while(lerSharp(1) < 9) {
      mover(forca_Baixa * -1, forca_Baixa * -1);
    }
    pararMotores(); 
    for(int k; k < 15; k++) {
      alertasVitima();
    }
    droparVitima(1);
    delay(1000);
  }


  // vitima tras
   if (ladodavitima == 3) { // Tras
    while(lerSharp(3) > 10) {
      mover(forca * -1, forca * -1);
    }
    delay(500);
    pararMotores();
    delay(600);
    while(lerSharp(3) < 12) {
      mover(forca_Baixa, forca_Baixa);
    }
    pararMotores();
    delay(600);
    for(int k; k < 15; k++) {
      alertasVitima();
    }
    droparVitima(2);
    delay(1000);
  }

  // vitima esquerda
   if (ladodavitima == 4) { // Esquerda
        CurvaGyro(angulo_curva * -1, forca);
     pararMotores();
    delay(600);
    mover(forca_Baixa * -1, forca_Baixa * -1);
    delay(700);
    pararMotores();
    delay(600);
    while(lerSharp(3) < 9) {
      mover(forca_Baixa, forca_Baixa);
    }
    pararMotores();
    for(int k; k < 15; k++) {
      alertasVitima();
    }
    droparVitima(2);
    delay(1000);
  }
}

void Frente() {
    anguloInicial = lendoMpuGyro();
    
    pararMotores();
    mover(forca_Baixa, forca_Baixa);
    delay(tempoandar);

    double correcao = ((lendoMpuGyro() * -1) - (anguloInicial * -1)) / 2;

    //MostrarLCD(BAIXO, 10, String(correcao));

   if(correcao > 0 && correcao < 8) {
    CurvaGyro(correcao, forca);
   }
    pararMotores();
    
    if(lerSharp(1) < 30) {
     while(lerSharp(1) <= 13) {
      mover(forca * -1, forca * -1);
    }
    

    while(lerSharp(1) >= 13) {
      mover(forca, forca);
    }
  }
  
  andou + 1;
  pararMotores();
 
}

void Direita() {
  CurvaGyro(angulo_curva * -1, forca);
  AjeitarNaParede();
  Frente();
}
void Esquerda() {
  CurvaGyro(angulo_curva, forca);
  AjeitarNaParede();
  Frente();
}

void Tras() {

    pararMotores();
    mover(forca_Baixa * -1, forca_Baixa * -1);
    delay(tempoandar);

    
  if(lerSharp(3) < 30) {
     while(lerSharp(3) <= 13) {
      mover(forca, forca);
    }
    while(lerSharp(3) >= 13) {
      mover(forca * -1, forca * -1);
    }
  }
  
  pararMotores();
 
}

void Subida() {
  int media = 20;
  int kp = -8;
  int erro;
  int ganho;
  int tp = -40;
  
  while(lendoMpuAccel() < angulo_rampa_subida) { // enquanto for menor que o angulo, ele sÃ³ vai andando
   /* erro = lerSharp(4) - media;
    ganho = erro * kp;
  
    mover(ganho + tp, ganho - tp);
  */
    mover(forca_Rampa, forca_Rampa);
  }

  

}

void Descida() {
  while(lendoMpuAccel() > angulo_rampa_descida) {
    mover(forca_Baixa, forca_Baixa);
  }
  
}

void AjeitarParedeFrente() {
  
  mover(forca_Baixa, forca_Baixa);
  delay(700);
  pararMotores();
  while(lerSharp(3) < 13) {
    mover(forca_Baixa * -1, forca_Baixa * -1);
  }
  pararMotores();
  
  //delay(700);
}

// o algoritmo vai pegar a coordenada atual, analisar os vizinhos e RETORNAR uma aÃ§Ã£o ao robÃ´
void Algoritmo() {

   andou = 0;
   checarBateria();
   
   //delay(1000);
   //quadradonegro = 0;
   numero++;
   int nunca = 0;
   
   xatual = (coordenadaatual.substring(0,2)).toInt();
   yatual = (coordenadaatual.substring(2,4)).toInt();
   
   //Historico[numero] = coordenadaatual.toInt();
   
   MostrarLCD(CIMA, 0, "X: " + String(xatual));
   MostrarLCD(BAIXO, 0, "Y: " + String(yatual));

  MostrarLCD(CIMA, 12, String(quadradonegro));
MostrarLCD(BAIXO, 10, String(verificarCoord()));

  if(verificarRampa(SUBIDA) == true) {
    Subida();
    
  } 
  else if(verificarRampa(DESCIDA) == true) {
    Descida();
    
  } else {
  
        // Checagem primeiro do black space
        if (verificarBlackSpace() == true) {
          //int BlackSpace[] = {coordenadaatual.toInt()};
          
          //voltarPara(Historico[numero - 1]);
           for(int t; t < 3; t++) {
                  Buzzer.turnOn();
                  delay(50);
                  Buzzer.turnOff();
                  delay(50);
            }
            
            Tras();


        
            // caso tenha parede, ele se alinha na parede
           if (norte == 1) {
                quadradonegro = NORTE; // NORTE 
                
              }
                         
                         
                         if (leste == 1) {
                quadradonegro = NORTE; // NORTE 
                
              }

                         if (sul == 1) {
                quadradonegro = SUL; // NORTE 
                
              }
                         if (oeste == 1) {
                quadradonegro = NORTE; // NORTE 
                
              }
              
              


             
            pararMotores();
            
            

            
          /* if(lerSharp(2) <= distancia_parede) {
              Esquerda();
              
           }
           else if (lerSharp(4) <= distancia_parede) {
            Direita();
           }*/
            
        } else {
          delay(2000);
          // se for vitima, ela dropa vitima
          if(verificarVitima() > 0) {
            Vitima(verificarVitima());
          }
      
          
          if (verificarEncruzilhada() == true) {
      
            // VerificarEncruzilhadas
      
              // se tiver mais que um caminho
             
          } else {
      
             // se nao for encruzilhada
      
            if(sistemaFechado() == true) {
      
               // VoltarUltimaEncruzilhada();
      
               // se tiver 3 paredes ao redor e o outro ja foi visitado
               LED2.turnOn();
               delay(100);
               LED2.turnOff();

                if(lerSharp(1) < distancia_parede) {
                  
                 // se tiver duas paredes e os quadrados em volta ja foram visitados
                 while(lerSharp(1) > 7) {
                  mover(forca, forca);
                 }
                 delay(200);
                 pararMotores();
                 while(lerSharp(1) < 13) {
                  mover(forca_Baixa * -1, forca_Baixa * -1);
                 }
                 pararMotores();
                }
               mover(forca, forca * -1);
               delay(1800);
               
               //CurvaGyro(170, forca);
                pararMotores();
                if(lerSharp(3) < distancia_parede) {
                      while(lerSharp(3) > 7) {
                      mover(forca * -1, forca * -1);
                     }
                     delay(600);
                     pararMotores();
                     while(lerSharp(3) < 13) {
                      mover(forca_Baixa, forca_Baixa);
                     }
                }
               pararMotores();
               if(norte == 1) {
                     norte = 0; leste = 0; sul = 1; oeste = 0;
               } else if (sul == 1){
                     norte = 1; leste = 0; sul = 0; oeste = 0;
               } else if (leste == 1) {
                     norte = 0; leste = 0; sul = 0; oeste = 1;
               } else if(oeste == 1) {
                     norte = 0; leste = 1; sul = 0; oeste = 0;
               }
               Frente();
               
      
            } else {


              LED1.turnOff();
                // se nao estiver num sistema fechado
                if (norte == 1) {
                  // verifica se tem parede, se ja passou e se nao tem black space
                  if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarBlackSpaceAoRedor(LESTE) == false) {
                    Direita();
                    norte = 0; leste = 1; sul = 0; oeste = 0;
                  }
                  else if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarBlackSpaceAoRedor(NORTE) == false) {
                    Frente();
                    norte = 1; leste = 0; sul = 0; oeste = 0; 
                  }
                  else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarBlackSpaceAoRedor(OESTE) == false) {
                    Esquerda();
                    norte = 0; leste = 0; sul = 0; oeste = 1;
                  }
                  
                }
      
      
                else if (leste == 1) {
                  // verifica se tem parede, se ja passou e se nao tem black space
                  if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarBlackSpaceAoRedor(LESTE) == false) {
                    Direita();
                    norte = 0; leste = 0; sul = 1; oeste = 0;
                  }
                  else if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarBlackSpaceAoRedor(NORTE) == false) {
                    Frente();
                    norte = 0; leste = 1; sul = 0; oeste = 0;
                  }
                  else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarBlackSpaceAoRedor(OESTE) == false) {
                    Esquerda();
                    norte = 1; leste = 0; sul = 0; oeste = 0;
                  }
                  
                }
      
                else if (oeste == 1) {
                  // verifica se tem parede, se ja passou e se nao tem black space
                  if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarBlackSpaceAoRedor(LESTE) == false) {
                    Direita();
                    norte = 1; leste = 0; sul = 0; oeste = 0;
                  }
                  else if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarBlackSpaceAoRedor(NORTE) == false) {
                    Frente();
                    norte = 0; leste = 0; sul = 0; oeste = 1;
                  }
                  else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarBlackSpaceAoRedor(OESTE) == false) {
                    Esquerda();
                    norte = 0; leste = 0; sul = 1; oeste = 0;
                  }
                  
                }
                else if (sul == 1) {
                  // verifica se tem parede, se ja passou e se nao tem black space
                  if(verificarParede(LESTE) == false && verificarCordBlackSpace(xatual + 1, yatual) == false && verificarBlackSpaceAoRedor(LESTE) == false) {
                    Direita();
                    norte = 0; leste = 0; sul = 0; oeste = 1;
                  }
                  else if(verificarParede(NORTE) == false && verificarCordBlackSpace(xatual, yatual + 1) == false && verificarBlackSpaceAoRedor(NORTE) == false) {
                    Frente();
                    norte = 0; leste = 0; sul = 1; oeste = 0;
                  }
                  else if(verificarParede(OESTE) == false && verificarCordBlackSpace(xatual - 1, yatual) == false && verificarBlackSpaceAoRedor(OESTE) == false) {
                    Esquerda();
                    norte = 0; leste = 1; sul = 0; oeste = 0;
                  }
                  
                }
                LED1.turnOn();
                quadradonegro = 0;
            } // termina verifacao do sistema fechado
      
            
          } // termina verificacao encruzilhada
          
        } // termina a verificacao Black Space
  
  } // termina verificaRampa
  coordenadaatual = "";

  //if(andou <= 1) {
  // atualizar coordenadas
   if (norte == 1) {
    coordenadaatual += xatual;
    coordenadaatual += yatual + 1;
   }
   else if (leste == 1) {
    coordenadaatual += xatual + 1;
    coordenadaatual += yatual;
   }
   else if (sul == 1) {
    coordenadaatual += xatual;
    coordenadaatual += yatual - 1;
   }
   else if (oeste == 1) {
    coordenadaatual += xatual - 1;
    coordenadaatual += yatual;
   } 
  //}
    
  /*
    // tomada de acao
        if (checarencruzilhada) // nao se esquecer de contar as coordenadas visitadas
            // salva no array
            if(y+1 == ja foi visitado or y+7)
            // return false
            
            if(x+1 == ja foi visitado)
            // return false
            
            if (x-1 == ja foi visitado)
            // return false
            
            // qual retornar true, ele segue por esse
        
        // se nao for encruzilhada
            if (y+1 == disponivel OR BlackSpace == false)
                // vai para frente
            elseif (x+1 == disponivel OR BlackSpace == false)
                // vai para direita
            elseif(x-1 == disponivel OR BlackSpace == false)
                // vai para esquerda
            else
                // volta para a ultima encruzilhada
        
        
    */
    // salva 
    // salvar os bytes
    // funcao que analisa esse byte e da uma aÃ§Ã£o ao robo

  
  
}


/*
int lastError = 0;

int PID (double kP, double kI, double kD, double tP, int media) {

      int erro = lerTodosQTR() - media;

      //int error = map(media, 0, 7000, -100, 100);

      int nova_media = 0;

      //int desaceleracao = map((error - nova_media), -100, 100, 1, 0);
      
      int P = kP * erro;
      int I = I + (erro * kI);
      int D = kD * (erro - lastError);
      
      int ganho = P+I+D;
      
      lastError = erro;
      
      double motorB = tP + ganho;
      double motorC = tP - ganho;

      mover(motorB, motorC);

      //Serial.println(analogRead(A15));

};
*/

