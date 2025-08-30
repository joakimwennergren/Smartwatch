/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "lvgl.h"
#include <roboto_58.h>
#include <roboto_28.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c1;

OSPI_HandleTypeDef hospi1;
DMA_HandleTypeDef handle_GPDMA1_Channel2;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */

/* Task handle */

HAL_DMA_CallbackIDTypeDef id;

lv_color16_t buf_1[PANEL_WIDTH * PANEL_HEIGHT];

void HAL_OSPI_TxCpltCallback(OSPI_HandleTypeDef *h)
{
	/*
	uint8_t Buffer[40] = {0};
    sprintf(Buffer, "DMA COMPLETE, chunks sent = %u\n", bytes_sent);
    HAL_UART_Transmit(&huart4, (uint8_t*)Buffer, strlen(Buffer), 1000);

    if(bytes_sent++ >= 2){
    	bytes_sent = 0;
    }
    */

    //(void)co5300_kick_next();   // chain next chunk (if any)
}

void lvgl_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map) {

    int width  = area->x2 - area->x1 + 1;
    int height = area->y2 - area->y1 + 1;

    const size_t size = (size_t)width * (size_t)height * sizeof(lv_color16_t);

    lv_draw_sw_rgb565_swap((uint16_t *)px_map, width * height);

    // Send the whole framebuffer or just the area
    CO5300_WritePixels_DMA_chunked(px_map, size);

    lv_display_flush_ready(display);
}

/* Task function */
void MyTask(void *argument)
{

	  /*-[ I2C Bus Scanning ]-*/
	/*
	  uint8_t Buffer[25] = {0};
	  uint8_t Space[] = " - ";
	  uint8_t StartMSG[] = "Starting I2C Scanning: \r\n";
	  uint8_t EndMSG[] = "\r\n";
	  uint8_t i = 0, ret;

      sprintf(Buffer, "Device found at 0x%02X\r\n", 0);
      HAL_UART_Transmit(&huart4, (uint8_t*)Buffer, strlen(Buffer), 1000);

	  for (uint8_t i = 0x01; i < 127; i++) {
	      ret = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 3, 5);
	      if (ret == HAL_OK) {
	          sprintf(Buffer, "Device found at 0x%02X\r\n", i);
	          HAL_UART_Transmit(&huart4, (uint8_t*)Buffer, strlen(Buffer), 1000);
	      } else {
	          //sprintf(Buffer, "No response at 0x%02X\r\n", i);
	      }
	      vTaskDelay(pdMS_TO_TICKS(10));
	  }
	 */

/*
  HAL_GPIO_WritePin(GPIOC, VCI_EN_Pin, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_SET);
  vTaskDelay(pdMS_TO_TICKS(16));
  HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_RESET);
  vTaskDelay(pdMS_TO_TICKS(16));
  HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_SET);

  vTaskDelay(pdMS_TO_TICKS(60));

  CO5300_SendInitSequence();

  vTaskDelay(pdMS_TO_TICKS(60));

  // Initialize LVGL
  lv_init();
  // Display handle
  lv_display_t *display_g = lv_display_create(PANEL_WIDTH, PANEL_HEIGHT);
  lv_display_set_flush_cb(display_g, lvgl_flush_cb);
  lv_display_set_buffers(display_g, frame_buffer, NULL, sizeof(frame_buffer), LV_DISPLAY_RENDER_MODE_DIRECT);
  lv_log_register_print_cb(my_lv_log_cb);
  //create_lvgl_tick_task();
  //create_lvgl_timer_task();


  //lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);


  lv_obj_t * label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello world");
  //lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  while(1)
  {
	    lv_timer_handler();
	    lv_tick_inc(10);
	    vTaskDelay(pdMS_TO_TICKS(10));
  }
  */



  /*
  const uint8_t palette[][2] = {
	  {0xFF, 0xE0}, // Yellow
	  {0x00, 0x00},
      {0xE0, 0x00} // Red
      //{0x07, 0xE0}, // Green
      //{0x22, 0x1F}, // Blue
      //{0xFF, 0xFF}, // White
      //{0x00, 0x00}, // Black
      //{0x68, 0xFF}, // Cyan
      //{0xF8, 0x1F}  // Magenta
  };
  static uint32_t current_color = 0;
  const uint32_t palette_size = sizeof(palette) / sizeof(palette[0]);
  uint8_t Buffer[40] = {0};

  for(;;) {

	  CST820_TouchData td;
	  if (CST820_ReadTouch(&td) == HAL_OK && td.touch_count > 0) {
	      // Red pixel at first touch point
		  DrawPixel(td.x1, td.y1, 0xF800);

	      // Send updated frame
	      CO5300_WritePixels_4line(hospi1, frame, PANEL_WIDTH * PANEL_HEIGHT * 2);
	  }


      for (uint32_t i = 0; i < sizeof(frame_buffer); i += 1) {
          frame_buffer[i]     	  = palette[current_color][0];
          frame_buffer[i + 1]     = palette[current_color][1];
      }

      CO5300_WritePixels_DMA_chunked(frame_buffer, sizeof(frame_buffer));
      current_color = (current_color + 1) % palette_size;
      vTaskDelay(pdMS_TO_TICKS(1000));
  }
  */
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
void MX_FREERTOS_Init(void);
static void MX_GPIO_Init(void);
static void MX_GPDMA1_Init(void);
static void MX_ICACHE_Init(void);
static void MX_I2C1_Init(void);
static void MX_OCTOSPI1_Init(void);
static void MX_UART4_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM16_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

static CST820_TouchData td;
//uint8_t frame_buffer[FRAMEBUFFER_SIZE];

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
	uint8_t Buffer[25] = {0};
    sprintf(Buffer, "RTC 1 minute tick!");
    HAL_UART_Transmit(&huart4, (uint8_t*)Buffer, strlen(Buffer), 1000);
}

