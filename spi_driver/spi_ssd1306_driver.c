/****************************************************************************//**
*  \file       spi_ssd1306_driver.c
*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>

#include "ssd1306.h"

static struct spi_device *etx_spi_device;

/* SPI device info (legacy board-file style) */
struct spi_board_info etx_spi_device_info = {
  .modalias     = "etx-spi-ssd1306-driver",
  .max_speed_hz = 4000000,
  .bus_num      = SPI_BUS_NUM,
  .chip_select  = 0,
  .mode         = SPI_MODE_0
};

/****************************************************************************
 * SPI Write
 ****************************************************************************/
int etx_spi_write(uint8_t data)
{
  int ret;
  uint8_t rx = 0x00;

  if (!etx_spi_device)
    return -ENODEV;

  struct spi_transfer tr = {
    .tx_buf = &data,
    .rx_buf = &rx,
    .len    = 1,
  };

  ret = spi_sync_transfer(etx_spi_device, &tr, 1);
  return ret;
}

/****************************************************************************
 * SPI DEVICE ID TABLE  (IMPORTANT)
 ****************************************************************************/
static const struct spi_device_id etx_spi_ids[] = {
    { "etx-spi-ssd1306-driver", 0 },
    { }
};

/* 👉 This exposes the table for auto-loading */
MODULE_DEVICE_TABLE(spi, etx_spi_ids);

/****************************************************************************
 * PROBE
 ****************************************************************************/
static int etx_probe(struct spi_device *spi)
{
  int ret;

  pr_info("SPI OLED Probe Called\n");

  etx_spi_device = spi;

  spi->bits_per_word = 8;
  spi->mode = SPI_MODE_0;

  ret = spi_setup(spi);
  if (ret) {
    pr_err("SPI setup failed\n");
    return ret;
  }

  /* OLED INIT */
  ETX_SSD1306_DisplayInit();

  ETX_SSD1306_SetBrightness(255);
  ETX_SSD1306_InvertDisplay(false);

  ETX_SSD1306_StartScrollHorizontal(true, 0, 2);

  ETX_SSD1306_SetCursor(0, 0);
  ETX_SSD1306_String("Welcome\nTo\nEmbeTronicX\n");

  ETX_SSD1306_SetCursor(4, 35);
  ETX_SSD1306_String("SPI Linux\n");

  ETX_SSD1306_SetCursor(5, 23);
  ETX_SSD1306_String("Device Driver\n");

  ETX_SSD1306_SetCursor(6, 37);
  ETX_SSD1306_String("Tutorial\n");

  msleep(9000);

  ETX_SSD1306_ClearDisplay();
  ETX_SSD1306_DeactivateScroll();

  ETX_SSD1306_PrintLogo();

  pr_info("OLED Initialized\n");

  return 0;
}

/****************************************************************************
 * REMOVE
 ****************************************************************************/
static int etx_remove(struct spi_device *spi)
{
  pr_info("SPI OLED Remove Called\n");

  ETX_SSD1306_ClearDisplay();
  ETX_SSD1306_DisplayDeInit();

  return 0;
}

/****************************************************************************
 * SPI DRIVER STRUCTURE
 ****************************************************************************/
static struct spi_driver etx_spi_driver = {
    .driver = {
        .name = "etx-spi-ssd1306-driver",
    },
    .probe    = etx_probe,
    .remove   = etx_remove,
    .id_table = etx_spi_ids,
};

/****************************************************************************
 * INIT
 ****************************************************************************/
static int __init etx_spi_init(void)
{
  int ret;
  struct spi_master *master;

  pr_info("SPI Init\n");

  /* Register SPI driver */
  ret = spi_register_driver(&etx_spi_driver);
  if (ret) {
    pr_err("Driver registration failed\n");
    return ret;
  }

  /* Get SPI Master */
  master = spi_busnum_to_master(etx_spi_device_info.bus_num);
  if (!master) {
    pr_err("SPI Master not found\n");
    spi_unregister_driver(&etx_spi_driver);
    return -ENODEV;
  }

  /* Create SPI device */
  etx_spi_device = spi_new_device(master, &etx_spi_device_info);
  spi_master_put(master);

  if (!etx_spi_device) {
    pr_err("Failed to create SPI device\n");
    spi_unregister_driver(&etx_spi_driver);
    return -ENODEV;
  }

  pr_info("SPI device created\n");
  return 0;
}

/****************************************************************************
 * EXIT
 ****************************************************************************/
static void __exit etx_spi_exit(void)
{
  pr_info("SPI Exit\n");

  if (etx_spi_device)
    spi_unregister_device(etx_spi_device);

  spi_unregister_driver(&etx_spi_driver);
}

module_init(etx_spi_init);
module_exit(etx_spi_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SPI SSD1306 OLED Driver");
MODULE_VERSION("1.0");