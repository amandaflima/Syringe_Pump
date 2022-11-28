const int DIR = 8;
const int STEP = 9;
float comp_por_ml = 0;
float passos = 0;
int passos_arredondado = 0;
int pino_enable = 11;
int numero = 0;
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

bool mensagemVolSeringaExibida = false;
bool volSeringaDigitada = false;
float vol_seringa = 0;


void setup() {
  Serial.begin(9600);
  pinMode(pino_enable, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void loop() {

  inputDensidadeLiquido();

  if (densidadeLiquidoDigitada) {
    inputMassa();
  }

  if (massaDigitada) {
    inputCompSeringa();
  }

  if (compSeringaDigitada) {
    inputVolSeringa();
  }

  if (volSeringaDigitada) {
    Serial.println("fim");
    //Calculos
    volume_liquido = massa_saida / densidade;
    comp_por_ml = comp_seringa / vol_seringa;
    passos = (comp_por_ml * 200 * volume_liquido) / 2;  //se não der certo testar 1600*comp_por_ml
    passos_arredondado = round(passos);

    digitalWrite(DIR, LOW);

    //Realiza uma volta completa
    for (int i = 0; i < passos_arredondado; i++) {
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




void inputDensidadeLiquido() {
  if (mensagemDensidadeExibida == false)  //Se ainda não tiver exibido a mensagem, exibe
  {
    Serial.println("Digite a densidade do liquido: ");
    mensagemDensidadeExibida = true;
  }

  if (densidadeLiquidoDigitada == true)  //Se ja tiver sido digitada a mensagem , sai da função
  {
    return;
  }

  if (Serial.available() > 0) {

    densidade = Serial.parseFloat();
    densidadeLiquidoDigitada = true;

    Serial.println("Densidade do liquido digitada = " + String(densidade));
  }
}


void inputMassa() {

  if (mensagemMassaExibida == false) {
    Serial.println("\nDigite massa de saida desejado: ");
    mensagemMassaExibida = true;
  }

  if (massaDigitada) {
    return;
  }

  if (Serial.available() > 0) {
    massa_saida = Serial.parseFloat();
    massaDigitada = true;

    Serial.println("Massa de saida digitada = " + String(massa_saida));
  }
}

void inputCompSeringa() {

  if (mensagemCompSeringaExibida == false) {
    Serial.println("\nDigite o comprimento da seringa: ");
    mensagemCompSeringaExibida = true;
  }

  if (compSeringaDigitada) {
    return;
  }

  if (Serial.available() > 0) {
    comp_seringa = Serial.parseFloat();
    compSeringaDigitada = true;

    Serial.println("Comprimento da seringa digitada = " + String(comp_seringa));
  }
}

void inputVolSeringa() {

  if (mensagemVolSeringaExibida == false) {
    Serial.println("\nDigite o volume da seringa: ");
    mensagemVolSeringaExibida = true;
  }

  if (volSeringaDigitada) {
    return;
  }

  if (Serial.available() > 0) {
    vol_seringa = Serial.parseFloat();
    volSeringaDigitada = true;

    Serial.println("Volume da seringa digitada = " + String(vol_seringa));
  }
}

void limparTudo() {
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
}
