#include <SPI.h>

// XIAO nRF52840 pinout

// HV513 
//   LE   -> D1
//   CLK  -> D5
//   DIN  -> D3

#define HV_LE    D1
#define HV_CLK   D5
#define HV_DIN   D3

// MCP41050 (hardware SPI)
//   SCK  -> D8
//   CS   -> D9
//   SI   -> D10

#define MCP_SCK  D8
#define MCP_CS   D9
#define MCP_SI   D10

const uint32_t SPI_HZ = 1000000;
const uint32_t HV_STEP_DELAY_MS = 1000;

// HV513 test output pattern:
// HVOUT8 -> HVOUT6 -> HVOUT3 -> HVOUT1 -> HVOUT3 -> HVOUT6 -> repeat
const uint8_t SEQ[] = {
  0x80, // HVOUT8
  0x20, // HVOUT6
  0x04, // HVOUT3
  0x01, // HVOUT1
  0x04, // HVOUT3
  0x20  // HVOUT6
};

const size_t SEQ_LEN = sizeof(SEQ) / sizeof(SEQ[0]);

uint8_t hvState = 0x00;

// Write raw input to potentiometer via SPI
void potWriteRaw(uint8_t rawValue) {
  const uint8_t CMD_WRITE_POT0 = 0x11;

  digitalWrite(MCP_CS, LOW);
  SPI.beginTransaction(SPISettings(SPI_HZ, MSBFIRST, SPI_MODE0));
  SPI.transfer(CMD_WRITE_POT0);
  SPI.transfer(rawValue);
  SPI.endTransaction();
  digitalWrite(MCP_CS, HIGH);
}

// Converts target voltage input to raw potentiometer 255 to 0 value, sent to the pot
// note 255 is minimum resistance (0 Ohms), 0 is maximum (50 kOhms ideal) 
uint8_t voltageToPotRaw(float targetVoltage) {
  const float R2 = 1620000.0f;
  const float R1_FIXED = 8200.0f;
  const float RPOT_MAX = 50000.0f;

  if (targetVoltage < 43.25f) targetVoltage = 43.25f;
  if (targetVoltage > 297.84f) targetVoltage = 297.84f;

  float denominator = (targetVoltage / 1.5f) - 1.0f;
  float R1 = R2 / denominator;
  float Rpot = R1 - R1_FIXED;

  if (Rpot < 0.0f) Rpot = 0.0f;
  if (Rpot > RPOT_MAX) Rpot = RPOT_MAX;

  float rawFloat = 255.0f - (255.0f * Rpot / RPOT_MAX);
  int rawInt = (int)(rawFloat + 0.5f);

  if (rawInt < 0) rawInt = 0;
  if (rawInt > 255) rawInt = 255;

  return (uint8_t)rawInt;
}

// Function wrapper
void potWriteVoltage(float targetVoltage) {
  potWriteRaw(voltageToPotRaw(targetVoltage));
}

void hvLatch() {
  digitalWrite(HV_LE, HIGH);
  delayMicroseconds(1);
  digitalWrite(HV_LE, LOW);
}

void writeHVState() {
  for (int bitIndex = 7; bitIndex >= 0; bitIndex--) {
    digitalWrite(HV_CLK, LOW);
    digitalWrite(HV_DIN, (hvState >> bitIndex) & 0x01);
    delayMicroseconds(1);
    digitalWrite(HV_CLK, HIGH);
    delayMicroseconds(1);
  }

  digitalWrite(HV_CLK, LOW);
  hvLatch();
}

void clearAllOutputs() {
  hvState = 0x00;
  writeHVState();
}

// Write HVOUT high for HV513
void setOutputHigh(uint8_t outputNumber) {
  if (outputNumber < 1 || outputNumber > 8) return;
  hvState |= (1 << (outputNumber - 1));
  writeHVState();
}

// Write HVOUT low for HV513
void setOutputLow(uint8_t outputNumber) {
  if (outputNumber < 1 || outputNumber > 8) return;
  hvState &= ~(1 << (outputNumber - 1));
  writeHVState();
}

void setup() {
  pinMode(HV_LE, OUTPUT);
  pinMode(HV_CLK, OUTPUT);
  pinMode(HV_DIN, OUTPUT);

  digitalWrite(HV_LE, LOW);
  digitalWrite(HV_CLK, LOW);
  digitalWrite(HV_DIN, LOW);

  pinMode(MCP_CS, OUTPUT);
  digitalWrite(MCP_CS, HIGH);

  // Hardware SPI uses MCP_SCK (D8) and MCP_SI (D10)
  SPI.begin();

  clearAllOutputs();

  // raw 255 = minimum pot resistance = maximum output voltage
  potWriteRaw(255);

  // Example:
  // potWriteVoltage(250.0f);
  // setOutputHigh(1);
  // setOutputLow(1);
}

void loop() {
  static size_t idx = 0;

  hvState = SEQ[idx];
  writeHVState();

  delay(HV_STEP_DELAY_MS);

  idx++;
  if (idx >= SEQ_LEN) idx = 0;
}