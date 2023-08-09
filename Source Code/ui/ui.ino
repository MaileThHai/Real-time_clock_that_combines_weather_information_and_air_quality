#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "RTClib.h"

#include <FirebaseESP32.h> 
#include <WiFi.h> 
#include <WiFiClient.h> 

#include "twilio.hpp"

// Values from Twilio (find them on the dashboard)
static const char *account_sid = "ACc81a10ec0612785b23dfd7068d9fd134";
static const char *auth_token = "eb7f4cbc6cca1183e7dcfe46a5dc3432";
// Phone number should start with "+<countrycode>"
static const char *from_number = "+17626759416";
// You choose!
// Phone number should start with "+<countrycode>"
static const char *to_number = "+84975165970";
static const char *message = "Sent from my ESP32 - The Temperature or Air Quality to bad!";

Twilio *twilio;

// Default Threshold Temperature Value
float thresholdTemperature = 35.0;
int thresholdAirQuality = 2000;

#define FIREBASE_HOST "https://realtimeclock-weather-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "HqzqyvT2sTw5rmfzJzGv2tecuFWcrIStUxl7mjZt" 
FirebaseData fbdo;  
#define WIFI_SSID "A12.10" 
#define WIFI_PASSWORD "anhem121" 
// #define WIFI_SSID "Iphone 11" 
// #define WIFI_PASSWORD "12341234" 

#include <DHT.h>
#define DHTPIN 17         // Zur Messung verwendeter Pin, in unserem Fall also Pin 4
#define DHTTYPE DHT11    // DHT 11
DHT dht(DHTPIN, DHTTYPE); 

float temperature, humidity;
int air_quality;

byte Buzzer = 5; 

#include "MQ135.h"
#define SENSOR 32

#define ONE_MINUTE_MS (60 * 1000)
#define ONE_HOUR_MS (60 * 60 * 1000)
#define TWELVE_HOUR_MS (12 * 60 * 60 * 1000)
static uint8_t conv2d(const char *p)
{
  uint8_t v = 0;
  return (10 * (*p - '0')) + (*++p - '0');
}
static unsigned long ms_offset;

RTC_DS1307 rtc;
byte _day, _month, _hour24, _hour12, _minute, _second, _dtw;
int _year;
byte hr24;
char st[2];

/*Change to your screen resolution*/
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp );
}

/*Read the touchpad*/
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    uint16_t touchX = 0, touchY = 0;

    bool touched = tft.getTouch( &touchX, &touchY, 600 ); //false;//

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = screenHeight - touchY; // Thay đổi giá trị touchX thành screenHeight - touchY
        data->point.y = screenWidth - touchX; // Thay đổi giá trị touchY thành touchX
    }
}

void setup()
{
    Serial.begin( 115200 ); /* prepare for possible serial debug */

    rtc.begin();
    dht.begin();
    pinMode(Buzzer, OUTPUT);
    // rtc.adjust(DateTime(2023, 8, 1, 00, 3, 0));    

    GetDateTime();
    ms_offset = ((60 * 60 * _hour24) + (60 * _minute) + _second) * 1000;

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    Serial.print("Connect Wi-Fi"); 
    while (WiFi.status() != WL_CONNECTED) 
    {  
      Serial.print("."); 
      delay(300); 
    } 
    Serial.println(); 
    Serial.print("WiFi IP: "); 
    Serial.println(WiFi.localIP()); 
    Serial.println(); 
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
    Firebase.reconnectWiFi(true); 
    Firebase.setReadTimeout(fbdo, 1000 * 60);
    Firebase.setwriteSizeLimit(fbdo, "tiny");


    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation(0); /* Landscape orientation, flipped */

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/

    disp_drv.hor_res = screenHeight; // Thay đổi giá trị hor_res
    disp_drv.ver_res = screenWidth; // Thay đổi giá trị ver_res

    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );


    ui_init();

    Serial.println( "Setup done" );

    twilio = new Twilio(account_sid, auth_token);
    delay(1000);
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
    
  DisplayDateTime();
  DHT11_DISPLAY();
  MQ135_DISPLAY();
  DHT11_FIREBASE();
  MQ135_FIREBASE();

  // Kiểm tra nhiệt độ và chất lượng không khí
    if (temperature > thresholdTemperature || air_quality > thresholdAirQuality)
    {
        Button_Sound(1);       
        delay(100);
        Button_Sound(0);
        // Gửi tin nhắn SMS
        String response;
        bool success = twilio->send_message(to_number, from_number, message, response);
        if (success)
        {
            Serial.println("Sent message successfully!");
        }
        else
        {
            Serial.println(response);
        }
        delay(60000);
    }

}

