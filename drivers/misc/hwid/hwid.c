/*
 * Copyright (C) 2021 XiaoMi, Inc.
 *               2022 The LineageOS Project
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <linux/module.h>
#include <soc/qcom/socinfo.h>

#include "hwid.h"

#define HW_MAJOR_VERSION_SHIFT      16
#define HW_MINOR_VERSION_SHIFT      0
#define HW_COUNTRY_VERSION_SHIFT    20
#define HW_BUILD_VERSION_SHIFT      16
#define HW_MAJOR_VERSION_MASK       0xFFFF0000
#define HW_MINOR_VERSION_MASK       0x0000FFFF
#define HW_COUNTRY_VERSION_MASK     0xFFF00000
#define HW_BUILD_VERSION_MASK       0x000F0000

char *SOC_207_PRODUCTS[] = {
	"nuwa",
	"fuxi",
	"wangshu",
	"socrates",
	"ishtar",
	"babylon",
	"vermeer",
	"sheng"
};
int SOC_207_PRODUCT_CNT = sizeof(SOC_207_PRODUCTS) / sizeof(char*);

static uint project;
module_param(project, uint, 0444);

static uint hwid_value;
module_param(hwid_value, uint, 0444);

uint32_t get_hw_version_platform(void)
{
	return project;
}
EXPORT_SYMBOL(get_hw_version_platform);

uint32_t get_hw_id_value(void)
{
	return hwid_value;
}
EXPORT_SYMBOL(get_hw_id_value);

uint32_t get_hw_country_version(void)
{
	return (hwid_value & HW_COUNTRY_VERSION_MASK) >> HW_COUNTRY_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_country_version);

uint32_t get_hw_version_major(void)
{
	return (hwid_value & HW_MAJOR_VERSION_MASK) >> HW_MAJOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_major);

uint32_t get_hw_version_minor(void)
{
	return (hwid_value & HW_MINOR_VERSION_MASK) >> HW_MINOR_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_minor);

uint32_t get_hw_version_build(void)
{
	return (hwid_value & HW_BUILD_VERSION_MASK) >> HW_BUILD_VERSION_SHIFT;
}
EXPORT_SYMBOL(get_hw_version_build);

char* product_name_get(void) {
	int soc_id = socinfo_get_id();
	char **product_array = NULL;
	int product_count = 0;
	int index = 0;

	switch(soc_id) {
		case 0x207: // SM8550
			product_array = SOC_207_PRODUCTS;
			product_count = SOC_207_PRODUCT_CNT;
			index = project - 1;
			break;
		default:
			goto unknown;
	}

	if (index < product_count && product_array != NULL) {
		return product_array[index];
	}

unknown:
	return "unknown";
}
EXPORT_SYMBOL(product_name_get);

MODULE_AUTHOR("weixiaotian1@xiaomi.com");
MODULE_LICENSE("GPL v2");
