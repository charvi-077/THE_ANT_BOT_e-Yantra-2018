/*
   Team Id:2683
 
 Author List: Ankur,Charvi
 
 Filename:fsm_cases.ino
 Theme: Ant Bot
 Functions:return_case, left_traversal, right_traversal, CN_2_end, millis_delay,trash,ah0_trash_service,ah1_trash_service,pick,chk_c,got_it,supply
 ah2_trash_service,ah3_trash_service,color_glow ,color_detect1,color_detect2,sendData0,sendData1,sendData2,sendData3,sendData4,sendData5,sendData6,sendData7,
 sendData8,CN_2_start,start_2_CN.
 Global Variables: None
 */

 
 
 
 
 
 /*
* Function Name:right_turn
* Input: Initial state 
* Output: None
* Logic: implementation for right turn at node.
* Example call : right_turn( state )
/*
/*###############################################################################################
 #################################################################################################
 ------------------       program for taking right turn           ---------------------*/


int  right_turn(int state )
{
  fwd_go = 11;
  turn_go = 00;
  flag_rgt = 0;
  while (flag_rgt !=3 )
  {
    sensor_data();
      if ( (state == 00)  && flag_rgt ==0 )
      { 
        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 1 && right >= 0) || (left >= 0 && center >= 1 && right >= 1) )
        {
          flag_rgt++;
          turn=00;
          state =01;//left motor
          cases(state);
          
        }
      }
      else if (state ==01 || flag_rgt == 0)
      {
          if (left >= 0 && center >= 1 && right >= 0)
          {
            flag_rgt = 3;
            state =00;//left motor
            cases(state);
          }
          else if  ((left >= 1 && center >= 3 && right >= 1) ||(left >= 1 && center >= 3 && right >= 0) )
          {
            state =01;//right motor
            cases(state);
          }
        
          else if((left >= 0 && center >= 3 && right >= 1) || (left >= 0 && center >= 0 && right >= 1) || (left >= 0 && center >= 0 && right >= 0) || (left >= 1 && center >= 0 && right >= 0)   || (left >= 1 && center >= 3 && right >= 0))
          {
            state = 01;//left motor
            cases(state);
          } 

      }
    }   
  
return state;  
}
/*-------------------- right turn function of the end here --------------------------------------*/





/*###############################################################################################
 #################################################################################################


/*-----------------------     end here                     --------------------------------------*/
 




int bit_read(int num)
{
  if(bitRead(num, 6) == 0 && bitRead(num, 5) == 0)
  {
    if(bitRead(num, 7) == 1)
    { QAH = 0;
      Serial.print("\n Queen AH is 0");}
      
      
    SIM[0] = num;
  }
  else if(bitRead(num, 6) == 0 && bitRead(num, 5) == 1)
  {
    if(bitRead(num, 7) == 1)
      {QAH = 1;
      Serial.print("\n Queen AH is 1");}
    SIM[1] = num;
  }
  else if(bitRead(num, 6) == 1 && bitRead(num, 5) == 0)
  {
    if(bitRead(num, 7) == 1)
      {QAH = 2;
      Serial.print("\n Queen AH is 2");}
    SIM[2] = num;
  }
  else if(bitRead(num, 6) == 1 && bitRead(num, 5) == 1)
  {
    if(bitRead(num, 7) == 1)
      {QAH = 3;
      Serial.print("\n Queen AH is 3");}
      SIM[3] = num;
  }
}



int detect_aruco()
{ 

  // The code below rotates the the two servo with defined angle in corresponding upward and downward direction by calling the function in defined class 
  // attaches the servo on pin 9 to the servo object
  //################################DATA1################################
  data = -1;
  decrease(core,90,50);
  Wire.onRequest(sendData1);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  //Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  //Serial.print(data);
  bit_read(data);


  //################################DATA2################################  
  data=-1;
  increase(core,50, 130);

  Wire.onRequest(sendData2);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  //Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  //Serial.print(data);
  bit_read(data);
  //################################180TURN################################ 
  velocity(95,87);
  turn_full = 180;

  left_turn(state);
  line_bck1(state);


  //################################DATA3################################ 
  data = -1;

  Wire.onRequest(sendData4);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  //Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  //Serial.print(data);
  bit_read(data);
  //################################DATA4################################ 
  data = -1;
  decrease(core,130, 45);

  Wire.onRequest(sendData3);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  //  //Serial.print("###########################DATA REUCEIVED#################### \n");
  //
  //  //Serial.print(data);
  bit_read(data);
  //#################MOVE SERVO BACK TO ITS POSITION#########

  increase(core,45, 90); // Servo back in 
  
  
  the_sequence_decider();
  services();
  
  
  for(int i = 0; i<4; i++)
  {
    Serial.print("\nSEQUENCE"); 
    Serial.print(sequence[i]); 
  }
  
  Serial.print("\nQAH"); 
  Serial.print(QAH);
    
    
  for(int i = 0; i<8; i++)
  {
    Serial.print("\n SERVICE REQUIRED"); 
    Serial.print(service_required[i]); 
  }
  
  cal_block_seq();
  
  for(int i = 0; i<7; i++)
  {
    Serial.print("\n BLOCK SEQUENCE"); 
    Serial.print(block_sequence[i]); 
    req_bl[i] = block_sequence[i];

  }
}  





/*###############################################################################################
 #################################################################################################
 ------------------ detect_color function start here        ----------------------------------*/
void detect_color()
{

  data = -1;
  Wire.onRequest(sendData5);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }
  Serial.print("DAta");
  Serial.print(data);

}
/*-------------------- detect_color function of the end here --------------------------------------*/


