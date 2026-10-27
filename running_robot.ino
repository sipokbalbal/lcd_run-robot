#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C LCD: 주소 0x27, 16칸 × 2줄
LiquidCrystal_I2C lcd(0x27, 16, 2);

// 로봇 애니메이션: 5×8 픽셀, 8프레임
byte robot[8][8] = {
  {
    B01110,
    B01010,
    B01110,
    B10101,
    B01110,
    B00100,
    B01010,
    B10001
  },
  {
    B01110,
    B01010,
    B01110,
    B00101,
    B11110,
    B00100,
    B01010,
    B01001
  },
  {
    B01110,
    B01010,
    B11111,
    B01110,
    B00100,
    B00110,
    B01000,
    B00000
  },
  {
    B01110,
    B01010,
    B01110,
    B10100,
    B01111,
    B00100,
    B01010,
    B10010
  },
  {
    B01110,
    B01010,
    B01110,
    B00101,
    B11110,
    B00100,
    B01010,
    B10001
  },
  {
    B01110,
    B01010,
    B01110,
    B10100,
    B01111,
    B00100,
    B01010,
    B01010
  },
  {
    B01110,
    B01010,
    B11111,
    B01110,
    B00100,
    B01100,
    B00010,
    B00000
  },
  {
    B01110,
    B01010,
    B01110,
    B10100,
    B01110,
    B00101,
    B01010,
    B10010
  }
};

const unsigned long frameInterval = 100; // 100ms마다 변경
unsigned long previousMillis = 0;
byte currentFrame = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Custom Character 8개 등록
  for (byte i = 0; i < 8; i++) {
    lcd.createChar(i, robot[i]);
  }

  // 첫째 줄, 첫 번째 칸에 출력
  lcd.setCursor(0, 0);
  lcd.write((uint8_t)currentFrame);

  previousMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= frameInterval) {
    previousMillis = currentMillis;

    // 0~7 프레임 반복
    currentFrame = (currentFrame + 1) % 8;

    // 화면을 지우지 않고 첫 번째 칸만 갱신
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)currentFrame);
  }
}
