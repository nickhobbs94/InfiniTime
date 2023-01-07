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
        void UpdateTOTP();
        void Refresh() override;

        bool OnTouchEvent(TouchEvents event) override;

      private:
        lv_task_t* taskRefresh;

        lv_obj_t* unixTimeText;
        lv_obj_t* awsKey;

        const Controllers::DateTime& dateTimeController;
      };
    }
  }
}
