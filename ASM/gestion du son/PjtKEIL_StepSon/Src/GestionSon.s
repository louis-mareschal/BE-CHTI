	PRESERVE8
	THUMB   
		
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly
	import LongueurSon
	import Son

;Section RAM (read write):
	area    maram,data,readwrite
IndexTable dcd 0;
	export IndexTable		
SortieSon dcw 0;
	export SortieSon


; ===============================================================================================
	

	export CallbackSon
		
	export StartSon
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
		
	import PWM_Set_Value_TIM3_Ch3
; écrire le code ici


StartSon proc
    ldr R0,=IndexTable
    mov R1, #0
    str R1, [r0]
    bx lr
    endp
		
		
CallbackSon proc
	push {lr}
	ldr R0, =IndexTable
	ldrh R0, [R0]
	mov R1, R0
	ldr R3, =LongueurSon
	ldr R3, [R3]
	sub R1, R3
	cmp R1, #0
	beq sinon
alors
	mov R3, #2
	mul R0, R3
	ldr R1, =Son
	ldrsh R2, [R1, R0]
	; maintenent il faut recentrer le son entre [0,719], son_recentree = (son+32768)/ (65535/719) ;
	; on prendra son_recentree = ( son + 32768 )*719 / 65536 => max à 718,98 ;
	add R2, #32768
	mov R3, #719
	mul R2, R3
	mov R3, #65536
	sdiv R2, R3
	ldr R3, =SortieSon
	strh R2, [R3]
	
	;PWM_Set_Value_TIM3_Ch3(SortieSon);
	push{R0}
	mov R0, R2 
	bl PWM_Set_Value_TIM3_Ch3
	pop{R0}
	
	ldr R0, =IndexTable
	ldrh R1, [R0]
	add R1, #1
	str R1, [R0]
	bl fin
sinon 
	mov R2, #360
	ldr R3, =SortieSon
	strh R2, [R3]
	
	;PWM_Set_Value_TIM3_Ch3(SortieSon);
	push{R0}
	mov R0, R2 
	bl PWM_Set_Value_TIM3_Ch3
	pop{R0}
fin
	
	pop {lr}
	bx lr
	endp	
		
	END	