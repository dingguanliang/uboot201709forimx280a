/*
 * (C) Copyright 2011 Freescale Semiconductor, Inc.
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * Based on m28evk.h:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIGS_IMX280A_H__
#define __CONFIGS_IMX280A_H__

/* System configurations */
#define CONFIG_MX28				/* i.MX28 SoC */
#define CONFIG_MACH_TYPE	MACH_TYPE_IMX280A

/* Memory configuration */
#define CONFIG_NR_DRAM_BANKS		1		/* 1 bank of DRAM */
#define PHYS_SDRAM_1			0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE		0x4000000	/* Max 64 MB RAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#ifndef CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SIZE			(16 * 1024)
#else
#define CONFIG_ENV_SIZE			(4 * 1024)
#endif
#define CONFIG_ENV_OVERWRITE

/* Environment is in MMC */
#if defined(CONFIG_CMD_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		    (64 * 1024)    /* env offset is 64KB */
#define CONFIG_SYS_MMC_ENV_DEV		0               /* env dev is 0 */
#endif

/* Environment is in NAND */
#if defined(CONFIG_CMD_NAND) && defined(CONFIG_ENV_IS_IN_NAND)
#define CONFIG_ENV_SIZE_REDUND		CONFIG_ENV_SIZE /* second env size */
#define CONFIG_ENV_SECT_SIZE		(128 * 1024)
#define CONFIG_ENV_RANGE		    (512 * 1024)
#define CONFIG_ENV_OFFSET		    0x300000        /* env offset is 3MB */
#define CONFIG_ENV_OFFSET_REDUND	\
		(CONFIG_ENV_OFFSET + CONFIG_ENV_RANGE)      /* second env offset is 3MB+512KB */
#endif

/* UBI and NAND partitioning */
#ifdef CONFIG_CMD_NAND
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define MTDIDS_DEFAULT			"nand0=gpmi-nand"
#define MTDPARTS_DEFAULT			\
	"mtdparts=gpmi-nand:"			\
		"3m(bootloader)ro,"		\
		"512k(environment),"		\
		"512k(redundant-environment),"	\
		"10m(kernel),"			\
		"512k(fdt),"			\
		"20m(ramdisk),"			\
		"-(filesystem)"
#endif

/* RTC */
#ifdef  CONFIG_CMD_DATE
#define CONFIG_RTC_MXS
#endif

/* Boot Linux */
#define CONFIG_BOOTFILE		    "uImage"
#define CONFIG_LOADADDR		    0x41ffffa0
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

#if defined(CONFIG_CMD_MMC)
#define CONFIG_EXTRA_ENV_SETTINGS   \
    "mmc_args=setenv bootargs console=ttyAMA0,${baudrate} init=/sbin/init root=/dev/mmcblk0p3 rootwait rw"
#define CONFIG_BOOTCOMMAND \
    "run mmc_args; fatload mmc 0:1 ${loadaddr} ${bootfile}; "   \
    "bootm ${loadaddr}"
#elif defined(CONFIG_CMD_NAND)
#define CONFIG_EXTRA_ENV_SETTINGS   \
    "nand_args=setenv bootargs console=ttyAMA0,${baudrate} ubi.mtd=6 root=ubi0:rootfs rootfstype=ubifs " \
    MTDPARTS_DEFAULT
#define CONFIG_BOOTCOMMAND  \
    "run nand_args; nand read ${loadaddr} 0x400000 0x600000; "   \
    "bootm 0x41ffffa0"
#else
#define CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_BOOTCOMMAND
#endif

/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_IMX280A_H__ */
