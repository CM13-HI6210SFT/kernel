/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : lt_nv_common_interface.h
  版 本 号   : 初稿
  作    者   : wangxu
  生成日期   : 2014年3月13日
  最近修改   :
  功能描述   : TL 公共NV定义
  函数列表   :
  修改历史   :
  1.日    期   : 2014年3月13日
    作    者   : wangxu
    修改内容   : 创建文件
--------------------------------------------------------------------------------


******************************************************************************/


#ifndef __LT_NV_COMMON_INTERFACE_H__
#define __LT_NV_COMMON_INTERFACE_H__
#include "TLPhyInterface.h"
#include "LNvCommon.h"/*alex nv write*/

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/
#define TL_DCXO_POLY_COEF_NUM									(4)
#define TL_DCXO_TEMP_AFC_MAX_NUM          						(144)
#define TL_DCXO_UNITARY_TEMP									(250)
#define TL_DCXO_POLY_COEF_DEFAULT_A0_MANTISSA					(0)
#define TL_DCXO_POLY_COEF_DEFAULT_A0_EXP						(0)
#define TL_DCXO_POLY_COEF_DEFAULT_A1_MANTISSA					(1920998616)
#define TL_DCXO_POLY_COEF_DEFAULT_A1_EXP						(49154)
#define TL_DCXO_POLY_COEF_DEFAULT_A2_MANTISSA					(144403660)
#define TL_DCXO_POLY_COEF_DEFAULT_A2_EXP						(16379)
#define TL_DCXO_POLY_COEF_DEFAULT_A3_MANTISSA					(3271384601)
#define TL_DCXO_POLY_COEF_DEFAULT_A3_EXP						(16369)


/************************************************************
                               枚举定义
************************************************************/


