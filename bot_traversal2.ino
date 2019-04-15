
/*
   Team Id:2683
 
 Author List: Ankur,Charvi
 
 Filename:bot_traversal.ino
 Theme: Ant Bot
 Functions:return_case, left_traversal, right_traversal, CN_2_end, millis_delay,trash,ah0_trash_service,ah1_trash_service,pick,chk_c,got_it,supply
 ah2_trash_service,ah3_trash_service,color_glow ,color_detect1,color_detect2,sendData0,sendData1,sendData2,sendData3,sendData4,sendData5,sendData6,sendData7,
 sendData8,CN_2_start,start_2_CN.
 Global Variables: None
 */

/*                          DEFINING DIRECTIONS OF BOT LOCATION
                                        ^
                                    <--- --->
                                        V                                                          */
                                    
/*###############################################################################################
 ################################################################################################# */

/*
  Function Name:return_case()
 Input: None
 Output: None
 Logic: It takes the first two AH from the sequence of AH to be followed and then
 it makes the supply_check[2] array to be {0, 0}, {0, 1}, {1,0}, {1, 1}
 {0, 0} => No service at both the AH of the first two || second two AH in sequence
 {0, 1} => Service only at the 2nd AH of the first two || second two AH in sequence
 {1, 0} => Service at the 1st AH of the first two || second two AH in sequence
 {1, 1} => Service at both AH of the first two || second two AH in sequence
 Example Call: return_case();
 */


int return_case()
{


  if (bitRead(SIM[two_bits[0]], 0) == 0 && bitRead(SIM[two_bits[0]], 1) == 0 && bitRead(SIM[two_bits[0]], 2) == 0 && bitRead(SIM[two_bits[0]], 3) == 0 && bitRead(SIM[two_bits[0]], 4) == 0)
  {
    supply_check[0] = 0;
  }
  else
  {
    supply_check[0] = 1;
  }

  if (bitRead(SIM[two_bits[1]], 0) == 0 && bitRead(SIM[two_bits[1]], 1) == 0 && bitRead(SIM[two_bits[1]], 2) == 0 && bitRead(SIM[two_bits[1]], 3) == 0 && bitRead(SIM[two_bits[1]], 4) == 0)
  {
    supply_check[1] = 0;
  }
  else
  {
    supply_check[1] = 1;
  }

}

/*###############################################################################################
 ################################################################################################# */

/*
  Function Name:left_traversal()
 Input: None
 Output: None
 Logic: Traverse on the AH depending on the Service requirements on AH
 Example Call: left_traversal();
 */

void left_traversal()
{

  if (supply_check[0] == 0 && supply_check[1] == 1)
  {
    turn_full = 90;
    left_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam
    service_at_ah(two_bits[1]);
    if (trash_flag == 1)
    {

      turn_full = 180;
      left_turn(state);

      line_fwd(state); /// Reach at CN
      line_bck(state);

    }
    else if (trash_flag == -1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state);
      line_bck(state);

      turn_full = 90;
      right_turn(state);

      line_fwd(state);
      line_bck(state);
    }
  }

  if (supply_check[0] == 1 && supply_check[1] == 0)
  {
    turn_full = 90;
    right_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam pick place trash
    service_at_ah(two_bits[0]);
    
    if (trash_flag == -1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state);
      line_bck(state);

      turn_full = 90;
      left_turn(state);

      line_fwd(state);
      line_bck(state);
    }

    else if (trash_flag == 1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state); /// Reach at CN
      line_bck(state);
    }
  }

  if (supply_check[0] == 1 && supply_check[1] == 1)
  {
    turn_full = 90;
    right_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam pick place trash
    service_at_ah(two_bits[0]);
    
    if(trash_flag == -1)
    {

    turn_full = 180;
    left_turn(state);
        
    line_fwd(state);
    line_bck(state);

    fwd_node_2_node(state);
    line_bck(state);
    
    }
    
    else if(trash_flag == 1) 
    {
       if(two_bits[1] == 3)
       {
             turn_full = 180;
             left_turn(state);
        
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             right_turn(state);
             
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             left_turn(state);
             
             line_fwd(state);
             line_bck(state);
       }
       else if(two_bits[1] == 1)
       {
             turn_full = 180;
             left_turn(state);
        
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             left_turn(state);
             
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             left_turn(state);
             
             line_fwd(state);
             line_bck(state);
       }
       
       trash_flag = -1;
    }

    //servo ka kaam pick place trash
    service_at_ah(two_bits[1]);

    if(trash_flag == -1)
    {
              turn_full = 180;
              left_turn(state);
          
              line_fwd(state);
              line_bck(state);
          
              turn_full = 90;
              right_turn(state);
          
              line_fwd(state);
              line_bck(state);
    }
    
    else if(trash_flag == 1)
    {
              turn_full = 180;
              left_turn(state);
          
              line_fwd(state);
              line_bck(state);
    }
 
  }
}

/*###############################################################################################
 ################################################################################################# */

/*
  Function Name:right_traversal()
 Input: None
 Output: None
 Logic: Traverse on the AH depending on the Service requirements on AH
 Example Call: right_traversal();
 */

