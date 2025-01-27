
#define HSE 2
#define PLL 3

#define SYSCLK 0
#define PLLI2S 1

#define HSI 0
#define LSE 1

#define MCO_DIV_1 000
#define MCO_DIV_2 100
#define MCO_DIV_3 101
#define MCO_DIV_4 110
#define MCO_DIV_5 111



void ClockHseON(void);
void ClockHseOFF(void);
void ClockHseOFF(void);
void ClockPllON(void);
void ClockMCO1 (char clk, char div);

void ClockMCO2 (char clk, char div);