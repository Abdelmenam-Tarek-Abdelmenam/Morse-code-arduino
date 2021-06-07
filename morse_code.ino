/*
*code to convert any characters to its morse code and display it at led
*outher :- Abdelmenam Tarek Abdelmenam
* date :- 1/3/2021
*/
//the delay unit between events "change it  as you want"
#define delay_unit 500 
// the led that the output wil apear in 
#define led 13

void setup() {
  Serial.begin(9600) ;
  pinMode( led , OUTPUT ) ;
}

String morse_decoder ( char in ){
  /*
   *function to convert any character to its morse code 
   *input : charcter  ex : A
   *output : string that contain the morse code ".-" 
  */
  // array contains morse codes of all numbers 0 -> 9
  String morse_num[] = { "-----" , ".----" , "..---" , "...—" , "....-" 
                                  , "....."  , "-...." , "--..." , "---.." , "----."} ;
 // array contains morse codes of all charachters A -> Z
  String morse_upper[]={ ".-" , "-..." , "-.-." , "-.." , "." , "..-." ,
                         "--." , "...." , ".." , ".---" , "-.-",".-..",
                         "--","-.","---",".--.","--.-",".-.","...","-",
                         "..-","...-",".--","-..-","-.--" , "--.." };
  if (isdigit(in)){ //check if the charachter is number 
    return morse_num[in-48] ;  //  48 is the asci of '0' 
  }
  else if(isupper(in)){ //check if the charachter is upper case letter 
    return morse_upper[in-65] ; // 65 is the asci of 'A'
  }
  else if(islower(in)) { //check if the input is lower case and manipulate as upper   
    return morse_upper[in-97] ; //97 is the asci of 'a'
  }
}

void morse_to_led( String code ){
  /*
   * function to convert any morse code to a led 
   * input : the morse code ex : '.-'
   * the output apear on the led
   */
   Serial.println(code) ;
  for(int i = 0; i< code.length() ; i++ ){ //iretrate usife the code charahters 
    if(code[i] == '.'){ 
        digitalWrite( led , HIGH ) ;
        delay(delay_unit) ; 
    }
    else if ( code[i] == '-' ){
       digitalWrite( led , HIGH ) ;
       delay(3 * delay_unit) ;
    }
    digitalWrite( led , LOW ) ;
    delay(delay_unit) ; //wait betwwen two events
  }
}

void loop() {
    // initialize the led as off
    digitalWrite( led , LOW ) ;
    Serial.println("you can enter the input" ) ;
    if (Serial.available() ){
    //read the input  character by character
     char input = Serial.read() ; 
     Serial.print(input) ;
     if( isdigit(input) || islower(input) || isupper(input) || input==' ' ){ 
     if (input != ' ' ){ //so it isn't a sperator between 2 word
     String code = morse_decoder(input);
     morse_to_led(code);
     delay(3 * delay_unit) ; //wait between two charachters 
     }
     else { 
      delay(7*delay_unit) ; //wait between two words 
     }
    }
     else { Serial.println("unsupported input") ; }
    }  
}