void right_traversal()
{

  if (supply_check[0] == 0 && supply_check[1] == 1)
  {
    turn_full = 90;
    right_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam pick place trash
    service_at_ah(two_bits[1]);

    if (trash_flag == 1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state); /// Reach at CN
      line_bck(state);
    }
    else if (trash_flag == -1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state);
      line_bck(state);

      turn_full = 90;
      left_turn(state);

      line_fwd(state);
      line_bck(state);
    }
  }

  if (supply_check[0] == 1 && supply_check[1] == 0)
  {
    turn_full = 90;
    left_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam pick place trash
    service_at_ah(two_bits[0]);
    if (trash_flag == 1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state); /// Reach at CN
      line_bck(state);
    }

    else if (trash_flag == -1)
    {
      turn_full = 180;
      left_turn(state);

      line_fwd(state);
      line_bck(state);

      turn_full = 90;
      right_turn(state);

      line_fwd(state);
      line_bck(state);
    }
  }

  if (supply_check[0] == 1 && supply_check[1] == 1)
  {
    turn_full = 90;
    left_turn(state);

    line_fwd(state);
    line_bck(state);

    //servo ka kaam pick place trash
    service_at_ah(two_bits[0]);
    
    if(trash_flag == -1)
    {

          turn_full = 180;
          left_turn(state);
      
          line_fwd(state);
          line_bck(state);
      
          fwd_node_2_node(state);
          line_bck(state);
    }
    else if(trash_flag == 1)
    {
        if(two_bits[1] == 0)
        {
             turn_full = 180;
             left_turn(state);
        
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             right_turn(state);
             
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             right_turn(state);
             
             line_fwd(state);
             line_bck(state);
       }
       else if(two_bits[1] == 2)
       {
             turn_full = 180;
             left_turn(state);
        
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             left_turn(state);
             
             line_fwd(state);
             line_bck(state);
             
             turn_full = 90;
             right_turn(state);
             
             line_fwd(state);
             line_bck(state);
       }
       
       trash_flag = -1;
      
    }

    //servo ka kaam pick place trash
    service_at_ah(two_bits[1]);

    if(trash_flag == -1)
    {
          turn_full = 180;
          left_turn(state);
      
          line_fwd(state);
          line_bck(state);
      
          turn_full = 90;
          left_turn(state);
      
          line_fwd(state);
          line_bck(state);
    }
    else if(trash_flag == 1)
    {
          turn_full = 180;
          left_turn(state);
        
          line_fwd(state);
          line_bck(state);
    }
  }
}

/*###############################################################################################
 ################################################################################################# */

/*
  Function Name:CN_2_end()
 Input: sequence[] => An array which stores the sequence of AH to be serviced
 Output: None
 Logic: Servicing all the Ant Hills in the priority order
 Example Call: CN_2_end(sequence);
 */