static void RTC_SetupOnce(void)
{
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};

	sTime.Hours = 14; sTime.Minutes = 9; sTime.Seconds = 0;
	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

	/*
	sDate.WeekDay = RTC_WEEKDAY_MONDAY;
	sDate.Month   = RTC_MONTH_JANUARY;
	sDate.Date    = 1;
	sDate.Year    = 25;  // 2025
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	*/

	//HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, BKP_MAGIC);
}

void RTC_Read(RTC_TimeTypeDef *t, RTC_DateTypeDef *d)
{
    HAL_RTC_GetTime(&hrtc, t, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, d, RTC_FORMAT_BIN); // MUST read date after time (freezes shadow regs)
}

void my_input_read(lv_indev_t * indev, lv_indev_data_t * data)
{
    if(td.touch_count > 0) {
        data->point.x = td.x1;
        data->point.y = td.y1;
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static void arc_event_cb(lv_event_t * e)
{
    lv_obj_t *arc = lv_event_get_target(e);

    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) {
        int32_t v = lv_arc_get_value(arc);
        // R51 FF (brightness)
        uint8_t buf[4];
        buf[0] = (uint8_t)v;
        (void)CO5300_QSPI_WriteCmd(0x51, buf, 1);
        // do something with v...
    }
}

LV_IMG_DECLARE(brightness);
void build_gui()
{
    /* Create an arc */
    lv_obj_t * arc = lv_arc_create(lv_screen_active());

    /* Set size and position */
    lv_obj_set_size(arc, 70, 70);
    lv_obj_set_pos(arc, 46, 46);

    /* Configure arc angles */
    lv_arc_set_range(arc, 10, 100);         // Value range
    lv_arc_set_value(arc, 100);             // Current value
    lv_arc_set_rotation(arc, 270);         // Rotate arc start
    lv_arc_set_bg_angles(arc, 0, 360);     // Background arc full circle
    lv_arc_set_angles(arc, 0, 350);

    lv_obj_set_style_arc_color(arc, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, 6, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc, 6, LV_PART_INDICATOR);

    /* Make the knob white */
    lv_obj_set_style_bg_color(arc, lv_color_white(), LV_PART_KNOB);
    lv_obj_set_style_bg_opa(arc, LV_OPA_COVER, LV_PART_KNOB);

    /* Change background arc color */
    lv_obj_set_style_arc_color(arc, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 6, LV_PART_MAIN);

    lv_obj_add_event_cb(arc, arc_event_cb, LV_EVENT_ALL, NULL);

    /* Create an image inside the arc and center it */
    lv_obj_t *img = lv_image_create(arc);

    /* Option 1: compiled image (C array generated by LVGL’s image converter) */
    lv_image_set_src(img, &brightness);   // e.g. extern const lv_image_dsc_t my_logo;

    /* Option 2: file path (enable FS + decoder like PNG/SVG if needed) */
    // lv_image_set_src(img, "A:/logo.png");  // or "S:/logo.svg", etc.

    lv_obj_center(img);                 // put it in the middle of the arc

    lv_obj_set_style_bg_opa(arc, LV_OPA_70, LV_PART_KNOB);
    //lv_obj_set_style_border_opa(arc, LV_OPA_TRANSP, LV_PART_KNOB);
}

static void clock_timer_cb(lv_timer_t *t)
{
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
    lv_obj_t *label = (lv_obj_t *)lv_timer_get_user_data(t);

	RTC_Read(&sTime, &sDate);

    // ---- Option B (embedded): read from your RTC instead ----
    // int hour = rtc_get_hours();
    // int min  = rtc_get_minutes();

    char buf[9];  // "HH:MM" + NUL
    lv_snprintf(buf, sizeof(buf), "%02d:%02d", sTime.Hours, sTime.Minutes);
    lv_label_set_text(label, buf);
}

void create_line(void) {
    static lv_point_t line_points[] = {
        {0, 0},   // start
        {PANEL_WIDTH, 0}  // end (100px wide, y=0 so it's horizontal)
    };

    lv_obj_t *line = lv_line_create(lv_scr_act());
    lv_line_set_points(line, line_points, 2);

    // Optional style
    lv_obj_set_style_line_width(line, 2, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, lv_color_hex(0xFFFFFF), LV_PART_MAIN);

    // Position on screen
    lv_obj_align(line, LV_ALIGN_TOP_MID, 0, 82);  // 50 px from top
}

LV_IMG_DECLARE(tree);

void set_date_label(lv_obj_t *label) {

    // Swedish weekday names
    const char *weekday_sv[] = {"Sön", "Mån", "Tis", "Ons", "Tors", "Fre", "Lör"};

    // Format buffer
    char buf[32];
    snprintf(buf, sizeof(buf), "%s %d Aug 2025",
             weekday_sv[4],
             28,
             8,
             2025);

    // Set text in LVGL label
    lv_label_set_text(label, buf);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 355);  // 50 px from top

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_font(&style, &roboto_28);
    lv_obj_add_style(label, &style, 0);
}


