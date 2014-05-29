int LIGHT_ON = 255;
int LIGHT_OFF = 0;
int MAX_LIGHT = 5; 
int sensorPins[5] = {0,1,2,3,4};     
int shootSignalPins[5] = {7,6,5,9,0};
int hitSignalPins[5]   = {9,8,10,8,9};
int score = 0;
int total = 0;
int spd = 250;
void setup(void) {
	Serial.begin(9600);   
}
 
void printScore(){
	Serial.print("Current score = ");
	Serial.print(score); 
	Serial.print(" / ");
	Serial.println(total); 
}

void loop(void) {
	// Randomly select a light
	int newLight = random(0,3);
	total = total + 1;
	// Turn all other light off
	for (int i = 0; i < MAX_LIGHT; i++){
		analogWrite(shootSignalPins[i], LIGHT_OFF);
        	analogWrite(hitSignalPins[i], LIGHT_OFF);
	}
	delay(500);
//     	Serial.print("new light = ");
  //      Serial.println(newLight);
	// Turn on the target
	analogWrite(shootSignalPins[newLight], LIGHT_ON);
	int count = 0;
	// three second 
	while (count < spd){
		int sensorReading = analogRead(sensorPins[newLight]);
          	//Serial.print("sensor reading = ");
            //    Serial.println(sensorReading);
		if (sensorReading > 1000){
			// Hit
			score = score + 1;
			analogWrite(hitSignalPins[newLight], LIGHT_ON);
			analogWrite(shootSignalPins[newLight], LIGHT_OFF);
                        //spd = spd - 100;
			delay(1000);
			break;
		}
		count = count + 1;		
		delay(1);
	}
	printScore();
}