/*###############################################################################################
 #################################################################################################
 ------------------      pick_it function start here          ----------------------------------*/
int pick_it()
{
   if(face_side == 1){
 int r = core.read();
 if(r > 4){
 decrease(core, r,4);}
 else if (r<4){
 increase(core, r ,4);}
 }
 else if (face_side == -1){
  int r = core.read();
 if(r < 178){
 increase(core, r,178);}
 else if (r>178){
 decrease(core, r ,178);}
 }
  //increase(picker,30,150);  

 //increase(stopper,0,180);

  increase(picker,30,170);

  increase(griper,95,180);

  decrease(picker,165,27,25);

  decrease(griper,180,95,30);

 // increase(stopper,10,180);

  increase(picker,30,160);

  decrease(stopper,180,0,25);

  decrease(picker,160,27);


}

/*--------------------  pick_it function of the end here --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 ------------------      pick_it function start here          ----------------------------------*/
int pick_it_up()
{
  //increase(picker,30,150);  

 //increase(stopper,20,180);
  if(face_side == 1){
 int r = core.read();
 if(r > 4){
 decrease(core, r,4);}
 else if (r<4){
 increase(core, r ,4);}
 }
 else if (face_side == -1){
  int r = core.read();
 if(r < 178){
 increase(core, r,178);}
 else if (r>178){
 decrease(core, r ,178);}
 }

  increase(picker,27,173);

  increase(griper,95,180);

  decrease(picker,173,30,25);

  decrease(griper,180,155,50);
  
  decrease(griper,155,95,5);

  increase(stopper,0,180,0);

  increase(picker,30,160);

  decrease(stopper,180,0,20);

  decrease(picker,160,30);


}

/*--------------------  pick_it function of the end here --------------------------------------*/


/*###############################################################################################
 #################################################################################################
 ------------------      drop_it function start here          ---------------------------------*/

void drop_it()
{

  increase(griper,95,180);

  increase(picker,30,170);

  decrease(griper,180,95,5);

  decrease(picker,170,30);


}
/*--------------------  drop_it function of the end here --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 ------------------     trash_it_up function start here          ---------------------------------*/
void trash_it_up()
{
  color_glow(4);

  increase(picker,30,170);

  increase(griper,95,180);

  decrease(picker,170,50,20);


}
/*--------------------  trash_it_up function of the end here --------------------------------------*/

/*###############################################################################################
 #################################################################################################
 ------------------     trash_it_down function start here          ---------------------------------*/
void trash_it_down()

{

  increase(picker,50,170,20);

  decrease(griper,180,95,3);

  decrease(picker,170,27);
  
  



}


int service_at_ah(int ah)
{



  if ((bitRead(SIM[ah],0) == 0) && ((bitRead(SIM[ah],2) != 0) || (bitRead(SIM[ah],1) != 0)) && ((bitRead(SIM[ah],4) != 0) || (bitRead(SIM[ah],3) != 0)))
  {


    decrease(core,90,0);    //drop at service 1
    drop_it();
    increase(core,0,180);  //drop at service 2
    drop_it();
    decrease(core,180,90); //servo vapsi


  }

  if ((bitRead(SIM[ah],0) == 0) && ((bitRead(SIM[ah],2) == 0) && (bitRead(SIM[ah],1) == 0)) && ((bitRead(SIM[ah],4) != 0) || (bitRead(SIM[ah],3) != 0)))
  {
    increase(core,90,180);
    drop_it();
    decrease(core,180,90); //servo vapsi
  }
  if ((bitRead(SIM[ah],0) == 0) && ((bitRead(SIM[ah],2) != 0) || (bitRead(SIM[ah],1) != 0)) && ((bitRead(SIM[ah],4) == 0) && (bitRead(SIM[ah],3) == 0)))
  {

    decrease(core,90,0);
    drop_it();
    increase(core,0,90);
  }
  if ((bitRead(SIM[ah],0) == 1) && ((bitRead(SIM[ah],2) != 0) || (bitRead(SIM[ah],1) != 0)) && ((bitRead(SIM[ah],4) == 0) && (bitRead(SIM[ah],3) == 0)))
  {

    decrease(core,90,0);
    drop_it();
    increase(core,0,180);
    trash_it_up();
    decrease(core,180,90);
    trash(ah);
    trash_flag = 1;

  }
  if ((bitRead(SIM[ah],0) == 1) && ((bitRead(SIM[ah],2) == 0) && (bitRead(SIM[ah],1) == 0)) && ((bitRead(SIM[ah],4) != 0) || (bitRead(SIM[ah],3) != 0)))
  { 

    increase(core,90,180);
    drop_it();
    decrease(core,180,0);
    trash_it_up();
    increase(core,0,90);
    trash(ah);
    trash_flag = 1;

  }
  if ((bitRead(SIM[ah],0) == 1) && ((bitRead(SIM[ah],2) == 0) && (bitRead(SIM[ah],1) == 0)) && ((bitRead(SIM[ah],4) == 0) && (bitRead(SIM[ah],3) == 0)))
  { 
    decrease(core,90,0);
    data = -1;

    Wire.onRequest(sendData7);

    while(data == -1)
    {
       Wire.onReceive(receiveData);
    }
    
    Wire.onRequest(sendData8);
    data = 4;
    if (data == 4)
    { 
      trash_it_up();
      increase(core,0,90);
      trash(ah);
      trash_flag = 1;
    }
    else 
    {
      increase(core,90,180);
      trash_it_up();
      decrease(core,180,90);
      trash(ah);
      trash_flag = 1;
    }
  }

}


