#include <Contact.h>
#include <Relay.h>
#include <CnC.h>

const char nodeName[] PROGMEM = "safety";
const char sepName[] PROGMEM = " ";
const char hkName[] PROGMEM = "hk";
const char cmdGetName[] PROGMEM = "get";
const char cmdSetName[] PROGMEM = "set";

const char pingName[] PROGMEM = "ping";
const char moveCoridorContactName[] PROGMEM = "moveCoridorContact";
const char moveCoridorNotUsedContactName[] PROGMEM = "moveCoridorNotUsedContact";
const char moveDiningContactName[] PROGMEM = "moveDiningContact";
const char moveDiningNotUsedContactName[] PROGMEM = "moveDiningNotUsedContact";
const char moveEntryContactName[] PROGMEM = "moveEntryContact";
const char moveEntryNotUsedContactName[] PROGMEM = "moveEntryNotUsedContact";
const char moveSpareContactName[] PROGMEM = "moveSpareContact";
const char moveSpareNotUsedContactName[] PROGMEM = "moveSpareNotUsedContact";
const char moveRelayName[] PROGMEM = "moveRelay";
const char out0RelayName[] PROGMEM = "out0Relay";
const char out1RelayName[] PROGMEM = "out1Relay";
const char out2RelayName[] PROGMEM = "out2Relay";
const char out3RelayName[] PROGMEM = "out3Relay";
const char out4RelayName[] PROGMEM = "out4Relay";

Contact moveCoridorContact(moveCoridorContactName, 12);
Contact moveCoridorNotUsedContact(moveCoridorNotUsedContactName, 11);
Contact moveDiningContact(moveDiningContactName, 10);
Contact moveDiningNotUsedContact(moveDiningNotUsedContactName, 9);
Contact moveEntryContact(moveEntryContactName, A1);
Contact moveEntryNotUsedContact(moveEntryNotUsedContactName, A0);
Contact moveSpareContact(moveSpareContactName, A3);
Contact moveSpareNotUsedContact(moveSpareNotUsedContactName, A2);
Relay moveRelay(moveRelayName, 13);
Relay out0Relay(out0RelayName, 3);
Relay out1Relay(out1RelayName, 4);
Relay out2Relay(out2RelayName, 5);
Relay out3Relay(out3RelayName, 6);
Relay out4Relay(out4RelayName, 7);

static uint32_t loopNb = 0;

void ping_cmdGet(int arg_cnt, char **args) { cnc_print_cmdGet_u32(pingName, loopNb); }
void moveCoridorContact_cmdGet(int arg_cnt, char **args) { moveCoridorContact.cmdGet(arg_cnt, args); }
void moveDiningContact_cmdGet(int arg_cnt, char **args) { moveDiningContact.cmdGet(arg_cnt, args); }
void moveEntryContact_cmdGet(int arg_cnt, char **args) { moveEntryContact.cmdGet(arg_cnt, args); }
void moveRelay_cmdGet(int arg_cnt, char **args) { moveRelay.cmdGet(arg_cnt, args); }
void moveRelay_cmdSet(int arg_cnt, char **args) { moveRelay.cmdSet(arg_cnt, args); }
void out0Relay_cmdGet(int arg_cnt, char **args) { out0Relay.cmdGet(arg_cnt, args); }
void out0Relay_cmdSet(int arg_cnt, char **args) { out0Relay.cmdSet(arg_cnt, args); }
void out1Relay_cmdGet(int arg_cnt, char **args) { out1Relay.cmdGet(arg_cnt, args); }
void out1Relay_cmdSet(int arg_cnt, char **args) { out1Relay.cmdSet(arg_cnt, args); }
void out2Relay_cmdGet(int arg_cnt, char **args) { out2Relay.cmdGet(arg_cnt, args); }
void out2Relay_cmdSet(int arg_cnt, char **args) { out2Relay.cmdSet(arg_cnt, args); }
void out3Relay_cmdGet(int arg_cnt, char **args) { out3Relay.cmdGet(arg_cnt, args); }
void out3Relay_cmdSet(int arg_cnt, char **args) { out3Relay.cmdSet(arg_cnt, args); }
void out4Relay_cmdGet(int arg_cnt, char **args) { out4Relay.cmdGet(arg_cnt, args); }
void out4Relay_cmdSet(int arg_cnt, char **args) { out4Relay.cmdSet(arg_cnt, args); }

void setup() {
  Serial.begin(115200);
  cncInit(nodeName);
  cnc_hkName_set(hkName);
  cnc_cmdGetName_set(cmdGetName);
  cnc_cmdSetName_set(cmdSetName);
  cnc_sepName_set(sepName);
  cnc_cmdGet_Add(pingName, ping_cmdGet);
  cnc_cmdGet_Add(moveCoridorContactName , moveCoridorContact_cmdGet);
  cnc_cmdGet_Add(moveDiningContactName, moveDiningContact_cmdGet);
  cnc_cmdGet_Add(moveEntryContactName, moveEntryContact_cmdGet);
  cnc_cmdSet_Add(moveRelayName, moveRelay_cmdGet);
  cnc_cmdSet_Add(moveRelayName, moveRelay_cmdSet);
  cnc_cmdSet_Add(out0RelayName, out0Relay_cmdGet);
  cnc_cmdSet_Add(out0RelayName, out0Relay_cmdSet);
  cnc_cmdSet_Add(out1RelayName, out1Relay_cmdGet);
  cnc_cmdSet_Add(out1RelayName, out1Relay_cmdSet);
  cnc_cmdSet_Add(out2RelayName, out2Relay_cmdGet);
  cnc_cmdSet_Add(out2RelayName, out2Relay_cmdSet);
  cnc_cmdSet_Add(out3RelayName, out3Relay_cmdGet);
  cnc_cmdSet_Add(out3RelayName, out3Relay_cmdSet);
  cnc_cmdSet_Add(out4RelayName, out4Relay_cmdGet);
  cnc_cmdSet_Add(out4RelayName, out4Relay_cmdSet);
  moveRelay.open();
  out0Relay.open();
  out1Relay.open();
  out2Relay.open();
  out3Relay.open();
  out4Relay.open();
}

void loop() {
  delay(1);
  moveRelay.run(false);
  out0Relay.run(false);
  out1Relay.run(false);
  out2Relay.run(false);
  out3Relay.run(false);
  out4Relay.run(false);

  /* HK @ 1Hz */
  if(0 == loopNb%1000) {
    moveCoridorContact.run(true);
    moveDiningContact.run(true);
    moveEntryContact.run(true);
  }
  cncPoll();
  loopNb++;
  if(1000000000 <= loopNb) { loopNb = 0; }
}

