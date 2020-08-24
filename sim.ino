#define SIM_LEN 64
char simCmdChr[SIM_LEN];
String simRespStr = const_str_empty;

Stream* simSerial;

void simSetup() {
  SoftwareSerial* ss = new SoftwareSerial(WEMOS_D2, WEMOS_D1); // RX, TX
  ss->begin(9600);
  ss->enableIntTx(false);
  simSerial = ss;
}

void simLoop() {
  String cmd = srCmd();
  if (cmd.startsWith(const_str_at)) {
    Serial.print("SIM req: ");
    Serial.print(cmd);
    Serial.print(const_str_nr);
    simSerial->print(cmd);
    simSerial->print(const_str_nr);
  }

  if (cmd.startsWith(const_str_sms)) {
    simSendSms(cmd.substring(3));
  }
  // Читаем ответ модуля
  int i = 0;
  while (simSerial->available()) {
    simCmdChr[i++] = simSerial->read();
    if (i >= SIM_LEN - 1) {
      break;
    }
  }
  simCmdChr[i] = '\0';
  if (i > 0) {
    simRespStr = String(simCmdChr);
    Serial.print("SIM resp: ");
    Serial.println(simRespStr);
  } else {
    simRespStr = const_str_empty;
  }
}

void simSendSms(String sms) {
  simSerial->print("AT+CMGF=1");
  simSerial->print(const_str_nr);
  simSerial->print("AT+CMGS=\"");
  simSerial->print(configSimPhone);
  simSerial->print("\"");
  simSerial->print(const_str_nr);
  simSerial->print(sms);
  simSerial->write(26);
}

String simResp() {
  return simRespStr;
}