void CN_2_end(int sequence[]) // {0,3,2,1} || {1,2,3,0} || {2,1,0,3} || {3,0,1,2}
{
  //  int first_two_bit_array[2] = {
  //    sequence[0], sequence[1]  };  //First two {0,3} , {3,0}, {1,2}, {2,1}
  //  int second_two_bit_array[2] = {
  //    sequence[2], sequence[3]  };  //Second two {2,1} , {1,2}, {3,0}, {0,3}





  two_bits[0] = sequence[0];   //First two {0,3} , {3,0}, {1,2}, {2,1}
  two_bits[1] = sequence[1];
  return_case(); // it maked the supply_check[0] and supply_check[1] {0,0}, {0,1}, {1,0}, {1,1} for First two AH 0 and 3

  if ((sequence[0] == 0 && sequence[1] == 3 ) || (sequence[0] == 3 && sequence[1] == 0 ))
  {
            if (supply_check[0] != 0 || supply_check[1] != 0)
        
              // It make the bot turn left from the CN if {0,3} || {3,0} have some work
            {
                        turn_full = 90;
                  
                        left_turn(state);
                  
                        line_fwd(state);
                        line_bck(state);
                  
                  
                        if (sequence[0] == 0 && sequence[1] == 3)
                        {
                          left_traversal();
                          AH_count = 2;
                        }
                  
                        else if (sequence[0] == 3 && sequence[1] == 0)
                        {
                          right_traversal();
                          AH_count = 2;
                        }
                  
                  
                        //Presently bot   -------> stands like this when no trash in both AH
                        //Presently bot   -------> stands like this when no trash in both AH
                        //Presently bot   -------> stands like this when no trash in both AH
                  
                        //           OR if trash
                  
                        //Presently bot    V    stands like this when service only one of the AH
                        //Presently bot    V    stands like this
                        //Presently bot    V    stands like this
                        
                        
                  
                  
                        two_bits[0] = sequence[2];    //Second two {2,1} , {1,2}, {3,0}, {0,3}
                        two_bits[1] = sequence[3];
                        return_case(); // it maked the supply_check[0] and supply_check[1] {0,0}, {0,1}, {1,0}, {1,1} for last two AH, 1 and 2
                  
                        if (supply_check[0] != 0 || supply_check[1] != 0)
                        {
                                    if (trash_flag == -1)
                                    {
                                      fwd_node_2_node(state);
                                      line_bck(state);
                                    }
                                    else if (trash_flag == 1)
                                    {
                                      turn_full = 90;
                                      left_turn(state);
                            
                                      line_fwd(state);
                                      line_bck(state);
                                      trash_flag = -1;
                                    }
                            
                                    //delay
                            
                                    if (sequence[2] == 2 && sequence[3] == 1)
                                    {
                                      left_traversal();
                                      AH_count = 4;
                                    }
                                    else if (sequence[2] == 1 && sequence[3] == 2)
                                    {
                                      right_traversal();
                                      AH_count = 4;
                                    }
                            
                            
                                    //Presently bot <------ stands like this
                                    //Presently bot <------ stands like this
                                    //Presently bot <------ stands like this
                                    //             OR if Trash
                                    //Presently bot    V    stands like this
                                    //Presently bot    V    stands like this
                                    //Presently bot    V    stands like this
                            
                                    //Move bot to start
                                    if (trash_flag == 1)
                                    {
                                      fwd_node_2_node(state);
                                      line_bck(state);
                            
                                      fwd_node_2_node(state);
                                      line_bck(state);
                            
                                      digitalWrite(2, HIGH);
                                      delay(5000);
                                      digitalWrite(2, LOW);
                            
                                      trash_flag = -1;
                                    }
                                    else if (trash_flag == -1)
                                    {
                                      turn_full = 90;
                                      left_turn(state);
                            
                                      line_fwd(state);
                                      line_bck(state);
                            
                                      fwd_node_2_node(state);
                                      line_bck(state);
                            
                                      digitalWrite(2, HIGH);
                                      delay(5000);
                                      digitalWrite(2, LOW);
                                    }
                  
                  
                        }
                        else
                        {
                                    AH_count = 4;
                            
                                    //Presently bot   -------> stands like this
                                    //Presently bot   -------> stands like this
                                    //Presently bot   -------> stands like this
                                    //             OR if Trash
                                    //Presently bot    V    stands like this
                                    //Presently bot    V    stands like this
                                    //Presently bot    V    stands like this
                            
                                    //Move bot to CN
                                    if (trash_flag == -1)
                                    {
                                            turn_full = 90;
                                            right_turn(state);
                                  
                                            line_fwd(state);
                                            line_bck(state);
                                  
                                            fwd_node_2_node(state);
                                            line_bck(state);
                                  
                                            digitalWrite(2, HIGH);
                                            delay(5000);
                                            digitalWrite(2, LOW);
                            
                                    }
                                    else if (trash_flag == 1)
                                    {
                                            fwd_node_2_node(state);
                                            line_bck(state);
                                  
                                            fwd_node_2_node(state);
                                            line_bck(state);
                                  
                                            digitalWrite(2, HIGH);
                                            delay(5000);
                                            digitalWrite(2, LOW);
                                  
                                            trash_flag = -1;
                                    }
                            
                            
                                    //Presently bot   ^   stands like this
                                    //Presently bot   ^   stands like this
                                    //Presently bot   ^   stands like this
                  
                        }
        
        
        
            }
            
            
            
            ////////////////////////////////////////////////////////////////////////////////////////////////
            
            
            else
            {
                            AH_count = 2;
                      
                            //Presently bot   ^   stands like this
                            //Presently bot   ^   stands like this
                            //Presently bot   ^   stands like this
                      
                            two_bits[0] = sequence[2];    //Second two {2,1} , {1,2}, {3,0}, {0,3}
                            two_bits[1] = sequence[3];
                            return_case();
                            if (supply_check[0] != 0 || supply_check[1] != 0)
                            {
                                                  turn_full = 90;
                                                  right_turn(state);
                                          
                                                  line_fwd(state);
                                                  line_bck(state);
                                  
                                  
                                  
                                                  if (sequence[2] == 2 && sequence[3] == 1)
                                                  {
                                                          left_traversal();
                                                          AH_count = 4;
                                                  }
                                                  else if (sequence[2] == 1 && sequence[3] == 2)
                                                  {
                                                          right_traversal();
                                                          AH_count = 4;
                                                  }
                                          
                                          
                                                  //bot <------ stands like this
                                                  //bot <------ stands like this
                                                  //bot <------ stands like this
                                                  //          OR if Trash
                                                  //bot    V    stands like this
                                                  //bot    V    stands like this
                                                  //bot    V    stands like this
                                          
                                          
                                          
                                                  if (trash_flag == -1)
                                                  {
                                                          turn_full = 90;
                                                          left_turn(state);
                                                
                                                          line_fwd(state);
                                                          line_bck(state);
                                                
                                                          fwd_node_2_node(state);
                                                          line_bck(state);
                                                
                                                          digitalWrite(2, HIGH);
                                                          delay(5000);
                                                          digitalWrite(2, LOW);
                                          
                                                  }
                                                  else if (trash_flag == 1)
                                                  {
                                                          fwd_node_2_node(state);
                                                          line_bck(state);
                                                
                                                          fwd_node_2_node(state);
                                                          line_bck(state);
                                                
                                                          digitalWrite(2, HIGH);
                                                          delay(5000);
                                                          digitalWrite(2, LOW);
                                                
                                                          trash_flag = -1;
                                                  }
                                          
                                          
                                          
                                                  //Presently bot   v   stands like this
                                                  //Presently bot   v   stands like this
                                                  //Presently bot   v   stands like this
                                    }
                                    else
                                    {
                                      AH_count = 4;
                              
                                      //ROtate bot on CN
                                      turn_full = 180;
                                      left_turn(state);
                              
                                      line_fwd(state);
                                      line_bck(state);
                              
                                      fwd_node_2_node(state);
                                      line_bck(state);
                              
                                      digitalWrite(2, HIGH);
                                      delay(5000);
                                      digitalWrite(2, LOW);
                              
                                      //Presently bot   v   stands like this on START
                                      //Presently bot   v   stands like this on START
                                      //Presently bot   v   stands like this on START
              
              
                                    }


            }

  }

  else if ((sequence[0] == 1 && sequence[1] == 2 ) || (sequence[0] == 2 && sequence[1] == 1 ))
  {

            if (supply_check[0] != 0 || supply_check[1] != 0)
            {
                        // It make the bot turn left from the CN if {0,3} || {3,0} have some work
                      
                  
                        //Presently bot   ^   stands like this
                        //Presently bot   ^   stands like this
                        //Presently bot   ^   stands like this
                  
                        turn_full = 90;
                        right_turn(state);
                  
                        line_fwd(state);
                        line_bck(state);
                  
                        //delay
                        if (sequence[0] == 1 && sequence[1] == 2)
                        {
                          right_traversal();
                          AH_count = 2;
                        }
                  
                        else if (sequence[0] == 2 && sequence[1] == 1)
                        {
                          left_traversal();
                          AH_count = 2;
                        }
                  
                  
                        //bot <------ stands like this
                        //bot <------ stands like this
                        //bot <------ stands like this
                        //          OR if trash
                        //Presently bot   v   stands like this
                        //Presently bot   v   stands like this
                        //Presently bot   v   stands like this
                  
                  
                        two_bits[0] = sequence[2];   //Second two {2,1} , {1,2}, {3,0}, {0,3}
                        two_bits[1] = sequence[3];
                        return_case(); // it maked the supply_check[0] and supply_check[1] {0,0}, {0,1}, {1,0}, {1,1} for last two AH, 1 and 2
                  
                        if (supply_check[0] != 0 || supply_check[1] != 0)
                        {
                          if (trash_flag == -1)
                          {
                            fwd_node_2_node(state);
                            line_bck(state);
                          }
                          else if ( trash_flag == 1)
                          {
                            turn_full = 90;
                            right_turn(state);
                  
                            line_fwd(state);
                            line_bck(state);
                  
                            trash_flag = -1;
                          }
                  
                          //delay
                  
                          if (sequence[2] == 0 && sequence[3] == 3)
                          {
                            left_traversal();
                            AH_count = 4;
                          }
                          else if (sequence[2] == 3 && sequence[3] == 0)
                          {
                            right_traversal();
                            AH_count = 4;
                          }
                  
                  
                          //Presently bot   -------> stands like this
                          //Presently bot   -------> stands like this
                          //Presently bot   -------> stands like this
                          //           OR if TRASH
                          //bot      V      stands like this
                          //bot      V      stands like this
                          //bot      V      stands like this
                  
                          //Rotate bot on CN
                  
                  
                          if ( trash_flag == -1)
                          {
                            turn_full = 90;
                            right_turn(state);
                  
                            line_fwd(state);
                            line_bck(state);
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            digitalWrite(2, HIGH);
                            delay(5000);
                            digitalWrite(2, LOW);
                          }
                          else if (trash_flag == 1)
                          {
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            digitalWrite(2, HIGH);
                            delay(5000);
                            digitalWrite(2, LOW);
                  
                            trash_flag = -1;
                          }
                  
                  
                        }
                        else
                        {
                          AH_count = 4;
                          //bot <------ stands like this
                          //bot <------ stands like this
                          //bot <------ stands like this
                  
                          //        OR if Trash
                  
                          //bot      V      stands like this
                          //bot      V      stands like this
                          //bot      V      stands like this
                  
                          //Rotate bot on CN
                          if ( trash_flag == -1)
                          {
                            turn_full = 90;
                            left_turn(state);
                  
                            line_fwd(state);
                            line_bck(state);
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            digitalWrite(2, HIGH);
                            delay(5000);
                            digitalWrite(2, LOW);
                          }
                          else if (trash_flag == 1)
                          {
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            fwd_node_2_node(state);
                            line_bck(state);
                  
                            digitalWrite(2, HIGH);
                            delay(5000);
                            digitalWrite(2, LOW);
                          }
                  
                  
                          //Presently bot   v   stands like this on START
                          //Presently bot   v   stands like this on START
                          //Presently bot   v   stands like this on START
                  
                        }
        
        

            }
            else
            {
                      AH_count = 2;
                
                      //Presently bot   ^   stands like this
                      //Presently bot   ^   stands like this
                      //Presently bot   ^   stands like this
                
                      two_bits[0] = sequence[2];   //Second two {2,1} , {1,2}, {3,0}, {0,3}
                      two_bits[1] = sequence[3];
                      return_case();
                
                      if (supply_check[0] != 0 || supply_check[1] != 0)
                      {
                                turn_full = 90;
                                left_turn(state);
                        
                                line_fwd(state);
                                line_bck(state);
                        
                                //delay
                        
                                if (sequence[2] == 0 && sequence[3] == 3)
                                {
                                    left_traversal();
                                    AH_count = 4;
                                }
                                else if (sequence[2] == 3 && sequence[3] == 0)
                                {
                                    right_traversal();
                                    AH_count = 4;
                                }
                        
                                //Presently bot   -------> stands like this
                                //Presently bot   -------> stands like this
                                //Presently bot   -------> stands like this
                        
                                //          OR if trash
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                        
                                //Rotate bot on CN
                                
                                if (trash_flag == -1)
                                {
                                      turn_full = 90;
                                      right_turn(state);
                          
                                      line_fwd(state);
                                      line_bck(state);
                          
                                      fwd_node_2_node(state);
                                      line_bck(state);
                          
                          
                                      digitalWrite(2, HIGH);
                                      delay(5000);
                                      digitalWrite(2, LOW);
                                }
                                
                                
                                else if (trash_flag == 1)
                                {
                        
                                      fwd_node_2_node(state);
                                      line_bck(state);
                            
                                      fwd_node_2_node(state);
                                      line_bck(state);
                            
                                      digitalWrite(2, HIGH);
                                      delay(5000);
                                      digitalWrite(2, LOW);
                            
                                      trash_flag = -1;
                                }
                        
                        
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                      }
                      
                    
                      else
                      {
                                AH_count = 4;
                        
                                //Rotate on CN
                                turn_full = 180;
                                left_turn(state);
                        
                                line_fwd(state);
                                line_bck(state);
                        
                                fwd_node_2_node(state);
                                line_bck(state);
                        
                        
                                digitalWrite(2, HIGH);
                                delay(5000);
                                digitalWrite(2, LOW);
                        
                        
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                                //Presently bot   v   stands like this
                
                
                      }
                
        
            }

    }


}


