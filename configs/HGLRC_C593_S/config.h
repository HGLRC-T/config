/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU                   STM32C591

#define BOARD_NAME                      HGLRC_C593_S
#define MANUFACTURER_ID                 HGLR

// HSE 8 MHz crystal on PH0/PH1 (Y1)
#define SYSTEM_HSE_MHZ                  8

// Config persists in the C591 internal flash (CONFIG_IN_FLASH, the default
// backend -- __config_start = 0x080FC000, a 16 KB region in the last two 8 KB
// pages of the 1 MB part). This avoids the early boot-time SPI3 read that the
// external flash (W25Q128) needs, which the C5 polled-SPI path corrupts before
// DMA is up. The W25Q128 still serves the blackbox.

// --- USB VCP -------------------------------------------------------------
// OTG FS on PA11 (D-) / PA12 (D+); USB VBUS sense on PC3.
#define USE_VCP

// --- Status LED ----------------------------------------------------------
#define LED0_PIN                        PC0
#define LED1_PIN                        PC5

// --- UART pin map --------------------------------------------------------
#define UART1_TX_PIN                    PB6
#define UART1_RX_PIN                    PB7

#define UART2_TX_PIN                    PA2
#define UART2_RX_PIN                    PA3

#define UART3_TX_PIN                    PB10
#define UART3_RX_PIN                    PC4

#define UART4_TX_PIN                    PA0
#define UART4_RX_PIN                    PA1

#define UART5_RX_PIN                    PD2

#define USE_UART6
#define UART6_TX_PIN                    PC6
#define UART6_RX_PIN                    PC7

// --- IMU on SPI1 ---------------------------------------------------------
// SPI1 SCK=PA5, MISO=PA6, MOSI=PA7, CS=PA4, INT/DRDY=PB2.
// U3 is populated with ICM-42688-P. An LSM6DSK320X may be fitted as an
// assembly alternative, but is not populated on this board revision.
#define USE_ACC
#define USE_GYRO
#define USE_GYRO_EXTI
#define USE_ACCGYRO_LSM6DSK320X
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO_SPI_ICM42688P

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN                    PA5
#define SPI1_SDI_PIN                    PA6
#define SPI1_SDO_PIN                    PA7

#define GYRO_1_SPI_INSTANCE             SPI1
#define GYRO_1_CS_PIN                   PA4
#define GYRO_1_EXTI_PIN                 PB2
#define GYRO_1_ALIGN                    CW0_DEG

// --- External flash: ZB25VQ128DWJG on SPI3 -------------------------------
// SPI3 SCK=PC10, MISO=PC11, MOSI=PC12, CS=PA15. PC12 is shared with the
// USART5 TX alternate function, but is wired only to flash on this board.
#define USE_SPI_DEVICE_3
#define SPI3_SCK_PIN                    PC10
#define SPI3_SDI_PIN                    PC11
#define SPI3_SDO_PIN                    PB5

#define USE_FLASH
#define USE_FLASH_M25P16
#define USE_FLASH_W25Q128FV
#define FLASH_SPI_INSTANCE              SPI3
#define FLASH_CS_PIN                    PA15

#define USE_FLASHFS
#define USE_BLACKBOX

// --- OSD: AT7456E on SPI2 ------------------------------------------------
// SPI2 SCK=PB13, MISO=PB14, MOSI=PB15 (AF5), CS=PB12.
#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN                    PB13
#define SPI2_SDI_PIN                    PB14
#define SPI2_SDO_PIN                    PB15

#define USE_MAX7456
#define MAX7456_SPI_INSTANCE            SPI2
#define MAX7456_SPI_CS_PIN              PB12

#define USE_OSD
// AT7456E is an SD (analog) OSD; declare USE_OSD_SD so common_pre.h does not
// auto-select USE_OSD_HD and short-circuit init.c onto the MSP OSD path.
#define USE_OSD_SD

// --- Baro: SPA06-003 (DPS310-compatible) on I2C1 -------------------------
// I2C1 SCL=PB8 and SDA=PB9. The same bus is exposed on the GPS connector.
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL_PIN                    PB8
#define I2C1_SDA_PIN                    PB9

#define USE_BARO
#define USE_BARO_DPS310
#define BARO_I2C_INSTANCE               I2CDEV_1

// --- Mag: external compass on I2C1 (GPS port) ----------------------------
#define USE_MAG
#define MAG_I2C_INSTANCE                I2CDEV_1

// --- LED strip -----------------------------------------------------------
#define USE_LED_STRIP
#define LED_STRIP_PIN                   PB3

// --- Motors ---------------------------------------------------------------
// M1=PC9, M2=PC8, M3=PB0, M4=PB1. The remaining four outputs are routed to
// PA10, PA9, PA8, and PB4, but are not enabled until their C591 timer map is
// verified on hardware.
#define MOTOR1_PIN                      PC9
#define MOTOR2_PIN                      PC8
#define MOTOR3_PIN                      PB0
#define MOTOR4_PIN                      PB1

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP(0, MOTOR1_PIN, 2, -1) \
    TIMER_PIN_MAP(1, MOTOR2_PIN, 2, -1) \
    TIMER_PIN_MAP(2, MOTOR3_PIN, 1, -1) \
    TIMER_PIN_MAP(3, MOTOR4_PIN, 1, -1) \
    TIMER_PIN_MAP(4, LED_STRIP_PIN, 1, -1)

// --- ADC: VBAT + current -------------------------------------------------
// PC2 = ADC channel 12 (VBAT divider), PC1 = ADC channel 11 (current sense).
// ADC1_DMA_OPT picks the first DMA spec for ADC1; the defaults make the
// external channels active (config.c forces .enabled = (source == ADC)).
#define USE_ADC
#define USE_ADC_INTERNAL
#define ADC_INSTANCE                    ADC1
#define ADC1_INSTANCE                   ADC1
#define ADC1_DMA_OPT                    0
#define ADC_VBAT_PIN                    PC2
#define ADC_CURR_PIN                    PC1
#define DEFAULT_VOLTAGE_METER_SOURCE    VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE    CURRENT_METER_ADC

#define DEFAULT_BLACKBOX_DEVICE         BLACKBOX_DEVICE_FLASH

#define ESC_SENSOR_UART      SERIAL_PORT_UART5
#define GPS_UART             SERIAL_PORT_UART4

// --- Buzzer --------------------------------------------------------------
// Passive buzzer driven by PC3 via Q1 (MMBT3904 NPN low-side, base pulled to
// GND) -- active high, idle-safe, so not inverted.
#define USE_BEEPER
#define BEEPER_PIN                      PC3

// --- PINIO: VTX/O4 power switch + camera switch --------------------------
// PC15 gates the 12 V BEC; PC14 selects CAM1/CAM2 through the video mux.
// Output push-pull, active high by default -- verify switch polarity on the
// bench and flip the *_CONFIG value (to 129) if a rail is inverted.
#define PINIO1_BOX           40
#define PINIO1_PIN           PC15
#define PINIO1_CONFIG        129
#define BOX_USER1_NAME       "12V BEC"

#define PINIO2_BOX           41
#define PINIO2_PIN           PC14
#define BOX_USER2_NAME       "Cam1,2"
