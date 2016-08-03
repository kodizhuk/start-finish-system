/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _DS1307_H
#define _DS1307_H

#include <I2C.h>
#include <I2C_I2C.h>

typedef struct
{
    uint8_t second;
    uint8_t minutes;
    uint8_t hours;
    uint8_t timeFormat;
    uint8_t AmRm;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint16_t year;  
}DS1307_DATE_TIME;

#define DS1307_SLAVE_ADRESS (0x68)
#define DS1307_NULL_ADRESS  (0x00)
#define DS1307_NUMBER_OF_BYTES     (0x07)

#define DS1307_SEC_MASK         (0x0f)
#define DS1307_10_SEC_MASK      (0x70)
#define DS1307_MIN_MASK         (0x0f)
#define DS1307_10_MIN_MASK      (0x70)
#define DS1307_HOUR_MASK        (0x0f)
#define DS1307_10_12HOUR_MASK   (0x10)
#define DS1307_10_24HOUR_MASK   (0x30)
#define DS1307_DAY_MASK         (0x07)
#define DS1307_DATE_MASK        (0x0f)
#define DS1307_10_DATE_MASK     (0x30)
#define DS1307_MONTH_MASK       (0x0f)
#define DS1307_10_MONTH_MASK    (0x10)
#define DS1307_YEAR_MASK        (0x0f)
#define DS1307_10_YEAR_MASK     (0xf0)
#define DS1307_TIME_FORMAT_MASK (0x40)
#define DS1307_AM_RM_MASK       (0x20)
#define DS1307_OFF_MASK         (0x80)

#define DS1307_SEC_ADRESS   (0x00)
#define DS1307_MIN_ADRESS   (0x01)
#define DS1307_HOUR_ADRESS  (0x02)
#define DS1307_DAY_ADRESS   (0x03)
#define DS1307_DATE_ADRESS  (0x04)
#define DS1307_MONTH_ADRESS (0x05)
#define DS1307_YEAR_ADRESS  (0x06)

/* Time format definitions */
#define DS1307_PM                  (0u)
#define DS1307_AM                  (1u)
#define DS1307_12TIME_FORMAT       (0u)
#define DS1307_24TIME_FORMAT       (1u)
#define DS1307_UNIX_TIME_PM   ((12uL * 3600uL) + 1uL)

/* Definition of time register fields */
#define DS1307_TIME_FORMAT_OFFSET     (23u)
#define DS1307_PERIOD_OF_DAY_OFFSET   (22u)
#define DS1307_10_HOURS_OFFSET        (20u)
#define DS1307_HOURS_OFFSET           (16u)
#define DS1307_10_MINUTES_OFFSET      (12u)
#define DS1307_MINUTES_OFFSET         (8u)
#define DS1307_10_SECONDS_OFFSET      (4u)
#define DS1307_SECONDS_OFFSET         (0u)

/* Definition of date register fields */
#define DS1307_10_MONTH_OFFSET   (28u)
#define DS1307_MONTH_OFFSET      (24u)
#define DS1307_10_DAY_OFFSET     (20u)
#define DS1307_DAY_OFFSET        (16u)
#define DS1307_1000_YEAR_OFFSET  (12u)
#define DS1307_100_YEAR_OFFSET   (8u)
#define DS1307_10_YEAR_OFFSET    (4u)
#define DS1307_YEAR_OFFSET       (0u)

/*Define for unix time*/
/* UNIX time begins in 1970 year.  */
#define DS1307_YEAR_0             (1970u)
#define DS1307_SECONDS_PER_LEAP_YEAR    (366uL * 24uL * 3600uL)
#define DS1307_SECONDS_PER_NONLEAP_YEAR (365uL * 24uL * 3600uL)
#define DS1307_MONTHS_PER_YEAR     (12uL)
#define DS1307_HOURS_PER_DAY       (24uL)
#define DS1307_HOURS_PER_HALF_DAY  (12uL)
#define DS1307_SECONDS_PER_MINUTE  (60uL)
#define DS1307_SECONDS_PER_HOUR    (3600uL)
#define DS1307_SECONDS_PER_DAY     (24uL * 3600uL)

#define DS1307_10_MONTH_MASK_UNIX          (0x00000001uL << DS1307_10_MONTH_OFFSET)
#define DS1307_MONTH_MASK_UNIX             (0x0000000FuL << DS1307_MONTH_OFFSET)
#define DS1307_10_DAY_MASK_UNIX            (0x00000003uL << DS1307_10_DAY_OFFSET)
#define DS1307_DAY_MASK_UNIX               (0x0000000FuL << DS1307_DAY_OFFSET)
#define DS1307_1000_YEAR_MASK_UNIX         (0x00000003uL << DS1307_1000_YEAR_OFFSET)
#define DS1307_100_YEAR_MASK_UNIX          (0x0000000FuL << DS1307_100_YEAR_OFFSET)
#define DS1307_10_YEAR_MASK_UNIX           (0x0000000FuL << DS1307_10_YEAR_OFFSET)
#define DS1307_YEAR_MASK_UNIX              (0x0000000FuL << DS1307_YEAR_OFFSET)