#define STAR_COUNT           100
#define TICK_MS              20
#define MIN_SPEED_PX         1
#define MAX_SPEED_PX         4
#define MIN_SIZE_PX          1
#define MAX_SIZE_PX          3

typedef struct {
    int16_t x, y;
    uint8_t size;
    uint8_t speed;
    uint8_t opa;        // 0..255
} star_t;

typedef struct {
    lv_obj_t   *sky;
    lv_timer_t *timer;
    uint32_t frame;
    star_t stars[STAR_COUNT];
} stars_ctx_t;

static void star_randomize(star_t *s, bool spawn_above_only) {
    s->size  = (uint8_t)lv_rand(MIN_SIZE_PX, MAX_SIZE_PX);
    s->speed = (uint8_t)lv_rand(MIN_SPEED_PX, MAX_SPEED_PX);
    s->x     = (int16_t)lv_rand(0, PANEL_WIDTH - s->size);
    s->y     = spawn_above_only ? (int16_t)(-lv_rand(5, 50))
                                : (int16_t)lv_rand(-50, PANEL_HEIGHT);
    s->opa   = (uint8_t)(200 + lv_rand(0, 55));
}

/* Draw the whole starfield in one pass */
static void sky_draw_cb(lv_event_t *e) {
    stars_ctx_t *ctx = (stars_ctx_t *)lv_event_get_user_data(e);
    if(!ctx) return;

    lv_layer_t *layer = lv_event_get_layer(e);

    lv_draw_rect_dsc_t dsc;
    lv_draw_rect_dsc_init(&dsc);
    dsc.radius   = LV_RADIUS_CIRCLE;
    dsc.bg_color = lv_color_white();

    for(uint32_t i = 0; i < STAR_COUNT; i++) {
        const star_t *s = &ctx->stars[i];
        dsc.bg_opa = s->opa;

        /* layer coordinates are relative to the object */
        lv_area_t a = {
            .x1 = s->x,
            .y1 = s->y,
            .x2 = (lv_coord_t)(s->x + s->size - 1),
            .y2 = (lv_coord_t)(s->y + s->size - 1),
        };
        lv_draw_rect(layer, &dsc, &a);
    }
}

