/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include "balong_fb.h"

//#define ARRAY_SIZE(x)  (sizeof(x)/sizeof(x[0]))
// This macro is the decrement of R and G to improve the lcd's color temperature performence.
#define CT_CALIBRATION_VALUE 26
#define CHANGE_MAX	100
#define DISCOUNT_COEFFICIENT(value)  (CHANGE_MAX - value) / CHANGE_MAX
static unsigned  int g_comform_value = 0;
static u32 blue_coefficient = 0;
extern struct semaphore balong_fb_blank_sem;
extern u32 g_601_csc_value[10];
extern bool g_is_set_color_temperature;
extern struct semaphore g_ct_sem;
static u32 g_blue_coefficient = 0;
static bool g_comform_flag = false;
/*add lcd info*/
char g_lcd_name_buf[LCD_INFO_LENGTH] = "No LCD panel!";
static ssize_t lcd_info_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    snprintf(buf, PAGE_SIZE, "%s %d x %d\n", g_lcd_name_buf,
            hisifd->panel_info.xres, hisifd->panel_info.yres);

    ret = strlen(buf) + 1;
    return ret;

}
static ssize_t hisifb_sbl_ctrl_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int val = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    val = (int)simple_strtoul(buf, NULL, 0);
    if (hisifd->panel_info.sbl_enable) {
        down(&balong_fb_blank_sem);
        hisifd->sbl_lsensor_value =  val & 0xffff;
        hisifd->sbl_enable = (val >> 24) & 0x1;

        if (!hisifd->panel_power_on) {
            /* sbl first set, but panel is off,
             * can't set sbl, save sbl value and set it in the panel on
             */
            up(&balong_fb_blank_sem);
            return 0;
        }

        //use IC SRE function here
        pdata->set_sre(hisifd->pdev, hisifd->sbl_enable, hisifd->sbl_lsensor_value);
        up(&balong_fb_blank_sem);
    }
    return count;
}
static ssize_t hisifb_sbl_ctrl_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    snprintf(buf, PAGE_SIZE, "sbl_lsensor_value = %d, sbl_enable = %d\n",
            hisifd->sbl_lsensor_value, hisifd->sbl_enable);

    ret = strlen(buf) + 1;
    return ret;

}

static ssize_t hisifb_lcd_cabc_mode_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int ret = 0;
    int val = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    val = (int)simple_strtoul(buf, NULL, 0);
    if (pdata->lcd_cabc_mode_store) {
        down(&balong_fb_blank_sem);
        if (!hisifd->panel_power_on) {
            balongfb_loge("system is now power off !\n");
            up(&balong_fb_blank_sem);
            return 0;
        }
        ret = pdata->lcd_cabc_mode_store(hisifd->pdev, val);
        up(&balong_fb_blank_sem);
    }
    return count;
}

static ssize_t hisifb_lcd_cabc_mode_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }
    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }
    snprintf(buf, PAGE_SIZE, "cabc_mode = %d\n", hisifd->g_CABC_mode);
    ret = strlen(buf) + 1;
    return ret;
}

static ssize_t hisifb_lcd_check_reg_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    if (pdata->lcd_gram_check_show) {
        if (!hisifd->panel_power_on){
            balongfb_loge("system is now power off !\n");
            return 0;
        }
        ret = pdata->lcd_gram_check_show(hisifd->pdev);
    }
    snprintf(buf, PAGE_SIZE, "%d\n", ret);
    balongfb_logi("gram check lcd_readvalue = 0x%x\n", hisifd->lcd_readvalue);
    ret = strlen(buf) + 1;
    return ret;
}

static ssize_t hisifb_lcd_inversion_mode_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    snprintf(buf, PAGE_SIZE, "lcd_inversion_mode =  0x%x\n", hisifd->lcd_inversion_mode);
    ret = strlen(buf) + 1;
    return ret;
}