/*###############################################################################################
 ################################################################################################# */
/*
  Function Name:trash()
 Input: No of Ant Hill
 Output: None
 Logic: trash service on the respective Ant Hills
 Example Call: trash(ah);
 */


void trash(int ah)
{

  switch(ah)
  {
  case 0:
    ah0_trash_service();
    break; 
  case 1:
    ah1_trash_service();
    break;
  case 2:
    ah2_trash_service();
    break;
  case 3:
    ah3_trash_service();
    break;
  }

}
/*
  Function Name:ah0_trash_service() 
 Input: None
 Output: None
 Logic: trash deposition from AH0
 Example Call: ah0_trash_service();
*/

void ah0_trash_service() 
{
  
  turn_full=180;
  left_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full=90;
  left_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full =90;
  left_turn(state);
  
  velocity(65, 60);
  
  line_fwd(state);
  line_bck(state);
  
  velocity(75, 70);


  if(trash_count == 0)
  {
    increase(core,90,110);

    trash_it_down();

    decrease(core,110, 90);

    trash_count = 1;
  }
  else if(trash_count == 1)
  {
    decrease(core,90,70);

    trash_it_down();

    increase(core,70, 90);

    trash_count = 2;
  }



}
/*
  Function Name:ah1_trash_service() 
 Input: None
 Output: None
 Logic: trash deposition from AH1
 Example Call: ah1_trash_service();
*/
void ah1_trash_service() 
{
  turn_full=180;
  left_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full=90;
  right_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full =90;
  right_turn(state);
  
  velocity(65, 60);

  line_fwd(state);
  line_bck(state);
  
  velocity(75, 70);

  if(trash_count == 0)
  {
    increase(core,90,110);

    trash_it_down();

    decrease(core,110, 90);

    trash_count = 1;
  }
  
  else if(trash_count == 1)
  {
    decrease(core,90,70);

    trash_it_down();

    increase(core,70, 90);

    trash_count = 2;
  }




}