void the_sequence_decider()
{  Serial.print("In the SeQuhgfhdjhbvhdj");
  switch(QAH)
  { 
    
  case 0: 
        sequence[0] = 0;
        sequence[1] = 3;
        sequence[2] = 2;
        sequence[3] = 1;
        break;
  case 1:
        sequence[0] = 1;
        sequence[1] = 2;
        sequence[2] = 3;
        sequence[3] = 0;
        break;
  case 2:
        sequence[0] = 2;
        sequence[1] = 1;
        sequence[2] = 0;
        sequence[3] = 3;
        break;
  case 3:
        sequence[0] = 3;
        sequence[1] = 0;
        sequence[2] = 1;
        sequence[3] = 2;
        break;
      
  case -1: 
        sequence[0] = 0;
        sequence[1] = 3;
        sequence[2] = 2;
        sequence[3] = 1;
        break;
    } 
//  Serial.println(sequence[0]);
//  Serial.println(sequence[1]);
//  Serial.println(sequence[2]);
//  Serial.println(sequence[3]);
}

void services()
{
  Serial.print("\n In services");
/*  for(i = 1; i<4; i++)
  { //SERVICE 1
    Serial.print("i");
    Serial.println(sequence[i]);
   
    if(bitRead(SIM[sequence[i]], 2) == 0 && bitRead(SIM[sequence[i]],1) == 0)
    service_required[k-1] = -1; 
    if(bitRead(SIM[sequence[i]], 4) == 0 && bitRead(SIM[sequence[i]], 3) == 0)
    service_required[k] = -1;

    if(bitRead(SIM[sequence[i]], 2) == 0 && bitRead(SIM[sequence[i]],1) == 1)
    service_required[k-1] = 1; 
    if(bitRead(SIM[sequence[i]], 4) == 0 && bitRead(SIM[sequence[i]], 3) == 1)
    service_required[k] = 1;

   
    if(bitRead(SIM[sequence[i]], 2) == 1 && bitRead(SIM[sequence[i]], 1) == 0)
    service_required[k-1] = 2;
    if(bitRead(SIM[sequence[i]], 4) == 1 && bitRead(SIM[sequence[i]], 3) == 0)
    service_required[k] = 2;
    
    if(bitRead(SIM[sequence[i]], 2) == 1 && bitRead(SIM[sequence[i]], 1) == 1)
    service_required[k-1] = 3;
    if(bitRead(SIM[sequence[i]], 4) == 1 && bitRead(SIM[sequence[i]], 3) == 1)
    service_required[k] = 3;
    
    //SERVICE 2
//    if(bitRead(SIM[sequence[i]], 4) == 0 && bitRead(SIM[sequence[i]], 3) == 0)
//    service_required[k] = -1;
//    if(bitRead(SIM[sequence[i]], 4) == 0 && bitRead(SIM[sequence[i]], 3) == 1)
//    service_required[k] = 1;
//    if(bitRead(SIM[sequence[i]], 4) == 1 && bitRead(SIM[sequence[i]], 3) == 0)
//    service_required[k] = 2;
//    if(bitRead(SIM[sequence[i]], 4) == 1 && bitRead(SIM[sequence[i]], 3) == 1)
//    service_required[k] = 3;

    k-=2;    
  }*/
  
  
    //SERVICE 1
    if(bitRead(SIM[sequence[0]], 2) == 0 && bitRead(SIM[sequence[0]], 1) == 0)
    service_required[6] = -1;
    if(bitRead(SIM[sequence[0]], 2) == 0 && bitRead(SIM[sequence[0]], 1) == 1)
    service_required[6] = 1;
    if(bitRead(SIM[sequence[0]], 2) == 1 && bitRead(SIM[sequence[0]], 1) == 0)
    service_required[6] = 2;
    if(bitRead(SIM[sequence[0]], 2) == 1 && bitRead(SIM[sequence[0]], 1) == 1)
    service_required[6] = 3;
    //SERVICE 2
    if(bitRead(SIM[sequence[0]], 4) == 0 && bitRead(SIM[sequence[0]], 3) == 0)
    service_required[7] = -1;
    if(bitRead(SIM[sequence[0]], 4) == 0 && bitRead(SIM[sequence[0]], 3) == 1)
    service_required[7] = 1;
    if(bitRead(SIM[sequence[0]], 4) == 1 && bitRead(SIM[sequence[0]], 3) == 0)
    service_required[7] = 2;
    if(bitRead(SIM[sequence[0]], 4) == 1 && bitRead(SIM[sequence[0]], 3) == 1)
    service_required[7] = 3;
    //SERVICE 1
    if(bitRead(SIM[sequence[1]], 2) == 0 && bitRead(SIM[sequence[1]], 1) == 0)
    service_required[4] = -1;
    if(bitRead(SIM[sequence[1]], 2) == 0 && bitRead(SIM[sequence[1]], 1) == 1)
    service_required[4] = 1;
    if(bitRead(SIM[sequence[1]], 2) == 1 && bitRead(SIM[sequence[1]], 1) == 0)
    service_required[4] = 2;
    if(bitRead(SIM[sequence[1]], 2) == 1 && bitRead(SIM[sequence[1]], 1) == 1)
    service_required[4] = 3;
    //SERVICE 2
    if(bitRead(SIM[sequence[1]], 4) == 0 && bitRead(SIM[sequence[1]], 3) == 0)
    service_required[5] = -1;
    if(bitRead(SIM[sequence[1]], 4) == 0 && bitRead(SIM[sequence[1]], 3) == 1)
    service_required[5] = 1;
    if(bitRead(SIM[sequence[1]], 4) == 1 && bitRead(SIM[sequence[1]], 3) == 0)
    service_required[5] = 2;
    if(bitRead(SIM[sequence[1]], 4) == 1 && bitRead(SIM[sequence[1]], 3) == 1)
    service_required[5] = 3;
    //SERVICE 1
    if(bitRead(SIM[sequence[2]], 2) == 0 && bitRead(SIM[sequence[2]], 1) == 0)
    service_required[2] = -1;
    if(bitRead(SIM[sequence[2]], 2) == 0 && bitRead(SIM[sequence[2]], 1) == 1)
    service_required[2] = 1;
    if(bitRead(SIM[sequence[2]], 2) == 1 && bitRead(SIM[sequence[2]], 1) == 0)
    service_required[2] = 2;
    if(bitRead(SIM[sequence[2]], 2) == 1 && bitRead(SIM[sequence[2]], 1) == 1)
    service_required[2] = 3;
    //SERVICE 2
    if(bitRead(SIM[sequence[2]], 4) == 0 && bitRead(SIM[sequence[2]], 3) == 0)
    service_required[3] = -1;
    if(bitRead(SIM[sequence[2]], 4) == 0 && bitRead(SIM[sequence[2]], 3) == 1)
    service_required[3] = 1;
    if(bitRead(SIM[sequence[2]], 4) == 1 && bitRead(SIM[sequence[2]], 3) == 0)
    service_required[3] = 2;
    if(bitRead(SIM[sequence[2]], 4) == 1 && bitRead(SIM[sequence[2]], 3) == 1)
    service_required[3] = 3;
    //SERVICE 1
    if(bitRead(SIM[sequence[3]], 2) == 0 && bitRead(SIM[sequence[3]], 1) == 0)
    service_required[0] = -1;
    if(bitRead(SIM[sequence[3]], 2) == 0 && bitRead(SIM[sequence[3]], 1) == 1)
    service_required[0] = 1;
    if(bitRead(SIM[sequence[3]], 2) == 1 && bitRead(SIM[sequence[3]], 1) == 0)
    service_required[0] = 2;
    if(bitRead(SIM[sequence[3]], 2) == 1 && bitRead(SIM[sequence[3]], 1) == 1)
    service_required[0] = 3;
    //SERVICE 2
    if(bitRead(SIM[sequence[3]], 4) == 0 && bitRead(SIM[sequence[3]], 3) == 0)
    service_required[1] = -1;
    if(bitRead(SIM[sequence[3]], 4) == 0 && bitRead(SIM[sequence[3]], 3) == 1)
    service_required[1] = 1;
    if(bitRead(SIM[sequence[3]], 4) == 1 && bitRead(SIM[sequence[3]], 3) == 0)
    service_required[1] = 2;
    if(bitRead(SIM[sequence[3]], 4) == 1 && bitRead(SIM[sequence[3]], 3) == 1)
    service_required[1] = 3;

    



//   for(int i = 0; i<8; i++) 
//   {
//    if(service_required[i]!= -1)
//    {
//    Serial.print(service_required[i]);
//    Serial.print(",");}
//   }



}