static ssize_t hisifb_lcd_inversion_mode_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd->lcd_inversion_mode = (int)simple_strtoul(buf, NULL, 0);
    if (pdata->lcd_inversion_mode_store) {
        down(&balong_fb_blank_sem);
        if (!hisifd->panel_power_on){
            balongfb_loge("system is now power off !\n");
            up(&balong_fb_blank_sem);
            return 0;
        }
        down(&hisifd->sem);
        ret = pdata->lcd_inversion_mode_store(hisifd->pdev, hisifd->lcd_inversion_mode);
        up(&hisifd->sem);
        up(&balong_fb_blank_sem);
    }
    return count;
}

static ssize_t hisifb_color_temperature_show(struct device* dev, 
        struct device_attribute* attr, char* buf)
{
    snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                g_601_csc_value [0], g_601_csc_value [1], g_601_csc_value [2],
                g_601_csc_value [3], g_601_csc_value [4], g_601_csc_value [5],
                g_601_csc_value [6], g_601_csc_value [7], g_601_csc_value [8]);
    return strlen(buf) + 1;
}

static ssize_t hisifb_color_temperature_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int i = 0;
    unsigned int csc_value[10];
    char *token, *cur;

    cur = buf;
    while (token = strsep(&cur, ",")) {
        csc_value[i++] = simple_strtol(token, NULL, 0);
    }

    down(&g_ct_sem);
    for (i = 0; i < 9; i++)
    {
        g_601_csc_value[i]= 2 * csc_value[i];
    }
    // This adjust is just designed for boe panel because it's performance too warm.
    if( colortemp_adjust_flag == 1 )
    {
        //Reduce the component value of R and G to improve CT value.
        g_601_csc_value [0] = g_601_csc_value [0] - CT_CALIBRATION_VALUE;
        g_601_csc_value [4] = g_601_csc_value [4] - CT_CALIBRATION_VALUE;
    }
    blue_coefficient = g_601_csc_value [8];
    g_601_csc_value [8] = g_601_csc_value [8] * DISCOUNT_COEFFICIENT(g_comform_value);
    g_is_set_color_temperature = true;
    up(&g_ct_sem);
    pr_info("Color_Temperature Paramaters: [R]= %d; [G]= %d; [B]= %d \n",g_601_csc_value [0],g_601_csc_value [4] ,g_601_csc_value [8]);
    return count;
}

static ssize_t hisifb_lcd_region_limit_show(struct device* dev,
        struct device_attribute* attr, char* buf)
{
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                hisifd->panel_info.dirty_region_info.left_align, hisifd->panel_info.dirty_region_info.right_align,
                hisifd->panel_info.dirty_region_info.top_align,hisifd->panel_info.dirty_region_info.bottom_align,
                hisifd->panel_info.dirty_region_info.w_align, hisifd->panel_info.dirty_region_info.h_align,
                hisifd->panel_info.dirty_region_info.w_min, hisifd->panel_info.dirty_region_info.h_min,
                hisifd->panel_info.dirty_region_info.top_start,hisifd->panel_info.dirty_region_info.bottom_start);

    return strlen(buf) + 1;
}

static ssize_t hisifb_lcd_region_limit_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int i = 0;
    int limit_value[11];
    char *token, *cur;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    cur = buf;
    while (token = strsep(&cur, ",")) {
        limit_value[i++] = (int)simple_strtol(token, NULL, 0);
    }

    hisifd->panel_info.dirty_region_info.left_align   = limit_value[0];
    hisifd->panel_info.dirty_region_info.right_align  = limit_value[1];
    hisifd->panel_info.dirty_region_info.top_align    = limit_value[2];
    hisifd->panel_info.dirty_region_info.bottom_align = limit_value[3];
    hisifd->panel_info.dirty_region_info.w_align      = limit_value[4];
    hisifd->panel_info.dirty_region_info.h_align      = limit_value[5];
    hisifd->panel_info.dirty_region_info.w_min        = limit_value[6];
    hisifd->panel_info.dirty_region_info.h_min        = limit_value[7];
    hisifd->panel_info.dirty_region_info.top_start    = limit_value[8];
    hisifd->panel_info.dirty_region_info.bottom_start = limit_value[9];

    return count;
}

