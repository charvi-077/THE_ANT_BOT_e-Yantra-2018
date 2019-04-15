'''
 * Team Id:2683

 * Author List: Ankur
         
 * Filename: Receive_i2c.py
 * Theme: Ant Bot
 * Functions: access, send_data, aruco_detecr, main
 * Global variables: g, g_previous, address
 '''
import smbus                         #library for i2c communication
import aruco_detect2                 #Import aruco_detect function to get the ID of the aruco marker
import time			     
from rgb_color_detect import color_detect #import color_detect function to detect the color of box
from trash_detect import trash_detect  # import trash_detect function to detect the color of the trash boxes

bus = smbus.SMBus(1)         #Initialize the i2c bus object
address = 0x08		     #Define the address for the i2c communication	

g = 0			    #Initializing the variable g for accepting the data received from arduino using i2c
g_previous = -1		    #Initializing the variable g_previous



""" 
* Function Name: access
* Input: None
* Output: returns the data present at the i2c bus
* Logic: Read the i2c bus data                 
* Example Call: access()
"""
def access():               #Function to read the data on the i2c bus
    return  bus.read_byte(address)

""" 
* Function Name: send_data
* Input: data (data to be sent to arduino on the i2c bus)
* Output: None
* Logic: Sends the data on the i2c bus to arduino                
* Example Call: send_data(data)
"""   
def send_data(data):       #Function to send the data on the i2c bus
    bus.write_byte(address, data)
    

""" 
* Function Name: aruco_detect
* Input: g (data received on the i2c bus)
* Output: returns the detected aruco id
* Logic: Calls the function for aruco detection               
* Example Call: aruco_detect(g)
"""    
def aruco_detect(g):      #Function to detect aruco when the required i2c data is received
	
	
	    returned = aruco_detect2.cap_aruco_detect(g)
	    return returned
	    #send_data(returned) #send 2 to i2c for aruco detected
			
        
""" 
* Function Name: main
* Input: None
* Output: None
* Logic: The function receives i2c bus data continously and performs selected operations on the 
         specified data.
         1. If data received is 8 ---> Run the arduino code
         2. If the data received is in the range 1 to 4 its the call for aruco detection for 4 arucos
         3. If the data received is 5, 6 its the call for color detection of the boxes    
         4. If the data received is 7, the call is for the trash_detection
* Example Call: The function is called automatically by the interpreter when the file is run
"""              
if __name__ == "__main__":
                
                
                while(1):
                    g = access()    # receive 0,1,2,3 for arudo detect call
                    
                    if((g == 8) and (g != g_previous)):      #For the start of arduino code
                    	   send_data(8)
                    	   g_previous = g
                    
                    if ((g != g_previous) and (g >= 1 and g <= 4)):   #For aruco detection when called
                        ID = aruco_detect(g)
                        #print("#####################ID#########")
                        print("ID detected : ", ID)
		
                        if ID is not -1:
                            send_data(ID)
                            g_previous = g
                            #print("#############Data Sent###########")
                   
                        
                    if ((g != g_previous) and (g >= 5 and g <= 6)):  #For color detection when called
                        color = color_detect()
                        #print(color)
                        send_data(color)
                        g_previous = g
                        
                    if ((g != g_previous) and (g == 7)):   #For trash detection when called
                        yellow = trash_detect()
                        #print(yellow)
                        send_data(yellow)
                        g_previous = g
                        

                       
                    
		

		

	