void cal_block_seq()
{
      for(int i = 0, j = 0; i<8; i++)
    {
        if(service_required[i] != -1)
        {
            block_sequence[j] = service_required[i];
            j++;
        }
    
    }
}

 
 /*
* Function Name:sensor_data
* Input: None
* Output: None
* Logic: Reading the sensor data and mapping it for black line identification.
* Example call : sensor_data( state )
/

/*###############################################################################################
 #################################################################################################
 -----------------------function of the sensor data --------------------------------------*/

void sensor_data()
{
  reading_i[0]=analogRead(sen_pin[0]);                   // read the value from left input pin
  reading_i[1]=analogRead(sen_pin[1]);                   // read the value from center input pin
  reading_i[2]=analogRead(sen_pin[2]);                   // read the value from right input pin

  left   = map(reading_i[0], min_left, max_left, 0, 4);        //mapping the left function in fixed limit
  center = map(reading_i[1], min_center, max_center, 0, 4);//mapping the center function in fixed limit
  right  = map(reading_i[2], min_right, max_right, 0, 4
 
  );    //mapping the right function in fixed limit


  Serial.print("left= ");
  Serial.print(left);
  Serial.print("\t");

  Serial.print("centre= ");
  Serial.print(center);
  Serial.print("\t");

  Serial.print("right= ");
  Serial.print(right);
  Serial.print("\t ");

//  i = 12;
//    Serial.print(" i= ");
//   
//    Serial.print("\t ");  


////
//  Serial.print("i");
//  Serial.print(i);  
//  Serial.print("\t");
//  
  Serial.print("flag_fwd= ");
  Serial.print(flag_fwd);
  Serial.print("\t"); 
  
  Serial.print("flag_rgt= ");
  Serial.print(flag_rgt);
  Serial.print("\t"); 
  
  Serial.print("flag_lft= ");
  Serial.print(flag_lft);
  Serial.print("\t"); 
//  
  Serial.print("flag_bck= ");
  Serial.print(flag_bck);
  Serial.print("\t"); 
  
  
   // Serial.print("node= ");
  //Serial.print(flag_lft);
  Serial.print("\t \n"); 


}

/*-------------------- sensor_data function of the end here --------------------------------------*/



/*###############################################################################################
 #################################################################################################
 ------------------       program to follow forward line to node turn           ---------------------*/
