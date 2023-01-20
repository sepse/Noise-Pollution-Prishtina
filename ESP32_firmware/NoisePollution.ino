/** 
 * ESP32 I2S Noise Level Example.
 * 
 * This example calculates a mean noise level.
 */

#include <Arduino.h>
#include <driver/i2s.h>
#include "arduinoFFT.h"

#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

int number = 0;

// size of noise sample, originally 1024
#define SAMPLES 1024

const i2s_port_t I2S_PORT = I2S_NUM_0;
const int BLOCK_SIZE = SAMPLES;

#define OCTAVES 9

// our FFT data
static float real[SAMPLES];
static float imag[SAMPLES];
static arduinoFFT fft(real, imag, SAMPLES, SAMPLES);
static float energy[OCTAVES];
// A-weighting curve from 31.5 Hz ... 8000 Hz
static const float aweighting[] = { -39.4, -26.2, -16.1, -8.6, -3.2, 0.0, 1.2, 1.0, -1.1 };

static void print(const char *fmt, ...)
{
    // format it
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    // send it to serial
    Serial.write(buf);
}

static void integerToFloat(int32_t * integer, float *vReal, float *vImag, uint16_t samples)
{
    for (uint16_t i = 0; i < samples; i++) {
        vReal[i] = (integer[i] >> 16) / 10.0;
        vImag[i] = 0.0;
    }
}

// calculates energy from Re and Im parts and places it back in the Re part (Im part is zeroed)
static void calculateEnergy(float *vReal, float *vImag, uint16_t samples)
{
    for (uint16_t i = 0; i < samples; i++) {
        vReal[i] = sq(vReal[i]) + sq(vImag[i]);
        vImag[i] = 0.0;
    }
}

// sums up energy in bins per octave
static void sumEnergy(const float *bins, float *energies, int bin_size, int num_octaves)
{
    // skip the first bin
    int bin = bin_size;
    for (int octave = 0; octave < num_octaves; octave++) {
        float sum = 0.0;
        for (int i = 0; i < bin_size; i++) {
            sum += real[bin++];
        }
        energies[octave] = sum;
        bin_size *= 2;
    }
}

static float decibel(float v)
{
    return 10.0 * log(v) / log(10);
}

// converts energy to logaritmic, returns A-weighted sum
static float calculateLoudness(float *energies, const float *weights, int num_octaves, float scale)
{
    float sum = 0.0;
    for (int i = 0; i < num_octaves; i++) {
        float energy = scale * energies[i];
        sum += energy * pow(10, weights[i] / 10.0);
        energies[i] = decibel(energy);
    }
    return decibel(sum);
}

void setup(void)
{
    Serial.begin(115200);
    Serial.println("Configuring I2S...");
    esp_err_t err;

    WiFi.mode(WIFI_STA); 
    ThingSpeak.begin(client);  // Initialize ThingSpeak

    // The I2S config as per the example
    const i2s_config_t i2s_config = {
        .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),      // Receive, not transfer
        .sample_rate = 22627,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,   // although the SEL config should be left, it seems to transmit on right
        .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,       // Interrupt level 1
        .dma_buf_count = 8,     // number of buffers
        .dma_buf_len = BLOCK_SIZE,      // samples per buffer
        .use_apll = true
    };

    // The pin config as per the setup
    const i2s_pin_config_t pin_config = {
        .bck_io_num = 14,       // SKC
        .ws_io_num = 15,        // WS
        .data_out_num = -1,     // not used (only for speakers)
        .data_in_num = 32       // SD
    };

    // Configuring the I2S driver and pins.
    // This function must be called before any I2S driver read/write operations.
    err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
    if (err != ESP_OK) {
        Serial.printf("Failed installing driver: %d\n", err);
        while (true);
    }
    err = i2s_set_pin(I2S_PORT, &pin_config);
    if (err != ESP_OK) {
        Serial.printf("Failed setting pin: %d\n", err);
        while (true);
    }
    Serial.println("I2S driver installed.");
}

static void print_level(float energy)
{
//    static const unsigned char levels[] = {' ', 0xB0, 0xB1, 0xB2, 0xDB};
    static const unsigned char levels[] = { ' ', '.', 'o', 'O', 'X' };

    int index = (int) (energy / 8) - 1;
    if (index < 0) {
        index = 0;
    }
    if (index > 4) {
        index = 4;
    }
    char c = levels[index];
    print("%c%c%c", c, c, c);
}


void loop(void)
{
    static int32_t samples[BLOCK_SIZE];

    // Read multiple samples at once and calculate the sound pressure
    size_t num_bytes_read;
    esp_err_t err = i2s_read(I2S_PORT,
                             (char *) samples,
                             BLOCK_SIZE,        // the doc says bytes, but its elements.
                             &num_bytes_read,
                             portMAX_DELAY);    // no timeout
    int samples_read = num_bytes_read / 8;

    // integer to float
    integerToFloat(samples, real, imag, SAMPLES);

    // apply flat top window, optimal for energy calculations
    fft.Windowing(FFT_WIN_TYP_FLT_TOP, FFT_FORWARD);
    fft.Compute(FFT_FORWARD);

    // calculate energy in each bin
    calculateEnergy(real, imag, SAMPLES);

    // sum up energy in bin for each octave
    sumEnergy(real, energy, 1, OCTAVES);

    // calculate loudness per octave + A weighted loudness
    float loudness = calculateLoudness(energy, aweighting, OCTAVES, 1.0);

    // show loudness
    for (int i = 0; i < OCTAVES; i++) {
        print_level(energy[i]);
    }
    print(" => %6.1f", loudness);
    print("\n");
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
    }
  
    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    int x = ThingSpeak.writeField(myChannelNumber, 1, loudness, myWriteAPIKey);
    if(x == 200){
    Serial.println("Channel update successful.");
    }
    else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
    delay(20000);
}
