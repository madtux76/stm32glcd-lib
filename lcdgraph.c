#include "main.h"
#include "lcdngraph.h"

void LcdWrite(uint8_t cflag,uint8_t data){
  uint8_t tmp;
  tmp = data;
  if (cflag == 0)
       HAL_GPIO_WritePin(CONTROL_PORT,DAT_COM_SW_LINE,GPIO_PIN_RESET);
  if (cflag == 1)
        HAL_GPIO_WritePin(CONTROL_PORT,DAT_COM_SW_LINE,GPIO_PIN_SET);

   HAL_GPIO_WritePin(CONTROL_PORT,CS_LINE,GPIO_PIN_RESET);
       HAL_SPI_Transmit(&hspi1,&tmp,1,HAL_TIMEOUT);
    HAL_GPIO_WritePin(CONTROL_PORT,GPIO_PIN_3,GPIO_PIN_SET);   

};
void LcdGotoXY(int8_t x, int8_t y)
{
  LcdWrite( 0, 0x80 | x);  // Column.
  LcdWrite( 0, 0x40 | y);  // Row.
};
void LcdBitmap(char my_array[]){
  for (int index = 0 ; index < (84 * 48 / 8) ; index++)
    LcdWrite(L_DAT, (int8_t)my_array[index]);
}
void LcdClear(void)
{
  for (int index = 0; index < 84 * 48 / 8; index++)
  {
    LcdWrite(L_DAT, 0x00);
  }
};
void LcdInit(void){
 HAL_GPIO_WritePin(CONTROL_PORT,RESET_LINE,GPIO_PIN_RESET);
 HAL_GPIO_WritePin(CONTROL_PORT,RESET_LINE,GPIO_PIN_SET);

  LcdWrite(L_COM, 0x21 );  // LCD Extended Commands.
  LcdWrite(L_COM, 0xB1 );  // Set LCD Vop (Contrast).
  LcdWrite(L_COM, 0x04 );  // Set Temp coefficent. //0x04
  LcdWrite(L_COM, 0x14 );  // LCD bias mode 1:48. //0x13
  LcdWrite(L_COM, 0x0C );  // LCD in normal mode.
  LcdWrite(L_COM, 0x20 );
  LcdWrite(L_COM, 0x0C ); 
};

void LcdCharacter(char character)
{
  LcdWrite(1, 0x00);
  for (int index = 0; index < 5; index++)
  {
    LcdWrite(L_DAT, FONT[character - 0x20][index]);
  }
  LcdWrite(L_DAT, 0x00);
};

void LcdString(char *characters)
{
  while (*characters)
  {
    LcdCharacter(*characters++);
  }
};