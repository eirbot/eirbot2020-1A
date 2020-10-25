#ifndef __PINOUT_H_
#define __PINOUT_H_


// moteur gauche
#define break_G_PIN D5
#define PWM_G_PIN D6
#define dir_G_PIN D7

// moteur droit
#define break_D_PIN PE_8
#define PWM_D_PIN D3
#define dir_D_PIN D4

// bluetooth serie
#define TX_BLUE_PIN PB_10
#define RX_BLUE_PIN PB_11

//GP2 avant
#define GP2_A1_PIN PF_4
#define GP2_A2_PIN PC_2
#define GP2_A3_PIN PB_1

//GP2 arriere
#define GP2_R1_PIN PF_9
#define GP2_R2_PIN PF_7
#define GP2_R3_PIN PF_8

//servo gauche PWM
#define BRAS_G_PIN PA_3

//servo droit PWM
#define BRAS_D_PIN PA_0

//pavillon
#define PAVILLON_PIN PC_6


//contacteurs
// #define CTC_1_PIN PC_8
// #define CTC_2_PIN PC_6
#define CTC_3_PIN PG_0
#define CTC_4_PIN PE_0

// BONUS
#define bonus_1_PIN PD_7
#define bonus_2_PIN PD_6
#define bonus_3_PIN PD_5
#define bonus_4_PIN PD_4
#define bonus_5_PIN PD_3



#endif // __PINOUT_H_
