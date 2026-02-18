# a96g418-dispBd
이프로젝트는 a96g418을 제품의 디스플레이 보드로 사용하기 위해 작성할 예정임
MCU : A31T418GDN
원본 :
  Example_STKS-A96T418-GDN-TOUCH-A V1.0.9 2024-07-12 를 기준으로 작성한 것임
분석 : 
	홈페이지에 원본과 같이 있는 Example_Code_A96T418 V1.01 (2023-05-17)과 비교하여 다른 점을 확인함
	Example_STKS의 Driver의 파일내용이 application/source에 포함되었고 이파일이 Example_Code와 다른것이 있슴
	  1. 작은 수정 파일
  		- 공백라인 또는 주석부분의 형식 변경
		: a96T418_bit.c,h
		: a96T418_clock.c,h
		: a96T418_gpio.c,h
		: a96T418_timer1.c,h
		: a96T418_timer2.c,h
		: a96T418_usart1_uart.c,h
		: a96T418_delay.c,h
		: typedef.h
	  2. 많이 다른 것
		: a96T418_usi_i2c.c,h
		: a96T418_wdt.c,h
	  3. Example_STKS의 Driver 에만 있는것
		: a96T418.h : Example_Code 의 common에 있으나 많이 다름 (내용은 같은 것 같음)
		: a96T418_adc.c,h
		: a96T418_buzzer.c,h
		: a96T418_flash.c,h
		: a96T418_pwr.c,h
		: a96T418_timer0.c,h
		: a96T418_timer3.c,h
		: a96T418_timer4.c,h
		: a96T418_timer5.c,h
		: a96T418_usart1_spi.c,h
		: a96T418_usi_spi.c,h
		: a96T418_usi_usart.c,h
		: a96T418_WT.c,h
		: flash_enter.a51
		: startup.a51 : Example_Code 의 common에 있으나 많이 다름
	  4. 기타
		: a96T418_.c,h
수정계획
	1. 폴더명 변경
		: Example_STKS-A96T418-GDN-TOUCH-A -> a96g418-dispBd
	2. 구조 변경
		|- application 
		  |- doc
		  |- driver
		  |- keil 
		  |- library
		  |- source
		  |-  
		  |-  

		|- Driver(확장용) 
	 	: a96T418_.c,h
		: a96T418_.c,h

