# Programming a line following Robot
Today we are going to program a 4 wheel drive skid steering robot to follow a black line painted over a white floor. A skid steer robot is a robot that has 4 wheels that are driven, it can go forwards and backwards and left and right. When steering, the robot 'slides' due to the wheels moving at different speeds, therefore skidding.



The robot has three downward facing sensors. The sensors are made out of an infrared light and a infra red receiver. To detect the line the robot shines the IR light and then measures the reflection from the floor. A white floor is going to be highly reflective, while a black floor will reflect very little or nothing at all.

The robot also has three lights at the front that can produce many colours. This lights are called RGB LEDs which means that they are Light Emitting Diodes that produce Red, Green and Blue lights. The combination of this three colours can create almost any colour.

## Using the RGB LEDs

```
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      3
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
```
Inside `setup()` we need to tell the microcontroller the pin that the LEDs are connected
`pinMode(8, OUTPUT);`

### Setting the colours of the LEDs

`pixels.setPixelColor(0,pixels.Color(0,0,0));` this command turns off the first LED
`pixels.setPixelColor(1,pixels.Color(100,0,0));` this command turns RED the second LED
`pixels.setPixelColor(2,pixels.Color(0,100,0));` this command turns GREEN the third LED
`pixels.show();` This command applies the desired colour to all the LEDs

What variable selects the LED? How Can we turn the first LED Blue?

To set all three sensors to the same colour, we can iterate though them with the following `for` loop:
```
  for(int i=0;i<3;i++){
      pixels.setPixelColor(i,pixels.Color(0,0,0));
      pixels.show();   
  } 
  ```

## Reading the sensors

Reading the line sensors is quite straight forward. Beacuse they are connected to an analog input we just need to use the command `analogRead(A0)` to read the first sensor. We can replace `A0` with `A1` or `A2` if we want to read either the second or third sensor.
We can store the value of the sensor in memory if we assign thje value that we read to a variable like this:
`int sensor_1_value = analogRead(A0)`
This will allow us to use the value later on in the code.

## Logic statements
In programming we make use of logic statements to thell the microcontroller what to do depending on the data available. In our case we want to tell it to do move it depending on the readings from the line sensors.
```
if(valuee > another_value){
  //This happens
}
else{
  //This happens
}
```
## Moving the motors
```
ctrlCar(FORWARD,120);
ctrlCar(BACKWARD,120);
ctrlCar(RIGHT,120);
ctrlCar(LEFT,120);
ctrlCar(STOP,0);
```