static void stars_timer_cb(lv_timer_t *tmr) {
    stars_ctx_t *ctx = (stars_ctx_t *)lv_event_get_user_data(tmr);
    if(!ctx || !lv_obj_is_valid(ctx->sky)) return;

    ctx->frame++;

    for(uint32_t i = 0; i < STAR_COUNT; i++) {
        star_t *s = &ctx->stars[i];
        s->y += s->speed;

        if(s->y > PANEL_HEIGHT + s->size) {
            star_randomize(s, true);
        } else if((ctx->frame + i) % 12 == 0) {
            /* twinkle a bit */
            uint8_t base = 190;
            uint8_t jitter = (uint8_t)lv_rand(0, 65);
            s->opa = (uint8_t)(base + jitter);  // 190..255
        }
    }

    /* One invalidate for the whole sky is enough */
    lv_obj_invalidate(ctx->sky);
}

static void sky_delete_event_cb(lv_event_t *e) {
    stars_ctx_t *ctx = (stars_ctx_t *)lv_event_get_user_data(e);
    if(!ctx) return;
    if(ctx->timer) {
        lv_timer_del(ctx->timer);
        ctx->timer = NULL;
    }
    lv_free(ctx);
}

/* Public entry */
void create_night_sky(void) {
    lv_obj_t *sky = lv_obj_create(lv_scr_act());
    lv_obj_set_size(sky, PANEL_WIDTH, PANEL_HEIGHT);
    lv_obj_center(sky);
    lv_obj_clear_flag(sky, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_all(sky, 0, 0);

    /* Strong, visible gradient */
    lv_obj_set_style_bg_color(sky, lv_color_hex(0x0E1A4B), 0);      // top blue
    lv_obj_set_style_bg_grad_color(sky, lv_color_hex(0x000000), 0); // bottom
    lv_obj_set_style_bg_grad_dir(sky, LV_GRAD_DIR_VER, 0);
    lv_obj_set_style_bg_main_stop(sky, 32, 0);
    lv_obj_set_style_bg_grad_stop(sky, 240, 0);
    lv_obj_set_style_bg_opa(sky, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(sky, 0, 0);

    /* context */
    stars_ctx_t *ctx = (stars_ctx_t *)lv_malloc(sizeof(*ctx));
    LV_ASSERT_MALLOC(ctx);
    lv_memset(ctx, 0, sizeof(*ctx));
    ctx->sky = sky;

    for(uint32_t i = 0; i < STAR_COUNT; i++) star_randomize(&ctx->stars[i], false);

    /* draw and animate */
    lv_obj_add_event_cb(sky, sky_draw_cb, LV_EVENT_DRAW_MAIN, ctx);
    ctx->timer = lv_timer_create(stars_timer_cb, TICK_MS, ctx);
    lv_obj_add_event_cb(sky, sky_delete_event_cb, LV_EVENT_DELETE, ctx);
}

void gui_tick_task(void *argument) {
	for(;;) {
		lv_tick_inc(10);
		osDelay(10);
	}
}

void gui_task(void *argument) {
	// Reset display and touch controller
	HAL_GPIO_WritePin(GPIOC, VCI_EN_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(32);
	HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(32);
	HAL_GPIO_WritePin(GPIOA, TP_RST_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(120);
	CO5300_SendInitSequence();
	HAL_Delay(120);



	// Initialize LVGL
	lv_init();
	lv_display_t *display_g = lv_display_create(PANEL_WIDTH, PANEL_HEIGHT);
	lv_display_set_color_format(display_g, LV_COLOR_FORMAT_RGB565);        // important
	lv_display_set_flush_cb(display_g, lvgl_flush_cb);
	lv_display_set_buffers(display_g, buf_1, NULL, sizeof(buf_1), LV_DISPLAY_RENDER_MODE_FULL);

	/*

	lv_indev_t *touch = lv_indev_create();
	lv_indev_set_type(touch, LV_INDEV_TYPE_POINTER);
	lv_indev_set_read_cb(touch, my_input_read);  // your callback (see below)
	lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0xFF0000), LV_PART_MAIN);
	create_night_sky();
	lv_obj_t *img = lv_img_create(lv_scr_act());
	lv_img_set_src(img, &tree);
	lv_obj_center(img);
	static lv_style_t style;
	lv_style_init(&style);
	lv_style_set_text_font(&style, &roboto_58);
	lv_obj_t * label = lv_label_create(lv_screen_active());
	lv_label_set_text(label, "00:00");
	lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 300);  // 50 px from top
	lv_timer_create(clock_timer_cb, 1000, label);
	lv_obj_move_foreground(label);    // or create label after the image
	lv_obj_add_style(label, &style, 0);
	lv_obj_t *label2 = lv_label_create(lv_scr_act());
	set_date_label(label2);
	build_gui();
	lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
	*/

	for (;;) {
		CST820_ReadTouch(&td);
		lv_timer_handler();
		osDelay(10);
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the System Power */
  SystemPower_Config();

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_ICACHE_Init();
  MX_I2C1_Init();
  MX_OCTOSPI1_Init();
  MX_UART4_Init();
  MX_RTC_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
  RTC_SetupOnce();

  // Create thread
  osThreadAttr_t task_attr_tick = {
      .name = "GUITickTask",
      .priority = osPriorityNormal,
      .stack_size = 512 // stack size in bytes
  };

  osThreadNew(gui_tick_task, NULL, &task_attr_tick);

  // Create thread
  osThreadAttr_t task_attr = {
      .name = "GUITask",
      .priority = osPriorityNormal,
      .stack_size = 1 * 1024  // stack size in bytes
  };

  osThreadNew(gui_task, NULL, &task_attr);

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Call init function for freertos objects (in app_freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_MSI|RCC_OSCILLATORTYPE_MSIK;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.MSIKClockRange = RCC_MSIKRANGE_4;
  RCC_OscInitStruct.MSIKState = RCC_MSIK_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 10;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();

  /*
   * Switch to SMPS regulator instead of LDO
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
/* USER CODE BEGIN PWR */
/* USER CODE END PWR */
}

/**
  * @brief GPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPDMA1_Init(void)
{

  /* USER CODE BEGIN GPDMA1_Init 0 */

  /* USER CODE END GPDMA1_Init 0 */

  /* Peripheral clock enable */
  __HAL_RCC_GPDMA1_CLK_ENABLE();

  /* GPDMA1 interrupt Init */
    HAL_NVIC_SetPriority(GPDMA1_Channel2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel2_IRQn);

  /* USER CODE BEGIN GPDMA1_Init 1 */
    HAL_DMA_RegisterCallback(&handle_GPDMA1_Channel2, id, HAL_OSPI_TxCpltCallback);


  /* USER CODE END GPDMA1_Init 1 */
  /* USER CODE BEGIN GPDMA1_Init 2 */

  /* USER CODE END GPDMA1_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000E14;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief OCTOSPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_OCTOSPI1_Init(void)
{

  /* USER CODE BEGIN OCTOSPI1_Init 0 */

  /* USER CODE END OCTOSPI1_Init 0 */

  OSPIM_CfgTypeDef sOspiManagerCfg = {0};

  /* USER CODE BEGIN OCTOSPI1_Init 1 */

  /* USER CODE END OCTOSPI1_Init 1 */
  /* OCTOSPI1 parameter configuration*/
  hospi1.Instance = OCTOSPI1;
  hospi1.Init.FifoThreshold = 1;
  hospi1.Init.DualQuad = HAL_OSPI_DUALQUAD_DISABLE;
  hospi1.Init.MemoryType = HAL_OSPI_MEMTYPE_MICRON;
  hospi1.Init.DeviceSize = 24;
  hospi1.Init.ChipSelectHighTime = 4;
  hospi1.Init.FreeRunningClock = HAL_OSPI_FREERUNCLK_DISABLE;
  hospi1.Init.ClockMode = HAL_OSPI_CLOCK_MODE_3;
  hospi1.Init.WrapSize = HAL_OSPI_WRAP_NOT_SUPPORTED;
  hospi1.Init.ClockPrescaler = 1;
  hospi1.Init.SampleShifting = HAL_OSPI_SAMPLE_SHIFTING_NONE;
  hospi1.Init.DelayHoldQuarterCycle = HAL_OSPI_DHQC_DISABLE;
  hospi1.Init.ChipSelectBoundary = 0;
  hospi1.Init.DelayBlockBypass = HAL_OSPI_DELAY_BLOCK_BYPASSED;
  hospi1.Init.MaxTran = 0;
  hospi1.Init.Refresh = 0;
  if (HAL_OSPI_Init(&hospi1) != HAL_OK)
  {
    Error_Handler();
  }
  sOspiManagerCfg.ClkPort = 1;
  sOspiManagerCfg.NCSPort = 1;
  sOspiManagerCfg.IOLowPort = HAL_OSPIM_IOPORT_1_LOW;
  if (HAL_OSPIM_Config(&hospi1, &sOspiManagerCfg, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN OCTOSPI1_Init 2 */

  /* USER CODE END OCTOSPI1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_PrivilegeStateTypeDef privilegeState = {0};
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
  RTC_AlarmTypeDef sAlarm = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  hrtc.Init.BinMode = RTC_BINARY_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  privilegeState.rtcPrivilegeFull = RTC_PRIVILEGE_FULL_YES;
  privilegeState.backupRegisterPrivZone = RTC_PRIVILEGE_BKUP_ZONE_NONE;
  privilegeState.backupRegisterStartZone2 = RTC_BKP_DR0;
  privilegeState.backupRegisterStartZone3 = RTC_BKP_DR0;
  if (HAL_RTCEx_PrivilegeModeSet(&hrtc, &privilegeState) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the Alarm A
  */
  sAlarm.AlarmTime.Hours = 0x0;
  sAlarm.AlarmTime.Minutes = 0x0;
  sAlarm.AlarmTime.Seconds = 0x0;
  sAlarm.AlarmTime.SubSeconds = 0x0;
  sAlarm.AlarmMask = RTC_ALARMMASK_NONE;
  sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
  sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
  sAlarm.AlarmDateWeekDay = 0x1;
  sAlarm.Alarm = RTC_ALARM_A;
  if (HAL_RTC_SetAlarm(&hrtc, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 79;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 65535;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart4, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart4, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, VCI_EN_Pin|LCD_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TP_RST_GPIO_Port, TP_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : TP_INT_Pin */
  GPIO_InitStruct.Pin = TP_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TP_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : VCI_EN_Pin LCD_RESET_Pin */
  GPIO_InitStruct.Pin = VCI_EN_Pin|LCD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : TP_RST_Pin */
  GPIO_InitStruct.Pin = TP_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TP_RST_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
