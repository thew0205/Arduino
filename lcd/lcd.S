
_SPH_ = 0x3e
_SPL_ = 0x3d
_SREG_ = 0x3f
_tmp_reg_ = 0
_zero_reg_ = 1
delay_time = 100000
.global send_character
.global send_function
.global initf
  .text
  .section  .text
TCCR1A = 0x80
TCCR1B  = TCCR1A +1
TCCR1C = TCCR1A +2
TCNT1L = TCCR1A + 4
TCNT1H = TCCR1A + 5
OCR1A1L = TCCR1A + 8
OCR1A1H = TCCR1A + 9
TIMSK1 = 0x6F

PINB = 0x03
DDRB = PINB + 1
PORTB = PINB + 2

PINC = 0x06
DDRC = PINC + 1
PORTC = PINC + 2

PIND = 0x09
DDRD = PIND + 1
PORTD = PIND + 2

BIT5 = 5

EN = 0
RW = 1
RS = 2

SHITFBY = 5

initf:
ldi r16, 0xff; set all port D as output
    out DDRD, r16
//    ldi r16, ((0x01 << EN) | (0x01 << RW) | (0x01 << RS) ); set the first three pin as outoput
    out DDRC, r16
    sbi DDRB, BIT5; set pin 5 of port B as output
//    sbi PORTB, BIT5
    ret

send_character:
ldi r18, 0xff
  del1:  
  dec r18
    brne del1
//    ldi r17,  0x51
    out PORTD, r17
    ldi r16, ((0x01 << EN) | (0x00 << RW) | (0x01 << RS) ); set the first three pin as outoput
    out PORTC, r16
    ;ldi r16,0x01; (0x01 << EN)
   ; out PORTC, r16
    ldi r16, ((0x00 << EN) | (0x00 << RW) | (0x00 << RS) ); set the first three pin as outoput
    out PORTC, r16
  ret



send_function:
ldi r19, 0xff
dell2:

ldi r18, 0xff
  del10:  
  dec r18
    brne del10
    dec r19
    brne dell2
//   ldi r17,  0b00001111
    out PORTD, r17
    ldi r16, ((0x01 << EN) | (0x00 << RW) | (0x00 << RS) ); set the first three pin as outoput
    out PORTC, r16
    ;ldi r16,0x01; (0x01 << EN)
   ; out PORTC, r16
    ldi r16, ((0x00 << EN) | (0x00 << RW) | (0x00 << RS) ); set the first three pin as outoput
    out PORTC, r16
  ret
    sei            ; enable global interrupt

.L4:

    rjmp .L4    ; a useless loop to keep the controller busy
  rjmp .exit
  .size send_character, .-send_character

.exit:
  jmp init; restart device

tim1_compa:
    sbi PINB, BIT5 ; setting the bit automatically toggles the status of the pin
    reti

default_excetpion:
  rjmp default_excetpion


delay_loop:
    ldi r24,lo8(delay_time)
  ldi r25,hi8(delay_time)
  ldi r26,hlo8(delay_time)
  ldi r27,hhi8(delay_time)
delay_comapre:
  cpi r24,0
  cpc r25,_zero_reg_
  cpc r26,_zero_reg_
  cpc r27,_zero_reg_
  brlt delay_return
  sbiw r24,1
  sbc r26,_zero_reg_
  sbc r27,_zero_reg_
  rjmp delay_comapre
delay_return:
    ret
