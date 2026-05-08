#include <SPI.h>

// Startup delay before anything happens (milliseconds)
#define STARTUP_DELAY_MS 30000  

// Delay between each HV513 output step (milliseconds)
#define HV_STEP_DELAY_MS 1000   

// MCP41050 potentiometer value (0–255)
// 0   = minimum wiper position
// 255 = maximum wiper position
#define POT_VALUE 255           

// Optional: delay after setting potentiometer (milliseconds)
#define POST_POT_DELAY_MS 2000  

// HV513
#define HV_DIN  MOSI
#define HV_CLK  SCK
#define HV_LE   D5   // latch enable

// MCP41050 digital potentiometer
#define MCP_CS  D9   // chip select

// =========================
// SPI settings
// =========================
const uint32_t SPI_HZ = 1000000;

// =========================
// HV513 sequence
// 8 -> 6 -> 3 -> 1 -> 3 -> 6 -> repeat
// =========================
const uint8_t SEQ[] = {
  0x80, // HVOUT8
  0x20, // HVOUT6
  0x04, // HVOUT3
  0x01, // HVOUT1
  0x04, // HVOUT3
  0x20  // HVOUT6
};
const size_t SEQ_LEN = sizeof(SEQ) / sizeof(SEQ[0]);

// =========================
// MCP41050 write
// =========================
static void mcp41050_write(uint8_t value) {
  const uint8_t CMD_WRITE_POT0 = 0x11;

  digitalWrite(MCP_CS, LOW);

  SPI.beginTransaction(SPISettings(SPI_HZ, MSBFIRST, SPI_MODE0));
  SPI.transfer(CMD_WRITE_POT0);
  SPI.transfer(value);
  SPI.endTransaction();

  digitalWrite(MCP_CS, HIGH);
}

// =========================
// HV513 helpers
// =========================
static inline void hv513_latch() {
  digitalWrite(HV_LE, HIGH);
  delayMicroseconds(1);
  digitalWrite(HV_LE, LOW);
}

static void hv513_writeByte(uint8_t data) {
  // Ensure MCP is not selected
  digitalWrite(MCP_CS, HIGH);

  SPI.beginTransaction(SPISettings(SPI_HZ, MSBFIRST, SPI_MODE0));
  SPI.transfer(data);
  SPI.endTransaction();

  hv513_latch();
}

// =========================
// Init
// =========================
static void initPins() {
  pinMode(HV_LE, OUTPUT);
  digitalWrite(HV_LE, LOW);

  pinMode(MCP_CS, OUTPUT);
  digitalWrite(MCP_CS, HIGH);  // deselect pot

  SPI.begin();
}

// =========================
// Setup
// =========================
void setup() {
  initPins();

  // Start with all HV outputs low
  hv513_writeByte(0x00);

  // 1) Startup delay
  delay(STARTUP_DELAY_MS);

  // 2) Set potentiometer once
  mcp41050_write(POT_VALUE);

  // 3) Wait after setting pot
  delay(POST_POT_DELAY_MS);
}

// =========================
// Loop
// =========================
void loop() {
  static size_t idx = 0;

  hv513_writeByte(SEQ[idx]);
  delay(HV_STEP_DELAY_MS);

  idx++;
  if (idx >= SEQ_LEN) idx = 0;
}