void GetDateTime() {
  DateTime now = rtc.now();
  _day = now.day();
  _month = now.month();
  _year = now.year();
  _hour24 = now.hour();
  _minute = now.minute();
  _second = now.second();
  _dtw = now.dayOfTheWeek();
}

void DisplayDateTime(){
  GetDateTime();
    char dow_matrix[7][10] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
    char month_matrix[12][10] = {"DEC", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV"};

    char hour[10];
    char minute[10];
    char second[10];
    char day[10];
    char month[10];
    char year[10];

    itoa(_hour24, hour, 10);
    itoa(_minute, minute, 10);
    itoa(_second, second, 10);
    itoa(_day, day, 10);
    itoa(_month, month, 10);
    itoa(_year, year, 10);

    //Định dạng chuỗi giờ, phút, giây
    sprintf(hour, "%02d", _hour24);
    sprintf(minute, "%02d", _minute);

    lv_label_set_text(ui_hour, hour);
    lv_label_set_text(ui_minute, minute);
    lv_label_set_text(ui_nameday1, dow_matrix[_dtw]);
    lv_label_set_text(ui_date2, day);
    lv_label_set_text(ui_month1, month_matrix[_month]);
    lv_label_set_text(ui_year1, year);

    char dateana_matrix[7][10] = {"SUN", "MON", "TUE", "WED", "THUR", "FRI", "SAT"};
    
    lv_label_set_text(ui_houranalog, hour);
    lv_label_set_text(ui_minanalog, minute);
    lv_label_set_text(ui_namedateAna, dateana_matrix[_dtw]);
    lv_label_set_text(ui_dayana, day);
    lv_label_set_text(ui_namemonthana, month_matrix[_month]);

    unsigned long ms = millis();
    
    unsigned long clock_ms = (ms_offset + ms) % TWELVE_HOUR_MS;
    uint8_t hour_current = clock_ms / ONE_HOUR_MS;
    uint8_t minute_current = (clock_ms % ONE_HOUR_MS) / ONE_MINUTE_MS;
    int16_t angle = (clock_ms % ONE_MINUTE_MS) * 3600 / ONE_MINUTE_MS;
    lv_img_set_angle(ui_clocksec, angle);
    angle = (angle + (minute_current * 3600)) / 60;
    lv_img_set_angle(ui_clockmin, angle);
    angle = (angle + (hour_current * 3600)) / 12;
    lv_img_set_angle(ui_clockhour, angle);

}

void DHT11_DISPLAY()
{
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  char temp[10];
  char hum[10];
  itoa(temperature, temp, 10);
  itoa(humidity, hum, 10);

  lv_label_set_text(ui_temp1, temp);
  lv_label_set_text(ui_humm, hum);
}

void MQ135_DISPLAY() {
  static unsigned long previousTime = 0;
  unsigned long currentTime = millis();
  unsigned long delayTime = 5000; // Khoảng thời gian delay 5000ms

  if (currentTime - previousTime >= delayTime) {
    previousTime = currentTime;

    MQ135 gasSensor = MQ135(SENSOR);
    air_quality = gasSensor.getPPM();

     char airq[10];
    itoa(air_quality, airq, 10);

    lv_label_set_text(ui_ppm, airq);
  }
}

void DHT11_FIREBASE(){
  static unsigned long previousTime = 0;
  unsigned long currentTime = millis();
  unsigned long delayTime = 60000; // Khoảng thời gian delay 60000ms
  if (currentTime - previousTime >= delayTime) {
    previousTime = currentTime;
  // Read temperature and humidity from DHT11 sensor
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Firebase.setFloat(fbdo, "/realtimeclock-weather/R_Temperature", temperature);
  Firebase.setFloat(fbdo, "/realtimeclock-weather/R_Humidity", humidity); 
  }
}
void MQ135_FIREBASE(){
  static unsigned long previousTime = 0;
  unsigned long currentTime = millis();
  unsigned long delayTime = 60000; // Khoảng thời gian delay 60000ms

  if (currentTime - previousTime >= delayTime) {
    previousTime = currentTime;

    MQ135 gasSensor = MQ135(SENSOR);
    air_quality = gasSensor.getPPM();
    Firebase.setDouble(fbdo, "/realtimeclock-weather/R_AirQuality", air_quality); 
  }
}

void Button_Sound(byte snd) {
  digitalWrite(Buzzer, snd);
}
