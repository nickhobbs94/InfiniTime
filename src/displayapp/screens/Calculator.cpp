#include "displayapp/screens/Calculator.h"
#include <cstdio>
#include <cstdlib>
#include <lvgl/lvgl.h>
#include "libs/TOTP-MCU/sha1.h"
#include "libs/TOTP-MCU/TOTP.h"
#include "libs/TOTP-MCU/sha1.c"
#include "libs/TOTP-MCU/TOTP.c"


using namespace Pinetime::Applications::Screens;

Calculator::Calculator(Pinetime::Applications::DisplayApp* app, Controllers::DateTime& dateTimeController) : Screen(app), dateTimeController {dateTimeController} {
  lv_obj_t* label;

  lv_style_init(&btn_style);
  lv_style_set_radius(&btn_style, LV_STATE_DEFAULT, 20);
  lv_style_set_bg_color(&btn_style, LV_STATE_DEFAULT, LV_COLOR_AQUA);
  lv_style_set_bg_opa(&btn_style, LV_STATE_DEFAULT, LV_OPA_50);

  btnPlayPause = lv_btn_create(lv_scr_act(), nullptr);
  btnPlayPause->user_data = this;
  lv_obj_set_size(btnPlayPause, 76, 76);
  lv_obj_align(btnPlayPause, nullptr, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_add_style(btnPlayPause, LV_STATE_DEFAULT, &btn_style);
  txtPlayPause = lv_label_create(btnPlayPause, nullptr);

  // format score text
  scoreText = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_width(scoreText, LV_HOR_RES);
  lv_label_set_align(scoreText, LV_ALIGN_IN_LEFT_MID);
  lv_obj_align(scoreText, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_label_set_recolor(scoreText, true);
  lv_label_set_text_fmt(scoreText, "Score #FFFF00 %i#", score);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

Calculator::~Calculator() {
  lv_task_del(taskRefresh);
  lv_style_reset(&btn_style);
  lv_obj_clean(lv_scr_act());
}

bool Calculator::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  score += 1;
  const int x = dateTimeController.UTCDateTime().time_since_epoch() / std::chrono::seconds(1);
  uint8_t hmacKey[] = {0x4d, 0x79, 0x4c, 0x65, 0x67, 0x6f, 0x44, 0x6f, 0x6f, 0x72};
  TOTP(hmacKey, 6, 60);
  const u_int32_t y = getCodeFromTimestamp(x);
  lv_label_set_text_fmt(scoreText, "TOTP #FFFF00 %06i#", y);
  return true;
}




