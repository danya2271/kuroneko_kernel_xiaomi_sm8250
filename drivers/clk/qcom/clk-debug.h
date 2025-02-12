/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright (c) 2016, 2019, The Linux Foundation. All rights reserved. */

#ifndef __QCOM_CLK_DEBUG_H__
#define __QCOM_CLK_DEBUG_H__

#include <linux/platform_device.h>
#include "../clk.h"

/**
 * struct mux_regmap_names - Structure of mux regmap mapping
 * @mux:		pointer to a clock debug mux
 * @regmap_name:	corresponding regmap name used to match a debug mux to
			its regmap
 */
struct mux_regmap_names {
	struct clk_debug_mux *mux;
	const char *regmap_name;
};

/* Debugfs Measure Clocks */

/**
 * struct measure_clk_data - Structure of clk measure
 *
 * @cxo:		XO clock.
 * @xo_div4_cbcr:	offset of debug XO/4 div register.
 * @ctl_reg:		offset of debug control register.
 * @status_reg:		offset of debug status register.
 * @cbcr_offset:	branch register to turn on debug mux.
 */
struct measure_clk_data {
	struct clk *cxo;
	u32 ctl_reg;
	u32 status_reg;
	u32 xo_div4_cbcr;
};

/**
 * struct clk_debug_mux - Structure of clock debug mux
 *
 * @mux_sels:		indicates the debug mux index at recursive debug mux.
 * @pre_div_val:	optional divider values for clocks that were pre-divided
			before feeding into the debug muxes
 * @num_parents:	number of parents
 * @regmap:		regmaps of debug mux
 * @priv:		private measure_clk_data to be used by debug mux
 * @en_mask:		indicates the enable bit mask at global clock
 *			controller debug mux.
 * @debug_offset:	debug mux offset.
 * @post_div_offset:	register with post-divider settings for the debug mux.
 * @cbcr_offset:	branch register to turn on debug mux.
 * @src_sel_mask:	indicates the mask to be used for src selection in
			primary mux.
 * @src_sel_shift:	indicates the shift required for source selection in
			primary mux.
 * @post_div_mask:	indicates the post div mask to be used for the primary
			mux.
 * @post_div_shift:	indicates the shift required for post divider
			selection in primary mux.
 * @period_offset:	offset of the period register used to read to determine
			the mc clock period
 * @hw:			handle between common and hardware-specific interfaces.
 */
struct clk_debug_mux {
	int *mux_sels;
	int *pre_div_vals;
	int num_parents;
	struct regmap *regmap;
	void *priv;
	u32 en_mask;
	u32 debug_offset;
	u32 cbcr_offset;
	u32 src_sel_mask;
	u32 src_sel_shift;
	u32 post_div_offset;
	u32 post_div_mask;
	u32 post_div_shift;
	u32 post_div_val;
	u32 period_offset;
	u32 bus_cl_id;
	struct clk_hw hw;
};

#define to_clk_measure(_hw) container_of((_hw), struct clk_debug_mux, hw)

extern const struct clk_ops clk_debug_mux_ops;

static inline int clk_debug_measure_register(struct clk_hw *hw) {return 0;};
static inline void clk_debug_measure_add(struct clk_hw *hw, struct dentry *dentry) {};
static inline void clk_debug_bus_vote(struct clk_hw *hw, bool enable) {};
static inline int map_debug_bases(struct platform_device *pdev, const char *base,
		    struct clk_debug_mux *mux) {return 0;};

#endif
