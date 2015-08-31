//defining pin constants
const short BUTTON = 8;
const short LED    = 11;

short buttonpressed = 0;  //used to only catch one event per click (button "bouncing" is unhandled in this sketch but could be 
                          //                                        handled by adding a 50ms delay to the code that reads the high)
int   onoff         = 0;  //holds LED state, 0 off, 1 on
int   level         = 0;  //holds brightness level for the PWM
int   updown        = 0;  //holds brightening or dimming state, 0 = brighten, 1 = dim 

void setup() {
    //PIN setup
    pinMode(BUTTON, INPUT);
    pinMode(LED   , OUTPUT);    
}

void loop() {
    //Button handling, reads the high, and if the first cycle that saw it marks the button as pressed so the next cycle won't 
    //also perform the pressed action.
    if(digitalRead(BUTTON) == HIGH && buttonpressed == 0){
        //toggle state.  Fancy code here will just toggle between 0 and 1.
        onoff = 1 - onoff;
        
        //marks the button as read, so we won't repress next cycle
        buttonpressed = 1;
    }else if (digitalRead(BUTTON) == LOW && buttonpressed == 1){
        
        //marks the button as unpressed so we can read the next press.
        buttonpressed = 0;
    }

    //state logical, if the LED is on do the brighten/dim logic, else just be off
    if(onoff == 1){
        //bright or dim logical
        if(updown == 0){
            level += 1; //change brightness level
            
            //if we get to the last level, change brighten/dim state for next cycle
            if(level == 255) updown = 1;
        }else{
            level -= 1; //change brightness level
            
            //if we get to the last level, change brighten/dim state for next cycle
            if(level == 0) updown = 0;
        }
        
        analogWrite(LED, level);
        
        //this controls the speed of the brightening and dimming.  Also slows everything else 
        //down like button reading, so be careful
        delay(25);
    }else{
        //Just turn the LED off.
        analogWrite(LED, 0);  //(I don't think rewritting PIN state will hurt on next cycle?)
        
        //Make the level start at zero and brighten state again for when LED is turned on again
        updown = 0;
        level = 0;
    }
}
