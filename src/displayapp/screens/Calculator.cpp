#include "displayapp/screens/Calculator.h"
#include <cstdio>
#include <cstdlib>
#include <lvgl/lvgl.h>
#include "libs/TOTP-MCU/sha1.h"
#include "libs/TOTP-MCU/TOTP.h"
#include "libs/TOTP-MCU/sha1.c"
#include "libs/TOTP-MCU/TOTP.c"
#include "secrets/totp-secret.h"


using namespace Pinetime::Applications::Screens;

Calculator::Calculator(Pinetime::Applications::DisplayApp* app, Controllers::DateTime& dateTimeController) : Screen(app), dateTimeController {dateTimeController} {

  // format unix time text
  unixTimeText = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_width(unixTimeText, LV_HOR_RES);
  lv_label_set_align(unixTimeText, LV_ALIGN_IN_LEFT_MID);
  lv_obj_align(unixTimeText, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  lv_label_set_recolor(unixTimeText, true);
  lv_label_set_text_fmt(unixTimeText,  "Unix Timestamp: \n#FFFF00 %i#", 0);

  // format aws key text
  awsKey = lv_label_create(lv_scr_act(), nullptr);
  lv_obj_set_width(awsKey, LV_HOR_RES);
  lv_label_set_align(awsKey, LV_ALIGN_IN_LEFT_MID);
  lv_obj_align(awsKey, nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 50);
  lv_label_set_recolor(awsKey, true);
  lv_label_set_text_fmt(awsKey,        "AWS: #FFFF00 %06i#", 0);

  taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

Calculator::~Calculator() {
  lv_task_del(taskRefresh);
  lv_obj_clean(lv_scr_act());
}

void Calculator::UpdateTOTP() {
  const int unixTime = dateTimeController.UTCDateTime().time_since_epoch() / std::chrono::seconds(1);
  lv_label_set_text_fmt(unixTimeText,  "Unix Timestamp: \n#FFFF00 %i#", unixTime);
  TOTP(AWS_KEY, 40, 30);
  lv_label_set_text_fmt(awsKey, "AWS: #FFFF00 %06i#", getCodeFromTimestamp(unixTime));
}

void Calculator::Refresh(){
  UpdateTOTP();
}

bool Calculator::OnTouchEvent(Pinetime::Applications::TouchEvents event) {
  UpdateTOTP();
  return true;
}




