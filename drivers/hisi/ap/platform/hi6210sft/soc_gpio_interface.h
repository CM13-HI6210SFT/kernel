#ifndef __SOC_GPIO_INTERFACE_H__
#define __SOC_GPIO_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_GPIO_GPIODATA_0_ADDR(base) ((base) + (0x0004))
#define SOC_GPIO_GPIODATA_1_ADDR(base) ((base) + (0x0008))
#define SOC_GPIO_GPIODATA_2_ADDR(base) ((base) + (0x0010))
#define SOC_GPIO_GPIODATA_3_ADDR(base) ((base) + (0x0020))
#define SOC_GPIO_GPIODATA_4_ADDR(base) ((base) + (0x0040))
#define SOC_GPIO_GPIODATA_5_ADDR(base) ((base) + (0x0080))
#define SOC_GPIO_GPIODATA_6_ADDR(base) ((base) + (0x0100))
#define SOC_GPIO_GPIODATA_7_ADDR(base) ((base) + (0x0200))
#define SOC_GPIO_GPIODIR_ADDR(base) ((base) + (0x400))
#define SOC_GPIO_GPIOIS_ADDR(base) ((base) + (0x404))
#define SOC_GPIO_GPIOIBE_ADDR(base) ((base) + (0x408))
#define SOC_GPIO_GPIOIEV_ADDR(base) ((base) + (0x40C))
#define SOC_GPIO_GPIOIE_ADDR(base) ((base) + (0x410))
#define SOC_GPIO_GPIOIE2_ADDR(base) ((base) + (0x500))
#define SOC_GPIO_GPIOIE3_ADDR(base) ((base) + (0x504))
#define SOC_GPIO_GPIORIS_ADDR(base) ((base) + (0x414))
#define SOC_GPIO_GPIOMIS_ADDR(base) ((base) + (0x418))
#define SOC_GPIO_GPIOMIS2_ADDR(base) ((base) + (0x530))
#define SOC_GPIO_GPIOMIS3_ADDR(base) ((base) + (0x534))
#define SOC_GPIO_GPIOIC_ADDR(base) ((base) + (0x41C))
#define SOC_GPIO_GPIOAFSEL_ADDR(base) ((base) + (0x420))
#define SOC_GPIO_GPIODEBBYP_ADDR(base) ((base) + (0x618))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_0_UNION;
#endif
#define SOC_GPIO_GPIODATA_0_data_register_START (0)
#define SOC_GPIO_GPIODATA_0_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_GPIO_GPIODATA_1_UNION;
#endif
#define SOC_GPIO_GPIODATA_1_data_register_START (0)
#define SOC_GPIO_GPIODATA_1_data_register_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_2_UNION;
#endif
#define SOC_GPIO_GPIODATA_2_data_register_START (0)
#define SOC_GPIO_GPIODATA_2_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_3_UNION;
#endif
#define SOC_GPIO_GPIODATA_3_data_register_START (0)
#define SOC_GPIO_GPIODATA_3_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_4_UNION;
#endif
#define SOC_GPIO_GPIODATA_4_data_register_START (0)
#define SOC_GPIO_GPIODATA_4_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_5_UNION;
#endif
#define SOC_GPIO_GPIODATA_5_data_register_START (0)
#define SOC_GPIO_GPIODATA_5_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_6_UNION;
#endif
#define SOC_GPIO_GPIODATA_6_data_register_START (0)
#define SOC_GPIO_GPIODATA_6_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODATA_7_UNION;
#endif
#define SOC_GPIO_GPIODATA_7_data_register_START (0)
#define SOC_GPIO_GPIODATA_7_data_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_direct : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODIR_UNION;
#endif
#define SOC_GPIO_GPIODIR_data_direct_START (0)
#define SOC_GPIO_GPIODIR_data_direct_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt_sense : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIS_UNION;
#endif
#define SOC_GPIO_GPIOIS_interrupt_sense_START (0)
#define SOC_GPIO_GPIOIS_interrupt_sense_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt_sense : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIBE_UNION;
#endif
#define SOC_GPIO_GPIOIBE_interrupt_sense_START (0)
#define SOC_GPIO_GPIOIBE_interrupt_sense_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt_event : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIEV_UNION;
#endif
#define SOC_GPIO_GPIOIEV_interrupt_event_START (0)
#define SOC_GPIO_GPIOIEV_interrupt_event_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt_mask : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIE_UNION;
#endif
#define SOC_GPIO_GPIOIE_interrupt_mask_START (0)
#define SOC_GPIO_GPIOIE_interrupt_mask_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt2_mask : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIE2_UNION;
#endif
#define SOC_GPIO_GPIOIE2_interrupt2_mask_START (0)
#define SOC_GPIO_GPIOIE2_interrupt2_mask_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt3_mask : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIE3_UNION;
#endif
#define SOC_GPIO_GPIOIE3_interrupt3_mask_START (0)
#define SOC_GPIO_GPIOIE3_interrupt3_mask_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int raw_interrupt_status : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIORIS_UNION;
#endif
#define SOC_GPIO_GPIORIS_raw_interrupt_status_START (0)
#define SOC_GPIO_GPIORIS_raw_interrupt_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int masked_interrupt_status : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOMIS_UNION;
#endif
#define SOC_GPIO_GPIOMIS_masked_interrupt_status_START (0)
#define SOC_GPIO_GPIOMIS_masked_interrupt_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int masked_interrupt2_status : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOMIS2_UNION;
#endif
#define SOC_GPIO_GPIOMIS2_masked_interrupt2_status_START (0)
#define SOC_GPIO_GPIOMIS2_masked_interrupt2_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int masked_interrupt3_status : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOMIS3_UNION;
#endif
#define SOC_GPIO_GPIOMIS3_masked_interrupt3_status_START (0)
#define SOC_GPIO_GPIOMIS3_masked_interrupt3_status_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int interrupt_status_clear : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOIC_UNION;
#endif
#define SOC_GPIO_GPIOIC_interrupt_status_clear_START (0)
#define SOC_GPIO_GPIOIC_interrupt_status_clear_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode_control_select_register : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIOAFSEL_UNION;
#endif
#define SOC_GPIO_GPIOAFSEL_mode_control_select_register_START (0)
#define SOC_GPIO_GPIOAFSEL_mode_control_select_register_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int input_filter : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_GPIO_GPIODEBBYP_UNION;
#endif
#define SOC_GPIO_GPIODEBBYP_input_filter_START (0)
#define SOC_GPIO_GPIODEBBYP_input_filter_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
