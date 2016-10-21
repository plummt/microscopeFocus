/*
  MotorMove
  This will let a user controll a motor via a serial command
*/

int setPoint;
int potValue;
int difference;
bool moveVar = false;
bool slow;
bool dir;//0 == difference < 0; 1 == difference > 0
int DB = 10;
int slowZone = 50;
//int A0;
String inChar;
// the setup routine runs once when you press reset:


void setup() {
  Serial.begin(9600);
  potValue = 0;  //change this to read from the potentometer
  setPoint = potValue;
}


// the loop routine runs over and over again forever:
void loop() {
  if (Serial.available() > 0) {
    // read incoming serial data:
    inChar = Serial.readString();
    //parseInput(inChar);
    String head = inChar.substring(0, 1);
    String tail = inChar.substring(inChar.length() - 1, inChar.length());
    if ((head == "#") && (tail == "\n")) {
      Serial.println("It had a #");
      String command = inChar.substring(2, 3);

      // PARSE INPUT
      if (command == "A") {
        Serial.println("OK");
      }
      else if (command == "s") { //change the setpoint
        Serial.println("Setting Difference");
        String valueStr = inChar.substring(3);
        setPoint = valueStr.toInt();
        moveMotor();
      }
      else {
        Serial.println(inChar.substring(0, inChar.length() - 1) + "?");
      }
    }
  }
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *  This is the main function of this program.
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
void moveMotor() {
  bool moveing = true;
  while (moveing) {
    difference = setPoint - potValue;
    if (abs(difference) > ((DB / 2))) {
      if (abs(difference) > slowZone) {
        if (moveVar) {
          //Do nothing
        }
        else {//(moveVar) == False
          moveVar = true;
          slow = false;
          dir = (difference > 0);
          //Turn on Motor, with speed == high******
          Serial.println("Working");//This is not truely needed, so long as it responds when it is finished with the movement.
        }
      }
      else { //(abs(difference) < slowZone)
        if (moveVar) {
          if (slow == false) {
            //make the motor move slowly
            slow = true;
          }
        }
        else {//(moveVar) == False
          moveVar = true;
          slow = true;
          dir = (difference > 0);
          //Turn on Motor, with speed == slow******
          Serial.println("Working");//This is not truely needed, so long as it responds when it is finished with the movement.
        }
      }
    }
    else {//(abs(difference) < (.5 * (DB)))
      if (moveVar) {
        //Turn Motor Off*******
        Serial.println(potValue);
        moveing = false;
      }
      else {//(moveVar) == False
        Serial.println(potValue);
        moveing = false;
      }
    }
  }
}














