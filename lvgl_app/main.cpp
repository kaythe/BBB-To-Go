#include <iostream>
#include <chrono>
#include <thread>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";

    lv_init();
    fbdev_init();
    evdev_init();

    static lv_disp_buf_t disp_buf;
    static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX];
    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);

    lv_disp_drv_t fb_drv;
    lv_disp_drv_init(&fb_drv);
    fb_drv.flush_cb = fbdev_flush;
    fb_drv.buffer = &disp_buf;
    lv_disp_drv_register(&fb_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = evdev_read;
    lv_indev_t * mouse = lv_indev_drv_register(&indev_drv);

    lv_obj_t * welcomeLabel = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(welcomeLabel, "Welcome to LVGL!");
    lv_obj_align(welcomeLabel, NULL, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * cursorObj = lv_led_create(lv_scr_act(), NULL);
    std::cout << mouse << cursorObj << std::endl;
    lv_indev_set_cursor(mouse, cursorObj);

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        lv_tick_inc(5);
        lv_task_handler();
    }

}