/*
  Function Name:ah2_trash_service() 
 Input: None
 Output: None
 Logic: trash deposition from AH2
 Example Call: ah2_trash_service();
*/

void ah2_trash_service() 
{
  turn_full=180;
  left_turn(state);

  line_fwd(state);
  line_bck(state);


  turn_full=90;
  left_turn(state);

  line_fwd(state);
  line_bck(state);


  turn_full =90;
  right_turn(state);

  velocity(65, 60);

  line_fwd(state);
  line_bck(state);
  
  velocity(75, 70);


  if(trash_count == 0)
  {
    increase(core,90,110);

    trash_it_down();

    decrease(core,110, 90);

    trash_count = 1;
  }
  
  else if(trash_count == 1)
  {
    decrease(core,90,70);

    trash_it_down();

    increase(core,70, 90);

    trash_count = 2;
  }



}

/*
  Function Name:ah3_trash_service() 
 Input: None
 Output: None
 Logic: trash deposition from AH3
 Example Call: ah3_trash_service();
*/

void ah3_trash_service() 
{
  turn_full=180;
  left_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full=90;
  right_turn(state);

  line_fwd(state);
  line_bck(state);

  turn_full =90;
  left_turn(state);
  
  velocity(65, 60);

  line_fwd(state);
  line_bck(state);
  
  velocity(75, 70);

  if(trash_count == 0)
  {
    increase(core,90,110);

    trash_it_down();

    decrease(core,110, 90);

    trash_count = 1;
  }

  else if(trash_count == 1)
  {
    decrease(core,90,70);

    trash_it_down();

    increase(core,70, 90);

    trash_count = 2;
  }



}

