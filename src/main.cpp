extern "C" {
    #include "DEV_Config.c"
    #include "LCD_1in28.c"
    #include "font20.c"
    #include "GUI_Paint.h"
}

int main(void) {
    if (DEV_Module_Init() != 0) {
        return -1;
    }

    /* LCD Init */
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);

    /* Turn backlight on */
    EPD_BL_PIN = 25;
    DEV_GPIO_Mode(EPD_BL_PIN, GPIO_OUT);
    DEV_Digital_Write(EPD_CS_PIN, 1);
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_BL_PIN, 1);

    UDOUBLE Imagesize = LCD_1IN28_HEIGHT*LCD_1IN28_WIDTH*2;
    UWORD *texture;

    if ((texture = (UWORD *) malloc(Imagesize)) == NULL) {
        printf("Failed to allocate memory...\r\n");
        exit(0);
    }

    Paint_NewImage((UBYTE *)texture,LCD_1IN28.WIDTH,LCD_1IN28.HEIGHT, ROTATE_0, WHITE);
    Paint_SetScale(65);
    int count(0);

    while (true) {
        Paint_Clear(WHITE);
        Paint_DrawString_EN(count, count, "Hello, World!", &Font20, BLACK, WHITE);
        LCD_1IN28_Display(texture);

        count = (count < 256) ? count + 1 : 0;
        printf("%d\n", count);
        DEV_Delay_ms(100);
    }

    DEV_Module_Exit();
    return 0;
}