#define DS1307_TIME_FORMAT_MASK_UNIX       (0x00000001uL << DS1307_TIME_FORMAT_OFFSET)
#define DS1307_PERIOD_OF_DAY_MASK_UNIX     (0x00000001uL << DS1307_PERIOD_OF_DAY_OFFSET)
#define DS1307_10_HOURS_MASK_UNIX          (0x00000003uL << DS1307_10_HOURS_OFFSET)
#define DS1307_HOURS_MASK_UNIX             (0x0000000FuL << DS1307_HOURS_OFFSET)
#define DS1307_10_MINUTES_MASK_UNIX        (0x00000007uL << DS1307_10_MINUTES_OFFSET)
#define DS1307_MINUTES_MASK_UNIX           (0x0000000FuL << DS1307_MINUTES_OFFSET)
#define DS1307_10_SECONDS_MASK_UNIX        (0x00000007uL << DS1307_10_SECONDS_OFFSET)
#define DS1307_SECONDS_MASK_UNIX           (0x0000000FuL << DS1307_SECONDS_OFFSET)

/* Number of days in month definitions */
#define DS1307_DAYS_IN_JANUARY     (31u)
#define DS1307_DAYS_IN_FEBRUARY    (28u)
#define DS1307_DAYS_IN_MARCH       (31u)
#define DS1307_DAYS_IN_APRIL       (30u)
#define DS1307_DAYS_IN_MAY         (31u)
#define DS1307_DAYS_IN_JUNE        (30u)
#define DS1307_DAYS_IN_JULY        (31u)
#define DS1307_DAYS_IN_AUGUST      (31u)
#define DS1307_DAYS_IN_SEPTEMBER   (30u)
#define DS1307_DAYS_IN_OCTOBER     (31u)
#define DS1307_DAYS_IN_NOVEMBER    (30u)
#define DS1307_DAYS_IN_DECEMBER    (31u)

/* Month definitions */
#define DS1307_JANUARY    (1)
#define DS1307_FEBRUARY   (2)
#define DS1307_MARCH      (3)
#define DS1307_APRIL      (4)
#define DS1307_MAY        (5)
#define DS1307_JUNE       (6)
#define DS1307_JULY       (7)
#define DS1307_AUGUST     (8)
#define DS1307_SEPTEMBER  (9)
#define DS1307_OCTOBER    (10)
#define DS1307_NOVEMBER   (11)
#define DS1307_DECEMBER   (12)

static uint16 DS1307_daysBeforeMonthTbl1[DS1307_MONTHS_PER_YEAR] = {
                                                 (0u), /* JANUARY */
                                                 (0u + 31u), /* FEBRUARY */
                                                 (0u + 31u + 28u), /* MARCH */
                                                 (0u + 31u + 28u + 31u), /* APRIL */
                                                 (0u + 31u + 28u + 31u + 30u), /* MAY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u), /* JUNE */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u), /* JULY */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u), /* AUGUST */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u), /* SEPTEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u), /* OCTOBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u), /* NOVEMBER */
                                                 (0u + 31u + 28u + 31u + 30u + 31u + 30u + 31u + 31u + 30u + 31u + 30u)}; /* DECEMBER */

static uint8 DS1307_daysInMonthTbl[DS1307_MONTHS_PER_YEAR] = {DS1307_DAYS_IN_JANUARY,
                                                            DS1307_DAYS_IN_FEBRUARY,
                                                            DS1307_DAYS_IN_MARCH,
                                                            DS1307_DAYS_IN_APRIL,
                                                            DS1307_DAYS_IN_MAY,
                                                            DS1307_DAYS_IN_JUNE,
                                                            DS1307_DAYS_IN_JULY,
                                                            DS1307_DAYS_IN_AUGUST,
                                                            DS1307_DAYS_IN_SEPTEMBER,
                                                            DS1307_DAYS_IN_OCTOBER,
                                                            DS1307_DAYS_IN_NOVEMBER,
                                                            DS1307_DAYS_IN_DECEMBER};

static uint32 DS1307_ReadTimeToStruct(void);
static uint32_t DS1307_WriteTimeFromStruct(void);
static uint32_t DS1307_ConstructTime(uint32 timeFormat, uint32 stateAmPm, uint32 hour, uint32 min, uint32 sec);
static uint32 DS1307_ConstructDate(uint32 month, uint32 day, uint32 year);
static uint64 DS1307_DateTimeToUnix(uint32 inputDate, uint32 inputTime);

/*user function*/
uint64_t DS1307_GetUnixTime(void);
void DS1307_SetUnixTime(uint64_t time);
void DS1307_Start(void);
void DS1307_Stop(void);

#endif

/* [] END OF FILE */