int line_fwd(int state )
{
  fwd_go = 11;
  flag_fwd = 0;
  while (flag_fwd != 9)
  { 
    sensor_data();
    current_time = millis();
    if (left >= 1 && center >= 2 && right >= 1) 
    {
      flag_fwd = 9;
      state = 00;//stop
      cases(state);      
    }


    else if(fwd_go == 11)
    {   
      if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;//backward
        cases(state);
      }
      else if (left >= 1 && center >= 2 && right >= 1) 
      {
        flag_fwd= 9;
        state = 00;//stop
        cases(state);
      }
      else if(left >= 1 && center >= 1 && right == 0)
      {
        flag_fwd = 9;
        state = 00 ;
        cases(state);   
      }
      else if(left == 0 && center >= 1 && right >= 1) 
      {
        flag_fwd = 9 ;
        state = 00;//left
        cases(state);
      }
      else if(left >= 1 && center == 0 && right == 0)
      {
        //while((state == 11) && (millis()<current_time+5))
        //{
          state = 10;//right
          cases(state);
        //}
      }  

      else if(left == 0 && center == 0 && right >= 3)
      {
       // while((state == 11) && (millis()<current_time+5))
        //{
          state = 01;//right
          cases(state);
       // }
      } 
      else 
      {
        state=11;//backward
        cases(state);
      }
    }   

    else if (state == 01)
    {
      if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 1 && right == 0) || (left >= 0 && center >= 1 && right >= 1))
      {
        flag_fwd = 9;
        state = 00;//stop
        cases(state);
      }
      else  if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if(left >= 1 && center == 0 && right == 0)
      {
        state = 10;//right
        cases(state);
      }  
    }   

    else  if (state == 10)
    {
      if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 1 && right == 0) || (left >= 0 && center >= 1 && right >= 1)) 
      {
        flag_fwd = 9;
        state = 00;//stop
        cases(state);            
      }             
      else if(left == 0 && center >= 2 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if (left == 0 && center == 0 && right >= 2)
      {
        state = 01;//left
        cases(state);
      }  
    }
  }     
  return state;
}
/*-------------------- line follow function of the end here --------------------------------------*/

 /*
* Function Name:line_bck
* Input: Initial state 
* Output: None
* Logic:implementation for backward traversal.
* Example call : line_bck( state )
/
/*###############################################################################################
 #################################################################################################
 ------------------       program to follow backward line to node turn           ---------------------*/
int line_bck( int state )
{
  fwd_go = 00 ; //backward
  flag_bck =0;
  i=20;
  while (flag_bck != 9)
  {  

    sensor_data(); 

    if (state == 00)
    {
      if ((left >= 0 && center >= 1 && right >= 0) || (left >= 1 && center >= 1 && right >= 0) || (left >= 1 && center >= 0 && right >= 0) || (left >= 0 && center >= 0 && right >= 0) || (left >= 0 && center >= 0 && right >= 1) || (left >= 0 && center >= 1 && right >= 1) || (left >=1  && center >= 1 && right >= 1)  )
      { 

        flag_bck = 1;
        state = 11;
        cases(state); 
         
      }   
    }

    else if (flag_bck == 1)
    {
      if( state == 11)
      {
        if(left == 0 && center >= 1 && right == 0)
        {
          flag_bck =2;
          state = 11;//fordward
          cases(state);
           

        }     
        else if((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1))
        {
          state = 00;//fordward
          cases(state); 
          break;
            
             
        }
        else if( (left >= 3 && center == 0 && right == 0))
        {
          state = 01;//left
          cases(state);

        }
        else if(left >= 1 && center >= 1 && right >= 0) 
        {
          state = 00 ;
          cases(state);
          break;
        }
        else if( (left == 0 && center == 0 && right >= 3)) 
        {
          state = 10;//right
          cases(state);
        } 
       else if(left == 0 && center >= 1 && right >= 1) 
        {
          state = 00 ;
          cases(state);
          break;
        }
      }     

      else if (state == 01)
      {
        if(left == 0 && center >= 1 && right == 0)
        {
          flag_bck =2;  
          state = 11;
          cases(state);

        }     
        else if((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1))
        {
          flag_bck =9;
          state = 00;
          cases(state);
          break;
        }
        else if((left >= 1 && center == 0 && right == 0))
        {

          state = 01;//left
          cases(state); 
        }  
        else if(left >=1 && center >= 1 && right >= 0) 
        {
          state = 00 ;
          cases(state);
          break;
        }
      }      
      else  if (state == 10)
      {
        if(left == 0 && center >= 1 && right == 0)
        {
          flag_bck =2;
          state = 11;
          cases(state); 
        }      
        else if((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1))
        {
          flag_bck = 9;
          state = 00;
          cases(state);  
           break;
        }
        else if( (left == 0 && center == 0 && right >= 2)) 
        {
          state = 10;//right
          cases(state);
        }  
        else if(left == 0 && center >= 1 && right >= 1) 
        {
          state = 00 ;
          cases(state);
          break;
        }
      }
    }





    //follow straight line
    else if(flag_bck == 2)
    {      
      //state
      current_time = millis();
     if( state == 11)
      {   

        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1))
        {
          flag_bck =9; 
          state = 00;//stop
          cases(state);
          break;
  
        }
        else if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;//fordward
          cases(state);
        }


        else if(left >= 1 && center == 0 && right == 0)
        {
//          while((state == 11) && (millis()<current_time+10))
//          {
            state = 01;//left  right
            cases(state);
    //      }
        }  
        else if(left >= 0 && center >= 1 && right >= 1) 
        {
          flag_bck = 9 ;
          state = 00 ;
          cases(state);
       break;  
      
        }
        else if(left == 0 && center == 0 && right >= 1)
        {
//          while((state == 11) && (millis()<current_time+10))
//          {
            state = 10;//left
            cases(state);
        //  }
        }
        else if(left >= 1 && center >= 1 && right >= 0) 
        {
          flag_bck = 9;
          state = 00;//right
          cases(state);
          break;
           
        } 
//        else 
//        {
//          state=11;//fordward
//          cases(state);
//        }
      }   

      else if (state == 01)
      {
        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1))
        {
          flag_bck =9;
          state = 00;//stop
          cases(state);
          break; 

        }
        else  if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;
          cases(state);
        }
        else if(left >= 1 && center == 0 && right == 0)
        {
          state = 01;//left
          cases(state);
        }  
                else if(left >= 1 && center >= 1 && right >= 0) 
        {
          flag_bck = 9;
          state = 00;//right
          cases(state);
          break;
           
        }
      }   

      else  if (state == 10)
      {
        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 0 && right >= 1)) 
        {
          flag_bck =9;
          state = 00;//stop
          cases(state);
          break;
         
        }             
        else if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;
          cases(state);
        }
        else if (left == 0 && center == 0 && right >= 2)
        {
          state = 10;//right
          cases(state);
        }  
                else if(left >= 0 && center >= 1 && right >= 1) 
        {
          flag_bck = 9 ;
          state = 00 ;
          cases(state);
       break;  
      
        }
      }
    }
  }  
  //return state;
 
}
/*-------------------- backward line follow function of the end here --------------------------------------*/


 
 
 /*
* Function Name:line_bck
* Input: Initial state 
* Output: None
* Logic: implementation for backward traversal.
* Example call : line_bck( state )
/*

/*###############################################################################################
 #################################################################################################
 ------------------       program to follow backward line to node turn     ---------------------*/
