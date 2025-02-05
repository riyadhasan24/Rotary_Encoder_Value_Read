/* The source Code from : https://github.com/riyadhasan24
 * By Md. Riyad Hasan
 */
 
#define CLK 2  // Clock Pin (A) / (CLOCK)
#define DT 3   // Data Pin (B) / (DATA)

volatile int Encoder_Value = 0;  // Holds encoder count
int Last_State_CLK;

int State_DT = digitalRead(DT);
int State_CLK = digitalRead(CLK);


void setup() 
{
  Serial.begin(9600);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
    
  Last_State_CLK = digitalRead(CLK);  // Read initial state

  // Attach interrupt on CLK pin
  attachInterrupt(digitalPinToInterrupt(CLK), Read_Encoder, CHANGE);
}

void loop() 
{
  Serial.println(Encoder_Value);  // Print encoder count
  delay(100);
}

// Interrupt Service Routine (ISR)
void Read_Encoder() 
{
  // Check rotation direction
  if (State_CLK != Last_State_CLK) 
  {  
    if (State_DT != State_CLK) 
    {
      Encoder_Value++;  // Clockwise → Increase
    } 
    else 
    {
      if (Encoder_Value > 0) 
      {  
        Encoder_Value--;  // Counterclockwise → Decrease only if > 0
      }
    }
  }
  Last_State_CLK = State_CLK;  // Update last state
}

