//defining pin constants
const short BUTTON = 8;
const short LED    = 13;


short buttonpressed = 0;  //used to only catch one event per click (button "bouncing" is unhandled in this sketch but could be 
                          //                                        handled by adding a 50ms delay to the code that reads the high)
int   onoff = 0;          //holds LED state, 0 off, 1 on

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

    //if state is on, make the LED bright, else turn it off (I don't think rewritting PIN state will hurt on next cycle?)
    if(onoff == 1){
        digitalWrite(LED, HIGH);
    }else{
        digitalWrite(LED, LOW);
    }
}