int line_bck1( int state )
{
  fwd_go = 00 ; //backward
  flag_bck = 0;
  while (flag_bck != 9)
  {  
    sensor_data();    
    //state
    current_time = millis();
    if (left >= 1 && center >= 2 && right >= 1) 
    {
      flag_bck =9;
      state = 00;//stop
      cases(state);      
    }


    else if( fwd_go == 00 )
    {   
      if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;//backward
        cases(state);
      }
      else if (left >= 1 && center >= 2 && right >= 1) 
      {
        flag_bck =9;
        state = 00;//stop
        cases(state);
      }

      else if(left >= 1 && center == 0 && right == 0)
      {
 
          state = 10;//right
          cases(state);
        
      }  
      else if(left >= 1 && center >= 1 && right == 0)
      {
       
        state = 10 ;
        cases(state);   
      }
      else if(left == 0 && center == 0 && right >= 3)
      {

          state = 01;//right
          cases(state);
        
      }
      else if(left == 0 && center >= 1 && right >= 1) 
      {
        
        state = 01;//left
        cases(state);
      } 
      else 
      {
        state=11;//backward
        cases(state);
      }
    }   

    else if (state == 01)
    {
      if (left >= 1 && center >= 1 && right >= 1) 
      {
        flag_bck =9;
        state = 00;//stop
        cases(state);
      }
      else  if(left == 0 && center >= 1 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if( (left >= 1 && center == 0 && right == 0) || (left >= 1 && center >= 1 && right == 0)  )
      {
        state = 10;//right
        cases(state);
      }  
    }   

    else  if (state == 10)
    {
      if (left >= 1 && center >= 1 && right >= 1) 
      {
        flag_bck = 9;
        state = 00;//stop
        cases(state);            
      }             
      else if(left == 0 && center >= 2 && right == 0)
      {
        state = 11;
        cases(state);
      }
      else if( (left == 0 && center == 0 && right >= 2) || (left == 0 && center >= 1 && right >= 1) )
      {
        state = 01;//left
        cases(state);
      }  
    }
  }

  return state; 
}
/*-------------------- backward line follow function of the end here --------------------------------------*/


 
 
 /*
* Function Name:left_turn
* Input: Initial state 
* Output: None
* Logic: implementation for left turn at node.
* Example call : left_turn( state )
/*
/*###############################################################################################
 #################################################################################################
 ------------------       program for taking left turn           ---------------------*/

int  left_turn(int state)
{ 
  fwd_go = 11;
  turn_go = 11;
  flag_lft = 0;
  while(flag_lft != 9)
  { 
    sensor_data();
    
//    i=10;
//    
//    if(flag_fwd == 3 || flag_fwd == 9 )
//    { 
//      if( left == 0 && center >= 1 && right >= 1) 
//      { current_time=millis();
//        while((millis()<current_time+15))
//        {
//          //sensor_data();
//          state = 10;//
//          cases(state);
////          if ( left == 0 && center >= 1 && right >= 0)
////          {
////            flag_bck = 0;//any arbitary flag to call backward line to node 
////            flag_fwd = 5;//any arbitary flag
////            //break;
////          }  
//        }
//      } 
//      if(left == 1 && center >= 1 && right == 0) 
//      {
//        current_time=millis();
//        while((millis()<current_time+15))
//        {
//          //sensor_data();
//          state = 10;//
//          cases(state);
////          if ( left == 0 && center >= 1 && right >= 0)
////          {
////            flag_bck = 0;//any arbitary flag to call backward line to node 
////            flag_fwd = 5;//any arbitary flag
////           // break;
////          }
//        }  
//      } 
//    }     

    if ((state == 00)  && flag_lft == 0 )
    { 
    
     if ((left >= 1 && center >= 2 && right >= 1) || (left >= 1 && center >= 2 && right >= 0) || (left >= 0 && center >= 2 && right >= 1))
      {
        flag_lft=5;
        turn=11;
        state =10;//right turn
        cases(state);
        
      }
    } 
    else if(state ==10   && flag_lft == 5 )
    {
      if(left == 0 && center >= 1 && right == 0)
      {
        flag_lft=9;
        state = 00;//stop
        cases(state); 
      }    

      else if ((left >= 1 && center >= 3 && right >= 1 )||(left >= 0 && center >= 3 && right >= 1 ))
      {
        state =10;//right motor
        cases(state);
      }

      else if((left >= 1 && center >= 3 && right >= 0) || (left >= 1 && center >= 0 && right >= 0) || (left >= 0 && center >= 0 && right >= 0) || (left >= 0 && center >= 0 && right >= 1) || (left >= 0 && center >= 3 && right >= 1))
      {
        state = 10;//right motor
        cases(state);
      } 

    }
  }
  return state;
} 
/*-------------------- left turn function of the end here --------------------------------------*/

 /*
* Function Name:fwd_node_2_node
* Input: Initial state 
* Output: None
* Logic:implementation for bot traversal from one node to other.
* Example call : fwd_node_2_node( state )
/*
/*###############################################################################################
 #################################################################################################
 ------------------       function for going from forward node to node    ---------------------*/




