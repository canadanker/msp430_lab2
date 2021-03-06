#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "song.h"
#include "led.h"

char switch_state_down, switch_state_changed;

static char switch_update_interrupt_sense(){
  char p2val = P2IN;                            
  P2IES |= (p2val & SWITCHES);                    /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);                   /* if switch down, sense up */
  return p2val;
}

void switches_init(){                                /* setup switch */
  P2REN |= SWITCHES;                               /* enable interrupts from switches */
  P2IE = SWITCHES;                                 /* pull-ups for switches */
  P2OUT |= SWITCHES;                               /* set switches' bits for input */
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}


/* Switch handler:
   Plays a different song for
   each individual switch pressed
 */

void switch_interrupt_handler(){
  char p2val = switch_update_interrupt_sense();

  if(!(p2val & SW0)){
    switch_state_down = (p2val & SW0) ? 0 : 1; /* 0 when SW1 is up */
    switch_state_changed = 1;
    led_update();
    playlist(1);  
  }
  else if(!(p2val & SW1)){
    switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
    switch_state_changed = 1;
    led_update();
    playlist(2);
  }
  else if(!(p2val & SW2)){
    switch_state_down = (p2val & SW2) ? 0 : 1; /* 0 when SW1 is up */
    switch_state_changed = 1;
    led_update();
    playlist(3); 
  }
  else if(!(p2val & SW3)){
    switch_state_down = (p2val & SW3) ? 0 : 1; /* 0 when SW1 is up */
    switch_state_changed = 1;
    led_update();
    playlist(4);    
  }
 
}