/*
  Function Name:color_glow(int) 
 Input: c  (led no)
 Output: None
 Logic: Glows the led (R, G, B, R/G) when required
 Example Call: color_glow(c);
*/
void color_glow(int c)
{
  if(c == 1)
  {
    
    digitalWrite(led_pin[0],HIGH);
    
    delay(1000);
    
    digitalWrite(led_pin[0], LOW);
    
  }
  else if(c == 2)
  {

    digitalWrite(led_pin[1],HIGH);

    delay(1000);

    digitalWrite(led_pin[1],LOW);

  }
  else if(c == 3){

    digitalWrite(led_pin[2],HIGH);
    
    delay(1000);
    
    digitalWrite(led_pin[2], LOW);
    
  }
  else if(c == 4){
    
    digitalWrite(led_pin[0],HIGH);
    digitalWrite(led_pin[1],HIGH);

    delay(1000);
    
    digitalWrite(led_pin[0],LOW);
    digitalWrite(led_pin[1], LOW);
    
  }
}

/*
  Function Name:color_detect1()
 Input: None
 Output: None
 Logic: Its the i2c data sending and receiving the color of the block
 Example Call: color_detect1();
*/

int color_detect1() 
{

  data = -1;


  Wire.onRequest(sendData5);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }

  return data; 
}
/*
  Function Name:color_detect2()
 Input: None
 Output: None
 Logic: Its the i2c data sending and receiving the color of the block
 Example Call: color_detect2();
*/
int color_detect2() 
{

  data = -1;


  Wire.onRequest(sendData6);

  while(data == -1)
  {
    Wire.onReceive(receiveData);
  }

  return data; 
} 



/*
  Function Name:sendData0()
 Input: None
 Output: None
 Logic: Send 0 on i2c bus
 Example Call: sendData0();
*/

void sendData0()
{
  Wire.write(0);
}
/*
  Function Name:sendData1()
 Input: None
 Output: None
 Logic: Send 1 on i2c bus
 Example Call: sendData1();
*/

void sendData1()
{   
  Wire.write(1);
}
/*
  Function Name:sendData2()
 Input: None
 Output: None
 Logic: Send 2 on i2c bus
 Example Call: sendData2();
*/

void sendData2()
{
  Wire.write(2);
}
/*
  Function Name:sendData3()
 Input: None
 Output: None
 Logic: Send 3 on i2c bus
 Example Call: sendData3();
*/

void sendData3()
{
  Wire.write(3);
}
/*
  Function Name:sendData4()
 Input: None
 Output: None
 Logic: Send 4 on i2c bus
 Example Call: sendData4();
*/

void sendData4()
{
  Wire.write(4);
}
/*
  Function Name:sendData5()
 Input: None
 Output: None
 Logic: Send 5 on i2c bus
 Example Call: sendData5();
*/

void sendData5()
{
  Wire.write(5);
}
/*
  Function Name:sendData6()
 Input: None
 Output: None
 Logic: Send 6 on i2c bus
 Example Call: sendData6();
*/

void sendData6()
{
  Wire.write(6);
}
/*
  Function Name:sendData7()
 Input: None
 Output: None
 Logic: Send 7 on i2c bus
 Example Call: sendData7();
*/

void sendData7()
{
  Wire.write(7);
}
/*
  Function Name:sendData8()
 Input: None
 Output: None
 Logic: Send 8 on i2c bus
 Example Call: sendData8();
*/

void sendData8()
{
  Wire.write(8);
}
/*
 Function Name:receiveData
 Input: None
 Output: None
 Logic: Receive data on the i2c bus
 Example Call: receiveData(byteCount);
*/

void receiveData(int byteCount)
{

  data = Wire.read();
 
}


/*
 Function Name:pick
 Input: c (led no to be called for the first block to be picked)
 Output: None
 Logic: Picking up the first desired block
 Example Call: pick(c);
*/


