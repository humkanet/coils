#ifndef _COILS_H
#define _COILS_H

#define DRV_IN13_PORT  D
#define DRV_IN13_PIN   6
#define DRV_IN24_PORT  B
#define DRV_IN24_PIN   0

#define DRV1_ENA_PORT  D
#define DRV1_ENA_PIN   5
#define DRV1_ENB_PORT  B
#define DRV1_ENB_PIN   5

#define DRV2_ENA_PORT  B
#define DRV2_ENA_PIN   6
#define DRV2_ENB_PORT  B
#define DRV2_ENB_PIN   7


void  coils_init(void);
void  coil1_forward(void);
void  coil1_reverse(void);
void  coil1_off(void);
void  coil2_forward(void);
void  coil2_reverse(void);
void  coil2_off(void);
void  coil3_forward(void);
void  coil3_reverse(void);
void  coil3_off(void);
void  coil4_forward(void);
void  coil4_reverse(void);
void  coil4_off(void);

#endif
