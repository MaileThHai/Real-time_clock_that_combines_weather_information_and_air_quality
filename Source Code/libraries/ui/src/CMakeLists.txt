SET(SOURCES components/ui_comp_date.c
    components/ui_comp_dategroup.c
    components/ui_comp_temperaturegroup.c
    components/ui_comp.c
    screens/ui_HOME.c
    screens/ui_MENU.c
    screens/ui_ANALOGCLOCK.c
    screens/ui_SETDAYTIME.c
    screens/ui_SETALARM.c
    screens/ui_SETTIME.c
    screens/ui_SET_DATE.c
    screens/ui_SETALARM1.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_bggg_png.c
    images/ui_img_sun_png.c
    images/ui_img_clouds_png.c
    images/ui_img_rain_png.c
    images/ui_img_house_png.c
    images/ui_img_backblack_png.c
    images/ui_img_clock_hour_png.c
    images/ui_img_clock_min_png.c
    images/ui_img_clock_sec_png.c
    images/ui_img_backk_png.c
    images/ui_img_216451335.c)

add_library(ui ${SOURCES})
