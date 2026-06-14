/****************************************************************************//**
*  \file       spi_ssd1306_driver.c
*******************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/spi/spi.h>
#include <linux/delay.h>
#include <linux/mod_devicetable.h>

#include "ssd1306.h"

/* File-scoped pointer needed by your helper library */
static struct spi_device *etx_spi_device = NULL;

/****************************************************************************
 * SPI Write
 ****************************************************************************/
int etx_spi_write(uint8_t data)
{
  int ret;
  uint8_t rx = 0x00;
  struct spi_transfer tr = {
    .tx_buf = &data,
    .rx_buf = &rx,
    .len    = 1,
  };

  if (!etx_spi_device)
    return -ENODEV;

  ret = spi_sync_transfer(etx_spi_device, &tr, 1);
  return ret;
}

/****************************************************************************
 * DRIVER MATCHING TABLES (Modern Approach)
 ****************************************************************************/
/* Legacy SPI bus matching */
static const struct spi_device_id etx_spi_ids[] = {
    { "ssd1306", 0 },
    { }
};
MODULE_DEVICE_TABLE(spi, etx_spi_ids);

/* Modern OpenFirmware (Device Tree) matching */
static const struct of_device_id etx_spi_of_match[] = {
    { .compatible = "solomon,ssd1306", },
    { }
};
MODULE_DEVICE_TABLE(of, etx_spi_of_match);

/****************************************************************************
 * PROBE
 ****************************************************************************/
static int etx_probe(struct spi_device *spi)
{
  int ret;

  pr_info("SPI OLED Probe Called\n");

  /* Save the hardware device context when the kernel discovers it */
  etx_spi_device = spi;

  spi->bits_per_word = 8;
  spi->mode = SPI_MODE_0;

  ret = spi_setup(spi);
  if (ret) {
    dev_err(&spi->dev, "SPI setup failed\n");
    return ret;
  }

  /* OLED INITIALIZATION */
  ETX_SSD1306_DisplayInit();
  ETX_SSD1306_SetBrightness(255);
  ETX_SSD1306_InvertDisplay(false);
  ETX_SSD1306_StartScrollHorizontal(true, 0, 2);

  ETX_SSD1306_SetCursor(0, 0);
  ETX_SSD1306_String("Welcome\nTo\nEmbeTronicX\n");

  msleep(2000); /* Reduced from 9000 to keep kernel execution responsive */

  ETX_SSD1306_ClearDisplay();
  ETX_SSD1306_DeactivateScroll();
  ETX_SSD1306_PrintLogo();

  dev_info(&spi->dev, "OLED Initialized Successfully\n");
  return 0;
}

/****************************************************************************
 * REMOVE
 ****************************************************************************/
static void etx_remove(struct spi_device *spi)
{
  dev_info(&spi->dev, "SPI OLED Remove Called\n");

  ETX_SSD1306_ClearDisplay();
  ETX_SSD1306_DisplayDeInit();
  etx_spi_device = NULL;
}

/****************************************************************************
 * SPI DRIVER STRUCTURE
 ****************************************************************************/
static struct spi_driver etx_spi_driver = {
    .driver = {
        .name = "etx-spi-ssd1306-driver",
        .of_match_table = etx_spi_of_match,
    },
    .probe    = etx_probe,
    .remove   = etx_remove,
    .id_table = etx_spi_ids,
};

/* Simplifies driver registration by building the init/exit boilerplates */
module_spi_driver(etx_spi_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modern SPI SSD1306 OLED Driver");
MODULE_VERSION("2.0");
#if 0
&spi0 {
    status = "okay";
    #address-cells = <1>;
    #size-cells = <0>;

    /* Your SSD1306 OLED Display Node */
    ssd1306_oled: oled@0 {
        compatible = "solomon,ssd1306";
        reg = <0>;                      /* Matches Chip Select 0 (CS0) */
        spi-max-frequency = <4000000>;   /* Sets communication speed to 4 MHz */
        status = "okay";
    };
};
#endif