/************************************************************
                             数据结构定义
************************************************************/
/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 保存DCXO多项式的 4个系数和温度的最大最小值
*****************************************************************************/
typedef struct
{
	UINT32							aulMantissaDefault[TL_DCXO_POLY_COEF_NUM];  /* 依次存放a0,a1,a2,a3的尾数 */
	UINT16							ausExponentDefault[TL_DCXO_POLY_COEF_NUM]; /* 依次存放a0,a1,a2,a3的指数 */
	INT16							sTmax;								/* 样本温度最大值 */
	INT16							sTmin;								/* 样本温度最小值 */
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU;

enum TLCOMM_NV_32K_TYPE_ENUM
{
    TLCOMM_NV_32K_TYPE_32000            = 0,        /*32k时钟个数32000*/
    TLCOMM_NV_32K_TYPE_32764            = 1,        /*32k时钟个数32764*/
    TLCOMM_NV_32K_TYPE_32768            = 2     /*32k时钟个数32768*/
};
typedef UINT16 TLCOMM_NV_32K_TYPE_ENUM_UINT16;

enum TLCOMM_NV_SINGLE_XO_TYPE_ENUM
{
    TLCOMM_NV_SINGLE_XO_TYPE_UNSUPPORT    = 0,                                    /* 不支持单时钟 */                                                           /* 上行仅存在DPCH */
    TLCOMM_NV_SINGLE_XO_TYPE_TCXO         = 1,                                    /* 单TCXO */                                                           /* 上行存在RACH */
    TLCOMM_NV_SINGLE_XO_TYPE_DCXO         = 2,                                    /* 单DCXO */
    TLCOMM_NV_SINGLE_XO_TYPE_BUTT
};
typedef UINT16 TLCOMM_NV_SINGLE_XO_TYPE_ENUM_UINT16;

typedef struct
{
    TLCOMM_NV_SINGLE_XO_TYPE_ENUM_UINT16 enSingleXoType;                    /*单时钟类型*/
    TLCOMM_NV_32K_TYPE_ENUM_UINT16       en32kType;                         /*32k时钟频率类型*/
}TLCOMM_NV_SINGLE_XO_DEFINE_STRU;

/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 存放一组DCXO的温度-频率(实际为AFC控制值)样本
*****************************************************************************/
typedef struct
{
    INT16                           sTemp;                                /* 温度 */
    INT16                           sFreqPpm;                             /* 上面温度下对应的相对频偏 */
}TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU;


/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO读取温度的周期,区分IDLE态和DCH态
*****************************************************************************/
typedef struct
{
    UINT16                          usIdlePeriod;                          /* IDLE态下读取周期 */
    UINT16                          usConnPeriod;                          /* CONN态下读取周期 */
}TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU;


/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO多项式系数更新门限
*****************************************************************************/
typedef struct
{
    UINT8   ucMinSampleNum;
    UINT8   ucMaxSampleNUm;
    UINT8   ucSampleInStep;
    UINT8   ucRsv;
    UINT16  usSampleInThr;
    INT16   sCoefVerifyTemp;
}TLCOMM_NV_DCXO_TEMP_CTRL_THR_ONE_AREA_STRU;
typedef struct
{
    INT16                                 sMinTemp;
    INT16                                 sMaxTemp;
    INT16                                 sLowestHighTempAreaThr;
    INT16                                 sHighestLowTempAreaThr;
	TLCOMM_NV_DCXO_TEMP_CTRL_THR_ONE_AREA_STRU astTempCtrlOneArea[3];
}TLCOMM_NV_DCXO_TEMP_CTRL_THR_STRU;
/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCXO多项式系数更新门限
*****************************************************************************/
typedef struct
{
    UINT32                          aulLowMantissa[TL_DCXO_POLY_COEF_NUM];
    UINT16                          ausLowExponent[TL_DCXO_POLY_COEF_NUM];
    UINT32                          aulHighMantissa[TL_DCXO_POLY_COEF_NUM];
    UINT16                          ausHighExponent[TL_DCXO_POLY_COEF_NUM];
    TLCOMM_NV_DCXO_TEMP_CTRL_THR_STRU stTempCtrlThr;
}TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU;


/*****************************************************************************
 结构名    : TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 存放DCXO的温度-频率(实际为AFC控制值)样本集合
*****************************************************************************/
#if 0
typedef struct
{
    UINT32                          uwValidNum;                             /* 样本的有效个数 */
    INT16                           shwTmax;                                /* 样本温度最大值 */
    INT16                           shwTmin;                                /* 样本温度最小值 */
    TLCOMM_NV_DCXO_AFC_VS_TEMP_VALUE_STRU astAfcTempValue[TL_DCXO_TEMP_AFC_MAX_NUM]; /* 样本数据 */
}TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;
#endif

#define TL_DCXO_TEMP_AFC_ONE_AREA_MAX_NUM                           (40)
typedef struct
{
    INT16                           sTemp;                                /* 温度 0.1*/
    INT16                           sFreqPpm;                             /* 上面温度下对应的相对频偏 */
}TLCOMM_NV_DCXO_T2F_SAMPLE_STRU;

typedef struct
{
    UINT8   ucValidNum;
    UINT8   ucWriteIdx;
    UINT8   ucMinSampleNum;
    UINT8   ucMaxSampleNUm;
    UINT8   ucSampleInStep;
    UINT8   ucRsv;
    UINT16  usSampleInThr;
    INT16   sCoefVerifyTemp;
    INT16   sRsv;
    TLCOMM_NV_DCXO_T2F_SAMPLE_STRU astSample[TL_DCXO_TEMP_AFC_ONE_AREA_MAX_NUM];
}TLCOMM_NV_DCXO_T2F_ONE_TEMP_AREA_STRU;

#define TLCOMM_NV_DCXO_T2F_LOW_TEMP_AREA_IDX                    (0)
#define TLCOMM_NV_DCXO_T2F_MID_TEMP_AREA_IDX                    (1)
#define TLCOMM_NV_DCXO_T2F_HIGH_TEMP_AREA_IDX                   (2)
typedef struct
{
    INT16                                 sMinTemp;
    INT16                                 sMaxTemp;
    INT16                                 sLowestHighTempAreaThr;
    INT16                                 sHighestLowTempAreaThr;
    TLCOMM_NV_DCXO_T2F_ONE_TEMP_AREA_STRU astTempArea[3];
}TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU;
/*end*/

typedef struct
{
    UINT32                                      ulCoefValid;                /*计算的校准系数是否有效*/
    TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU     stCoef;                     /*差值3次方曲线系数*/
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_STRU;

typedef struct
{
    TLCOMM_NV_DCXO_TEMP_COMP_POLY_STRU astcoef[3];
}TLCOMM_NV_DCXO_TEMP_COMP_POLY_ALL_STRU;

typedef struct
{
    INT16  sInitCfix;
    UINT16 usFreqErrThreshold;
    UINT16 usCfixLowerLimit;
    UINT16 usCfixUpperLimit;
}NV_DCXO_C_TRIM_DEFAULT;

typedef struct
{
    UINT16 usC2fixLowerLimit;
    UINT16 usC2fixUpperLimit;
    UINT16 usC2fixFactoryCal;
	UINT16 usRsv;
}NV_DCXO_C2_FIX_DEFAULT;

typedef struct
{
    INT16 sInitAfc;
	INT16 sInitTemperature;
}NV_XO_INIT_FREQUENCY;

typedef struct
{
    INT16  sCtrim;
	UINT16 usRsv;
}NV_DCXO_C_TRIM;

typedef struct
{
    INT16  sC2fix;
	UINT16 usRsv;
}NV_DCXO_C2_FIX;

typedef struct
{
	UINT32 ulTLCommNVSize;
}TL_COMM_NV_SIZE_PARA_STRU;

typedef struct
{
    UINT16 usAptPdmHoldNtxFlag;     /* 1: 有效 0: 无效*/
    UINT16 usUseAptFlg;             /* PUCCH/PRACH/SRS信道强制使用APT标志，1:使用 0:不强制，只在EAGLE下使用 */
}TL_COMM_NV_APT_PDM_CFG_PARA_STRU;

/*****************************************************************************
 结构名    : TLCOMM_NV_PARA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : TL 公共NV
*****************************************************************************/
typedef struct
{
	TL_COMM_NV_SIZE_PARA_STRU	  stNvSize;
	NV_DCXO_C_TRIM_DEFAULT        stDcxoCTrimdefault;
	NV_DCXO_C2_FIX_DEFAULT        stDcxoC2Fixdefault;
	NV_XO_INIT_FREQUENCY          stXoInitFrequency;
	NV_DCXO_C_TRIM                stDcxoCTrim;
	NV_DCXO_C2_FIX                stDcxoC2Fix;

	TLCOMM_NV_DCXO_TEMP_COMP_POLY_COEF_STRU stDcxoDefaultPlyCoef;/*DCXO 温补多项式缺省系数*/
	TLCOMM_NV_DCXO_TEMP_COMP_THRESHOLD_STRU stDcxoPlyCoefUpdateThr;/*DCXO温补系数刷新门限*/
	TLCOMM_NV_DCXO_FREQ_VS_TEMP_ARRAY_STRU  stDcxoFrqToTempBuffer;/*温度ppm样本*/
	TLCOMM_NV_DCXO_TEMP_READ_PERIOD_STRU	stDcxoTempSamplePeriod;/*温度频偏采样周期*/
	TLCOMM_NV_DCXO_TEMP_COMP_POLY_ALL_STRU  stDcxoCmpPlyCoef;/*DCXO 温补多项式计算系数*/
    TL_COMM_NV_APT_PDM_CFG_PARA_STRU        stAptPdmCfgPara; /* apt_pdm相关配置 */
}TLCOMM_NV_PARA_STRU;

extern TLCOMM_NV_PARA_STRU *gpTLNvCommPara;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LT_NV_COMMON_INTERFACE_H__ */