static ssize_t hisifb_lcd_comform_mode_show(struct device *dev,
    struct device_attribute *attr, char *buf)
{
    if (NULL == dev || NULL == attr || NULL == buf) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }
    snprintf(buf, PAGE_SIZE, "%d,%d,%d,%d,%d,%d,%d,%d,%d,g_comform_value = %d\n",
                            g_601_csc_value [0], g_601_csc_value [1], g_601_csc_value [2],
                            g_601_csc_value [3], g_601_csc_value [4], g_601_csc_value [5],
                            g_601_csc_value [6], g_601_csc_value [7], g_601_csc_value [8],
                            g_comform_value);
    return strlen(buf) + 1;
}

static ssize_t hisifb_lcd_comform_mode_store(struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
    unsigned int val = 0;

    if (NULL == dev || NULL == attr || NULL == buf) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    down(&g_ct_sem);
    val = (unsigned int)simple_strtoul(buf, NULL, 0);
    g_comform_value = val;
    if (false == g_comform_flag)
    {
        g_comform_flag = true;
        g_blue_coefficient = g_601_csc_value[8];
    }
    if(val == 0)
    {
        g_601_csc_value [8] = blue_coefficient;
        g_blue_coefficient = 0;
        g_comform_flag = false;
    }
    else if(val <= 50)
    {
        blue_coefficient = g_601_csc_value [8];
        g_601_csc_value [8] = (g_blue_coefficient * DISCOUNT_COEFFICIENT(g_comform_value));
    }
    else
    {
        balongfb_logi("It can't support this level %u !\n", val);
        up(&g_ct_sem);
        return count;
    }
    balongfb_logi("comform_mode = %u !\n", val);
    g_is_set_color_temperature = true;
    up(&g_ct_sem);
    return count;
}

static ssize_t hisifb_lcd_scan_mode_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    snprintf(buf, PAGE_SIZE, "lcd_scan_mode =  0x%x\n", hisifd->lcd_scan_mode);
    ret = strlen(buf) + 1;
    return ret;
}

static ssize_t hisifb_lcd_scan_mode_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer\n");
        return -EINVAL;
    }

    hisifd->lcd_scan_mode = (int)simple_strtoul(buf, NULL, 0);
    if (NULL != strstr(saved_command_line, "androidboot.swtype=factory"))
    {
    if (pdata->lcd_scan_mode_store)
    {
        down(&balong_fb_blank_sem);
        if (!hisifd->panel_power_on)
        {
            balongfb_loge("system is now power off !\n");
            up(&balong_fb_blank_sem);
            return 0;
        }
        down(&hisifd->sem);
        ret = pdata->lcd_scan_mode_store(hisifd->pdev, hisifd->lcd_scan_mode);
        up(&hisifd->sem);
        up(&balong_fb_blank_sem);
    }
    }
    return count;
}

static ssize_t hisifb_lcd_support_mode_show(struct device *dev,
    struct device_attribute *attr, char *buf)
{
    ssize_t ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    if (NULL == dev) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    down(&balong_fb_blank_sem);
    if (pdata->lcd_support_mode_show) {
        ret = pdata->lcd_support_mode_show(hisifd->pdev, buf);
    }
    up(&balong_fb_blank_sem);

    return ret;
}

static ssize_t hisifb_lcd_support_mode_store(struct device *dev,
    struct device_attribute *attr, const char *buf, size_t count)
{
    ssize_t ret = 0;
    struct fb_info *fbi = NULL;
    struct balong_fb_data_type *hisifd = NULL;
    struct balong_fb_panel_data *pdata = NULL;

