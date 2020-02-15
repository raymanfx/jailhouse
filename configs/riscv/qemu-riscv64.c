/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Configuration for QEMU riscv64 virtual target, 1G RAM, 4 cores
 *
 * Copyright (c) Siemens AG, 2020
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * NOTE: Add "mem=768M" to the kernel command line.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_system header;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[1];
} __attribute__((packed)) config = {
	.header = {
		.signature = JAILHOUSE_SYSTEM_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.flags = JAILHOUSE_SYS_VIRTUAL_DEBUG_CONSOLE,
		.hypervisor_memory = {
			.phys_start = 0xbfc00000,
			.size =       0x00400000,
		},
		.root_cell = {
			.name = "qemu-riscv64",

			.cpu_set_size = sizeof(config.cpus),
			.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		},
	},

	.cpus = {
		0xf,
	},

	.mem_regions = {
		/* RAM */ {
			.phys_start = 0x80000000,
			.virt_start = 0x80000000,
			.size = 0x3fa10000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE,
		},
	}
};