int fwd_node_2_node(int state  )
{
  fwd_go = 11;
  flag_fwd = 0 ;
  while(flag_fwd != 3)
  { 
    sensor_data();

    if (flag_fwd == 0)
    {

      if ((left >= 1 && center >= 1 && right == 0) || (left == 0 && center >= 1 && right >= 1) || (left >=1  && center >= 1 && right >= 1)  )
      { //current_time = millis();
        //while((millis()<current_time+15))
        {
        flag_fwd = 1;
        state = 11;
        cases(state); 
      }      
      }   
    }
    else if (flag_fwd == 1)
    {
      if( state == 11)
      {
        if(left == 0 && center >= 3 && right == 0)
        {
          flag_fwd =2;
          state = 11;//fordward
          cases(state);

        }     
        else if(left >= 1 && center >= 1 && right >= 1)
        {
          state = 11;//fordward
          cases(state);        
        }
        else if((left >= 2 && center >= 3 && right == 0) || (left >= 3 && center == 0 && right == 0))
        {
          state = 10;//left
          cases(state);

        }
        else if((left == 0 && center >= 1 && right >= 1) || (left == 0 && center == 0 && right >= 1)) 
        {
          state = 01;//right
          cases(state);
        } 
      }     

      else if (state == 01)
      {
        if(left == 0 && center >= 2 && right == 0)
        {
          flag_fwd =2;
          state = 11;
          cases(state);

        }     
        else if(left == 1 && center >= 2 && right == 1)
        {
          state = 11;
          cases(state);
        }
        else if((left >= 2 && center >= 2 && right == 0) || (left >= 3 && center == 0 && right == 0))
        {
          state = 10;//left
          cases(state);
        }  
      }      
      else  if (state == 10)
      {
        if(left == 0 && center >= 1 && right == 0)
        {
          flag_fwd =2;
          state = 11;
          cases(state); 
        }      
        else if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;
          cases(state);
        }
        else if((left == 0 && center >= 1 && right >= 1) || (left == 0 && center == 0 && right >= 1)) 
        {
          state = 01;//right
          cases(state);
        }  
      }
    }
    //follow straight line
    else if (flag_fwd == 2)
    {      
      //state
      current_time = millis();
      if (left >= 1 && center >= 2 && right >= 1) 
      {
        flag_fwd = 3;
        state = 00;//stop
        cases(state);      
      }


      else if( state == 11)
      {   

        if (left >= 1 && center >= 2 && right >= 1) 
        {
          flag_fwd =3; 
          state = 00;//stop
          cases(state);
                      
        }
       else if(left >= 1 && center >= 1 && right == 0)
        {
          flag_fwd =3;
          state = 00 ;
          cases(state);   
        }   
       else if(left == 0 && center >= 1 && right >= 1) 
        {
          flag_fwd=3;
          state = 00;//right
          cases(state);
        }        
        else if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;//fordward
          cases(state);
        }


        else if(left >= 1 && center == 0 && right == 0)
        {
        //  while((state == 11) && (millis()<current_time+5))
          //{
            state = 10;//left  right
            cases(state);
         // }
        }   
        else if(left == 0 && center == 0 && right >= 1)
        {
          //while((state == 11) && (millis()<current_time+5))
        //  {
            state = 01;//left
            cases(state);
          //}
        }

        else 
        {
          state=11;//fordward
          cases(state);
        }
      }   

      else if (state == 01)
      {
        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 1 && right == 0) || (left >= 0 && center >= 1 && right >= 1))
        {
           flag_fwd =3;
          state = 00;//stop
          cases(state);
         
        }
        else  if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;
          cases(state);
        }
        else if(left >= 1 && center == 0 && right == 0)
        {
          state = 10;//left
          cases(state);
        }  
      }   

      else  if (state == 10)
      {
        if ((left >= 1 && center >= 1 && right >= 1) || (left >= 1 && center >= 1 && right == 0) || (left >= 0 && center >= 1 && right >= 1))
        {
          flag_fwd =3;
          state = 00;//stop
          cases(state);            
        }             
        else if(left == 0 && center >= 1 && right == 0)
        {
          state = 11;
          cases(state);
        }
        else if (left == 0 && center == 0 && right >= 1)
        {
          state = 01;//right
          cases(state);
        }  
      }
    }
  }  
  return state; 
}

/*-------------------- forward line follow function of the end here --------------------------------------*/

 
 
 
 /*
* Function Name:return_case()
* Input: None
* Output: None
* Logic:       


/*###############################################################################################
 #################################################################################################
 ------------------       cases for different states         ---------------------*/

