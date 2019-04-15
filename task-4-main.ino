
/*
 * Team Id:2683
 
 * Author List: Ankur,Charvi,Dhawal, Pranav
 
 
 * Filename:bot_traversal.ino
 * Theme: Ant Bot
 * Functions:setup, loop, millis_servo(int), increase(servo, int, int, int), decrease(servo, int, int, int), velocity(int, int)
 * Global Variables: curr_node, supply_taken,speed_right, diff, curr_node, supply_taken, col, req_bl, status_supply, AH_count, service_required[], face_side, supply_center,
 *                   cpos1, cpos2, subt, QAH, data, led_pin, node_count, SIM[], trash_flag, trash_count, block_sequence[], sequence[], service_required[], state, etc. 
 * Macros: enright, righta, rightb, enleft, lefta, leftb, max_left, min_left, max_center, min_center, max_right, min_right, SLAVE_ADDRESS
 * Function Definations: cases(int), right_turn(int, int), left_turn(int, int), start_node(), sensor_data(), bck_node_2_node(int), fwd_node_2_node(int), line_bck(int), supply()
 */
/*----------------------- header file calling of the start here --------------------------------------*/
#include<Wire.h>
#include <Servo.h>

/*----------------------- header  of the end  here --------------------------------------*/


/*###############################################################################################
 #################################################################################################
 -----------------------constant function of the start here --------------------------------------*/

#define enright  11              //enabling pwm pin on right pin
#define righta   4               //enabling right motor on/off  
#define rightb   12              //enabling right motor on/off
#define enleft   3               //enabling pwm pin on left pin
#define lefta    7               //enabling left motor on/off
#define leftb    8               //enabling left motor on/off
#define max_left 500             //defining the max value encounter by the left sensor
#define min_left 20              //defining the min value encounter by the left sensor
#define max_center 500           //defining the max value encounter by the center sensor
#define min_center 20            //defining the min value encounter by the center sensor
#define max_right 450            //defining the max value encounter by the right sensor
#define min_right 20             //defining the min value encounter by the right sensor140 154 
#define SLAVE_ADDRESS 0x08
/*-----------------------     end here                     --------------------------------------*/

int speed_right = 0;   //giving the pwm value for the right sensor   //left = 162, right = 153 
int speed_left = 0 ;//giving the pwm value for the left sensor 
int curr_node = 3;




/*###############################################################################################
 #################################################################################################
 ----------------------- functions are define here --------------------------------------*/
int cases(int value);                          //taking the different output from the state
int right_turn(int state ,int turn_full);      //function for taking right turn till the line detected
int left_turn (int state ,int turn_full);       //function for taking left turn till the line detected
int start_node();                              //function for making a small forward turn till the middle line is detected    
void sensor_data();                             //function to get sensor data
int bck_node_2_node(int state);                //function for maoving backward the bot from one node to the another node
int fwd_node_2_node(int state);                //function for maoving forward  the bot from one node to the another node
int line_bck(int state);                       //function for maoving backward the bot from line  to the another node
int line_fwd(int state);                       //function for maoving forward  the bot from line  to the another node



int supply_taken = 0;
int diff = -1;
int col, count = 0;
int req_bl[7] = {0}; 

int cpos1 = -1, cpos2 = -1, subt =0;
int status_supply[7] = {
  0};
int supply_center = 3;

int face_side = 0;
int sequence[] = {0, 0, 0, 0}; /*{2, 1, 0, 3}; */

int supply_check[] = {
  -1, -1};
int AH_count = 0;
int two_bits[2] = {
  -1,-1};
int trash_flag = -1;
int trash_count = 0;
int service_required[8]={
  0};
int block_sequence[7]={
  0};


/*--------------------------    end here                   --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 -----------------------different varialble initiallize here --------------------------------------*/


unsigned int fwd_go = 22,turn_go = 22;                     //random values
unsigned int previous_millis = 0;                          //function for define the time period for the hardware timer                   
unsigned long interval = 1000;                             //interval of the millis function
unsigned int state =00 ,i=0 ,node=0,turn=0; 
unsigned int flag_rgt=0,flag_lft=0,flag_bck=0,flag_fwd=0;
int turn_full = 0;
unsigned int right = 0 ;                                   //taking the sensor value using map function for left sensor  
unsigned int center = 0;                                   //taking the sensor value using map function for center sensor
unsigned int left = 0;                                     //taking the sensor value using map function for right sensor




unsigned long current_time = 0;
unsigned int sen_pin[]={
  A0,A6,A7};                         //line sensor input 
