#include "GaussianNoise.h"

RF24 radio(CE_PIN, CSN_PIN);

// Function to generate Gaussian noise
double Gaussian::randomGaussian() {
  double u1, u2, v1, v2, s;
  do {
    u1 = 2.0 * random(0, RAND_MAX) / RAND_MAX - 1.0;
    u2 = 2.0 * random(0, RAND_MAX) / RAND_MAX - 1.0;
    s = u1 * u1 + u2 * u2;
  } while (s >= 1.0 || s == 0.0);
  
  s = sqrt((-2.0 * log(s)) / s);
  v1 = u1 * s;
  v2 = u2 * s;

  return v1; // Return one value (you can return v2 too if needed)
}

void Gaussian::setUp() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);  // Set power level to low
  radio.setDataRate(RF24_250KBPS); // Set data rate to 250kbps
  radio.setChannel(X); // Set the channel 
  radio.openWritingPipe(PIPE); // Set the transmitting pipe address

  Serial.println("Start RF24 Gaussian Noise Transmission");
}

void Gaussian::sendNoise() {
  const int buffer_size = 32; // Buffer size to store noise values
  double noise[buffer_size];

  // Generating Gaussian noise
  for (int i = 0; i < buffer_size; ++i) {
    noise[i] = randomGaussian(); // Filling the buffer with Gaussian noise values
  }

  // Sending generated noise
  for (int i = 0; i < buffer_size; ++i) {
    radio.write(&noise[i], sizeof(noise[i])); // Sending one value at a time
    delay(10); // Delay between transmissions
  }
}