/**
 * VÍ DỤ 2-1a: KIỂM TRA PHÂN HỆ NGUỒN BẰNG GPIO THUẦN (ADC)
 */
#include <Arduino.h>

#define BATTERY_PIN 34 // Pin ADC đo điện áp
#define V_REF 3.3f
#define R1 1200.0 // 1.2k ohm
#define R2 1200.0 // 1.2k ohm

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }

    Serial.println("\n[EXAMPLE] Bắt đầu bài test Phân hệ Nguồn (EPS)...");
    Serial.println("[EPS] Initializing Power System...");
    pinMode(BATTERY_PIN, INPUT);
    Serial.println("[EPS] Battery voltage measurement using ADC (GPIO34).");
    Serial.println("[EXAMPLE] Bắt đầu đọc điện áp Pin liên tục...\n");
}

void loop() {
    int adc = analogRead(BATTERY_PIN);
    float v_pin = (adc / 4095.0f) * V_REF;
    float voltage = v_pin * ((R1 + R2) / R2);

    String logString = "[Uptime: " + String(millis() / 1000) + "s] ";
    logString += "Battery Voltage: " + String(voltage, 2) + "V";
    Serial.println(logString);

    if (voltage < 3.2 && voltage > 1.0) {
        Serial.println(" ---> [WARNING] Điện áp pin quá thấp. Hệ thống nên chuyển sang chế độ tiết kiệm pin!");
    } else if (voltage > 4.1) {
        Serial.println(" ---> [INFO] Pin đầy.");
    }

    delay(2000);
}

