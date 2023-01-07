#pragma once

#include <lvgl/src/lv_core/lv_obj.h>
#include "displayapp/screens/Screen.h"
#include "components/datetime/DateTimeController.h"

namespace Pinetime {
  namespace Applications {
    namespace Screens {
      class Calculator : public Screen {
      public:
        Calculator(DisplayApp* app, Controllers::DateTime& dateTimeController);
        ~Calculator() override;

        bool OnTouchEvent(TouchEvents event) override;

      private:
        lv_style_t btn_style;
        lv_task_t* taskRefresh;
        lv_obj_t* btnPlayPause;
        lv_obj_t* txtPlayPause;

        lv_obj_t* scoreText;
        unsigned int score = 0;

        const Controllers::DateTime& dateTimeController;
      };
    }
  }
}
