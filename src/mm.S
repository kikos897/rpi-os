#define CYCLES 1000
#define FREQ 1400000000
#define TIME 1000000000

.globl memzero
memzero:
	str xzr, [x0], #8
	subs x1, x1, #8
	b.gt memzero
	ret
.globl temp
temp:
	sub x0,x0,#1
	cmp x0,0x0
	bne temp
	ret
.globl delay_ms
delay_ms:
    // Récupérer le nombre actuel de cycles d'horloge
    mrs x0, cntvct_el0
    // Calculer le nombre de cycles d'horloge nécessaires pour le délai souhaité
    ldr x1, =CYCLES
    mul x0, x0, x1
    // Diviser par la fréquence d'horloge pour obtenir le temps en millisecondes
    ldr x1, =FREQ
    udiv x0, x0, x1
    // Stocker le temps de départ
    mov x1, x0
    // Boucle jusqu'à ce que le nombre de millisecondes souhaité soit atteint
    loop:
    mrs x2, cntvct_el0
    sub x2, x2, x1
    ldr x10, =TIME
    cmp x2, x10
    b.lt loop
    // Retourner au code appelant
    ret