int SIM[4] = {0, 0, 0, 0}/*{6, 33, 208, 99}  /*{131, 32, 197, 96 } */,id_rx[4];
unsigned int reading_i[3];                                 //input of the sensor value
unsigned int reading_o[3];                                 //input of the sensor value
int node_count = 0;    //initialize node count
int data = -1;
int QAH = -1;                                              //-1 means No sim is ant hill

int led_pin[] = {
  A3,A1,A2};                                // Initializing LED pins

//unsigned int id_no,id_n1,id_n2,current_tim1;
//unsigned int byte_ar_data[4][8],id_bit_no,id_out[4][4]={
//  9};
//char Category[25],Hill[25],Serv2[25],Serv1[25],Trash[25];
/*-----------------------setup  function of the end here --------------------------------------*/



//#############################################################################################


void millis_servo(int interval)  //Function provides required hardware delays for servo
{

  unsigned long  current_time = millis();
  while(millis()<current_time+interval)
  {

  }

}

void increase(Servo servo,int angle1,int angle2, int d =10)
{
  for(int pos = angle1; pos <= angle2; pos++) // goes from 0 degrees to 180 degrees
  {
    servo.write(pos);
    millis_servo(d);
   // Serial.print(servo.read());


  }
  millis_servo(30);

}

void decrease(Servo servo,int angle1,int angle2, int d=10)
{
  for( int pos = angle1; pos>=angle2; pos--)
    // goes from 180 degrees to 0 degrees
  {
    servo.write(pos);
    millis_servo(d);

    // tell servo to go to position in variable 'pos'
    // waits 15ms for the servo to reach the position
  }
  //millis_servo(30);
  millis_servo(30);
}






/*###############################################################################################
 #################################################################################################
 -----------------------setup function of the start here --------------------------------------*/
void velocity(int left, int right)
{
  speed_left = left;
  speed_right = right;
}
Servo picker;    //servo at picker
Servo griper;    //servo at gripper
Servo core;      //servo at base
Servo stopper;   //servo at lock



/*
* Function Name:setup()
 * Input: None
 * Output: None
 * Logic: Contains the sequencing call of functions
 *Example Call: Called automatically by the compiler only once
 */

void setup()
{ 
  Serial.begin(9600);  //initializing the serial monitor for viewing    
  Wire.begin(SLAVE_ADDRESS);
  pinMode(sen_pin[0], INPUT);                    //initialing left sensor as input
  
  pinMode(sen_pin[1], INPUT);                    //initialing center sensor as input
  pinMode(sen_pin[2], INPUT);                    //initialing right sensor as input

  pinMode(led_pin[0], OUTPUT);                   //initialing red led as o/p
  pinMode(led_pin[1], OUTPUT);                   //initialing green led as o/p
  pinMode(led_pin[2], OUTPUT);                   //initialing blue led as o/p

  //initializing motor driver pins
  pinMode(enright, OUTPUT);                      //making the right pwm pin as enable 
  pinMode(righta, OUTPUT);                       //making the right pin as output 
  pinMode(rightb, OUTPUT);                       //making the right pin as output 
  pinMode(lefta, OUTPUT);                        //making the left  pin as output 
  pinMode(leftb, OUTPUT);                        //making the left  pin as output 
  pinMode(enleft, OUTPUT);                       //making the left pwm pin as enable 
  pinMode(2, OUTPUT);    //buzzer pin


  //
  
  picker.attach(9);             // attaches the servo on pin 9 to the servo object
  griper.attach(5);             // attaches the servo on pin 5 to the servo object
  stopper.write(180);
  stopper.attach(10);           // attaches the servo on pin 10 to the servo object
  core.attach(6);               // attaches the servo on pin 6 to the servo object
  
  //griper.write(100);
  picker.write(30);
  stopper.write(180);
  griper.write(95);
  //delay(500);
  //core.write(6);
  //griper.write(180);
 // pick_it();
  
//
  velocity(72, 68);
  
  data = -1;
  decrease(core,90,50);
  Wire.onRequest(sendData8);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  

   start_2_CN();
   detect_aruco();
   velocity(72,68);
   CN_2_start();
   increase(stopper, 0,180, 0);
   CN_2_end(sequence);

  
  
  


}    
/*-----------------------setup  function of the end here --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 
/*
 * Function Name:loop()
 * Input: None
 * Output: None
 * Logic: No work
 *Example Call: Called automatically by the compiler after the setup()
 */


//-----------------------loop function of the start here --------------------------------------*/

void loop()
{  

}
/*-----------------------loop  function of the end here --------------------------------------*/
