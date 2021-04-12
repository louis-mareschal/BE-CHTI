	PRESERVE8
	THUMB   

	include DriverJeuLaser.inc 
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
;char FlagCligno;
FlagCligno	dcb 1
	export FlagCligno
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici
;char FlagCligno;
;
;void timer_callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
;		
;}
	export timer_callback
	

	
	
;void timer_callback(void)
timer_callback proc
	push {lr}
	ldr R2,=FlagCligno
	ldrb R0, [R2]
	cmp R0, #1
;	if (FlagCligno==1)
	bne sinon
;		FlagCligno=0;
;		GPIOB_Set(1);
alors
	mov R0,#0
	strb R0, [R2]
	mov R0,#1 
	bl GPIOB_Set
	b finsi
	
;	else
;		FlagCligno=1;
;		GPIOB_Clear(1);
sinon
	mov R0,#1
	str R0, [R2]
	push {lr}
	mov R0,#1 
	bl GPIOB_Clear
	pop {lr}
	
finsi
	pop {lr}
	bx lr
	; ou : pop {pc}
	endp
;	}		
;}
	END	