int cases(int value)
{
  switch (value)
  {
  case 00 : 
    stp();   //stop the motor
    break; 
  case 11 : 
    if (fwd_go == 11)
    {
      fwd();
    }
    else if (fwd_go == 00 )
    {
      bck();
    } 
    break;

  case 01 : 
    if (fwd_go == 11)
    {
      if(turn_go == 00) 
      {
        if( turn_full == 90 )
        {
          if (turn == 00)
          {
               sf_lft();
                delay(1200);
                turn++;
          }
          else 
          {
            sf_lft();

          }
        }
        else if( turn_full == 180 )
        {
          if (turn == 00)
          {
                hr_lft();
                delay(1300);
                turn++;
          }
          else 
          {
            hr_lft();
          }
        } 
      }

      else 
      {
        sf_lft();  //move the motor forward 
      }
    }

    else if (fwd_go == 00 )
    {
      bck_lft();
    }                   
    break;            
  case 10 : 
    if (fwd_go == 11)
    {
      if(turn_go == 11) 
      {
        if( turn_full == 90 )
        {
          if (turn == 11)
          {
            sf_rgt();
            delay(1500);
            turn++;
          }
          else 
          {
            sf_rgt();
          }
        }
        else if( turn_full == 180 )
        {
          if (turn == 11)
          {
            hr_rgt();
            delay(1000);
            turn++;
          }
          else 
          {
            hr_rgt();
          }
        }   
      } 
      else 
      {
        sf_rgt();  //move the motor forward 
      }
    }

    else if (fwd_go == 00 )
    {
      bck_rgt();
    }                    
    break;           

  default : 
    stp();  //stop the motor  
    break;           
  }
}
/*-------------------- cases function of the end here --------------------------------------*/



/*###############################################################################################
 #################################################################################################
 ------------------      function for speed calling          ---------------------*/

//forward function both motor on

void fwd()
{
  analogWrite(enleft,  speed_left);   //pwm value for the left motor 
  digitalWrite(lefta,  LOW );    //making left pin of motor low
  digitalWrite(leftb,  HIGH);    //making left pin of motor high
  digitalWrite(righta, LOW );    //making right pin of motor low
  digitalWrite(rightb, HIGH);    //making right pin of motor high
  analogWrite(enright, speed_right);   //pwm value for the left motor 
}

// left motor on
void sf_lft()
{
  analogWrite(enleft,  72);    //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high  
  digitalWrite(righta, LOW);  //making right pin of motor low
  digitalWrite(rightb, HIGH); //making right pin of motor high
  analogWrite(enright, 0);    //pwm value for the left motor 0
}

//right motor on 
void sf_rgt()
{
  analogWrite(enleft,  0);    //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high
  digitalWrite(righta, LOW);  //making right pin of motor low
  digitalWrite(rightb, HIGH); //making right pin of motor high
  analogWrite(enright, 68);   //pwm value for the left motor 0
}

// left motor o
void hr_lft()
{
  analogWrite(enleft,  60);   //pwm value for the left motor 95
  digitalWrite(lefta,  LOW);  //making left pin of motor low
  digitalWrite(leftb,  HIGH); //making left pin of motor high  
  digitalWrite(righta, HIGH); //making right pin of motor high
  digitalWrite(rightb, LOW);  //making right pin of motor low
  analogWrite(enright, 55);   //pwm value for the left motor 87
}
//right motor on 
void hr_rgt()
{
  analogWrite(enleft,  60);    //pwm value for the left motor 85
  digitalWrite(lefta,  HIGH);  //making left pin of motor high
  digitalWrite(leftb,  LOW);   //making left pin of motor low
  digitalWrite(righta, LOW);   //making right pin of motor low
  digitalWrite(rightb, HIGH);  //making right pin of motor high
  analogWrite(enright, 54);    //pwm value for the left motor 77

}
//backward movement
void bck()
{
  analogWrite(enleft,  55 );    //pwm value for the left motor  56 
  digitalWrite(lefta,  HIGH);   //making left pin of motor high
  digitalWrite(leftb,  LOW);    //making left pin of motor low
  digitalWrite(righta, HIGH);   //making right pin of motor high
  digitalWrite(rightb, LOW);    //making right pin of motor low
  analogWrite(enright, 49);     //pwm value for the left motor 51
}
//taking left turn in backward
void bck_lft()
{
  analogWrite(enleft,  50);     //pwm value for the left motor 
  digitalWrite(lefta,  HIGH);   //making left pin of motor high
  digitalWrite(leftb,  LOW);    //making left pin of motor low  
  digitalWrite(righta, LOW);   //making right pin of motor high
  digitalWrite(rightb, HIGH);    //making right pin of motor low
  analogWrite(enright, 0);      //pwm value for the left motor 
}
////taking right turn in backward 
void bck_rgt()
{
  analogWrite(enleft,  0);     //pwm value for the left motor 
  digitalWrite(lefta,  LOW);  //making left pin of motor high
  digitalWrite(leftb,  HIGH);   //making left pin of motor low
  digitalWrite(righta, HIGH);  //making right pin of motor high
  digitalWrite(rightb, LOW);   //making right pin of motor low
  analogWrite(enright, 45);   //pwm value for the left motor 
}
//both motor off position
void stp()
{
  digitalWrite(righta, LOW);  //making left pin of motor low
  digitalWrite(rightb, LOW);  //making left pin of motor low
  digitalWrite(lefta , LOW);  //making right pin of motor low
  digitalWrite(leftb , LOW);  //making right pin of motor low
}  
/*-------------------- speed calling function of the end here --------------------------------------*/