    if (NULL == dev) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    hisifd = (struct balong_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    pdata = dev_get_platdata(&hisifd->pdev->dev);
    if (NULL == pdata) {
        balongfb_loge("NULL Pointer!\n");
        return -EINVAL;
    }

    down(&balong_fb_blank_sem);
    if (pdata->lcd_support_mode_store) {
        ret = pdata->lcd_support_mode_store(hisifd->pdev, buf, count);
    }
    up(&balong_fb_blank_sem);
    return count;
}

/*lint -e665*/
static DEVICE_ATTR(sbl_ctrl, S_IRUGO|S_IWUSR, hisifb_sbl_ctrl_show, hisifb_sbl_ctrl_store);
static DEVICE_ATTR(lcd_model, S_IRUGO, lcd_info_show, NULL);
static DEVICE_ATTR(lcd_cabc_mode, S_IRUGO|S_IWUSR, hisifb_lcd_cabc_mode_show, hisifb_lcd_cabc_mode_store);
static DEVICE_ATTR(lcd_check_reg, S_IRUGO, hisifb_lcd_check_reg_show,NULL);
static DEVICE_ATTR(lcd_inversion_mode, S_IRUGO|S_IWUSR, hisifb_lcd_inversion_mode_show,hisifb_lcd_inversion_mode_store);
static DEVICE_ATTR(lcd_color_temperature, S_IRUGO|S_IWUSR, hisifb_color_temperature_show,hisifb_color_temperature_store);
static DEVICE_ATTR(lcd_region_limit, S_IRUGO|S_IWUSR, hisifb_lcd_region_limit_show,hisifb_lcd_region_limit_store);
static DEVICE_ATTR(lcd_scan_mode, S_IRUGO|S_IWUSR, hisifb_lcd_scan_mode_show, hisifb_lcd_scan_mode_store);
static DEVICE_ATTR(lcd_support_mode, S_IRUGO|S_IWUSR, hisifb_lcd_support_mode_show, hisifb_lcd_support_mode_store);
static DEVICE_ATTR(lcd_comform_mode, S_IRUGO|S_IWUSR, hisifb_lcd_comform_mode_show, hisifb_lcd_comform_mode_store);
/*lint +e665*/

static struct attribute *hisi_fb_attrs[] = {
    &dev_attr_sbl_ctrl.attr,
    &dev_attr_lcd_model.attr,
    &dev_attr_lcd_cabc_mode.attr,
    &dev_attr_lcd_check_reg.attr,
    &dev_attr_lcd_inversion_mode.attr,
    &dev_attr_lcd_color_temperature.attr,
    &dev_attr_lcd_region_limit.attr,
    &dev_attr_lcd_scan_mode.attr,
    &dev_attr_lcd_support_mode.attr,
    &dev_attr_lcd_comform_mode.attr,
    NULL,
};
static struct attribute_group hisi_fb_attr_group = {
    .attrs = hisi_fb_attrs,
};
//This function is used to init file nodes about lcd.
//Here,init cabc mode to UI Mode.
void init_hisi_fb_sysfs(struct balong_fb_data_type *balongfd)
{
    balongfd->g_CABC_mode = 1;
}
int hisi_fb_sysfs_create(struct platform_device *pdev)
{
    int ret = 0;
    struct balong_fb_data_type *balongfd = NULL;
    balongfd = platform_get_drvdata(pdev);
    BUG_ON(balongfd == NULL);

    ret = sysfs_create_group(&balongfd->fbi->dev->kobj, &hisi_fb_attr_group);
    if (ret) {
        balongfb_loge("create sysfs file failed, error=%d!\n", ret);
        return ret;
    }
    init_hisi_fb_sysfs(balongfd);
    return ret;
}

void hisi_fb_sysfs_remove(struct platform_device *pdev)
{
     struct balong_fb_data_type *balongfd = NULL;
    balongfd = platform_get_drvdata(pdev);
    BUG_ON(balongfd == NULL);

    sysfs_remove_group(&balongfd->fbi->dev->kobj, &hisi_fb_attr_group);
}
