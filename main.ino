const int DIR   = 8;
const int STEP  = 9;
float comp_por_ml = 0;
float passos = 0;
int passos_arredondado = 0;
int pino_enable = 11;

float volume_liquido = 0;

bool mensagemDensidadeExibida = false;
bool densidadeLiquidoDigitada = false;
float densidade = 0;

bool mensagemMassaExibida = false;
bool massaDigitada = false;
float massa_saida = 0;

bool mensagemCompSeringaExibida = false;
bool compSeringaDigitada = false;
float comp_seringa = 0;

bool mensagem_numero = false;
bool numeroDigitado = false;
int numero = 0;

bool mensagemVolSeringaExibida = false;
bool volSeringaDigitada = false;
float vol_seringa = 0;


void setup()
{
  Serial.begin(9600); //Comunicação com o serial monitor
  pinMode(pino_enable, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void loop()
{
  //Input de valores
  inputDensidadeLiquido();

  if (densidadeLiquidoDigitada)
  {
    inputMassa();
  }

  if (massaDigitada)
  {
    inputCompSeringa();
  }

  if (compSeringaDigitada)
  {
    inputVolSeringa();
  }

  if (volSeringaDigitada)
  {
    input_numero();
  }

  if (numeroDigitado) {
    if (numero == 1) { //Para girar no sentido anti-horário

      //Calculos
      volume_liquido = massa_saida / densidade;
      comp_por_ml = comp_seringa / vol_seringa;
      passos = (comp_por_ml * 200 * volume_liquido) / 2;
      passos_arredondado = round(passos);

      Serial.println("Número de passos: ");
      Serial.print(passos_arredondado);
      Serial.println(" ");


      digitalWrite(DIR, LOW);

      //Realiza a quantidade de voltas necessárias para injetar o volume desejado
      for (int i = 0; i < passos_arredondado; i++)
      {
        //Realiza um Passo
        digitalWrite(STEP, HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP, LOW);
        delayMicroseconds(500);
      }

      delay(1000);
      limparTudo(); //zera as variáveis para entrar no looping novamente
    }

    else if (numero == 2) { //Para girar no sentido horário

      //Calculos
      volume_liquido = massa_saida / densidade;
      comp_por_ml = comp_seringa / vol_seringa;
      passos = (comp_por_ml * 200 * volume_liquido) / 2;
      passos_arredondado = round(passos);


      digitalWrite(DIR, HIGH);

      //Realiza uma volta completa
      for (int i = 0; i < passos_arredondado; i++)
      {
        //Realiza um Passo
        digitalWrite(STEP, HIGH);
        delayMicroseconds(500);
        digitalWrite(STEP, LOW);
        delayMicroseconds(500);
      }

      delay(1000);
      limparTudo();

    }

  }

}



//Funções para inserir os valores no monitor serial
void inputDensidadeLiquido()
{
  if (mensagemDensidadeExibida == false) //Se ainda não tiver exibido a mensagem, exibe
  {
    Serial.println("Digite a densidade do liquido (g/ml): ");
    delay(5000);
    mensagemDensidadeExibida = true;
  }

  if (densidadeLiquidoDigitada == true) //Se ja tiver sido digitada a mensagem , sai da função
  {
    return;
  }

  if (Serial.available() > 0)
  {

    densidade = Serial.parseFloat();
    densidadeLiquidoDigitada = true;

    Serial.println("Densidade do liquido digitada = " + String(densidade));
  }
}


void inputMassa()
{

  if (mensagemMassaExibida == false)
  {
    Serial.println("\nDigite massa de saida desejado: ");
    delay(5000);
    mensagemMassaExibida = true;
  }

  if (massaDigitada)
  {
    return;
  }

  if (Serial.available() > 0)
  {
    massa_saida = Serial.parseFloat();
    massaDigitada = true;

    Serial.println("Massa de saida digitada = " + String(massa_saida));
  }

}

void inputCompSeringa()
{

  if (mensagemCompSeringaExibida == false)
  {
    Serial.println("\nDigite o comprimento da seringa: \n 90.0mm/60ml  \n 70.5mm/20ml \n 44.5mm/5ml \n 51.7mm/3ml \n 51.1mm/0.5ml\n 41.2mm/0.3ml \n ");
    delay(10000);
    mensagemCompSeringaExibida = true;
  }

  if (compSeringaDigitada)
  {
    return;
  }

  if (Serial.available() > 0)
  {
    comp_seringa = Serial.parseFloat();
    compSeringaDigitada = true;

    Serial.println("Comprimento da seringa digitada = " + String(comp_seringa));
  }

}

void inputVolSeringa()
{

  if (mensagemVolSeringaExibida == false)
  {
    Serial.println("\nDigite o volume da seringa: \n 90.0mm/60ml  \n 70.5mm/20ml \n 44.5mm/5ml \n 51.7mm/3ml \n 51.1mm/0.5ml \n 41.2mm/0.3ml");
    delay(10000);
    mensagemVolSeringaExibida = true;
  }

  if (volSeringaDigitada)
  {
    return;
  }

  if (Serial.available() > 0)
  {
    vol_seringa = Serial.parseFloat();
    volSeringaDigitada = true;

    Serial.println("Volume da seringa digitada = " + String(vol_seringa));
  }

}

void input_numero()
{

  if (mensagem_numero == false)
  {
    Serial.println("\nDigite 1 para girar no sentido anti-horário ou 2 para o sentido horário: ");
    delay(5000);
    mensagem_numero = true;
  }

  if (numeroDigitado)
  {
    return;
  }

  if (Serial.available() > 0)
  {
    numero = Serial.parseFloat();
    numeroDigitado = true;

    Serial.println("girando" );
  }

}

//Função para resetar as variáveis
void limparTudo()
{
  mensagemDensidadeExibida = false;
  densidadeLiquidoDigitada = false;
  densidade = 0;

  mensagemMassaExibida = false;
  massaDigitada = false;
  massa_saida = 0;

  mensagemCompSeringaExibida = false;
  compSeringaDigitada = false;
  comp_seringa = 0;

  mensagemVolSeringaExibida = false;
  volSeringaDigitada = false;
  vol_seringa = 0;

  mensagem_numero = false;
  numeroDigitado = false;
  numero = 0;


}