void pick(int c) {
  color_glow(c);
  if(count == 0){
  pick_it();
  Serial.println("pick_it()");}
  else{
  pick_it_up();
  Serial.println("pick_it_up()");}
  
  count++;
  simu_supp[curr_node] = 0;
  status_supply[curr_node] = 0;
  Serial.print("count = ");
  Serial.println(count);
  Serial.println("---");
  Serial.print(" Picked block = ");
  Serial.println(c);
}
/*
 Function Name:check_c
 Input: None
 Output: None
 Logic: Match the color with the desired to be pick 
 Example Call: check_c();
*/
void chk_c() {

  if (col == req_bl[count])
  {
    pick(col);

  }
  else {
    //Serial.println("chk_c in else");
    status_supply[curr_node] = col;
  }
}
/*
 Function Name:got_it
 Input: None
 Output: None
 Logic: Checks the current pos of the servo and checks the node position of the supply to be picked
 Example Call: got_it();
*/
void got_it() {
  if ( face_side == -1){
    if (subt < 0) {
      face_side = 1;
      Serial.println("in got it with diff<0 face side -1");
      turn_full = 180;
      //velocity(93, 85);
      left_turn(state);
      decrease(core,177,3);
      //velocity(72,68);
      line_fwd(state);
      line_bck(state);
      Serial.print("difference=");
      Serial.println(subt);
      Serial.print("curr_node = ");
      Serial.println(curr_node);
      curr_node = curr_node - 1;
      subt = subt + 1;
      Serial.print("differ = ");
      Serial.println(subt);
      Serial.print("curr_node =");
      Serial.println(curr_node);
      while (subt != 0 ) {
        Serial.println("hi");
        fwd_node_2_node(state);
        //if(curr_node != 0 || curr_node != 6)
        line_bck(state);
        curr_node = curr_node - 1;
        subt = subt + 1;
        Serial.print("diff");
        Serial.println(subt);
        Serial.print("curr_node");
        Serial.println(curr_node);
        //delay(100);
      }
    }
    else if (subt > 0) {
      Serial.println("in got it with diff > 0 with face side -1");
      while (subt != 0) {
        //velocity(72,68);
        fwd_node_2_node(state);
        //if(curr_node != 0 || curr_node != 6)
        line_bck(state);
        subt--;
        curr_node++;
        Serial.print("diff");
        Serial.println(subt);
        Serial.print("curr_node");
        Serial.println(curr_node);
        delay(100);
      }
    }
  }
  if ( face_side == 1){
    if (subt > 0) {
      face_side = -1;
      Serial.println("in got it with diff<0 wiht faceside 1");
      turn_full = 180;
      //velocity(93, 85);
      left_turn(state);
      increase(core,3,177);
      velocity(65,60);
      line_fwd(state);
      line_bck(state);
      Serial.print("diff");
      Serial.println(subt);
      Serial.print("curr_node");
      Serial.println(curr_node);
      curr_node = curr_node + 1;
      subt = subt - 1;
      Serial.print("diff");
      Serial.println(subt);
      Serial.print("curr_node");
      Serial.println(curr_node);
      while (subt != 0 ) {
        fwd_node_2_node(state);
        //if(curr_node != 0 || curr_node != 6)
        line_bck(state);
        curr_node = curr_node + 1;
        subt = subt - 1;
        Serial.print("diff");
        Serial.println(subt);
        Serial.print("curr_node");
        Serial.println(curr_node);
        //delay(100);
      }
    }
    else if (subt < 0) {
      Serial.println("in got it with diff > 0  faceside 1");
      while (subt != 0) {
        //velocity(72,68);
        ;
        fwd_node_2_node(state);
        //if(curr_node != 0 || curr_node != 6)
        line_bck(state);
        subt = subt + 1;
        curr_node = curr_node -1;
        Serial.print("diff");
        Serial.println(subt);
        Serial.print("curr_node");
        Serial.println(curr_node);
        delay(100);
      }
    }
  }


}
/*
 Function Name:supply
 Input: None
 Output: None
 Logic: Picks up the desired supply by checking the req_bl array which contains the color of blocks to be picked
        1 = red
        2 = green
        3 = blue
 Example Call: supply();
*/
int supply() {
/*  
Supply 1 or S1 ==> curr_node =0
Supply 2 or S2 ==> curr_node =1
Supply 3 or S3 ==> curr_node =2
Node after Start ==> curr_node =3
Supply 4 or S4 ==> curr_node =4
Supply 5 or S5 ==> curr_node =5
Supply 6 or S6 ==> curr_node =6

*/
 

  if (!supply_taken) {                                              // check if supply is taken or not
    if (curr_node == 3) {                                           // if standing at the node after START
      turn_full = 90;
      ////velocity(90, 0);
      right_turn(state);                                            // takes a right turn of 90 degree
      face_side = 1;                                                // faceside tell the ant bot about in which direction is it facing 1 --> left( to START) and -1 --> right( to START)
      velocity(72,68);

      line_fwd(state);
      delay(500);
      line_bck(state);
      delay(500);
      curr_node = 2;                                                 // at curr_node 2 of shrub area
      decrease(core,90,0);

      Serial.println(curr_node);
      col = color_detect1();
      Serial.println("chk_c in");
      chk_c();
      Serial.println("chk_c out");
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }

      fwd_node_2_node(state);
      delay(500);
      line_bck(state);
      delay(500);
      //increase(core,35,80);
      curr_node = 1;                                            // at curr_node 1 of shrub area
      core.write(0);
      Serial.println(curr_node);
      col = color_detect2();
      chk_c();
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }
      //velocity(72,68);
      fwd_node_2_node(state);
      delay(500);
      line_bck(state);
      delay(500);
      //decrease(core,80,35);
      curr_node = 0;                                            // at curr_node 0 of shrub area
      core.write(0);
      Serial.println(curr_node);
      col = color_detect1();
      chk_c();
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }

      turn_full = 180;
      //velocity(93,85 );
      left_turn(state);
      face_side = -1;
      increase(core,0,176);
      //line_bck(state);
      //velocity(72,68);
      line_fwd(state);
      delay(500);
      line_bck(state);
      delay(500);
      curr_node = 1;                                                            // at curr_node 1 of shrub area
      Serial.println(curr_node);
      ////velocity(73,68);
      int diff = supply_center - curr_node;
      while (diff != 0) {
        fwd_node_2_node(state);
        delay(500);
        line_bck(state);
        delay(500);
        curr_node++;
        Serial.println(curr_node);
        diff--;

      }                                                                            // at curr_node 3 of shrub area
      diff = 0;
      //velocity(72,68);
      fwd_node_2_node(state);
      delay(500);
      line_bck(state);
      delay(500);
      curr_node = 4;                                                               // at curr_node 4 of shrub area     
      Serial.println(curr_node);
      col = color_detect2();
      chk_c();
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }

      ////velocity(73,68);
      fwd_node_2_node(state);
      delay(500);
      line_bck(state);
      delay(500);
      curr_node = 5;                                                              // at curr_node 5 of shrub area
      core.write(177);
      Serial.println(curr_node);
      col = color_detect1();
      chk_c();
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }

      //velocity(72,68);
      fwd_node_2_node(state);
      delay(500);
      line_bck(state);
      delay(500);

      curr_node = 6;                                                                               // at curr_node 6 of shrub area
      core.write(177);
      Serial.println(curr_node);
      col = color_detect2();
      chk_c();
      if(req_bl[count] == 0){
        subt = 3 - curr_node;
        got_it();
        turn_full = 90;
        if(face_side == 1){
          increase(core,3,90);
          right_turn(state);
        }
        else if (face_side == -1){
          decrease(core,177,90);
          left_turn(state);
        }
        return 0;
      }


      Serial.print("count = ");
      Serial.println(count);
      //{2, 2, 3, 1, 0, 0}; 1,2,3,0,3,1,2    1,0,3,0,3,1,0    1,0,3,0,0,1,0
      Serial.print("Status Supply = ");
      for ( int v = 0; v < 7; v++) {
        Serial.print(status_supply[v]);
        Serial.print("  ");
      }

      Serial.println("");
      while ( req_bl[count] != 0 && count < 6 ) {
        for ( int k = curr_node - 1 ; k >= 0; k--) {
          if (status_supply[k] == req_bl[count]) {
            cpos1 = k;
            break;
          }
        }
        for (int  k = curr_node + 1; k < 7 ; k++) {
          if (status_supply[k] == req_bl[count]) {
            cpos2 = k;
            break;
          }
        }
        if ( cpos1 != -1 && cpos2 != -1)
        {
          Serial.print("cpos1 = ");
          Serial.print(cpos1);
          Serial.println("");
          Serial.print("cpos2 = ");
          Serial.print(cpos2);
          Serial.println("");
          if ( abs(cpos1 - curr_node) >= abs(cpos2 - curr_node))
          { 
            subt = cpos2 - curr_node;
            Serial.print("diff");
            Serial.println(subt);
            got_it();
            pick(req_bl[count]);
          }
          else if (abs(cpos1 - curr_node) < abs(cpos2 - curr_node)) {
            subt = cpos1 - curr_node;
            Serial.print("diff");
            Serial.println(subt);
            got_it();
            pick(req_bl[count]);
          }
        }
        else if ( cpos1 == -1) {
          Serial.print("cpos2 = ");
          Serial.print(cpos2);
          Serial.println("");
          subt = cpos2 - curr_node;
          Serial.print("diff");
          Serial.println(subt);
          got_it();
          pick(req_bl[count]);

        }
        else if (cpos2 == -1) {
          Serial.print("cpos1 = ");
          Serial.print(cpos1);
          Serial.println("");
          subt = cpos1 - curr_node;
          Serial.print("diff");
          Serial.println(subt);
          got_it();
          pick(req_bl[count]);
        }

        cpos1 = -1;
        cpos2 = -1;
        subt = 0;
      }
      for ( int v = 0; v < 7; v++) {
        Serial.print(status_supply[v]);
        Serial.print("  ");
      }

      subt = 3 - curr_node;
      got_it();
      turn_full = 90;
      if(face_side == 1){
        increase(core,3,90);
        right_turn(state);
      }
      else if (face_side == -1){
        decrease(core,177,90);
        left_turn(state);
      }

    }
  }
}



/*
 Function Name:start_2_CN
 Input: None
 Output: None
 Logic: Moves from start locatioin to CN
 Example Call: start_2_CN();
*/


void start_2_CN()
{
    
    fwd_node_2_node(state);
    
    line_bck(state);
    
    velocity(95,87);
    
    fwd_node_2_node(state);

    line_bck1(state);
   
}
/*
 Function Name:CN_2_start
 Input: None
 Output: None
 Logic: Moves from CN to node before start
 Example Call: CN_2_start();
*/
void CN_2_start()
{
  
    fwd_node_2_node(state);
    
    line_bck(state);
   
}

/*
 Function Name:millis_delay
 Input: interval (dalay in ms)
 Output: None
 Logic: Hardware delay
 Example Call: millis_delay(20);
*/
 
void millis_delay(int interval)  //Function provides required hardware delays
{
  current_time = millis();
  while (millis() < current_time + interval) {
  }

}
